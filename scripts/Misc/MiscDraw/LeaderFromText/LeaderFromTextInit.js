function init(basePath) {
    var action = new RGuiAction(qsTranslate("LeaderFromText", "&Leader from Selected Text"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LeaderFromText.js");
    action.setDefaultShortcut(new QKeySequence("T,2,L"));
    action.setDefaultCommands(["LeaderFromText", "lftxt"]);
    action.setGroupSortOrder(54100);
    action.setSortOrder(401);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
