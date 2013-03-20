function init(basePath) {
    var action = new RGuiAction(qsTranslate("Lengthen", "&Lengthen / Shorten"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Lengthen.js");
    action.setIcon(basePath + "/Lengthen.svg");
    action.setDefaultShortcut(new QKeySequence("l,e"));
    action.setDefaultCommands(["lengthen", "shorten", "trimamount", "le"]);
    action.setSortOrder(1200);
    EAction.addGuiActionTo(action, Modify, true, true, true);
}
