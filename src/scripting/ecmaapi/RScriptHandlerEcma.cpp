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
#include <iostream>
//#ifdef _MSC_VER
//extern "C" {
//#include "getopt_long.h"
//}
//#else
//#include <getopt.h>
//#endif

#include <QDomNode>
#include <QFile>
#include <QRegExp>
#include <QScriptEngine>
#include <QScriptValueIterator>
#include <QStringList>
#include <QTextStream>
#include <QFontDatabase>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QXmlResultItems>
#include <QXmlStreamWriter>

#include <QtScriptTools>

#include "RMetaTypes.h"
#include "REcmaHelper.h"

#include "RAutoLoadEcma.h"
#include "RDebug.h"
#include "RScriptHandlerEcma.h"
#include "RSingleApplication.h"

#include "REcmaAction.h"
#include "REcmaActionAdapter.h"
#include "REcmaAddObjectOperation.h"
#include "REcmaAddObjectsOperation.h"
#include "REcmaArc.h"
#include "REcmaArcData.h"
#include "REcmaArcEntity.h"
#include "REcmaAutoLoadEcma.h"
#include "REcmaBlock.h"
#include "REcmaBlockListener.h"
#include "REcmaBlockListenerAdapter.h"
#include "REcmaBlockReferenceData.h"
#include "REcmaBlockReferenceEntity.h"
#include "REcmaBox.h"
#include "REcmaChangePropertyOperation.h"
#include "REcmaCharacterWidget.h"
#include "REcmaCircle.h"
#include "REcmaCircleData.h"
#include "REcmaCircleEntity.h"
#include "REcmaClipboardOperation.h"
#include "REcmaCloseCurrentEvent.h"
#include "REcmaColor.h"
#include "REcmaColorCombo.h"
#include "REcmaCommandEvent.h"
#include "REcmaCommandLine.h"
#include "REcmaCoordinateEvent.h"
#include "REcmaCoordinateListener.h"
#include "REcmaCoordinateListenerAdapter.h"
#include "REcmaCopyOperation.h"
#include "REcmaDebug.h"
#include "REcmaDeleteAllEntitiesOperation.h"
#include "REcmaDeleteObjectOperation.h"
#include "REcmaDeleteObjectsOperation.h"
#include "REcmaDeleteSelectionOperation.h"
#include "REcmaDimAlignedData.h"
#include "REcmaDimAlignedEntity.h"
#include "REcmaDimAngularData.h"
#include "REcmaDimAngularEntity.h"
#include "REcmaDimDiametricData.h"
#include "REcmaDimDiametricEntity.h"
#include "REcmaDimLinearData.h"
#include "REcmaDimLinearEntity.h"
#include "REcmaDimOrdinateData.h"
#include "REcmaDimOrdinateEntity.h"
#include "REcmaDimRadialData.h"
#include "REcmaDimRadialEntity.h"
#include "REcmaDimRotatedData.h"
#include "REcmaDimRotatedEntity.h"
#include "REcmaDimensionData.h"
#include "REcmaDimensionEntity.h"
#include "REcmaDocument.h"
#include "REcmaDocumentInterface.h"
#include "REcmaDockWidget.h"
#include "REcmaEllipse.h"
#include "REcmaEllipseData.h"
#include "REcmaEllipseEntity.h"
#include "REcmaEntity.h"
#include "REcmaEntityData.h"
#include "REcmaEntityPickEvent.h"
#include "REcmaEventFilter.h"
#include "REcmaExporter.h"
#include "REcmaFileCache.h"
#include "REcmaFileExporter.h"
#include "REcmaFileExporterAdapter.h"
#include "REcmaFileExporterFactory.h"
#include "REcmaFileExporterFactoryAdapter.h"
#include "REcmaFileExporterRegistry.h"
#include "REcmaFileImporter.h"
#include "REcmaFileImporterAdapter.h"
#include "REcmaFileImporterRegistry.h"
#include "REcmaFileSystemModel.h"
#include "REcmaFocusListener.h"
#include "REcmaFocusListenerAdapter.h"
#include "REcmaFontChooserWidget.h"
#include "REcmaFontDatabase.h"
#include "REcmaFontList.h"
#include "REcmaFontList.h"
#include "REcmaGraphicsScene.h"
//#include "REcmaGraphicsSceneGl.h"
#include "REcmaGraphicsSceneQt.h"
#include "REcmaGraphicsView.h"
#include "REcmaGraphicsViewGl.h"
#include "REcmaGraphicsViewImage.h"
#include "REcmaGraphicsViewQt.h"
#include "REcmaGrid.h"
#include "REcmaGuiAction.h"
#include "REcmaHatchData.h"
#include "REcmaHatchEntity.h"
#include "REcmaImageData.h"
#include "REcmaImageEntity.h"
#include "REcmaImporter.h"
#include "REcmaInputEvent.h"
#include "REcmaLayer.h"
#include "REcmaLayerListener.h"
#include "REcmaLayerListenerAdapter.h"
#include "REcmaLeaderData.h"
#include "REcmaLeaderEntity.h"
#include "REcmaLine.h"
#include "REcmaLineData.h"
#include "REcmaLineEntity.h"
#include "REcmaLinetype.h"
#include "REcmaLinetypeCombo.h"
#include "REcmaLinetypePattern.h"
#include "REcmaLinetypePatternMap.h"
#include "REcmaLineweight.h"
#include "REcmaLineweightCombo.h"
#include "REcmaListView.h"
#include "REcmaListWidget.h"
#include "REcmaMainWindow.h"
#include "REcmaMainWindowQt.h"
#include "REcmaMath.h"
#include "REcmaMathLineEdit.h"
#include "REcmaMdiChildQt.h"
#include "REcmaMemoryStorage.h"
#include "REcmaMixedOperation.h"
#include "REcmaModifyObjectOperation.h"
#include "REcmaModifyObjectsOperation.h"
#include "REcmaMouseEvent.h"
#include "REcmaMoveReferencePointOperation.h"
#include "REcmaMoveSelectionOperation.h"
#include "REcmaNavigationAction.h"
#include "REcmaObject.h"
#include "REcmaOperation.h"
#include "REcmaOrthoGrid.h"
#include "REcmaPainterPath.h"
#include "REcmaPainterPathDevice.h"
#include "REcmaPasteOperation.h"
#include "REcmaPattern.h"
#include "REcmaPatternListMetric.h"
#include "REcmaPatternListImperial.h"
#include "REcmaPenListener.h"
#include "REcmaPenListenerAdapter.h"
#include "REcmaPluginLoader.h"
#include "REcmaPluginInfo.h"
#include "REcmaPoint.h"
#include "REcmaPointData.h"
#include "REcmaPointEntity.h"
#include "REcmaPolyline.h"
#include "REcmaPolylineData.h"
#include "REcmaPolylineEntity.h"
#include "REcmaPropertyAttributes.h"
#include "REcmaPropertyEditor.h"
#include "REcmaPropertyEvent.h"
#include "REcmaPropertyListener.h"
#include "REcmaPropertyTypeId.h"
#include "REcmaRestrictHorizontal.h"
#include "REcmaRestrictVertical.h"
#include "REcmaRestrictOrthogonal.h"
#include "REcmaRestrictOff.h"
#include "REcmaRuler.h"
#include "REcmaRulerQt.h"
#include "REcmaRunner.h"
#include "REcmaS.h"
#include "REcmaScriptAction.h"
#include "REcmaSelectionListener.h"
#include "REcmaSelectionListenerAdapter.h"
#include "REcmaSettings.h"
#include "REcmaShape.h"
#include "REcmaSharedPointerArc.h"
#include "REcmaSharedPointerArcEntity.h"
#include "REcmaSharedPointerBlock.h"
#include "REcmaSharedPointerBlockReferenceEntity.h"
#include "REcmaSharedPointerBox.h"
#include "REcmaSharedPointerCircle.h"
#include "REcmaSharedPointerCircleEntity.h"
#include "REcmaSharedPointerDimAlignedEntity.h"
#include "REcmaSharedPointerDimAngularEntity.h"
#include "REcmaSharedPointerDimDiametricEntity.h"
#include "REcmaSharedPointerDimLinearEntity.h"
#include "REcmaSharedPointerDimOrdinateEntity.h"
#include "REcmaSharedPointerDimRadialEntity.h"
#include "REcmaSharedPointerDimRotatedEntity.h"
#include "REcmaSharedPointerDimensionEntity.h"
#include "REcmaSharedPointerEllipse.h"
#include "REcmaSharedPointerEllipseEntity.h"
#include "REcmaSharedPointerEntity.h"
#include "REcmaSharedPointerHatchEntity.h"
#include "REcmaSharedPointerImageEntity.h"
#include "REcmaSharedPointerLayer.h"
#include "REcmaSharedPointerLeaderEntity.h"
#include "REcmaSharedPointerLine.h"
#include "REcmaSharedPointerLineEntity.h"
#include "REcmaSharedPointerLinetype.h"
#include "REcmaSharedPointerObject.h"
#include "REcmaSharedPointerPoint.h"
#include "REcmaSharedPointerPointEntity.h"
#include "REcmaSharedPointerPolyline.h"
#include "REcmaSharedPointerPolylineEntity.h"
#include "REcmaSharedPointerShape.h"
#include "REcmaSharedPointerSolidEntity.h"
#include "REcmaSharedPointerSpline.h"
#include "REcmaSharedPointerSplineEntity.h"
#include "REcmaSharedPointerTextData.h"
#include "REcmaSharedPointerTextEntity.h"
#include "REcmaSharedPointerTextEntity.h"
#include "REcmaSharedPointerTextLabel.h"
#include "REcmaSharedPointerTriangle.h"
#include "REcmaSharedPointerUcs.h"
#include "REcmaSharedPointerView.h"
#include "REcmaSnap.h"
#include "REcmaSnapAuto.h"
#include "REcmaSnapCenter.h"
#include "REcmaSnapDistance.h"
#include "REcmaSnapEnd.h"
#include "REcmaSnapEntityBase.h"
#include "REcmaSnapFree.h"
#include "REcmaSnapGrid.h"
#include "REcmaSnapIntersection.h"
#include "REcmaSnapListener.h"
#include "REcmaSnapMiddle.h"
#include "REcmaSnapOnEntity.h"
#include "REcmaSnapPerpendicular.h"
#include "REcmaSnapReference.h"
#include "REcmaSnapRestriction.h"
#include "REcmaSolidData.h"
#include "REcmaSolidEntity.h"
#include "REcmaSpatialIndex.h"
#include "REcmaSpatialIndexNavel.h"
#include "REcmaSpatialIndexSimple.h"
#include "REcmaSpatialIndexVisitor.h"
#include "REcmaSpatialIndexVisitorAdapter.h"
#include "REcmaSpline.h"
#include "REcmaSplineData.h"
#include "REcmaSplineEntity.h"
#include "REcmaStemmer.h"
#include "REcmaStorage.h"
#include "REcmaTabletEvent.h"
#include "REcmaTerminateEvent.h"
#include "REcmaTextData.h"
#include "REcmaTextEdit.h"
#include "REcmaTextEntity.h"
#include "REcmaTextLabel.h"
#include "REcmaTextRenderer.h"
#include "REcmaThread.h"
#include "REcmaTransformation.h"
#include "REcmaTranslation.h"
#include "REcmaTransaction.h"
#include "REcmaTransactionListener.h"
#include "REcmaTriangle.h"
#include "REcmaUcs.h"
#include "REcmaUnit.h"
#include "REcmaVector.h"
#include "REcmaView.h"
#include "REcmaViewFocusListener.h"
#include "REcmaViewFocusListenerAdapter.h"
#include "REcmaViewListener.h"
#include "REcmaViewListenerAdapter.h"
#include "REcmaWebView.h"
#include "REcmaWheelEvent.h"

