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
#include <iostream>

#include <QDomNode>
#include <QFile>
#include <QRegExp>
#include <QScriptEngine>
#include <QScriptValueIterator>
#include <QStringList>
#include <QTextCharFormat>
#include <QTextStream>
#include <QFontDatabase>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintDialog>
#include <QXmlResultItems>
#include <QXmlStreamWriter>
#include <QXmlContentHandler>

#include <QtScriptTools>

#include "RAutoLoadEcma.h"
#include "RDebug.h"
#include "REcmaHelper.h"
#include "RMetaTypes.h"
#include "RScriptHandlerEcma.h"
#include "RScriptHandlerRegistry.h"
#include "RSingleApplication.h"

#include "REcmaAction.h"
#include "REcmaActionAdapter.h"
#include "REcmaAddObjectOperation.h"
#include "REcmaAddObjectsOperation.h"
#include "REcmaArc.h"
#include "REcmaArcData.h"
#include "REcmaArcEntity.h"
#include "REcmaAutoLoadEcma.h"
#include "REcmaAttributeData.h"
#include "REcmaAttributeEntity.h"
#include "REcmaAttributeDefinitionData.h"
#include "REcmaAttributeDefinitionEntity.h"
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
#include "REcmaClickReferencePointOperation.h"
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
#include "REcmaDimAngular2LData.h"
#include "REcmaDimAngular2LEntity.h"
#include "REcmaDimAngular3PData.h"
#include "REcmaDimAngular3PEntity.h"
#include "REcmaDimArcLengthData.h"
#include "REcmaDimArcLengthEntity.h"
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
#include "REcmaDocumentVariables.h"
#include "REcmaDockWidget.h"
#include "REcmaDxfServices.h"
#include "REcmaEllipse.h"
#include "REcmaEllipseData.h"
#include "REcmaEllipseEntity.h"
#include "REcmaEntity.h"
#include "REcmaEntityData.h"
#include "REcmaEntityExportListener.h"
#include "REcmaEntityExportListenerAdapter.h"
#include "REcmaEntityPickEvent.h"
#include "REcmaEventFilter.h"
#include "REcmaEventHandler.h"
#include "REcmaExporter.h"
#include "REcmaExportListener.h"
#include "REcmaExportListenerAdapter.h"
#include "REcmaFaceData.h"
#include "REcmaFaceEntity.h"
#include "REcmaFileCache.h"
#include "REcmaFileExporter.h"
#include "REcmaFileExporterAdapter.h"
#include "REcmaFileExporterFactory.h"
#include "REcmaFileExporterFactoryAdapter.h"
#include "REcmaFileExporterRegistry.h"
#include "REcmaFileImporter.h"
#include "REcmaFileImporterAdapter.h"
#include "REcmaFileImporterFactory.h"
#include "REcmaFileImporterFactoryAdapter.h"
#include "REcmaFileImporterRegistry.h"
#include "REcmaFileSystemModel.h"
#include "REcmaFlowLayout.h"
#include "REcmaFocusListener.h"
#include "REcmaFocusListenerAdapter.h"
#include "REcmaFontChooserWidget.h"
#include "REcmaFontDatabase.h"
#include "REcmaFont.h"
#include "REcmaFontList.h"
#include "REcmaGraphicsScene.h"
#include "REcmaGraphicsSceneQt.h"
#include "REcmaGraphicsSceneDrawable.h"
#include "REcmaGraphicsView.h"
#include "REcmaGraphicsViewImage.h"
#include "REcmaGraphicsViewQt.h"
#include "REcmaGrid.h"
#include "REcmaGuiAction.h"
#include "REcmaHatchData.h"
#include "REcmaHatchEntity.h"
#include "REcmaImageData.h"
#include "REcmaImageEntity.h"
#include "REcmaImporter.h"
#include "REcmaImportListener.h"
#include "REcmaImportListenerAdapter.h"
#include "REcmaInputEvent.h"
#include "REcmaInterTransactionListener.h"
#include "REcmaInterTransactionListenerAdapter.h"
#include "REcmaKeyListener.h"
#include "REcmaKeyListenerAdapter.h"
#include "REcmaLayer.h"
#include "REcmaLayerListener.h"
#include "REcmaLayerListenerAdapter.h"
#include "REcmaLayerState.h"
#include "REcmaLayout.h"
#include "REcmaLeaderData.h"
#include "REcmaLeaderEntity.h"
#include "REcmaLine.h"
#include "REcmaLineData.h"
#include "REcmaLineEntity.h"
#include "REcmaLinetype.h"
#include "REcmaLinetypeCombo.h"
#include "REcmaLinetypePattern.h"
#include "REcmaLineweight.h"
#include "REcmaLinkedStorage.h"
#include "REcmaLineweightCombo.h"
#include "REcmaListView.h"
#include "REcmaListWidget.h"
#include "REcmaMainWindow.h"
#include "REcmaMainWindowQt.h"
#include "REcmaMath.h"
#include "REcmaMatrix.h"
#include "REcmaMathComboBox.h"
#include "REcmaMathLineEdit.h"
#include "REcmaMdiArea.h"
#include "REcmaMdiChildQt.h"
#include "REcmaMemoryStorage.h"
#include "REcmaMixedOperation.h"
#include "REcmaModifyObjectOperation.h"
#include "REcmaModifyObjectsOperation.h"
#include "REcmaMouseEvent.h"
#include "REcmaMoveReferencePointOperation.h"
#include "REcmaMoveSelectionOperation.h"
#include "REcmaNewDocumentListener.h"
#include "REcmaNewDocumentListenerAdapter.h"
#include "REcmaNavigationAction.h"
#include "REcmaObject.h"
#include "REcmaOperation.h"
#include "REcmaOperationUtils.h"
#include "REcmaOrthoGrid.h"
#include "REcmaPainterPath.h"
#include "REcmaPainterPathDevice.h"
#include "REcmaPasteOperation.h"
#include "REcmaPattern.h"
#include "REcmaPatternLine.h"
#include "REcmaPatternListMetric.h"
#include "REcmaPatternListImperial.h"
#include "REcmaPaletteListener.h"
#include "REcmaPaletteListenerAdapter.h"
#include "REcmaPenListener.h"
#include "REcmaPenListenerAdapter.h"
#include "REcmaPluginLoader.h"
#include "REcmaPluginInfo.h"
#include "REcmaPluginInterface.h"
#include "REcmaPoint.h"
#include "REcmaPointData.h"
#include "REcmaPointEntity.h"
#include "REcmaPolyline.h"
#include "REcmaPolylineData.h"
#include "REcmaPolylineEntity.h"
#include "REcmaPreferencesListener.h"
#include "REcmaPreferencesListenerAdapter.h"
#include "REcmaPropertyAttributes.h"
#include "REcmaPropertyChange.h"
#include "REcmaPropertyEditor.h"
#include "REcmaPropertyEvent.h"
#include "REcmaPropertyListener.h"
#include "REcmaPropertyTypeId.h"
#include "REcmaRay.h"
#include "REcmaRayData.h"
#include "REcmaRayEntity.h"
#include "REcmaRefPoint.h"
#include "REcmaRestrictAngleLength.h"
#include "REcmaRestrictHorizontal.h"
#include "REcmaRestrictVertical.h"
#include "REcmaRestrictOrthogonal.h"
#include "REcmaRestrictOff.h"
#include "REcmaRuler.h"
#include "REcmaRulerQt.h"
#include "REcmaRunner.h"
#include "REcmaS.h"
#include "REcmaScaleSelectionOperation.h"
#include "REcmaScriptAction.h"
#include "REcmaScriptHandler.h"
#include "REcmaSelectionListener.h"
#include "REcmaSelectionListenerAdapter.h"
#include "REcmaSettings.h"
#include "REcmaShape.h"
#include "REcmaSharedPointerArc.h"
#include "REcmaSharedPointerArcEntity.h"
#include "REcmaSharedPointerAttributeDefinitionEntity.h"
#include "REcmaSharedPointerAttributeEntity.h"
#include "REcmaSharedPointerBlock.h"
#include "REcmaSharedPointerBlockReferenceEntity.h"
#include "REcmaSharedPointerBox.h"
#include "REcmaSharedPointerCircle.h"
#include "REcmaSharedPointerCircleEntity.h"
#include "REcmaSharedPointerDimAlignedEntity.h"
#include "REcmaSharedPointerDimAngularEntity.h"
#include "REcmaSharedPointerDimAngular2LEntity.h"
#include "REcmaSharedPointerDimAngular3PEntity.h"
#include "REcmaSharedPointerDimArcLengthEntity.h"
#include "REcmaSharedPointerDimDiametricEntity.h"
#include "REcmaSharedPointerDimLinearEntity.h"
#include "REcmaSharedPointerDimOrdinateEntity.h"
#include "REcmaSharedPointerDimRadialEntity.h"
#include "REcmaSharedPointerDimRotatedEntity.h"
#include "REcmaSharedPointerDimensionEntity.h"
#include "REcmaSharedPointerDocumentVariables.h"
#include "REcmaSharedPointerEllipse.h"
#include "REcmaSharedPointerEllipseEntity.h"
#include "REcmaSharedPointerEntity.h"
#include "REcmaSharedPointerFaceEntity.h"
#include "REcmaSharedPointerHatchEntity.h"
#include "REcmaSharedPointerImageEntity.h"
#include "REcmaSharedPointerLayer.h"
#include "REcmaSharedPointerLayerState.h"
#include "REcmaSharedPointerLayout.h"
#include "REcmaSharedPointerLeaderEntity.h"
#include "REcmaSharedPointerLine.h"
#include "REcmaSharedPointerLineEntity.h"
#include "REcmaSharedPointerLinetype.h"
#include "REcmaSharedPointerObject.h"
#include "REcmaSharedPointerPoint.h"
#include "REcmaSharedPointerPointEntity.h"
#include "REcmaSharedPointerPolyline.h"
#include "REcmaSharedPointerPolylineEntity.h"
#include "REcmaSharedPointerRay.h"
#include "REcmaSharedPointerRayEntity.h"
#include "REcmaSharedPointerShape.h"
#include "REcmaSharedPointerSolidEntity.h"
#include "REcmaSharedPointerSpline.h"
#include "REcmaSharedPointerSplineEntity.h"
#include "REcmaSharedPointerTextBasedData.h"
#include "REcmaSharedPointerTextBasedEntity.h"
#include "REcmaSharedPointerTextData.h"
#include "REcmaSharedPointerTextEntity.h"
#include "REcmaSharedPointerTextLabel.h"
#include "REcmaSharedPointerToleranceEntity.h"
#include "REcmaSharedPointerTraceEntity.h"
#include "REcmaSharedPointerTriangle.h"
#include "REcmaSharedPointerUcs.h"
#include "REcmaSharedPointerView.h"
#include "REcmaSharedPointerViewportEntity.h"
#include "REcmaSharedPointerXLine.h"
#include "REcmaSharedPointerXLineEntity.h"
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
#include "REcmaSnapTangential.h"
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
#include "REcmaTextBasedData.h"
#include "REcmaTextBasedEntity.h"
#include "REcmaTextData.h"
#include "REcmaTextEdit.h"
#include "REcmaTextEntity.h"
#include "REcmaTextLabel.h"
#include "REcmaTextLayout.h"
#include "REcmaTextRenderer.h"
#include "REcmaThread.h"
#include "REcmaToleranceData.h"
#include "REcmaToleranceEntity.h"
#include "REcmaToolButton.h"
#include "REcmaToolMatrixItemDelegate.h"
#include "REcmaTraceData.h"
#include "REcmaTraceEntity.h"
#include "REcmaTransformation.h"
#include "REcmaTransform.h"
#include "REcmaTransformOp.h"
#include "REcmaTranslation.h"
#include "REcmaTransaction.h"
#include "REcmaTransactionListener.h"
#include "REcmaTransactionListenerAdapter.h"
#include "REcmaTreeWidget.h"
#include "REcmaTriangle.h"
#include "REcmaUcs.h"
#include "REcmaUnit.h"
#include "REcmaVector.h"
#include "REcmaView.h"
#include "REcmaViewFocusListener.h"
#include "REcmaViewFocusListenerAdapter.h"
#include "REcmaViewListener.h"
#include "REcmaViewListenerAdapter.h"
#include "REcmaViewportData.h"
#include "REcmaViewportEntity.h"
#include "REcmaWheelEvent.h"
#include "REcmaWidget.h"
#include "REcmaXLine.h"
#include "REcmaXLineData.h"
#include "REcmaXLineEntity.h"

