function init(basePath) {
    var action = new RGuiAction(qsTranslate("CloseAll", "&Close All"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/CloseAll.js");
    action.setIcon(basePath + "/CloseAll.svg");
    action.setDefaultShortcut(new QKeySequence("Ctrl+Shift+W"));
    action.setGroupSortOrder(50100);
    action.setSortOrder(100);
    action.setWidgetNames(["WindowMenu", "WindowToolBar"]);
}
