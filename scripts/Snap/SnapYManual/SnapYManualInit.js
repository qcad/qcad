function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapYManual", "&Y/X from Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapYManual.js");
    action.setIcon(basePath + "/SnapYManual.svg");
    action.setDefaultShortcut(new QKeySequence(".,y"));
    action.setDefaultCommands([".y"]);
    action.setSortOrder(3600);
    action.setOverride();
    action.setNoState();
    EAction.addGuiActionTo(action, Snap, true, false, false, false);
};
