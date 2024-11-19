function init(basePath) {
    var action = new RGuiAction(qsTranslate("HatchFromSelection", "&Hatch from Selection") + "…", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/HatchFromSelection.js");
    action.setStatusTip(qsTranslate("HatchFromSelection", "Create hatch or solid fill from selected boundary"));
    action.setDefaultShortcut(new QKeySequence("h,a"));
    action.setDefaultCommands(["hatch", "ha"]);
    action.setGroupSortOrder(11800);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawHatchMenu", "HatchToolBar", "HatchToolsPanel", "HatchMatrixPanel"]);
}
