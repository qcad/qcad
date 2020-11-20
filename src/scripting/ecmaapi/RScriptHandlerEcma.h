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

#ifndef RSCRIPTHANDLERECMA_H
#define RSCRIPTHANDLERECMA_H

#include "ecmaapi_global.h"

#include <QString>
#include <QtScript>
#include <QMainWindow>

#include "RScriptHandler.h"
#include "RDocumentInterface.h"
#include "RGuiAction.h"
#include "REcmaFocusListenerAdapter.h"

class QScriptEngineDebugger;


/**
 * Script handler implementation for ECMA scripts, based on Qt Script.
 *
 * \ingroup ecma
 */
class QCADECMAAPI_EXPORT RScriptHandlerEcma: public QObject, public RScriptHandler {
Q_OBJECT

public:
    RScriptHandlerEcma();
    virtual ~RScriptHandlerEcma();

    static RScriptHandler* factory();

    static QList<QString> getSupportedFileExtensionsStatic();
    QList<QString> getSupportedFileExtensions();

    virtual void doScript(const QString& scriptFile,const QStringList& arguments = QStringList());
    virtual QVariant eval(const QString& script, const QString& fileName = QString());
    virtual QVariant evalGlobal(const QString& script, const QString& fileName = QString());
    virtual RFileImporterAdapter* createFileImporter(const QString& className, RDocument& document);

    virtual bool isRunning();
    virtual void abort();
    virtual bool hasUncaughtExceptions();

    virtual void createActionDocumentLevel(const QString& scriptFile,
            RGuiAction* guiAction, RDocumentInterface* documentInterface);
    virtual void createActionApplicationLevel(const QString& scriptFile,
            RGuiAction* guiAction);

    void initGlobalVariables(const QString& scriptFile);

    QScriptEngine& getScriptEngine() {
        return *engine;
    }

    static bool isIncluded(QScriptEngine* engine, const QString& className);
    static void markIncluded(QScriptEngine* engine, const QString& className);

    static QScriptValue ecmaInclude(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue doInclude(QScriptEngine* engine, const QString& fileName, QString trContext = QString(), bool force=false);

    static QScriptValue ecmaEvalAppEngine(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaEvalDocEngine(QScriptContext* context, QScriptEngine* engine);

    static QScriptValue ecmaExit(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaPrint(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaDebug(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaWarning(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaCritical(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaMessageHandler(QScriptContext* context, QScriptEngine* engine, RS::MessageType type);
    static QScriptValue ecmaGray(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQtEscape(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaDestroy(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQObjectFindChild(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQObjectGetChildren(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQDomNodeAppendChild(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQDomNodeRemoveChild(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQTextCharFormatSetFontFamilies(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQPrinterSetPdfVersion(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaGetAvailablePrinterNames(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaGetDefaultPrinterName(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaCreatePrinter(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaBacktrace(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaAttachDebugger(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaDetachDebugger(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaCollectGarbage(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQLayoutGetWidth(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQByteArrayToString(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue ecmaQUrlQueryItems(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue ecmaQLocaleScript(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQLocaleScriptToString(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQLineEditValidator(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQItemSelectionModelCountSelectedRows(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQItemSelectionModelSelectedRow(QScriptContext* context, QScriptEngine* engine);
    //static QScriptValue ecmaQWebPageSetLinkDelegationPolicy(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaMSleep(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaParseXml(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaArguments(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaGetObjectId(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaImportExtension(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue ecmaIsDeleted(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue ecmaSerialize(QScriptContext *context, QScriptEngine *engine);
    //static QScriptValue ecmaBlockEvents(QScriptContext* context, QScriptEngine* engine);
    //static QScriptValue ecmaUnblockEvents(QScriptContext* context, QScriptEngine* engine);
    //static QScriptValue ecmaGetOpt(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaAddApplicationFont(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaDownload(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaDownloadToFile(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQSortFilterProxyModelCastToQAbstractItemModel(QScriptContext* context, QScriptEngine* engine);
//    static QScriptValue ecmaQFontDatabaseFamilies(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQEventCast(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQFileClose(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQFileReadAll(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQFileFileName(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQFileWrite(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQImagePixelColor(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQImageSetPixelColor(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQImageSetColorTable(QScriptContext* context, QScriptEngine* engine);

    //static QScriptValue ecmaGetShapeIntersections(QScriptContext* context, QScriptEngine* engine);

    static bool eventFilter(void *message);

    static QScriptValue throwError(const QString& message, QScriptContext* context);

    template<class T>
    static QScriptValue ecmaObjectDestroy(QScriptContext* context, QScriptEngine* engine) {
        T* self = qscriptvalue_cast<T*> (context->thisObject());

        if (self == NULL) {
            return throwError("destroy(): Object is NULL", context);
        }
        delete self;
        self = NULL;

        context->thisObject().setData(engine->nullValue());
        context->thisObject().prototype().setData(engine->nullValue());
        context->thisObject().setPrototype(engine->nullValue());
        context->thisObject().setScriptClass(NULL);
        return engine->undefinedValue();
    }

public slots:
    void triggerActionApplicationLevel(const QString& scriptFile) {
        RScriptHandler::triggerActionApplicationLevel(scriptFile);
    }
    void installTranslatorFunctions() {
        if (engine == NULL) {
            qWarning("REcmaHandler::installTranslationFunctions: "
                "engine is NULL");
            return;
        }
        engine->installTranslatorFunctions();
    }
    void exceptionHandler(const QScriptValue& exception);

protected:
    static QString readScript(const QString& fileName, bool forceReload = false);

private:
    QScriptEngine* engine;
    QScriptEngineDebugger* debugger;

    static bool translatorInstalled;
    static bool alwaysLoadScripts;
    //static QAbstractEventDispatcher::EventFilter defaultEventFilter;
};

Q_DECLARE_METATYPE(RScriptHandlerEcma*)

#endif // RECMASCRIPTHANDLER_H
