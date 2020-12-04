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
#include "RBox.h"
#include "RDebug.h"
#include "RDocument.h"
#include "RDocumentVariables.h"
#include "RLinetypeListImperial.h"
#include "RLinetypeListMetric.h"
#include "RLinkedStorage.h"
#include "RMainWindow.h"
#include "RMath.h"
#include "RMemoryStorage.h"
#include "RMouseEvent.h"
#include "RSettings.h"
#include "RSpatialIndexSimple.h"
#include "RStorage.h"
#include "RUcs.h"
#include "RUnit.h"
#include "RPolyline.h"

RDocument* RDocument::clipboard = NULL;


/**
 * Creates a new document with the given storage as back-end.
 * The document takes ownership of the storage and spatial index.
 * A new document contains one layer ("0") and a number of default
 * line types. The default unit is Millimeter.
 */
RDocument::RDocument(
    RStorage& storage,
    RSpatialIndex& spatialIndex)
    : storage(storage),
      spatialIndex(spatialIndex),
      disableSpatialIndicesByBlock(false),
      transactionStack(storage),
      linetypeByLayerId(RObject::INVALID_ID),
      linetypeByBlockId(RObject::INVALID_ID),
      autoTransactionGroup(false) {

    storage.setDocument(this);
    init();
    RDebug::incCounter("RDocument");
}

//void RDocument::addLinetype(QString name) {
//    RTransaction t(storage, "", false);

//    if (queryLinetype(name).isNull()) {
//        t.addObject(QSharedPointer<RObject>(new RLinetype(this, name)));
//    }
//}

void RDocument::init(bool beforeLoad) {
    RS::Unit defaultUnit = (RS::Unit)RSettings::getValue("UnitSettings/Unit", RS::None).toInt();
    RS::Measurement measurement = (RS::Measurement)RSettings::getValue("UnitSettings/Measurement", RS::Metric).toInt();
    if (measurement!=RS::Metric && measurement!=RS::Imperial) {
        measurement = RUnit::isMetric(defaultUnit) ? RS::Metric : RS::Imperial;
    }

    RTransaction transaction(storage, "", false);
    transaction.setRecordAffectedObjects(false);
    transaction.setSpatialIndexDisabled(true);
    transaction.setBlockRecursionDetectionDisabled(true);

    RLinkedStorage* ls = dynamic_cast<RLinkedStorage*>(&storage);
    bool storageIsLinked = (ls!=NULL);

    // add document variables object:
    //if (!storageIsLinked && queryDocumentVariables().isNull()) {
    //if (!storageIsLinked && queryDocumentVariables().isNull()) {
    //    transaction.addObject(QSharedPointer<RDocumentVariables>(new RDocumentVariables(this)));
    //}
    QSharedPointer<RDocumentVariables> docVars = QSharedPointer<RDocumentVariables>(new RDocumentVariables(this));

    // add default line types if not already added (RLinkedStorage):
    if (!storageIsLinked && queryLinetype("BYLAYER").isNull()) {
        transaction.addObject(
            QSharedPointer<RLinetype>(
                new RLinetype(this, RLinetypePattern(measurement==RS::Metric, "BYLAYER", "By Layer"))
            )
        );
        transaction.addObject(
            QSharedPointer<RLinetype>(
                new RLinetype(this, RLinetypePattern(measurement==RS::Metric, "BYBLOCK", "By Block"))
            )
        );
        transaction.addObject(
            QSharedPointer<RLinetype>(
                new RLinetype(this, RLinetypePattern(measurement==RS::Metric, "Continuous", "Solid line"))
            )
        );
    }

    // add default layer:
    if (!storageIsLinked && queryLayer("0").isNull()) {
        RColor c = RSettings::getColorValue("Layer/DefaultColorLayer0", RColor(Qt::white));
        RLineweight::Lineweight lw = (RLineweight::Lineweight)RSettings::getIntValue("Layer/DefaultLineweightLayer0", RLineweight::Weight025);
        QSharedPointer<RLayer> layer0 = QSharedPointer<RLayer>(
            new RLayer(
                this, "0", false, false,
                c, getLinetypeId("CONTINUOUS"),
                lw
            )
        );
        transaction.addObject(layer0);
        //qDebug() << "id of layer 0: " << getLayerId("0");
    }

    storage.setLayer0Id(getLayerId("0"));

    // add model space block with layout:
    if (!storageIsLinked && queryBlock(RBlock::modelSpaceName).isNull()) {
        QSharedPointer<RLayout> modelLayout(
            new RLayout(
                this, "Model"
            )
        );
        transaction.addObject(modelLayout);

        QSharedPointer<RBlock> modelSpace(
            new RBlock(
                this, RBlock::modelSpaceName, RVector()
            )
        );
        transaction.addObject(modelSpace);
        modelSpace->setLayoutId(modelLayout->getId());
    }

    // add first default paper space with layout and viewport:
    if (!storageIsLinked && queryBlock(RBlock::paperSpaceName).isNull()) {
        QSharedPointer<RLayout> layout(
            new RLayout(
                this, "Layout1"
            )
        );
        transaction.addObject(layout);

        QSharedPointer<RBlock> paperSpace(
            new RBlock(
                this, RBlock::paperSpaceName, RVector()
            )
        );
        transaction.addObject(paperSpace);
        paperSpace->setLayoutId(layout->getId());

//        QSharedPointer<RViewportEntity> viewport(
//            new RViewportEntity(
//                this, RViewportData()
//            )
//        );
//        viewport->setCenter(RVector(128.5, 97.5));
//        viewport->setViewCenter(RVector(128.5, 97.5));
//        viewport->setViewTarget(RVector(0,0));
//        viewport->setWidth(314.226);
//        viewport->setHeight(222.18);
//        viewport->setOverall(true);
//        viewport->setBlockId(paperSpace->getId());
//        viewport->setLayerId(getLayerId("0"));

//        transaction.addObject(viewport, false);
    }

    storage.setModelSpaceBlockId(getBlockId(RBlock::modelSpaceName));

    // caching for faster operations:
    QSharedPointer<RLinetype> ltByLayer = queryLinetype("BYLAYER");
    if (!ltByLayer.isNull()) {
        linetypeByLayerId = ltByLayer->getId();
    }
    QSharedPointer<RLinetype> ltByBlock = queryLinetype("BYBLOCK");
    if (!ltByBlock.isNull()) {
        linetypeByBlockId = ltByBlock->getId();
    }

    if (!storageIsLinked) {
        docVars->setCurrentLayerId(getLayerId("0"));

        setCurrentBlock(RBlock::modelSpaceName);

        setCurrentLinetype("BYLAYER");

        // default variables:
        docVars->setUnit(defaultUnit);
        docVars->setMeasurement(measurement);
        initLinetypes(&transaction);
        docVars->setLinetypeScale(RSettings::getDoubleValue("LinetypeSettings/Scale", 1.0));

        // point display:
        docVars->setKnownVariable(RS::PDMODE, RSettings::getIntValue("PointDisplaySettings/Mode", 0));
        docVars->setKnownVariable(RS::PDSIZE, RSettings::getDoubleValue("PointDisplaySettings/Size", 0.0));

        // dimension properties:
        docVars->setKnownVariable(RS::DIMTXT, RSettings::getDoubleValue("DimensionSettings/DIMTXT", 2.5));
        docVars->setKnownVariable(RS::DIMEXE, RSettings::getDoubleValue("DimensionSettings/DIMEXE", 1.25));
        docVars->setKnownVariable(RS::DIMEXO, RSettings::getDoubleValue("DimensionSettings/DIMEXO", 0.625));
        docVars->setKnownVariable(RS::DIMGAP, RSettings::getDoubleValue("DimensionSettings/DIMGAP", 0.625));
        docVars->setKnownVariable(RS::DIMASZ, RSettings::getDoubleValue("DimensionSettings/DIMASZ", 2.5));
        docVars->setKnownVariable(RS::DIMSCALE, RSettings::getDoubleValue("DimensionSettings/DIMSCALE", 1.0));
        docVars->setKnownVariable(RS::DIMDLI, RSettings::getDoubleValue("DimensionSettings/DIMDLI", 5.0));
        docVars->setKnownVariable(RS::DIMCLRT, RSettings::getColorValue("DimensionSettings/DimensionTextColor", RColor(RColor::ByBlock)));

        // arrow head:
        if (RSettings::getStringValue("DimensionSettings/ArrowStyle", "Arrow")=="Arrow") {
            // tick size is 0 for arrows:
            docVars->setKnownVariable(RS::DIMTSZ, 0.0);
        }

        // arch tick head:
        else {
            docVars->setKnownVariable(RS::DIMTSZ, RSettings::getDoubleValue("DimensionSettings/DIMASZ", 2.5));
        }

        docVars->setKnownVariable(RS::DIMLUNIT, RSettings::getIntValue("DimensionSettings/LinearFormat", RS::Decimal));
        docVars->setKnownVariable(RS::DIMDEC, RSettings::getIntValue("DimensionSettings/LinearPrecision", 4));
        docVars->setKnownVariable(RS::DIMDSEP, RSettings::getIntValue("DimensionSettings/DecimalPoint", '.'));

        // show trailing zeroes:
        if (RSettings::getBoolValue("DimensionSettings/LinearShowTrailingZeros", false)) {
            docVars->setKnownVariable(RS::DIMZIN, 0);
        }

        // suppress trailing zeroes:
        else {
            docVars->setKnownVariable(RS::DIMZIN, 8);
        }

        docVars->setKnownVariable(RS::DIMAUNIT, RSettings::getIntValue("DimensionSettings/AngularFormat", RS::DegreesDecimal));
        docVars->setKnownVariable(RS::DIMADEC, RSettings::getIntValue("DimensionSettings/AngularPrecision", 0));

        // show trailing zeroes:
        if (RSettings::getBoolValue("DimensionSettings/AngularShowTrailingZeros", false)) {
            docVars->setKnownVariable(RS::DIMAZIN, 0);
        }

        // suppress trailing zeroes:
        else {
            docVars->setKnownVariable(RS::DIMAZIN, 2);
        }

        // max number of active viewports:
        docVars->setKnownVariable(RS::MAXACTVP, 64);

        // mirror text:
        docVars->setKnownVariable(RS::MIRRTEXT, RSettings::getIntValue("TextSettings/MirrorText", 0));

        //  multi page printing settings:
        setVariable("MultiPageSettings/Columns", RSettings::getIntValue("MultiPageSettings/Columns", 1));
        setVariable("MultiPageSettings/Rows", RSettings::getIntValue("MultiPageSettings/Rows", 1));
        setVariable("MultiPageSettings/GlueMarginsLeft", RSettings::getDoubleValue("MultiPageSettings/GlueMarginsLeft", 0));
        setVariable("MultiPageSettings/GlueMarginsTop", RSettings::getDoubleValue("MultiPageSettings/GlueMarginsTop", 0));
        setVariable("MultiPageSettings/GlueMarginsRight", RSettings::getDoubleValue("MultiPageSettings/GlueMarginsRight", 0));
        setVariable("MultiPageSettings/GlueMarginsBottom", RSettings::getDoubleValue("MultiPageSettings/GlueMarginsBottom", 0));
        setVariable("MultiPageSettings/PrintCropMarks", RSettings::getBoolValue("MultiPageSettings/PrintCropMarks", false));

        // color printing settings:
        setVariable("ColorSettings/ColorMode", RSettings::getStringValue("ColorSettings/ColorMode", "FullColor"));
        RColor col = RSettings::getColorValue("ColorSettings/BackgroundColor", RColor(QString("white")));
        QVariant v;
        v.setValue<RColor>(col);
        setVariable("ColorSettings/BackgroundColor", v);

        // printer page settings:
        QString vs;
        double vd;

        // paper size:
        vd = RSettings::getDoubleValue("PageSettings/PaperWidth", 0);
        if (vd<1.0e-4) {
            vd = 210;
        }
        setVariable("PageSettings/PaperWidth", vd);

        vd = RSettings::getDoubleValue("PageSettings/PaperHeight", 0);
        if (vd<1.0e-4) {
            vd = 297;
        }
        setVariable("PageSettings/PaperHeight", vd);

        // orientation:
        vs = RSettings::getStringValue("PageSettings/PageOrientation", "");
        if (vs.isEmpty()) {
            vs = "Portrait";
        }
        setVariable("PageSettings/PageOrientation", vs);

        // paper unit:
        setVariable("UnitSettings/PaperUnit", RSettings::getIntValue("UnitSettings/PaperUnit", RS::Millimeter));

        // offset:
        setVariable("PageSettings/OffsetX", RSettings::getDoubleValue("PageSettings/OffsetX", 0));
        setVariable("PageSettings/OffsetY", RSettings::getDoubleValue("PageSettings/OffsetY", 0));

        // scale:
        vs = RSettings::getStringValue("PageSettings/Scale", "1:1");
        if (vs.isEmpty()) {
            vs = "1:1";
        }
        setVariable("PageSettings/Scale", vs);

        setVariable("PageSettings/ShowPaperBorders", RSettings::getBoolValue("PageSettings/ShowPaperBorders", true));
        //setVariable("PageSettings/ShowBoundingBox", RSettings::getBoolValue("PageSettings/ShowBoundingBox", false));

        setVariable("PageTagSettings/EnablePageTags", RSettings::getBoolValue("PageTagSettings/EnablePageTags", false));
        setVariable("PageTagSettings/TagAlignment", RSettings::getValue("PageTagSettings/TagAlignment", "Inside"));
        setVariable("PageTagSettings/TagFont", RSettings::getValue("PageTagSettings/TagFont", QFont("Arial", 10)));
        setVariable("PageTagSettings/TagPosition", RSettings::getValue("PageTagSettings/TagPosition", "TopLeft"));

        // grid settings:
        QString s;
        for (int i=0; i<4; i++) {
            s = QString("Grid/DisplayGrid0%1").arg(i);
            setVariable(s, RSettings::getBoolValue(s, true));
            s = QString("Grid/IsometricGrid0%1").arg(i);
            setVariable(s, RSettings::getBoolValue(s, false));
            s = QString("Grid/IsometricProjection0%1").arg(i);
            setVariable(s, RSettings::getIntValue(s, (int)RS::IsoTop));
            s = QString("Grid/GridSpacingX0%1").arg(i);
            setVariable(s, RSettings::getStringValue(s, "auto"));
            s = QString("Grid/GridSpacingY0%1").arg(i);
            setVariable(s, RSettings::getStringValue(s, "auto"));
            s = QString("Grid/MetaGridSpacingX0%1").arg(i);
            setVariable(s, RSettings::getStringValue(s, "auto"));
            s = QString("Grid/MetaGridSpacingY0%1").arg(i);
            setVariable(s, RSettings::getStringValue(s, "auto"));
        }

        docVars->setDimensionFont(RSettings::getStringValue("DimensionSettings/DimensionFont", "Standard"));

        // notify new document listeners
        if (RMainWindow::hasMainWindow()) {
            RMainWindow::getMainWindow()->notifyNewDocumentListeners(this, &transaction, beforeLoad);
        }
    }

    transaction.addObject(docVars);

    transaction.end();
    resetTransactionStack();
    storage.setModified(false);
}

