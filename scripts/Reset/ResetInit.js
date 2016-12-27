include("scripts/EAction.js");

function init(basePath) {
    // make sure the reset toolbar comes first:
    var tb = EAction.getToolBar(qsTranslate("Reset", "Reset"), "ResetToolBar");

    var action = new RGuiAction(qsTranslate("Reset", "&Reset / Idle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Reset.js");
    action.setIcon(basePath + "/Reset.svg");

    // workaround for Linux/Qt bug
    // input of @ in command line not possible on German keyboard where
    // Alt-Q is used to enter @:
    var useShortcut = true;
    if (RS.getSystemId()==="linux") {
        var locale = RSettings.getLocale();
        if (locale.length>=2) {
            if (locale.substring(0,2)==="de") {
                useShortcut = false;
            }
        }
    }

    if (useShortcut) {
        action.setDefaultShortcut(new QKeySequence("q,q"));
    }

    action.setDefaultCommands(["reset", "qq"]);
    action.setGroupSortOrder(2700);
    action.setSortOrder(200);
    action.setWidgetNames(["EditMenu", "ResetToolBar"]);

    RSettings.setValue("Reset/VisibleInToolBar", true);
}
