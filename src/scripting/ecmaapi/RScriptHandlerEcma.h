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
 * \ingroup scripting_ecma
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
    virtual void eval(const QString& script, const QString& fileName = QString());
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

    static QScriptValue ecmaExit(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaPrint(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaDebug(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaWarning(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaCritical(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaMessageHandler(QScriptContext* context, QScriptEngine* engine, RS::MessageType type);
    static QScriptValue ecmaGray(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQtEscape(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaDestroy(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQPainterDestroy(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQPrinterDestroy(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQXmlResultItemsDestroy(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQXmlStreamWriterDestroy(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQObjectFindChild(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQObjectGetChildren(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQDomNodeAppendChild(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQDomNodeRemoveChild(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaAttachDebugger(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaDetachDebugger(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaCollectGarbage(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQLayoutGetWidth(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQByteArrayToString(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue ecmaQUrlQueryItems(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue ecmaMSleep(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaArguments(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaGetObjectId(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaImportExtension(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue ecmaIsDeleted(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue ecmaSerialize(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue ecmaBlockEvents(QScriptContext* context, QScriptEngine* engine);
    //static QScriptValue ecmaUnblockEvents(QScriptContext* context, QScriptEngine* engine);
    //static QScriptValue ecmaGetOpt(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaAddApplicationFont(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaDownload(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue ecmaQSortFilterProxyModelCastToQAbstractItemModel(QScriptContext* context, QScriptEngine* engine);
//    static QScriptValue ecmaQFontDatabaseFamilies(QScriptContext* context, QScriptEngine* engine);

    static bool eventFilter(void *message);

    static QScriptValue throwError(const QString& message, QScriptContext* context);

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
    static QAbstractEventDispatcher::EventFilter defaultEventFilter;
};

Q_DECLARE_METATYPE(RScriptHandlerEcma*)

#endif // RECMASCRIPTHANDLER_H
