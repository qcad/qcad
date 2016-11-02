function init(basePath) {
    var title;
    if (RS.getSystemId()==="osx") {
        // don't translate quit menu under OS X:
        title = "&Quit";
    }
    else {
        title = qsTranslate("Quit", "&Quit");
    }

    var action = new RGuiAction(title, RMainWindowQt.getMainWindow());
    if (RS.getSystemId() === "osx") {
        action.disableIcon();
    }
    action.setRequiresDocument(false);
    action.setDefaultShortcut(new QKeySequence(QKeySequence.Quit));
    action.setDefaultCommands(["quit", "exit"]);
    action.checkable = false;
    action.setGroupSortOrder(1990);
    action.setSortOrder(100);
    action.setWidgetNames(["FileMenu"]);

    var appWin = EAction.getMainWindow();
    action.triggered.connect(appWin, "quit");
}
