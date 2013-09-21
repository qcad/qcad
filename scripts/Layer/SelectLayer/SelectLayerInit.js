function init(basePath) {
    var menu = Layer.getMenu();
    var action = new RGuiAction(qsTranslate("SelectLayer", "&Select Layer"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectLayer.js");
    action.setIcon(basePath + "/SelectLayer.svg");
    action.setDefaultShortcut(new QKeySequence("y,+"));
    action.setDefaultCommands(["layerselect", "selectlayer", "y+"]);
    action.setSortOrder(1000);
    EAction.addGuiActionTo(action, Layer, true, true, false, true);
}
