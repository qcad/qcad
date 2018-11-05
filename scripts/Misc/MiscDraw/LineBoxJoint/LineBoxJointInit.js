function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineBoxJoint", "Box &Joint from 2 Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineBoxJoint.js");
    action.setIcon(basePath + "/LineBoxJoint.svg");
    action.setStatusTip(qsTranslate("LineBoxJoint", "Draw Box Joint Fingers, Slots and Tennons"));
    action.setDefaultShortcut(new QKeySequence("l,j"));
    action.setDefaultCommands(["boxjoint", "bxj"]);
    action.setGroupSortOrder(54200);
    action.setSortOrder(100);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