void RDocument::initLinetypes(RTransaction* transaction) {
    bool useLocalTransaction = (transaction==NULL);
    if (useLocalTransaction) {
        transaction = new RTransaction(storage, "", false);
    }

    QList<QSharedPointer<RObject> > lts = getDefaultLinetypes();
    for (int i=0; i<lts.length(); i++) {
        transaction->addObject(lts[i]);
    }

    if (useLocalTransaction) {
        transaction->end();
        delete transaction;
    }
}

QList<QSharedPointer<RObject> > RDocument::getDefaultLinetypes() {
    QList<QSharedPointer<RObject> > ret;

    // read patterns from file system and add to doc:
    QStringList patternList;
    if (RUnit::isMetric(getUnit())) {
        patternList = RLinetypeListMetric::getNames();
    }
    else {
        patternList = RLinetypeListImperial::getNames();
    }
    for (int i = 0; i < patternList.length(); i++) {
        QString name = patternList[i];

        RLinetypePattern* pattern = NULL;
        if (RUnit::isMetric(getUnit())) {
            pattern = RLinetypeListMetric::get(name);
        }
        else {
            pattern = RLinetypeListImperial::get(name);
        }

        if (pattern!=NULL) {
            QSharedPointer<RLinetype> lt = queryLinetype(name);
            if (lt.isNull()) {
                // add new pattern:
                lt = QSharedPointer<RLinetype>(new RLinetype(this, *pattern));
            }
            else {
                // replace previous pattern (e.g. on unit change):
                lt->setPatternString(pattern->getPatternString());
                lt->setMetric(pattern->isMetric());
                lt->setName(pattern->getName());
                lt->setDescription(pattern->getDescription());
            }
            ret.append(lt);
        }
    }

    return ret;
}


/**
 * Resets this document to its initial, empty state.
 */
void RDocument::clear(bool beforeLoad) {
    // preserve unit:
    RS::Unit u = getUnit();

    fileName = "";
    storage.clear();
    clearSpatialIndices();

    init(beforeLoad);
    setUnit(u);

    transactionStack.reset();
}


RDocument::~RDocument() {
    RDebug::decCounter("RDocument");
    storage.doDelete();
    clearSpatialIndices();
    spatialIndex.doDelete();
}

void RDocument::setUnit(RS::Unit unit, RTransaction* transaction) {
    storage.setUnit(unit, transaction);
    initLinetypes(transaction);
}

RS::Unit RDocument::getUnit() const {
    return storage.getUnit();
}

void RDocument::setMeasurement(RS::Measurement m,  RTransaction* transaction) {
    storage.setMeasurement(m, transaction);
    initLinetypes(transaction);

    // update hatches:
    QSet<REntity::Id> ids = storage.queryAllEntities(false, true);

    QSetIterator<REntity::Id> i(ids);
    while (i.hasNext()) {
        QSharedPointer<REntity> entity = storage.queryEntityDirect(i.next());
        if (entity.isNull()) {
            continue;
        }
        if (entity->isUndone()) {
            continue;
        }
        if (entity->getType()!=RS::EntityHatch) {
            continue;
        }
        qDebug() << "update hatch";
        entity->update();
        //RHatchEntity* hatch = dynamic_cast<RHatchEntity*>(entity);
    }
}

/**
 * \copydoc RStorage::getMeasurement
 */
RS::Measurement RDocument::getMeasurement() const {
    return storage.getMeasurement();
}

bool RDocument::isMetric() const {
    RS::Measurement m = getMeasurement();

    if (m==RS::UnknownMeasurement) {
        return RUnit::isMetric(getUnit());
    }

    return m==RS::Metric;
}

/**
 * \copydoc RStorage::setDimensionFont
 */
void RDocument::setDimensionFont(const QString& f, RTransaction* transaction) {
    storage.setDimensionFont(f, transaction);
}

/**
 * \copydoc RStorage::getDimensionFont
 */
QString RDocument::getDimensionFont() const {
    return storage.getDimensionFont();
}

/**
 * \copydoc RStorage::setLinetypeScale
 */
void RDocument::setLinetypeScale(double v, RTransaction* transaction) {
    storage.setLinetypeScale(v, transaction);
}

/**
 * \copydoc RStorage::getLinetypeScale
 */
double RDocument::getLinetypeScale() const {
    return storage.getLinetypeScale();
}

QString RDocument::formatLinear(double value) {
    return RUnit::formatLinear(
        value,
        getUnit(),
        getLinearFormat(),
        getLinearPrecision(),
        false,
        showLeadingZeroes(),
        showTrailingZeroes(),
        false
    );
}

QString RDocument::formatAngle(double value) {
    return RUnit::formatAngle(
        value,
        getAngleFormat(),
        getAnglePrecision(),
        showLeadingZeroesAngle(),
        showTrailingZeroesAngle()
    );
}

/**
 * \return The linear format type for this document.
 * This is determined by the variable "$DIMLUNIT".
 */
RS::LinearFormat RDocument::getLinearFormat() const {
    return (RS::LinearFormat)getKnownVariable(RS::DIMLUNIT, 2).toInt();
}

void RDocument::setLinearFormat(RS::LinearFormat f) {
    setKnownVariable(RS::DIMLUNIT, f);
}


/**
 * \return The linear precision for this document.
 * This is determined by the variable "$DIMDEC".
 */
int RDocument::getLinearPrecision() {
    return getKnownVariable(RS::DIMDEC, 4).toInt();
}



bool RDocument::showLeadingZeroes() {
    return !(getKnownVariable(RS::DIMZIN, 8).toInt() & 4);
}


bool RDocument::showTrailingZeroes() {
    return !(getKnownVariable(RS::DIMZIN, 8).toInt() & 8);
}

bool RDocument::showLeadingZeroesAngle() {
    return !(getKnownVariable(RS::DIMAZIN, 3).toInt() & 1);
}


bool RDocument::showTrailingZeroesAngle() {
    return !(getKnownVariable(RS::DIMAZIN, 3).toInt() & 2);
}


/**
 * \return The angle format type for this document.
 * This is determined by the variable "$DIMAUNIT".
 */
RS::AngleFormat RDocument::getAngleFormat() {
    return (RS::AngleFormat)getKnownVariable(RS::DIMAUNIT, 0).toInt();
}

/**
 * \return The angular precision for this document.
 * This is determined by the variable "$DIMADEC".
 */
int RDocument::getAnglePrecision() {
    return getKnownVariable(RS::DIMADEC, 2).toInt();
}

/**
 * \return The decimal separator for this document.
 * This is determined by the variable "$DIMDSEP".
 * 0 means '.'.
 */
char RDocument::getDecimalSeparator() {
    int ret = (char)getKnownVariable(RS::DIMDSEP, (int)'.').toInt();
    if (ret==0) {
        ret = '.';
    }
    return ret;
}

/**
 * \copydoc RStorage::getVariables
 */
QStringList RDocument::getVariables() const {
    return storage.getVariables();
}

/**
 * \copydoc RStorage::hasVariable
 */
bool RDocument::hasVariable(const QString& key) const {
    return storage.hasVariable(key);
}

/**
 * \copydoc RStorage::removeVariable
 */
void RDocument::removeVariable(const QString& key) {
    storage.removeVariable(key);
}

/**
 * \copydoc RStorage::setVariable
 */
void RDocument::setVariable(const QString& key, const QVariant& value, bool overwrite) {
    storage.setVariable(key, value, overwrite);
}

/**
 * \copydoc RStorage::getVariable
 */
