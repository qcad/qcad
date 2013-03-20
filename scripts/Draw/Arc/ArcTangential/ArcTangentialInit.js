function init(basePath) {
    var action = new RGuiAction(qsTranslate("ArcTangential", "&Tangentially connected"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ArcTangential.js");
    action.setIcon(basePath + "/ArcTangential.svg");
    action.setStatusTip(qsTranslate("ArcTangential", "Draw arc tangential to base entity"));
    action.setDefaultShortcut(new QKeySequence("a,n"));
    action.setDefaultCommands(["arctangential", "an"]);
    action.setSortOrder(700);
    EAction.addGuiActionTo(action, Arc, true, true, true, true);
}
