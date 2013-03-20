function init(basePath) {
    var action = new RGuiAction(qsTranslate("DimAngular", "&Angular"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DimAngular.js");
    action.setIcon(basePath + "/DimAngular.svg");
    action.setStatusTip(qsTranslate("DimAngular", "Draw angular dimension"));
    action.setDefaultShortcut(new QKeySequence("d,n"));
    action.setDefaultCommands(["dimangular", "dn"]);
    action.setSortOrder(900);
    EAction.addGuiActionTo(action, Dimension, true, true, true, true);
}
