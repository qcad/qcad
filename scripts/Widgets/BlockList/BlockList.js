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

include("../../WidgetFactory.js");

/**
 * Block list widget class (QWidget).
 */
function RBlockListQt(parent) {
    RListWidget.call(this, parent);
    if (RS.getSystemId()==="osx") {
        this.setIconOffset(7);
    }
    this.iconSize = new QSize(32, 16);
    this.di = null;

    var appWin = EAction.getMainWindow();
    var adapter = new RBlockListenerAdapter();
    appWin.addBlockListener(adapter);
    adapter.blocksUpdated.connect(this, "updateBlocks");
    adapter.blocksCleared.connect(this, "clearBlocks");

    this.itemSelectionChanged.connect(this, "blockActivated");
    this.itemDoubleClicked.connect(this, "editBlock");
    this.iconClicked.connect(this, "iconClickedSlot");
    this.basePath = includeBasePath;
}

RBlockListQt.prototype = new RListWidget();

RBlockListQt.prototype.contextMenuEvent = function(e) {
    var item = this.itemAt(e.pos());
    if (!isNull(item)) {
        this.setCurrentItem(item);
    }

    var menu = new QMenu();
    RGuiAction.getByScriptFile("scripts/Block/ToggleBlockVisibility/ToggleBlockVisibility.js").addToMenu(menu);
    RGuiAction.getByScriptFile("scripts/Block/ShowAllBlocks/ShowAllBlocks.js").addToMenu(menu);
    RGuiAction.getByScriptFile("scripts/Block/HideAllBlocks/HideAllBlocks.js").addToMenu(menu);
    RGuiAction.getByScriptFile("scripts/Block/AddBlock/AddBlock.js").addToMenu(menu);
    RGuiAction.getByScriptFile("scripts/Block/RemoveBlock/RemoveBlock.js").addToMenu(menu);
    RGuiAction.getByScriptFile("scripts/Block/RenameBlock/RenameBlock.js").addToMenu(menu);
    RGuiAction.getByScriptFile("scripts/Block/EditBlock/EditBlock.js").addToMenu(menu);
    RGuiAction.getByScriptFile("scripts/Block/InsertBlock/InsertBlock.js").addToMenu(menu);
    RGuiAction.getByScriptFile("scripts/Block/SelectBlockReferences/SelectBlockReferences.js").addToMenu(menu);
    RGuiAction.getByScriptFile("scripts/Block/DeselectBlockReferences/DeselectBlockReferences.js").addToMenu(menu);

    menu.exec(QCursor.pos());

    e.ignore();
};

/**
 * Called when blocks are addded, edited or deleted. Updates the block list.
 */
RBlockListQt.prototype.updateBlocks = function(documentInterface) {
    this.di = documentInterface;

    var block;
    
    var currentRow = this.currentRow;
    var pos = this.verticalScrollBar().sliderPosition;
    this.clear();
    if (isNull(documentInterface)) {
        return;
    }

    var doc = documentInterface.getDocument();

    var currentBlockId = doc.getCurrentBlockId();
    var result = doc.queryAllBlocks();
    for (var i=0; i<result.length; ++i) {
        var id = result[i];
        block = doc.queryBlock(id);
        if (block.isNull()) {
            continue;
        }

        // hide anonymous blocks:
        if (RSettings.getBoolValue("BlockList/HideInternalBlocks", false)===true) {
            if (block.getName().toLowerCase().startsWith("a$c") && block.getName().length===13) {
                continue;
            }
        }

        var item = new QListWidgetItem(block.getName(), this);
        var iconName =
            //this.basePath + "/blockstatus_%1.svg"
            //    .arg(Number(id==currentBlockId));
                    this.basePath + "/blockstatus_%1%2.svg"
                        .arg(Number(block.isFrozen()))
                        .arg(Number(id==currentBlockId));
        item.setIcon(new QIcon(iconName));
        this.addItem(item);
    }
    this.sortItems();

    block = doc.queryCurrentBlock();
    if (!block.isNull()) {
        var list = this.findItems(block.getName(), Qt.MatchExactly);
        if (list.length!==0) {
            this.setCurrentItem(list[0]);
        }
    }
    this.verticalScrollBar().sliderPosition = pos;

    if (currentRow!=-1 && !isNull(this.item(currentRow))) {
        this.currentRow = currentRow;
        this.item(currentRow).setSelected(true);
    }
    this.blockActivated();
};

/**
 * Called when no document is active. Clears the block list.
 */
RBlockListQt.prototype.clearBlocks = function() {
    this.clear();
};

/**
 * Called when the user clicks the icon beside the block name to hide
 * all block inserts of that block.
 */
RBlockListQt.prototype.iconClickedSlot = function(x, item) {
    if (isNull(this.di) || isNull(item)) {
        return;
    }

    var doc = this.di.getDocument();
    var block = doc.queryBlock(item.text());
    if (block.isNull()) {
        return;
    }

    if (x < this.iconSize.width() / 2) {
        block.setFrozen(!block.isFrozen());
    }
    else if (x < this.iconSize.width()) {
        this.setCurrentItem(item);
        this.editBlock();
    }

    var op = new RModifyObjectOperation(block);
    this.di.applyOperation(op);

    this.updateBlocks(this.di);
};

/**
 * Called when a block name is activated (clicked, highlighted) in the block list.
 */
