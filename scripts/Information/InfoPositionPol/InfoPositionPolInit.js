function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoPositionPol", "&Polar Position"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoPositionPol.js");
    action.setIcon(basePath + "/InfoPositionPol.svg");
    action.setDefaultShortcut(new QKeySequence("i,l"));
    action.setDefaultCommands([ "infopospol", "il" ]);
    action.setSortOrder(300);
    EAction.addGuiActionTo(action, Information, true, true, true);
}
