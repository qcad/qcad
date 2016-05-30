function init(basePath) {
    var action = new RGuiAction(qsTranslate("RunScript", "R&un Script"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/RunScript.js");
    action.setIcon(basePath + "/RunScript.svg");
    action.setDefaultShortcut(new QKeySequence("x,c"));
    action.setDefaultCommands(["runscript", "rscript", "xscript", "rsc", "xsc"]);
    action.setStatusTip(qsTranslate("RunScript", "Open and run a script file"));
    action.setNoState();
    action.setGroupSortOrder(3800);
    action.setSortOrder(200);
    action.setWidgetNames(["MiscDevelopmentMenu", "MiscDevelopmentToolBar", "MiscDevelopmentToolsPanel"]);
}
