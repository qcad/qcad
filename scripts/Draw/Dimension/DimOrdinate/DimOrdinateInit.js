function init(basePath) {
    var action = new RGuiAction(qsTranslate("DimOrdinate", "&Ordinate (X/Y)"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DimOrdinate.js");
    action.setIcon(basePath + "/DimOrdinate.svg");
    action.setStatusTip(qsTranslate("DimOrdinate", "Draw ordinate dimension"));
    action.setDefaultShortcut(new QKeySequence("d,o"));
    action.setDefaultCommands(["dimordinate", "do"]);
    action.setSortOrder(500);
    EAction.addGuiActionTo(action, Dimension, true, true, true, true);
}
