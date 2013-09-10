function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoAngle", "&Angle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoAngle.js");
    action.setIcon(basePath + "/InfoAngle.svg");
    action.setDefaultShortcut(new QKeySequence("i,a"));
    action.setDefaultCommands([ "infoangle", "ia" ]);
    action.setSortOrder(300);
    EAction.addGuiActionTo(action, Information, true, true, true, true);
}
