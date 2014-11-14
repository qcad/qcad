function init(basePath) {
    var action = new RGuiAction(qsTranslate("RestrictAngleLength", "Restrict &Angle or Length"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RestrictAngleLength.js");
    action.setIcon(basePath + "/RestrictAngleLength.svg");
    action.setDefaultShortcut(new QKeySequence("e,g"));
    action.setDefaultCommands(["restrictanglelength", "eg"]);
    action.setGroup("snaprestrictions");
    action.setNoState(true);
    action.setGroupSortOrder(15600);
    action.setSortOrder(500);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
