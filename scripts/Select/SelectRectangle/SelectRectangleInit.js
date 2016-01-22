function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectRectangle", "(De-)Select &Rectangular Area"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectRectangle.js");
    action.setIcon(basePath + "/SelectRectangle.svg");
    action.setStatusTip(qsTranslate("SelectRectangle", "(De-)Select all entities inside a rectangle"));
    action.setDefaultShortcuts([ new QKeySequence("t,r"), new QKeySequence("t,w") ]);
    action.setDefaultCommands(["selectrectangle", "selectwindow", "tr", "tw"]);
    action.setGroupSortOrder(4200);
    action.setSortOrder(100);
    action.setWidgetNames(["SelectMenu", "SelectToolBar", "SelectToolsPanel", "SelectMatrixPanel"]);
}
