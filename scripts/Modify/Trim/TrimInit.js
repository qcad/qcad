function init(basePath) {
    var action = new RGuiAction(qsTranslate("Trim", "&Trim"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Trim.js");
    action.setIcon(basePath + "/Trim.svg");
    action.setDefaultShortcuts(
        [ new QKeySequence("r,m"),
          new QKeySequence("x,t") ]);
    action.setDefaultCommands(["trim", "extend", "rm", "xt", "mr"]);
    action.setSortOrder(1000);
    EAction.addGuiActionTo(action, Modify, true, true, true, true);
}
