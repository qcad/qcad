function init(basePath) {
    var action = new RGuiAction(qsTranslate("InvertSelection", "&Invert Selection"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InvertSelection.js");
    action.setIcon(basePath + "/InvertSelection.svg");
    action.setStatusTip(qsTranslate("InvertSelection", "Invert the current selection"));
    action.setDefaultShortcut(new QKeySequence("t,i"));
    action.setDefaultCommands(["selectinvert", "invertselection", "ti"]);
    action.setNoState();
    action.setSortOrder(300);
    EAction.addGuiActionTo(action, Select, true, true, true);
}
