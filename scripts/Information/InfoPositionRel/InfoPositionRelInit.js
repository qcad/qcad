function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoPositionRel", "&Relative Position"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoPositionRel.js");
    action.setIcon(basePath + "/InfoPositionRel.svg");
    action.setDefaultShortcut(new QKeySequence("i,v"));
    action.setDefaultCommands([ "infoposrel", "iv" ]);
    action.setGroupSortOrder(16100);
    action.setSortOrder(200);
    action.setWidgetNames(["InformationMenu", "InformationToolBar", "InformationToolsPanel", "InformationMatrixPanel"]);
}
