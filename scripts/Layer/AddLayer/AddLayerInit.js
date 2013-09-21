function init(basePath) {
    var action = new RGuiAction(qsTranslate("AddLayer", "&Add Layer"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/AddLayer.js");
    action.setIcon(basePath + "/AddLayer.svg");
    action.setDefaultShortcut(new QKeySequence("y,a"));
    action.setDefaultCommands(["layeradd", "ya"]);
    action.setSortOrder(500);
    EAction.addGuiActionTo(action, Layer, true, true, false, true);
}
