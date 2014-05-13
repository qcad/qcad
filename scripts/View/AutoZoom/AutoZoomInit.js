function init(basePath) {
    var action = new RGuiAction(qsTranslate("AutoZoom", "&Auto Zoom"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/AutoZoom.js");
    action.setIcon(basePath + "/AutoZoom.svg");
    action.setDefaultShortcut(new QKeySequence("z,a"));
    action.setDefaultCommands(["zoomauto", "za"]);
    action.setSortOrder(300);
    action.setNoState();
    EAction.addGuiActionTo(action, View, true, true, false);
}
