function postInit(basePath) {
    var menu = View.getMenu();
    var mainWindow = RMainWindowQt.getMainWindow();
    var subMenu = mainWindow.createPopupMenu();
    if (!isNull(subMenu)) {
        subMenu.title = qsTranslate("ViewToolBars", "&Toolbars and Widgets");
        var actions = subMenu.actions();
        for (var i=0; i<actions.length; i++) {
            if (actions[i].text==="Widgets") {
                actions[i].text = qsTranslate("ViewToolBars", "Widgets");
            }
            if (actions[i].text==="Toolbars") {
                actions[i].text = qsTranslate("ViewToolBars", "Toolbars");
            }
        }
        menu.addSeparator();
        menu.addMenu(subMenu);
    }
}
