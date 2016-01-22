function init(basePath) {
    var action = new RGuiAction(qsTranslate("RestrictHorizontal", "Restrict &Horizontally"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RestrictHorizontal.js");
    action.setIcon(basePath + "/RestrictHorizontal.svg");
    action.setDefaultShortcut(new QKeySequence("e,h"));
    action.setDefaultCommands(["restricthorizontal", "eh"]);
    action.setGroup("snaprestrictions");
    action.setNoState(true);
    action.setGroupSortOrder(15600);
    action.setSortOrder(300);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
