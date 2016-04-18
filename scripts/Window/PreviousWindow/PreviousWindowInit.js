function init(basePath) {
    var action = new RGuiAction(qsTranslate("PreviousWindow", "&Previous"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/PreviousWindow.js");
    action.setIcon(basePath + "/PreviousWindow.svg");
    action.setDefaultShortcuts([
        new QKeySequence(Qt.ControlModifier + Qt.Key_Left),
        new QKeySequence("Ctrl+PgDown")
    ]);
    action.setGroupSortOrder(50200);
    action.setSortOrder(200);
    action.setWidgetNames(["WindowMenu", "WindowToolBar"]);
}