#ifndef R_NO_DXF
#include "REcmaDxfImporter.h"
#include "REcmaDxfImporterFactory.h"
#endif

bool RScriptHandlerEcma::alwaysLoadScripts = false;
bool RScriptHandlerEcma::translatorInstalled = false;
QAbstractEventDispatcher::EventFilter RScriptHandlerEcma::defaultEventFilter;

RScriptHandlerEcma::RScriptHandlerEcma() : engine(NULL), debugger(NULL) {
    //  registerScriptHandler(this, getSupportedFileExtensionsStatic());
    engine = new QScriptEngine();

    alwaysLoadScripts = qApp->arguments().contains("-always-load-scripts");

    // 20120403: only enable script debugger over command line as expert option.
    // Script debugger causes crashes.
    if (RSettings::isGuiEnabled() && RSettings::isDebuggerEnabled()) {
        qWarning() << "RScriptHandlerEcma::RScriptHandlerEcma: script debugger enabled! Not recommended.";
        debugger = new QScriptEngineDebugger(engine);
        debugger->setObjectName("debugger");
        debugger->attachTo(engine);
    }
    else {
        connect(engine, SIGNAL(signalHandlerException(const QScriptValue&)),
                this, SLOT(exceptionHandler(const QScriptValue&)));
    }

    engine->installTranslatorFunctions();

    // iterate through module list and break if one module cannot be loaded
    QStringList modules;
    modules << "qt.core" << "qt.gui" << "qt.uitools" << "qt.webkit" << "qt.sql"
            << "qt.svg" << "qt.xml" << "qt.xmlpatterns";

#ifndef Q_OS_WIN32
    // NOTE: qt.network wrapper does not compile under Windows (SSL problems)
    modules << "qt.network";
#endif

    for (int i=0; i<modules.size(); i++) {
        engine->importExtension(modules.at(i));

        if (engine->hasUncaughtException()) {
            qWarning() << "ECMAScript extension module " << modules.at(i) << " could not be loaded:";
            qWarning() << engine->uncaughtException().toString();
            qWarning() << "Exception Backtrace:";
            qWarning() << engine->uncaughtExceptionBacktrace().join("\n");
            Q_ASSERT(false);
        }
    }
    
    // TODO: load more modules, based on chosen settings from application preferences

    //  QStringList availableExtensions = engine->availableExtensions();
    //  for (int i = 0; i < availableExtensions.size(); ++i) {
    //      qDebug("REcmaHandler::REcmaHandler: script extension: %s",
    //              (const char*) availableExtensions.at(i).toLatin1());
    //  }

    QScriptValue globalObject = engine->globalObject();
    globalObject.setProperty("include", engine->newFunction(ecmaInclude, 1));
    globalObject.setProperty("print", engine->newFunction(ecmaPrint));
    globalObject.setProperty("qDebug", engine->newFunction(ecmaDebug));
    globalObject.setProperty("qWarning", engine->newFunction(ecmaWarning));
    globalObject.setProperty("qCritical", engine->newFunction(ecmaCritical));
    globalObject.setProperty("qGray", engine->newFunction(ecmaGray));

    // crashes:
    //globalObject.setProperty("attachDebugger", engine->newFunction(ecmaAttachDebugger));

    globalObject.setProperty("detachDebugger", engine->newFunction(ecmaDetachDebugger));
    globalObject.setProperty("collectGarbage", engine->newFunction(ecmaCollectGarbage));
//  globalObject.setProperty("msleep", engine->newFunction(ecmaMSleep));
    globalObject.setProperty("importExtension", engine->newFunction(ecmaImportExtension));
    globalObject.setProperty("isDeleted", engine->newFunction(ecmaIsDeleted));
    globalObject.setProperty("serialize", engine->newFunction(ecmaSerialize));
    //globalObject.setProperty("blockEvents", engine->newFunction(ecmaBlockEvents));
    //globalObject.setProperty("unblockEvents", engine->newFunction(ecmaUnblockEvents));
    //globalObject.setProperty("getOpt", engine->newFunction(ecmaGetOpt));
    globalObject.setProperty("addApplicationFont", engine->newFunction(ecmaAddApplicationFont));
    globalObject.setProperty("download", engine->newFunction(ecmaDownload));
    globalObject.setProperty("qApp", engine->newQObject(dynamic_cast<RSingleApplication*>(qApp)));

    // fix Qt wrapper APIs
    QScriptValue classQObject = globalObject.property("QObject");
    classQObject.property("prototype").setProperty("findChild",
            engine->newFunction(ecmaQObjectFindChild));
    classQObject.property("prototype").setProperty("getChildren",
            engine->newFunction(ecmaQObjectGetChildren));
    classQObject.property("prototype").setProperty("getObjectId",
            engine->newFunction(ecmaGetObjectId));
    classQObject.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaDestroy));

//    QScriptValue classQDateTime = globalObject.property("QDateTime");
//    classQDateTime.property("prototype").setProperty("toString",
//            engine->newFunction(ecmaQDateTimeToString));

    QScriptValue classQSortFilterProxyModel = globalObject.property("QSortFilterProxyModel");
    //QScriptValue proto = classQSortFilterProxyModel.prototype();
    //proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractProxyModel*>()));
    classQSortFilterProxyModel.property("prototype").setProperty("castToQAbstractItemModel",
            engine->newFunction(ecmaQSortFilterProxyModelCastToQAbstractItemModel));
    //classQSortFilterProxyModel.property("prototype").setProperty("sourceModel",
    //        engine->newFunction(ecmaQSortFilterProxyModel));

    QScriptValue classQDir = globalObject.property("QDir");
    classQDir.setProperty("separator", engine->newVariant(QDir::separator()));

    QScriptValue classQDomNode = globalObject.property("QDomNode");
    classQDomNode.property("prototype").setProperty("appendChild",
            engine->newFunction(ecmaQDomNodeAppendChild));
    classQDomNode.property("prototype").setProperty("removeChild",
            engine->newFunction(ecmaQDomNodeRemoveChild));

    QScriptValue classQPrinter = globalObject.property("QPrinter");
    classQPrinter.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaQPrinterDestroy));

    QScriptValue classQPainter = globalObject.property("QPainter");
    classQPainter.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaQPainterDestroy));

    QScriptValue classQXmlResultItems = globalObject.property("QXmlResultItems");
    classQXmlResultItems.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaQXmlResultItemsDestroy));

    QScriptValue classQXmlStreamWriter = globalObject.property("QXmlStreamWriter");
    classQXmlStreamWriter.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaQXmlStreamWriterDestroy));

    QScriptValue classQLayout = globalObject.property("QLayout");
    classQLayout.property("prototype").setProperty("getWidth",
            engine->newFunction(ecmaQLayoutGetWidth));

    QScriptValue classQByteArray = globalObject.property("QByteArray");
    classQByteArray.property("prototype").setProperty("toString",
            engine->newFunction(ecmaQByteArrayToString));

    QScriptValue classQUrl = globalObject.property("QUrl");
    classQUrl.property("prototype").setProperty("queryItems",
            engine->newFunction(ecmaQUrlQueryItems));

    QScriptValue classQt = globalObject.property("Qt");
    classQt.setProperty("escape",
            engine->newFunction(ecmaQtEscape));

