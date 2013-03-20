function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineOrthogonal", "&Orthogonal"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineOrthogonal.js");
    action.setIcon(basePath + "/LineOrthogonal.svg");
    action.setStatusTip(qsTranslate("LineOrthogonal", "Draw line orthogonal to base entity"));
    action.setDefaultShortcut(new QKeySequence("l,o"));
    action.setDefaultCommands(["lineorthogonal", "lo"]);
    action.setSortOrder(1300);
    EAction.addGuiActionTo(action, Line, true, true, true);
}
