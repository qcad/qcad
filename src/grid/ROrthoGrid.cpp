/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
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
    minMetaSpacing(RVector::invalid),
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

    key = QString("Grid/IsometricGrid0%1").arg(viewportNumber);
    isometric = doc->getVariable(key, false, true).toBool();

    RS::Unit unit = doc->getUnit();
    RS::LinearFormat linearFormat = doc->getLinearFormat();

    // default values for missing configurations and 'auto' settings:
    minSpacing.valid = true;
    minMetaSpacing.valid = true;
    if (isFractionalFormat(linearFormat) && !RUnit::isMetric(unit)) {
        //minSpacing.x = minSpacing.y = RNANDOUBLE;
        //minMetaSpacing.x = minMetaSpacing.y = RNANDOUBLE;
        minSpacing.x = minSpacing.y = RUnit::convert(1.0, RS::Inch, unit) / 1024;
        minMetaSpacing.x = minMetaSpacing.y = RUnit::convert(1.0, RS::Inch, unit) / 1024;
    }
    else {
        minSpacing.x = minSpacing.y = 1.0e-6;
        minMetaSpacing.x = minMetaSpacing.y = RNANDOUBLE;
        //minSpacing.x = minSpacing.y = RNANDOUBLE;
        //minMetaSpacing.x = minMetaSpacing.y = 1.0e-6;
    }

    key = QString("Grid/GridSpacingX0%1").arg(viewportNumber);
    QVariant strSx = doc->getVariable(key, QVariant(), true);
    key = QString("Grid/GridSpacingY0%1").arg(viewportNumber);
    QVariant strSy = doc->getVariable(key, QVariant(), true);

    spacing.valid = true;

    bool autoX = !strSx.isValid() || strSx.toString()=="auto";
    bool autoY = !strSy.isValid() || strSy.toString()=="auto";

    // grid spacing x:
    if (!autoX) {
        // fixed:
        double d = RMath::eval(strSx.toString());
        if (!RMath::hasError() && d>RS::PointTolerance) {
            minSpacing.x = spacing.x = d;
        }
    }

    // grid spacing y:
    if (!autoY) {
        double d = RMath::eval(strSy.toString());
        if (!RMath::hasError() && d>RS::PointTolerance) {
            minSpacing.y = spacing.y = d;
        }
    }




    // meta grid:
    key = QString("Grid/MetaGridSpacingX0%1").arg(viewportNumber);
    QVariant strMsx = doc->getVariable(key, QVariant(), true);
    key = QString("Grid/MetaGridSpacingY0%1").arg(viewportNumber);
    QVariant strMsy = doc->getVariable(key, QVariant(), true);

    metaSpacing.valid = true;

    bool metaAutoX = !strMsx.isValid() || strMsx.toString()=="auto";
    bool metaAutoY = !strMsy.isValid() || strMsy.toString()=="auto";

    // meta grid spacing x:
    if (!metaAutoX) {
        // fixed:
        double d = RMath::eval(strMsx.toString());
        if (d>RS::PointTolerance) {
            minMetaSpacing.x = metaSpacing.x = d;
        }
    }

    // meta grid spacing y:
    if (!metaAutoY) {
        // fixed:
        double d = RMath::eval(strMsy.toString());
        if (d>RS::PointTolerance) {
            minMetaSpacing.y = metaSpacing.y = d;
        }
    }

    int minDevicePixelSpacing = minPixelSpacing;

    if (RSettings::getHighResolutionGraphicsView()) {
        minDevicePixelSpacing *= RSettings::getDevicePixelRatio();
    }

    // auto scale grid:
    QList<RVector> s = getIdealSpacing(minDevicePixelSpacing, minSpacing, minMetaSpacing);
    if (RSettings::getAutoScaleGrid()) {
        autoSpacing = spacing = s.at(0);
    }
    if (RSettings::getAutoScaleMetaGrid()) {
        autoMetaSpacing = metaSpacing = s.at(1);
    }

    // switch grid off below given pixel limit:
    if (view.mapDistanceToView(spacing.x) < minDevicePixelSpacing) {
        spacing = RVector::invalid;
    }
    if (view.mapDistanceToView(metaSpacing.x) < minDevicePixelSpacing) {
        metaSpacing = RVector::invalid;
    }
    if (view.mapDistanceToView(spacing.y) < minDevicePixelSpacing) {
        spacing = RVector::invalid;
    }
    if (view.mapDistanceToView(metaSpacing.y) < minDevicePixelSpacing) {
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
        QString i1 = RUnit::getLabel(spacing.x / cos(M_PI/6), *doc, 8, true, true);
        QString i2 = RUnit::getLabel(metaSpacing.x / cos(M_PI/6) / 2, *doc, 8, true, true);
        infoText = QString("%1 < %2").arg(i1).arg(i2);
    }
    else {
        QString i1 = RUnit::getLabel(spacing.x, *doc, 8, true, true);
        QString i2 = RUnit::getLabel(metaSpacing.x, *doc, 8, true, true);
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

QList<RVector> ROrthoGrid::getIdealSpacing(int minPixelSpacing, const RVector& minSpacing, const RVector& minMetaSpacing) {
    return ROrthoGrid::getIdealGridSpacing(view, minPixelSpacing, minSpacing, minMetaSpacing);
}

QList<RVector> ROrthoGrid::getIdealGridSpacing(RGraphicsView& view, int minPixelSpacing, const RVector& minSpacing, const RVector& minMetaSpacing) {
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

        // never drop below min spacing:
        if (metaSpacing.x<minMetaSpacing.x) {
            metaSpacing.x = minMetaSpacing.x;
        }
        if (metaSpacing.y<minMetaSpacing.y) {
            metaSpacing.y = minMetaSpacing.y;
        }

        // foot: never show meta grid of < 1 foot:
        if (unit==RS::Foot) {
            if (metaSpacing.x<1.0) {
                metaSpacing.x = 1.0;
            }
            if (metaSpacing.y<1.0) {
                metaSpacing.y = 1.0;
            }
        }

//        if (metaSpacing.x < this->metaSpacing.x) {
//            metaSpacing.x = this->metaSpacing.x;
//        }

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

        // grid spacing:
        double x, y;
        x = minSpacing.x * factor.x;
        y = minSpacing.y * factor.y;
        ret.append(RVector(x,y));

        // meta grid spacing:
        double mx, my;
        if (RMath::isNaN(minMetaSpacing.x)) {
            mx = x * 10;
        }
        else {
            //mx = minMetaSpacing.x * factor.x;
            mx = minMetaSpacing.x;
        }

        if (RMath::isNaN(minMetaSpacing.y)) {
            my = y * 10;
        }
        else {
            //my = minMetaSpacing.y * factor.y;
            my = minMetaSpacing.y;
        }
        ret.append(RVector(mx, my));

        //ret.append(RVector(minSpacing.x * factor.x, minSpacing.y * factor.y));
        //ret.append(RVector(minMetaSpacing.x * factor.x, minMetaSpacing.y * factor.y));
        //ret.append(ret.at(0) * 10);

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
    // experimental, not working for isometric grid yet:
    if (!isometric && RSettings::getBoolValue("GraphicsView/SolidGridLines", false)) {
        RVector sp = spacing;
        //if (isometric) {
        //    sp *= 2;
        //}
        paintGridLines(sp, gridBox, false);
    }
    else {
        paintGridPoints(spacing, gridBox);
    }
}

void ROrthoGrid::paintMetaGrid() {
    paintGridLines(metaSpacing, metaGridBox, true);
}

void ROrthoGrid::paintGridPoints(const RVector& space, const RBox& box) {
    if (!space.isValid()) {
        return;
    }

    RVector min = box.getCorner1();
    RVector max = box.getCorner2();

    if ((max.x - min.x) / space.x > 1e3 || (max.y - min.y) / space.y > 1e3) {
        return;
    }

    RVector gridPointUcs;
    int x, y;
    for (gridPointUcs.x = min.x; gridPointUcs.x < max.x; gridPointUcs.x += space.x) {
        x = RMath::mround(gridPointUcs.x/space.x);
        for (gridPointUcs.y = min.y; gridPointUcs.y < max.y; gridPointUcs.y += space.y) {
            y = RMath::mround(gridPointUcs.y/space.y);
            if (!isometric || (x+y)%2==0) {
                view.paintGridPoint(gridPointUcs);
            }
        }
    }
}

void ROrthoGrid::paintGridLines(const RVector& space, const RBox& box, bool meta) {
    Q_UNUSED(meta)

    if (!space.isValid()) {
        return;
    }

    // updates cache if necessary:
    getProjection();
    isIsometric();

    RVector min = box.getCorner1();
    RVector max = box.getCorner2();

    double deltaX = max.x - min.x;
    double deltaY = max.y - min.y;

    if (deltaX / space.x > 1e3 || deltaY / space.y > 1e3) {
        return;
    }

    double dx = deltaY / tan(M_PI/6);
    if (isometric) {
        min.x -= dx;
        max.x += dx;
    }
    int c;
    double x;
    for (x=min.x, c=0; x<max.x; x+=space.x, c++) {
        //int x2 = RMath::mround(x/space.x);
        //if (!isometric || c%2==0) {
        if (isometric) {
            if (projection==RS::IsoTop || projection==RS::IsoRight) {
                view.paintGridLine(RLine(RVector(x, min.y), RVector(x+dx, max.y)));
            }
            if (projection==RS::IsoTop || projection==RS::IsoLeft) {
                view.paintGridLine(RLine(RVector(x, min.y), RVector(x-dx, max.y)));
            }

            // vertical grid lines:
            if (projection==RS::IsoRight || projection==RS::IsoLeft) {
                view.paintGridLine(RLine(RVector(x, min.y), RVector(x, max.y)));
                view.paintGridLine(RLine(RVector(x-space.x/2, min.y), RVector(x-space.x/2, max.y)));
            }
        }
        else {
            view.paintGridLine(RLine(RVector(x, min.y), RVector(x, max.y)));
        }
        //}
    }

    // horizontal lines:
    if (!isometric) {
        for (double y=min.y; y<max.y; y+=space.y) {
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

            // TODO: alternative cross hairs from corners to cursor:
//            view.paintGridLine(RLine(pos, RVector(b.c1.x, b.c1.y)));
//            view.paintGridLine(RLine(pos, RVector(b.c1.x, b.c2.y)));
//            view.paintGridLine(RLine(pos, RVector(b.c2.x, b.c1.y)));
//            view.paintGridLine(RLine(pos, RVector(b.c2.x, b.c2.y)));
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

void ROrthoGrid::paintRuler(RRuler& ruler, qreal devicePixelRatio) {
    RDocument* doc = view.getDocument();
    if (doc == NULL) {
        return;
    }

    RS::Unit unit = doc->getUnit();
    RS::LinearFormat linearFormat = doc->getLinearFormat();

    // use grid spacing if available or auto grid spacing:
    RVector localSpacing = spacing;
    if (!localSpacing.isValid() ||
        (autoSpacing.isValid() && autoSpacing.getMagnitude2D() < localSpacing.getMagnitude2D())) {
        localSpacing = autoSpacing;
    }

    // use meta grid spacing if available or auto meta grid spacing:
    RVector localMetaSpacing = metaSpacing;
    if (!localMetaSpacing.isValid() ||
        (autoMetaSpacing.isValid() && autoMetaSpacing.getMagnitude2D() < localMetaSpacing.getMagnitude2D())) {
        //localMetaSpacing = autoMetaSpacing;
    }

    //if (!localMetaSpacing.isValid()) {
    //    qDebug() << "no local meta spacing";
    //    return;
    //}

    if (localSpacing.getMagnitude()<1.0e-6 || localMetaSpacing.getMagnitude()<1.0e-6)  {
        //qDebug() << "local (meta) spacing too small";
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

    // ideal tick spacing in pixels:
    int pSpacing = (int) ceil(view.mapDistanceToView(tickSpacing));

    QString l1 = RUnit::getLabel(isHorizontal ? min.x : min.y, *doc, 8, false, true);
    QString l2 = RUnit::getLabel(isHorizontal ? max.x : max.y, *doc, 8, false, true);
    int labelWidth = std::max(
            QFontMetrics(ruler.getFont()).boundingRect(l1).width(),
            QFontMetrics(ruler.getFont()).boundingRect(l2).width()) + 15;

    // smallest displayable distance between labels in steps (ticks):
    int minLabelStep = 1;
    if (pSpacing>0) {
        minLabelStep = labelWidth / pSpacing + 1;
    }

    int labelStep = minLabelStep;
    //if (!RUnit::isMetric(doc->getUnit())) {
    if (isFractionalFormat(linearFormat) && !RUnit::isMetric(unit)) {
        // non metric
        double f = 1.0/128;
        do {
            if (localMetaSpacing.isValid()) {
                if (isHorizontal) {
                    labelStep = RMath::mround(localMetaSpacing.x / localSpacing.x) * f;
                } else {
                    labelStep = RMath::mround(localMetaSpacing.y / localSpacing.y) * f;
                }
            }
            else {
                labelStep = (int)f;
            }
            f = f * 2;
            if (f>65536) {
                labelStep = -1;
            }
        } while (labelStep < minLabelStep && labelStep>=0);
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

    if (labelStep<1) {
        labelStep = 1;
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
        ruler.paintTick(v*devicePixelRatio, hasLabel,
                        hasLabel ? RUnit::getLabel(p, *doc, 8, true, true) : QString());
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
            return RS::NoProjection;
        }

        RDocument* doc = getDocument();
        if (doc==NULL) {
            return RS::NoProjection;
        }
        projection = (int)doc->getVariable(QString("Grid/IsometricProjection0%1").arg(viewportNumber), (int)RS::NoProjection, true).toInt();
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
