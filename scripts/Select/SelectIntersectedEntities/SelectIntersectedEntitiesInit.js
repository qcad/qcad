function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectIntersectedEntities", "(De-)Select In&tersected Entities"),
            RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectIntersectedEntities.js");
    action.setIcon(basePath + "/SelectIntersectedEntities.svg");
    action.setStatusTip(qsTranslate("SelectIntersectedEntities", "(De-)Select all entities intersected by a line"));
    action.setDefaultShortcuts([
            new QKeySequence("t,x"),
            new QKeySequence("u,x")
        ]);
    action.setDefaultCommands(["selectintersected", "tx", "ux"]);
    action.setSortOrder(700);
    EAction.addGuiActionTo(action, Select, true, true, true);
}
