function init(basePath) {
    var action = new RGuiAction(qsTranslate("OptionsToolBarFocus", "&Focus on Options Toolbar"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/OptionsToolBarFocus.js");
    if (RS.getSystemId()==="osx") {
        action.setDefaultShortcut(new QKeySequence(Qt.MetaModifier + Qt.Key_Space));
    }
    else {
        action.setDefaultShortcut(new QKeySequence(Qt.ControlModifier + Qt.Key_Space));
    }
    action.setNoState(true);
    action.checkable = false;
    action.setGroupSortOrder(3900);
    action.setSortOrder(200);
    action.setWidgetNames(["ViewMenu", "!ViewToolBar", "!ViewToolsPanel"]);
}
