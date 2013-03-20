function init(basePath) {
    var action = new RGuiAction(qsTranslate("Bevel", "&Chamfer / Bevel"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Bevel.js");
    action.setIcon(basePath + "/Bevel.svg");
    action.setDefaultShortcut(new QKeySequence("c,h"));
    action.setDefaultCommands(["bevel", "chamfer", "ch"]);
    action.setSortOrder(2000);
    EAction.addGuiActionTo(action, Modify, true, true, true, true);
}