//#if QT_VERSION < 0x050600
//#  if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
//#    include "REcmaWebView.h"
//#  endif
//#endif

bool RScriptHandlerEcma::alwaysLoadScripts = false;
bool RScriptHandlerEcma::translatorInstalled = false;
//QAbstractEventDispatcher::EventFilter RScriptHandlerEcma::defaultEventFilter;

RScriptHandlerEcma::RScriptHandlerEcma() : engine(NULL), debugger(NULL) {
    //  registerScriptHandler(this, getSupportedFileExtensionsStatic());
    engine = new QScriptEngine();

    alwaysLoadScripts = qApp->arguments().contains("-always-load-scripts");

    // only enable script debugger over command line as expert option.
    // Script debugger can cause crashes.
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

//#if QT_VERSION >= 0x050000
//    modules << "qt.core" << "qt.gui" << "qt.printsupport" << "qt.widgets" << "qt.uitools" << "qt.webkit"
//            << "qt.webkitwidgets" << "qt.sql" << "qt.xml" << "qt.xmlpatterns";
//#else
//    modules << "qt.core" << "qt.gui" << "qt.uitools" << "qt.webkit" << "qt.sql"
//            << "qt.svg" << "qt.xml" << "qt.xmlpatterns" << "qt.network";
//#endif

    modules = engine->availableExtensions();

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
    
    QScriptValue globalObject = engine->globalObject();
    globalObject.setProperty("include", engine->newFunction(ecmaInclude, 1));
    globalObject.setProperty("evalAppEngine", engine->newFunction(ecmaEvalAppEngine));
    globalObject.setProperty("evalDocEngine", engine->newFunction(ecmaEvalDocEngine));
    globalObject.setProperty("print", engine->newFunction(ecmaPrint));
    globalObject.setProperty("qDebug", engine->newFunction(ecmaDebug));
    globalObject.setProperty("qWarning", engine->newFunction(ecmaWarning));
    globalObject.setProperty("qCritical", engine->newFunction(ecmaCritical));
    globalObject.setProperty("qGray", engine->newFunction(ecmaGray));

    globalObject.setProperty("bt", engine->newFunction(ecmaBacktrace));
    //globalObject.setProperty("attachDebugger", engine->newFunction(ecmaAttachDebugger));
    globalObject.setProperty("detachDebugger", engine->newFunction(ecmaDetachDebugger));
    globalObject.setProperty("collectGarbage", engine->newFunction(ecmaCollectGarbage));
    globalObject.setProperty("importExtension", engine->newFunction(ecmaImportExtension));
    globalObject.setProperty("isDeleted", engine->newFunction(ecmaIsDeleted));
    globalObject.setProperty("serialize", engine->newFunction(ecmaSerialize));
    globalObject.setProperty("addApplicationFont", engine->newFunction(ecmaAddApplicationFont));
    globalObject.setProperty("download", engine->newFunction(ecmaDownload));
    globalObject.setProperty("downloadToFile", engine->newFunction(ecmaDownloadToFile));
    globalObject.setProperty("mSleep", engine->newFunction(ecmaMSleep));
    globalObject.setProperty("parseXml", engine->newFunction(ecmaParseXml));
    globalObject.setProperty("qApp", engine->newQObject(dynamic_cast<RSingleApplication*>(qApp)));
    //globalObject.setProperty("getShapeIntersections", engine->newFunction(ecmaGetShapeIntersections));

    globalObject.setProperty("getAvailablePrinterNames", engine->newFunction(ecmaGetAvailablePrinterNames));
    globalObject.setProperty("getDefaultPrinterName", engine->newFunction(ecmaGetDefaultPrinterName));
    globalObject.setProperty("createPrinter", engine->newFunction(ecmaCreatePrinter));

    // fix Qt wrapper APIs
    QScriptValue classQObject = globalObject.property("QObject");
    classQObject.property("prototype").setProperty("findChild", engine->newFunction(ecmaQObjectFindChild));
    classQObject.property("prototype").setProperty("getChildren", engine->newFunction(ecmaQObjectGetChildren));
    classQObject.property("prototype").setProperty("getObjectId", engine->newFunction(ecmaGetObjectId));
    classQObject.property("prototype").setProperty("destroy", engine->newFunction(ecmaDestroy));

    QScriptValue classQSortFilterProxyModel = globalObject.property("QSortFilterProxyModel");
    classQSortFilterProxyModel.property("prototype").setProperty("castToQAbstractItemModel",
            engine->newFunction(ecmaQSortFilterProxyModelCastToQAbstractItemModel));

    QScriptValue classQDir = globalObject.property("QDir");
    classQDir.setProperty("separator", engine->newVariant(QDir::separator()));

    QScriptValue classQEvent = globalObject.property("QEvent");
    classQEvent.property("prototype").setProperty("cast",
            engine->newFunction(ecmaQEventCast));

    QScriptValue classQDomNode = globalObject.property("QDomNode");
    classQDomNode.property("prototype").setProperty("appendChild",
            engine->newFunction(ecmaQDomNodeAppendChild));
    classQDomNode.property("prototype").setProperty("removeChild",
            engine->newFunction(ecmaQDomNodeRemoveChild));

    QScriptValue classQTextCharFormat = globalObject.property("QTextCharFormat");
    classQTextCharFormat.property("prototype").setProperty("setFontFamilies",
            engine->newFunction(ecmaQTextCharFormatSetFontFamilies));

    QScriptValue classQFontMetrics = globalObject.property("QFontMetrics");
    classQFontMetrics.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaObjectDestroy<QFontMetrics>));

    QScriptValue classQPrinter = globalObject.property("QPrinter");
    classQPrinter.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaObjectDestroy<QPrinter>));
    classQPrinter.property("prototype").setProperty("setPdfVersion",
            engine->newFunction(ecmaQPrinterSetPdfVersion));

    QScriptValue classQPrintDialog = globalObject.property("QPrintDialog");
    classQPrintDialog.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaObjectDestroy<QPrintDialog>));

    QScriptValue classQTimer = globalObject.property("QTimer");
    classQTimer.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaObjectDestroy<QTimer>));

    QScriptValue classQImageWriter = globalObject.property("QImageWriter");
    classQImageWriter.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaObjectDestroy<QImageWriter>));

    QScriptValue classQPainter = globalObject.property("QPainter");
    classQPainter.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaObjectDestroy<QPainter>));

    QScriptValue classQXmlResultItems = globalObject.property("QXmlResultItems");
    classQXmlResultItems.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaObjectDestroy<QXmlResultItems>));

    QScriptValue classQXmlStreamWriter = globalObject.property("QXmlStreamWriter");
    classQXmlStreamWriter.property("prototype").setProperty("destroy",
            engine->newFunction(ecmaObjectDestroy<QXmlStreamWriter>));

    QScriptValue classQLayout = globalObject.property("QLayout");
    classQLayout.property("prototype").setProperty("getWidth",
            engine->newFunction(ecmaQLayoutGetWidth));

    QScriptValue classQByteArray = globalObject.property("QByteArray");
    classQByteArray.property("prototype").setProperty("toString",
            engine->newFunction(ecmaQByteArrayToString));

    QScriptValue classQUrl = globalObject.property("QUrl");
    classQUrl.property("prototype").setProperty("queryItems",
            engine->newFunction(ecmaQUrlQueryItems));

    QScriptValue classQLocale = globalObject.property("QLocale");
    classQLocale.property("prototype").setProperty("script",
            engine->newFunction(ecmaQLocaleScript));
    classQLocale.setProperty("scriptToString",
            engine->newFunction(ecmaQLocaleScriptToString));

    QScriptValue classQFile = globalObject.property("QFile");
    classQFile.property("prototype").setProperty("write",
            engine->newFunction(ecmaQFileWrite));

    QScriptValue classQImage = globalObject.property("QImage");
    classQImage.property("prototype").setProperty("pixelColor",
                                                 engine->newFunction(ecmaQImagePixelColor));
    classQImage.property("prototype").setProperty("setPixelColor",
                                                 engine->newFunction(ecmaQImageSetPixelColor));
    classQImage.property("prototype").setProperty("setColorTable",
                                                  engine->newFunction(ecmaQImageSetColorTable));