QVariant RDocument::getVariable(const QString& key, const QVariant& defaultValue, bool useSettings) const {
    QVariant ret = storage.getVariable(key);
    if (!ret.isValid()) {
        if (useSettings) {
            return RSettings::getValue(key, defaultValue);
        }
        ret = defaultValue;
    }
    return ret;
}

/**
 * \copydoc RStorage::setKnownVariable
 */
void RDocument::setKnownVariable(RS::KnownVariable key, const QVariant& value, RTransaction* transaction) {
    storage.setKnownVariable(key, value, transaction);

    if (key==RS::MEASUREMENT) {
        initLinetypes(transaction);
    }
}

/**
 * \copydoc RStorage::setKnownVariable
 */
void RDocument::setKnownVariable(RS::KnownVariable key, const RVector& value, RTransaction* transaction) {
    QVariant v;
    v.setValue(value);
    storage.setKnownVariable(key, v, transaction);
}

/**
 * \copydoc RStorage::getKnownVariable
 */
QVariant RDocument::getKnownVariable(RS::KnownVariable key, const QVariant& defaultValue) const {
    QVariant ret = storage.getKnownVariable(key);
    if (!ret.isValid()) {
        ret = defaultValue;
    }
    return ret;
}

/**
 * \copydoc RStorage::queryCurrentLayer
 */
QSharedPointer<RLayer> RDocument::queryCurrentLayer() {
    return storage.queryCurrentLayer();
}

/**
 * \copydoc RStorage::getCurrentLayerId
 */
RLayer::Id RDocument::getCurrentLayerId() const {
    return storage.getCurrentLayerId();
//    QSharedPointer<RDocumentVariables> v = queryDocumentVariablesDirect();
//    v->getCurrentLayerId();
}

/**
 * \copydoc RStorage::getCurrentLayerName
 */
QString RDocument::getCurrentLayerName() const {
    return getLayerName(storage.getCurrentLayerId());
}

/**
 * \copydoc RStorage::setCurrentColor
 */
void RDocument::setCurrentColor(const RColor& color) {
    storage.setCurrentColor(color);
}

/**
 * \copydoc RStorage::getCurrentColor
 */
RColor RDocument::getCurrentColor() const {
    return storage.getCurrentColor();
}

/**
 * \copydoc RStorage::setCurrentLineweight
 */
void RDocument::setCurrentLineweight(RLineweight::Lineweight lw) {
    storage.setCurrentLineweight(lw);
}

/**
 * \copydoc RStorage::getCurrentLineweight
 */
RLineweight::Lineweight RDocument::getCurrentLineweight() const {
    return storage.getCurrentLineweight();
}

/**
 * \copydoc RStorage::setCurrentLinetype
 */
void RDocument::setCurrentLinetype(RLinetype::Id ltId) {
    storage.setCurrentLinetype(ltId);
}

/**
 * \copydoc RStorage::setCurrentLinetype
 */
void RDocument::setCurrentLinetype(const QString& name) {
    storage.setCurrentLinetype(name);
}

/**
 * \copydoc RStorage::setCurrentLinetypePattern
 */
void RDocument::setCurrentLinetypePattern(const RLinetypePattern& p) {
    storage.setCurrentLinetypePattern(p);
}

/**
 * \copydoc RStorage::getCurrentLinetypeId
 */
RLinetype::Id RDocument::getCurrentLinetypeId() const {
    return storage.getCurrentLinetypeId();
}

/**
 * \copydoc RStorage::getCurrentLinetypePattern
 */
RLinetypePattern RDocument::getCurrentLinetypePattern() const {
    return storage.getCurrentLinetypePattern();
}

//RTransaction RDocument::setCurrentLayer(RLayer::Id layerId) {
//    return storage.setCurrentLayer(layerId);
////    RTransaction transaction(getStorage(), "Setting current layer", true);
////    setCurrentLayer(transaction, layerId);
////    transaction.end(this);
////    return transaction;
//}

//RTransaction RDocument::setCurrentLayer(const QString& layerName) {
//    return storage.setCurrentLayer(layerName);
////    RLayer::Id id = getLayerId(layerName);
////    if (id == RLayer::INVALID_ID) {
////        return RTransaction();
////    }
////    return setCurrentLayer(id);
//}

/**
 * \copydoc RStorage::setCurrentLayer
 */
void RDocument::setCurrentLayer(RLayer::Id layerId, RTransaction* transaction) {
    storage.setCurrentLayer(layerId, transaction);
}

/**
 * \copydoc RStorage::setCurrentLayer
 */
void RDocument::setCurrentLayer(const QString& layerName, RTransaction* transaction) {
    storage.setCurrentLayer(layerName, transaction);
}

//void RDocument::setCurrentLayer(RTransaction& transaction, RLayer::Id layerId) {
//    storage.setCurrentLayer(transaction, layerId);
////    QSharedPointer<RDocumentVariables> v = queryDocumentVariables();
////    v->setCurrentLayerId(layerId);
////    transaction.addObject(v);
//}

//void RDocument::setCurrentLayer(RTransaction& transaction, const QString& layerName) {
//    storage.setCurrentLayer(transaction, layerName);
////    RLayer::Id id = getLayerId(layerName);
////    if (id == RLayer::INVALID_ID) {
////        return;
////    }
////    setCurrentLayer(transaction, id);
//}

/**
 * \copydoc RStorage::queryCurrentBlock
 */
QSharedPointer<RBlock> RDocument::queryCurrentBlock() {
    return storage.queryCurrentBlock();
}

/**
 * \copydoc RStorage::getCurrentBlockId
 */
RBlock::Id RDocument::getCurrentBlockId() const {
    return storage.getCurrentBlockId();
}

QString RDocument::getCurrentBlockName() const {
    return getBlockName(storage.getCurrentBlockId());
}

void RDocument::setCurrentBlock(RBlock::Id blockId) {
    RBlock::Id prevBlockId = getCurrentBlockId();

    removeBlockFromSpatialIndex(blockId);

    storage.setCurrentBlock(blockId);

    // add references to block we're leaving to spatial index:
    if (prevBlockId!=RBlock::INVALID_ID) {
        addBlockToSpatialIndex(prevBlockId, blockId);
    }
}

void RDocument::setCurrentBlock(const QString& blockName) {
    //storage.setCurrentBlock(blockName);
    RBlock::Id id = getBlockId(blockName);
    if (id == RBlock::INVALID_ID) {
        return;
    }
    setCurrentBlock(id);
}

void RDocument::setCurrentViewport(RObject::Id viewportId) {
    storage.setCurrentViewport(viewportId);
}

RObject::Id RDocument::getCurrentViewportId() {
    return storage.getCurrentViewportId();
}

bool RDocument::hasCurrentViewport() {
    return getCurrentViewportId()!=RObject::INVALID_ID;
}

void RDocument::unsetCurrentViewport() {
    storage.unsetCurrentViewport();
}

QString RDocument::getTempBlockName() const {
    do {
        int p1 = qrand() % 100000;
        int p2 = qrand() % 100000;
        QString blockName = QString("A$C%1%2").arg(p1, 5, 10, QChar('0')).arg(p2, 5, 10, QChar('0'));
        if (!hasBlock(blockName)) {
            return blockName;
        }
    } while(true);
}

/**
 * \copydoc RStorage::getBlockName
 */
QString RDocument::getBlockName(RBlock::Id blockId) const {
    return storage.getBlockName(blockId);
}

QString RDocument::getBlockNameFromLayout(const QString& layoutName) const {
    return storage.getBlockNameFromLayout(layoutName);
}

QString RDocument::getBlockNameFromLayout(RLayout::Id layoutId) const {
    return storage.getBlockNameFromLayout(layoutId);
}

/**
 * \copydoc RStorage::getBlockNames
 */
QSet<QString> RDocument::getBlockNames(const QString& rxStr) const {
    return storage.getBlockNames(rxStr);
}

QList<RBlock::Id> RDocument::sortBlocks(const QList<RBlock::Id>& blockIds) const {
    return storage.sortBlocks(blockIds);
}

QList<RLayer::Id> RDocument::sortLayers(const QList<RLayer::Id>& layerIds) const {
    return storage.sortLayers(layerIds);
}

/**
 * \copydoc RStorage::setCurrentView
 */
void RDocument::setCurrentView(RView::Id viewId) {
    storage.setCurrentView(viewId);
}

/**
 * \copydoc RStorage::setCurrentView
 */
void RDocument::setCurrentView(const QString& viewName) {
    storage.setCurrentView(viewName);
}

/**
 * \copydoc RStorage::getCurrentViewId
 */
RView::Id RDocument::getCurrentViewId() const {
    return storage.getCurrentViewId();
}

/**
 * \copydoc RStorage::queryCurrentView
 */
QSharedPointer<RView> RDocument::queryCurrentView() {
    return storage.queryCurrentView();
}

/**
 * \copydoc RStorage::hasView
 */
bool RDocument::hasView(const QString& viewName) const {
    return storage.hasView(viewName);
}

/**
 * \copydoc RStorage::getLayerName
 */
QString RDocument::getLayerName(RLayer::Id layerId) const {
    return storage.getLayerName(layerId);
}

/**
 * \copydoc RStorage::getLayerNames
 */
QSet<QString> RDocument::getLayerNames(const QString& rxStr) const {
    return storage.getLayerNames(rxStr);
}

/**
 * \copydoc RStorage::getLayerStateName
 */
QString RDocument::getLayerStateName(RLayerState::Id layerStateId) const {
    return storage.getLayerStateName(layerStateId);
}

/**
 * \copydoc RStorage::getLayerStateNames
 */
QSet<QString> RDocument::getLayerStateNames(const QString& rxStr) const {
    return storage.getLayerStateNames(rxStr);
}

/**
 * \copydoc RStorage::getLayoutName
 */
QString RDocument::getLayoutName(RLayout::Id layoutId) const {
    return storage.getLayoutName(layoutId);
}

/**
 * \copydoc RStorage::getViewNames
 */
QSet<QString> RDocument::getViewNames() const {
    return storage.getViewNames();
}

/**
 * \copydoc RStorage::hasLayer
 */
bool RDocument::hasLayer(const QString& layerName) const {
    return storage.hasLayer(layerName);
}

/**
 * \copydoc RStorage::hasLayerStates
 */
bool RDocument::hasLayerStates() const {
    return storage.hasLayerStates();
}

/**
 * \copydoc RStorage::hasLayerState
 */
bool RDocument::hasLayerState(const QString& layerStateName) const {
    return storage.hasLayerState(layerStateName);
}

/**
 * \copydoc RStorage::getLayerId
 */
RLayer::Id RDocument::getLayerId(const QString& layerName) const {
    return storage.getLayerId(layerName);
}

RLayer::Id RDocument::getLayer0Id() const {
    return storage.getLayer0Id();
}

/**
 * \copydoc RStorage::getLayerStateId
 */
RLayerState::Id RDocument::getLayerStateId(const QString& layerStateName) const {
    return storage.getLayerStateId(layerStateName);
}

/**
 * \copydoc RStorage::hasBlock
 */
bool RDocument::hasBlock(const QString& blockName) const {
    return storage.hasBlock(blockName);
}

/**
 * \copydoc RStorage::hasLayout
 */
bool RDocument::hasLayout(const QString& layoutName) const {
    return storage.hasLayout(layoutName);
}

/**
 * \copydoc RStorage::hasLinetype
 */
bool RDocument::hasLinetype(const QString& linetypeName) const {
    return storage.hasLinetype(linetypeName);
}

