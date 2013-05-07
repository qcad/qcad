function init(basePath) {
    if (RSettings.hasQuitFlag()) {
        return;
    }

    var action = new RGuiAction(
        qsTranslate("CheckForUpdates", "Check for &Updates..."),
        RMainWindowQt.getMainWindow()
    );
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/CheckForUpdates.js");
    qDebug("check updates: ", basePath + "/CheckForUpdates.js");
    action.setSortOrder(1000);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false, true);
}
