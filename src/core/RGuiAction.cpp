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
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QMenu>
#include <QToolBar>
#include <QVectorIterator>

#include "RDebug.h"
#include "RGuiAction.h"
#include "RScriptHandler.h"
#include "RSettings.h"
#include "RSingleApplication.h"



QMap<QString, RGuiAction*> RGuiAction::actionsByCommand;
QMap<QString, RGuiAction*> RGuiAction::actionsByPrimaryCommand;
QMap<QString, RGuiAction*> RGuiAction::actionsByScriptFile;
QMultiMap<QString, RGuiAction*> RGuiAction::actionsByGroup;
QList<RGuiAction*> RGuiAction::actions;




RGuiAction::RGuiAction(const QString& text, QObject* parent)
  : QAction(text, parent),
    factory(NULL),
    groupDefault(false),
    requiresDocument(true), 
    requiresSelection(false),
    requiresUndoableTransaction(false),
    requiresRedoableTransaction(false),
    override(false),
    noState(false),
    sortOrder(-1),
    iconDisabled(false),
    enabledOverride(-1),
    documentInterface(NULL) {
    
    initTexts();
    
    connect(this, SIGNAL(triggered()),
            this, SLOT(slotTrigger()));

    setCheckable(true);

    actions.push_back(this);
}



RGuiAction::~RGuiAction() {
    QList<QMap<QString, RGuiAction*>*> maps;
    maps << &actionsByCommand;
    maps << &actionsByPrimaryCommand;
    maps << &actionsByScriptFile;
    maps << &actionsByGroup;

    QListIterator<QMap<QString, RGuiAction*>*> vi(maps);
    while (vi.hasNext()) {
        QStringList keys;
        QMap<QString, RGuiAction*>* map = vi.next();
        QMapIterator<QString, RGuiAction*> i(*map);
        while (i.hasNext()) {
            i.next();
            if (i.value() == this) {
                keys << i.key();
            }
        }
        keys.removeDuplicates();
        QStringListIterator ki(keys);
        while (ki.hasNext()) {
            QString s = ki.next();
            map->remove(s);
        }
    }

    actions.removeAll(this);
}


void RGuiAction::setDocumentInterface(RDocumentInterface* di) {
    documentInterface = di;
}

RDocumentInterface* RGuiAction::getDocumentInterface() {
    return documentInterface;
}


void RGuiAction::initTexts() {
    QString textAndKeycode = text();
    QString textOnly = textAndKeycode;
    textOnly.replace('&', "");

#ifndef Q_OS_MACX
    // Override shortcut text (does not work for Mac OS X):
    if (!shortcutText.isEmpty()) {
        if (textAndKeycode.indexOf(QLatin1Char('\t'))!=-1) {
            textAndKeycode = textAndKeycode.left(textAndKeycode.indexOf('\t'));
        }
        textAndKeycode += QLatin1Char('\t');
        textAndKeycode += shortcutText;
    }
#endif

    setText(textAndKeycode);

    QString tip = toolTip;
    if (tip.isNull()) {
        tip = textOnly;
    }

    QString kcs = shortcutText.isEmpty() ? shortcut().toString() : shortcutText;
    if (!kcs.isEmpty()) {
        QAction::setToolTip(getToolTip(tip, kcs));
    }
    else {
        QAction::setToolTip(tip);
    }
}

QString RGuiAction::formatToolTip(const QString& text, const QString& shortcut) {
    QString sc = shortcut;

    sc.replace(", ", "");
#ifdef Q_OS_MACX
    // change order to standard order on mac:
    sc.replace("Ctrl+Shift+", "Shift+Ctrl+");
    sc.replace("Ctrl+", QString("%1").arg(QChar(0x2318)));
    sc.replace("Shift+", QString("%1").arg(QChar(0x21E7)));
#endif

    return QString("%1 <span style=\"color: gray; font-size: small\">%2</span>")
                .arg(text)
                .arg(sc);
}