#if QT_VERSION >= 0x050000
    QScriptValue classQLineEdit = globalObject.property("QLineEdit");
    classQLineEdit.property("prototype").setProperty("validator",
            engine->newFunction(ecmaQLineEditValidator));

    // workaround API for not scriptable QModelIndexList:
    QScriptValue classQItemSelectionModel = globalObject.property("QItemSelectionModel");
    classQItemSelectionModel.property("prototype").setProperty("countSelectedRows",
            engine->newFunction(ecmaQItemSelectionModelCountSelectedRows));
    classQItemSelectionModel.property("prototype").setProperty("selectedRow",
            engine->newFunction(ecmaQItemSelectionModelSelectedRow));

//    QScriptValue classQWebPage = globalObject.property("QWebPage");
//    classQWebPage.property("prototype").setProperty("setLinkDelegationPolicy",
//            engine->newFunction(ecmaQWebPageSetLinkDelegationPolicy));

# if QT_VERSION < 0x050301
    classQFile.property("prototype").setProperty("close",
            engine->newFunction(ecmaQFileClose));
# endif
    classQFile.property("prototype").setProperty("readAll",
            engine->newFunction(ecmaQFileReadAll));

# if QT_VERSION < 0x050A00
    // causes crash in autosave under Qt 5.10:
    classQFile.property("prototype").setProperty("fileName",
            engine->newFunction(ecmaQFileFileName));
