function init(basePath) {
    var menu = Layer.getMenu();
    var action = new RGuiAction(qsTranslate("ToggleLayerVisibility", "&Toggle Visibility"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ToggleLayerVisibility.js");
    action.setIcon(basePath + "/ToggleLayerVisibility.svg");
    action.setDefaultShortcut(new QKeySequence("y,v"));
    action.setDefaultCommands(["layertogglevisibility", "yv"]);
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, Layer, true, true);
}
