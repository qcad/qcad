function init(basePath) {
    var action = new RGuiAction(qsTranslate("XLineHorizontal", "&Horizontal Construction Line"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/XLineHorizontal.js");
    action.setIcon(basePath + "/XLineHorizontal.svg");
    action.setStatusTip(qsTranslate("XLineHorizontal", "Draw horizontal construction line"));
    action.setDefaultShortcut(new QKeySequence("x,h"));
    action.setDefaultCommands(["xlinehorizontal", "xh"]);
    action.setGroupSortOrder(54050);
    action.setSortOrder(100);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
