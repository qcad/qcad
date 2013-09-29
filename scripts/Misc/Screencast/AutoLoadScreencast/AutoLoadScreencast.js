include("scripts/Misc/Screencast/ScInputInfo/ScInputInfo.js");

if (typeof(initDialog)==="undefined") {
    initDialog = [];
}

initDialog.push(function(dialog) {
    qDebug("screencast initDialog");

    var appWin = RMainWindowQt.getMainWindow();

    qDebug("running: ", appWin["ScreencastRunning"]);
    if (appWin["ScreencastRunning"]) {
        // not needed?
        //dialog.modal = false;

        dialog.show();
    }
});
