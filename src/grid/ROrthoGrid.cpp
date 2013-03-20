/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */
#include <math.h>

#include <QFontMetrics>

#include "RDebug.h"
#include "RDocumentInterface.h"
#include "RExporter.h"
#include "RGraphicsScene.h"
#include "RGraphicsView.h"
#include "RLine.h"
#include "ROrthoGrid.h"
#include "RSettings.h"
#include "RUcs.h"
#include "RUnit.h"



ROrthoGrid::ROrthoGrid(RGraphicsView &view)
  : RGrid(view),
    spacing(RVector::invalid),
    minSpacing(RVector::invalid),
    metaSpacing(RVector::invalid),
    scaleGrid(true),
    minPixelSpacing(10),
    isometric(-1),
    projection(-1)
{
    minPixelSpacing = RSettings::getIntValue("GraphicsView/MinGridSpacing", 10);
}



ROrthoGrid::~ROrthoGrid() {
}


void ROrthoGrid::clearCache() {
    RGrid::clearCache();
    isometric = -1;
    projection = -1;
}

/**
 * Maps the given model position to the grid.
 */
RVector ROrthoGrid::snapToGrid(const RVector& positionUcs) {
    RDocumentInterface* documentInterface = view.getDocumentInterface();
    if (documentInterface==NULL) {
        return RVector::invalid;
    }

    RVector sp = spacing;
    if (!sp.isValid()) {
        sp = metaSpacing;
        if (isometric) {
            sp /= 2;
        }
    }

    int x = RMath::mround(positionUcs.x / sp.x);
    int y = RMath::mround(positionUcs.y / sp.y);
    int z = RMath::mround(positionUcs.z / sp.z);

    // closest grid point is not available in isometric grid,
    // find closest available grid point:
    if (isometric && (x+y)%2!=0) {
        int cx, cy;
        double minDist = RMAXDOUBLE;
        double dist;
        for (int ix=-1; ix<=1; ix++) {
            for (int iy=-1; iy<=1; iy++) {
                if (qAbs(ix) + qAbs(iy)!=1) {
                    continue;
                }
                cx = RMath::mround(positionUcs.x / sp.x) + ix;
                cy = RMath::mround(positionUcs.y / sp.y) + iy;
                dist = positionUcs.getDistanceTo(RVector(cx*sp.x, cy*sp.y));
                if (dist<minDist) {
                    x = cx;
                    y = cy;
                    minDist = dist;
                }
            }
        }
    }

    RVector gridPositionUcs = RVector(
        x * sp.x,
        y * sp.y,
        z * sp.z
    );

    RUcs ucs = documentInterface->getCurrentUcs();
    return ucs.mapFromUcs(gridPositionUcs);
}



/**
 * Updates the grid information, in particular the grid spacing and
 * grid region to the current view port.
 */
