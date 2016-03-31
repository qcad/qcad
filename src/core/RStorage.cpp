/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
#include "RDocument.h"
#include "RSettings.h"
#include "RStorage.h"
#include "RMainWindow.h"

RStorage::RStorage() :
    document(NULL),
    modified(false),
    maxDrawOrder(0),
    idCounter(0),
    handleCounter(0),
    currentColor(RColor::ByLayer),
    currentLineweight(RLineweight::WeightByLayer),
    currentLinetypeId(RLinetype::INVALID_ID),
    //currentLayerId(RLayer::INVALID_ID),
    currentViewId(RView::INVALID_ID),
    currentBlockId(RBlock::INVALID_ID),
    lastTransactionId(-1),
    lastTransactionGroup(1) {
}

void RStorage::clear() {
    modified = false;
    maxDrawOrder = 0;
    idCounter = 0;
    handleCounter = 0;
    currentColor = RColor::ByLayer;
    currentLineweight = RLineweight::WeightByLayer,
    currentLinetypeId = RLinetype::INVALID_ID;
    currentViewId = RView::INVALID_ID;
    currentBlockId = RBlock::INVALID_ID;
    lastTransactionId = -1;
    lastTransactionGroup = 1;
}

void RStorage::setObjectId(RObject& object, RObject::Id objectId) {
    object.setId(objectId);
}

void RStorage::setObjectHandle(RObject& object, RObject::Handle objectHandle) {
    object.setHandle(objectHandle);
    if (objectHandle>handleCounter) {
        handleCounter = objectHandle+1;
    }
}

void RStorage::setUndoStatus(RObject& object, bool status) {
    object.setUndone(status);
}

RObject::Id RStorage::getNewObjectId() {
    return idCounter++;
}

RObject::Id RStorage::getMaxObjectId() {
    return idCounter;
}

RObject::Handle RStorage::getNewObjectHandle() {
    return handleCounter++;
}

RObject::Handle RStorage::getMaxObjectHandle() {
    return handleCounter;
}

//RTransaction RStorage::setCurrentLayer(RLayer::Id layerId) {
//    RTransaction transaction(*this, "Setting current layer", true);
//    setCurrentLayer(transaction, layerId);
//    transaction.end();
//    return transaction;
//}

//RTransaction RStorage::setCurrentLayer(const QString& layerName) {
//    RLayer::Id id = getLayerId(layerName);
//    if (id == RLayer::INVALID_ID) {
//        return RTransaction();
//    }
//    return setCurrentLayer(id);
//}

//void RStorage::setCurrentLayer(RTransaction& transaction, RLayer::Id layerId) {
//    QSharedPointer<RDocumentVariables> v = queryDocumentVariables();
//    v->setCurrentLayerId(layerId);
//    transaction.addObject(v);
//}

//void RStorage::setCurrentLayer(RTransaction& transaction, const QString& layerName) {
//    RLayer::Id id = getLayerId(layerName);
//    if (id == RLayer::INVALID_ID) {
//        return;
//    }
//    setCurrentLayer(transaction, id);
//}

void RStorage::setCurrentLayer(RLayer::Id layerId, RTransaction* transaction) {
    bool useLocalTransaction;
    QSharedPointer<RDocumentVariables> docVars = startDocumentVariablesTransaction(transaction, useLocalTransaction);
    Q_ASSERT(!docVars.isNull());
    docVars->setCurrentLayerId(layerId);
    endDocumentVariablesTransaction(transaction, useLocalTransaction, docVars);
}

void RStorage::setCurrentLayer(const QString& layerName, RTransaction* transaction) {
    bool useLocalTransaction;
    QSharedPointer<RDocumentVariables> docVars = startDocumentVariablesTransaction(transaction, useLocalTransaction);
    Q_ASSERT(!docVars.isNull());
    RLayer::Id layerId = getLayerId(layerName);
    if (layerId == RLayer::INVALID_ID) {
        return;
    }
    docVars->setCurrentLayerId(layerId);
    endDocumentVariablesTransaction(transaction, useLocalTransaction, docVars);
}

