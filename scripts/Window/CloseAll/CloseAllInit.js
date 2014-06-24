function init(basePath) {
    var action = new RGuiAction(qsTranslate("CloseAll", "&Close All"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/CloseAll.js");
    action.setDefaultShortcut(new QKeySequence("Ctrl+Shift+W"));
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, Window, true, false, false);
}
