function init(basePath) {
    var action = new RGuiAction(qsTranslate("SaveAs", "Save &As..."),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SaveAs.js");
    action.setIcon(basePath + "/SaveAs.svg");
    action.setDefaultShortcut(new QKeySequence("Ctrl+Shift+S"));
    action.setDefaultCommands(["saveas"]);
    action.setSortOrder(1100);
    EAction.addGuiActionTo(action, File, true, true);
}
