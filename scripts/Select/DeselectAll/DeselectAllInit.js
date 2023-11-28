function init(basePath) {
    var action = new RGuiAction(qsTranslate("DeselectAll", "&Deselect All"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DeselectAll.js");
    action.setStatusTip(qsTranslate("DeselectAll", "Deselect all entities"));
    action.setDefaultShortcuts([
        new QKeySequence("t,n"),
        new QKeySequence("Ctrl+K"),
        new QKeySequence("Ctrl+D"),
        new QKeySequence("Ctrl+Shift+A")
    ]);
    action.setDefaultCommands(["deselectall", "tn"]);
    action.setNoState();
    action.setGroupSortOrder(4100);
    action.setSortOrder(100);
    action.setWidgetNames(["SelectMenu", "SelectToolBar", "SelectToolsPanel", "SelectMatrixPanel"]);
}
