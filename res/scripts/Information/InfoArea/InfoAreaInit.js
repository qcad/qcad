function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoArea", "Pol&ygonal Area"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoArea.js");
    action.setIcon(basePath + "/InfoArea.svg");
    action.setDefaultShortcut(new QKeySequence("i,r"));
    action.setDefaultCommands([ "infoarea", "ir" ]);
    action.setGroupSortOrder(16450);
    action.setSortOrder(100);
    action.setWidgetNames(["InformationMenu", "InformationToolBar", "InformationToolsPanel", "InformationMatrixPanel"]);
}
