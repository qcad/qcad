function init(basePath) {
    var action = new RGuiAction(qsTranslate("LeftClick", "&Left Click"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LeftClick.js");
    if (RSettings.getQtVersion()>=0x060000) {
        action.setDefaultShortcut(new QKeySequence(new QKeyCombination(Qt.ControlModifier, Qt.Key_Return)));
    }
    else {
        action.setDefaultShortcut(new QKeySequence(Qt.ControlModifier + Qt.Key_Return));
    }
    action.setOverride();
    action.setNoState();
    action.setGroupSortOrder(2670);
    action.setSortOrder(100);
    action.setWidgetNames(["EditMenu"]);
}