//    globalObject.setProperty("QFontDatabase", engine->newFunction());
//    QScriptValue classQFontDatabase = globalObject.property("QFontDatabase");
//    classQFontDatabase.setProperty("families", engine->newFunction(ecmaQFontDatabaseFamilies));


    /*
    QScriptValue classQListView = globalObject.property("QListView");
    classQListView.property("prototype").setProperty("mousePressEvent",
            engine->newFunction(ecmaQListViewMousePressEvent));
            */

    QScriptValue classQCoreApplication = globalObject.property(
            "QCoreApplication");
    classQCoreApplication.setProperty("arguments", engine->newFunction(
            ecmaArguments));

    // *** do not change the order ***
    REcmaMath::init(*engine);
    REcmaStemmer::init(*engine);

    REcmaPropertyTypeId::init(*engine);

    REcmaS::init(*engine);
    REcmaUnit::init(*engine);
    REcmaDebug::init(*engine);
    REcmaSettings::init(*engine);
    REcmaColor::init(*engine);
    REcmaLineweight::init(*engine);
    REcmaThread::init(*engine);
    REcmaRunner::init(*engine);
    REcmaLinetypePattern::init(*engine);
    REcmaLinetypePatternMap::init(*engine);
    REcmaPattern::init(*engine);
    REcmaPatternListMetric::init(*engine);
    REcmaPatternListImperial::init(*engine);
    REcmaFontList::init(*engine);
    REcmaFileCache::init(*engine);

    REcmaVector::init(*engine);

    REcmaShape::init(*engine);
    REcmaSharedPointerShape::init(*engine);
    REcmaArc::init(*engine);
    REcmaSharedPointerArc::init(*engine);
    REcmaBox::init(*engine);
    REcmaCircle::init(*engine);
    REcmaSharedPointerCircle::init(*engine);
    REcmaEllipse::init(*engine);
    REcmaSharedPointerEllipse::init(*engine);
    REcmaLine::init(*engine);
    REcmaSharedPointerLine::init(*engine);
    REcmaPoint::init(*engine);
    REcmaSharedPointerPoint::init(*engine);
    REcmaPolyline::init(*engine);
    REcmaSharedPointerPolyline::init(*engine);
    REcmaSpline::init(*engine);
    REcmaSharedPointerSpline::init(*engine);
    REcmaTriangle::init(*engine);
    REcmaSharedPointerTriangle::init(*engine);
    REcmaTextLabel::init(*engine);
    REcmaSharedPointerTextLabel::init(*engine);

    REcmaStorage::init(*engine);
    REcmaMemoryStorage::init(*engine);

    REcmaDocument::init(*engine);
    REcmaDocumentInterface::init(*engine);

    REcmaSelectionListener::init(*engine);
    REcmaSelectionListenerAdapter::init(*engine);
    REcmaTransactionListener::init(*engine);
    REcmaSnapListener::init(*engine);

    REcmaGuiAction::init(*engine);
    REcmaSpatialIndex::init(*engine);
    REcmaSpatialIndexNavel::init(*engine);
    REcmaSpatialIndexSimple::init(*engine);
    REcmaSpatialIndexVisitor::init(*engine);
    REcmaSpatialIndexVisitorAdapter::init(*engine);

    REcmaGraphicsScene::init(*engine);
//    REcmaGraphicsSceneGl::init(*engine);
    REcmaGraphicsSceneQt::init(*engine);
    //REcmaGraphicsSceneQV::init(*engine);
    REcmaPainterPath::init(*engine);
    REcmaPainterPathDevice::init(*engine);

    REcmaGrid::init(*engine);
    REcmaOrthoGrid::init(*engine);
    REcmaRuler::init(*engine);
    REcmaRulerQt::init(*engine);

    REcmaSnap::init(*engine);
    REcmaSnapEntityBase::init(*engine);
    REcmaSnapAuto::init(*engine);
    REcmaSnapCenter::init(*engine);
    REcmaSnapDistance::init(*engine);
    REcmaSnapEnd::init(*engine);
    REcmaSnapFree::init(*engine);
    REcmaSnapGrid::init(*engine);
    REcmaSnapIntersection::init(*engine);
    REcmaSnapMiddle::init(*engine);
    REcmaSnapOnEntity::init(*engine);
    REcmaSnapPerpendicular::init(*engine);
    REcmaSnapReference::init(*engine);

    REcmaSnapRestriction::init(*engine);
    REcmaRestrictHorizontal::init(*engine);
    REcmaRestrictVertical::init(*engine);
    REcmaRestrictOrthogonal::init(*engine);
    REcmaRestrictOff::init(*engine);

    REcmaGraphicsView::init(*engine);
    REcmaGraphicsViewGl::init(*engine);
    REcmaGraphicsViewImage::init(*engine);
    REcmaGraphicsViewQt::init(*engine);
    //REcmaGraphicsViewQV::init(*engine);

    REcmaMainWindow::init(*engine);
    REcmaMainWindowQt::init(*engine);
    REcmaMdiChildQt::init(*engine);

    REcmaAction::init(*engine);
    REcmaActionAdapter::init(*engine);
    REcmaNavigationAction::init(*engine);
    REcmaScriptAction::init(*engine);
//  REcmaScriptActionEcma::init(*engine);

    REcmaEventFilter::init(*engine);

    REcmaTerminateEvent::init(*engine);
    REcmaInputEvent::init(*engine);
    REcmaMouseEvent::init(*engine);
    REcmaWheelEvent::init(*engine);
    REcmaTabletEvent::init(*engine);
    REcmaCloseCurrentEvent::init(*engine);

    REcmaCommandEvent::init(*engine);
    REcmaCoordinateEvent::init(*engine);
    REcmaEntityPickEvent::init(*engine);
    REcmaCoordinateListener::init(*engine);
    REcmaCoordinateListenerAdapter::init(*engine);

    REcmaObject::init(*engine);
    REcmaSharedPointerObject::init(*engine);
    REcmaEntity::init(*engine);
    REcmaSharedPointerEntity::init(*engine);
    REcmaLayer::init(*engine);
    REcmaSharedPointerLayer::init(*engine);
    REcmaBlock::init(*engine);
    REcmaSharedPointerBlock::init(*engine);
    REcmaView::init(*engine);
    REcmaSharedPointerView::init(*engine);
    REcmaLinetype::init(*engine);
    REcmaSharedPointerLinetype::init(*engine);
    REcmaUcs::init(*engine);
    REcmaSharedPointerUcs::init(*engine);

    REcmaEntityData::init(*engine);

    REcmaBlockReferenceData::init(*engine);
    REcmaBlockReferenceEntity::init(*engine);
    REcmaSharedPointerBlockReferenceEntity::init(*engine);

    REcmaPointData::init(*engine);
    REcmaPointEntity::init(*engine);
    REcmaSharedPointerPointEntity::init(*engine);

    REcmaLineData::init(*engine);
    REcmaLineEntity::init(*engine);
    REcmaSharedPointerLineEntity::init(*engine);

    REcmaCircleData::init(*engine);
    REcmaCircleEntity::init(*engine);
    REcmaSharedPointerCircleEntity::init(*engine);

    REcmaArcData::init(*engine);
    REcmaArcEntity::init(*engine);
    REcmaSharedPointerArcEntity::init(*engine);

    REcmaEllipseData::init(*engine);
    REcmaEllipseEntity::init(*engine);
    REcmaSharedPointerEllipseEntity::init(*engine);

    REcmaPolylineData::init(*engine);
    REcmaPolylineEntity::init(*engine);
    REcmaSharedPointerPolylineEntity::init(*engine);

    REcmaSolidData::init(*engine);
    REcmaSolidEntity::init(*engine);
    REcmaSharedPointerSolidEntity::init(*engine);

    REcmaSplineData::init(*engine);
    REcmaSplineEntity::init(*engine);
    REcmaSharedPointerSplineEntity::init(*engine);

    REcmaTextData::init(*engine);
    REcmaTextEntity::init(*engine);
    REcmaSharedPointerTextData::init(*engine);
    REcmaSharedPointerTextEntity::init(*engine);

    REcmaLeaderData::init(*engine);
    REcmaLeaderEntity::init(*engine);
    REcmaSharedPointerLeaderEntity::init(*engine);

    REcmaHatchData::init(*engine);
    REcmaHatchEntity::init(*engine);
    REcmaSharedPointerHatchEntity::init(*engine);

    REcmaImageData::init(*engine);
    REcmaImageEntity::init(*engine);
    REcmaSharedPointerImageEntity::init(*engine);

    REcmaDimensionData::init(*engine);
    REcmaDimensionEntity::init(*engine);
    REcmaSharedPointerDimensionEntity::init(*engine);

    REcmaDimLinearData::init(*engine);
    REcmaDimLinearEntity::init(*engine);
    REcmaSharedPointerDimLinearEntity::init(*engine);

    REcmaDimAlignedData::init(*engine);
    REcmaDimAlignedEntity::init(*engine);
    REcmaSharedPointerDimAlignedEntity::init(*engine);

    REcmaDimAngularData::init(*engine);
    REcmaDimAngularEntity::init(*engine);
    REcmaSharedPointerDimAngularEntity::init(*engine);

    REcmaDimDiametricData::init(*engine);
    REcmaDimDiametricEntity::init(*engine);
    REcmaSharedPointerDimDiametricEntity::init(*engine);

    REcmaDimRadialData::init(*engine);
    REcmaDimRadialEntity::init(*engine);
    REcmaSharedPointerDimRadialEntity::init(*engine);

    REcmaDimRotatedData::init(*engine);
    REcmaDimRotatedEntity::init(*engine);
    REcmaSharedPointerDimRotatedEntity::init(*engine);

    REcmaDimOrdinateData::init(*engine);
    REcmaDimOrdinateEntity::init(*engine);
    REcmaSharedPointerDimOrdinateEntity::init(*engine);

    REcmaTransaction::init(*engine);

    REcmaImporter::init(*engine);
    REcmaFileImporter::init(*engine);
    REcmaFileImporterAdapter::init(*engine);
