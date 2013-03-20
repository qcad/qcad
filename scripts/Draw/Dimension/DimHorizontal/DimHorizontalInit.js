function init(basePath) {
    var action = new RGuiAction(qsTranslate("DimHorizontal", "&Horizontal"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DimHorizontal.js");
    action.setIcon(basePath + "/DimHorizontal.svg");
    action.setStatusTip(qsTranslate("DimHorizontal", "Draw horizontal dimension"));
    action.setDefaultShortcut(new QKeySequence("d,h"));
    action.setDefaultCommands(["dimhor", "dimhorizontal", "dh"]);
    action.setSortOrder(300);
    EAction.addGuiActionTo(action, Dimension, true, true, true);
}
