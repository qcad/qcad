function init(basePath) {
    var action = new RGuiAction(qsTranslate("NextWindow", "&Next"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/NextWindow.js");

    var scs = [];
    if (RSettings.getQtVersion()>=0x060000) {
        scs.push(new QKeySequence(new QKeyCombination(Qt.ControlModifier, Qt.Key_Right)));
    }
    else {
        scs.push(new QKeySequence(Qt.ControlModifier + Qt.Key_Right));
    }
    scs.push(new QKeySequence("Ctrl+PgUp"));
    action.setDefaultShortcuts(scs);

    action.setGroupSortOrder(50200);
    action.setSortOrder(100);
    action.setWidgetNames(["WindowMenu", "WindowToolBar"]);
}
