function init(basePath) {
    var menu = Block.getMenu();
    var action = new RGuiAction(qsTranslate("DeselectBlockReferences", "&Deselect Block References"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DeselectBlockReferences.js");
    action.setIcon(basePath + "/DeselectBlockReferences.svg");
    action.setDefaultShortcut(new QKeySequence("b,-"));
    action.setDefaultCommands(["blockdeselect", "deselectblock", "b-"]);
    action.setSortOrder(2900);
    EAction.addGuiActionTo(action, Block, true, true);
}
