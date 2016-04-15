function init(basePath) {
    var action = new RGuiAction(qsTranslate("DeselectBlockReferences", "&Deselect Block References"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DeselectBlockReferences.js");
    action.setIcon(basePath + "/DeselectBlockReferences.svg");
    action.setDefaultShortcut(new QKeySequence("b,-"));
    action.setDefaultCommands(["blockdeselect", "deselectblock", "b-"]);
    action.setGroupSortOrder(14400);
    action.setSortOrder(200);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