void ROrthoGrid::update(bool force) {
    if (!force && viewBox==view.getBox()) {
        return;
    }

    viewBox = view.getBox();
    int viewportNumber = view.getViewportNumber();

    RDocument* doc = view.getDocument();
    if (doc == NULL) {
        qWarning() << "ROrthoGrid::update: document is NULL";
        return;
    }


    RGraphicsScene* scene = view.getScene();
    if (scene==NULL) {
        qWarning() << "ROrthoGrid::update: scene is NULL";
        return;
    }

    RS::ProjectionRenderingHint hint =  scene->getProjectionRenderingHint();

    // for 3d views, we have no convenient way to calculate the grid dimensions:
    if (hint == RS::RenderThreeD) {
        gridBox = RBox(RVector(-1000, -1000), RVector(1000, 1000));
        spacing = RVector(10.0, 10.0);
        return;
    }

    QString key;

    // backwards compatibility:
    //QVariant isometricDefault = doc->getVariable("Grid/IsometricGrid", QVariant(), false);
    //if (viewportNumber==0 && isometricDefault.isValid()) {
    //
    //}
    key = QString("Grid/IsometricGrid0%1").arg(viewportNumber);
    isometric = doc->getVariable(key, false, true).toBool();

    RS::Unit unit = doc->getUnit();
    RS::LinearFormat linearFormat = doc->getLinearFormat();

    // init values for missing configurations and 'auto' settings:
    minSpacing.valid = true;
    if (isFractionalFormat(linearFormat) && !RUnit::isMetric(unit)) {
        minSpacing.x = minSpacing.y = RUnit::convert(1.0, RS::Inch, unit) / 1024;
    }
    else {
        minSpacing.x = minSpacing.y = 1.0e-6;
    }

    QList<RVector> s = getIdealSpacing(minPixelSpacing, minSpacing);
    autoSpacing = s.at(0);
    autoMetaSpacing = s.at(1);
    /*
    if (isometric) {
        autoSpacing.x = autoSpacing.y * 2.0 * sin(M_PI/3.0);
        autoMetaSpacing.x = autoMetaSpacing.y * 2.0 * sin(M_PI/3.0);
    }
    */

    // backwards compatibility:
    //QVariant strSxDefault = doc->getVariable("Grid/GridSpacingX", QVariant(), true);
    key = QString("Grid/GridSpacingX0%1").arg(viewportNumber);
    QVariant strSx = doc->getVariable(key, QVariant(), true);
    // backwards compatibility:
    //QVariant strSyDefault = doc->getVariable("Grid/GridSpacingY", QVariant(), true);
    key = QString("Grid/GridSpacingY0%1").arg(viewportNumber);
    QVariant strSy = doc->getVariable(key, QVariant(), true);

    spacing.valid = true;

    // grid spacing x:
    if (strSx.isValid() && strSx.toString()!="auto") {
        // fixed:
        double d = RMath::eval(strSx.toString());
        if (!RMath::hasError() && d>RS::PointTolerance) {
            minSpacing.x = spacing.x = d;
        }
    }
    else {
        // auto:
        spacing.x = autoSpacing.x;
    }

    if (view.mapDistanceToView(spacing.x) < minPixelSpacing) {
        spacing = RVector::invalid;
    }

    // grid spacing y:
    if (strSy.isValid() && strSy.toString()!="auto") {
        double d = RMath::eval(strSy.toString());
        if (!RMath::hasError() && d>RS::PointTolerance) {
            minSpacing.y = spacing.y = d;
        }
    }
    else {
        // auto:
        spacing.y = autoSpacing.y;
    }

    if (view.mapDistanceToView(spacing.y) < minPixelSpacing) {
        spacing = RVector::invalid;
    }

    //QVariant strMsxDefault = doc->getVariable("Grid/MetaGridSpacingX", QVariant(), true);
    key = QString("Grid/MetaGridSpacingX0%1").arg(viewportNumber);
    QVariant strMsx = doc->getVariable(key, QVariant(), true);
    //QVariant strMsyDefault = doc->getVariable("Grid/MetaGridSpacingY", QVariant(), true);
    key = QString("Grid/MetaGridSpacingY0%1").arg(viewportNumber);
    QVariant strMsy = doc->getVariable(key, QVariant(), true);

    metaSpacing.valid = true;

    // meta grid spacing x:
    if (strMsx.isValid() && strMsx.toString()!="auto") {
        // fixed:
        double d = RMath::eval(strMsx.toString());
        if (d>RS::PointTolerance) {
            metaSpacing.x = d;
        }
    }
    else {
        // auto:
        metaSpacing.x = autoMetaSpacing.x;
    }

    if (view.mapDistanceToView(metaSpacing.x) < minPixelSpacing) {
        metaSpacing = RVector::invalid;
    }

    // meta grid spacing y:
    if (strMsy.isValid() && strMsy.toString()!="auto") {
        // fixed:
        double d = RMath::eval(strMsy.toString());
        if (d>RS::PointTolerance) {
            metaSpacing.y = d;
        }
    }
    else {
        // auto:
        metaSpacing.y = autoMetaSpacing.y;
    }

    if (view.mapDistanceToView(metaSpacing.y) < minPixelSpacing) {
        metaSpacing = RVector::invalid;
    }

//    qDebug() << "spacing: " << spacing;
//    qDebug() << "minSpacing: " << minSpacing;
//    qDebug() << "metaSpacing: " << metaSpacing;

//    if (scaleGrid) {
//        QList<RVector> s = ROrthoGrid::getIdealSpacing(view, minPixelSpacing, minSpacing);
//        spacing = s.at(0);
//        metaSpacing = s.at(1);
//    } else {
//        spacing = minSpacing;
//    }
    
    RVector minGridPoint;
    RVector maxGridPoint;

    spacing.z = 1;

    if (isometric) {
        spacing.x = spacing.y * 2.0 * sin(M_PI/3.0);
        metaSpacing.x = metaSpacing.y * 2.0 * sin(M_PI/3.0);

        spacing = spacing / 2;
        //metaSpacing = metaSpacing / 2;
    }

    minGridPoint = viewBox.getCorner1();
    minGridPoint = minGridPoint.getDividedComponents(spacing).getFloor();
    minGridPoint = minGridPoint.getMultipliedComponents(spacing);

    maxGridPoint = viewBox.getCorner2();
    maxGridPoint = maxGridPoint.getDividedComponents(spacing).getCeil();
    maxGridPoint = maxGridPoint.getMultipliedComponents(spacing);

    minGridPoint.z = viewBox.getCorner1().z;
    maxGridPoint.z = viewBox.getCorner2().z;
    
    gridBox = RBox(minGridPoint, maxGridPoint);

    minGridPoint = viewBox.getCorner1();
    minGridPoint = minGridPoint.getDividedComponents(metaSpacing).getFloor();
    minGridPoint = minGridPoint.getMultipliedComponents(metaSpacing);

    maxGridPoint = viewBox.getCorner2();
    maxGridPoint = maxGridPoint.getDividedComponents(metaSpacing).getCeil();
    maxGridPoint = maxGridPoint.getMultipliedComponents(metaSpacing);

    minGridPoint.z = viewBox.getCorner1().z;
    maxGridPoint.z = viewBox.getCorner2().z;
    
    metaGridBox = RBox(minGridPoint, maxGridPoint);

    if (isometric) {
        QString i1 = RUnit::getLabel(spacing.x / cos(M_PI/6), *doc, true, true);
        QString i2 = RUnit::getLabel(metaSpacing.x / cos(M_PI/6) / 2, *doc, true, true);
        infoText = QString("%1 < %2").arg(i1).arg(i2);
    }
    else {
        QString i1 = RUnit::getLabel(spacing.x, *doc, true, true);
        QString i2 = RUnit::getLabel(metaSpacing.x, *doc, true, true);
        infoText = QString("%1 < %2").arg(i1).arg(i2);
    }
}

