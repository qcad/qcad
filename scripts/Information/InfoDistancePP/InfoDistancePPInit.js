function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoDistancePP", "Distance &Point to Point"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoDistancePP.js");
    action.setIcon(basePath + "/InfoDistancePP.svg");
    action.setDefaultShortcut(new QKeySequence("i,p"));
    action.setDefaultCommands([ "infodist", "ip" ]);
    action.setGroupSortOrder(16200);
    action.setSortOrder(100);
    action.setWidgetNames(["InformationMenu", "InformationToolBar", "InformationToolsPanel", "InformationMatrixPanel"]);
}