RLayer::Id RStorage::getCurrentLayerId() const {
    QSharedPointer<RDocumentVariables> v = queryDocumentVariablesDirect();
    if (v.isNull()) {
        return RLayer::INVALID_ID;
    }
    return v->getCurrentLayerId();
}

void RStorage::setCurrentColor(const RColor& color) {
    currentColor = color;
}

RColor RStorage::getCurrentColor() const {
    return currentColor;
}

void RStorage::setCurrentLineweight(RLineweight::Lineweight lw) {
    currentLineweight = lw;
}

RLineweight::Lineweight RStorage::getCurrentLineweight() const {
    return currentLineweight;
}

void RStorage::setCurrentLinetype(RLinetype::Id ltId) {
    currentLinetypeId = ltId;
}

void RStorage::setCurrentLinetype(const QString& name) {
    QSet<RLinetype::Id> ltIds = queryAllLinetypes();
    QSet<RLinetype::Id>::iterator it;
    for (it = ltIds.begin(); it != ltIds.end(); ++it) {
        QSharedPointer<RLinetype> lt = queryLinetypeDirect(*it);
        if (lt->getName().toUpper()==name.toUpper()) {
            setCurrentLinetype(lt->getId());
            return;
        }
    }
}

void RStorage::setCurrentLinetypePattern(const RLinetypePattern& p) {
    setCurrentLinetype(p.getName());
}

RLinetype::Id RStorage::getCurrentLinetypeId() const {
    return currentLinetypeId;
}

RLinetypePattern RStorage::getCurrentLinetypePattern() const {
    QSharedPointer<RLinetype> lt = queryCurrentLinetype();
    if (lt.isNull()) {
        return RLinetypePattern();
    }
    return lt->getPattern();
}

bool RStorage::hasView(const QString& viewName) const {
    QStringList sl = getViewNames().toList();
    return sl.contains(viewName, Qt::CaseInsensitive);
}

bool RStorage::hasLayer(const QString& layerName) const {
    QStringList sl = getLayerNames().toList();
    return sl.contains(layerName, Qt::CaseInsensitive);
}

bool RStorage::hasLayout(const QString& layoutName) const {
    QStringList sl = getLayoutNames().toList();
    return sl.contains(layoutName, Qt::CaseInsensitive);
}

bool RStorage::hasBlock(const QString& blockName) const {
    QStringList sl = getBlockNames().toList();
    return sl.contains(blockName, Qt::CaseInsensitive);
}

bool RStorage::hasLinetype(const QString& linetypeName) const {
    QStringList sl = getLinetypeNames().toList();
    return sl.contains(linetypeName, Qt::CaseInsensitive);
}

QList<REntity::Id> RStorage::orderBackToFront(const QSet<REntity::Id>& entityIds) const {
    QMap<int, REntity::Id> res;
    QSet<REntity::Id>::const_iterator it;
    //maxDrawOrder = 0;
    for (it = entityIds.begin(); it != entityIds.end(); ++it) {
        QSharedPointer<REntity> e = queryEntityDirect(*it);
        if (!e.isNull()) {
            res.insertMulti(e->getDrawOrder(), *it);
            //maxDrawOrder = qMax(e->getDrawOrder()+1, maxDrawOrder);
        }
    }
    return res.values();
}

int RStorage::getMinDrawOrder() {
    QSet<REntity::Id> entityIds = queryAllEntities(false, false);
    QSet<REntity::Id>::const_iterator it;
    int minDrawOrder = maxDrawOrder;
    for (it = entityIds.begin(); it != entityIds.end(); ++it) {
        QSharedPointer<REntity> e = queryEntityDirect(*it);
        if (!e.isNull()) {
            if (e->getDrawOrder()<minDrawOrder) {
                minDrawOrder = e->getDrawOrder();
            }
        }
    }
    return minDrawOrder - 1;
}

