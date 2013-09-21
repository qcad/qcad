function init(basePath) {
    var menu = Layer.getMenu();
    var action = new RGuiAction(qsTranslate("DeselectLayer", "&Deselect Layer"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DeselectLayer.js");
    action.setIcon(basePath + "/DeselectLayer.svg");
    action.setDefaultShortcut(new QKeySequence("y,-"));
    action.setDefaultCommands(["layerdeselect", "deselectlayer", "y-"]);
    action.setSortOrder(1100);
    EAction.addGuiActionTo(action, Layer, true, true);
}
