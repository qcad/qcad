function init(basePath) {
    var action = new RGuiAction(qsTranslate("NextWindow", "&Next"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/NextWindow.js");
    action.setIcon(basePath + "/NextWindow.svg");
    action.setDefaultShortcuts([
        new QKeySequence(Qt.ControlModifier + Qt.Key_Right),
        new QKeySequence("Ctrl+PgUp")
    ]);
    action.setGroupSortOrder(50200);
    action.setSortOrder(100);
    action.setWidgetNames(["WindowMenu", "WindowToolBar"]);
}
