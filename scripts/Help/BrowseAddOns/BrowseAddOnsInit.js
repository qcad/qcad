function init(basePath) {
    var action = new RGuiAction(qsTranslate("BrowseAddOns", "Browse for Add-ons"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/BrowseAddOns.js");
    action.setNoState();
    action.setGroupSortOrder(110200);
    action.setSortOrder(400);
    action.setWidgetNames(["HelpMenu", "!HelpToolBar"]);

    // uninstall add-ons:
    var uninstallAddOns = RSettings.getStringListValue("BrowseAddOns/Uninstall", []);
    RSettings.setValue("BrowseAddOns/Uninstall", []);
    for (var i=0; i<uninstallAddOns.length; i++) {
        var addOnName = uninstallAddOns[i];
        qDebug("uninstalling add-on: ", addOnName);
        var addOnPath = RSettings.getDataLocation() + QDir.separator + addOnName;
        if (removeDirectory(addOnPath)) {
            qWarning("cannot uninstall add-on: ", addOnName);
        }
    }
}
