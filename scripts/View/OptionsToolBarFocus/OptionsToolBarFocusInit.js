function init(basePath) {
    var action = new RGuiAction(qsTranslate("OptionsToolBarFocus", "&Focus on Options Toolbar"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/OptionsToolBarFocus.js");
    if (RS.getSystemId()==="osx") {
        action.setDefaultShortcut(new QKeySequence(Qt.MetaModifier + Qt.Key_Space));
    }
    else {
        action.setDefaultShortcut(new QKeySequence(Qt.ControlModifier + Qt.Key_Space));
    }
    action.setSortOrder(100010);
    action.setNoState(true);
    action.checkable = false;
    EAction.addGuiActionTo(action, View, true, false, false, false);
}
