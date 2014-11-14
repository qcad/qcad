function init(basePath) {
    var action = new RGuiAction(qsTranslate("ToggleStatusBar", "&Status Bar"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/ToggleStatusBar.js");
    action.setDefaultShortcut(new QKeySequence("g,s"));
    action.setGroupSortOrder(3800);
    action.setSortOrder(200);
    action.setWidgetNames(["ViewMenu"]);
}
