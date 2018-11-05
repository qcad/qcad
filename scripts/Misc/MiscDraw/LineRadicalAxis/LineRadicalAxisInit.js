function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineRadicalAxis", "Radical Axis of 2 Circles"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineRadicalAxis.js");
    action.setIcon(basePath + "/LineRadicalAxis.svg");
    action.setGroupSortOrder(54400);
    action.setSortOrder(100);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
