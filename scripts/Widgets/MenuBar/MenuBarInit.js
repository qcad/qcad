function init(basePath) {
    var appWin = EAction.getMainWindow();

    var menuBar = appWin.menuBar();
    var h = menuBar.height;
    var noNativeMenuBar = QCoreApplication.testAttribute(Qt.AA_DontUseNativeMenuBar);

    if (h>40 && noNativeMenuBar) {
        // reduce size of menu bar on macOS if it is huge 
        // due to notch but we are not using the native menu bar:
        menuBar.maximumHeight = 24;
    }
}

