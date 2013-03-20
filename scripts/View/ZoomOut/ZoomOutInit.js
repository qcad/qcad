function init(basePath) {
    var action = new RGuiAction(qsTranslate("ZoomOut", "Zoom &Out"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ZoomOut.js");
    action.setIcon(basePath + "/ZoomOut.svg");
    action.setDefaultShortcuts([
        new QKeySequence("-"),
        new QKeySequence(QKeySequence.ZoomOut)
    ]);
    action.setDefaultCommands(["zoomout"]);
    action.setSortOrder(200);
    action.setNoState();
    EAction.addGuiActionTo(action, View, true, true, false);
}
