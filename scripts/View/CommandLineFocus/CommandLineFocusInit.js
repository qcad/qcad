function init(basePath) {
    var action = new RGuiAction(qsTranslate("CommandLineFocus", "&Focus on Command Line"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/CommandLineFocus.js");
    action.setDefaultShortcuts(
                [
                    new QKeySequence(" "),
                    new QKeySequence("Ctrl+M"),
                ]);
    action.setNoState();
    action.checkable = false;
    action.setGroupSortOrder(3900);
    action.setSortOrder(100);
    action.setWidgetNames(["ViewMenu", "!ViewToolBar", "!ViewToolsPanel"]);
}
