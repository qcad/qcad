function init(basePath) {
    var action = new RGuiAction(qsTranslate("PrintPreview", "Print Pre&view"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PrintPreview.js");
    action.setIcon(basePath + "/PrintPreview.svg");
    action.setDefaultShortcut(new QKeySequence(Qt.ControlModifier + Qt.ShiftModifier + Qt.Key_P));
    action.setDefaultCommands(["printpreview"]);
    action.setStatusTip(qsTranslate("PrintPreview", "Preview how current drawing would be printed"));
    action.setSortOrder(3000);
    EAction.addGuiActionTo(action, File, true, true, false, true);
}