QSharedPointer<RDocumentVariables> RStorage::startDocumentVariablesTransaction(RTransaction*& transaction, bool& useLocalTransaction) {
    useLocalTransaction = (transaction==NULL);

    if (useLocalTransaction) {
        transaction = new RTransaction(*this, "Change document setting", true);
    }

    return queryDocumentVariables();
}

void RStorage::endDocumentVariablesTransaction(RTransaction* transaction, bool useLocalTransaction, QSharedPointer<RDocumentVariables> docVars) {
    transaction->addObject(docVars);

    if (RMainWindow::hasMainWindow()) {
        RMainWindow::getMainWindow()->postTransactionEvent(*transaction,
                    transaction->hasOnlyChanges());
    }

    if (useLocalTransaction) {
        transaction->end();
        delete transaction;
    }
}

void RStorage::setUnit(RS::Unit unit, RTransaction* transaction) {
    bool useLocalTransaction;
    QSharedPointer<RDocumentVariables> docVars = startDocumentVariablesTransaction(transaction, useLocalTransaction);
    Q_ASSERT(!docVars.isNull());
    docVars->setUnit(unit);
    endDocumentVariablesTransaction(transaction, useLocalTransaction, docVars);
}

RS::Unit RStorage::getUnit() const {
    QSharedPointer<RDocumentVariables> v = queryDocumentVariablesDirect();
    if (v.isNull()) {
        return RS::None;
    }
    return v->getUnit();
}

void RStorage::setMeasurement(RS::Measurement m, RTransaction* transaction) {
    bool useLocalTransaction;
    QSharedPointer<RDocumentVariables> docVars = startDocumentVariablesTransaction(transaction, useLocalTransaction);
    Q_ASSERT(!docVars.isNull());
    docVars->setMeasurement(m);
    endDocumentVariablesTransaction(transaction, useLocalTransaction, docVars);
}

RS::Measurement RStorage::getMeasurement() const {
    QSharedPointer<RDocumentVariables> v = queryDocumentVariablesDirect();
    if (v.isNull()) {
        return RS::UnknownMeasurement;
    }
    return v->getMeasurement();
}

void RStorage::setDimensionFont(const QString& f, RTransaction* transaction) {
    bool useLocalTransaction;
    QSharedPointer<RDocumentVariables> docVars = startDocumentVariablesTransaction(transaction, useLocalTransaction);
    Q_ASSERT(!docVars.isNull());
    docVars->setDimensionFont(f);
    endDocumentVariablesTransaction(transaction, useLocalTransaction, docVars);
}

QString RStorage::getDimensionFont() const {
    QSharedPointer<RDocumentVariables> v = queryDocumentVariablesDirect();
    if (v.isNull()) {
        return "Standard";
    }
    return v->getDimensionFont();
}

void RStorage::setLinetypeScale(double v, RTransaction* transaction) {
    bool useLocalTransaction;
    QSharedPointer<RDocumentVariables> docVars = startDocumentVariablesTransaction(transaction, useLocalTransaction);
    docVars->setLinetypeScale(v);
    endDocumentVariablesTransaction(transaction, useLocalTransaction, docVars);
}

