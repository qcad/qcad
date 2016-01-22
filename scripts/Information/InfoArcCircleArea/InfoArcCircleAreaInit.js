function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoArcCircleArea", "Arc/Circle/Ellipse Area"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoArcCircleArea.js");
    action.setIcon(basePath + "/InfoArcCircleArea.svg");
    action.setDefaultShortcut(new QKeySequence("i,c"));
    action.setDefaultCommands([ "acearea", "ic" ]);
    action.setGroupSortOrder(16450);
    action.setSortOrder(200);
    action.setWidgetNames(["InformationMenu", "InformationToolBar", "InformationToolsPanel", "InformationMatrixPanel"]);
}
