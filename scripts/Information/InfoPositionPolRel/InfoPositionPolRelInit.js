function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoPositionPolRel", "Relative P&olar Position"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoPositionPolRel.js");
    action.setIcon(basePath + "/InfoPositionPolRel.svg");
    action.setDefaultShortcut(new QKeySequence("i,t"));
    action.setDefaultCommands([ "infopospolrel", "it" ]);
    action.setGroupSortOrder(16100);
    action.setSortOrder(400);
    action.setWidgetNames(["InformationMenu", "InformationToolBar", "InformationToolsPanel", "InformationMatrixPanel"]);
}
