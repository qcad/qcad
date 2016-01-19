function postInit(basePath) {
    var menu = View.getMenu();
    var mainWindow = RMainWindowQt.getMainWindow();
    var subMenu = mainWindow.createPopupMenu();
    if (!isNull(subMenu)) {
        subMenu.title = qsTranslate("ViewToolBars", "&Toolbars and Widgets");
        menu.addSeparator();
        menu.addMenu(subMenu);
    }
}
