function init(basePath) {
    var action = new RGuiAction(qsTranslate("ToggleStatusBar", "&Status Bar"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/ToggleStatusBar.js");
    action.setDefaultShortcut(new QKeySequence("g,s"));
    action.setSortOrder(20000);
    EAction.addGuiActionTo(action, View, true, false, false);
}
