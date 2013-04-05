function init(basePath) {
    var action = new RGuiAction(qsTranslate("ReportBug", "Report &Bug"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ReportBug.js");
    action.setSortOrder(700);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false);
}
