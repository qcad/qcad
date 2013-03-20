function init(basePath) {
    var action = new RGuiAction(qsTranslate("WindowZoom", "&Window Zoom"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/WindowZoom.js");
    action.setIcon(basePath + "/WindowZoom.svg");
    action.setDefaultShortcut(new QKeySequence("z,w"));
    action.setDefaultCommands(["zoomwindow", "zw"]);
    action.setSortOrder(600);
    EAction.addGuiActionTo(action, View, true, true, false);
}
