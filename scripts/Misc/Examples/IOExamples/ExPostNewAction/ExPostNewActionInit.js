include("scripts/File/NewFile/NewFile.js");

function init(basePath) {
    // disabled by default (remove return to activate):
    return;

    var action = new RGuiAction("ExPostNewAction", RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/ExPostNewAction.js");
    action.setNoState();

    if (!isNull(NewFile)) {
        NewFile.addPostNewAction(basePath + "/ExPostNewAction.js");
        NewFile.addPostOpenAction(basePath + "/ExPostNewAction.js");
    }
}

