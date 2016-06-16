function init(basePath) {
    var action = new RGuiAction(qsTranslate("ExLayerFromHatches", "&Create New Layer from Hatches"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExLayerFromHatches.js");
    action.setIcon(basePath + "/ExLayerFromHatches.svg");
    action.setGroupSortOrder(78100);
    action.setSortOrder(500);
    action.setWidgetNames(["LayerExamplesMenu"]);
}
