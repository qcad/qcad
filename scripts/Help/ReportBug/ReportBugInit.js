function init(basePath) {
    var action = new RGuiAction(qsTranslate("ReportBug", "Report &Bug"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ReportBug.js");
    // action.setIcon(basePath + "/ReportBug.svg");
    action.setSortOrder(300);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false);
}
