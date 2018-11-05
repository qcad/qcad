function init(basePath) {
    var action = new RGuiAction(qsTranslate("PointPole", "Pole of Line and Circle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PointPole.js");
    action.setIcon(basePath + "/PointPole.svg");
    action.setGroupSortOrder(54300);
    action.setSortOrder(100);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
