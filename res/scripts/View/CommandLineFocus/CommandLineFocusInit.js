function init(basePath) {
    var action = new RGuiAction(qsTranslate("CommandLineFocus", "&Focus on Command Line"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/CommandLineFocus.js");
    action.setDefaultShortcuts(
                [
                    new QKeySequence(Qt.Key_Space.valueOf()),
                    new QKeySequence(Qt.ControlModifier + Qt.Key_M),
                ]);
    action.setNoState();
    action.checkable = false;
    action.setGroupSortOrder(3900);
    action.setSortOrder(100);
    action.setWidgetNames(["ViewMenu", "!ViewToolBar", "!ViewToolsPanel"]);
}
