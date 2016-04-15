include("scripts/EAction.js");

function init(basePath) {
    // make sure the reset toolbar comes first:
    var tb = EAction.getToolBar(qsTranslate("Reset", "Reset"), "ResetToolBar");

    var action = new RGuiAction(qsTranslate("Reset", "&Reset / Idle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Reset.js");
    action.setIcon(basePath + "/Reset.svg");
    action.setDefaultShortcut(new QKeySequence("q,q"));
    action.setDefaultCommands(["reset", "qq"]);
    action.setGroupSortOrder(2700);
    action.setSortOrder(200);
    action.setWidgetNames(["EditMenu", "ResetToolBar"]);

    RSettings.setValue("Reset/VisibleInToolBar", true);
}