QString RGuiAction::getToolTip(const QString& text, const QString& shortcut) {
    QString ret = formatToolTip(text, shortcut);

    // additional info for disabled tools:
    if (!isEnabled()) {
        if (requiresSelection) {
            ret += "<br>" + tr("Requires selection");
        }
    }

    return ret;
}

void RGuiAction::setShortcutText(const QString& text) {
    shortcutText = text;
    initTexts();
}

QString RGuiAction::getShortcutText() {
    return shortcutText;
}

void RGuiAction::setIcon(const QString& iconFile) {
    if (iconFile.isEmpty()) {
        QAction::setIcon(QIcon());
    }
    else {
        QAction::setIcon(QIcon(iconFile));
    }
}



void RGuiAction::disableIcon() {
    iconDisabled = true;
}

bool RGuiAction::isIconDisabled() {
    return iconDisabled;
}

void RGuiAction::setDefaultShortcuts(const QList<QKeySequence>& shortcuts) {
    defaultShortcuts = shortcuts;
    this->setShortcuts(shortcuts);
}

QList<QKeySequence> RGuiAction::getDefaultShortcuts() {
    return defaultShortcuts;
}

void RGuiAction::setDefaultShortcut(const QKeySequence& shortcut) {
    defaultShortcuts = QList<QKeySequence>() << shortcut;
    this->setShortcut(shortcut);
}

void RGuiAction::setShortcut(const QKeySequence& shortcut) {
    QAction::setShortcut(shortcut);
    initTexts();
}

void RGuiAction::setShortcuts(const QList<QKeySequence>& shortcuts) {
    QAction::setShortcuts(shortcuts);
    initTexts();
}

void RGuiAction::setToolTip(const QString& tip) {
    toolTip = tip;
    initTexts();
}

//void RGuiAction::setToolTip(const QString& tip) {
//    QAction::setToolTip(tip);
//    initTexts();
//}

void RGuiAction::setStatusTip(const QString& tip) {
    QAction::setStatusTip(tip);
    initTexts();
}

void RGuiAction::setEnabled(bool on) {
    if (on == false) {
        setChecked(false);
    }
    QAction::setEnabled(on);
}

/**
 * \param override -1: don't set override (default), 1: true, 0: false
 */
void RGuiAction::setEnabledOverride(bool on, int override) {
    // button is enabled / disabled for other reasons. leave untouched:
    if (override!=-1) {
        enabledOverride = override;
    }

    if (on == false) {
        setChecked(false);
    }

    QAction::setEnabled(on && enabledOverride!=0);
}

void RGuiAction::setChecked(bool on) {
    QAction::setChecked(on);
}

bool RGuiAction::isChecked() {
    return QAction::isChecked();
}

void RGuiAction::setSortOrder(int sortOrder) {
    this->sortOrder = sortOrder;
    this->setProperty("SortOrder", sortOrder);
    // for debugging: setToolTip(QString("[%1]").arg(sortOrder));
}

int RGuiAction::getSortOrder() {
    return sortOrder;
}

void RGuiAction::addToMenu(QMenu* menu) {
    if (menu==NULL) {
        qWarning("RGuiAction::addToMenu: menu is NULL");
        Q_ASSERT(false);
        return;
    }
    addToWidget(menu);
}

void RGuiAction::addToToolBar(QToolBar* tb) {
    if (tb==NULL) {
        qWarning("RGuiAction::addToMenu: tb is NULL");
        Q_ASSERT(false);
        return;
    }
    addToWidget(tb);
    QWidget* w = tb->widgetForAction(this);
    if (w != NULL) {
        w->setObjectName("ToolButton" + objectName());
    }
}

