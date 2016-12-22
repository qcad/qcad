function init(basePath) {
    var action = new RGuiAction(qsTranslate("ConvertUnit", "Convert Drawing &Unit"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ConvertUnit.js");
    action.setIcon(basePath + "/ConvertUnit.svg");
    action.setStatusTip(qsTranslate("ConvertUnit", "Convert drawing to a different drawing unit"));
    action.setDefaultShortcut(new QKeySequence("c,u"));
    action.setDefaultCommands(["convertunit", "cu"]);
    action.setGroupSortOrder(2650);
    action.setSortOrder(100);
    action.setWidgetNames(["EditMenu", "!EditToolBar", "EditToolsPanel", "EditMatrixPanel"]);
}
