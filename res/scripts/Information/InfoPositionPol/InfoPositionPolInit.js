function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoPositionPol", "&Polar Position"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoPositionPol.js");
    action.setIcon(basePath + "/InfoPositionPol.svg");
    action.setDefaultShortcut(new QKeySequence("i,l"));
    action.setDefaultCommands([ "infopospol", "il" ]);
    action.setGroupSortOrder(16100);
    action.setSortOrder(300);
    action.setWidgetNames(["InformationMenu", "InformationToolBar", "InformationToolsPanel", "InformationMatrixPanel"]);
}
