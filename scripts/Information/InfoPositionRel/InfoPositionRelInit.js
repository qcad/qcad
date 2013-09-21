function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoPositionRel", "&Relative Position"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoPositionRel.js");
    action.setIcon(basePath + "/InfoPositionRel.svg");
    action.setDefaultShortcut(new QKeySequence("i,v"));
    action.setDefaultCommands([ "infoposrel", "iv" ]);
    action.setSortOrder(200);
    EAction.addGuiActionTo(action, Information, true, true, true);
}