/**
 * \copydoc RStorage::getBlockId
 */
RBlock::Id RDocument::getBlockId(const QString& blockName) const {
    return storage.getBlockId(blockName);
}

/**
 * \copydoc RStorage::getBlockIdAuto
 */
RBlock::Id RDocument::getBlockIdAuto(const QString& blockLayoutName) const {
    return storage.getBlockIdAuto(blockLayoutName);
}

/**
 * \copydoc RStorage::getModelSpaceBlockId
 */
RBlock::Id RDocument::getModelSpaceBlockId() const {
    return storage.getModelSpaceBlockId();
}

/**
 * \copydoc RStorage::getLinetypeName
 */
QString RDocument::getLinetypeName(RLinetype::Id linetypeId) const {
    return storage.getLinetypeName(linetypeId);
}

/**
 * \copydoc RStorage::getLinetypeDescription
 */
QString RDocument::getLinetypeDescription(RLinetype::Id linetypeId) const {
    return storage.getLinetypeDescription(linetypeId);
}

/**
 * \copydoc RStorage::getLinetypeLabel
 */
QString RDocument::getLinetypeLabel(RLinetype::Id linetypeId) const {
    return storage.getLinetypeLabel(linetypeId);
}

/**
 * \copydoc RStorage::getLinetypeId
 */
RLinetype::Id RDocument::getLinetypeId(const QString& linetypeName) const {
    return storage.getLinetypeId(linetypeName);
}

/**
 * \copydoc RStorage::getLinetypeNames
 */
QSet<QString> RDocument::getLinetypeNames() const {
    return storage.getLinetypeNames();
}

/**
 * \copydoc RStorage::getLinetypePatterns
 */
QList<RLinetypePattern> RDocument::getLinetypePatterns() const {
    return storage.getLinetypePatterns();
}

bool RDocument::isByLayer(RLinetype::Id linetypeId) const {
    return linetypeId == linetypeByLayerId;
}

bool RDocument::isByBlock(RLinetype::Id linetypeId) const {
    return linetypeId == linetypeByBlockId;
}

RLineweight::Lineweight RDocument::getMaxLineweight() const {
    return storage.getMaxLineweight();
}

void RDocument::setFileName(const QString& fn) {
    fileName = fn;
}

QString RDocument::getFileName() const {
    return fileName;
}

void RDocument::setFileVersion(const QString& fv) {
    fileVersion = fv;
}

QString RDocument::getFileVersion() const {
    return fileVersion;
}

void RDocument::resetTransactionStack() {
    transactionStack.reset();
}

bool RDocument::isUndoAvailable() const {
    return transactionStack.isUndoAvailable();
}

bool RDocument::isRedoAvailable() const {
    return transactionStack.isRedoAvailable();
}

/**
 * \copydoc RStorage::startTransactionGroup
 */
void RDocument::startTransactionGroup() {
    storage.startTransactionGroup();
}

/**
 * \copydoc RStorage::getTransactionGroup
 */
int RDocument::getTransactionGroup() const {
    return storage.getTransactionGroup();
}


/**
 * \return Reference to storage that backs the document.
 */
RStorage& RDocument::getStorage() {
    return storage;
}

const RStorage& RDocument::getStorage() const {
    return storage;
}

/**
 * \return Reference to the spatial index.
 */
RSpatialIndex& RDocument::getSpatialIndex() {
    return spatialIndex;
}

const RSpatialIndex& RDocument::getSpatialIndex() const {
    return spatialIndex;
}

RSpatialIndex* RDocument::getSpatialIndexForBlock(RBlock::Id blockId) const {
    if (disableSpatialIndicesByBlock) {
        return &spatialIndex;
    }

    if (!spatialIndicesByBlock.contains(blockId)) {
        spatialIndicesByBlock.insert(blockId, spatialIndex.create());
    }
    return spatialIndicesByBlock[blockId];
}

RSpatialIndex* RDocument::getSpatialIndexForCurrentBlock() const {
    RBlock::Id currentBlockId = getCurrentBlockId();
    return getSpatialIndexForBlock(currentBlockId);
}

/**
 * \return Reference to the transaction stack for undo/redo handling.
 */
RTransactionStack& RDocument::getTransactionStack() {
    return transactionStack;
}



/**
 * Queries all objects of this document.
 *
 * \return Set of object IDs.
 */
QSet<RObject::Id> RDocument::queryAllObjects() const {
    return storage.queryAllObjects();
}

/**
 * \copydoc RStorage::queryAllVisibleEntities
 */
QSet<REntity::Id> RDocument::queryAllVisibleEntities() const {
    return storage.queryAllVisibleEntities();
}

/**
 * Queries all entities of this document. This operation can be
 * slow, depending on the total number of entities and the
 * storage type that is used for this document.
 *
 * \return Set of entity IDs.
 */
QSet<REntity::Id> RDocument::queryAllEntities(bool undone, bool allBlocks, RS::EntityType type) const {
    return storage.queryAllEntities(undone, allBlocks, type);
}

/**
 * \copydoc RStorage::queryAllEntities
 */
QSet<REntity::Id> RDocument::queryAllEntities(bool undone, bool allBlocks, QList<RS::EntityType> types) const {
    return storage.queryAllEntities(undone, allBlocks, types);
}

/**
 * \copydoc RStorage::queryWorkingSetEntities
 */
QSet<REntity::Id> RDocument::queryWorkingSetEntities() const {
    return storage.queryWorkingSetEntities();
}

/**
 * Queries all UCSs of this document.
 *
 * \return Set of UCS IDs.
 */
QSet<RUcs::Id> RDocument::queryAllUcs() const {
    return storage.queryAllUcs();
}

/**
 * Queries all layers of this document.
 *
 * \return Set of layer IDs.
 */
QSet<RLayer::Id> RDocument::queryAllLayers() const {
    return storage.queryAllLayers();
}

/**
 * Queries all layer state objects of this document.
 *
 * \return Set of layer state IDs.
 */
QSet<RLayer::Id> RDocument::queryAllLayerStates() const {
    return storage.queryAllLayerStates();
}

/*
QList<RLayer::Id> RDocument::queryAllLayers() const {
    QSet<RLayer::Id> result;
    storage.queryAllLayers(result);
    return result.toList();
}
*/

/**
 * \copydoc RStorage::queryAllBlocks
 */
QSet<RBlock::Id> RDocument::queryAllBlocks() const {
    return storage.queryAllBlocks();
}

/**
 * \copydoc RStorage::queryAllLayoutBlocks
 */
QSet<RBlock::Id> RDocument::queryAllLayoutBlocks(bool includeModelSpace) const {
    return storage.queryAllLayoutBlocks(includeModelSpace);
}

/**
 * \copydoc RStorage::queryAllLayouts
 */
QSet<RLayout::Id> RDocument::queryAllLayouts() const {
    return storage.queryAllLayouts();
}

/*
QList<RBlock::Id> RDocument::queryAllBlocks() const {
    QSet<RBlock::Id> result;
    storage.queryAllBlocks(result);
    return result.toList();
}
*/

/**
 * \copydoc RStorage::queryAllViews
 */
QSet<RView::Id> RDocument::queryAllViews() const {
    return storage.queryAllViews();
}

/**
 * \copydoc RStorage::queryAllLinetypes
 */
QSet<RLinetype::Id> RDocument::queryAllLinetypes() const{
    return storage.queryAllLinetypes();
}

/**
 * \copydoc RStorage::queryLayerEntities
 */
QSet<REntity::Id> RDocument::queryLayerEntities(RLayer::Id layerId, bool allBlocks) const {
    return storage.queryLayerEntities(layerId, allBlocks);
}

/**
 * \copydoc RStorage::hasBlockEntities
 */
bool RDocument::hasBlockEntities(RBlock::Id blockId) const {
    return storage.hasBlockEntities(blockId);
}

/**
 * \copydoc RStorage::queryBlockEntities
 */
QSet<REntity::Id> RDocument::queryBlockEntities(RBlock::Id blockId) const {
    return storage.queryBlockEntities(blockId);
}

/**
 * \copydoc RStorage::queryLayerBlockEntities
 */
QSet<REntity::Id> RDocument::queryLayerBlockEntities(RLayer::Id layerId, RBlock::Id blockId) const {
    return storage.queryLayerBlockEntities(layerId, blockId);
}

/**
 * \copydoc RStorage::hasChildEntities
 */
bool RDocument::hasChildEntities(REntity::Id parentId) const {
    return storage.hasChildEntities(parentId);
}

/**
 * \copydoc RStorage::queryChildEntities
 */
QSet<REntity::Id> RDocument::queryChildEntities(REntity::Id parentId, RS::EntityType type) const {
    return storage.queryChildEntities(parentId, type);
}

/**
 * \copydoc RStorage::queryBlockReferences
 */
QSet<REntity::Id> RDocument::queryBlockReferences(RBlock::Id blockId) const {
    return storage.queryBlockReferences(blockId);
}

/**
 * \copydoc RStorage::queryAllBlockReferences
 */
QSet<REntity::Id> RDocument::queryAllBlockReferences() const {
    return storage.queryAllBlockReferences();
}

/*
QSet<REntity::Id> RDocument::queryViewEntities(RView::Id viewId) const {
    return storage.queryViewEntities(viewId);
}
*/

/**
 * Queries the one entity that is closest to the given position and
 * within the given range (2d).
 *
 * \param wcsPosition The position to which the entity has to be close (2d).
 * \param range The range in which to search.
 */
REntity::Id RDocument::queryClosestXY(
    const RVector& wcsPosition,
    double range,
    bool draft,
    double strictRange,
    bool includeLockedLayers,
    bool selectedOnly) {

    RVector rangeV(
        range,
        range
    );

    // find entities that are within given maximum distance
    //   (approximation based on bounding boxes):
    QSet<REntity::Id> candidates =
        queryIntersectedEntitiesXY(
            RBox(
                wcsPosition - rangeV,
                wcsPosition + rangeV
            ),
            true, includeLockedLayers,
            RBlock::INVALID_ID, RDEFAULT_QLIST_RS_ENTITYTYPE,
            selectedOnly
        );

    if (candidates.isEmpty()) {
        return REntity::INVALID_ID;
    }

    return queryClosestXY(candidates, wcsPosition, range, draft, strictRange);
}

/**
 * Queries the entity that is closest to the given position \c wcsPosition.
 * Only entities in the given set of \c candidates are considered.
 * \c candidates is usually the result of an approximate spatial
 * index query.
 *
 * \param candidates Sets of candidates to consider.
 * \param wcsPosition
 * \param range Maximum distance between position and entity.
 */
REntity::Id RDocument::queryClosestXY(
    QSet<REntity::Id>& candidates,
    const RVector& wcsPosition,
    double range,
    bool draft,
    double strictRange) {

    double minDist = RMAXDOUBLE;
    REntity::Id ret = REntity::INVALID_ID;

    QSet<REntity::Id>::iterator it;
    for (it=candidates.begin(); it!=candidates.end(); it++) {
        if (RMouseEvent::hasMouseMoved()) {
            return REntity::INVALID_ID;
        }
        QSharedPointer<REntity> e = queryEntityDirect(*it);
        if (e.isNull()) {
            continue;
        }
        double dist = e->getDistanceTo(wcsPosition, true, range, draft, strictRange);

        if (e->isPointType() && dist<strictRange*1.1) {
            // make point type entities easier to select:
            dist/=100.0;
        }

        if (!RMath::isNaN(dist) && dist < minDist && dist < range+RS::PointTolerance) {
            minDist = dist;
            ret = *it;
        }
    }

    return ret;
}

