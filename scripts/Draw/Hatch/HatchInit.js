function init(basePath) {
    var action = new RGuiAction(qsTranslate("Hatch", "&Hatch"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Hatch.js");
    action.setIcon(basePath + "/Hatch.svg");
    action.setStatusTip(qsTranslate("Hatch", "Draw hatch or solid fill"));
    action.setDefaultShortcut(new QKeySequence("h,a"));
    action.setDefaultCommands(["hatch", "ha"]);
    action.setSortOrder(1200);
    EAction.addGuiActionTo(action, Draw, true, false, true);
}
