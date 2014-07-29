function init(basePath) {
    var action = new RGuiAction(qsTranslate("DisplayDistanceAngle", "Display Distance/Angle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DisplayDistanceAngle.js");
    action.setDefaultShortcuts([new QKeySequence(Qt.Key_F8.valueOf())]);
    action.setSortOrder(200000);
    action.setNoState(true);
    action.setOverride();
    action.checkable = false;
    EAction.addGuiActionTo(action, View, true, false, false, true);
}
