function init(basePath) {
    var action = new RGuiAction(qsTranslate("PreviousWindow", "&Previous"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/PreviousWindow.js");
    action.setDefaultShortcuts([
        new QKeySequence(Qt.ControlModifier + Qt.Key_Left),
        new QKeySequence("Ctrl+PgDown")
    ]);
    action.setSortOrder(600);
    EAction.addGuiActionTo(action, Window, true, false, false);
}
