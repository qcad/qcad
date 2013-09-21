function init(basePath) {
    var menu = Layer.getMenu();
    var action = new RGuiAction(qsTranslate("DeselectLayer", "&Deselect Layer"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DeselectLayer.js");
    action.setIcon(basePath + "/DeselectLayer.svg");
    action.setDefaultShortcut(new QKeySequence("y,d"));
    action.setDefaultCommands(["layerdeselect", "deselectlayer", "yd"]);
    action.setSortOrder(900);
    EAction.addGuiActionTo(action, Layer, true, true);
}