#ifndef R_NO_DXF
    REcmaDxfImporter::init(*engine);
    REcmaDxfImporterFactory::init(*engine);
#endif
    REcmaFileImporterRegistry::init(*engine);

    REcmaExporter::init(*engine);
    REcmaFileExporter::init(*engine);
    REcmaFileExporterAdapter::init(*engine);
    REcmaFileExporterFactory::init(*engine);
    REcmaFileExporterFactoryAdapter::init(*engine);
    REcmaFileExporterRegistry::init(*engine);

    REcmaOperation::init(*engine);

    REcmaAddObjectsOperation::init(*engine);
    REcmaClipboardOperation::init(*engine);
    REcmaDeleteObjectsOperation::init(*engine);

    REcmaAddObjectOperation::init(*engine);
    REcmaChangePropertyOperation::init(*engine);
    REcmaCopyOperation::init(*engine);
    REcmaDeleteAllEntitiesOperation::init(*engine);
    REcmaDeleteObjectOperation::init(*engine);
    REcmaDeleteSelectionOperation::init(*engine);
    REcmaMixedOperation::init(*engine);
    REcmaModifyObjectOperation::init(*engine);
    REcmaModifyObjectsOperation::init(*engine);
    REcmaMoveReferencePointOperation::init(*engine);
    REcmaMoveSelectionOperation::init(*engine);
    REcmaPasteOperation::init(*engine);

    REcmaTransformation::init(*engine);

    REcmaTranslation::init(*engine);

    REcmaCommandLine::init(*engine);
    REcmaTextEdit::init(*engine);
    REcmaMathLineEdit::init(*engine);
    REcmaCharacterWidget::init(*engine);
    REcmaDockWidget::init(*engine);

    REcmaPropertyListener::init(*engine);
    REcmaPropertyEditor::init(*engine);

    REcmaListWidget::init(*engine);
    REcmaListView::init(*engine);
    REcmaLayerListener::init(*engine);
    REcmaLayerListenerAdapter::init(*engine);
    REcmaBlockListener::init(*engine);
    REcmaBlockListenerAdapter::init(*engine);
    REcmaViewListener::init(*engine);
    REcmaViewListenerAdapter::init(*engine);
    REcmaPenListener::init(*engine);
    REcmaPenListenerAdapter::init(*engine);
    REcmaColorCombo::init(*engine);
    REcmaLineweightCombo::init(*engine);
    REcmaLinetypeCombo::init(*engine);
    REcmaFontChooserWidget::init(*engine);
    REcmaFontDatabase::init(*engine);

    REcmaPluginLoader::init(*engine);
    REcmaPluginInfo::init(*engine);

    REcmaFontList::init(*engine);

    REcmaPropertyEvent::init(*engine);

    REcmaPropertyAttributes::init(*engine);

    REcmaFileSystemModel::init(*engine);

    REcmaWebView::init(*engine);

    REcmaFocusListener::init(*engine);
    REcmaFocusListenerAdapter::init(*engine);
    REcmaViewFocusListener::init(*engine);
    REcmaViewFocusListenerAdapter::init(*engine);

    REcmaTextRenderer::init(*engine);

    REcmaAutoLoadEcma::init(*engine);

    // *** end of "do not change the order" ***

    // give plugins a chance to initialize their script extensions:
    RPluginLoader::initScriptExtensions(*engine);

    // eval auto load scripts:
    QStringList files = RAutoLoadEcma::getAutoLoadFiles();
    for (int i=0; i<files.size(); i++) {
        doScript(files[i]);
    }
}


RScriptHandlerEcma::~RScriptHandlerEcma() {
    // potential fix for FS#414:
    if (debugger!=NULL) {
        debugger->detach();
        delete debugger;
        debugger = NULL;
    }

    if (engine->hasUncaughtException()) {
        qWarning() << "At least one uncaught exception:";
        qWarning() << engine->uncaughtExceptionBacktrace().join("\n");
    }

    if (engine->isEvaluating()) {
        qWarning() << "Deleting script engine that is still evaluating.";
    }
    // potential fix for FS#414:
    //engine->abortEvaluation();
    delete engine;
}

RScriptHandler* RScriptHandlerEcma::factory() {
    return new RScriptHandlerEcma();
}

QList<QString> RScriptHandlerEcma::getSupportedFileExtensionsStatic() {
    QList<QString> ret;
    ret.push_back("js");
    return ret;
}

QList<QString> RScriptHandlerEcma::getSupportedFileExtensions() {
    return getSupportedFileExtensionsStatic();
}

bool RScriptHandlerEcma::isRunning() {
    return engine->isEvaluating();
}

void RScriptHandlerEcma::abort() {
    engine->abortEvaluation();
}

bool RScriptHandlerEcma::hasUncaughtExceptions() {
    return engine->hasUncaughtException();
}

/**
 * \todo move to RScriptHandler
 */
void RScriptHandlerEcma::doScript(const QString& scriptFile,const QStringList& arguments) {
    QFileInfo fi(scriptFile);
    if (!fi.exists()) {
        qWarning()
            << QString("RScriptHandlerEcma::doScript: "
                "file '%1' does not exist").arg(scriptFile);
        return;
    }

    QString className = fi.completeBaseName();

    /*
    // leads to cryptic crashes:
    if (isIncluded(engine, className)) {
        return;
    }
    */

    QScriptValue globalObject = engine->globalObject();

//    qDebug() << "RScriptHandlerEcma::doScript: " << className << " (" << scriptFile << ")";

//    QScriptValue cl = globalObject.property(className);
//    if (cl.isValid() && cl.isFunction()) {
//        qDebug() << "RScriptHandlerEcma::doScript: class already loaded: " << className;
//        return;
//    }

//    qDebug() << "RScriptHandlerEcma::doScript: loading class: " << className;

    initGlobalVariables(scriptFile);
    if (!arguments.isEmpty()) {
        // set global variable args to (command line) arguments:
        globalObject.setProperty("args", qScriptValueFromValue(engine,arguments));
    }

    QString contents = readScript(scriptFile, alwaysLoadScripts);
    if (contents.isEmpty()) {
        qDebug() << "RScriptHandlerEcma::doScript: script file is empty";
        return;
    }

    /*
    if (!qApp->arguments().contains("-always-load-scripts")) {
        alreadyIncluded.insert(fi.completeBaseName());
        vAlreadyIncluded.setValue(alreadyIncluded);
        engine->setProperty("alreadyIncluded", vAlreadyIncluded);
    }
    */

    //engine->currentContext()
    //engine->currentContext()->setActivationObject(engine->globalObject());
    eval(contents, scriptFile);

//    if (!alwaysLoadScripts) {
//        alreadyIncluded.insert(className);
//        vAlreadyIncluded.setValue(alreadyIncluded);
//        engine->setProperty("alreadyIncluded", vAlreadyIncluded);
//    }

//    if (className!="RestrictOff" && className!="SnapAuto") {
//    markIncluded(engine, className);
//    }

//    qDebug() << "RScriptHandlerEcma::doScript: " << className << " DONE";
}

