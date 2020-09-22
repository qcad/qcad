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
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QMenu>
#include <QPainter>
#include <QSvgRenderer>
#include <QToolBar>
#include <QVectorIterator>

#include "RDebug.h"
#include "RGuiAction.h"
#include "RScriptHandler.h"
#include "RSingleApplication.h"
#include "RWidget.h"



QMap<QString, RGuiAction*> RGuiAction::actionsByCommand;
QMap<QString, RGuiAction*> RGuiAction::actionsByShortcut;
QMap<QString, RGuiAction*> RGuiAction::actionsByPrimaryCommand;
QMap<QString, RGuiAction*> RGuiAction::actionsByScriptFile;
QMultiMap<QString, RGuiAction*> RGuiAction::actionsByGroup;
QList<RGuiAction*> RGuiAction::actions;




RGuiAction::RGuiAction(const QString& text, QObject* parent)
  : QAction(text, parent),
    factory(NULL),
    oriText(text),
    groupDefault(false),
    forceGlobal(false),
    requiresDocument(true),
    requiresSelection(false),
    requiresUndoableTransaction(false),
    requiresRedoableTransaction(false),
    override(false),
    allowInterrupt(false),
    noState(false),
    toggleable(false),
    iconDisabled(false),
    enabledOverride(-1) {
    //documentInterface(NULL) {
    
    initTexts();
    
    connect(this, SIGNAL(triggered()), this, SLOT(slotTrigger()));

    setCheckable(true);

    actions.push_back(this);

    setMenuRole(QAction::NoRole);
}



RGuiAction::~RGuiAction() {
    //qDebug() << "RGuiAction::~RGuiAction:" << scriptFile << " / sep: " << isSeparator();

    QList<QMap<QString, RGuiAction*>*> maps;
    maps << &actionsByCommand;
    maps << &actionsByShortcut;
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
    //documentInterface = NULL;
}


//void RGuiAction::setDocumentInterface(RDocumentInterface* di) {
//    documentInterface = di;
//}

//RDocumentInterface* RGuiAction::getDocumentInterface() const {
//    return documentInterface;
//}

void RGuiAction::setText(const QString& text) {
    this->oriText = text;
    initTexts();
}


void RGuiAction::initTexts() {
    QString textOnly = oriText;
    textOnly.replace('&', "");

    QString textAndKeycode = oriText;

    // Override shortcut text:
    if (!shortcutText.isEmpty()) {
#ifdef Q_OS_MACX
        if (!textAndKeycode.endsWith(" (" + shortcutText + ")")) {
            textAndKeycode += " (" + shortcutText + ")";
        }
#else
        // tab does not work for Mac OS X:
        if (textAndKeycode.indexOf(QLatin1Char('\t'))!=-1) {
            textAndKeycode = textAndKeycode.left(textAndKeycode.indexOf('\t'));
        }
        textAndKeycode += QLatin1Char('\t');
        textAndKeycode += shortcutText;
#endif
    }

    QAction::setText(textAndKeycode);

    QString tip = toolTip;
    if (tip.isNull()) {
        tip = textOnly;
    }

    QString kcs = shortcutText.isEmpty() ? shortcut().toString() : shortcutText;
    if (!kcs.isEmpty()) {
        tip = getToolTip(tip, kcs);
    }

    QAction::setToolTip(tip);
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
    QString col = RSettings::hasDarkGuiBackground() ? "lightgray" : "gray";

    return QString("%1 <span style=\"color: " + col + "; font-size: small\">%2</span>")
                .arg(text)
                .arg(sc);
}


QString RGuiAction::getToolTip(const QString& text, const QString& shortcut) {
    QString ret = formatToolTip(text, shortcut);

    // additional info for disabled tools:
    if (!isEnabled()) {
        if (requiresSelection) {
            ret += "<br><i>" + tr("Requires selection") + "</i>";
        }
    }

    return ret;
}

void RGuiAction::setShortcutText(const QString& text) {
    shortcutText = text;
    initTexts();
}

QString RGuiAction::getShortcutText() const {
    return shortcutText;
}

QString RGuiAction::getShortcutsString(const QString& separator, QKeySequence::SequenceFormat format) const {
//    if (isNull(ksList)) {
//        return "";
//    }

    QString ret = "";

    QList<QKeySequence> scs = getShortcuts();
    for (int i=0; i<scs.length(); ++i) {
        ret += scs[i].toString(format);
        if (i<scs.length()-1) {
            ret += separator;
        }
    }

    return ret;
}

