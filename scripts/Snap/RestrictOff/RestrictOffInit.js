function init(basePath) {
    var action = new RGuiAction(qsTranslate("RestrictOff", "Restrictions &Off"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RestrictOff.js");
    action.setIcon(basePath + "/RestrictOff.svg");
    action.setDefaultShortcut(new QKeySequence("e,n"));
    action.setDefaultCommands(["restrictoff", "en"]);
    action.setGroup("snaprestrictions");
    action.setGroupDefault(true);
    action.setNoState(true);
    action.setGroupSortOrder(15600);
    action.setSortOrder(100);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
