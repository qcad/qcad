function init(basePath) {
    var action = new RGuiAction(qsTranslate("MolImport", "Leetro MOL Import..."), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/MolImport.js");
    action.setIcon(basePath + "/MolImport.svg");
    action.setDefaultCommands( [ "molimport" ]);
    action.setSortOrder(2360);
    //action.setNoState();
    EAction.addGuiActionTo(action, MiscIO, true, false, false, false);
}
