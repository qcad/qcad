include("scripts/File/NewFile/NewFile.js");

function init(basePath) {
    // disabled by default (remove return to activate):
    return;

    if (!isNull(NewFile)) {
        NewFile.addPostNewAction(basePath + "/ExNewFileHandler.js");
    }
}

