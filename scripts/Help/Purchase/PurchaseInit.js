function init(basePath) {
    var action = new RGuiAction(qsTranslate("Purchase", "&Purchase %1 Extensions").arg(qApp.applicationName),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/Purchase.js");
    action.setSortOrder(1500);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false, true);
}
