function init(basePath) {
    var action = new RGuiAction(qsTranslate("IsoProject", "&Isometric Projection"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/IsoProject.js");
    action.setIcon(basePath + "/IsoProject.svg");
    action.setDefaultShortcut(new QKeySequence("p,j"));
    action.setDefaultCommands(["isometric", "pj"]);
    action.setGroupSortOrder(18200);
    action.setSortOrder(100);
    action.setWidgetNames(["ModifyProjectionMenu", "ProjectionToolBar", "ProjectionToolsPanel", "ProjectionMatrixPanel"]);
}
