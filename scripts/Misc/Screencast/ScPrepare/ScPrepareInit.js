function init(basePath) {
    // disabled for now:
    return;

    var action = new RGuiAction("&Prepare Window Position", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ScPrepare.js");
    action.setSortOrder(50);
    action.setDefaultCommands(["screencast"]);
    EAction.addGuiActionTo(action, Screencast, true, false, false);
};