bool ROrthoGrid::isFractionalFormat(RS::LinearFormat linearFormat) {
    if (linearFormat==RS::ArchitecturalStacked ||
        linearFormat==RS::FractionalStacked ||
        linearFormat==RS::Architectural ||
        linearFormat==RS::Fractional) {

        return true;
    }
    else {
        return false;
    }
}

QList<RVector> ROrthoGrid::getIdealSpacing(int minPixelSpacing, const RVector& minSpacing) {
    return ROrthoGrid::getIdealGridSpacing(view, minPixelSpacing, minSpacing);
}

QList<RVector> ROrthoGrid::getIdealGridSpacing(RGraphicsView& view, int minPixelSpacing, const RVector& minSpacing) {
    RS::Unit unit = view.getDocument()->getUnit();
    RS::LinearFormat linearFormat = view.getDocument()->getLinearFormat();
    QList<RVector> ret;

    if (isFractionalFormat(linearFormat) && !RUnit::isMetric(unit)) {
        double idealInchSpacing = RUnit::convert(view.mapDistanceFromView(qMax(minPixelSpacing, 1)), unit, RS::Inch);

        RVector spacing = RUnit::convert(minSpacing, unit, RS::Inch);
        spacing.x = inchAutoscale(spacing.x, idealInchSpacing, unit);
        spacing.y = inchAutoscale(spacing.y, idealInchSpacing, unit);
        spacing = RUnit::convert(spacing, RS::Inch, unit);

        // never drop below min spacing:
        if (spacing.x<minSpacing.x) {
            spacing.x = minSpacing.x;
        }
        if (spacing.y<minSpacing.y) {
            spacing.y = minSpacing.y;
        }

        RVector metaSpacing = spacing; // RVector(1.0 / 64, 1.0 / 64, 1.0 / 64);
        metaSpacing.x = inchAutoscale(metaSpacing.x, idealInchSpacing * 4, unit);
        metaSpacing.y = inchAutoscale(metaSpacing.y, idealInchSpacing * 4, unit);

        metaSpacing = RUnit::convert(metaSpacing, RS::Inch, unit);

        // foot: never show meta grid of < 1 foot:
        if (unit==RS::Foot) {
            if (metaSpacing.x<1.0) {
                metaSpacing.x = 1.0;
            }
            if (metaSpacing.y<1.0) {
                metaSpacing.y = 1.0;
            }
        }

        ret.append(spacing);
        ret.append(metaSpacing);
        return ret;
    } else {
        // ideal (minimum) grid spacing for the given view (some odd number):
        double idealSpacing = view.mapDistanceFromView(qMax(minPixelSpacing, 1));

        // idealSpacing = minSpacing * idealFactor
        RVector idealFactor(idealSpacing / minSpacing.x,
                            idealSpacing / minSpacing.y);

        // idealFactor = minSpacing * 10^n
        RVector n(log(idealFactor.x / minSpacing.x) / log(10.0),
                  log(idealFactor.y / minSpacing.y) / log(10.0));

        // factor = minSpacing * 10^ceil(n)
        RVector factor(minSpacing.x * pow(10.0, ceil(n.x - 1.0e-6)),
                       minSpacing.y * pow(10.0, ceil(n.y - 1.0e-6)));

        // never drop below min spacing:
        if (factor.x<1.0) {
            factor.x = 1.0;
        }
        if (factor.y<1.0) {
            factor.y = 1.0;
        }

        ret.append(RVector(minSpacing.x * factor.x, minSpacing.y * factor.y));
        ret.append(ret.at(0) * 10);

        return ret;
    }
}