QSet<REntity::Id> RDocument::queryInfiniteEntities() const {
    return storage.queryInfiniteEntities();
}

/**
 * Queries all entities which are completely inside the given box.
 *
 * \param box Query box.
 *
 * \param result Set of IDs of entities that are completely inside the
 *      given area.
 */
QSet<REntity::Id> RDocument::queryContainedEntities(const RBox& box) const {
    RSpatialIndex* si = getSpatialIndexForCurrentBlock();
    QSet<REntity::Id> ret = si->queryContained(box).keys().toSet();

    // always exclude construction lines (XLine):
    ret.subtract(queryInfiniteEntities());

    return ret;
}


QSet<REntity::Id> RDocument::queryIntersectedEntitiesXYFast(const RBox& box) {
    RBox boxExpanded = box;
    boxExpanded.c1.z = RMINDOUBLE;
    boxExpanded.c2.z = RMAXDOUBLE;

    // box contains bounding box of this document:
    // return all visible entities:
    if (boxExpanded.contains(getBoundingBox())) {
        QSet<REntity::Id> ids;
        //RDebug::startTimer(70);
        ids = queryAllVisibleEntities();
        //RDebug::stopTimer(70, "queryAllVisibleEntities");
        return ids;
    }

    return queryIntersectedShapesXYFast(boxExpanded);
}

QSet<REntity::Id> RDocument::queryIntersectedShapesXYFast(const RBox& box, bool noInfiniteEntities) {
    // always include construction lines (XLine):
    QSet<REntity::Id> infinites;
    if (!noInfiniteEntities) {
        infinites = queryInfiniteEntities();
    }

    // box is completely outside the bounding box of this document:
    if (box.isOutside(getBoundingBox())) {
        return infinites;
    }

    RSpatialIndex* si = getSpatialIndexForBlock(getCurrentBlockId());
    //RDebug::startTimer(120);
    QSet<REntity::Id> candidates = si->queryIntersected(box).keys().toSet();
    //RDebug::stopTimer(120, "si->queryIntersected");
    candidates.unite(infinites);

    QSet<REntity::Id> res;
    QSet<REntity::Id>::iterator it;
    for (it=candidates.begin(); it!=candidates.end(); ++it) {
        if (RMouseEvent::hasMouseMoved()) {
            return QSet<REntity::Id>();
        }

        QSharedPointer<REntity> entity;
        entity = queryVisibleEntityDirect(*it);
        if (entity.isNull()) {
            continue;
        }

        if (!entity->isVisible()) {
            continue;
        }

        res.insert(*it);
    }

    return res;
}

QSet<REntity::Id> RDocument::queryIntersectedEntitiesXY(
        const RBox& box, bool checkBoundingBoxOnly, bool includeLockedLayers, RBlock::Id blockId,
        const QList<RS::EntityType>& filter, bool selectedOnly, RLayer::Id layerId) const {

    bool onlyVisible = false;

    RBox boxExpanded = box;
    boxExpanded.c1.z = RMINDOUBLE;
    boxExpanded.c2.z = RMAXDOUBLE;

    if (blockId==RBlock::INVALID_ID) {
        blockId = getCurrentBlockId();
        onlyVisible = true;
    }
    bool usingCurrentBlock = (blockId == getCurrentBlockId());

    // box contains bounding box of this document:
    // return all visible entities:
    if (usingCurrentBlock && boxExpanded.contains(getBoundingBox())) {
        QSet<REntity::Id> ids;
        if (onlyVisible) {
            //RDebug::startTimer(70);
            ids = queryAllVisibleEntities();
            //RDebug::stopTimer(70, "queryAllVisibleEntities");
            //qDebug() << "all visible ids:" << ids;
        }
        else {
            ids = queryAllEntities(false, false);
        }

        return ids;
    }

    return queryIntersectedShapesXY(box, checkBoundingBoxOnly, includeLockedLayers, blockId, filter, selectedOnly, layerId).keys().toSet();
}

QMap<REntity::Id, QSet<int> > RDocument::queryIntersectedShapesXY(
        const RBox& box, bool checkBoundingBoxOnly, bool includeLockedLayers, RBlock::Id blockId,
        const QList<RS::EntityType>& filter, bool selectedOnly, RLayer::Id layerId) const {

    bool onlyVisible = false;

    QSet<RS::EntityType> filterSet = filter.toSet();
    RBox boxExpanded = box;
    boxExpanded.c1.z = RMINDOUBLE;
    boxExpanded.c2.z = RMAXDOUBLE;
    //bool usingCurrentBlock = false;
    if (blockId==RBlock::INVALID_ID) {
        blockId = getCurrentBlockId();
        onlyVisible = true;
        //qDebug() << "onlyVisible:" << onlyVisible;
    }

    bool usingCurrentBlock = (blockId == getCurrentBlockId());

    // always include construction lines (XLine):
    QMap<REntity::Id, QSet<int> > infinites;
    {
        QSet<REntity::Id> ids = queryInfiniteEntities();
        QSet<REntity::Id>::iterator it;
        for (it=ids.begin(); it!=ids.end(); it++) {
            infinites.insert(*it, QSet<int>());
        }
    }

    // box is completely outside the bounding box of this document:
    if (usingCurrentBlock && boxExpanded.isOutside(getBoundingBox()) && checkBoundingBoxOnly) {
        return infinites;
    }

    QMap<REntity::Id, QSet<int> > candidates;

    // box contains bounding box of this document:
    if (usingCurrentBlock && boxExpanded.contains(getBoundingBox())) {
        QSet<REntity::Id> ids;
        if (onlyVisible) {
            ids = queryAllVisibleEntities();
        }
        else {
            ids = queryAllEntities(false, false);
        }
        QSet<REntity::Id>::iterator it;
        for (it=ids.begin(); it!=ids.end(); it++) {
            candidates.insert(*it, QSet<int>());
        }
    }
    else {
        RSpatialIndex* si = getSpatialIndexForBlock(blockId);
        candidates = si->queryIntersected(boxExpanded);
        candidates.unite(infinites);
    }

    RBox boxFlattened = box;
    boxFlattened.c1.z = 0.0;
    boxFlattened.c2.z = 0.0;
    RPolyline pl;
    pl.appendVertex(boxFlattened.c1);
    pl.appendVertex(RVector(boxFlattened.c2.x, boxFlattened.c1.y));
    pl.appendVertex(boxFlattened.c2);
    pl.appendVertex(RVector(boxFlattened.c1.x, boxFlattened.c2.y));
    pl.appendVertex(boxFlattened.c1);

    // filter out entities that don't intersect with the given box
    // or are not on the current block or are on a frozen layer:
    QMap<REntity::Id, QSet<int> > res;
    QMap<REntity::Id, QSet<int> >::iterator it;
    for (it=candidates.begin(); it!=candidates.end(); ++it) {
        if (RMouseEvent::hasMouseMoved()) {
            return QMap<REntity::Id, QSet<int> >();
        }

        QSharedPointer<REntity> entity;
        if (onlyVisible) {
            entity = queryVisibleEntityDirect(it.key());
        }
        else {
            entity = queryEntityDirect(it.key());
        }
        if (entity.isNull()) {
            continue;
        }

        if (!onlyVisible) {
            // undone:
            if (entity->isUndone()) {
                continue;
            }

            // not on current or given block:
            if (entity->getBlockId()!=blockId) {
                continue;
            }

            if (!entity->isVisible()) {
                continue;
            }
        }

        if (selectedOnly) {
            if (!entity->isSelected() && !entity->isSelectedWorkingSet()) {
                continue;
            }
        }

        // layer is off:
//        if (isLayerOff(entity->getLayerId())) {
//            // block references are exported even if layer is off:
//            if (entity->getType()!=RS::EntityBlockRef) {
//                continue;
//            }
//        }

//        // layer is frozen:
//        if (isLayerFrozen(entity->getLayerId())) {
//            // viewports are exported even if layer is off or frozen (but without border):
//            if (entity->getType()!=RS::EntityViewport) {
//                continue;
//            }
//        }

//        // referenced block is off:
//        QSharedPointer<RBlockReferenceEntity> blockRef = entity.dynamicCast<RBlockReferenceEntity>();
//        if (!blockRef.isNull()) {
//            RBlock::Id referencedBlockId = blockRef->getReferencedBlockId();
//            if (referencedBlockId!=RBlock::INVALID_ID) {
//                QSharedPointer<RBlock> block = queryBlockDirect(referencedBlockId);
//                if (!block.isNull() && block->isFrozen()) {
//                    continue;
//                }
//            }
//        }

        // layer is locked:
        if (!includeLockedLayers) {
            if (isLayerLocked(entity->getLayerId())) {
                continue;
            }
        }

        // restrict to a specific layer:
        if (layerId!=RLayer::INVALID_ID) {
            if (entity->getLayerId()!=layerId) {
                continue;
            }
        }

        // hide block attributes if block reference is hidden:
//        if (RSettings::getHideAttributeWithBlock()) {
//            if (entity->getType()==RS::EntityAttribute) {
//                REntity::Id blockRefId = entity->getParentId();
//                QSharedPointer<REntity> parent = queryEntityDirect(blockRefId);
//                QSharedPointer<RBlockReferenceEntity> blockRef = parent.dynamicCast<RBlockReferenceEntity>();
//                if (!blockRef.isNull()) {
//                    if (isLayerFrozen(blockRef->getLayerId()) ||
//                        isBlockFrozen(blockRef->getReferencedBlockId())) {
//                        continue;
//                    }
//                }
//            }
//        }

        // apply filter:
        if (filterSet.contains(entity->getType())) {
            continue;
        }

        if (boxExpanded.contains(entity->getBoundingBox())) {
            res[it.key()] = it.value();
            continue;
        }

        if (!checkBoundingBoxOnly &&
            !entity->intersectsWith(pl)) {
            continue;
        }

        res[it.key()] = it.value();
    }

    return res;
}


QSet<REntity::Id> RDocument::queryContainedEntitiesXY(const RBox& box) const {
    RBox boxExpanded = box;
    boxExpanded.c1.z = RMINDOUBLE;
    boxExpanded.c2.z = RMAXDOUBLE;
    QSet<REntity::Id> candidates = queryContainedEntities(boxExpanded);

    //spatialIndex.queryContained(boxExpanded).keys().toSet();

    // filter out entities that are not on the current block
    // or whoes entire bounding box is not inside this query box
    // (e.g. block references which add multiple bounding boxes to the index):
    QSet<REntity::Id> outsiders;
    QSet<REntity::Id>::iterator it;
    for (it=candidates.begin(); it!=candidates.end(); ++it) {
        QSharedPointer<REntity> entity = queryEntity(*it);
        if (entity.isNull()) {
            outsiders.insert(*it);
            continue;
        }

        // undone:
        if (entity->isUndone()) {
            outsiders.insert(*it);
            continue;
        }

        // not on current block:
        if (entity->getBlockId() != getCurrentBlockId()) {
            outsiders.insert(*it);
            continue;
        }

        if (!entity->isVisible()) {
            outsiders.insert(*it);
            continue;
        }

//        // layer is off:
//        if (isLayerOff(entity->getLayerId())) {
//            outsiders.insert(*it);
//            continue;
//        }

//        // layer is frozen:
//        if (isLayerFrozen(entity->getLayerId())) {
//            outsiders.insert(*it);
//            continue;
//        }

//        // block is off:
//        QSharedPointer<RBlockReferenceEntity> blockRef = entity.dynamicCast<RBlockReferenceEntity>();
//        if (!blockRef.isNull()) {
//            if (isBlockFrozen(blockRef->getReferencedBlockId())) {
//                outsiders.insert(*it);
//                continue;
//            }
//        }

        if (!boxExpanded.contains(entity->getBoundingBox())) {
            outsiders.insert(*it);
            continue;
        }
    }

    return candidates - outsiders;
}


