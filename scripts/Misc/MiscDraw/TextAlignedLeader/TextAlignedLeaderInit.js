function init(basePath) {
    var action = new RGuiAction(qsTranslate("TextAlignedLeader", "&Text Aligned Leader"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/TextAlignedLeader.js");
    action.setDefaultShortcut(new QKeySequence("2,T"));
    action.setDefaultCommands(["textalignedleader", "tal"]);
    action.setGroupSortOrder(54100);
    action.setSortOrder(400);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