double ROrthoGrid::inchAutoscale(double value, double idealSpacing, RS::Unit unit) {
    while (value < idealSpacing) {
        if (RMath::mround(value) >= 36) {
            value *= 2;
        } else if (RMath::mround(value) >= 12) {
            value *= 3;
        } else if (RMath::mround(value) >= 4) {
            value *= 3;
        } else if (RMath::mround(value) >= 1) {
            value *= 2;
        } else {
            value *= 2;
        }
    }

    if (unit==RS::Mile) {
        // more than a mile but not dividable by a mile, correct:
        if (RMath::mround(value)>5280*12 && RMath::mround(value)%(5280*12)!=0) {
            int f = RMath::mround(value) / (5280*12);
            value = 5280*12*f;
        }
    }

    return value;
}

void ROrthoGrid::paint() {
    if (!spacing.isValid()) {
        return;
    }

    RVector min = gridBox.getCorner1();
    RVector max = gridBox.getCorner2();

    if ((max.x - min.x) / spacing.x > 1e3 || (max.y - min.y) / spacing.y > 1e3) {
        return;
    }

    RVector gridPointUcs;
    int x, y;
    for (gridPointUcs.x = min.x; gridPointUcs.x < max.x; gridPointUcs.x += spacing.x) {
        x = RMath::mround(gridPointUcs.x/spacing.x);
        for (gridPointUcs.y = min.y; gridPointUcs.y < max.y; gridPointUcs.y += spacing.y) {
            y = RMath::mround(gridPointUcs.y/spacing.y);
            if (!isometric || (x+y)%2==0) {
                view.paintGridPoint(gridPointUcs);
            }
        }
    }
}

void ROrthoGrid::paintMetaGrid() {
    if (!metaSpacing.isValid()) {
        return;
    }

    // updates cache if necessary:
    getProjection();
    isIsometric();

    RVector min = metaGridBox.getCorner1();
    RVector max = metaGridBox.getCorner2();

    double deltaX = max.x - min.x;
    double deltaY = max.y - min.y;

    if (deltaX / metaSpacing.x > 1e3 || deltaY / metaSpacing.y > 1e3) {
        return;
    }

    double dx = deltaY / tan(M_PI/6);
    if (isometric) {
        min.x -= dx;
        max.x += dx;
    }
    for (double x=min.x; x<max.x; x+=metaSpacing.x) {
        if (isometric) {
//            qDebug() << "painting isometr. meta grid: x: " << x;
//            qDebug() << "painting isometr. meta grid: dx: " << dx;

            if (projection==RS::IsoTop || projection==RS::IsoRight) {
                view.paintGridLine(RLine(RVector(x, min.y), RVector(x+dx, max.y)));
            }
            if (projection==RS::IsoTop || projection==RS::IsoLeft) {
                view.paintGridLine(RLine(RVector(x, min.y), RVector(x-dx, max.y)));
            }

            // vertical meta grid lines:
            if (projection==RS::IsoRight || projection==RS::IsoLeft) {
                view.paintGridLine(RLine(RVector(x, min.y), RVector(x, max.y)));
                view.paintGridLine(RLine(RVector(x-metaSpacing.x/2, min.y), RVector(x-metaSpacing.x/2, max.y)));
            }
        }
        else {
            view.paintGridLine(RLine(RVector(x, min.y), RVector(x, max.y)));
        }
    }

    for (double y=min.y; y<max.y; y+=metaSpacing.y) {
        if (isometric) {

        }
        else {
            view.paintGridLine(RLine(RVector(min.x, y), RVector(max.x, y)));
        }
    }
}

