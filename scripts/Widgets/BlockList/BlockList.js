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

include("scripts/Widgets/Widgets.js");
include("scripts/WidgetFactory.js");

/**
 * Block list widget class (QWidget).
 */
function RBlockListQt(parent, addListener, showHeader) {
    RTreeWidget.call(this, parent);

    if (isNull(addListener)) {
        addListener = true;
    }
    if (isNull(showHeader)) {
        showHeader = false;
    }

    this.di = undefined;

    if (!showHeader) {
        this.header().close();
    }
    this.iconSize = new QSize(16, 16);
    this.indentation = 0;
    this.rootIsDecorated = false;

    this.setSelectableColumn(2);

    this.columnCount = 3;

    this.header().stretchLastSection = false;
    if (RSettings.isQt(5)) {
        this.header().minimumSectionSize = 22;
        this.header().setSectionResizeMode(BlockList.colName, QHeaderView.Stretch);
        this.header().setSectionResizeMode(BlockList.colVisible, QHeaderView.Interactive);
        this.header().setSectionResizeMode(BlockList.colEdit, QHeaderView.Interactive);
    }
    else {
        this.header().setResizeMode(BlockList.colName, QHeaderView.Stretch);
        this.header().setResizeMode(BlockList.colVisible, QHeaderView.Interactive);
        this.header().setResizeMode(BlockList.colEdit, QHeaderView.Interactive);
    }

    this.setColumnWidth(BlockList.colVisible, 22);
    this.setColumnWidth(BlockList.colEdit, 22);

    if (addListener) {
        var appWin = EAction.getMainWindow();
        var adapter = new RBlockListenerAdapter();
        appWin.addBlockListener(adapter);
        adapter.blocksUpdated.connect(this, "updateBlocks");
        adapter.currentBlockSet.connect(this, "updateCurrentBlock");
        adapter.blocksCleared.connect(this, "clearBlocks");
    }

    this.itemDoubleClicked.connect(this, "editBlock");
    this.itemColumnClicked.connect(this, "itemColumnClickedSlot");
    this.itemSelectionChanged.connect(this, "blockActivated");
    this.basePath = includeBasePath;

    this.currentItem = undefined;

}

RBlockListQt.prototype = new RTreeWidget();

RBlockListQt.getWidget = function() {
    var appWin = EAction.getMainWindow();
    return appWin.findChild("BlockList");
};

/**
 * Add an additional action to be used in the context menu.
 * Can be used by plugins to hook into the block list context menu.
 */
RBlockListQt.addContextMenuScriptFile = function(scriptFile, blockList) {
    //var blockList = RBlockListQt.getWidget();
    if (isNull(blockList)) {
        return;
    }

    var scriptFiles = RBlockListQt.getContextMenuScriptFiles(blockList);
    scriptFiles.push(scriptFile);
    blockList.setProperty("ContextMenuScriptFiles", scriptFiles);
};

RBlockListQt.getContextMenuScriptFiles = function(blockList) {
    //var blockList = RBlockListQt.getWidget();
    if (isNull(blockList)) {
        return [];
    }

    var scriptFiles = blockList.property("ContextMenuScriptFiles");
    if (isNull(scriptFiles)) {
        scriptFiles = [];
    }
    return scriptFiles;
};

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

    RBlockListQt.complementContextMenu(menu, RBlockListQt.getWidget());

    menu.exec(QCursor.pos());

    e.ignore();
};

RBlockListQt.complementContextMenu = function(menu, blockListWidget) {
    // add addtional context menu actions provided by plugins:
    var scriptFiles = RBlockListQt.getContextMenuScriptFiles(blockListWidget);
    for (var i=0; i<scriptFiles.length; i++) {
        var scriptFile = scriptFiles[i];
        var a = RGuiAction.getByScriptFile(scriptFile);
        if (!isNull(a)) {
            a.addToMenu(menu);
        }
    }
};

RBlockListQt.prototype.filter = function(block) {
    var hideInternal = RSettings.getBoolValue("BlockList/HideInternalBlocks", false);

    if (hideInternal===true) {
        var blockNameLower = block.getName().toLowerCase();

        // hide anonymous blocks:
        if (blockNameLower.startsWith("a$c") &&
            blockNameLower.length===13) {
            return false;
        }

        // hide blocks tagged as resources
        // such blocks may be added by add-ons to provide
        // additional resources such as CAM tools, etc.
        if (block.hasCustomProperty("QCAD", "ResourceFlag")) {
            return false;
        }
    }
    return true;
};

