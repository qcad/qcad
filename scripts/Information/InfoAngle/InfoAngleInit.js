function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoAngle", "&Angle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoAngle.js");
    action.setIcon(basePath + "/InfoAngle.svg");
    action.setDefaultShortcut(new QKeySequence("i,a"));
    action.setDefaultCommands([ "infoangle", "ia" ]);
    action.setGroupSortOrder(16300);
    action.setSortOrder(100);
    action.setWidgetNames(["InformationMenu", "InformationToolBar", "InformationToolsPanel", "InformationMatrixPanel"]);
}