RBlockListQt.prototype.blockActivated = function() {
    if (isNull(this.di)) {
        this.enableActions(false);
        return;
    }

    var list = this.selectedItems();
    if (list.length===0) {
        this.enableActions(false);
        return;
    }

    var item = list[0];
    if (isNull(item)) {
        this.enableActions(false);
        return;
    }

    var document = this.di.getDocument();
    if (isNull(document)) {
        this.enableActions(false);
        return;
    }

    var currentBlock = document.queryCurrentBlock();
    if (isNull(currentBlock)) {
        this.enableActions(false);
        return;
    }

    // prevent removal or insertion of current block:
    var insertable = currentBlock.getName()!=item.text() && !item.text().startsWith("*");
    this.enableActions(insertable);
};

/**
 * Enable / disable buttons that edit, remove or insert the active block.
 */
RBlockListQt.prototype.enableActions = function(enable) {
    var override;
    if (enable===true) {
        override = 1;
    }
    else {
        override = 0;
    }

    var action;
    action = RGuiAction.getByScriptFile("scripts/Block/ToggleBlockVisibility/ToggleBlockVisibility.js");
    action.setEnabledOverride(enable, override);
    action = RGuiAction.getByScriptFile("scripts/Block/InsertBlock/InsertBlock.js");
    action.setEnabledOverride(enable, override);
    action = RGuiAction.getByScriptFile("scripts/Block/RemoveBlock/RemoveBlock.js");
    action.setEnabledOverride(enable, override);
    action = RGuiAction.getByScriptFile("scripts/Block/RenameBlock/RenameBlock.js");
    action.setEnabledOverride(enable, override);
}

/**
 * Called when the user wants to edit the currently selected block
 * (double click).
 */
RBlockListQt.prototype.editBlock = function() {
    var action = RGuiAction.getByScriptFile("scripts/Block/EditBlock/EditBlock.js");
    if (!isNull(action)) {
        action.slotTrigger();
    }

    this.blockActivated();
}



/**
 * \class BlockList
 * \brief Initializes the block list widget (RBlockListQt).
 * \ingroup ecma_widgets
 */
function BlockList(guiAction) {
    Widgets.call(this, guiAction);
}

BlockList.prototype = new Widgets();

BlockList.getPreferencesCategory = function() {
    return [ qsTr("Widgets"), qsTr("Block List") ];
};

BlockList.applyPreferences = function(doc, mdiChild) {
    var appWin = RMainWindowQt.getMainWindow();
    appWin.notifyBlockListeners(EAction.getDocumentInterface());
};


/**
 * Shows / hides the layer list.
 */
BlockList.prototype.beginEvent = function() {
    Widgets.prototype.beginEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("BlockListDock");
    if (!QCoreApplication.arguments().contains("-no-show")) {
        dock.visible = !dock.visible;
    }
};

BlockList.prototype.finishEvent = function() {
    Widgets.prototype.finishEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("BlockListDock");
    this.getGuiAction().setChecked(dock.visible);
};


/**
 * Initializes the block list widget.
 */
BlockList.init = function(basePath) {
    var appWin = RMainWindowQt.getMainWindow();

    var action = new RGuiAction(qsTr("Block List"), appWin);
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/BlockList.js");
    action.setIcon(basePath + "/BlockList.svg");
    action.setDefaultShortcut(new QKeySequence("g,b"));
    action.setGroupSortOrder(3600);
    action.setSortOrder(200);
    action.setWidgetNames(["ViewMenu", "ViewToolBar", "ViewToolsPanel", "WidgetsToolBar"]);

    var formWidget = WidgetFactory.createWidget(basePath, "BlockList.ui");
    var layout = formWidget.findChild("verticalLayout");
    var blockList = new RBlockListQt(layout);
    blockList.objectName = "BlockList";
    layout.addWidget(blockList, 1, 0);

    var button;
    button = formWidget.findChild("ShowAllBlocks");
    button.setDefaultAction(RGuiAction.getByScriptFile("scripts/Block/ShowAllBlocks/ShowAllBlocks.js"));
    button = formWidget.findChild("HideAllBlocks");
    button.setDefaultAction(RGuiAction.getByScriptFile("scripts/Block/HideAllBlocks/HideAllBlocks.js"));
    button = formWidget.findChild("AddBlock");
    button.setDefaultAction(RGuiAction.getByScriptFile("scripts/Block/AddBlock/AddBlock.js"));
    button = formWidget.findChild("RemoveBlock");
    button.setDefaultAction(RGuiAction.getByScriptFile("scripts/Block/RemoveBlock/RemoveBlock.js"));
    button = formWidget.findChild("RenameBlock");
    button.setDefaultAction(RGuiAction.getByScriptFile("scripts/Block/RenameBlock/RenameBlock.js"));
    button = formWidget.findChild("EditBlock");
    button.setDefaultAction(RGuiAction.getByScriptFile("scripts/Block/EditBlock/EditBlock.js"));
    button = formWidget.findChild("InsertBlock");
    button.setDefaultAction(RGuiAction.getByScriptFile("scripts/Block/InsertBlock/InsertBlock.js"));
//    button = formWidget.findChild("CreateBlock");
//    button.setDefaultAction(RGuiAction.getByScriptFile("scripts/Block/CreateBlock/CreateBlock.js"));
    button = formWidget.findChild("CloseBlock");
    button.setDefaultAction(RGuiAction.getByScriptFile("scripts/Block/EditMainDrawing/EditMainDrawing.js"));
    
    var dock = new RDockWidget(qsTr("Block List"), appWin);
    dock.objectName = "BlockListDock";
    dock.setWidget(formWidget);
    appWin.addDockWidget(Qt.RightDockWidgetArea, dock);

    dock.shown.connect(function() { action.setChecked(true); });
    dock.hidden.connect(function() { action.setChecked(false); });

    dock.visible = false;
};