/* *
 * \todo refactor (3D)
 *
 * Queries all entities which are completely inside the given box in X/Y direction
 * and at least partially inside the given box in Z direction.
 * This is used for selections on the XY plane.
 *
 * \param box Query box.
 *
 * \param result Set of entity IDs.
 */
/*
QSet<REntity::Id> RDocument::queryEntitiesContainedXYIntersectedZ(const RBox& box) {
    QSet<REntity::Id> intersected =
        queryIntersectedEntities(box, true);

    QSet<REntity::Id> contained2d =
        spatialIndex.queryContained(
            box.c1.x, box.c1.y, RMINDOUBLE,
            box.c2.x, box.c2.y, RMAXDOUBLE
        );

    return intersected.intersect(contained2d);
}
*/



/**
 * Queries all selected entities.
 *
 * \return Set of IDs of all selected entities.
 */
QSet<REntity::Id> RDocument::querySelectedEntities() const {
    return storage.querySelectedEntities();
}

/**
 * Queries all selected objects.
 *
 * \return Set of IDs of all selected objects.
 */
QSet<RObject::Id> RDocument::querySelectedLayers() const {
    return storage.querySelectedLayers();
}

QSet<REntity::Id> RDocument::queryConnectedEntities(REntity::Id entityId, double tolerance, RObject::Id layerId) {
    QSet<REntity::Id> ret;

    QSharedPointer<REntity> entity = queryEntityDirect(entityId);
    if (entity.isNull()) {
        return ret;
    }

    RVector vTolerance = RVector(tolerance, tolerance);

    ret.insert(entityId);

    // select all connected entities:
    QList<RVector> connectionPoints = entity->getEndPoints();

    do {
        QList<RVector> newConnectionPoints;

        for (int i=0; i<connectionPoints.length(); ++i) {
            RVector cp = connectionPoints[i];

            RBox box(cp - vTolerance, cp + vTolerance);

            // find connected entities:
            // candidates intersect with small box around end point:
            QSet<REntity::Id> candidates = queryIntersectedEntitiesXY(box, true, false, RBlock::INVALID_ID, QList<RS::EntityType>(), false, layerId);
                      //QList<RS::EntityType>() << RS::EntityLine << RS::EntityArc << RS::EntityEllipse << RS::EntityPolyline << RS::EntitySpline);

            candidates.remove(entityId);
            candidates.subtract(ret);

            // filter out candidates with end points outside range:
            QList<REntity::Id> connectedEntities;
            QList<RVector> connectedPoints;
            QSet<REntity::Id>::iterator it;
            for (it=candidates.begin(); it!=candidates.end() /*&& found<=10*/; ++it) {
                REntity::Id candidateId = *it;
                QSharedPointer<REntity> candidate = queryEntityDirect(candidateId);
                QList<RVector> eps = candidate->getEndPoints();
                for (int k=0; k<eps.length(); ++k) {
                    RVector ep = eps[k];
                    if (ep.getDistanceTo(cp) <= tolerance) {
                        connectedEntities.append(candidateId);
                        connectedPoints.append(ep);
                        break;
                    }
                }
            }

            // select connected entities and find new connection points:
            for (int q = 0; q<connectedEntities.length(); ++q) {
                REntity::Id cEntityId = connectedEntities[q];
                RVector connectedPoint = connectedPoints[q];

                ret.insert(cEntityId);

                QSharedPointer<REntity> cEntity = queryEntityDirect(cEntityId);
                QList<RVector> eps = cEntity->getEndPoints();
                for (int ck=0; ck<eps.length(); ck++) {
                    RVector ep = eps[ck];
                    if (connectedPoint.equalsFuzzy(ep)) {
                        continue;
                    }
                    newConnectionPoints.append(ep);
                }
            }
        }
        connectionPoints = newConnectionPoints;
    } while (!connectionPoints.isEmpty());

    return ret;
}

QSet<RObject::Id> RDocument::queryPropertyEditorObjects() {
    QSet<RObject::Id> objectIds = querySelectedEntities();

    if (RSettings::getBoolValue("PropertyEditor/ShowBlockLayer", false)==true) {
        // no entities selected:
        if (objectIds.isEmpty()) {
            // expose properties of current layer:
            //objectIds.insert(getCurrentLayerId());

            // expose properties of selected layer(s):
            objectIds.unite(querySelectedLayers());

            // expose properties of selected block:
            RBlock::Id blockId = getCurrentBlockId();
            objectIds.insert(blockId);

            // expose properties of layout associated with current block:
            QSharedPointer<RBlock> block = queryBlock(blockId);
            if (!block.isNull()) {
                if (block->hasLayout()) {
                    RLayout::Id layoutId = block->getLayoutId();
                    objectIds.insert(layoutId);
//                    QSharedPointer<RLayout> layout = queryLayout(layoutId);
//                    if (!layout.isNull()) {

//                    }
                }
            }
        }
    }

    return objectIds;
}

QSharedPointer<RDocumentVariables> RDocument::queryDocumentVariables() const {
    return storage.queryDocumentVariables();
}

QSharedPointer<RDocumentVariables> RDocument::queryDocumentVariablesDirect() const {
    return storage.queryDocumentVariablesDirect();
}

/**
 * Queries the object with the given ID.
 *
 * \return Shared pointer to the object or a null pointer.
 */
QSharedPointer<RObject> RDocument::queryObject(RObject::Id objectId) const {
    return storage.queryObject(objectId);
}

/**
 * Queries the object with the given ID.
 * If the storage has the object instantiated, the instance is
 * returned (rather than a clone).
 * Objects queried this way should not be
 * modified unless undo / redo functionality is not required.
 *
 * \return Pointer to the object or NULL.
 */
QSharedPointer<RObject> RDocument::queryObjectDirect(RObject::Id objectId) const {
    return storage.queryObjectDirect(objectId);
}

QSharedPointer<RObject> RDocument::queryObjectByHandle(RObject::Handle objectHandle) const {
    return storage.queryObjectByHandle(objectHandle);
}

/**
 * Queries the entity with the given ID. A clone of the actual entity is returned.
 * Clones should always be used when modifying entities.
 *
 * \return Pointer to the entity or NULL.
 */
QSharedPointer<REntity> RDocument::queryEntity(REntity::Id entityId) const {
    return storage.queryEntity(entityId);
}

/**
 * Queries the entity with the given ID.
 * If the storage has the entity instantiated, the instance is
 * returned (rather than a clone).
 * Entities queried this way should not be
 * modified unless undo / redo functionality is not required.
 *
 * \return Pointer to the entity or NULL.
 */
QSharedPointer<REntity> RDocument::queryEntityDirect(REntity::Id entityId) const {
    return storage.queryEntityDirect(entityId);
}

QSharedPointer<REntity> RDocument::queryVisibleEntityDirect(REntity::Id entityId) const {
    return storage.queryVisibleEntityDirect(entityId);
}

/**
 * Queries the UCS with the given ID.
 *
 * \return Pointer to the UCS or NULL.
 */
QSharedPointer<RUcs> RDocument::queryUcs(RUcs::Id ucsId) const {
    return storage.queryUcs(ucsId);
}



/**
 * Queries the UCS with the given name.
 *
 * \return Pointer to the UCS or NULL.
 */
QSharedPointer<RUcs> RDocument::queryUcs(const QString& ucsName) const {
    return storage.queryUcs(ucsName);
}


/**
 * Queries the layer with the given ID.
 *
 * \return Pointer to the layer or NULL.
 */
QSharedPointer<RLayer> RDocument::queryLayer(RLayer::Id layerId) const {
    return storage.queryLayer(layerId);
}

/**
 * Queries the layer with the given ID direct (no cloning).
 * Layers queried this way should not be
 * modified unless undo / redo functionality is not required.
 *
 * \return Pointer to the layer or NULL.
 */
QSharedPointer<RLayer> RDocument::queryLayerDirect(RLayer::Id layerId) const {
    return storage.queryLayerDirect(layerId);
}

/**
 * Queries the layer with the given name.
 *
 * \return Pointer to the layer or NULL.
 */
QSharedPointer<RLayer> RDocument::queryLayer(const QString& layerName) const {
    return storage.queryLayer(layerName);
}

/**
 * Queries the layer state with the given ID.
 *
 * \return Pointer to the layer state or NULL.
 */
QSharedPointer<RLayerState> RDocument::queryLayerState(RLayerState::Id layerStateId) const {
    return storage.queryLayerState(layerStateId);
}

/**
 * Queries the layer state with the given ID direct (no cloning).
 * Layer states queried this way should not be
 * modified unless undo / redo functionality is not required.
 *
 * \return Pointer to the layer state or NULL.
 */
QSharedPointer<RLayerState> RDocument::queryLayerStateDirect(RLayerState::Id layerStateId) const {
    return storage.queryLayerStateDirect(layerStateId);
}

/**
 * Queries the layer state with the given name.
 *
 * \return Pointer to the layer state or NULL.
 */
QSharedPointer<RLayerState> RDocument::queryLayerState(const QString& layerStateName) const {
    return storage.queryLayerState(layerStateName);
}

/**
 * Queries the layout with the given ID.
 *
 * \return Pointer to the layout or NULL.
 */
QSharedPointer<RLayout> RDocument::queryLayout(RLayout::Id layoutId) const {
    return storage.queryLayout(layoutId);
}

/**
 * Queries the layout with the given ID direct (no cloning).
 * Layouts queried this way should not be
 * modified unless undo / redo functionality is not required.
 *
 * \return Pointer to the layout or NULL.
 */
QSharedPointer<RLayout> RDocument::queryLayoutDirect(RLayout::Id layoutId) const {
    return storage.queryLayoutDirect(layoutId);
}

/**
 * Queries the layout with the given name.
 *
 * \return Pointer to the layout or NULL.
 */
QSharedPointer<RLayout> RDocument::queryLayout(const QString& layoutName) const {
    return storage.queryLayout(layoutName);
}

/**
 * Queries the block with the given ID direct (no cloning).
 * Blocks queried this way should not be
 * modified unless undo / redo functionality is not required.
 *
 * \return Pointer to the block or NULL.
 */
QSharedPointer<RBlock> RDocument::queryBlockDirect(RBlock::Id blockId) const {
    return storage.queryBlockDirect(blockId);
}

/**
 * Queries the block with the given name direct (no cloning).
 * Blocks queried this way should not be
 * modified unless undo / redo functionality is not required.
 *
 * \return Pointer to the block or NULL.
 */
QSharedPointer<RBlock> RDocument::queryBlockDirect(const QString& blockName) const {
    return storage.queryBlockDirect(blockName);
}

/**
 * Queries the block with the given ID.
 *
 * \return Pointer to the block or NULL.
 */
QSharedPointer<RBlock> RDocument::queryBlock(RBlock::Id blockId) const {
    return storage.queryBlock(blockId);
}

