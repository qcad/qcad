function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapXManual", "&X/Y from Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapXManual.js");
    action.setIcon(basePath + "/SnapXManual.svg");
    action.setDefaultShortcut(new QKeySequence(".,x"));
    action.setDefaultCommands([".x"]);
    action.setSortOrder(3500);
    action.setOverride();
    action.setNoState();
    EAction.addGuiActionTo(action, Snap, true, false, false, true);
};