void RScriptHandlerEcma::eval(const QString& script, const QString& fileName) {
    QScriptValue err = engine->evaluate(script, fileName);
    if (engine->hasUncaughtException()) {
        qWarning()
                << "RScriptHandlerEcma::eval: script engine exception: "
                << err.toString();
        qWarning() << engine->uncaughtExceptionBacktrace().join("\n");
    }
}

RFileImporterAdapter* RScriptHandlerEcma::createFileImporter(const QString& className, RDocument& document) {
    QScriptValue globalObject = engine->globalObject();
    //QScriptContext* context = engine->currentContext();

    // get script class:
    QScriptValue clazz = globalObject.property(className);

    // instantiate (call constructor):
    QScriptValue argument = qScriptValueFromValue(engine, &document);
    QScriptValue obj = clazz.construct(QScriptValueList() << argument);

    // return:
    RFileImporterAdapter* imp = REcmaHelper::scriptValueTo<RFileImporterAdapter>(obj);
    return imp;
}

/**
 * \return The pre-processed contents of the given file with all includes resolved.
 */
QString RScriptHandlerEcma::readScript(const QString& fileName, bool forceReload) {

    return RFileCache::getContents(fileName, forceReload);

    /*
    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly)) {
        qWarning() << "RScriptHandlerEcma::readScript: cannot read script file: " << fileName;
        return QString();
    }

    QTextStream stream(&f);
    stream.setCodec("UTF-8");
    QString contents = stream.readAll();
    f.close();

    return contents;
    */
}

void RScriptHandlerEcma::createActionDocumentLevel(const QString& scriptFile,
        RGuiAction* guiAction, RDocumentInterface* documentInterface) {

    if (engine->isEvaluating()) {
        //qWarning() << "RScriptHandlerEcma::createActionDocumentLevel(): "
        //           << scriptFile
        //           << ": Engine is busy. Aborting...";
        return;
    }

    if (guiAction==NULL) {
        qWarning() << "RScriptHandlerEcma::createActionDocumentLevel(): "
                   << "guiAction is NULL";
    }

    if (documentInterface == NULL && guiAction!=NULL) {
        documentInterface = guiAction->getDocumentInterface();
    }
    if (documentInterface == NULL) {
        documentInterface = RMainWindow::getDocumentInterfaceStatic();
    }
    if (documentInterface == NULL) {
        qWarning() << "RScriptHandlerEcma::createActionDocumentLevel(): "
                   << scriptFile
                   << ": No document interface given or found.";
        return;
    }

    if (!QFileInfo(scriptFile).exists()) {
        getScriptEngine().currentContext()->throwError(QString(
                "File %1 does not exists.").arg(scriptFile));
        return;
    }

    doScript(scriptFile);

    QString className = QFileInfo(scriptFile).completeBaseName();
    QScriptValue globalObject = getScriptEngine().globalObject();
    QScriptValue ecmaConstructor = globalObject.property(className);
    if (!(ecmaConstructor.isValid() && ecmaConstructor.isFunction())) {
        getScriptEngine().currentContext()->throwError(
                QString("Class not found or not valid: %1").arg(className));
        return;
    }

    // call constructor of ECMA class with GUI action as argument:
    QScriptValueList constructorArgs;
    constructorArgs.append(getScriptEngine().toScriptValue(guiAction));
    QScriptValue ecmaObject = ecmaConstructor.construct(constructorArgs);

//    if (engine->hasUncaughtException()) {
//        qWarning() << engine->uncaughtException().toString();
//        qWarning() << "Exception Backtrace:";
//        qWarning() << engine->uncaughtExceptionBacktrace().join("\n");
//        Q_ASSERT(false);
//    }

    if (!ecmaObject.isValid()) {
        getScriptEngine().currentContext()->throwError(QString(
                "Constructor %1 not found.").arg(className));
        return;
    }

    REcmaShellActionAdapter* action = qscriptvalue_cast<REcmaShellActionAdapter*>(ecmaObject.prototype());
    //REcmaShellActionAdapter* action = qscriptvalue_cast<REcmaShellActionAdapter*>(ecmaObject);
    //REcmaShellActionAdapter* action = new REcmaShellActionAdapter(guiAction);
    if (action!=NULL) {
        if (documentInterface != NULL) {
            // essential to rescue member variables that were set in the constructor:
            action->__qtscript_self = ecmaObject;
            documentInterface->setCurrentAction(action);
        }
        else {
            qDebug() << "RScriptHandlerEcma::createActionDocumentLevel: documentInterface is NULL";
        }
    }
    else {
        qDebug() << "RScriptHandlerEcma::createActionDocumentLevel: action is NULL";
    }
}

void RScriptHandlerEcma::createActionApplicationLevel(
        const QString& scriptFile, RGuiAction* guiAction) {

    //createActionApplicationLevelT<RScriptActionEcma> (scriptFile, guiAction);

    if (!QFileInfo(scriptFile).exists()) {
        engine->currentContext()->throwError(QString(
                "File %1 does not exists.").arg(scriptFile));
        return;
    }

    engine->currentContext()->setActivationObject(engine->globalObject());

    doScript(scriptFile);

    QString className = QFileInfo(scriptFile).completeBaseName();
    QScriptValue globalObject = engine->globalObject();
    QScriptValue ecmaConstructor = globalObject.property(className);
    if (!ecmaConstructor.isValid()) {
        qWarning() << "class not found: " << className;
        engine->currentContext()->throwError(
                QString("Class not found: %1").arg(className));
        return;
    }

    if (!ecmaConstructor.isFunction()) {
        qWarning() << "class constructor not found: " << className;
        engine->currentContext()->throwError(
                    QString("Class constructor not found: %1").arg(className));
        return;
    }

    // call constructor of ECMA class with GUI action as argument:
    QScriptValueList constructorArgs;
    RGuiAction* guiActionQt = dynamic_cast<RGuiAction*>(guiAction);
    if (guiActionQt!=NULL) {
        constructorArgs.append(engine->toScriptValue(guiActionQt));
    }
    else {
        constructorArgs.append(engine->toScriptValue(guiAction));
    }
    QScriptValue ecmaObject = ecmaConstructor.construct(constructorArgs);
    if (!ecmaObject.isValid()) {
        qWarning() << "constructor not found: " << className;
        engine->currentContext()->throwError(QString(
                "Constructor %1 not found.").arg(className));
        return;
    }

    REcmaShellActionAdapter* action =
            qscriptvalue_cast<REcmaShellActionAdapter*>(ecmaObject.prototype());
    if (action!=NULL) {
        // essential to rescue member variables that were set in the constructor:
        action->__qtscript_self = ecmaObject;
        action->beginEvent();
        action->finishEvent();
    }
    else {
        qDebug() << "RScriptHandlerEcma::createActionApplicationLevel: action is NULL / not derived from RAction";
    }
}

/**
 * Initializes some global ECMA variables that are available to all scripts.
 */
void RScriptHandlerEcma::initGlobalVariables(const QString& scriptFile) {

    // initialize global ECMA variables:
    QScriptValue globalObject = engine->globalObject();
    globalObject.setProperty("scriptFile", QScriptValue(engine, scriptFile));
    /*
    globalObject.setProperty("scriptFilePath", QScriptValue(engine, QFileInfo(
            scriptFile).filePath()));
    */
    globalObject.setProperty("includeBasePath", QScriptValue(engine,
            QFileInfo(scriptFile).absolutePath()));
}

QScriptValue RScriptHandlerEcma::ecmaInclude(QScriptContext* context, QScriptEngine* engine) {
    QString arg;
    QString trContext;
    bool force = false;

    if (context->argumentCount() == 1 && context->argument(0).isString()) {
        arg = context->argument(0).toString();
    }
    else if (context->argumentCount() == 2 && context->argument(0).isString() && context->argument(1).isString()) {
        arg = context->argument(0).toString();
        trContext = context->argument(1).toString();
    }
    else if (context->argumentCount() == 3 && context->argument(0).isString() && context->argument(1).isString() && context->argument(2).isBool()) {
        arg = context->argument(0).toString();
        trContext = context->argument(1).toString();
        force = context->argument(2).toBool();
    }
    else {
        return context->throwError(QString("include: wrong number / type of arguments"));
    }

    return doInclude(engine, arg, trContext, force);
}


bool RScriptHandlerEcma::isIncluded(QScriptEngine* engine, const QString& className) {
    //if (alwaysLoadScripts) {
    //    return false;
    //}

    QVariant vAlreadyIncluded;

    vAlreadyIncluded = engine->property("alreadyIncluded");
    if (!vAlreadyIncluded.isValid()) {
        //qDebug() << "isIncluded: no property alreadyIncluded";
        return false;
    }

    QSet<QString> alreadyIncluded;
    alreadyIncluded = vAlreadyIncluded.value<QSet<QString> >();
    if (!alreadyIncluded.contains(className)) {
        //qDebug() << "isIncluded: not yet included: " << className;
        return false;
    }

    //qDebug() << "ecmaInclude: already included: " << className;
    return true;
}