/**
 * Queries the block with the given name.
 *
 * \return Pointer to the block or NULL.
 */
QSharedPointer<RBlock> RDocument::queryBlock(const QString& blockName) const {
    return storage.queryBlock(blockName);
}

/**
 * Queries the view with the given ID.
 *
 * \return Pointer to the view or NULL.
 */
QSharedPointer<RView> RDocument::queryView(RView::Id viewId) const {
    return storage.queryView(viewId);
}

/**
 * Queries the view with the given name.
 *
 * \return Pointer to the view or NULL.
 */
QSharedPointer<RView> RDocument::queryView(const QString& viewName) const {
    return storage.queryView(viewName);
}

/**
 * Queries the linetype with the given ID.
 *
 * \return Pointer to the linetype or NULL.
 */
QSharedPointer<RLinetype> RDocument::queryLinetype(RLinetype::Id linetypeId) const {
    return storage.queryLinetype(linetypeId);
}

/**
 * Queries the linetype with the given name.
 *
 * \return Pointer to the linetype or NULL.
 */
QSharedPointer<RLinetype> RDocument::queryLinetype(const QString& linetypeName) const {
    return storage.queryLinetype(linetypeName);
}

/**
 * \copydoc RStorage::isSelected
 */
bool RDocument::isSelected(REntity::Id entityId) {
    return storage.isSelected(entityId);
}

/**
 * \copydoc RStorage::isSelectedWorkingSet
 */
bool RDocument::isSelectedWorkingSet(REntity::Id entityId) {
    return storage.isSelectedWorkingSet(entityId);
}

/**
 * \copydoc RStorage::isLayerLocked
 */
bool RDocument::isLayerLocked(RLayer::Id layerId) const {
    return storage.isLayerLocked(layerId);
}

/**
 * \copydoc RStorage::isLayerLocked
 */
bool RDocument::isLayerLocked(const RLayer& layer) const {
    return storage.isLayerLocked(layer);
}

/**
 * \copydoc RStorage::isParentLayerLocked
 */
bool RDocument::isParentLayerLocked(RLayer::Id layerId) const {
    return storage.isParentLayerLocked(layerId);
}

/**
 * \copydoc RStorage::isParentLayerLocked
 */
bool RDocument::isParentLayerLocked(const RLayer& layer) const {
    return storage.isParentLayerLocked(layer);
}

bool RDocument::isEntityEditable(REntity::Id entityId) const {
    QSharedPointer<REntity> entity = queryEntityDirect(entityId);
    if (entity.isNull()) {
        return false;
    }

    return entity->isEditable();
}

//bool RDocument::isEntityLayerLocked(REntity::Id entityId) const {
//    QSharedPointer<REntity> entity = queryEntityDirect(entityId);
//    if (entity.isNull()) {
//        return false;
//    }

//    return isLayerLocked(entity->getLayerId());
//}

/**
 * \copydoc RStorage::isLayerOff
 */
bool RDocument::isLayerOff(RLayer::Id layerId) const {
    return storage.isLayerOff(layerId);
}

/**
 * \copydoc RStorage::isLayerOff
 */
bool RDocument::isLayerOff(const RLayer& layer) const {
    return storage.isLayerOff(layer);
}

/**
 * \copydoc RStorage::isLayerOffOrFrozen
 */
bool RDocument::isLayerOffOrFrozen(RLayer::Id layerId) const {
    return storage.isLayerOffOrFrozen(layerId);
}

/**
 * \copydoc RStorage::isLayerOffOrFrozen
 */
bool RDocument::isLayerOffOrFrozen(const RLayer& layer) const {
    return storage.isLayerOffOrFrozen(layer);
}

/**
 * \copydoc RStorage::isLayerFrozen
 */
bool RDocument::isLayerFrozen(RLayer::Id layerId) const {
    return storage.isLayerFrozen(layerId);
}

/**
 * \copydoc RStorage::isLayerFrozen
 */
bool RDocument::isLayerFrozen(const RLayer& layer) const {
    return storage.isLayerFrozen(layer);
}

/**
 * \copydoc RStorage::isParentLayerFrozen
 */
bool RDocument::isParentLayerFrozen(RLayer::Id layerId) const {
    return storage.isParentLayerFrozen(layerId);
}

/**
 * \copydoc RStorage::isParentLayerFrozen
 */
bool RDocument::isParentLayerFrozen(const RLayer& layer) const {
    return storage.isParentLayerFrozen(layer);
}

/**
 * \copydoc RStorage::isBlockFrozen
 */
bool RDocument::isBlockFrozen(RBlock::Id blockId) const {
    return storage.isBlockFrozen(blockId);
}

/**
 * \copydoc RStorage::isLayoutBlock
 */
bool RDocument::isLayoutBlock(RBlock::Id blockId) const {
    return storage.isLayoutBlock(blockId);
}

bool RDocument::isEntityLayerFrozen(REntity::Id entityId) const {
    QSharedPointer<REntity> entity = queryEntityDirect(entityId);
    if (entity.isNull()) {
        return false;
    }

    return storage.isLayerFrozen(entity->getLayerId());
}

/**
 * \copydoc RStorage::isEntityVisible
 */
bool RDocument::isEntityVisible(const REntity& entity, RObject::Id blockId) const {
    return storage.isEntityVisible(entity, blockId);
}

/**
 * \copydoc RStorage::isParentLayerSnappable
 */
bool RDocument::isParentLayerSnappable(RLayer::Id layerId) const {
    return storage.isParentLayerSnappable(layerId);
}

/**
 * \copydoc RStorage::isParentLayerSnappable
 */
bool RDocument::isParentLayerSnappable(const RLayer& layer) const {
    return storage.isParentLayerSnappable(layer);
}

/**
 * \copydoc RStorage::isLayerSnappable
 */
bool RDocument::isLayerSnappable(RLayer::Id layerId) const {
    return storage.isLayerSnappable(layerId);
}

/**
 * \copydoc RStorage::isLayerSnappable
 */
bool RDocument::isLayerSnappable(const RLayer& layer) const {
    return storage.isLayerSnappable(layer);
}

/**
 * \copydoc RStorage::isLayerPlottable
 */
bool RDocument::isLayerPlottable(RLayer::Id layerId) const {
    return storage.isLayerPlottable(layerId);
}

/**
 * \copydoc RStorage::isLayerPlottable
 */
bool RDocument::isLayerPlottable(const RLayer& layer) const {
    return storage.isLayerPlottable(layer);
}

/**
 * \copydoc RStorage::isParentLayerPlottable
 */
bool RDocument::isParentLayerPlottable(RLayer::Id layerId) const {
    return storage.isParentLayerPlottable(layerId);
}

/**
 * \copydoc RStorage::isParentLayerPlottable
 */
bool RDocument::isParentLayerPlottable(const RLayer& layer) const {
    return storage.isParentLayerPlottable(layer);
}

/**
 * \copydoc RStorage::countSelectedEntities
 */
int RDocument::countSelectedEntities() const {
    return storage.countSelectedEntities();
}

/**
 * \todo refactoring to operation
 *
 * Deselectes all selected entities.
 */
void RDocument::clearSelection(QSet<REntity::Id>* affectedEntities) {
    storage.clearEntitySelection(affectedEntities);
}

/**
 * Selects all not selected entities.
 */
void RDocument::selectAllEntities(QSet<REntity::Id>* affectedEntities) {
    storage.selectAllEntities(affectedEntities);
}

/**
 * \todo refactoring to operation
 *
 * \copydoc RStorage::selectEntity
 */
void RDocument::selectEntity(
    REntity::Id entityId,
    bool add,
    QSet<REntity::Id>* affectedEntities) {

    storage.selectEntity(entityId, add, affectedEntities);
}

/**
 * \copydoc RStorage::deselectEntity
 */
void RDocument::deselectEntity(
    REntity::Id entityId,
    QSet<REntity::Id>* affectedEntities) {

    storage.deselectEntity(entityId, affectedEntities);
}

/**
 * \todo refactoring to operation
 *
 * \copydoc RStorage::selectEntities
 *
 */
int RDocument::selectEntities(
    const QSet<REntity::Id>& entityIds,
    bool add,
    QSet<REntity::Id>* affectedEntities) {

    return storage.selectEntities(entityIds, add, affectedEntities);
}

/**
 * \todo refactoring to operation
 *
 * \copydoc RStorage::deselectEntities
 *
 */
int RDocument::deselectEntities(
    const QSet<REntity::Id>& entityIds,
    QSet<REntity::Id>* affectedEntities) {

    return storage.deselectEntities(entityIds, affectedEntities);
}

/**
 * \copydoc RStorage::hasSelection
 */
bool RDocument::hasSelection() const {
    return storage.hasSelection();
}

/**
 * \copydoc RStorage::getBoundingBox
 */
RBox RDocument::getBoundingBox(bool ignoreHiddenLayers, bool ignoreEmpty) const {
    return storage.getBoundingBox(ignoreHiddenLayers, ignoreEmpty);
}

/**
 * \copydoc RStorage::getSelectionBox
 */
RBox RDocument::getSelectionBox() const {
    return storage.getSelectionBox();
}

/**
 * \copydoc RStorage::getEntitiesBox
 */
RBox RDocument::getEntitiesBox(QSet<REntity::Id>& ids) const {
    return storage.getEntitiesBox(ids);
}

void RDocument::clearSpatialIndices() {
    spatialIndex.clear();
    QMap<RBlock::Id, RSpatialIndex*>::iterator it;
    for (it=spatialIndicesByBlock.begin(); it!=spatialIndicesByBlock.end(); it++) {
        delete *it;
    }
    spatialIndicesByBlock.clear();
}

/**
 * Rebuilds the entire spatial index from scratch (e.g. when current
 * block is changed).
 */
void RDocument::rebuildSpatialIndex() {
    clearSpatialIndices();

    QSet<REntity::Id> result = storage.queryAllEntities(false, true);

    QList<int> allIds;
    QList<QList<RBox> > allBbs;
    QMap<RBlock::Id, QList<int> > allIdsByBlock;
    QMap<RBlock::Id, QList<QList<RBox> > > allBbsByBlock;

    QSetIterator<REntity::Id> i(result);
    while (i.hasNext()) {
        QSharedPointer<REntity> entity = storage.queryEntityDirect(i.next());
        if (entity.isNull()) {
            continue;
        }
        if (entity->isUndone()) {
            continue;
        }

        entity->update();

        RObject::Id entityId = entity->getId();
        QList<RBox> bbs = entity->getBoundingBoxes();

        if (disableSpatialIndicesByBlock) {
            allIds.append(entityId);
            allBbs.append(bbs);
        }
        else {
            RBlock::Id blockId = entity->getBlockId();

            if (!allIdsByBlock.contains(blockId)) {
                allIdsByBlock.insert(blockId, QList<int>());
            }
            allIdsByBlock[blockId].append(entityId);

            if (!allBbsByBlock.contains(blockId)) {
                allBbsByBlock.insert(blockId, QList<QList<RBox> >());
            }
            allBbsByBlock[blockId].append(bbs);
        }
    }


    if (!disableSpatialIndicesByBlock) {
        QList<RBlock::Id> blockIds = queryAllBlocks().toList();
        for (int i=0; i<blockIds.length(); i++) {
            RBlock::Id blockId = blockIds[i];
            RSpatialIndex* si = getSpatialIndexForBlock(blockId);

            // remove entries without bounding boxes:
            for (int i=allIdsByBlock[blockId].length()-1; i>=0 && !allIdsByBlock[blockId].isEmpty(); i--) {
                if (allBbsByBlock[blockId][i].isEmpty()) {
                    allIdsByBlock[blockId].removeAt(i);
                    allBbsByBlock[blockId].removeAt(i);
                }
            }

            si->bulkLoad(allIdsByBlock[blockId], allBbsByBlock[blockId]);
//            for (int i=0; i<allIdsByBlock[blockId].length(); i++) {
//                si->addToIndex(allIdsByBlock[blockId][i], allBbsByBlock[blockId][i]);
//            }
        }
    }
    else {
        spatialIndex.bulkLoad(allIds, allBbs);
    }

    // clear cached bounding box:
    storage.update();
}

