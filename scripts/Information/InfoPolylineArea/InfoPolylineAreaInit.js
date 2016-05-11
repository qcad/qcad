function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoPolylineArea", "Polyl&ine Area"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoPolylineArea.js");
    action.setIcon(basePath + "/InfoPolylineArea.svg");
    action.setDefaultShortcut(new QKeySequence("i,i"));
    action.setDefaultCommands([ "infopolylinearea", "ii" ]);
    action.setGroupSortOrder(16450);
    action.setSortOrder(300);
    action.setWidgetNames(["InformationMenu", "InformationToolBar", "InformationToolsPanel", "InformationMatrixPanel"]);
}
