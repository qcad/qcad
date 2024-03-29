function init(basePath) {
    var action = new RGuiAction(qsTranslate("ToolMatrixFocus", "&Focus on Tool Matrix"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/ToolMatrixFocus.js");

    if (RSettings.getQtVersion()>=0x060000) {
        if (RS.getSystemId()==="osx") {
            action.setDefaultShortcut(new QKeySequence(new QKeyCombination(Qt.ShiftModifier|Qt.MetaModifier, Qt.Key_Space)));
        }
        else {
            action.setDefaultShortcut(new QKeySequence(new QKeyCombination(Qt.ShiftModifier|Qt.ControlModifier, Qt.Key_Space)));
        }
    }
    else {
        if (RS.getSystemId()==="osx") {
            action.setDefaultShortcut(new QKeySequence(Qt.ShiftModifier + Qt.MetaModifier + Qt.Key_Space));
        }
        else {
            action.setDefaultShortcut(new QKeySequence(Qt.ShiftModifier + Qt.ControlModifier + Qt.Key_Space));
        }
    }

    action.setNoState();
    action.checkable = false;
    action.setGroupSortOrder(3900);
    action.setSortOrder(300);
    action.setWidgetNames(["ViewMenu", "!ViewToolBar", "!ViewToolsPanel"]);
}
