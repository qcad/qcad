function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineDove2", "&Dovetail Joint from 2 Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineDove2.js");
    action.setIcon(basePath + "/LineDove2.svg");
    action.setStatusTip(qsTranslate("LineDove2", "Draw a dovetail joint"));
    action.setDefaultCommands(["dovetail"]);
    action.setGroupSortOrder(54200);
    action.setSortOrder(220);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel"]);
}
