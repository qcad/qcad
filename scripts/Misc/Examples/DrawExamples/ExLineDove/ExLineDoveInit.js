function init(basePath) {
    var action = new RGuiAction(qsTranslate("ExLineDove", "&Dovetail Joint"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExLineDove.js");
    action.setIcon(basePath + "/ExLineDove.svg");
    action.setStatusTip(qsTranslate("ExLineDove", "Draw a dovetail joint"));
    action.setDefaultCommands(["exdovetail"]);
    action.setGroupSortOrder(73100);
    action.setSortOrder(220);
    action.setWidgetNames(["DrawExamplesMenu"]);
}
