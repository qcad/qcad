function init(basePath) {
    var action = new RGuiAction(qsTranslate("VideoTutorials", "QCAD &Video Tutorials"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/VideoTutorials.js");
    action.setNoState();
    action.setGroupSortOrder(110200);
    action.setSortOrder(150);
    action.setWidgetNames(["HelpMenu", "!HelpToolBar"]);
}
