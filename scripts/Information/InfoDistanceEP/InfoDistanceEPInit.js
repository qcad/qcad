function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoDistanceEP", "Distance &Entity to Point"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoDistanceEP.js");
    action.setIcon(basePath + "/InfoDistanceEP.svg");
    action.setDefaultShortcut(new QKeySequence("i,e"));
    action.setDefaultCommands([ "infodistep", "ie" ]);
    action.setSortOrder(200);
//    var appWin = EAction.getMainWindow();
//    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Information, true, true, true);
}