void ROrthoGrid::paintCursor(const RVector& pos) {
    // crosshair size:
    double s = 0;
    if (!RSettings::getShowLargeCrosshair()) {
        s = view.mapDistanceFromView(25);
    }

    RBox b = view.getBox();
    if (isometric) {
        double dxp, dyp, dxn, dyn;
        if (RSettings::getShowLargeCrosshair()) {
            dxp = b.c2.x - pos.x;
            dyp = tan(M_PI/6) * dxp;
            dxn = pos.x - b.c1.x;
            dyn = tan(M_PI/6) * dxn;
        }
        else {
            dxp = dxn = cos(M_PI/6) * s;
            dyp = dyn = sin(M_PI/6) * s;
        }

        // .-´
        if (projection==RS::IsoTop || projection==RS::IsoRight) {
            view.paintGridLine(RLine(pos + RVector(dxp,dyp), pos - RVector(dxn,dyn)));
        }
        // `-.
        if (projection==RS::IsoTop || projection==RS::IsoLeft) {
            view.paintGridLine(RLine(pos + RVector(dxp,-dyp), pos - RVector(dxn,-dyn)));
        }

        // |
        if (projection==RS::IsoRight || projection==RS::IsoLeft) {
            if (RSettings::getShowLargeCrosshair()) {
                view.paintGridLine(RLine(RVector(pos.x, b.c1.y), RVector(pos.x, b.c2.y)));
            }
            else {
                view.paintGridLine(RLine(RVector(pos.x, pos.y - s), RVector(pos.x, pos.y + s)));
            }
        }
    }
    else {
        if (RSettings::getShowLargeCrosshair()) {
            view.paintGridLine(RLine(RVector(b.c1.x, pos.y), RVector(b.c2.x, pos.y)));
            view.paintGridLine(RLine(RVector(pos.x, b.c1.y), RVector(pos.x, b.c2.y)));
        }
        else {
            double s = view.mapDistanceFromView(25);
            RVector sx(s, 0);
            RVector sy(0, s);
            view.paintGridLine(RLine(pos-sx, pos+sx));
            view.paintGridLine(RLine(pos-sy, pos+sy));
        }
    }
}

