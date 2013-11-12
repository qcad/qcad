function init(basePath) {
    // disabled for now:
    return;

    var action = new RGuiAction("&Mirrored", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ScMirrored.js");
    action.setSortOrder(20);
    action.setDefaultCommands(["screencast"]);
    EAction.addGuiActionTo(action, Screencast, true, false, false);
};
