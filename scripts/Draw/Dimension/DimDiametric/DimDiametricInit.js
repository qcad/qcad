function init(basePath) {
    var action = new RGuiAction(qsTranslate("DimDiametric", "&Diametric"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DimDiametric.js");
    action.setIcon(basePath + "/DimDiametric.svg");
    action.setStatusTip(qsTranslate("DimDiametric", "Draw diametric dimension"));
    action.setDefaultShortcut(new QKeySequence("d,d"));
    action.setDefaultCommands(["dimdia", "dimdiametric", "dd"]);
    action.setSortOrder(800);
    EAction.addGuiActionTo(action, Dimension, true, true, true);
}
