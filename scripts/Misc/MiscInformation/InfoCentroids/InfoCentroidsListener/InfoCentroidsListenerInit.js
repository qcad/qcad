/**
 * Adds a PRO menu item for the InfoCentroidsListener action to Misc/Information/2D Centroids menu.
 */
function init(basePath) {
    // Prevent InfoCentroidsListener to be loaded without PRO resources
    if (!hasPlugin("PROTOOLS")) {
        return;    // Don't initiate the Addon
    }
    // -> Continue with PRO recourses

    // Prevent InfoAddCustomCentroid to be loaded with inadequate framework lower than QCAD 3.27
    var frameworkV = getVersionNumber(RSettings.getMajorVersion(), RSettings.getMinorVersion(), RSettings.getRevisionVersion(), RSettings.getBuildVersion());
    var minV = getVersionNumber(3, 27, 0, 0);
    if (frameworkV < minV) {
        return;    // Don't initiate the Addon
    }
    // -> Continue when up to date framework

    var action = new RGuiAction(qsTranslate("InfoCentroidsListener", "Centroid &Listener"), RMainWindowQt.getMainWindow());    // '&' Indicates the key letter
    action.setRequiresDocument(true);
    action.setRequiresSelection(false);
    action.setScriptFile(basePath + "/InfoCentroidsListener.js");
    action.setIcon(basePath + "/InfoCentroidsListenerInactive.svg");
//    action.setDefaultShortcut(new QKeySequence("a,b,c"));    // Ruled out (none required)
    action.setDefaultCommands(["centroidlistener"]);    // List as an Array!
    var tipShort = qsTranslate("InfoCentroidsListener", "(De-)Activate a transaction listener for 2D Centroids");
    var tipLong = qsTranslate("InfoCentroidsListener", "(De-)Activate a transaction listener for binding changes applied to 2D Centroid markers");
    action.setStatusTip(tipLong);    // Overtakes and displays left in the Status Bar
    action.setToolTip(tipShort);    // Displays aside Tool bars
    action.setNoState(true);    // Indicates whether this action is stateless (i.e. terminates in beginEvent).
    action.setGroupSortOrder(72200);    // Unconfirmed by Andrew
    action.setSortOrder(100);
    action.setWidgetNames(["MiscInformationCentroidsMenu", "MiscInformationToolBar", "MiscInformationToolsPanel"]);    // List as an Array!
};

