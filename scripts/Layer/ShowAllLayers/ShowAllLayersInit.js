function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShowAllLayers", "&Show all Layers"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShowAllLayers.js");
    action.setIcon(basePath + "/ShowAllLayers.svg");
    action.setDefaultShortcut(new QKeySequence("y,s"));
    action.setDefaultCommands(["layershowall", "ys"]);
    action.setSortOrder(10);
    EAction.addGuiActionTo(action, Layer, true, true);
}

