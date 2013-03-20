function init(basePath) {
    var action = new RGuiAction(qsTranslate("ToggleBlockVisibility", "&Toggle Visibility"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ToggleBlockVisibility.js");
    action.setIcon(basePath + "/ToggleBlockVisibility.svg");
    action.setDefaultShortcut(new QKeySequence("b,v"));
    action.setDefaultCommands(["blocktogglevisibility", "bv"]);
    action.setSortOrder(5);
    EAction.addGuiActionTo(action, Block, true, true);
}
