function init(basePath) {
    var action = new RGuiAction(qsTranslate("Leader", "&Leader"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Leader.js");
    action.setIcon(basePath + "/Leader.svg");
    action.setStatusTip(qsTranslate("Leader", "Draw leader (line sequence with arrow)"));
    action.setDefaultShortcuts([
                            new QKeySequence("d,e"),
                            new QKeySequence("l,d")
                        ]);
    action.setDefaultCommands(["leader", "dimlea", "de", "ld"]);
    action.setSortOrder(600);
    EAction.addGuiActionTo(action, Dimension, true, true, true);
}
