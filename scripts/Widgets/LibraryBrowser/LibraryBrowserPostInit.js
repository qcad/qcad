function postInit(basePath) {
    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("LibraryBrowserDock");

    if (dock.visible) {
        include("scripts/Widgets/LibraryBrowser/LibraryBrowser.js");
        LibraryBrowser.showFirstTime();
    }
}
