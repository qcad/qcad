include("scripts/EAction.js");

function init(basePath) {
    // make sure the reset toolbar comes first:
    EAction.getToolBar(qsTranslate("Reset", "Reset"), "ResetToolBar");
}