void ROrthoGrid::paintRuler(RRuler& ruler) {
    RDocument* doc = view.getDocument();
    if (doc == NULL) {
        return;
    }

    RS::Unit unit = doc->getUnit();
    RS::LinearFormat linearFormat = doc->getLinearFormat();

    // use grid spacing if available or auto grid spacing:
    RVector localSpacing = spacing;
    if (!localSpacing.isValid() || autoSpacing.getMagnitude2d() < localSpacing.getMagnitude2d()) {
        localSpacing = autoSpacing;
    }

    // use meta grid spacing if available or auto meta grid spacing:
    RVector localMetaSpacing = metaSpacing;
    if (!localMetaSpacing.isValid() || autoMetaSpacing.getMagnitude2d() < localMetaSpacing.getMagnitude2d()) {
        localMetaSpacing = autoMetaSpacing;
    }

    if (!localMetaSpacing.isValid()) {
        return;
    }

    if (localSpacing.getMagnitude()<1.0e-6 || localMetaSpacing.getMagnitude()<1.0e-6)  {
        return;
    }

    RVector min = gridBox.getCorner1();
    RVector max = gridBox.getCorner2();
    bool isHorizontal = ruler.getOrientation() == Qt::Horizontal;

    double tickSpacing;
    //if (!RUnit::isMetric(doc->getUnit())) {
    if (isFractionalFormat(linearFormat) && !RUnit::isMetric(unit)) {
        if (isHorizontal) {
            tickSpacing = localSpacing.x;
        } else {
            tickSpacing = localSpacing.y;
        }
    } else {
        if (isHorizontal) {
            tickSpacing = localMetaSpacing.x;
        } else {
            tickSpacing = localMetaSpacing.y;
        }
        if (view.mapDistanceToView(tickSpacing) >= 80) {
            tickSpacing /= 10;
        } else if (view.mapDistanceToView(tickSpacing) >= 30) {
            tickSpacing /= 5;
        } else if (view.mapDistanceToView(tickSpacing) >= 20) {
            tickSpacing /= 2;
        }
    }
    int pSpacing = (int) ceil(view.mapDistanceToView(tickSpacing));

    QString l1 = RUnit::getLabel(isHorizontal ? min.x : min.y, *doc, false, true);
    QString l2 = RUnit::getLabel(isHorizontal ? max.x : max.y, *doc, false, true);
    int labelWidth = std::max(
            QFontMetrics(ruler.getFont()).boundingRect(l1).width(),
            QFontMetrics(ruler.getFont()).boundingRect(l2).width()) + 15;
    int minLabelStep = labelWidth / pSpacing + 1;

    int labelStep = minLabelStep;
    //if (!RUnit::isMetric(doc->getUnit())) {
    if (isFractionalFormat(linearFormat) && !RUnit::isMetric(unit)) {
        // non metric
        int f = 1;
        do {
            if (isHorizontal) {
                labelStep = RMath::mround(localMetaSpacing.x / localSpacing.x) * f;
            } else {
                labelStep = RMath::mround(localMetaSpacing.y / localSpacing.y) * f;
            }
            f = f * 2;
            if (f>65536) {
                labelStep = -1;
            }
        } while (labelStep < minLabelStep && labelStep>0);
    } else {
        // metric
        if (labelStep >= 3 && labelStep <= 4) {
            labelStep = 5;
        } else if (labelStep >= 6 && labelStep <= 9) {
            labelStep = 10;
        } else if (labelStep >= 11 && labelStep <= 19) {
            labelStep = 20;
        } else if (labelStep >= 21 && labelStep <= 99) {
            labelStep = 100;
        }
    }

    if (labelStep<0) {
        return;
    }

    double minPos;
    double maxPos;
    if (isHorizontal) {
        minPos = (floor(view.mapFromView(RVector(0, 0)).x
                / (labelStep * tickSpacing))-1) * (labelStep * tickSpacing);
        maxPos = (ceil(view.mapFromView(RVector(view.getWidth(), 0)).x
                / (labelStep * tickSpacing))+1) * (labelStep * tickSpacing);
    } else {
        minPos = (floor(view.mapFromView(RVector(0, view.getHeight())).y
                / (labelStep * tickSpacing))-1) * (labelStep * tickSpacing);
        maxPos = (ceil(view.mapFromView(RVector(0, 0)).y
                / (labelStep * tickSpacing))+1) * (labelStep * tickSpacing);
    }

    if ((maxPos - minPos) / tickSpacing > 1e3) {
        return;
    }

    int c;
    double p;
    for (c = 0, p = minPos; p < maxPos; p += tickSpacing, ++c) {
        bool hasLabel = c % labelStep == 0;
        double v;
        if (isHorizontal) {
            v = view.mapToView(RVector(p, 0)).x;
        } else {
            v = view.mapToView(RVector(0, p)).y;
        }
        ruler.paintTick(v, hasLabel, hasLabel ? RUnit::getLabel(p, *doc, false, true) : QString());
    }
}

QString ROrthoGrid::getInfoText() {
    //return QString("%1 / %2").arg(spacing.x).arg(metaSpacing.x);
    return infoText;
}

bool ROrthoGrid::isIsometric() const {
    if (isometric==-1) {
        int viewportNumber = getViewportNumber();
        if (viewportNumber==-1) {
            return false;
        }

        RDocument* doc = getDocument();
        if (doc==NULL) {
            return false;
        }
        isometric = (int)doc->getVariable(QString("Grid/IsometricGrid0%1").arg(viewportNumber), false, true).toBool();
    }
    return isometric;
}

void ROrthoGrid::setIsometric(bool on) {
    isometric = (int)on;

    int viewportNumber = getViewportNumber();
    if (viewportNumber==-1) {
        return;
    }

    RDocument* doc = getDocument();
    if (doc==NULL) {
        return;
    }

    doc->setVariable(QString("Grid/IsometricGrid0%1").arg(viewportNumber), on);
}

RS::IsoProjectionType ROrthoGrid::getProjection() const {
    if (projection==-1) {
        int viewportNumber = getViewportNumber();
        if (viewportNumber==-1) {
            return RS::IsoTop;
        }

        RDocument* doc = getDocument();
        if (doc==NULL) {
            return RS::IsoTop;
        }
        projection = (int)doc->getVariable(QString("Grid/IsometricProjection0%1").arg(viewportNumber), (int)RS::IsoTop, true).toInt();
    }
    return (RS::IsoProjectionType)projection;
}

void ROrthoGrid::setProjection(RS::IsoProjectionType p) {
    projection = (int)p;

    int viewportNumber = getViewportNumber();
    if (viewportNumber==-1) {
        return;
    }

    RDocument* doc = getDocument();
    if (doc==NULL) {
        return;
    }

    doc->setVariable(QString("Grid/IsometricProjection0%1").arg(viewportNumber), (int)p);
}
