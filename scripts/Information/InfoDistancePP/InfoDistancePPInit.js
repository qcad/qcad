function init(basePath) {
    var action = new RGuiAction(qsTranslate("InfoDistancePP", "Distance &Point to Point"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoDistancePP.js");
    action.setIcon(basePath + "/InfoDistancePP.svg");
    action.setDefaultShortcut(new QKeySequence("i,p"));
    action.setDefaultCommands([ "infodist", "ip" ]);
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, Information, true, true, true, true);
}
