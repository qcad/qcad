function init(basePath) {
    if (RSettings.getQtVersion() >= 0x060000) {
        // disabled / broken on qt 6:
        return;
    }

    var action = new RGuiAction(qsTranslate("MolImport", "Leetro MOL Import..."), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/MolImport.js");
    action.setDefaultCommands( [ "molimport" ]);
    action.setGroupSortOrder(52100);
    action.setSortOrder(200);
    action.setWidgetNames(["MiscIOMenu", "MiscIOToolBar", "MiscIOToolsPanel"]);
}
