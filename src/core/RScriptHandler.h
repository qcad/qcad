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

#ifndef RSCRIPTHANDLER_H
#define RSCRIPTHANDLER_H

#include "core_global.h"

#include <QList>
#include <QMetaType>
#include <QString>

#include "RNonCopyable.h"
#include "RDocumentInterface.h"
#include "RAction.h"
#include "RGuiAction.h"
#include "RScriptAction.h"
#include "RMainWindow.h"

class RFileImporterAdapter;

#ifndef RDEFAULT_QSTRING
#define RDEFAULT_QSTRING QString()
#endif

#ifndef RDEFAULT_QSTRINGLIST
#define RDEFAULT_QSTRINGLIST QStringList()
#endif


/**
 * Abstract base class for all script handlers.
 *
 * \scriptable
 * \ingroup core
 */
class QCADCORE_EXPORT RScriptHandler {

public:

    RScriptHandler() { }

    virtual ~RScriptHandler() { }

    /**
     * \return The file extensions of script files that are supported by
     *      this script handler.
     */
    virtual QList<QString> getSupportedFileExtensions() = 0;

    virtual void init(const QString& autostartFile = QString::null, const QStringList& arguments = RDEFAULT_QSTRINGLIST);

    /**
     * Runs the given script file.
     */
    virtual void doScript(const QString& scriptFile, const QStringList& arguments = RDEFAULT_QSTRINGLIST) = 0;

    /**
     * Evaluates the given script code.
     */
    virtual QVariant eval(const QString& script, const QString& fileName = RDEFAULT_QSTRING) = 0;

    /**
     * Evaluates the given script code in a global context.
     */
    virtual QVariant evalGlobal(const QString& script, const QString& fileName = RDEFAULT_QSTRING) = 0;

    /**
     * Creates a file importer from the given class name and for the given document.
     */
    virtual RFileImporterAdapter* createFileImporter(const QString& className, RDocument& document) = 0;

    /**
     * \return true if the script handle currently is running a script,
     *      false otherwise.
     */
    virtual bool isRunning() = 0;

    virtual void abort() = 0;

    virtual bool hasUncaughtExceptions() = 0;

    static void triggerActionApplicationLevel(const QString& scriptFile, RGuiAction* guiAction = NULL);

    /**
     * Creates a script based action for this script handler.
     */
    virtual void createActionDocumentLevel(const QString& scriptFile, RGuiAction* guiAction, RDocumentInterface* documentInterface = NULL) = 0;
    virtual void createActionApplicationLevel(const QString& scriptFile, RGuiAction* guiAction) = 0;

    /**
     * Creates a new document level action by instantiating class T and attaching the
     * action to the document interface of the currently active document.
     * Document level actions typically effect only the current document.
     * Document level actions stay active until they are explicitly finished.
     * \nonscriptable
     */
    template<class T>
    void createActionDocumentLevelT(const QString& scriptFile,
            RGuiAction* guiAction, RDocumentInterface* documentInterface) {
        if (documentInterface == NULL) {
            documentInterface = RMainWindow::getDocumentInterfaceStatic();
            if (documentInterface == NULL) {
                qWarning("RScriptHandler::createActionDocumentLevelT(): No document interface given or found.");
                return;
            }
        }

        RScriptAction* a = new T(scriptFile, guiAction);
        a->setDocumentInterface(documentInterface);
        documentInterface->setCurrentAction(a);
    }

    /**
     * Creates a new application level action by instantiating class T. Application level
     * actions typically do not effect any documents. Application level actions cannot
     * be attached to a document interface or anywhere else, so the action is instantiated,
     * \ref beginEvent is called and then the action is terminated immediately
     * (\ref finishEvent is called).
     * \nonscriptable
     */
    template<class T>
    void createActionApplicationLevelT(const QString& scriptFile, RGuiAction* guiAction) {
        T action(scriptFile, guiAction);
        action.beginEvent();
        action.finishEvent();
    }

protected:
    static QString autostartScriptName;
};

Q_DECLARE_METATYPE(RScriptHandler*)

#endif