double RStorage::getLinetypeScale() const {
    QSharedPointer<RDocumentVariables> v = queryDocumentVariablesDirect();
    if (v.isNull()) {
        return 1.0;
    }
    return v->getLinetypeScale();
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, RStorage& s) {
    dbg.nospace() << "RStorage(" << QString("%1").arg((long int)&s, 0, 16) << ", ";
    dbg.nospace() << "\n";
    //dbg.nospace() << "current block ID: " << s.getCurrentBlockId() << "\n";
    dbg.nospace() << "modified: " << s.isModified() << "\n";
    QSharedPointer<RBlock> block = s.queryCurrentBlock();
    if (block.isNull()) {
        dbg.nospace() << "current block: INVALID\n";
    }
    else {
        dbg.nospace() << "current block: " << block->getName() << "\n";
    }
    //dbg.nospace() << "current layer ID: " << s.getCurrentLayerId() << "\n";
    QSharedPointer<RLayer> layer = s.queryCurrentLayer();
    if (layer.isNull()) {
        dbg.nospace() << "current layer: INVALID\n";
    }
    else {
        dbg.nospace() << "current layer: " << layer->getName() << "\n";
    }
    dbg.nospace() << "current view ID: " << s.getCurrentViewId() << "\n";
    QSharedPointer<RLinetype> linetype = s.queryCurrentLinetype();
    if (linetype.isNull()) {
        dbg.nospace() << "current linetype: INVALID\n";
    }
    else {
        dbg.nospace() << "current linetype: " << linetype->getName() << "\n";
    }
    dbg.nospace() << "drawing unit: " << s.getUnit() << "\n";
    dbg.nospace() << "dimension font: " << s.getDimensionFont() << "\n";
    dbg.nospace() << "bounding box: " << s.getBoundingBox() << "\n";
    dbg.nospace() << "document variables: " << *s.queryDocumentVariables() << "\n";

    {
        QSet<RLayer::Id> layers = s.queryAllLayers(true);
        QSetIterator<RLayer::Id> i(layers);
        while (i.hasNext()) {
            RLayer::Id id = i.next();
            QSharedPointer<RLayer> l = s.queryObjectDirect(id).dynamicCast<RLayer>();
            if (l.isNull()) {
                dbg.nospace() << "layer not found: " << id;
                continue;
            }
            dbg.nospace() << *l.data() << "\n";
        }
    }

    {
        QSet<RView::Id> views = s.queryAllViews(true);
        QSetIterator<RView::Id> i(views);
        while (i.hasNext()) {
            RView::Id id = i.next();
            QSharedPointer<RView> v = s.queryObjectDirect(id).dynamicCast<RView>();
            if (v.isNull()) {
                dbg.nospace() << "view not found: " << id;
                continue;
            }
            dbg.nospace() << *v.data() << "\n";
        }
    }

    {
        QSet<RBlock::Id> blocks = s.queryAllBlocks(true);
        QSetIterator<RBlock::Id> i(blocks);
        while (i.hasNext()) {
            RBlock::Id id = i.next();
            QSharedPointer<RBlock> b = s.queryObjectDirect(id).dynamicCast<RBlock>();
            if (b.isNull()) {
                dbg.nospace() << "block not found: " << id;
                continue;
            }
            dbg.nospace() << *b.data() << "\n";
            dbg.nospace() << "block entities: " << s.queryBlockEntities(id) << "\n";
        }
    }

    {
        QSet<RLinetype::Id> linetypes = s.queryAllLinetypes();
        QSetIterator<RLinetype::Id> i(linetypes);
        while (i.hasNext()) {
            RLinetype::Id id = i.next();
            QSharedPointer<RLinetype> l = s.queryObjectDirect(id).dynamicCast<RLinetype>();
            if (l.isNull()) {
                dbg.nospace() << "linetype not found: " << id;
                continue;
            }
            dbg.nospace() << *l.data() << "\n";
        }
    }

    {
        QSet<REntity::Id> entities = s.querySelectedEntities();
        if (entities.size()==0) {
            entities = s.queryAllEntities(true, true);
        }
        QSetIterator<REntity::Id> i(entities);
        while (i.hasNext()) {
            REntity::Id id = i.next();
            QSharedPointer<REntity> e = s.queryObjectDirect(id).dynamicCast<REntity>();
            if (e.isNull()) {
                dbg.nospace() << "entity not found: " << id;
                continue;
            }
            dbg.nospace() << "Bounding Box: " << e->getBoundingBox() << "\n";
            dbg.nospace() << *e.data() << "\n\n";
        }
    }

    dbg.nospace() << "lastTransactionId: " << s.getLastTransactionId() << "\n";
    for (int a = 0; a <= s.getMaxTransactionId(); ++a) {
        RTransaction t = s.getTransaction(a);
        dbg.nospace() << t << "\n";
    }

    dbg.nospace() << "variables: \n";

    {
        QStringList vars = s.getVariables();
        vars.sort();
        QListIterator<QString> i(vars);
        while (i.hasNext()) {
            QString key = i.next();
            dbg.nospace() << "\t" << key << ": " << s.getVariable(key) << "\n";
        }
    }

    dbg.nospace() << "Known variables (DXF): \n";

    {
        for (int i=0; i<=RS::MaxKnownVariable; i++) {
            QVariant v = s.getKnownVariable((RS::KnownVariable)i);
            if (v.isValid()) {
                dbg.nospace() << "\t"
                              << RStorage::getKnownVariableName((RS::KnownVariable)i)
                              << ": " << v << "\n";
            }
        }
    }

    dbg.nospace() << ")";
    return dbg.space();
}