void RDocument::removeBlockFromSpatialIndex(RBlock::Id blockId) {
    static int recursionDepth = 0;
    recursionDepth++;

    if (recursionDepth>16) {
        recursionDepth--;
        return;
    }

    // remove entry for block references to the block the entity belongs to:
    QSet<REntity::Id> blockRefIds = queryBlockReferences(blockId);
    QSet<REntity::Id>::iterator it;
    for (it=blockRefIds.begin(); it!=blockRefIds.end(); it++) {
        QSharedPointer<RBlockReferenceEntity> blockRef = queryEntityDirect(*it).dynamicCast<RBlockReferenceEntity>();
        if (blockRef.isNull()) {
            continue;
        }

        removeBlockFromSpatialIndex(blockRef->getBlockId());
        removeFromSpatialIndex(blockRef);
    }

    recursionDepth--;
}

bool RDocument::blockContainsReferences(RBlock::Id blockId, RBlock::Id referencedBlockId) {
    if (blockId==referencedBlockId) {
        return true;
    }

    static int recursionDepth = 0;
    if (recursionDepth++>16) {
        recursionDepth--;
        qWarning() << "RDocument::blockContainsReferences: "
            << "maximum recursion depth reached: blockId: " << blockId;
        return true;
    }

    QSet<REntity::Id> blockEntityIds = queryBlockEntities(blockId);
    QSet<REntity::Id>::iterator it;
    for (it=blockEntityIds.begin(); it!=blockEntityIds.end(); it++) {
        QSharedPointer<REntity> entity = queryEntityDirect(*it);
        QSharedPointer<RBlockReferenceEntity> blockReference = entity.dynamicCast<RBlockReferenceEntity>();
        if (blockReference.isNull()) {
            continue;
        }

        if (blockContainsReferences(blockReference->getReferencedBlockId(), referencedBlockId)) {
            recursionDepth--;
            return true;
        }
    }

    recursionDepth--;
    return false;
}

/**
 * Add block references that point to blockId, unless they also point to ignoreBlockId.
 */
bool RDocument::addBlockToSpatialIndex(RBlock::Id blockId, RBlock::Id ignoreBlockId) {
    if (blockContainsReferences(blockId, ignoreBlockId)) {
        //qDebug() << "RDocument::addBlockToSpatialIndex: block " << getBlockName(blockId) << " contains " << getBlockName(ignoreBlockId);
        return false;
    }

    // add entries for block references to the block the entity belongs to:
    QSet<REntity::Id> blockRefIds = queryBlockReferences(blockId);
    QSet<REntity::Id>::iterator it;
    QSet<RBlock::Id> added;

    for (it=blockRefIds.begin(); it!=blockRefIds.end(); it++) {
        QSharedPointer<RBlockReferenceEntity> blockRef = queryEntityDirect(*it).dynamicCast<RBlockReferenceEntity>();
        if (blockRef.isNull()) {
            continue;
        }

        if (!added.contains(blockRef->getBlockId())) {
            addBlockToSpatialIndex(blockRef->getBlockId(), ignoreBlockId);
            added.insert(blockRef->getBlockId());
        }
        //if (!addBlockToSpatialIndex(blockRef->getBlockId(), ignoreBlockId)) {
        //    return false;
        //}

        blockRef->update();
        addToSpatialIndex(blockRef);
    }

    return true;
}


void RDocument::removeFromSpatialIndex(QSharedPointer<REntity> entity, const QList<RBox>& boundingBoxes) {
    QList<RBox> bbs = boundingBoxes;
    if (bbs.isEmpty()) {
        bbs = entity->getBoundingBoxes();
    }

    RBlock::Id blockId = entity->getBlockId();
    RSpatialIndex* si = getSpatialIndexForBlock(blockId);
;
    //bool ok = spatialIndex.removeFromIndex(entity->getId(), bbs);
    bool ok = si->removeFromIndex(entity->getId(), bbs);
    if (!ok) {
        //qWarning() << "RDocument::removeFromSpatialIndex: removing entity: " << *entity;
        //qWarning() << "failed to remove entity from spatial index";
    }
}

void RDocument::addToSpatialIndex(QSharedPointer<REntity> entity) {
    //spatialIndex.addToIndex(entity->getId(), entity->getBoundingBoxes());

    RBlock::Id blockId = entity->getBlockId();
    RSpatialIndex* si = getSpatialIndexForBlock(blockId);
    si->addToIndex(entity->getId(), entity->getBoundingBoxes());
}


void RDocument::updateAllEntities() {
    QSet<REntity::Id> ids = queryAllEntities(false, false);

    QSet<REntity::Id>::iterator it;
    for (it=ids.begin(); it!=ids.end(); it++) {
        QSharedPointer<REntity> entity = queryEntityDirect(*it);
        entity->setAutoUpdatesBlocked(true);
        entity->update();
        entity->setAutoUpdatesBlocked(false);
    }
}

/**
 * Undoes the last transaction.
 *
 * \return The transaction that was undone. Higher level callers can use
 *   this set to update scenes, views, etc accordingly.
 */
QList<RTransaction> RDocument::undo() {
    return transactionStack.undo();
}

/**
 * Redoes a previously undone transaction.
 *
 * \return Set of affected entity IDs. Higher level callers can use
 *   this set to update scenes, views, etc accordingly.
 */
QList<RTransaction> RDocument::redo() {
    return transactionStack.redo();
}

/**
 * \copydoc RStorage::isModified
 */
bool RDocument::isModified() const {
    return storage.isModified();
}

/**
 * \copydoc RStorage::getLastModifiedDateTime
 */
QDateTime RDocument::getLastModifiedDateTime() const {
    return storage.getLastModifiedDateTime();
}

/**
 * \copydoc RStorage::getLastModified
 */
QString RDocument::getLastModified() const {
    return storage.getLastModified();
}

/**
 * \copydoc RStorage::setModified
 */
void RDocument::setModified(bool m) {
    if (this==clipboard) {
        return;
    }
    storage.setModified(m);
}

void RDocument::copyVariablesFrom(const RDocument& other) {
    RTransaction* transaction = new RTransaction(storage, "Copy variables from other document", false);

    bool useLocalTransaction;
    QSharedPointer<RDocumentVariables> docVars = storage.startDocumentVariablesTransaction(transaction, useLocalTransaction);

    for (RS::KnownVariable kv=RS::ANGBASE; kv<=RS::MaxKnownVariable; kv=(RS::KnownVariable)(kv+1)) {
        QVariant otherKV = other.getKnownVariable(kv);
        if (otherKV.isValid()) {
            docVars->setKnownVariable(kv, otherKV);
            //setKnownVariable(kv, otherKV, &transaction);
        }
    }

    storage.endDocumentVariablesTransaction(transaction, useLocalTransaction, docVars);

    QStringList keys = other.getVariables();
    for (int i=0; i<keys.length(); i++) {
        QString key = keys[i];
        QVariant otherV = other.getVariable(key);
        if (otherV.isValid()) {
            setVariable(key, otherV);
        }
    }

    setDimensionFont(other.getDimensionFont(), transaction);

    transaction->end();
    delete transaction;
}

QString RDocument::addAutoVariable(double value) {
    RTransaction* transaction = new RTransaction(storage, "Add auto variable", false);
    bool useLocalTransaction;
    QSharedPointer<RDocumentVariables> docVars = storage.startDocumentVariablesTransaction(transaction, useLocalTransaction);
    QString ret = docVars->addAutoVariable(value);
    storage.endDocumentVariablesTransaction(transaction, useLocalTransaction, docVars);
    transaction->end();
    delete transaction;
    return ret;
}

QStringList RDocument::getAutoVariables() const {
    QSharedPointer<RDocumentVariables> docVars = queryDocumentVariablesDirect();
    if (docVars.isNull()) {
        return QStringList();
    }
    return docVars->getAutoVariables();
}

QString RDocument::substituteAutoVariables(const QString& expression) {
    QString exp = expression;

    QSharedPointer<RDocumentVariables> docVars = queryDocumentVariablesDirect();
    if (docVars.isNull()) {
        return expression;
    }

    QStringList autoVariables = docVars->getAutoVariables();
    for (int i=0; i<autoVariables.length(); i++) {
        QString key = autoVariables[i];
        double value = docVars->getCustomDoubleProperty("QCAD", key, RNANDOUBLE);
        if (RMath::isNaN(value)) {
            continue;
        }
        exp = exp.replace(QRegExp(QString("\\b%1\\b").arg(key)), QString("%1").arg(value, 0, 'f', 12));
    }

    return exp;
}

double RDocument::eval(const QString& expression, bool* ok) {
    QString exp = substituteAutoVariables(expression);
    return RMath::eval(exp, ok);
}

RDocument& RDocument::getClipboard() {
    if (clipboard==NULL) {
        clipboard = new RDocument(
            *(new RMemoryStorage()),
            *(new RSpatialIndexSimple())
        );
    }

    return *clipboard;
}

bool RDocument::isEditingWorkingSet() const {
    QSharedPointer<RDocumentVariables> docVars = queryDocumentVariablesDirect();
    return docVars->hasCustomProperty("QCAD", "WorkingSet/BlockName") && !docVars->hasCustomProperty("QCAD", "WorkingSet/Ignore");
}

void RDocument::setIgnoreWorkingSet(bool on) {
    if (on) {
        queryDocumentVariablesDirect()->setCustomProperty("QCAD", "WorkingSet/Ignore", true);
    }
    else {
        queryDocumentVariablesDirect()->removeCustomProperty("QCAD", "WorkingSet/Ignore");
    }
}

//RBlockReferenceEntity::Id RDocument::getWorkingSetBlockReferenceId() const {
//    return storage.getWorkingSetBlockReferenceId();
//}

//void RDocument::setWorkingSetBlockReferenceId(RBlockReferenceEntity::Id id, int group, RTransaction* transaction) {
//    storage.setWorkingSetBlockReferenceId(id, group, transaction);
//}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, RDocument& d) {
    dbg.nospace() << "RDocument(" << QString("0x%1").arg((long int)&d, 0, 16) << ", ";
    dbg.nospace() << d.getStorage();
    dbg.nospace() << d.getSpatialIndex();
//    QSet<RBlock::Id> blockIds = d.queryAllBlocks();
//    for (QSet<RBlock::Id>::iterator it=blockIds.begin(); it!=blockIds.end(); it++) {
//        dbg.nospace() << "\nspatial index for block: " << d.getBlockName(*it);
//        dbg.nospace() << *d.getSpatialIndexForBlock(*it);
//    }
    return dbg.space();
}

void RDocument::dump() {
    qDebug() << *this;
}
