function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineSimilarityAxes", "Similiarity axes of three circles"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineSimilarityAxes.js");
    //action.setIcon(basePath + "/LineSimilarityAxes.svg");
    action.setSortOrder(200);
    EAction.addGuiActionTo(action, MiscDraw, true, true);
}
