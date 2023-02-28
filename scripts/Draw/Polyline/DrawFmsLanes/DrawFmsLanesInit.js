function init(basePath) {
    var action = new RGuiAction(qsTranslate("DrawFmsLanes", "Draw &Fms Lanes"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DrawFmsLanes.js");
    action.setIcon(basePath + "/DrawFmsLanes.svg");
    action.setStatusTip(qsTranslate("DrawFmsLanes", "Draw FMS Lanes (ribs)"));
    action.setDefaultShortcut(new QKeySequence("p,f"));
    action.setDefaultCommands(["fms_lanes", "pl"]);
    action.setGroupSortOrder(11010);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawPolylineMenu", "PolylineToolBar", "PolylineToolsPanel", "PolylineMatrixPanel"]);
}