# endif
#endif

    QScriptValue classQt = globalObject.property("Qt");
    classQt.setProperty("escape", engine->newFunction(ecmaQtEscape));

    QScriptValue classQCoreApplication = globalObject.property(
            "QCoreApplication");
    classQCoreApplication.setProperty("arguments", engine->newFunction(
            ecmaArguments));
    classQCoreApplication.setProperty("exit", engine->newFunction(ecmaExit));

    // *** do not change the order ***
    REcmaMath::initEcma(*engine);
    REcmaMatrix::initEcma(*engine);
    REcmaStemmer::initEcma(*engine);

    REcmaPropertyTypeId::initEcma(*engine);

    REcmaS::initEcma(*engine);
    REcmaUnit::initEcma(*engine);
    REcmaDebug::initEcma(*engine);
    REcmaSettings::initEcma(*engine);
    REcmaColor::initEcma(*engine);
    REcmaLineweight::initEcma(*engine);
    REcmaThread::initEcma(*engine);
    REcmaRunner::initEcma(*engine);
    REcmaLinetypePattern::initEcma(*engine);
    REcmaPattern::initEcma(*engine);
    REcmaPatternLine::initEcma(*engine);
    REcmaPatternListMetric::initEcma(*engine);
    REcmaPatternListImperial::initEcma(*engine);
    REcmaFont::initEcma(*engine);
    REcmaFontList::initEcma(*engine);
    REcmaFileCache::initEcma(*engine);

    REcmaVector::initEcma(*engine);
    REcmaRefPoint::initEcma(*engine);

    REcmaImporter::initEcma(*engine);
    REcmaExporter::initEcma(*engine);

    REcmaShape::initEcma(*engine);
    REcmaSharedPointerShape::initEcma(*engine);
    REcmaArc::initEcma(*engine);
    REcmaSharedPointerArc::initEcma(*engine);
    REcmaBox::initEcma(*engine);
    REcmaCircle::initEcma(*engine);
    REcmaSharedPointerCircle::initEcma(*engine);
    REcmaEllipse::initEcma(*engine);
    REcmaSharedPointerEllipse::initEcma(*engine);
    REcmaLine::initEcma(*engine);
    REcmaSharedPointerLine::initEcma(*engine);
    REcmaXLine::initEcma(*engine);
    REcmaSharedPointerXLine::initEcma(*engine);
    REcmaRay::initEcma(*engine);
    REcmaSharedPointerRay::initEcma(*engine);
    REcmaPoint::initEcma(*engine);
    REcmaSharedPointerPoint::initEcma(*engine);
    REcmaPolyline::initEcma(*engine);
    REcmaSharedPointerPolyline::initEcma(*engine);
    REcmaSpline::initEcma(*engine);
    REcmaSharedPointerSpline::initEcma(*engine);
    REcmaTriangle::initEcma(*engine);
    REcmaSharedPointerTriangle::initEcma(*engine);
    REcmaTextLabel::initEcma(*engine);
    REcmaSharedPointerTextLabel::initEcma(*engine);

    REcmaStorage::initEcma(*engine);
    REcmaLinkedStorage::initEcma(*engine);
    REcmaMemoryStorage::initEcma(*engine);

    REcmaDocument::initEcma(*engine);
    REcmaDocumentInterface::initEcma(*engine);

    REcmaSelectionListener::initEcma(*engine);
    REcmaSelectionListenerAdapter::initEcma(*engine);
    REcmaExportListener::initEcma(*engine);
    REcmaExportListenerAdapter::initEcma(*engine);
    REcmaEntityExportListener::initEcma(*engine);
    REcmaEntityExportListenerAdapter::initEcma(*engine);
    REcmaImportListener::initEcma(*engine);
    REcmaImportListenerAdapter::initEcma(*engine);
    REcmaTransactionListener::initEcma(*engine);
    REcmaTransactionListenerAdapter::initEcma(*engine);
    REcmaInterTransactionListener::initEcma(*engine);
    REcmaInterTransactionListenerAdapter::initEcma(*engine);
    REcmaSnapListener::initEcma(*engine);
    REcmaNewDocumentListener::initEcma(*engine);
    REcmaNewDocumentListenerAdapter::initEcma(*engine);

    REcmaWidget::initEcma(*engine);
    REcmaGuiAction::initEcma(*engine);
    REcmaSpatialIndex::initEcma(*engine);
    REcmaSpatialIndexNavel::initEcma(*engine);
    REcmaSpatialIndexSimple::initEcma(*engine);
    REcmaSpatialIndexVisitor::initEcma(*engine);
    REcmaSpatialIndexVisitorAdapter::initEcma(*engine);

    REcmaGraphicsScene::initEcma(*engine);
    REcmaGraphicsSceneQt::initEcma(*engine);
    REcmaGraphicsSceneDrawable::initEcma(*engine);
    REcmaPainterPath::initEcma(*engine);
    REcmaPainterPathDevice::initEcma(*engine);

    REcmaGrid::initEcma(*engine);
    REcmaOrthoGrid::initEcma(*engine);
    REcmaRuler::initEcma(*engine);
    REcmaRulerQt::initEcma(*engine);

    REcmaSnap::initEcma(*engine);
    REcmaSnapEntityBase::initEcma(*engine);
    REcmaSnapAuto::initEcma(*engine);
    REcmaSnapCenter::initEcma(*engine);
    REcmaSnapDistance::initEcma(*engine);
    REcmaSnapEnd::initEcma(*engine);
    REcmaSnapFree::initEcma(*engine);
    REcmaSnapGrid::initEcma(*engine);
    REcmaSnapIntersection::initEcma(*engine);
    REcmaSnapMiddle::initEcma(*engine);
    REcmaSnapOnEntity::initEcma(*engine);
    REcmaSnapPerpendicular::initEcma(*engine);
    REcmaSnapReference::initEcma(*engine);
    REcmaSnapTangential::initEcma(*engine);

    REcmaSnapRestriction::initEcma(*engine);
    REcmaRestrictAngleLength::initEcma(*engine);
    REcmaRestrictHorizontal::initEcma(*engine);
    REcmaRestrictVertical::initEcma(*engine);
    REcmaRestrictOrthogonal::initEcma(*engine);
    REcmaRestrictOff::initEcma(*engine);

    REcmaGraphicsView::initEcma(*engine);
    REcmaGraphicsViewImage::initEcma(*engine);
    REcmaGraphicsViewQt::initEcma(*engine);

    REcmaMainWindow::initEcma(*engine);
    REcmaMainWindowQt::initEcma(*engine);
    REcmaMdiArea::initEcma(*engine);
    REcmaMdiChildQt::initEcma(*engine);

    REcmaAction::initEcma(*engine);
    REcmaActionAdapter::initEcma(*engine);
    REcmaNavigationAction::initEcma(*engine);
    REcmaScriptAction::initEcma(*engine);

    REcmaScriptHandler::initEcma(*engine);

    REcmaEventFilter::initEcma(*engine);
    REcmaEventHandler::initEcma(*engine);

    REcmaTerminateEvent::initEcma(*engine);
    REcmaInputEvent::initEcma(*engine);
    REcmaMouseEvent::initEcma(*engine);
    REcmaWheelEvent::initEcma(*engine);
    REcmaTabletEvent::initEcma(*engine);
    REcmaCloseCurrentEvent::initEcma(*engine);

    REcmaCommandEvent::initEcma(*engine);
    REcmaCoordinateEvent::initEcma(*engine);
    REcmaEntityPickEvent::initEcma(*engine);
    REcmaCoordinateListener::initEcma(*engine);
    REcmaCoordinateListenerAdapter::initEcma(*engine);

    REcmaObject::initEcma(*engine);
    REcmaSharedPointerObject::initEcma(*engine);
    REcmaDocumentVariables::initEcma(*engine);
    REcmaSharedPointerDocumentVariables::initEcma(*engine);
    REcmaEntity::initEcma(*engine);
    REcmaSharedPointerEntity::initEcma(*engine);
    REcmaLayer::initEcma(*engine);
    REcmaSharedPointerLayer::initEcma(*engine);
    REcmaLayerState::initEcma(*engine);
    REcmaSharedPointerLayerState::initEcma(*engine);
    REcmaLayout::initEcma(*engine);
    REcmaSharedPointerLayout::initEcma(*engine);
    REcmaBlock::initEcma(*engine);
    REcmaSharedPointerBlock::initEcma(*engine);
    REcmaView::initEcma(*engine);
    REcmaSharedPointerView::initEcma(*engine);
    REcmaLinetype::initEcma(*engine);
    REcmaSharedPointerLinetype::initEcma(*engine);
    REcmaUcs::initEcma(*engine);
    REcmaSharedPointerUcs::initEcma(*engine);

    REcmaEntityData::initEcma(*engine);

    REcmaBlockReferenceData::initEcma(*engine);
    REcmaBlockReferenceEntity::initEcma(*engine);
    REcmaSharedPointerBlockReferenceEntity::initEcma(*engine);

    REcmaPointData::initEcma(*engine);
    REcmaPointEntity::initEcma(*engine);
    REcmaSharedPointerPointEntity::initEcma(*engine);

    REcmaLineData::initEcma(*engine);
    REcmaLineEntity::initEcma(*engine);
    REcmaSharedPointerLineEntity::initEcma(*engine);

    REcmaXLineData::initEcma(*engine);
    REcmaXLineEntity::initEcma(*engine);
    REcmaSharedPointerXLineEntity::initEcma(*engine);

    REcmaRayData::initEcma(*engine);
    REcmaRayEntity::initEcma(*engine);
    REcmaSharedPointerRayEntity::initEcma(*engine);

    REcmaCircleData::initEcma(*engine);
    REcmaCircleEntity::initEcma(*engine);
    REcmaSharedPointerCircleEntity::initEcma(*engine);

    REcmaArcData::initEcma(*engine);
    REcmaArcEntity::initEcma(*engine);
    REcmaSharedPointerArcEntity::initEcma(*engine);

    REcmaEllipseData::initEcma(*engine);
    REcmaEllipseEntity::initEcma(*engine);
    REcmaSharedPointerEllipseEntity::initEcma(*engine);

    REcmaPolylineData::initEcma(*engine);
    REcmaPolylineEntity::initEcma(*engine);
    REcmaSharedPointerPolylineEntity::initEcma(*engine);

    REcmaSolidData::initEcma(*engine);
    REcmaSolidEntity::initEcma(*engine);
    REcmaSharedPointerSolidEntity::initEcma(*engine);

    REcmaTraceData::initEcma(*engine);
    REcmaTraceEntity::initEcma(*engine);
    REcmaSharedPointerTraceEntity::initEcma(*engine);

    REcmaFaceData::initEcma(*engine);
    REcmaFaceEntity::initEcma(*engine);
    REcmaSharedPointerFaceEntity::initEcma(*engine);

    REcmaViewportData::initEcma(*engine);
    REcmaViewportEntity::initEcma(*engine);
    REcmaSharedPointerViewportEntity::initEcma(*engine);

    REcmaSplineData::initEcma(*engine);
    REcmaSplineEntity::initEcma(*engine);
    REcmaSharedPointerSplineEntity::initEcma(*engine);

    REcmaTextBasedData::initEcma(*engine);
    REcmaTextBasedEntity::initEcma(*engine);
    REcmaSharedPointerTextBasedData::initEcma(*engine);
    REcmaSharedPointerTextBasedEntity::initEcma(*engine);

    REcmaTextData::initEcma(*engine);
    REcmaTextEntity::initEcma(*engine);
    REcmaSharedPointerTextData::initEcma(*engine);
    REcmaSharedPointerTextEntity::initEcma(*engine);

    REcmaAttributeDefinitionData::initEcma(*engine);
    REcmaAttributeDefinitionEntity::initEcma(*engine);
    REcmaSharedPointerAttributeDefinitionEntity::initEcma(*engine);

    REcmaAttributeData::initEcma(*engine);
    REcmaAttributeEntity::initEcma(*engine);
    REcmaSharedPointerAttributeEntity::initEcma(*engine);

    REcmaLeaderData::initEcma(*engine);
    REcmaLeaderEntity::initEcma(*engine);
    REcmaSharedPointerLeaderEntity::initEcma(*engine);

    REcmaHatchData::initEcma(*engine);
    REcmaHatchEntity::initEcma(*engine);
    REcmaSharedPointerHatchEntity::initEcma(*engine);

    REcmaImageData::initEcma(*engine);
    REcmaImageEntity::initEcma(*engine);
    REcmaSharedPointerImageEntity::initEcma(*engine);

    REcmaDimensionData::initEcma(*engine);
    REcmaDimensionEntity::initEcma(*engine);
    REcmaSharedPointerDimensionEntity::initEcma(*engine);

    REcmaDimLinearData::initEcma(*engine);
    REcmaDimLinearEntity::initEcma(*engine);
    REcmaSharedPointerDimLinearEntity::initEcma(*engine);

    REcmaDimAlignedData::initEcma(*engine);
    REcmaDimAlignedEntity::initEcma(*engine);
    REcmaSharedPointerDimAlignedEntity::initEcma(*engine);

    REcmaDimAngularData::initEcma(*engine);
    REcmaDimAngularEntity::initEcma(*engine);
    REcmaSharedPointerDimAngularEntity::initEcma(*engine);

    REcmaDimAngular2LData::initEcma(*engine);
    REcmaDimAngular2LEntity::initEcma(*engine);
    REcmaSharedPointerDimAngular2LEntity::initEcma(*engine);

    REcmaDimAngular3PData::initEcma(*engine);
    REcmaDimAngular3PEntity::initEcma(*engine);
    REcmaSharedPointerDimAngular3PEntity::initEcma(*engine);

    REcmaDimArcLengthData::initEcma(*engine);
    REcmaDimArcLengthEntity::initEcma(*engine);
    REcmaSharedPointerDimArcLengthEntity::initEcma(*engine);

    REcmaDimDiametricData::initEcma(*engine);
    REcmaDimDiametricEntity::initEcma(*engine);
    REcmaSharedPointerDimDiametricEntity::initEcma(*engine);

    REcmaDimRadialData::initEcma(*engine);
    REcmaDimRadialEntity::initEcma(*engine);
    REcmaSharedPointerDimRadialEntity::initEcma(*engine);

    REcmaDimRotatedData::initEcma(*engine);
    REcmaDimRotatedEntity::initEcma(*engine);
    REcmaSharedPointerDimRotatedEntity::initEcma(*engine);

    REcmaDimOrdinateData::initEcma(*engine);
    REcmaDimOrdinateEntity::initEcma(*engine);
    REcmaSharedPointerDimOrdinateEntity::initEcma(*engine);

    REcmaToleranceData::initEcma(*engine);
    REcmaToleranceEntity::initEcma(*engine);
    REcmaSharedPointerToleranceEntity::initEcma(*engine);

    REcmaTransaction::initEcma(*engine);

    REcmaFileImporter::initEcma(*engine);
    REcmaFileImporterAdapter::initEcma(*engine);
    REcmaFileImporterFactory::initEcma(*engine);
    REcmaFileImporterFactoryAdapter::initEcma(*engine);
    REcmaFileImporterRegistry::initEcma(*engine);

    REcmaFileExporter::initEcma(*engine);
    REcmaFileExporterAdapter::initEcma(*engine);
    REcmaFileExporterFactory::initEcma(*engine);
    REcmaFileExporterFactoryAdapter::initEcma(*engine);
    REcmaFileExporterRegistry::initEcma(*engine);

    REcmaOperation::initEcma(*engine);

    REcmaAddObjectsOperation::initEcma(*engine);
    REcmaClipboardOperation::initEcma(*engine);
    REcmaDeleteObjectsOperation::initEcma(*engine);

    REcmaAddObjectOperation::initEcma(*engine);
    REcmaChangePropertyOperation::initEcma(*engine);
    REcmaCopyOperation::initEcma(*engine);
    REcmaDeleteAllEntitiesOperation::initEcma(*engine);
    REcmaDeleteObjectOperation::initEcma(*engine);
    REcmaDeleteSelectionOperation::initEcma(*engine);
    REcmaMixedOperation::initEcma(*engine);
    REcmaModifyObjectOperation::initEcma(*engine);
    REcmaModifyObjectsOperation::initEcma(*engine);
    REcmaMoveReferencePointOperation::initEcma(*engine);
    REcmaMoveSelectionOperation::initEcma(*engine);
    REcmaScaleSelectionOperation::initEcma(*engine);
    REcmaPasteOperation::initEcma(*engine);
    REcmaClickReferencePointOperation::initEcma(*engine);
    REcmaOperationUtils::initEcma(*engine);

    REcmaTransformation::initEcma(*engine);

    REcmaTranslation::initEcma(*engine);

    REcmaTransform::initEcma(*engine);
    REcmaTransformOp::initEcma(*engine);

    REcmaCommandLine::initEcma(*engine);
    REcmaTextEdit::initEcma(*engine);
    REcmaMathLineEdit::initEcma(*engine);
    REcmaMathComboBox::initEcma(*engine);
    REcmaCharacterWidget::initEcma(*engine);
    REcmaDockWidget::initEcma(*engine);
    REcmaToolButton::initEcma(*engine);

    REcmaPropertyListener::initEcma(*engine);
    REcmaPropertyEditor::initEcma(*engine);

    REcmaToolMatrixItemDelegate::initEcma(*engine);
    REcmaFlowLayout::initEcma(*engine);
    REcmaListWidget::initEcma(*engine);
    REcmaTreeWidget::initEcma(*engine);
    REcmaListView::initEcma(*engine);
    REcmaLayerListener::initEcma(*engine);
    REcmaLayerListenerAdapter::initEcma(*engine);
    REcmaBlockListener::initEcma(*engine);
    REcmaBlockListenerAdapter::initEcma(*engine);
    REcmaViewListener::initEcma(*engine);
    REcmaViewListenerAdapter::initEcma(*engine);
    REcmaPenListener::initEcma(*engine);
    REcmaPenListenerAdapter::initEcma(*engine);
    REcmaPaletteListener::initEcma(*engine);
    REcmaPaletteListenerAdapter::initEcma(*engine);
    REcmaColorCombo::initEcma(*engine);
    REcmaLineweightCombo::initEcma(*engine);
    REcmaLinetypeCombo::initEcma(*engine);
    REcmaFontChooserWidget::initEcma(*engine);
    REcmaFontDatabase::initEcma(*engine);

    REcmaPluginLoader::initEcma(*engine);
    REcmaPluginInfo::initEcma(*engine);
    REcmaPluginInterface::initEcma(*engine);

    REcmaFontList::initEcma(*engine);

    REcmaPropertyEvent::initEcma(*engine);

    REcmaPropertyChange::initEcma(*engine);
    REcmaPropertyAttributes::initEcma(*engine);

    REcmaFileSystemModel::initEcma(*engine);

    REcmaTextLayout::initEcma(*engine);

