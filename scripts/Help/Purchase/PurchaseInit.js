function init(basePath) {
    var action = new RGuiAction(qsTranslate("Purchase", "&Purchase %1 Pro").arg(qApp.applicationName),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/Purchase.js");
    action.setSortOrder(500);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false, true);
}