void RScriptHandlerEcma::markIncluded(QScriptEngine* engine, const QString& className) {
    //if (alwaysLoadScripts) {
    //    return;
    //}

    QVariant vAlreadyIncluded;
    QSet<QString> alreadyIncluded;

    vAlreadyIncluded = engine->property("alreadyIncluded");
    if (vAlreadyIncluded.isValid()) {
        alreadyIncluded = vAlreadyIncluded.value<QSet<QString> >();
        //qDebug() << "markIncluded: alreadyIncluded: " << alreadyIncluded;
    }

    if (alreadyIncluded.contains(className)) {
        //qDebug() << "markIncluded: already in list";
        return;
    }

    alreadyIncluded.insert(className);
    vAlreadyIncluded.setValue(alreadyIncluded);
    engine->setProperty("alreadyIncluded", vAlreadyIncluded);

    //qDebug() << "markIncluded: alreadyIncluded: new[" << (int)engine << "]: " << alreadyIncluded;
}

QScriptValue RScriptHandlerEcma::doInclude(QScriptEngine* engine, const QString& arg, QString trContext, bool force) {
    static int including = 0;

    QScriptContext* context = engine->currentContext();
    //qDebug() << "ecmaInclude: " << arg;

    QString className = QFileInfo(arg).completeBaseName();

    if (!force && isIncluded(engine, className)) {
        return engine->undefinedValue();
    }

    QStringList list;
    //list << ":/scripts";
    //list << ":";
    list << engine->globalObject().property("includeBasePath").toString();
    list << QDir::currentPath();

    // remove duplicate paths:
    list = list.toSet().toList();

    QStringListIterator i(list);
    while (i.hasNext()) {
        QString basePath = i.next();

        QString fileName;
        //qDebug() << "arg: " << arg;
        QFileInfo fi(arg);
        if (fi.isAbsolute()) {
            fileName = arg;
        } else {
            fileName = basePath + QDir::separator() + arg;
            //fileName = QFileInfo(fileName).canonicalFilePath();
            //qDebug() << "fileName (canonical): " << fileName;
            fi = QFileInfo(fileName);
        }

        if (!fi.exists()) {
            //qDebug() << "ecmaInclude: file not found: " << fi.absoluteFilePath();
            continue;
        }

        //qDebug() << "ecmaInclude: including[" << (int)engine << "]: " << className << " (" << fi.absoluteFilePath() << ")";

        // file does not exist in that path or cannot be read:
        //QFile f(fileName);
        //if (!f.open(QIODevice::ReadOnly)) {
        //    continue;
        //}

        //qDebug() << "########    INCLUDING: " << fileName;

        //QTextStream stream(&f);
        //stream.setCodec("UTF-8");
        //QString contents = stream.readAll();
        //f.close();
        QString contents = readScript(fileName, force);

        //QFileInfo fi(fileName);

        if (trContext.isNull()) {
            trContext = fi.completeBaseName();
        }

        // post-processing for translation context:
        contents.replace("qsTr(\"", QString("qsTranslate('%1', \"").arg(trContext));
        contents.replace("QT_TR_NOOP(\"", QString("QT_TRANSLATE_NOOP('%1', \"").arg(trContext));

        QString includeBasePath = engine->globalObject().property("includeBasePath").toString();
        engine->globalObject().setProperty("includeBasePath", fi.absolutePath());
        //QScriptContext* nested = engine->pushContext();
        // this will make the evaluate "global":
        //nested->setActivationObject(engine->globalObject());
        context->setActivationObject(engine->globalObject());
        context->setThisObject(engine->globalObject());
        including++;
        engine->globalObject().setProperty("including", true);
        QScriptValue ret = engine->evaluate(contents, fileName);
        including--;
        engine->globalObject().setProperty("including", including!=0);

        //engine->popContext();
        engine->globalObject().setProperty("includeBasePath", includeBasePath);

        //qDebug() << "ecmaInclude: including: " << className << " DONE";

        markIncluded(engine, className);

        return ret;
    }

    return context->throwError(QString("include: cannot read file '%1'").arg(
                                   context->argument(0).toString()));
}

QScriptValue RScriptHandlerEcma::ecmaPrint(QScriptContext* context,
        QScriptEngine* engine) {
    return RScriptHandlerEcma::ecmaMessageHandler(context, engine, RS::Print);
}

QScriptValue RScriptHandlerEcma::ecmaDebug(QScriptContext* context,
        QScriptEngine* engine) {
    return RScriptHandlerEcma::ecmaMessageHandler(context, engine, RS::Debug);
}

QScriptValue RScriptHandlerEcma::ecmaWarning(QScriptContext* context,
        QScriptEngine* engine) {
    return RScriptHandlerEcma::ecmaMessageHandler(context, engine, RS::Warning);
}

QScriptValue RScriptHandlerEcma::ecmaCritical(QScriptContext* context,
        QScriptEngine* engine) {
    return RScriptHandlerEcma::ecmaMessageHandler(context, engine, RS::Critical);
}

