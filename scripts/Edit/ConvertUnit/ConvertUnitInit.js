function init(basePath) {
    var action = new RGuiAction(qsTranslate("ConvertUnit", "Convert Drawing Units"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ConvertUnit.js");
    action.setIcon(basePath + "/ConvertUnit.svg");
    action.setStatusTip(qsTranslate("ConvertUnit", "Change drawing units"));
    action.setDefaultShortcut(new QKeySequence("c,u"));
    action.setDefaultCommands(["convertunit", "cu"]);
    action.setGroupSortOrder(2650);
    action.setSortOrder(100);
    action.setWidgetNames(["EditMenu", "!EditToolBar", "EditToolsPanel", "EditMatrixPanel"]);
}