void RGuiAction::addToWidget(QWidget* w) {
    if (w==NULL) {
        qWarning("RGuiAction::addToWidget: widget is NULL");
        return;
    }

    QListIterator<QAction*> i(w->actions());
    while (i.hasNext()) {
        RGuiAction* a = dynamic_cast<RGuiAction*> (i.next());
        if (a == NULL) {
            continue;
        }
        if (getSortOrder() >= 0 && getSortOrder() < a->getSortOrder()) {
            w->insertAction(a, this);
            return;
        }
    }

    w->addAction(this);
}



void RGuiAction::updateTransactionListener(RDocument* document, RTransaction* transaction) {
    Q_UNUSED(transaction)

    bool enabled = true;

    if (requiresDocument && document==NULL) {
        enabled = false;
    }

    if (document != NULL) {
        if (requiresUndoableTransaction && !document->isUndoAvailable()) {
            enabled = false;
        }
        if (requiresRedoableTransaction && !document->isRedoAvailable()) {
            enabled = false;
        }
        if (requiresSelection && !document->hasSelection()) {
            enabled = false;
        }
    }

    setEnabledOverride(enabled, -1);
    initTexts();
}

void RGuiAction::updateSelectionListener(RDocumentInterface* documentInterface) {
    if (documentInterface == NULL) {
        return;
    }

    if (requiresSelection) {
        setEnabledOverride(documentInterface->getDocument().hasSelection(), -1);
        initTexts();
    }
}

void RGuiAction::updateFocus(RDocumentInterface* documentInterface) {
    if (documentInterface==NULL) {
        return;
    }
    if (group.isEmpty()) {
        return;
    }

    // re-activate active action in action group, e.g. snap function:
    if (isChecked()) {
        slotTrigger();
    }
}

void RGuiAction::setDefaultCommands(const QStringList& cmds) {
    setCommands(cmds);
    defaultCommandList = cmds;
}

/**
 * Sets the command(s) that can trigger this action from a command line.
 * 
 * \param cmd Comma separated list of command(s) to set for this action.  
 *      e.g. "mycommand", "mycommand,mycom,mc".
 */
void RGuiAction::setCommands(const QStringList& cmds) {
    // remove all previous commands for this action:
    QStringList keysToRemove;
    QMap<QString, RGuiAction*>::iterator it;
    for (it=actionsByCommand.begin(); it!=actionsByCommand.end(); ++it) {
        if (it.value()==this) {
            keysToRemove.append(it.key());
        }
    }

    for (int i=0; i<keysToRemove.count(); ++i) {
        actionsByCommand.remove(keysToRemove.at(i));
        actionsByPrimaryCommand.remove(keysToRemove.at(i));
    }

    //commandList = cmd.toLower().split(',');
    commandList = cmds;

    // update internal hash of action pointers:
    if (commandList.size()>0 && commandList.begin()->size()!=0) {
        QStringList::iterator it;
        for (it=commandList.begin(); it!=commandList.end(); ++it) {
            actionsByCommand[*it] = this;

            // first command or any command with length>2 will be included in tab-search:
            if (it==commandList.begin() || (*it).size()>2) {
                actionsByPrimaryCommand[*it] = this;
            }

            // upper case command is the main command for that action:
            if ((*it).size()>0 && (*it).at(0).isUpper()) {
                mainCommand = (*it);
            }
        }

        if (mainCommand.size()==0) {
            mainCommand = (*commandList.begin());
        }
    }

    initTexts();
}


/**
 * \param isSecondary true to avoid this action to be identified by
 * the given script file when calling getByScriptFile.
 * Used for example for recent file menu entries which all refer
 * to the script OpenFile.js.
 */
void RGuiAction::setScriptFile(const QString& sf, bool isSecondary) {
    QDir dir(".");
    QString relSf;
    if (sf.startsWith(":")) {
        relSf = sf;
    }
    else {
        relSf = dir.relativeFilePath(sf);
    }
    scriptFile = relSf;
    setObjectName(QFileInfo(sf).completeBaseName() + "Action");

    if (!isSecondary) {
        actionsByScriptFile[relSf] = this;
    }
}

