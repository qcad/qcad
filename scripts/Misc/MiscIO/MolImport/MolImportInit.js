function init(basePath) {
    var action = new RGuiAction(qsTranslate("MolImport", "Leetro MOL Import..."), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/MolImport.js");
    action.setIcon(basePath + "/MolImport.svg");
    action.setDefaultCommands( [ "molimport" ]);
    action.setGroupSortOrder(52100);
    action.setSortOrder(200);
    action.setWidgetNames(["MiscIOMenu", "MiscIOToolBar", "MiscIOToolsPanel"]);
}
