function init(basePath) {
    var action = new RGuiAction(
        qsTranslate("ReportTranslationError", "Report &Translation Error"),
        RMainWindowQt.getMainWindow()
    );
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ReportTranslationError.js");
    action.setSortOrder(800);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false);
}
