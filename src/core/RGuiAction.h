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

#ifndef RGUIACTION_H
#define RGUIACTION_H

#include "core_global.h"

#include <QMap>
#include <QMetaType>
#include <QString>
#include <QStringList>
#include <QList>
#include <QAction>

#include "RTransactionListener.h"
#include "RFocusListener.h"
#include "RSelectionListener.h"

class QToolBar;

class RDocument;
class RDocumentInterface;

/**
 * \brief Abstract base class for GUI action classes. 
 *
 * Such classes represent a GUI action that can be used to start a tool.
 * One GUI action class may be assigned to multiple GUI elements, for 
 * example a menu, a toolbutton and a context menu.
 *
 * Each GUI action can have multiple commands assigned to it. These commands
 * can be used to trigger the action from a command line.
 *
 * Each GUI action can have multiple shortcuts assigned to it. Shortcuts
 * are 'traditional' key combinations that can be used to trigger the action.
 * e.g. Ctrl + Z, Ctrl + N, ...
 * 
 * \ingroup core
 * 
 * \scriptable
 */
class QCADCORE_EXPORT RGuiAction:
    public QAction,
    public RFocusListener,
    public RTransactionListener,
    public RSelectionListener {

Q_OBJECT

public:
    typedef void (*FactoryFunction)();

public:
    RGuiAction(const QString& text, QObject* parent = 0);
    virtual ~RGuiAction();
    
    /**
     * Initializes the GUI action texts (for menus, tooltips, ...).
     * This function is called whenever the text of the action changes.
     */
    virtual void initTexts();

    static QString formatToolTip(const QString& text, const QString& shortcut);
    QString getToolTip(const QString& text, const QString& shortcut);

    void setDocumentInterface(RDocumentInterface* di);
    RDocumentInterface* getDocumentInterface();

    /**
     * Sets the shortcut(s) for this action.
     *
     * \param shortcut Comma separated list of shortcuts (e.g. "Ctrl-Shift-Z,Ctrl-Y").
     */
    void setShortcut(const QKeySequence& shortcut);
    void setDefaultShortcut(const QKeySequence& shortcut);
    void setShortcuts(const QList<QKeySequence>& shortcuts);
    void setDefaultShortcuts(const QList<QKeySequence>& shortcuts);
    QList<QKeySequence> getDefaultShortcuts();
    void setShortcutText(const QString& text);
    QString getShortcutText();
    void setSortOrder(int sortOrder);
    int getSortOrder();

    void addToMenu(QMenu* menu);
    void addToToolBar(QToolBar* tb);
    void addToWidget(QWidget* w);

    /**
     * Sets the action icon to the given icon file.
     */
    virtual void setIcon(const QString& iconFile);

    void disableIcon();
    bool isIconDisabled();

    /**
     * Sets the tooltip for this action. Tooltips are shown when the mouse cursor
     * hovers over a GUI element for some time.
     */
    virtual void setToolTip(const QString& tip);

    /**
     * Sets the status tip of this action. The status tip is shown in the status bar
     * of the application when the mouse cursor hovers of a menu entry.
     */
    virtual void setStatusTip(const QString& tip);

    /**
     * Enables or disables the action.
     */
    virtual void setEnabled(bool on);
    
    /**
     * Enables or disables the action.
     */
    virtual void setEnabledOverride(bool on, int override);
    
    /**
     * Checks or unchecks this action.
     */
    virtual void setChecked(bool on);

    static void triggerGroupDefault(const QString& group);
    static void triggerGroupDefaults();

    /**
     * \return True if this action is checked.
     */
    virtual bool isChecked();
    
    /**
     * If \c on is true, this action requires a document to be open. The GUI element(s)
     * can for example be grayed out if no document is open.
     */
    void setRequiresDocument(bool on) {
        requiresDocument = on;
    }

    /**
     * \retval true This action requires an open document to be started.
     * \retval false This action does not require an open document to be started.
     */
    bool getRequiresDocument() {
        return requiresDocument;
    }

    /**
     * If \c on is true, this action requires a selection to operate on. The GUI element(s)
     * can for example be grayed out if no selection is present.
     */
    void setRequiresSelection(bool on) {
        requiresSelection = on;
    }

    /**
     * \retval true This action requires an selection to be started.
     * \retval false This action does not require a selection to be started.
     */
    bool getRequiresSelection() {
        return requiresSelection;
    }

    void setRequiresUndoableTransaction(bool on) {
        requiresUndoableTransaction = on;
    }

    bool getRequiresUndoableTransaction() {
        return requiresUndoableTransaction;
    }

    void setRequiresRedoableTransaction(bool on) {
        requiresRedoableTransaction = on;
    }

    bool getRequiresRedoableTransaction() {
        return requiresRedoableTransaction;
    }

    void setOverride() {
        override = true;
    }

    bool isOverride() {
        return override;
    }

    void setNoState(bool checkable = false) {
        noState = true;
        setCheckable(checkable);
    }

    bool hasNoState() {
        return noState;
    }

    void setUniqueGroup(const QString& ug) {
        uniqueGroup = ug;
    }

    QString getUniqueGroup() {
        return uniqueGroup;
    }

    /**
     * \return The main command used to trigger this action. This is typically the
     *      full command (e.g. "line") rather than one of the abbreviated commands
     *      such as "ln".
     */
    QString getMainCommand() {
        return mainCommand;
    }

    /**
     * \return Complete list of commands that may be used to trigger this action.
     */
    QStringList getCommands() {
        return commandList;
    }

    QStringList getDefaultCommands() {
        return defaultCommandList;
    }
    
    void setDefaultCommands(const QStringList& cmds);
    void setCommands(const QStringList& cmds);
    
    /**
     * \nonscriptable
     */
    void setFactory(FactoryFunction f);
    
    /**
     * Sets the script file to be used for this action. This is only used for
     * script based actions.
     */
    void setScriptFile(const QString& sf, bool isSecondary = false);

    /**
     * \return Script file on which this action is based on.
     */
    QString getScriptFile() {
        return scriptFile;
    }

    virtual void setGroup(const QString& title);
    QString getGroup();

    void setGroupDefault(bool on);
    bool isGroupDefault();

    /**
     * \return List of all instantiated actions.
     */
    static QList<RGuiAction*> getActions() {
        return actions;
    }

    static bool triggerByCommand(const QString& cmd);
    static RGuiAction* getByScriptFile(const QString& scriptFile);
    static RGuiAction* getByClassName(const QString& className);
    static bool triggerByScriptFile(const QString& scriptFile);
    
    static QStringList getAvailableCommands(bool primaryOnly=false);
    static QStringList getAvailableCommands(const QString& start, bool primaryOnly=false);

    static void clear();

    virtual void updateTransactionListener(const RDocument* document);
    virtual void updateSelectionListener(RDocumentInterface* documentInterface);
    virtual void updateFocus(RDocumentInterface* documentInterface);

    void addArgument(const QString& arg);
    QStringList getArguments();
    void clearArguments();

public slots:
    /**
     * Called when the action is triggered (e.g. a button is pressed or a menu chosen).
     */
    bool slotTrigger(const QString& command = QString::null);

signals:
    void postTriggered();

protected:
    static QMap<QString, RGuiAction*> actionsByCommand;
    static QMap<QString, RGuiAction*> actionsByPrimaryCommand;
    static QMap<QString, RGuiAction*> actionsByScriptFile;
    static QMultiMap<QString, RGuiAction*> actionsByGroup;
    static QList<RGuiAction*> actions;

    FactoryFunction factory;
    QString scriptFile;
    QString mainCommand;
    QStringList commandList;
    QStringList defaultCommandList;
    QString group;
    bool groupDefault;
    
    bool requiresDocument;
    bool requiresSelection;
    bool requiresUndoableTransaction;
    bool requiresRedoableTransaction;
    bool override;
    bool noState;
    QString uniqueGroup;
    QStringList arguments;

    QList<QKeySequence> defaultShortcuts;
    QString shortcutText;
    QString toolTip;
    int sortOrder;
    bool iconDisabled;
    int enabledOverride;
    RDocumentInterface* documentInterface;
};

Q_DECLARE_METATYPE(RGuiAction*)
Q_DECLARE_METATYPE(QList<RGuiAction*>)

#endif