void RGuiAction::updateIcons() {
    QList<RGuiAction*> actions = getActions();
    for (int i=0; i<actions.length(); i++) {
        RGuiAction* action = actions[i];
        if (action==NULL) {
            continue;
        }
        action->updateIcon();
    }
}

void RGuiAction::updateIcon() {
    setIcon(iconFile);
}

void RGuiAction::setIcon(const QString& iconFile) {
    this->iconFile = iconFile;

    // look up theme specific icon:
    QFileInfo fi(iconFile);
    QString iconFileName = fi.fileName();
    QString themePath = RSettings::getThemePath();
    QString themeIconFile = iconFile;
    if (!themePath.isEmpty()) {
        // look up svg in theme:
        themeIconFile = themePath + "/icons/" + iconFileName;
        if (!QFileInfo(themeIconFile).exists()) {
            // no SVG found, look up PNG:
            QString iconBaseName = fi.baseName();
            themeIconFile = themePath + "/icons/" + iconBaseName + ".png";
            if (!QFileInfo(themeIconFile).exists()) {
                // no PNG found, use default icon:
                themeIconFile = iconFile;
            }
        }
    }

    if (themeIconFile.isEmpty()) {
        QAction::setIcon(QIcon());
    }
    else {
        QString fileName = themeIconFile;

        if (RSettings::hasDarkGuiBackground()) {
            QFileInfo fi(themeIconFile);
            QString iconFileDark = fi.absolutePath() + QDir::separator() + fi.baseName() + "-inverse." + fi.suffix();
            if (QFileInfo(iconFileDark).exists()) {
                fileName = iconFileDark;
            }
        }

        if (QFileInfo(fileName).suffix().toLower()=="svg" &&
            !QCoreApplication::arguments().contains("-max-icon-res")) {

            int iconSize = RSettings::getIntValue("CadToolBar/IconSize", 32);
            iconSize = qMax(iconSize, RSettings::getIntValue("ToolBar/IconSize", 32));
            iconSize = qMax(iconSize, RSettings::getIntValue("CadToolMatrix/IconSize", 24));

            // retina icons:
            if (RSettings::getDevicePixelRatio()>1) {
                iconSize*=RSettings::getDevicePixelRatio();
            }

            QPixmap pm(iconSize,iconSize);
            pm.fill(Qt::transparent);
            QPainter p;
            p.begin(&pm);
            QSvgRenderer renderer(fileName);
            renderer.render(&p, QRectF(0, 0, iconSize, iconSize));
            p.end();

            QIcon icon(pm);
            QAction::setIcon(icon);
        }
        else {
            QAction::setIcon(QIcon(themeIconFile));
        }
    }
}

void RGuiAction::disableIcon() {
    iconDisabled = true;
}

bool RGuiAction::isIconDisabled() const {
    return iconDisabled;
}

void RGuiAction::setDefaultShortcuts(const QList<QKeySequence>& shortcuts) {
    defaultShortcuts = shortcuts;
    setShortcuts(shortcuts);
}

QList<QKeySequence> RGuiAction::getDefaultShortcuts() {
    return defaultShortcuts;
}

void RGuiAction::setDefaultShortcut(const QKeySequence& shortcut) {
    defaultShortcuts = QList<QKeySequence>() << shortcut;
    setShortcut(shortcut);
}

void RGuiAction::addShortcut(const QKeySequence& shortcut) {
    if (shortcut.count()==1) {
        return;
    }

    QString key;
    for (int i=0; i<shortcut.count(); i++) {
        key += QChar(shortcut[i]);
    }
    key = key.toLower();
    actionsByShortcut.insert(key, this);

    if (shortcutText.isEmpty()) {
        // for first shortcut, set text to display in menu:
        shortcutText = key.toUpper();
    }

    multiKeyShortcuts.append(shortcut);
}

void RGuiAction::setShortcut(const QKeySequence& shortcut) {
    multiKeyShortcuts.clear();

    if (shortcut.count()==1) {
        // single key stroke (Ctrl-A, +, ...):
        // supported by Qt:
        QAction::setShortcut(shortcut);
    }
    else {
        // multi key stroke (LI, ...):
        // broken in Qt, use own implementation:
        addShortcut(shortcut);
    }

    //QAction::setShortcut(shortcut);
    //shortcuts = QList<QKeySequence>() << shortcut;
    initTexts();
}