//#if QT_VERSION < 0x050600
//#  if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
//    REcmaWebView::initEcma(*engine);
//#  endif
//#endif

    REcmaKeyListener::initEcma(*engine);
    REcmaKeyListenerAdapter::initEcma(*engine);

    REcmaFocusListener::initEcma(*engine);
    REcmaFocusListenerAdapter::initEcma(*engine);
    REcmaViewFocusListener::initEcma(*engine);
    REcmaViewFocusListenerAdapter::initEcma(*engine);

    REcmaPreferencesListener::initEcma(*engine);
    REcmaPreferencesListenerAdapter::initEcma(*engine);

    REcmaTextRenderer::initEcma(*engine);

    REcmaDxfServices::initEcma(*engine);

    REcmaAutoLoadEcma::initEcma(*engine);


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
        REcmaHelper::printStackTrace(engine->currentContext());
    }

    if (engine->isEvaluating()) {
        qWarning() << "Deleting script engine that is still evaluating.";
    }
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

    if (isIncluded(engine, fi.completeBaseName())) {
        return;
    }

    QScriptValue globalObject = engine->globalObject();
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

    eval(contents, scriptFile);

    markIncluded(engine, fi.completeBaseName());
}

QVariant RScriptHandlerEcma::eval(const QString& script, const QString& fileName) {
    QScriptValue err = engine->evaluate(script, fileName);
    if (engine->hasUncaughtException()) {
        qWarning()
                << "RScriptHandlerEcma::eval: script engine exception: "
                << err.toString();
        qWarning() << engine->uncaughtExceptionBacktrace().join("\n");
    }
    return err.toVariant();
}

QVariant RScriptHandlerEcma::evalGlobal(const QString& script, const QString& fileName) {
    QScriptContext* context = engine->currentContext();
    context->setActivationObject(engine->globalObject());
    context->setThisObject(engine->globalObject());

    QScriptValue err = engine->evaluate(script, fileName);
    return err.toVariant();
}

RFileImporterAdapter* RScriptHandlerEcma::createFileImporter(const QString& className, RDocument& document) {
    QScriptValue globalObject = engine->globalObject();

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

//    QFile f(fileName);
//    if (!f.open(QIODevice::ReadOnly)) {
//        qWarning() << "RScriptHandlerEcma::readScript: cannot read file: " << fileName;
//        return QString();
//    }

//    QString ret = f.readAll();
//    f.close();
//    return ret;
}

