function init(basePath) {
    var action = new RGuiAction(qsTranslate("ZoomToSelection", "Zoom to &Selection"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/ZoomToSelection.js");
    action.setIcon(basePath + "/ZoomToSelection.svg");
    action.setDefaultShortcut(new QKeySequence("z,s"));
    action.setDefaultCommands(["zoomselection", "zs"]);
    action.setSortOrder(400);
    EAction.addGuiActionTo(action, View, true, true, false);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
