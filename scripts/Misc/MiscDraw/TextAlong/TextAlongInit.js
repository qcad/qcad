function init(basePath) {
    var action = new RGuiAction(qsTranslate("TextAlong", "&Text Along Entity"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/TextAlong.js");
    action.setIcon(basePath + "/TextAlong.svg");
    action.setStatusTip(qsTranslate("TextAlong", "Draw text along an entity"));
    action.setDefaultShortcut(new QKeySequence("t,g"));
    action.setDefaultCommands(["textalong", "tg"]);
    action.setGroupSortOrder(54100);
    action.setSortOrder(300);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
