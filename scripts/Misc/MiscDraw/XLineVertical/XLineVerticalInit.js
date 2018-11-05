function init(basePath) {
    var action = new RGuiAction(qsTranslate("XLineVertical", "&Vertical Construction Line"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/XLineVertical.js");
    action.setIcon(basePath + "/XLineVertical.svg");
    action.setStatusTip(qsTranslate("XLineVertical", "Draw vertical construction line"));
    action.setDefaultShortcut(new QKeySequence("x,v"));
    action.setDefaultCommands(["xlinevertical", "xv"]);
    action.setGroupSortOrder(54050);
    action.setSortOrder(200);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
