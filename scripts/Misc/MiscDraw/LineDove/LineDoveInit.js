function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineDove", "&Dovetail joint"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineDove.js");
    action.setIcon(basePath + "/LineDove.svg");
    action.setStatusTip(qsTranslate("LineDove", "Draw a dovetail joint"));
    action.setDefaultCommands(["dovetail"]);
    action.setSortOrder(200);
    EAction.addGuiActionTo(action, MiscDraw, true, true);
}
