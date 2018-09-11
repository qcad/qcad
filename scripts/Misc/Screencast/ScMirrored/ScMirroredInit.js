function init(basePath) {
    // disabled for now:
    return;

    var action = new RGuiAction(qsTranslate("ScMirrored", "&Mirrored"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ScMirrored.js");
    action.setSortOrder(20);
    action.setDefaultCommands(["screencastmirrored"]);
    EAction.addGuiActionTo(action, Screencast, true, false, false);
};
