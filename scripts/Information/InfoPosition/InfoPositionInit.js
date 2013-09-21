function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoPosition", "&Position"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoPosition.js");
    action.setIcon(basePath + "/InfoPosition.svg");
    action.setDefaultShortcut(new QKeySequence("i,o"));
    action.setDefaultCommands([ "infopos", "io" ]);
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, Information, true, true, true);
}
