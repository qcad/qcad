function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoDistanceEE", "Distance &Entity to Entity"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoDistanceEE.js");
    action.setIcon(basePath + "/InfoDistanceEE.svg");
    action.setDefaultShortcut(new QKeySequence("i,n"));
    action.setDefaultCommands([ "infodistee", "in" ]);
    action.setGroupSortOrder(16200);
    action.setSortOrder(300);
    action.setWidgetNames(["InformationMenu", "InformationToolBar", "InformationToolsPanel", "InformationMatrixPanel"]);
}
