function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectIntersectedEntities", "(De-)Select In&tersected Entities"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectIntersectedEntities.js");
    action.setIcon(basePath + "/SelectIntersectedEntities.svg");
    action.setStatusTip(qsTranslate("SelectIntersectedEntities", "(De-)Select all entities intersected by a line"));
    action.setDefaultShortcut(new QKeySequence("t,x"));
    action.setDefaultCommands(["selectintersected", "tx", "ux"]);
    action.setGroupSortOrder(4300);
    action.setSortOrder(200);
    action.setWidgetNames(["SelectMenu", "SelectToolBar", "SelectToolsPanel", "SelectMatrixPanel"]);
}
