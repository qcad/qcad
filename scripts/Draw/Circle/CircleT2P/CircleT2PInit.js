function init(basePath) {
    var action = new RGuiAction(qsTranslate("CircleT2P", "2 Poin&ts and Tangent"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/CircleT2P.js");
    action.setIcon(basePath + "/CircleT2P.svg");
    action.setStatusTip(qsTranslate("CircleT2P", "Draw circle through two points and tangential to one entity"));
    action.setDefaultShortcut(new QKeySequence("c,t,1"));
    action.setDefaultCommands(["circletangent2p", "ct1"]);
    action.setSortOrder(1000);
    EAction.addGuiActionTo(action, Circle, true, true, true, true);
}
