/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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

include("../Widgets.js");
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
        adapter.blocksCleared.connect(this, "clearBlocks");
    }

    this.itemDoubleClicked.connect(this, "editBlock");
    this.itemColumnClicked.connect(this, "itemColumnClickedSlot");
    this.itemSelectionChanged.connect(this, "blockActivated");
    this.basePath = includeBasePath;
}

RBlockListQt.prototype = new RTreeWidget();

RBlockListQt.getBlockList = function() {
    var appWin = EAction.getMainWindow();
    return appWin.findChild("BlockList");
};

/**
 * Add an additional action to be used in the context menu.
 * Can be used by plugins to hook into the block list context menu.
 */
RBlockListQt.addContextMenuScriptFile = function(scriptFile) {
    var blockList = RBlockListQt.getBlockList();
    if (isNull(blockList)) {
        return;
    }

    var scriptFiles = RBlockListQt.getContextMenuScriptFiles();
    scriptFiles.push(scriptFile);
    blockList.setProperty("ContextMenuScriptFiles", scriptFiles);
};

RBlockListQt.getContextMenuScriptFiles = function() {
    var blockList = RBlockListQt.getBlockList();
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

    // add addtional context menu actions provided by plugins:
    var scriptFiles = RBlockListQt.getContextMenuScriptFiles();
    for (var i=0; i<scriptFiles.length; i++) {
        var scriptFile = scriptFiles[i];
        var a = RGuiAction.getByScriptFile(scriptFile);
        if (!isNull(a)) {
            a.addToMenu(menu);
        }
    }

    menu.exec(QCursor.pos());

    e.ignore();
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

RBlockListQt.prototype.sortBlockNames = function(blockNames) {
    var doc = this.di.getDocument();

    //var self = this;
    blockNames.sort(function(a, b) {
        var blockA = doc.queryBlock(a);
        var blockB = doc.queryBlock(b);
        if (isNull(blockA) || isNull(blockB)) {
            return 0;
        }

        // model space always first:
        if (blockA.getName()===RBlock.modelSpaceName) {
            return -1;
        }
        if (blockB.getName()===RBlock.modelSpaceName) {
            return 1;
        }

        // layouts always before other blocks:
        var blockAIsLayout = blockA.isLayout();
        var blockBIsLayout = blockB.isLayout();
        if (blockAIsLayout && !blockBIsLayout) {
            return -1;
        }
        if (!blockAIsLayout && blockBIsLayout) {
            return 1;
        }

        // sort among layouts by tab order:
        if (blockAIsLayout && blockBIsLayout) {
            var layoutAId = blockA.getLayoutId();
            var layoutBId = blockB.getLayoutId();
            var layoutA = doc.queryLayout(layoutAId);
            var layoutB = doc.queryLayout(layoutBId);
            if (!isNull(layoutA) && !isNull(layoutB)) {
                return layoutA.getTabOrder() - layoutB.getTabOrder();
            }
        }

        // sort by layout name or block name (ignoring * at start):
        var blockTitleA = RBlockListQt.getBlockTitle(blockA);
        var blockTitleB = RBlockListQt.getBlockTitle(blockB);
        if (blockTitleA.startsWith("*")) {
            blockTitleA = blockTitleA.substring(1);
        }
        if (blockTitleB.startsWith("*")) {
            blockTitleB = blockTitleB.substring(1);
        }

        return Array.alphaNumericalSorter(blockTitleA, blockTitleB);
    });
};

/**
 * Called when blocks are addded, edited or deleted. Updates the block list.
 */
RBlockListQt.prototype.updateBlocks = function(documentInterface) {
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

    var blockNameCandidates = doc.getBlockNames();

    var i;

    // filter block names:
    var blockNames = [];
    for (i=0; i<blockNameCandidates.length; i++) {
        var blockNameCandidate = blockNameCandidates[i];
        var blockCandidate = doc.queryBlockDirect(blockNameCandidate);
        if (blockCandidate.isNull()) {
            continue;
        }

        if (!this.filter(blockCandidate)) {
            continue;
        }

        blockNames.push(blockNameCandidate);
    }

    this.sortBlockNames(blockNames);

    var currentBlockId = doc.getCurrentBlockId();
    var currentItem = undefined;
    var selectedItem = undefined;
    for (i=0; i<blockNames.length; ++i) {
        var blockName = blockNames[i];
        var block = doc.queryBlockDirect(blockName);
        if (block.isNull()) {
            continue;
        }

        var item = this.createBlockItem(block);
        this.addTopLevelItem(item);
        if (blockName===selectedBlockName) {
            selectedItem = item;
        }

        if (currentBlockId===block.getId()) {
            currentItem = item;
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
    var iconName = autoIconPath(BlockList.includeBasePath + "/Visible%1.svg".arg(Number(!block.isFrozen())));
    item.setIcon(BlockList.colVisible, new QIcon(iconName));

    var doc = this.di.getDocument();
    var currentBlockId = doc.getCurrentBlockId();
    iconName = autoIconPath(BlockList.includeBasePath + "/Edit%1.svg".arg(Number(block.getId()===currentBlockId)));
    item.setIcon(BlockList.colEdit, new QIcon(iconName));
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
        this.updateBlocks(this.di);
    } else if (column===BlockList.colEdit) {
        this.setCurrentItem(item);
        this.editBlock();
        this.updateBlocks(this.di);
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
    this.enableActions(insertable);
};

/**
 * \return The block name for the given tree widget item.
 */
RBlockListQt.prototype.getBlockName = function(item) {
    return item.data(BlockList.colName, Qt.UserRole);
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