void RGuiAction::setFactory(FactoryFunction f) {
    factory = f;
}

void RGuiAction::triggerGroupDefault(const QString& group) {
    if (!group.isEmpty()) {
        // if nothing else in this group is checked,
        // check default action of this group:
        //bool found = false;
        RGuiAction* defaultGroupAction = NULL;
        QList<RGuiAction*> actions = actionsByGroup.values(group);
        for (int i = 0; i < actions.size(); ++i) {
            RGuiAction* action = actions.at(i);
            /*
            if (action->isChecked() && action!=this) {
                found = true;
                break;
            }
            */
            if (action->isGroupDefault()) {
                defaultGroupAction = action;
                break;
            }
        }
        if (/*!found &&*/ defaultGroupAction!=NULL /*&& !defaultAction->isChecked()*/) {
            defaultGroupAction->slotTrigger();
        }
    }
}

void RGuiAction::triggerGroupDefaults() {
    QStringList groups = actionsByGroup.keys().toSet().toList();
    for (int i=0; i<groups.length(); i++) {
        triggerGroupDefault(groups.at(i));
    }
}

void RGuiAction::setGroup(const QString& title) {
    group = title;
    actionsByGroup.insert(group, this);
}

QString RGuiAction::getGroup() {
    return group;
}

void RGuiAction::setGroupDefault(bool on) {
    groupDefault = on;
}

bool RGuiAction::isGroupDefault() {
    return groupDefault;
}

/**
 * Triggers the first action in the list of actions that is registered
 * to use the given command.
 *
 * \param command Command that was launched (e.g. "line" or "ln").
 */
bool RGuiAction::triggerByCommand(const QString& cmd) {
    QString cmdLower = cmd.toLower();
    if (actionsByCommand.count(cmdLower)!=0 && actionsByCommand[cmdLower]!=NULL) {
        if (actionsByCommand[cmdLower]->isEnabled()) {
            actionsByCommand[cmdLower]->slotTrigger(cmd);
        }
        return true;
    } else {
        return false;
    }
}



/**
 * Triggers the first action in the list of actions that is based
 * on the given \c scriptFile.
 */
bool RGuiAction::triggerByScriptFile(const QString& scriptFile) {
    RGuiAction* guiAction = getByScriptFile(scriptFile);
    if (guiAction!=NULL) {
        guiAction->slotTrigger();
        return true;
    }
    else {
        return false;
    }
}



/**
 * \return The first action in the list of actions that is based
 * on the given \c scriptFile.
 */
RGuiAction* RGuiAction::getByScriptFile(const QString& scriptFile) {
    QDir dir(".");

    QString relFilePath;
    if (scriptFile.startsWith(":")) {
        relFilePath = scriptFile;
    }
    else {
        relFilePath = dir.relativeFilePath(scriptFile);
    }

    if (actionsByScriptFile.count(relFilePath) != 0) {
        return actionsByScriptFile[relFilePath];
    }
    
    // look in scripts wrapped in plugins:
    relFilePath = ":" + relFilePath;
    if (actionsByScriptFile.count(relFilePath) != 0) {
        return actionsByScriptFile[relFilePath];
    }

    return NULL;
}

/**
 * \return The first action in the list of actions that defines 
 * a class with the given name. Test is based on file name only.
 */
RGuiAction* RGuiAction::getByClassName(const QString& className) {
    for (int i=0; i<actions.size(); i++) {
        RGuiAction* a = actions[i];
        if (a==NULL) {
            return NULL;
        }
        QString fileName = a->getScriptFile();
        if (QFileInfo(fileName).baseName()==className) {
            return a;
        }
    }
    return NULL;
}


/**
 * \return A list of available top level commands. These are commands
 *      that can be used to trigger actions.
 *
 * \param primaryOnly True: only include primary commands (e.g. 'point')
 *                    False: also include secondary commands (e.g. 'po')
 */
