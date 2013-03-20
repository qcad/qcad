function postInit(basePath) {
    var menu = View.getMenu();
    var mainWindow = RMainWindowQt.getMainWindow();
    var subMenu = mainWindow.createPopupMenu();
    subMenu.title = qsTranslate("ViewToolBars", "&Toolbars");
    menu.addSeparator();
    menu.addMenu(subMenu);
}
