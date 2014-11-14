function init(basePath) {
    var action = new RGuiAction(qsTranslate("Explode", "&Explode"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Explode.js");
    action.setIcon(basePath + "/Explode.svg");
    action.setDefaultShortcut(new QKeySequence("x,p"));
    action.setDefaultCommands(["explode", "xp"]);
    action.setGroupSortOrder(14700);
    action.setSortOrder(100);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "BlockMenu", "BlockToolBar", "BlockToolsPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
