function init(basePath) {
    var action = new RGuiAction(qsTranslate("DimRegen", "&Reset Label Position"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/DimRegen.js");
    action.setIcon(basePath + "/DimRegen.svg");
    action.setDefaultShortcut(new QKeySequence("d,s"));
    action.setDefaultCommands(["dimregen", "ds"]);
    action.setSortOrder(1000);
    action.setNoState();
    EAction.addGuiActionTo(action, Dimension, true, false, false, true);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
