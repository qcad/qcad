function init(basePath) {
    var action = new RGuiAction(qsTranslate(
                                            "LineBoxjoint",
                                            "Box &Joint from 2 Points"),
                                            RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineBoxjoint.js");
    action.setIcon(basePath + "/LineBoxjoint.svg");
    action.setStatusTip(qsTranslate("LineBoxjoint",
                                    "Draw Box Joint Fingers, Slots and Tennons"));
    action.setDefaultShortcut(new QKeySequence("l,j"));
    action.setDefaultCommands(["boxjoint", "bxj"]);
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, MiscDraw, true, true, true);
}
