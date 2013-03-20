function init(basePath) {
    var action = new RGuiAction(qsTranslate("IsoProject", "&Isometric Projection"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/IsoProject.js");
    action.setIcon(basePath + "/IsoProject.svg");
    action.setDefaultShortcut(new QKeySequence("p,j"));
    action.setDefaultCommands(["isometric", "pj"]);
    action.setSortOrder(9000);
    EAction.addGuiActionTo(action, Modify, true, true, false, true);

    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);

    var ctb = IsometricProjection.getCadToolBarPanel();
    if (!isNull(ctb)) {
        var separator = new RGuiAction("", RMainWindowQt.getMainWindow());
        separator.setSeparator(true);
        separator.setSortOrder(action.getSortOrder()-1);
        CadToolBarPanel.prototype.addAction.call(ctb, separator);

        CadToolBarPanel.prototype.addAction.call(ctb, action);
    }
}
