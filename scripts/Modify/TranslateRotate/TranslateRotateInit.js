function init(basePath) {
    var action = new RGuiAction(qsTranslate("TranslateRotate", "M&ove and Rotate"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/TranslateRotate.js");
    action.setIcon(basePath + "/TranslateRotate.svg");
    action.setDefaultShortcut(new QKeySequence("m,r"));
    action.setDefaultCommands(["moverotate", "mr"]);
    action.setSortOrder(500);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
    EAction.addGuiActionTo(action, Modify, true, true, true);
}
