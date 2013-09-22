function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoPositionPolRel", "&Polar Position"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoPositionPolRel.js");
    action.setIcon(basePath + "/InfoPositionPolRel.svg");
    action.setDefaultShortcut(new QKeySequence("i,l"));
    action.setDefaultCommands([ "infopospol", "il" ]);
    action.setSortOrder(300);
    EAction.addGuiActionTo(action, Information, true, true, true);
}
