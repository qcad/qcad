function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoPosition", "&Position"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoPosition.js");
    action.setIcon(basePath + "/InfoPosition.svg");
    action.setDefaultShortcut(new QKeySequence("i,o"));
    action.setDefaultCommands([ "infopos", "io" ]);
    action.setGroupSortOrder(16100);
    action.setSortOrder(100);
    action.setWidgetNames(["InformationMenu", "InformationToolBar", "InformationToolsPanel", "InformationMatrixPanel"]);
}
