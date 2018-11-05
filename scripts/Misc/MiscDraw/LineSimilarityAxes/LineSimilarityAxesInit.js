function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineSimilarityAxes", "Similarity Axes of 3 Circles"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineSimilarityAxes.js");
    action.setIcon(basePath + "/LineSimilarityAxes.svg");
    action.setGroupSortOrder(54400);
    action.setSortOrder(200);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
