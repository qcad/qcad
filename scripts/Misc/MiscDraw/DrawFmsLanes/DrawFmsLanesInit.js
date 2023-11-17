function init(basePath) {
    var action = new RGuiAction(qsTranslate("DrawFmsLanes", "Draw &Fms Lanes"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DrawFmsLanes.js");
    action.setStatusTip(qsTranslate("DrawFmsLanes", "Draw FMS Lanes (ribs)"));
    action.setDefaultShortcut(new QKeySequence("p,f"));
    action.setDefaultCommands(["fms_lanes", "pf"]);
    action.setGroupSortOrder(54250);
    action.setSortOrder(350);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
