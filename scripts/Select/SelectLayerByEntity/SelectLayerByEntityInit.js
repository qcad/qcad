function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectLayerByEntity", "(De-)Select La&yer"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectLayerByEntity.js");
    action.setIcon(basePath + "/SelectLayerByEntity.svg");
    action.setStatusTip(qsTranslate("SelectLayerByEntity", "(De-)Select all entities on the same layer"));
    action.setDefaultShortcut(new QKeySequence("t,l"));
    action.setDefaultCommands(["selectlayer", "tl"]);
    action.setSortOrder(800);
    EAction.addGuiActionTo(action, Select, true, true, true);
}
