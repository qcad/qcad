function init(basePath) {
    var action = new RGuiAction(qsTranslate("DeselectAll", "&Deselect All"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DeselectAll.js");
    action.setIcon(basePath + "/DeselectAll.svg");
    action.setStatusTip(qsTranslate("DeselectAll", "Deselect all entities"));
    action.setDefaultShortcuts([
        new QKeySequence("t,n"),
        new QKeySequence(Qt.ControlModifier + Qt.Key_K),
        new QKeySequence(Qt.ControlModifier + Qt.Key_D),
        new QKeySequence(Qt.ControlModifier + Qt.ShiftModifier + Qt.Key_A)
    ]);
    action.setDefaultCommands(["deselectall", "tn"]);
    action.setNoState();
    action.setGroupSortOrder(4100);
    action.setSortOrder(100);
    action.setWidgetNames(["SelectMenu", "SelectToolBar", "SelectToolsPanel", "SelectMatrixPanel"]);
}