RBlockListQt.prototype.updateCurrentBlock = function(documentInterface) {
    var doc = documentInterface.getDocument();

    // find item which was representing the current block before:
    if (!isNull(this.currentItem)) {
        // clear pen icon from item:
        //var blockName = this.currentItem.data(BlockList.colName, Qt.UserRole);
        //var block = doc.queryBlock(blockName);
        //this.updateItemIcons(this.currentItem, block);
        this.currentItem.setIcon(BlockList.colEdit, BlockList.iconEdit[0]);
    }

    // find item of current block:
    this.currentItem = RBlockListQt.getItem(this, doc.getCurrentBlockName());
    //for (var i=0; i<this.topLevelItemCount; i++) {
    //    var item = this.topLevelItem(i);
    //}

    // add pen icon to item:
    if (!isNull(this.currentItem)) {
        this.currentItem.setIcon(BlockList.colEdit, BlockList.iconEdit[1]);
    }
};

/**
 * Called when blocks are addded, edited or deleted. Updates the block list.
 */
RBlockListQt.prototype.updateBlocks = function(documentInterface) {
    this.currentItem = undefined;

    this.di = documentInterface;

    var pos = this.verticalScrollBar().sliderPosition;
    var selectedBlockName = undefined;
    var selectedItems = this.selectedItems();
    if (selectedItems.length===1) {
        selectedBlockName = selectedItems[0].data(BlockList.colName, Qt.UserRole);
    }

    this.clear();
    if (isNull(documentInterface)) {
        return;
    }

    var doc = documentInterface.getDocument();

    var blockCandidateIds = doc.queryAllBlocks();

    var i;

    // filter block names:
    var blockIds = [];
    for (i=0; i<blockCandidateIds.length; i++) {
        var blockCandidateId = blockCandidateIds[i];
        var blockCandidate = doc.queryBlockDirect(blockCandidateId);
        if (blockCandidate.isNull()) {
            continue;
        }

        if (!this.filter(blockCandidate)) {
            continue;
        }

        blockIds.push(blockCandidateId);
    }

    blockIds = this.sortBlocks(doc, blockIds);

    var currentBlockId = doc.getCurrentBlockId();
    var selectedItem = undefined;
    for (i=0; i<blockIds.length; ++i) {
        var blockId = blockIds[i];
        var block = doc.queryBlockDirect(blockId);
        if (block.isNull()) {
            continue;
        }

        var blockName = block.getName();

        var item = this.createBlockItem(block);
        this.addTopLevelItem(item);
        if (blockName===selectedBlockName) {
            selectedItem = item;
        }

        if (currentBlockId===block.getId()) {
            this.currentItem = item;
        }
    }

    this.verticalScrollBar().sliderPosition = pos;

    if (!isNull(selectedItem)) {
        this.blockSignals(true);
        selectedItem.setSelected(true);
        this.blockSignals(false);
    }

    this.blockActivated();
};

RBlockListQt.prototype.sortBlocks = function(doc, blockIds) {
    return doc.sortBlocks(blockIds);
};

RBlockListQt.getBlockTitle = function(block) {
    var title = block.getName();
    var layoutName = block.getLayoutName();
    if (layoutName.length>0) {
        title = layoutName + " (" + title + ")";
    }
    return title;
};

RBlockListQt.prototype.createBlockItem = function(block) {
    var item = new QTreeWidgetItem();
    var name = block.getName();

    var flags = new Qt.ItemFlags(Qt.ItemIsSelectable|Qt.ItemIsEnabled);
    item.setFlags(flags);

    var title = RBlockListQt.getBlockTitle(block);

    item.setText(BlockList.colName, title);

    item.setData(BlockList.colName, Qt.UserRole, name);

    this.updateItemIcons(item, block);

    return item;
};