void RScriptHandlerEcma::createActionDocumentLevel(const QString& scriptFile,
        RGuiAction* guiAction, RDocumentInterface* documentInterface) {

    if (engine->isEvaluating()) {
//        qWarning() << "RScriptHandlerEcma::createActionDocumentLevel(): "
//                   << scriptFile
//                   << ": Engine is busy. Aborting...";
        if (guiAction==NULL || !guiAction->getAllowInterrupt()) {
            return;
        }
    }

    if (guiAction==NULL) {
        qWarning() << "RScriptHandlerEcma::createActionDocumentLevel(): "
                   << "guiAction is NULL";
    }

//    if (documentInterface == NULL && guiAction!=NULL) {
//        documentInterface = guiAction->getDocumentInterface();
//    }
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
        qWarning() << "RScriptHandlerEcma::createActionDocumentLevel(): "
                   << scriptFile
                   << ": file not found.";
        getScriptEngine().currentContext()->throwError(QString(
                "File %1 does not exists.").arg(scriptFile));
        return;
    }

    engine->collectGarbage();

    doScript(scriptFile);

    QString className = QFileInfo(scriptFile).completeBaseName();
    QScriptValue globalObject = getScriptEngine().globalObject();

    globalObject.setProperty("guiAction", engine->toScriptValue(guiAction));
    globalObject.setProperty("documentInterface", engine->toScriptValue(documentInterface));

    eval("documentInterface.setCurrentAction(new " + className + "(guiAction));");

    /*
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
    */
}

void RScriptHandlerEcma::createActionApplicationLevel(
        const QString& scriptFile, RGuiAction* guiAction) {

    if (!QFileInfo(scriptFile).exists()) {
        engine->currentContext()->throwError(QString(
                "File %1 does not exists.").arg(scriptFile));
        return;
    }

    engine->currentContext()->setActivationObject(engine->globalObject());

    doScript(scriptFile);

    QString className = QFileInfo(scriptFile).completeBaseName();
    QScriptValue globalObject = engine->globalObject();

    globalObject.setProperty("guiAction", engine->toScriptValue(guiAction));
    eval("var __a__ = new " + className + "(guiAction);"
         "if (typeof(__a__.beginEvent)===\"function\") __a__.beginEvent();"
         "if (typeof(__a__.finishEvent)===\"function\") __a__.finishEvent();"
         "if (typeof(__a__.destroy)===\"function\") __a__.destroy();");
         //"if (!isNull(guiAction) && guiAction.hasNoState()) a.destroy();");

    /*
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
    */
}

/**
 * Initializes some global ECMA variables that are available to all scripts.
 */
