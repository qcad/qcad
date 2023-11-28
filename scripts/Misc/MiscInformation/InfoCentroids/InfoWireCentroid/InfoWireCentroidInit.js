/**
 * Adds a PRO menu item for the InfoWireCentroid action to Misc/Information/2D Centroids menu.
 */
function init(basePath) {
    // Prevent InfoWireCentroid to be loaded without PRO resources
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
    // -> Continue when framework is up to date

    var action = new RGuiAction(qsTranslate("InfoWireCentroid", "&Wire Centroid"), RMainWindowQt.getMainWindow());    // '&' Indicates the key letter
    action.setRequiresDocument(true);
    // # Issue # Grayed but requirement not displayed without QKeySequence
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/InfoWireCentroid.js");
//    action.setDefaultShortcut(new QKeySequence("w,m"));    // Wire's center of Mass ... Ruled out (collision with ModifyToolsPanel (unlisted), no good option)
    action.setDefaultCommands(["wcentroid", "getwc"]);    // List as an Array!
    var tipShort = qsTranslate("InfoWireCentroid", "Create a wire 2D Centroid for a selection");
    var tipLong = qsTranslate("InfoWireCentroid", "Creates a new uniform linear density 2D Centroid marker and value labels for a selection of entities");
    action.setStatusTip(tipLong);    // Overtakes and displays left in the Status Bar
    action.setToolTip(tipShort);    // Displays aside Tool bars
    // # Issue # It required forcing the action button state
    action.setNoState(true);    // Indicates whether this action is stateless (i.e. terminates in beginEvent).
    action.setGroupSortOrder(72000);    // Unconfirmed by Andrew
    action.setSortOrder(300);
    action.setWidgetNames(["MiscInformationCentroidsMenu", "MiscInformationToolBar", "MiscInformationToolsPanel"]);    // List as an Array!
};