/**
 * \return Name of the given known variable enum. Used for debugging.
 */
QString RStorage::getKnownVariableName(RS::KnownVariable n) {
    switch(n) {
    case RS::ANGBASE:
        return "ANGBASE";
    case RS::ANGDIR:
        return "ANGDIR";
    case RS::ATTMODE:
        return "ATTMODE";
    case RS::AUNITS:
        return "AUNITS";
    case RS::AUPREC:
        return "AUPREC";
    case RS::CECOLOR:
        return "CECOLOR";
    case RS::CELTSCALE:
        return "CELTSCALE";
    case RS::CHAMFERA:
        return "CHAMFERA";
    case RS::CHAMFERB:
        return "CHAMFERB";
    case RS::CHAMFERC:
        return "CHAMFERC";
    case RS::CHAMFERD:
        return "CHAMFERD";
    case RS::CMLJUST:
        return "CMLJUST";
    case RS::CMLSCALE:
        return "CMLSCALE";
    case RS::DIMADEC:
        return "DIMADEC";
    case RS::DIMALT:
        return "DIMALT";
    case RS::DIMALTD:
        return "DIMALTD";
    case RS::DIMALTF:
        return "DIMALTF";
    case RS::DIMALTRND:
        return "DIMALTRND";
    case RS::DIMALTTD:
        return "DIMALTTD";
    case RS::DIMALTTZ:
        return "DIMALTTZ";
    case RS::DIMALTU:
        return "DIMALTU";
    case RS::DIMALTZ:
        return "DIMALTZ";
    case RS::DIMAPOST:
        return "DIMAPOST";
    case RS::DIMASZ:
        return "DIMASZ";
    case RS::DIMATFIT:
        return "DIMATFIT";
    case RS::DIMAUNIT:
        return "DIMAUNIT";
    case RS::DIMAZIN:
        return "DIMAZIN";
    case RS::DIMBLK:
        return "DIMBLK";
    case RS::DIMBLK1:
        return "DIMBLK1";
    case RS::DIMBLK2:
        return "DIMBLK2";
    case RS::DIMCEN:
        return "DIMCEN";
    case RS::DIMCLRD:
        return "DIMCLRD";
    case RS::DIMCLRE:
        return "DIMCLRE";
    case RS::DIMCLRT:
        return "DIMCLRT";
    case RS::DIMDEC:
        return "DIMDEC";
    case RS::DIMDLE:
        return "DIMDLE";
    case RS::DIMDLI:
        return "DIMDLI";
    case RS::DIMDSEP:
        return "DIMDSEP";
    case RS::DIMEXE:
        return "DIMEXE";
    case RS::DIMEXO:
        return "DIMEXO";
    case RS::DIMFRAC:
        return "DIMFRAC";
    case RS::DIMGAP:
        return "DIMGAP";
    case RS::DIMJUST:
        return "DIMJUST";
    case RS::DIMLDRBLK:
        return "DIMLDRBLK";
    case RS::DIMLFAC:
        return "DIMLFAC";
    case RS::DIMLIM:
        return "DIMLIM";
    case RS::DIMLUNIT:
        return "DIMLUNIT";
    case RS::DIMLWD:
        return "DIMLWD";
    case RS::DIMLWE:
        return "DIMLWE";
    case RS::DIMPOST:
        return "DIMPOST";
    case RS::DIMRND:
        return "DIMRND";
    case RS::DIMSAH:
        return "DIMSAH";
    case RS::DIMSCALE:
        return "DIMSCALE";
    case RS::DIMSD1:
        return "DIMSD1";
    case RS::DIMSD2:
        return "DIMSD2";
    case RS::DIMSE1:
        return "DIMSE1";
    case RS::DIMSE2:
        return "DIMSE2";
    case RS::DIMSOXD:
        return "DIMSOXD";
    case RS::DIMTAD:
        return "DIMTAD";
    case RS::DIMTDEC:
        return "DIMTDEC";
    case RS::DIMTFAC:
        return "DIMTFAC";
    case RS::DIMTIH:
        return "DIMTIH";
    case RS::DIMTIX:
        return "DIMTIX";
    case RS::DIMTM:
        return "DIMTM";
    case RS::DIMTOFL:
        return "DIMTOFL";
    case RS::DIMTOH:
        return "DIMTOH";
    case RS::DIMTOL:
        return "DIMTOL";
    case RS::DIMTOLJ:
        return "DIMTOLJ";
    case RS::DIMTP:
        return "DIMTP";
    case RS::DIMTSZ:
        return "DIMTSZ";
    case RS::DIMTVP:
        return "DIMTVP";
    case RS::DIMTXSTY:
        return "DIMTXSTY";
    case RS::DIMTXT:
        return "DIMTXT";
    case RS::DIMTZIN:
        return "DIMTZIN";
    case RS::DIMUPT:
        return "DIMUPT";
    case RS::DIMZIN:
        return "DIMZIN";
    case RS::DISPSILH:
        return "DISPSILH";
    case RS::DRAWORDERCTL:
        return "DRAWORDERCTL";
    case RS::ELEVATION:
        return "ELEVATION";
    case RS::EXTMAX:
        return "EXTMAX";
    case RS::EXTMIN:
        return "EXTMIN";
    case RS::FACETRES:
        return "FACETRES";
    case RS::FILLETRAD:
        return "FILLETRAD";
    case RS::FILLMODE:
        return "FILLMODE";
    case RS::INSBASE:
        return "INSBASE";
    case RS::INSUNITS:
        return "INSUNITS";
    case RS::ISOLINES:
        return "ISOLINES";
    case RS::LIMCHECK:
        return "LIMCHECK";
    case RS::LIMMAX:
        return "LIMMAX";
    case RS::LIMMIN:
        return "LIMMIN";
    case RS::LTSCALE:
        return "LTSCALE";
    case RS::LUNITS:
        return "LUNITS";
    case RS::LUPREC:
        return "LUPREC";
    case RS::MAXACTVP:
        return "MAXACTVP";
    case RS::MEASUREMENT:
        return "MEASUREMENT";
    case RS::MIRRTEXT:
        return "MIRRTEXT";
    case RS::ORTHOMODE:
        return "ORTHOMODE";
    case RS::PDMODE:
        return "PDMODE";
    case RS::PDSIZE:
        return "PDSIZE";
    case RS::PELEVATION:
        return "PELEVATION";
    case RS::PELLIPSE:
        return "PELLIPSE";
    case RS::PEXTMAX:
        return "PEXTMAX";
    case RS::PEXTMIN:
        return "PEXTMIN";
    case RS::PINSBASE:
        return "PINSBASE";
    case RS::PLIMCHECK:
        return "PLIMCHECK";
    case RS::PLIMMAX:
        return "PLIMMAX";
    case RS::PLIMMIN:
        return "PLIMMIN";
    case RS::PLINEGEN:
        return "PLINEGEN";
    case RS::PLINEWID:
        return "PLINEWID";
    case RS::PROXYGRAPHICS:
        return "PROXYGRAPHICS";
    case RS::PSLTSCALE:
        return "PSLTSCALE";
    case RS::PUCSNAME:
        return "PUCSNAME";
    case RS::PUCSORG:
        return "PUCSORG";
    case RS::PUCSXDIR:
        return "PUCSXDIR";
    case RS::PUCSYDIR:
        return "PUCSYDIR";
    case RS::QTEXTMODE:
        return "QTEXTMODE";
    case RS::REGENMODE:
        return "REGENMODE";
    case RS::SHADEDGE:
        return "SHADEDGE";
    case RS::SHADEDIF:
        return "SHADEDIF";
    case RS::SKETCHINC:
        return "SKETCHINC";
    case RS::SKPOLY:
        return "SKPOLY";
    case RS::SPLFRAME:
        return "SPLFRAME";
    case RS::SPLINESEGS:
        return "SPLINESEGS";
    case RS::SPLINETYPE:
        return "SPLINETYPE";
    case RS::SURFTAB1:
        return "SURFTAB1";
    case RS::SURFTAB2:
        return "SURFTAB2";
    case RS::SURFTYPE:
        return "SURFTYPE";
    case RS::SURFU:
        return "SURFU";
    case RS::SURFV:
        return "SURFV";
    case RS::TEXTQLTY:
        return "TEXTQLTY";
    case RS::TEXTSIZE:
        return "TEXTSIZE";
    case RS::THICKNESS:
        return "THICKNESS";
    case RS::TILEMODE:
        return "TILEMODE";
    case RS::TRACEWID:
        return "TRACEWID";
    case RS::TREEDEPTH:
        return "TREEDEPTH";
    case RS::UCSNAME:
        return "UCSNAME";
    case RS::UCSORG:
        return "UCSORG";
    case RS::UCSXDIR:
        return "UCSXDIR";
    case RS::UCSYDIR:
        return "UCSYDIR";
    case RS::UNITMODE:
        return "UNITMODE";
    case RS::USERI1:
        return "USERI1";
    case RS::USERI2:
        return "USERI2";
    case RS::USERI3:
        return "USERI3";
    case RS::USERI4:
        return "USERI4";
    case RS::USERI5:
        return "USERI5";
    case RS::USERR1:
        return "USERR1";
    case RS::USERR2:
        return "USERR2";
    case RS::USERR3:
        return "USERR3";
    case RS::USERR4:
        return "USERR4";
    case RS::USERR5:
        return "USERR5";
    case RS::USRTIMER:
        return "USRTIMER";
    case RS::VISRETAIN:
        return "VISRETAIN";
    case RS::WORLDVIEW:
        return "WORLDVIEW";
    default:
        return "Unknown";
    }
}

/**
 * Adds a listener for modified status changed events.
 * This can for example be a modification indication widget.
 */
void RStorage::addModifiedListener(RModifiedListener* l) {
    if (l!=NULL) {
        modifiedListeners.push_back(l);
    } else {
        qWarning("RStorage::addModifiedListener(): Listener is NULL.");
    }
}

void RStorage::setModified(bool m) {
    if (m!=modified) {
        modified = m;

        QList<RModifiedListener*>::iterator it;
        for (it = modifiedListeners.begin(); it != modifiedListeners.end(); ++it) {
            (*it)->updateModifiedListener(this);
        }
    }
}
