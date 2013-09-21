function init(basePath) {
    var action = new RGuiAction(qsTranslate("EditLayer", "&Edit Layer"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EditLayer.js");
    action.setIcon(basePath + "/EditLayer.svg");
    action.setDefaultShortcut(new QKeySequence("y,e"));
    action.setDefaultCommands(["layeredit", "ye"]);
    action.setSortOrder(700);
    EAction.addGuiActionTo(action, Layer, true, true);
}
