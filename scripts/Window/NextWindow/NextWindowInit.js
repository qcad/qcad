function init(basePath) {
    var action = new RGuiAction(qsTranslate("NextWindow", "&Next"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/NextWindow.js");
    action.setDefaultShortcuts([
        new QKeySequence(Qt.ControlModifier + Qt.Key_Right),
        new QKeySequence("Ctrl+PgUp")
    ]);
    action.setSortOrder(500);
    EAction.addGuiActionTo(action, Window, true, false, false, true);
}
