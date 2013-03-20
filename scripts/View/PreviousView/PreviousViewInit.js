function init(basePath) {
    var action = new RGuiAction(qsTranslate("PreviousView", "&Previous View"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PreviousView.js");
    action.setIcon(basePath + "/PreviousView.svg");
    action.setDefaultShortcut(new QKeySequence("z,v"));
    action.setDefaultCommands(["zoomprevious", "zv"]);
    action.setSortOrder(500);
    action.setNoState();
    EAction.addGuiActionTo(action, View, true, true, false);
}