QStringList RGuiAction::getAvailableCommands(bool primaryOnly) {
    QStringList ret;

    if (primaryOnly) {
        QMap<QString, RGuiAction*>::iterator it;
        for (it=actionsByPrimaryCommand.begin(); it!=actionsByPrimaryCommand.end(); ++it) {
            ret.push_back(it.key());
        }
    }
    else {
        QMap<QString, RGuiAction*>::iterator it;
        for (it=actionsByCommand.begin(); it!=actionsByCommand.end(); ++it) {
            ret.push_back(it.key());
        }
    }
        
    return ret;
}



/**
 * \return List of available commands for triggering actions that start with \c start.
 *
 * This is typically used when the user presses the Tab key in a command line to
 * complete a started command. For example entering "li<tab>" will result in the
 * command to be completed to "line".
 *
 * \param primaryOnly True: only include primary commands (e.g. 'point')
 *                    False: also include secondary commands (e.g. 'po')
 */
QStringList RGuiAction::getAvailableCommands(const QString& start, bool primaryOnly) {
    QStringList ret;

    QStringList all = getAvailableCommands(primaryOnly);
    QStringList::iterator it;
    for (it=all.begin(); it<all.end(); ++it) {
        if (start.size()==0 || (*it).indexOf(start)==0) {
            ret.push_back(*it);
        }
    }

    return ret;
}



/**
 * This should be called when the action is triggered, i.e. a GUI element is 
 * activated (button pressed, menu selected, etc).
 */
bool RGuiAction::slotTrigger(const QString& command) {
    RMainWindow* mainWindow = RMainWindow::getMainWindow();
    if (mainWindow != NULL && !getMainCommand().isEmpty()) {
        // display main command somewhere, e.g. in command line:
        if (command.isNull()) {
            mainWindow->handleUserCommand(getMainCommand());
        }
        else {
            mainWindow->handleUserCommand(command);
        }
    }

    // uncheck all other actions in this group and check this action:
    if (!group.isEmpty()) {
        setChecked(true);
        QList<RGuiAction*> actions = actionsByGroup.values(group);
        for (int i = 0; i < actions.size(); ++i) {
            RGuiAction* action = actions.at(i);
            if (action!=this) {
                action->setChecked(false);
            }
        }
    }

    if (scriptFile.size() > 0) {
        // call action factory of script handler:
        if (requiresDocument) {
            RDocumentInterface* di;
            if (documentInterface!=NULL) {
                di = documentInterface;
            }
            else {
                di = RMainWindow::getDocumentInterfaceStatic();
            }
            if (di == NULL) {
                qWarning() << "This action requires a document to be open: " << scriptFile;
                return true;
            }

            QString extension = QFileInfo(scriptFile).suffix();
            RScriptHandler* scriptHandler = di->getScriptHandler(extension);
            if (scriptHandler == NULL) {
                qWarning("RGuiAction::slotTrigger: "
                    "no script handler found for scriptFile: %s",
                        (const char*) scriptFile.toUtf8());
                return false;
            }

            scriptHandler->createActionDocumentLevel(scriptFile, this);
        } else {
            RScriptHandler::triggerActionApplicationLevel(scriptFile, this);
        }
        emit postTriggered();
        return true;
    } else if (factory != NULL) {
        // call C++ action factory:
        factory();
        emit postTriggered();
        return true;
    }

    //qWarning("RGuiAction::doAction: factory is NULL");
    // A QAction based action might choose to call QAction::trigger if false is
    // returned:
    emit postTriggered();
    return false;
}



/** 
 * Cleans up all GUI action objects.
 */
void RGuiAction::clear() {
    while (!actions.isEmpty()) {
        delete actions.takeFirst();
    }
}

void RGuiAction::addArgument(const QString& arg) {
    arguments.append(arg);
}

QStringList RGuiAction::getArguments() {
    return arguments;
}

void RGuiAction::clearArguments() {
    arguments.clear();
}
