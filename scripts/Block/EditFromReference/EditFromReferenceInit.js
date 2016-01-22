function init(basePath) {
    var action = new RGuiAction(qsTranslate("EditFromReference", "E&dit Block from Reference"), RMainWindowQt.getMainWindow());
    action.setToolTip(qsTranslate("EditFromReference", "Edit block based on chosen block reference"));
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EditFromReference.js");
    action.setIcon(basePath + "/EditFromReference.svg");
    action.setDefaultShortcut(new QKeySequence("b,d"));
    action.setDefaultCommands(["blockeditfromreference", "bd"]);
    action.setGroupSortOrder(14350);
    action.setSortOrder(300);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
