/**
 * Adds a PRO menu item for the InfoAddCustomCentroid action to Misc/Information/2D Centroids menu.
 */
function init(basePath) {
    // Prevent InfoAddCustomCentroid to be loaded without PRO resources
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

    var action = new RGuiAction(qsTranslate("InfoAddCustomCentroid", "Add &custom 2D centroid"), RMainWindowQt.getMainWindow());    // '&' Indicates the key letter
    action.setRequiresDocument(true);
    action.setRequiresSelection(false);
    action.setScriptFile(basePath + "/InfoAddCustomCentroid.js");
//    action.setDefaultShortcut(new QKeySequence("a,b,c"));    // Ruled out (all Centroids)
    action.setDefaultCommands(["addcentroid", "addc"]);    // List as an Array!
    var tipShort = qsTranslate("InfoAddCustomCentroid", "Create a customizable 2D Centroid marker");
    var tipLong = qsTranslate("InfoAddCustomCentroid", "Creates a new point mass 2D Centroid marker customizable by dialog");
    action.setStatusTip(tipLong);    // Overtakes and displays left in the Status Bar
    action.setToolTip(tipShort);    // Displays aside Tool bars
    // # Issue # It required ruling out to clear mouseTips and revert to CAD Toolbar
//    action.setNoState();    // Indicates whether this action is stateless (i.e. terminates in beginEvent).
    action.setGroupSortOrder(72000);
    action.setSortOrder(100);
    action.setWidgetNames(["MiscInformationCentroidsMenu", "MiscInformationToolBar", "MiscInformationToolsPanel"]);    // List as an Array!
};

