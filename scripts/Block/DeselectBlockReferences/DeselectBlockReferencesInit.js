function init(basePath) {
    var action = new RGuiAction(qsTranslate("DeselectBlockReferences", "&Deselect Block References"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DeselectBlockReferences.js");
    action.setIcon(basePath + "/DeselectBlockReferences.svg");
    action.setDefaultShortcuts([
                            new QKeySequence("b,x")
                        ]);
    action.setDefaultCommands(["blockdeselect", "deselectblock", "bx"]);
    action.setGroupSortOrder(14400);
    action.setSortOrder(200);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
