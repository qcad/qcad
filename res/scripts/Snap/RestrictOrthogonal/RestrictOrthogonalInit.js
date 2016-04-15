function init(basePath) {
    var action = new RGuiAction(qsTranslate("RestrictOrthogonal", "Restrict &Orthogonally"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RestrictOrthogonal.js");
    action.setIcon(basePath + "/RestrictOrthogonal.svg");
    action.setDefaultShortcut(new QKeySequence("e,o"));
    action.setDefaultCommands(["restrictorthogonal", "eo"]);
    action.setGroup("snaprestrictions");
    action.setNoState(true);
    action.setGroupSortOrder(15600);
    action.setSortOrder(200);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
