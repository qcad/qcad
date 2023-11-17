function init(basePath) {
    var action = new RGuiAction(qsTranslate("PreviousWindow", "&Previous"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/PreviousWindow.js");

    var scs = [];
    if (RSettings.getQtVersion()>=0x060000) {
        scs.push(new QKeySequence(new QKeyCombination(Qt.ControlModifier, Qt.Key_Left)));
    }
    else {
        scs.push(new QKeySequence(Qt.ControlModifier + Qt.Key_Left));
    }
    scs.push(new QKeySequence("Ctrl+PgDown"));
    action.setDefaultShortcuts(scs);

    action.setGroupSortOrder(50200);
    action.setSortOrder(200);
    action.setWidgetNames(["WindowMenu", "WindowToolBar"]);
}