void RGuiAction::setShortcuts(const QList<QKeySequence>& shortcuts) {
    QList<QKeySequence> scs;

    multiKeyShortcuts.clear();

    for (int i=0; i<shortcuts.length(); i++) {
        if (shortcuts[i].count()==1) {
            scs.append(shortcuts[i]);
        }
        else {
            //setShortcut(shortcuts[i]);
            addShortcut(shortcuts[i]);
        }
    }

    // only one key shortcuts are set here:
    QAction::setShortcuts(scs);
    initTexts();
}

void RGuiAction::setShortcutsFromStrings(const QStringList& shortcuts) {
    QList<QKeySequence> scs;

    multiKeyShortcuts.clear();

    for (int i=0; i<shortcuts.length(); i++) {
        QKeySequence ks(shortcuts[i]);
        if (ks.count()==1) {
            scs.append(ks);
        }
        else {
            //setShortcut(shortcuts[i]);
            addShortcut(ks);
        }
    }

    // only one key shortcuts are set here:
    QAction::setShortcuts(scs);
    initTexts();
}

QList<QKeySequence> RGuiAction::getShortcuts() const {
    return multiKeyShortcuts + shortcuts();
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
    if (RSettings::getBoolValue("StatusBar/ShowTips", true)) {
        QAction::setStatusTip(tip);
        initTexts();
    }
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

bool RGuiAction::isChecked() const {
    return QAction::isChecked();
}

void RGuiAction::setRequiresSelection(bool on) {
    requiresSelection = on;

    if (requiresSelection) {
        RMainWindow* mw = RMainWindow::getMainWindow();
        if (mw) {
            mw->addSelectionListener(this);
        }
    }
}

void RGuiAction::setGroupSortOrderStatic(QAction* a, int groupSortOrder) {
    a->setProperty("GroupSortOrder", groupSortOrder);
}

void RGuiAction::setGroupSortOrderOverrideStatic(QAction* a, const QString& widgetName, int groupSortOrder) {
    QString n = QString("GroupSortOrderOverride") + widgetName;
    a->setProperty(n.toUtf8(), groupSortOrder);
}

int RGuiAction::getGroupSortOrderStatic(const QAction* a, const QWidget* w) {
    if (a==NULL) {
        return -1;
    }

    if (w!=NULL) {
        QString n = QString("GroupSortOrderOverride") + w->objectName();
        if (a->property(n.toUtf8()).isValid()) {
            return a->property(n.toUtf8()).toInt();
        }
    }
    if (a->property("GroupSortOrder").isValid()) {
        return a->property("GroupSortOrder").toInt();
    }
    return -1;
}

void RGuiAction::setSortOrderStatic(QAction* a, int sortOrder) {
    a->setProperty("SortOrder", sortOrder);
}

void RGuiAction::setSortOrderOverrideStatic(QAction* a, const QString& widgetName, int sortOrder) {
    QString n = QString("SortOrderOverride") + widgetName;
    a->setProperty(n.toUtf8(), sortOrder);
}

int RGuiAction::getSortOrderStatic(const QAction* a, const QWidget* w) {
    if (a==NULL) {
        return -1;
    }
    if (w!=NULL) {
        QString n = QString("SortOrderOverride") + w->objectName();
        if (a->property(n.toUtf8()).isValid()) {
            return a->property(n.toUtf8()).toInt();
        }
    }
    if (a->property("SortOrder").isValid()) {
        return a->property("SortOrder").toInt();
    }
    return -1;
}

void RGuiAction::setGroupSortOrder(int groupSortOrder) {
    setGroupSortOrderStatic(this, groupSortOrder);
}

void RGuiAction::setGroupSortOrderOverride(const QString& widgetName, int groupSortOrder) {
    setGroupSortOrderOverrideStatic(this, widgetName, groupSortOrder);
}

int RGuiAction::getGroupSortOrder(const QWidget* w) const {
    return getGroupSortOrderStatic(this, w);
}

void RGuiAction::setSortOrder(int sortOrder) {
    setSortOrderStatic(this, sortOrder);
}

void RGuiAction::setSortOrderOverride(const QString& widgetName, int sortOrder) {
    setSortOrderOverrideStatic(this, widgetName, sortOrder);
}

int RGuiAction::getSortOrder(const QWidget* w) const {
    return getSortOrderStatic(this, w);
}

void RGuiAction::setWidgetNamesStatic(QAction* a, const QStringList& widgetNames) {
    a->setProperty("WidgetNames", widgetNames);
}

QStringList RGuiAction::getWidgetNamesStatic(const QAction* a) {
    if (a->property("WidgetNames").isValid()) {
        return a->property("WidgetNames").toStringList();
    }
    else {
        return QStringList();
    }
}

void RGuiAction::setWidgetNames(const QStringList& widgetNames) {
    setWidgetNamesStatic(this, widgetNames);
}

QStringList RGuiAction::getWidgetNames() const {
    return getWidgetNamesStatic(this);
}

void RGuiAction::addToMenu(QMenu* menu) {
    if (menu==NULL) {
        qWarning("RGuiAction::addToMenu: menu is NULL");
        Q_ASSERT(false);
        return;
    }
    addToWidget(this, menu);
}

void RGuiAction::addToToolBar(QToolBar* tb) {
    if (tb==NULL) {
        qWarning("RGuiAction::addToMenu: tb is NULL");
        Q_ASSERT(false);
        return;
    }
    addToWidget(this, tb);
    QWidget* w = tb->widgetForAction(this);
    if (w != NULL) {
        w->setObjectName("ToolButton" + objectName());
    }
}

void RGuiAction::fixSeparators(const QWidget* w) {
    QAction* lastSeparator = NULL;

    int highestGroupSortOrder = -1;
    QList<QAction*> actions = w->actions();
    for (int i=0; i<actions.length(); i++) {
        //RGuiAction* a = dynamic_cast<RGuiAction*> (actions[i]);
        QAction* a = actions[i];
        if (a == NULL) {
            continue;
        }

        if (!a->isSeparator()) {
            continue;
        }

        a->setVisible(true);

        if (highestGroupSortOrder==-1 || getGroupSortOrderStatic(a, w)>highestGroupSortOrder) {
            highestGroupSortOrder = getGroupSortOrderStatic(a, w);
            lastSeparator = a;
        }
    }

    if (lastSeparator!=NULL) {
        lastSeparator->setVisible(false);
    }
}

void RGuiAction::addSeparatorToWidget(QAction* a, QWidget* w) {
    int go = getGroupSortOrderStatic(a, w);
    QString objectName = QString("Separator%1").arg(go);
    if (w->findChild<QWidget*>(objectName)!=NULL) {
        // separator for this group already added
        return;
    }

    QAction* separator = new RGuiAction("", w);
    separator->setSeparator(true);
    separator->setObjectName(objectName);
    setGroupSortOrderStatic(separator, go);
    setSortOrderStatic(separator, 99999);
    addToWidget(separator, w);
}

void RGuiAction::addToWidget(QAction* action, QWidget* w) {
    if (action==NULL || w==NULL) {
        qWarning("RGuiAction::addToWidget: widget or action is NULL");
        return;
    }

    if (w->actions().contains(action)) {
        return;
    }

    if (!action->isSeparator()) {
        if (QCoreApplication::arguments().contains("-debug-action-order")) {
            if (!action->text().contains("{")) {
                action->setText(action->text() + QString(" {%1,%2}").arg(getGroupSortOrderStatic(action, w)).arg(getSortOrderStatic(action, w)));
            }
        }
    }

    RWidget* rw = dynamic_cast<RWidget*>(w);

    // find existing groups:
    QSet<int> groupSortOrders;
    QList<QAction*> actions = w->actions();
    for (int i=0; i<actions.length(); i++) {
        //RGuiAction* a = dynamic_cast<RGuiAction*> (actions[i]);
        QAction* a = actions[i];
        if (a == NULL) {
            continue;
        }

        groupSortOrders.insert(getGroupSortOrderStatic(a, w));
    }

    QListIterator<QAction*> i(actions);
    while (i.hasNext()) {
        QAction* a = i.next();
        if (a == NULL) {
            continue;
        }

        int actionGroupSortOrder = getGroupSortOrderStatic(action, w);
        int actionSortOrder = getSortOrderStatic(action, w);

        int otherGroupSortOrder = getGroupSortOrderStatic(a, w);
        int otherSortOrder = getSortOrderStatic(a, w);

        // same separator group:
        if (actionGroupSortOrder >= 0 && actionGroupSortOrder == otherGroupSortOrder) {
            if (actionSortOrder >= 0 && actionSortOrder < otherSortOrder) {
                if (rw) {
                    rw->insertAction(a, action);
                }
                else {
                    w->insertAction(a, action);
                }
                return;
            }
        }

        // group before existing group:
        if (actionGroupSortOrder >= 0 && actionGroupSortOrder < otherGroupSortOrder) {
            if (rw) {
                rw->insertAction(a, action);
            }
            else {
                w->insertAction(a, action);
            }

            if (!action->isSeparator() && !groupSortOrders.contains(actionGroupSortOrder)) {
                addSeparatorToWidget(action, w);
            }
            fixSeparators(w);
            return;
        }
    }

    if (rw) {
        rw->addAction(action);
    }
    else {
        w->addAction(action);
    }

    int gso = getGroupSortOrderStatic(action, w);
    if (!action->isSeparator() && gso>=0 && !groupSortOrders.contains(gso)) {
        addSeparatorToWidget(action, w);
    }

    fixSeparators(w);
}

void RGuiAction::removeFromWidget(QAction* action, QWidget* w) {
    if (action==NULL || w==NULL) {
        qWarning("RGuiAction::removeFromWidget: widget or action is NULL");
        return;
    }

    RWidget* rw = dynamic_cast<RWidget*>(w);
    if (rw) {
        rw->removeAction(action);
    }
    else {
        w->removeAction(action);
    }
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

    if (requiresUndoableTransaction && document!=NULL) {
        if (text().contains("[") && text().contains("]")) {
            QString t = text();
            QString undoText = document->getTransactionStack().getUndoableTransactionText();
            if (undoText.isEmpty()) {
                undoText = "-";
            }
            t.replace(QRegExp("\\[[^\\]]*\\]"), "[" + undoText + "]");
            setText(t);
        }
    }

    if (requiresRedoableTransaction && document!=NULL) {
        if (text().contains("[") && text().contains("]")) {
            QString t = text();
            QString redoText = document->getTransactionStack().getRedoableTransactionText();
            if (redoText.isEmpty()) {
                redoText = "-";
            }
            t.replace(QRegExp("\\[[^\\]]*\\]"), "[" + redoText + "]");
            setText(t);
        }
    }

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

bool RGuiAction::triggerByShortcut(const QString& sc) {
    QString scLower = sc.toLower();
    if (actionsByShortcut.count(scLower)!=0 && actionsByShortcut[scLower]!=NULL) {
        if (actionsByShortcut[scLower]->isEnabled()) {
            actionsByShortcut[scLower]->slotTrigger();
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
        if (actionsByScriptFile.count(scriptFile) != 0) {
            return actionsByScriptFile[scriptFile];
        }

        // strip : at start:
        relFilePath = scriptFile.mid(1);
    }
    else {
        relFilePath = dir.relativeFilePath(scriptFile);
    }

    if (actionsByScriptFile.count(relFilePath) != 0) {
        return actionsByScriptFile[relFilePath];
    }
    
    // look in scripts wrapped in plugins:
    QString pluginFilePath = ":" + relFilePath;
    if (actionsByScriptFile.count(pluginFilePath) != 0) {
        return actionsByScriptFile[pluginFilePath];
    }

    // look in scripts wrapped in plugins:
    pluginFilePath = ":/" + relFilePath;
    if (actionsByScriptFile.count(pluginFilePath) != 0) {
        return actionsByScriptFile[pluginFilePath];
    }

    qWarning() << "action not found:" << relFilePath;
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

RGuiAction* RGuiAction::getByCommand(const QString& command) {
    if (actionsByCommand.count(command) != 0) {
        return actionsByCommand[command];
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
    if (mainWindow != NULL) {
        // display main command somewhere, e.g. in command line:
        if (command.isNull()) {
            QString mainCommand = getMainCommand();
            if (!mainCommand.isEmpty()) {
                mainWindow->handleUserCommand(mainCommand);
            }
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
        if (requiresDocument && !forceGlobal) {
            RDocumentInterface* di;
//            if (documentInterface!=NULL) {
//                di = documentInterface;
//                //qDebug() << "got di: " << (unsigned long int)di;
//            }
//            else {
                di = RMainWindow::getDocumentInterfaceStatic();
                //qDebug() << "getting di statically: " << (unsigned long int)di;
//            }
            if (di == NULL) {
                qWarning() << "This action requires a document to be open: " << scriptFile;
                return true;
            }

            if (isToggleable() && !isChecked()) {
                // if action is toggleable, terminate already running action:
                di->terminateCurrentAction();
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
        factory(this);
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

void RGuiAction::init() {
    RMainWindow* appWin = RMainWindow::getMainWindow();
    QStringList widgetNames = getWidgetNames();
    for (int i=0; i<widgetNames.length(); i++) {
        QString wn = widgetNames[i];
        QWidget* w = appWin->getChildWidget(wn);
        if (w!=NULL) {
            addToWidget(this, w);
        }
    }
}