void RScriptHandlerEcma::initGlobalVariables(const QString& scriptFile) {
    // initialize global ECMA variables:
    QScriptValue globalObject = engine->globalObject();
    globalObject.setProperty("scriptFile", QScriptValue(engine, scriptFile));
    globalObject.setProperty("includeBasePath", QScriptValue(engine,
            QFileInfo(scriptFile).absolutePath()));
    globalObject.setProperty("scriptFileBasePath", QScriptValue(engine,
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
    if (alwaysLoadScripts && className!="library" && className!="EAction" && className!="WidgetFactory") {
        // always include (again) to reload potential changes:
        return false;
    }

    QVariant vAlreadyIncluded;

    vAlreadyIncluded = engine->property("alreadyIncluded");
    if (!vAlreadyIncluded.isValid()) {
        return false;
    }

    QSet<QString> alreadyIncluded;
    alreadyIncluded = vAlreadyIncluded.value<QSet<QString> >();
    if (!alreadyIncluded.contains(className)) {
        return false;
    }

    return true;
}

void RScriptHandlerEcma::markIncluded(QScriptEngine* engine, const QString& className) {
    QVariant vAlreadyIncluded;
    QSet<QString> alreadyIncluded;

    vAlreadyIncluded = engine->property("alreadyIncluded");
    if (vAlreadyIncluded.isValid()) {
        alreadyIncluded = vAlreadyIncluded.value<QSet<QString> >();
    }

    if (alreadyIncluded.contains(className)) {
        return;
    }

    alreadyIncluded.insert(className);
    vAlreadyIncluded.setValue(alreadyIncluded);
    engine->setProperty("alreadyIncluded", vAlreadyIncluded);
}

QScriptValue RScriptHandlerEcma::doInclude(QScriptEngine* engine, const QString& arg, QString trContext, bool force) {
    static int including = 0;

    QScriptContext* context = engine->currentContext();

    QString className = QFileInfo(arg).completeBaseName();

    if (!force && isIncluded(engine, className)) {
        return engine->undefinedValue();
    }

    QStringList list;

    // Search based on the includeBasePath which changes depending on the plugin
    list << engine->globalObject().property("includeBasePath").toString();

    // ... then search based on the initial script path (does not change)
    list << engine->globalObject().property("scriptFileBasePath").toString();

    // ... then search based on the local data storage location path (does not change)
    list << RSettings::getDataLocation();

    // ... then search based on the program path (does not change)
    list << QDir::currentPath();

    // ... then search based on the built in plugin values (does not change)
    list << ":";

    // Remove the duplicates and preserve the order
    list.removeDuplicates();

    QStringListIterator i(list);
    while (i.hasNext()) {
        QString basePath = i.next();

        QString fileName;
        QFileInfo fi(arg);
        if (fi.isAbsolute()) {
            fileName = arg;
        } else {
            if (basePath==":") {
                fileName = basePath + arg;
            }
            else {
                if (basePath.startsWith(":")) {
                    // workaround for Qt 4.7.4 bug with resource paths 
                    // containing both \ and /:
                    fileName = basePath + "/" + arg;
                }
                else {
                    fileName = basePath + QDir::separator() + arg;
                }
            }
            fi = QFileInfo(fileName);
        }

        if (!fi.exists()) {
            continue;
        }

        QString contents = readScript(fileName, force);

        if (trContext.isNull()) {
            trContext = fi.completeBaseName();
        }

        // post-processing for translation context:
#if QT_VERSION >= 0x050000
        contents.replace("qsTr(\"", QString("qsTranslate('%1', \"").arg(trContext));
#else
        // workaround for Qt 4 API / see library.js:
        contents.replace("qsTr(\"", QString("qsTranslate2('%1', \"").arg(trContext));
#endif
        contents.replace("QT_TR_NOOP(\"", QString("QT_TRANSLATE_NOOP('%1', \"").arg(trContext));

        QString includeBasePath = engine->globalObject().property("includeBasePath").toString();

        engine->globalObject().setProperty("includeBasePath", fi.absolutePath());
        context->setActivationObject(engine->globalObject());
        context->setThisObject(engine->globalObject());
        including++;
        engine->globalObject().setProperty("including", true);
        QScriptValue ret = engine->evaluate(contents, fileName);
        including--;
        engine->globalObject().setProperty("including", including!=0);

        engine->globalObject().setProperty("includeBasePath", includeBasePath);

        markIncluded(engine, className);

        return ret;
    }

    return context->throwError(QString("include: cannot read file '%1'").arg(
                                   context->argument(0).toString()));
}

QScriptValue RScriptHandlerEcma::ecmaEvalAppEngine(QScriptContext* context, QScriptEngine* engine) {
    QString arg;
    if (context->argumentCount() == 1 && context->argument(0).isString()) {
        arg = context->argument(0).toString();

        RScriptHandler* sh = RScriptHandlerRegistry::getGlobalScriptHandler("js");
        if (sh) {
            sh->eval(arg);
        }
        else {
            qWarning() << "no script handler found for JS";
        }
    }
    else {
        return context->throwError(QString("evalAppEngine: wrong number / type of arguments"));
    }
}

QScriptValue RScriptHandlerEcma::ecmaEvalDocEngine(QScriptContext* context, QScriptEngine* engine) {
    QString arg;
    if (context->argumentCount() == 1 && context->argument(0).isString()) {
        arg = context->argument(0).toString();

        RMainWindowQt* appWin = RMainWindowQt::getMainWindow();
        if (appWin) {
            RDocumentInterface* di = appWin->getDocumentInterface();
            if (di) {
                RScriptHandler* sh = di->getScriptHandler("js");
                if (sh) {
                    sh->eval(arg);
                }
                else {
                    qWarning() << "no script handler found for JS";
                }
            }
            else {
                qWarning() << "no document interface";
            }
        }
        else {
            qWarning() << "no app win";
        }
    }
    else {
        return context->throwError(QString("evalDocEngine: wrong number / type of arguments"));
    }
}

QScriptValue RScriptHandlerEcma::ecmaExit(QScriptContext* context, QScriptEngine* engine) {
    qWarning() << "Exit called from script. Closing application.";

    if (context->argumentCount() == 0) {
        // doesn't do anything:
        //QCoreApplication::exit();
        exit(0);
    }
    if (context->argumentCount() == 1) {
        int ret = context->argument(0).toUInt32();
        // doesn't do anything:
        //QCoreApplication::exit(ret);
        exit(ret);
    } else {
        return throwError(
                "Wrong number/types of arguments for exit().",
                context);
    }
    return engine->undefinedValue();
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
#if QT_VERSION >= 0x050000
        cppResult = context->argument(0).toString().toHtmlEscaped();
#else
        cppResult = Qt::escape(context->argument(0).toString());
#endif
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

QScriptValue RScriptHandlerEcma::ecmaQTextCharFormatSetFontFamilies(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue result = engine->undefinedValue();
    QTextCharFormat* self = qscriptvalue_cast<QTextCharFormat*> (context->thisObject());
    if (self == NULL) {
        return throwError("QTextCharFormat.setFontFamilies(): This object is not a QTextCharFormat", context);
    }

    if (context->argumentCount() == 1 && context->argument(0).isArray()) {
        QStringList v;
        REcmaHelper::fromScriptValue(engine, context->argument(0), v);

#if QT_VERSION >= 0x050D00
        self->setFontFamilies(v);
#else
        self->setFontFamily(v[0]);
#endif
    }

    return result;
}

QScriptValue RScriptHandlerEcma::ecmaQPrinterSetPdfVersion(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue result = engine->undefinedValue();
    QPrinter* self = qscriptvalue_cast<QPrinter*> (context->thisObject());

    if (context->argumentCount() == 1 && context->argument(0).isNumber()) {
        int v = context->argument(0).toInt32();
#if QT_VERSION >= 0x050A00
        // only Qt >= 5.10:
        self->setPdfVersion((QPagedPaintDevice::PdfVersion)v);
#else
        qWarning() << "Setting the PDF version is not supported in this Qt version";
#endif
    }

    return result;
}

QScriptValue RScriptHandlerEcma::ecmaGetAvailablePrinterNames(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue result = engine->undefinedValue();
#if QT_VERSION >= 0x050000
    QStringList cppResult = QPrinterInfo::availablePrinterNames();
#else
    QList<QPrinterInfo> printerInfos = QPrinterInfo::availablePrinters();
    QStringList cppResult;
    for (int i=0; i<printerInfos.length(); i++) {
        cppResult.append(printerInfos.at(i).printerName());
    }
#endif
    result = qScriptValueFromValue(engine, cppResult);
    return result;
}

QScriptValue RScriptHandlerEcma::ecmaGetDefaultPrinterName(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue result = engine->undefinedValue();
#if QT_VERSION >= 0x050000
    QString cppResult = QPrinterInfo::defaultPrinterName();
#else
    QPrinterInfo defaultPrinter = QPrinterInfo::defaultPrinter();
    QString cppResult = defaultPrinter.printerName();
#endif
    result = qScriptValueFromValue(engine, cppResult);
    return result;
}

QScriptValue RScriptHandlerEcma::ecmaCreatePrinter(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue result = engine->undefinedValue();
    if (context->argumentCount() == 1 && context->argument(0).isString()) {
        QString name = context->argument(0).toString();
#if QT_VERSION >= 0x050000
        QPrinterInfo pi = QPrinterInfo::printerInfo(name);
#else
        QPrinterInfo pi;
        QList<QPrinterInfo> printerInfos = QPrinterInfo::availablePrinters();
        for (int i=0; i<printerInfos.length(); i++) {
            if (printerInfos.at(i).printerName().toLower()==name.toLower()) {
                pi = printerInfos.at(i);
                break;
            }
        }
#endif
        if (pi.isNull()) {
            return result;
        }
        QPrinter* cppResult = new QPrinter(pi, QPrinter::HighResolution);
        result = qScriptValueFromValue(engine, cppResult);
    } else {
        return throwError(
                "Wrong number/types of arguments for createPrinter(name).",
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
        for (int i=0; i<objList.size(); i++) {
            QString typeName = objList.at(i)->metaObject()->className();
            if (typeName=="QFormInternal::TranslationWatcher") {
                continue;
            }
            if (typeName=="QWebView") {
                continue;
            }
            cppResult.append(objList.at(i));
        }
        result = REcmaHelper::listToScriptValue(engine, cppResult);
    } else {
        return throwError(
                "Wrong number/types of arguments for QObject.getChildren().",
                context);
    }

    return result;
}

QScriptValue RScriptHandlerEcma::ecmaBacktrace(QScriptContext* context, QScriptEngine* engine) {
    REcmaHelper::printStackTrace(context);
    return engine->undefinedValue();
}

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
        //QUrl* url = qscriptvalue_cast<QUrl*> (context->argument(0));
        QList<QPair<QString, QString> > cppResult = self->queryItems();
        result = REcmaHelper::pairListToScriptValue<QString, QString>(engine, cppResult);
    } else {
        return throwError(
                    "Wrong number/types of arguments for QUrl.queryItems().",
                    context);
    }
    return result;
}

QScriptValue RScriptHandlerEcma::ecmaQLocaleScript(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue result = engine->undefinedValue();
    QLocale* self = qscriptvalue_cast<QLocale*> (context->thisObject());
    if (self == NULL) {
        return throwError("QLocale.script(): This object is not a QLocale", context);
    }

    if (context->argumentCount() == 0) {
#if QT_VERSION >= 0x040800
        QLocale::Script cppResult = self->script();
        return qScriptValueFromValue(engine, (int)cppResult);
#else
        return qScriptValueFromValue(engine, -1);
#endif
    } else {
        return throwError(
                "Wrong number/types of arguments for QLocale.script().",
                context);
    }
    return result;
}

QScriptValue RScriptHandlerEcma::ecmaQLocaleScriptToString(QScriptContext* context, QScriptEngine* engine) {
    QScriptValue result = engine->undefinedValue();

    if (context->argumentCount() == 1) {
#if QT_VERSION >= 0x040800
        QLocale::Script script = qscriptvalue_cast<QLocale::Script> (context->argument(0));
        QString cppResult = QLocale::scriptToString(script);
        return qScriptValueFromValue(engine, cppResult);
#else
        return qScriptValueFromValue(engine, QString("No information available (Qt < 4.8)"));
#endif
    } else {
        return throwError(
                    "Wrong number/types of arguments for QLocale.scriptToString().",
                    context);
    }
    return result;
}

QScriptValue RScriptHandlerEcma::ecmaQLineEditValidator(QScriptContext* context, QScriptEngine* engine) {
    qDebug() << "RScriptHandlerEcma::ecmaQLineEditValidator";

    QLineEdit* self = REcmaHelper::scriptValueTo<QLineEdit>(context->thisObject());
    if (self == NULL) {
        return throwError("QLineEdit.validator(): Object is NULL", context);
    }

    if (context->argumentCount() != 0) {
        return throwError("Wrong number/types of arguments for QLineEdit::validator.", context);
    }

    const QValidator* cppResult = self->validator();
    return qScriptValueFromValue(engine, cppResult);
    //return engine->newQObject();
}

QScriptValue RScriptHandlerEcma::ecmaQItemSelectionModelCountSelectedRows(QScriptContext* context, QScriptEngine* engine) {
    QItemSelectionModel* self = REcmaHelper::scriptValueTo<QItemSelectionModel>(context->thisObject());
    if (self == NULL) {
        return throwError("QItemSelectionModel.countSelectedRows(): Object is NULL", context);
    }

    if (context->argumentCount() != 0) {
        return throwError("Wrong number/types of arguments for QItemSelectionModel.countSelectedRows.", context);
    }

    int cppResult = self->selectedRows().length();
    return qScriptValueFromValue(engine, cppResult);
}

QScriptValue RScriptHandlerEcma::ecmaQItemSelectionModelSelectedRow(QScriptContext* context, QScriptEngine* engine) {
    QItemSelectionModel* self = REcmaHelper::scriptValueTo<QItemSelectionModel>(context->thisObject());
    if (self == NULL) {
        return throwError("QItemSelectionModel.selectedRow(): Object is NULL", context);
    }

    if (context->argumentCount() != 1) {
        return throwError("Wrong number/types of arguments for QItemSelectionModel.selectedRow.", context);
    }

    int idx = context->argument(0).toInteger();

    const QModelIndex cppResult = self->selectedRows().at(idx);
    return qScriptValueFromValue(engine, cppResult);
}

//QScriptValue RScriptHandlerEcma::ecmaQWebPageSetLinkDelegationPolicy(QScriptContext* context, QScriptEngine* engine) {
//    QWebPage* self = REcmaHelper::scriptValueTo<QWebPage>(context->thisObject());
//    if (self == NULL) {
//        return throwError("QWebPage.setLinkDelegationPolicy(): Object is NULL", context);
//    }

//    if (context->argumentCount() != 1) {
//        return throwError("Wrong number/types of arguments for QLineEdit::validator.", context);
//    }

//    QWebPage::LinkDelegationPolicy val = (QWebPage::LinkDelegationPolicy)context->argument(0).toInteger();
//    self->setLinkDelegationPolicy(val);

//    return engine->undefinedValue();
//}

QScriptValue RScriptHandlerEcma::ecmaMSleep(QScriptContext* context,
        QScriptEngine* engine) {

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

QScriptValue RScriptHandlerEcma::ecmaParseXml(QScriptContext* context, QScriptEngine* engine) {

    if (context->argumentCount() == 2 && context->argument(0).isString()) {
        QString fileName = context->argument(0).toString();
        QXmlContentHandler* handler = qscriptvalue_cast<QXmlContentHandler*>(context->argument(1));

        QFileInfo fi(fileName);
        QFile file(fi.absoluteFilePath());
        QXmlSimpleReader xmlReader;
        QXmlInputSource source(&file);
        xmlReader.setContentHandler(handler);
        bool ret = xmlReader.parse(&source, false);
        file.close();
        return qScriptValueFromValue(engine, ret);
    } else {
        return throwError("Wrong number/types of arguments for parseXml().", context);
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

QScriptValue RScriptHandlerEcma::ecmaDownloadToFile(QScriptContext* context, QScriptEngine* engine) {

    if (context->argumentCount() == 4 &&
        context->argument(0).isString() &&
        context->argument(1).isString() &&
        context->argument(2).isString() &&
        context->argument(3).isNumber()) {

        QString url = context->argument(0).toString();
        QString path = context->argument(1).toString();
        QString fileName = context->argument(2).toString();
        int timeout = context->argument(3).toInteger();

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
            qWarning() << "Cannot download " << url << ": "<< reply->errorString();
            delete reply;
            return qScriptValueFromValue(engine, false);
        }

        if (fileName.isEmpty()) {
            fileName = QFileInfo(QUrl(url).path()).fileName();
        }

        fileName = path + QDir::separator() + fileName;
        QDir dir;
        if (!dir.mkpath(path)) {
            qWarning() << "Cannot create dir " << path;
            delete reply;
            return qScriptValueFromValue(engine, false);
        }
        if (QFileInfo(fileName).exists() && !QFile(fileName).remove()) {
            qWarning() << "Cannot remove file " << fileName;
            delete reply;
            return qScriptValueFromValue(engine, false);
        }

        QByteArray contents = reply->readAll();
        if (contents.isEmpty()) {
            qWarning() << "URL does not exist " << url;
            delete reply;
            return qScriptValueFromValue(engine, false);
        }

        QFile f(fileName);
        if (!f.open(QIODevice::WriteOnly)) {
            qWarning() << "Cannot write output file " << f.fileName();
            delete reply;
            return qScriptValueFromValue(engine, false);
        }
        f.write(contents);
        f.close();

        delete reply;
        return qScriptValueFromValue(engine, true);
    } else {
        return throwError(
                    "Wrong number/types of arguments for downloadToFile().",
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

QScriptValue RScriptHandlerEcma::ecmaQEventCast(QScriptContext* context, QScriptEngine* engine) {

    QEvent* self = REcmaHelper::scriptValueTo<QEvent>(context->thisObject());
    if (self == NULL) {
        return throwError("QEvent.cast: Object is NULL", context);
    }

    if (context->argumentCount() != 0) {
        return throwError("Wrong number/types of arguments for QEvent.cast.", context);
    }

    {
        QMouseEvent* e = dynamic_cast<QMouseEvent*>(self);
        if (e!=NULL) {
            return qScriptValueFromValue(engine, e);
        }
    }
    {
        QKeyEvent* e = dynamic_cast<QKeyEvent*>(self);
        if (e!=NULL) {
            return qScriptValueFromValue(engine, e);
        }
    }
    {
        QShortcutEvent* e = dynamic_cast<QShortcutEvent*>(self);
        if (e!=NULL) {
            return qScriptValueFromValue(engine, e);
        }
    }

    return context->thisObject();
}

QScriptValue RScriptHandlerEcma::ecmaQFileClose(QScriptContext* context, QScriptEngine* engine) {
    //QFile* self = REcmaHelper::scriptValueTo<QFile>(context->thisObject());
    QFile* self = qscriptvalue_cast<QFile*>(context->thisObject());
    if (self == NULL) {
        return throwError("QFile.close: Object is NULL", context);
    }

    if (context->argumentCount() != 0) {
        return throwError("Wrong number/types of arguments for QFile.close.", context);
    }

    self->close();

    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaQFileReadAll(QScriptContext* context, QScriptEngine* engine) {
    QFile* self = qscriptvalue_cast<QFile*>(context->thisObject());
    if (self == NULL) {
        return throwError("QFile.readAll: Object is NULL", context);
    }

    if (context->argumentCount() != 0) {
        return throwError("Wrong number/types of arguments for QFile.readAll.", context);
    }

    QByteArray ret = self->readAll();

    return qScriptValueFromValue(engine, ret);
}

QScriptValue RScriptHandlerEcma::ecmaQFileFileName(QScriptContext* context, QScriptEngine* engine) {
    QFile* self = qscriptvalue_cast<QFile*>(context->thisObject());
    if (self == NULL) {
        return throwError("QFile.fileName: Object is NULL", context);
    }

    if (context->argumentCount() != 0) {
        return throwError("Wrong number/types of arguments for QFile.fileName.", context);
    }

    QString ret = self->fileName();

    return qScriptValueFromValue(engine, ret);
}

QScriptValue RScriptHandlerEcma::ecmaQFileWrite(QScriptContext* context, QScriptEngine* engine) {
    QFile* self = qscriptvalue_cast<QFile*>(context->thisObject());
    if (self == NULL) {
        return throwError("QFile.write: Object is NULL", context);
    }

    if (context->argumentCount() != 1) {
        return throwError("Wrong number/types of arguments for QFile.fileName.", context);
    }

    QByteArray* ap0 = qscriptvalue_cast<QByteArray*>(context->argument(0));
    qint64 ret = self->write(*ap0);

    return qScriptValueFromValue(engine, ret);
}

QScriptValue RScriptHandlerEcma::ecmaQImagePixelColor(QScriptContext* context, QScriptEngine* engine) {
    QImage* self = qscriptvalue_cast<QImage*>(context->thisObject());
    if (self == NULL) {
        return throwError("QImage.pixelColor: Object is NULL", context);
    }

    if (context->argumentCount() != 2) {
        return throwError("Wrong number/types of arguments for QImage.pixelColor.", context);
    }

    int a0 = qscriptvalue_cast<int>(context->argument(0));
    int a1 = qscriptvalue_cast<int>(context->argument(1));
#if QT_VERSION >= 0x050600
    QColor ret = self->pixelColor(a0, a1);
#else
    // TODO:
    QColor ret = QColor("white");
    Q_ASSERT(false);
#endif

    return qScriptValueFromValue(engine, ret);
}

QScriptValue RScriptHandlerEcma::ecmaQImageSetPixelColor(QScriptContext* context, QScriptEngine* engine) {
    QImage* self = qscriptvalue_cast<QImage*>(context->thisObject());
    if (self == NULL) {
        return throwError("QImage.setPixelColor: Object is NULL", context);
    }

    if (context->argumentCount() != 3) {
        return throwError("Wrong number/types of arguments for QImage.setPixelColor.", context);
    }

    int a0 = qscriptvalue_cast<int>(context->argument(0));
    int a1 = qscriptvalue_cast<int>(context->argument(1));
    QColor a2 = qscriptvalue_cast<QColor>(context->argument(2));
#if QT_VERSION >= 0x050600
    self->setPixelColor(a0, a1, a2);
#else
    // TODO:
    Q_ASSERT(false);
#endif

    return engine->undefinedValue();
}

QScriptValue RScriptHandlerEcma::ecmaQImageSetColorTable(QScriptContext *context, QScriptEngine *engine) {
    QImage* self = qscriptvalue_cast<QImage*>(context->thisObject());
    if (self == NULL) {
        return throwError("QImage.setColorTable: Object is NULL", context);
    }

    if (context->argumentCount() != 1) {
        return throwError("Wrong number/types of arguments for QImage.setColorTable.", context);
    }

    QVector<QRgb> a0;
    REcmaHelper::fromScriptValue(engine, context->argument(0), a0);
    //int a1 = qscriptvalue_cast<int>(context->argument(1));
    //QColor a2 = qscriptvalue_cast<QColor>(context->argument(2));
    self->setColorTable(a0);

    return engine->undefinedValue();
}

//QScriptValue RScriptHandlerEcma::ecmaBlockEvents(QScriptContext* context,
//        QScriptEngine* engine) {
//    Q_UNUSED(context)
//    Q_UNUSED(engine)

//    QAbstractEventDispatcher* evtDisp = QAbstractEventDispatcher::instance();
//    defaultEventFilter = evtDisp->setEventFilter(RScriptHandlerEcma::eventFilter);
//    return QScriptValue();
//}

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
    QStringList stack = engine->uncaughtExceptionBacktrace();
    qWarning() << stack.join("\n");
}
