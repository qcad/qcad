function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectByHandle", "By Handle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectByHandle.js");
    action.setDefaultShortcuts([
        new QKeySequence("t,h")
    ]);
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, MiscSelect, true, false, false, true);
}