QScriptValue RScriptHandlerEcma::ecmaGray(QScriptContext* context,
        QScriptEngine* engine) {
    if (context->argumentCount() == 1) {
        int cppResult = qGray(context->argument(0).toUInt32());
        return qScriptValueFromValue(engine, cppResult);
    } else {
        return throwError(
                "Wrong number/types of arguments for qGray().",
                context);
    }
    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaQtEscape(QScriptContext* context,
        QScriptEngine* engine) {
    if (context->argumentCount() == 1) {
        QString cppResult = Qt::escape(context->argument(0).toString());
        return qScriptValueFromValue(engine, cppResult);
    } else {
        return throwError(
                "Wrong number/types of arguments for Qt.escape().",
                context);
    }
    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaMessageHandler(QScriptContext* context,
        QScriptEngine* engine, RS::MessageType type) {
    //QScriptValue globalObject = engine->globalObject();
    //QString scriptFile = globalObject.property("scriptFile").toString();

    QString str;
    for (int i = 0; i < context->argumentCount(); ++i) {
        if (i != 0) {
            str += " ";
        }
        str += context->argument(i).toString();
    }

    switch (type) {
    case RS::Command:
    case RS::Print:
        std::cout << (const char*)str.toUtf8() << std::endl;
        break;
    case RS::Debug:
        qDebug() << qPrintable(str);
        break;
    case RS::Warning:
        qWarning() << qPrintable(str);
        break;
    case RS::Critical:
        qCritical() << qPrintable(str);
        break;
    }

    return qScriptValueFromValue(engine, str);
}

/*
QScriptValue RScriptHandlerEcma::ecmaQListViewMousePressEvent(QScriptContext* context,
        QScriptEngine* engine) {
    QtScriptShell_QListView* self =
            qscriptvalue_cast<QtScriptShell_QListView*> (context->thisObject().prototype());
    if (self == NULL) {
        return throwError("QListView.mousePressEvent(): This object is not a QListView",
                context);
    }
    QMouseEvent* evt = REcmaHelper::scriptValueTo<QMouseEvent>(
            context->argument(0));
    self->mousePressEvent(evt);
}
*/

QScriptValue RScriptHandlerEcma::ecmaQDomNodeAppendChild(QScriptContext* context,
        QScriptEngine* engine) {

    QScriptValue result = engine->undefinedValue();
    QDomNode* self = qscriptvalue_cast<QDomNode*> (context->thisObject());
    if (self == NULL) {
        return throwError("QDomNode.appendChild(): This object is not a QDomNode",
                context);
    }

    if (context->argumentCount() == 1 && context->argument(0).isVariant()) {
        QDomNode* node = qscriptvalue_cast<QDomNode*> (context->argument(0));
        QDomNode cppResult = self->appendChild(*node);
        result = qScriptValueFromValue(engine, cppResult);
    } else {
        return throwError(
                "Wrong number/types of arguments for QDomNode.appendChild().",
                context);
    }
    return result;
}

QScriptValue RScriptHandlerEcma::ecmaQDomNodeRemoveChild(QScriptContext* context,
        QScriptEngine* engine) {

    QScriptValue result = engine->undefinedValue();
    QDomNode* self = qscriptvalue_cast<QDomNode*> (context->thisObject());
    if (self == NULL) {
        return throwError("QDomNode.removeChild(): This object is not a QDomNode",
                context);
    }

    if (context->argumentCount() == 1 && context->argument(0).isVariant()) {
        QDomNode* node = qscriptvalue_cast<QDomNode*> (context->argument(0));
        QDomNode cppResult = self->removeChild(*node);
        result = qScriptValueFromValue(engine, cppResult);
    } else {
        return throwError(
                "Wrong number/types of arguments for QDomNode.removeChild().",
                context);
    }
    return result;
}

QScriptValue RScriptHandlerEcma::ecmaQObjectFindChild(QScriptContext* context,
        QScriptEngine* engine) {

    QScriptValue result = engine->undefinedValue();
    QObject* self = qscriptvalue_cast<QObject*> (context->thisObject());
    if (self == NULL) {
        return throwError("QObject.findChild(): This object is not a QObject",
                context);
    }

    if (context->argumentCount() == 1 && context->argument(0).isString()) {
        QString name = context->argument(0).toString();
        QObject* cppResult = self->findChild<QObject*> (name);
        if (cppResult == NULL) {
            /*
            qWarning(
                    QString(
                            "RScriptHandlerEcma::ecmaQObjectFindChild(): widget %1 not found").arg(
                            name));
            */
            return engine->undefinedValue();
        }
        result = engine->newQObject(cppResult);
    } else {
        return throwError(
                "Wrong number/types of arguments for QObject.findChild().",
                context);
    }

    return result;
}

QScriptValue RScriptHandlerEcma::ecmaQObjectGetChildren(QScriptContext* context,
        QScriptEngine* engine) {

    QScriptValue result = engine->undefinedValue();
    QObject* self = qscriptvalue_cast<QObject*> (context->thisObject());
    if (self == NULL) {
        return throwError("QObject.getChildren(): This object is not a QObject",
                context);
    }

    if (context->argumentCount() == 0) {
        QObjectList objList = self->children();
        QObjectList cppResult;
//        QVariantList vl;
//        qDebug() << "RScriptHandlerEcma::ecmaQObjectGetChildren: typeName: objList.size(): " << objList.size();
        for (int i=0; i<objList.size(); i++) {
            //if (dynamic_cast<QFormInternal::TranslationWatcher*>(objList.at(i))!=NULL) {
            //    continue;
            //}
            QString typeName = objList.at(i)->metaObject()->className();
//            qDebug() << "RScriptHandlerEcma::ecmaQObjectGetChildren: typeName: " << typeName;
            if (typeName=="QFormInternal::TranslationWatcher") {
                continue;
            }
            if (typeName=="QWebView") {
                continue;
            }
            //vl.append(objList.at(i));
            cppResult.append(objList.at(i));
        }
        //result = engine->newVariant(vl);
        result = REcmaHelper::listToScriptValue(engine, cppResult);
        //result = qScriptValueFromSequence(cppResult);
    } else {
        return throwError(
                "Wrong number/types of arguments for QObject.getChildren().",
                context);
    }

    return result;
}

//QScriptValue RScriptHandlerEcma::ecmaQDateTimeToString(QScriptContext* context,
//        QScriptEngine* engine) {

//    qDebug() << "RScriptHandlerEcma::ecmaQDateTimeToString";
//    QDateTime* self = REcmaHelper::scriptValueTo<QDateTime>(context->thisObject());
//    if (self == NULL) {
//        return throwError("QDateTime.toString(): Object is NULL", context);
//    }

//    if (context->argumentCount() == 1) {
//        QString format = context->argument(0).toString();
//        return qScriptValueFromValue(engine, QString(self->toString(format)));
//    }
//    else {
//        return qScriptValueFromValue(engine, QString(self->toString()));
//    }
//}

QScriptValue RScriptHandlerEcma::ecmaAttachDebugger(QScriptContext* context,
        QScriptEngine* engine) {
    Q_UNUSED(context)

    QScriptEngineDebugger* debugger =
            engine->findChild<QScriptEngineDebugger*> ("debugger");
    if (debugger != NULL) {
        qWarning() << "RScriptHandlerEcma::ecmaAttachDebugger: script debugger already attached.";
        return engine->undefinedValue();
    }

    qWarning() << "RScriptHandlerEcma::ecmaAttachDebugger: attaching script debugger. Not recommended.";
    debugger = new QScriptEngineDebugger(engine);
    debugger->setObjectName("debugger");
    debugger->attachTo(engine);

    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaDetachDebugger(QScriptContext* context,
        QScriptEngine* engine) {
    Q_UNUSED(context)

    QScriptEngineDebugger* debugger =
            engine->findChild<QScriptEngineDebugger*> ("debugger");
    if (debugger == NULL) {
        qWarning() << "RScriptHandlerEcma::ecmaDetachDebugger: script debugger not attached.";
        return engine->undefinedValue();
    }

    debugger->detach();
    delete debugger;

    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaCollectGarbage(QScriptContext* context,
                                                    QScriptEngine* engine) {
    Q_UNUSED(context)
    engine->collectGarbage();
    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaDestroy(QScriptContext* context,
        QScriptEngine* engine) {
    //  QScriptValue arg = context->argument(0);

    //  void* self = arg.data().toVariant().data();
    QObject* self = qscriptvalue_cast<QObject*> (context->thisObject());

    if (self == NULL) {
        return throwError("RDocument.destroy(): Object is NULL", context);
    }
    delete self;
    self = NULL;

    context->thisObject().setData(engine->nullValue());
    context->thisObject().prototype().setData(engine->nullValue());
    context->thisObject().setPrototype(engine->nullValue());
    context->thisObject().setScriptClass(NULL);
    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaQPrinterDestroy(QScriptContext* context,
        QScriptEngine* engine) {
    QPrinter* self = qscriptvalue_cast<QPrinter*> (context->thisObject());

    if (self == NULL) {
        return throwError("QPrinter.destroy(): Object is NULL", context);
    }
    delete self;
    self = NULL;

    context->thisObject().setData(engine->nullValue());
    context->thisObject().prototype().setData(engine->nullValue());
    context->thisObject().setPrototype(engine->nullValue());
    context->thisObject().setScriptClass(NULL);
    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaQPainterDestroy(QScriptContext* context,
        QScriptEngine* engine) {
    QPainter* self = qscriptvalue_cast<QPainter*> (context->thisObject());

    if (self == NULL) {
        return throwError("QPainter.destroy(): Object is NULL", context);
    }
    delete self;
    self = NULL;

    context->thisObject().setData(engine->nullValue());
    context->thisObject().prototype().setData(engine->nullValue());
    context->thisObject().setPrototype(engine->nullValue());
    context->thisObject().setScriptClass(NULL);
    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaQXmlResultItemsDestroy(QScriptContext* context,
                                                     QScriptEngine* engine) {
    QXmlResultItems* self = qscriptvalue_cast<QXmlResultItems*> (context->thisObject());

    if (self == NULL) {
        return throwError("QXmlResultItems.destroy(): Object is NULL", context);
    }
    delete self;
    self = NULL;

    context->thisObject().setData(engine->nullValue());
    context->thisObject().prototype().setData(engine->nullValue());
    context->thisObject().setPrototype(engine->nullValue());
    context->thisObject().setScriptClass(NULL);
    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaQXmlStreamWriterDestroy(QScriptContext* context,
                                                            QScriptEngine* engine) {
    QXmlStreamWriter* self = qscriptvalue_cast<QXmlStreamWriter*> (context->thisObject());

    if (self == NULL) {
        return throwError("QXmlStreamWriter.destroy(): Object is NULL", context);
    }
    delete self;
    self = NULL;

    context->thisObject().setData(engine->nullValue());
    context->thisObject().prototype().setData(engine->nullValue());
    context->thisObject().setPrototype(engine->nullValue());
    context->thisObject().setScriptClass(NULL);
    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaQLayoutGetWidth(QScriptContext* context,
        QScriptEngine* engine) {
    QLayout* self = REcmaHelper::scriptValueTo<QLayout>(context->thisObject());
    if (self == NULL) {
        return throwError("QLayout.getWidth(): Object is NULL", context);
    }

    if (context->argumentCount() != 0) {
        return throwError("Wrong number/types of arguments for QLayout::getWidth.", context);
    }

    int cppResult = self->geometry().width();
    return qScriptValueFromValue(engine, cppResult);
}

QScriptValue RScriptHandlerEcma::ecmaQByteArrayToString(QScriptContext* context,
        QScriptEngine* engine) {

    QByteArray* self = REcmaHelper::scriptValueTo<QByteArray>(context->thisObject());
    if (self == NULL) {
        return throwError("QByteArray.toString(): Object is NULL", context);
    }

    if (context->argumentCount() != 0) {
        return throwError("Wrong number/types of arguments for QByteArray.toString.", context);
    }

    return qScriptValueFromValue(engine, QString(self->data()));
}

QScriptValue RScriptHandlerEcma::ecmaQUrlQueryItems(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue result = engine->undefinedValue();
    QUrl* self = qscriptvalue_cast<QUrl*> (context->thisObject());
    if (self == NULL) {
        return throwError("QUrl.queryItems(): This object is not a QUrl", context);
    }

    if (context->argumentCount() == 0) {
        QUrl* url = qscriptvalue_cast<QUrl*> (context->argument(0));
        QList<QPair<QString, QString> > cppResult = self->queryItems();
        result = REcmaHelper::pairListToScriptValue<QString, QString>(engine, cppResult);
    } else {
        return throwError(
                "Wrong number/types of arguments for QUrl.queryItems().",
                context);
    }
    return result;
}

QScriptValue RScriptHandlerEcma::ecmaMSleep(QScriptContext* context,
        QScriptEngine* engine) {

    Q_ASSERT(false);
    if (context->argumentCount() == 1 && context->argument(0).isNumber()) {
        int val = context->argument(0).toInteger();
        QTime dieTime = QTime::currentTime().addMSecs(val);
        int c=0;
        QTime t = QTime::currentTime();
        while (t < dieTime) {
            t = QTime::currentTime();
            QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
            ++c;
        }
    } else {
        return throwError(
                "Wrong number/types of arguments for msleep().",
                context);
    }
    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaArguments(QScriptContext* context,
        QScriptEngine* engine) {

    if (context->argumentCount() == 0) {
        QStringList cppResult = QCoreApplication::arguments();
        return qScriptValueFromValue(engine, cppResult);
    } else {
        return throwError(
                "Wrong number/types of arguments for arguments().",
                context);
    }
    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaGetObjectId(QScriptContext* context,
        QScriptEngine* engine) {
    QScriptValue result = engine->undefinedValue();
    QObject* self = qscriptvalue_cast<QObject*> (context->thisObject());
    if (self == NULL) {
        return qScriptValueFromValue(engine, QString("NULL"));
    }
    return qScriptValueFromValue(engine, QString("%1 (0x%2)").arg(
            self->metaObject()->className()).arg((long int) self, 0, 16));
}

QScriptValue RScriptHandlerEcma::ecmaImportExtension(QScriptContext* context,
        QScriptEngine* engine) {
    return engine->importExtension(context->argument(0).toString());
}

QScriptValue RScriptHandlerEcma::ecmaIsDeleted(QScriptContext* context,
        QScriptEngine* engine) {
    if (context->argumentCount() == 1) {
        // not a QObject at all. cannot determine if the object was deleted:
        if (!context->argument(0).isQObject()) {
            return qScriptValueFromValue(engine, false);
        }

        //QObject* obj = qscriptvalue_cast<QObject*> (context->argument(0));
        QObject* obj = context->argument(0).toQObject();
        return qScriptValueFromValue(engine, obj == NULL);
    } else {
        return throwError("Wrong number/types of arguments for isDeleted().",
                context);
    }
}

//QScriptValue RScriptHandlerEcma::ecmaUnblockEvents(QScriptContext* context,
//        QScriptEngine* engine) {
//    Q_UNUSED(context)
//    Q_UNUSED(engine)

//    QAbstractEventDispatcher* evtDisp = QAbstractEventDispatcher::instance();
//    evtDisp->setEventFilter(defaultEventFilter);
//    return QScriptValue();
//}

QScriptValue RScriptHandlerEcma::ecmaAddApplicationFont(QScriptContext* context,
        QScriptEngine* engine) {

    if (context->argumentCount() == 1 && context->argument(0).isString()) {
        QString val = context->argument(0).toString();
        int ret = QFontDatabase::addApplicationFont(val);
        return qScriptValueFromValue(engine, ret);
    } else {
        return throwError(
                "Wrong number/types of arguments for addApplicationFont().",
                context);
    }
}

QScriptValue RScriptHandlerEcma::ecmaDownload(QScriptContext* context,
        QScriptEngine* engine) {

    if (context->argumentCount() == 2 && context->argument(0).isString() && context->argument(1).isNumber()) {
        QString url = context->argument(0).toString();
        int timeout = context->argument(1).toInteger();

        QNetworkAccessManager manager;
        QEventLoop loop;
        QNetworkReply *reply = manager.get(QNetworkRequest(url));
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

        // timeout:
        if (timeout>0) {
            QTimer::singleShot(timeout, &loop, SLOT(quit()));
        }

        // run loop:
        loop.exec();

        if (reply->error()!=QNetworkReply::NoError) {
            qDebug() << "Cannot download " << url << ": "<< reply->errorString();
        }

        QString content = reply->readAll();

        delete reply;

        return qScriptValueFromValue(engine, content);
    } else {
        return throwError(
                "Wrong number/types of arguments for download().",
                context);
    }
}

QScriptValue RScriptHandlerEcma::ecmaQSortFilterProxyModelCastToQAbstractItemModel(
    QScriptContext* context, QScriptEngine* engine) {

    QSortFilterProxyModel* self = REcmaHelper::scriptValueTo<QSortFilterProxyModel>(context->thisObject());
    if (self == NULL) {
        return throwError("QSortFilterProxyModel.castToQAbstractItemModel(): Object is NULL", context);
    }

    if (context->argumentCount() != 0) {
        return throwError("Wrong number/types of arguments for QSortFilterProxyModel.castToQAbstractItemModel.", context);
    }

    return engine->newQObject(dynamic_cast<QAbstractItemModel*>(self));
}

//QScriptValue RScriptHandlerEcma::ecmaQFontDatabaseFamilies(QScriptContext* context, QScriptEngine* engine) {
//    QFontDatabase fdb;
//    QStringList ret = fdb.families();
//    return engine->toScriptValue(ret);
//}

/*
QScriptValue RScriptHandlerEcma::ecmaGetOpt(QScriptContext* context,
        QScriptEngine* engine) {


    QMap<QString,QString> map;
    if (context->argumentCount() == 2 && context->argument(0).isArray()
            && context->argument(1).isArray()) {
        QStringList a0;
        REcmaHelper::fromScriptValue(engine, context->argument(0), a0);
        char** argv = new char*[a0.size()];
        for (int i = 0; i < a0.size(); ++i) {
            QString s = a0.at(i);
            argv[i] = new char[s.length() + 1];
            strcpy(argv[i], (const char*) s.toLatin1());
        }

        QList<QStringList> a1;
        REcmaHelper::fromScriptValue(engine, context->argument(1), a1);

        int size = a1.size();
        struct option* long_options = new option[size + 1];
        char** ccname = new char*[size];
        option* opt = new option[size];

        QString shortOptions;
        for (int i = 0; i < size; ++i) {
            QStringList sl = a1.at(i);

            char c;
            if (sl.at(2).size() == 0) {
                c = 0;
            } else {
                c = sl.at(2).toAscii().at(0);
            }

            QString name(sl.at(0));
            ccname[i] = new char[name.toLatin1().size() + 1];
            strcpy(ccname[i], name.toLatin1());

            int hasArgs = no_argument;
            if (sl.at(1) == "true") {
                hasArgs = required_argument;
            }

            opt[i].name = ccname[i];
            opt[i].has_arg = hasArgs;
            opt[i].flag = 0;
            opt[i].val = c;
            long_options[i] = opt[i];

            shortOptions.append(QString(c));
            if (hasArgs == required_argument) {
                shortOptions.append(":");
            }
        }
        option end_opt = { 0, 0, 0, 0 };
        long_options[size] = end_opt;

        int option_index = 0;
        while (1) {
            QByteArray shortOptionsBA = shortOptions.toLatin1();
            int c = getopt_long_only(a0.size(), argv,
                    (const char*)shortOptionsBA, long_options,
                    &option_index);

            if (c == -1) {
                break;
            }
            if (c == 0) {
                // If this option set a flag, do nothing else now.
                if (long_options[option_index].flag != 0) {
                    break;
                }
                map.insert(QString(long_options[option_index].name), QString(
                        optarg));
                continue;
            }
            if (shortOptions.contains(QChar(c))) {
                map.insert(QString(c), QString(optarg));
            }
        }

    } else {
        return throwError("Wrong number/types of arguments for getOpt().",
                context);
    }

    return REcmaHelper::toScriptValue(engine, map);
}
*/

QScriptValue RScriptHandlerEcma::ecmaBlockEvents(QScriptContext* context,
        QScriptEngine* engine) {
    Q_UNUSED(context)
    Q_UNUSED(engine)

    QAbstractEventDispatcher* evtDisp = QAbstractEventDispatcher::instance();
    defaultEventFilter = evtDisp->setEventFilter(RScriptHandlerEcma::eventFilter);
    return QScriptValue();
}

bool RScriptHandlerEcma::eventFilter(void *message) {
    Q_UNUSED(message)

    return true;
}

QScriptValue RScriptHandlerEcma::ecmaSerialize(QScriptContext* context,
        QScriptEngine* engine) {
    if (context->argumentCount() == 1) {
        QByteArray* b = qscriptvalue_cast<QByteArray*> (context->argument(0));
        if (b == NULL) {
            return throwError("Argument 0 is not QByteArray", context);
        }
        QByteArray ba = b->toHex();
        return qScriptValueFromValue(engine, QString(ba.data()));
    } else {
        return throwError("Wrong number/types of arguments for serialize().",
                context);
    }
}

QScriptValue RScriptHandlerEcma::throwError(const QString& message,
        QScriptContext* context) {
    QScriptContextInfo contextInfo(context);
    return context->throwError(QString("%1:%2:%3: %4\n%5") .arg(
            contextInfo.fileName()) .arg(contextInfo.lineNumber()) .arg(
            contextInfo.columnNumber()) .arg(message) .arg(
            context->backtrace().join("\n")));
}

void RScriptHandlerEcma::exceptionHandler(const QScriptValue& exception) {
    qWarning() << "Script Exception:\n" << exception.toString();
}