RBlockListQt.prototype.updateItemIcons = function(item, block) {
    //var iconName = autoIconPath(BlockList.includeBasePath + "/Visible%1.svg".arg(Number(!block.isFrozen())));
    item.setIcon(BlockList.colVisible, BlockList.iconVisible[Number(!block.isFrozen())]);

    var doc = this.di.getDocument();
    var currentBlockId = doc.getCurrentBlockId();
    //iconName = autoIconPath(BlockList.includeBasePath + "/Edit%1.svg".arg(Number(block.getId()===currentBlockId)));
    item.setIcon(BlockList.colEdit, BlockList.iconEdit[Number(block.getId()===currentBlockId)]);
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
RBlockListQt.prototype.itemColumnClickedSlot = function(item, column) {
    if (isNull(this.di) || isNull(item)) {
        return;
    }

    var doc = this.di.getDocument();
    var block = doc.queryBlock(this.getBlockName(item));
    if (block.isNull()) {
        return;
    }

    if (column===BlockList.colVisible) {
        block.setFrozen(!block.isFrozen());
        var op = new RModifyObjectOperation(block, false);
        this.di.applyOperation(op);
        //this.updateBlocks(this.di);
    } else if (column===BlockList.colEdit) {
        this.setCurrentItem(item);
        this.editBlock();
        //this.updateBlocks(this.di);
    }

    this.blockActivated();
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

    var blockName = this.getBlockName(item);

    // prevent removal or insertion of current block:
    var insertable = currentBlock.getName().toLowerCase()!==blockName.toLowerCase() && !blockName.startsWith("*");
    var renamable = document.getBlockId(blockName)!==document.getModelSpaceBlockId();
    var removable = document.getBlockId(blockName)!==document.getModelSpaceBlockId();
    this.enableActions(insertable, renamable, removable);
};

/**
 * \return The block name for the given tree widget item.
 */
RBlockListQt.prototype.getBlockName = function(item) {
    return item.data(BlockList.colName, Qt.UserRole);
};

/**
 * \return The list item for the block with the given block name.
 */
RBlockListQt.getItem = function(widget, blockName) {
    for (var i=0; i<widget.topLevelItemCount; i++) {
        var item = widget.topLevelItem(i);
        if (item.data(BlockList.colName, Qt.UserRole)===blockName) {
            return item;
        }
    }
    return undefined;
};

/**
 * Enable / disable buttons that edit, remove or insert the active block.
 */
RBlockListQt.prototype.enableActions = function(insertable, renamable, removable) {
    if (isNull(renamable)) {
        renamable = insertable;
    }
    if (isNull(removable)) {
        removable = insertable;
    }

    var override;
    if (insertable===true) {
        override = 1;
    }
    else {
        override = 0;
    }

    var action;
    action = RGuiAction.getByScriptFile("scripts/Block/ToggleBlockVisibility/ToggleBlockVisibility.js");
    action.setEnabledOverride(insertable, override);
    action = RGuiAction.getByScriptFile("scripts/Block/InsertBlock/InsertBlock.js");
    action.setEnabledOverride(insertable, override);

    action = RGuiAction.getByScriptFile("scripts/Block/RemoveBlock/RemoveBlock.js");
    action.setEnabledOverride(removable, removable ? 1 : 0);

    action = RGuiAction.getByScriptFile("scripts/Block/RenameBlock/RenameBlock.js");
    action.setEnabledOverride(renamable, renamable ? 1 : 0);
};

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
};



/**
 * \class BlockList
 * \brief Initializes the block list widget (RBlockListQt).
 * \ingroup ecma_widgets
 */
function BlockList(guiAction) {
    Widgets.call(this, guiAction);
}

BlockList.prototype = new Widgets();
BlockList.includeBasePath = includeBasePath;

BlockList.colVisible=0;
BlockList.colEdit=1;
BlockList.colName=2;

BlockList.iconVisible = [
    new QIcon(autoIconPath(BlockList.includeBasePath + "/Visible0.svg")),
    new QIcon(autoIconPath(BlockList.includeBasePath + "/Visible1.svg"))
];

BlockList.iconEdit = [
    new QIcon(autoIconPath(BlockList.includeBasePath + "/Edit0.svg")),
    new QIcon(autoIconPath(BlockList.includeBasePath + "/Edit1.svg"))
];

BlockList.getPreferencesCategory = function() {
    return [ qsTr("Widgets"), qsTr("Block List") ];
};

BlockList.applyPreferences = function(doc, mdiChild) {
    var appWin = RMainWindowQt.getMainWindow();
    appWin.notifyBlockListeners(EAction.getDocumentInterface());

    var blockList = appWin.findChild("BlockList");
    WidgetFactory.initList(blockList, "BlockList");
};

/**
 * \return Active item.
 */
BlockList.getActiveItem = function() {
    var appWin = RMainWindowQt.getMainWindow();
    var blockList = appWin.findChild("BlockList");
    if (isNull(blockList)) {
        return undefined;
    }

    return blockList.getActiveItem();
};

/**
 * Shows / hides the block list.
 */
BlockList.prototype.beginEvent = function() {
    Widgets.prototype.beginEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("BlockListDock");
    if (!QCoreApplication.arguments().contains("-no-show")) {
        dock.visible = !dock.visible;
        if (dock.visible) dock.raise();
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
    action.setDefaultCommands(["gb"]);
    action.setGroupSortOrder(3600);
    action.setSortOrder(200);
    action.setWidgetNames(["ViewMenu", "WidgetsToolBar", "ViewToolsPanel", "WidgetsMatrixPanel"]);

    var formWidget = WidgetFactory.createWidget(basePath, "BlockList.ui");
    var layout = formWidget.findChild("verticalLayout");
    var blockList = new RBlockListQt(layout);
    blockList.objectName = "BlockList";
    layout.addWidget(blockList, 1, 0);

    RSettings.setValue("BlockList/AlternatingRowColor", new RColor(230, 235, 250), false);
    WidgetFactory.initList(blockList, "BlockList");

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
    //dock.setProperty("Category", Widgets.getListContextMenuCategory());
    dock.setWidget(formWidget);
    appWin.addDockWidget(Qt.RightDockWidgetArea, dock);

    dock.shown.connect(function() { action.setChecked(true); });
    dock.hidden.connect(function() { action.setChecked(false); });

    dock.visible = false;
};
