function postInit() {
    if (RSettings.hasQuitFlag()) {
        return;
    }

    var appWin = RMainWindowQt.getMainWindow();

    // check for updates at startup:
    if (RSettings.getBoolValue("CheckForUpdates/AutoCheckUpdates", false)===true &&
        appWin.property("CheckForUpdates/Handled")!==true) {

        qDebug("checking for updates...");
        include("CheckForUpdates.js");
        var html = download(CheckForUpdates.getUrl(), 3000);
        if (html.indexOf("<title>Up To Date</title>")!==-1) {
            qDebug("no updates available");
        }
        else if (html.indexOf("<title>Update Available</title>")!=-1) {
            qDebug("updates available");
            var action = RGuiAction.getByScriptFile("scripts/Help/CheckForUpdates/CheckForUpdates.js");
            if (!isNull(action)) {
                action.slotTrigger();
            }
        }
    }
}
