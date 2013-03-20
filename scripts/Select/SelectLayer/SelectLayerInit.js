function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectLayer", "(De-)Select La&yer"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectLayer.js");
    action.setIcon(basePath + "/SelectLayer.svg");
    action.setStatusTip(qsTranslate("SelectLayer", "(De-)Select all entities on the same layer"));
    action.setDefaultShortcut(new QKeySequence("t,l"));
    action.setDefaultCommands(["selectlayer", "tl"]);
    action.setSortOrder(800);
    EAction.addGuiActionTo(action, Select, true, true, true);
}
