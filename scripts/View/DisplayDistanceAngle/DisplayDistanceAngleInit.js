function init(basePath) {
    var action = new RGuiAction(qsTranslate("DisplayDistanceAngle", "Display &Distance/Angle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DisplayDistanceAngle.js");
    if (RSettings.getQtVersion()>=0x060000) {
        action.setDefaultShortcuts([new QKeySequence(new QKeyCombination(Qt.Key_F8))]);
    }
    else {
        action.setDefaultShortcuts([new QKeySequence(Qt.Key_F8.valueOf())]);
    }
    action.setNoState(true);
    action.setOverride();
    action.checkable = false;
    action.setGroupSortOrder(3980);
    action.setSortOrder(100);
    action.setWidgetNames(["ViewMenu", "!ViewToolBar", "!ViewToolsPanel"]);
}
