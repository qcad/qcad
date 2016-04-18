function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectContour", "(De-)Select &Contour"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectContour.js");
    action.setIcon(basePath + "/SelectContour.svg");
    action.setStatusTip(qsTranslate("SelectContour", "(De-)Select connected entities"));
    action.setDefaultShortcut(new QKeySequence("t,c"));
    action.setDefaultCommands(["selectcontour", "tc"]);
    action.setGroupSortOrder(4300);
    action.setSortOrder(100);
    action.setWidgetNames(["SelectMenu", "SelectToolBar", "SelectToolsPanel", "SelectMatrixPanel"]);
}
