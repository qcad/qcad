function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectContour", "(De-)Select &Contour"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectContour.js");
    action.setIcon(basePath + "/SelectContour.svg");
    action.setStatusTip(qsTranslate("SelectContour", "(De-)Select connected entities"));
    action.setDefaultShortcut(new QKeySequence("t,c"));
    action.setDefaultCommands(["selectcontour", "tc"]);
    action.setSortOrder(600);
    EAction.addGuiActionTo(action, Select, true, true, true, true);
}
