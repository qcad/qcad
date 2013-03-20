function init(basePath) {
    var action = new RGuiAction(qsTranslate("CommandLineFocus", "&Focus on Command Line"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/CommandLineFocus.js");
    action.setDefaultShortcuts(
                [
                    new QKeySequence(Qt.Key_Space.valueOf()),
                    new QKeySequence(Qt.ControlModifier + Qt.Key_M),
                ]);
    action.setSortOrder(100000);
    action.setNoState(true);
    action.checkable = false;
    EAction.addGuiActionTo(action, View, true, false, false, true);
}
