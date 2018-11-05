function init(basePath) {
    var action = new RGuiAction(qsTranslate("PointPowerCenter", "Power Center of Three Circles"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PointPowerCenter.js");
    action.setIcon(basePath + "/PointPowerCenter.svg");
    action.setGroupSortOrder(54300);
    action.setSortOrder(200);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
