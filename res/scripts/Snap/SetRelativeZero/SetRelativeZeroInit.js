function init(basePath) {
    var action = new RGuiAction(qsTranslate("SetRelativeZero", "Set &Relative Zero"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SetRelativeZero.js");
    action.setIcon(basePath + "/SetRelativeZero.svg");
    action.setDefaultShortcut(new QKeySequence("r,z"));
    action.setDefaultCommands(["setrelativezero", "rz"]);
    action.setGroupSortOrder(15800);
    action.setSortOrder(100);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);
}
