function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineDove", "&Dovetail Joint from 2 Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineDove.js");
    action.setStatusTip(qsTranslate("LineDove", "Draw a dovetail joint"));
    action.setDefaultCommands(["dovetail"]);
    action.setGroupSortOrder(54200);
    action.setSortOrder(200);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
