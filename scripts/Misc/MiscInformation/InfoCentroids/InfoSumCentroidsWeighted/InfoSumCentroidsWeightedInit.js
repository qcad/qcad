/**
 * Adds a PRO menu item for the InfoSumCentroidsWeighted action to Misc/Information/2D Centroids menu.
 */
function init(basePath) {
    // Prevent InfoSumCentroidsWeighted to be loaded without PRO resources
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

    var action = new RGuiAction(qsTranslate("InfoSumCentroidsWeighted", "&Sum 2D Centroids weighted"), RMainWindowQt.getMainWindow());    // '&' Indicates the key letter
    action.setRequiresDocument(true);
    // # Issue # Grayed but requirement not displayed without QKeySequence
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/InfoSumCentroidsWeighted.js");
//    action.setDefaultShortcut(new QKeySequence("c,m"));    // 'Combine centers of Mass' ... Ruled out 
    action.setDefaultCommands(["sumcentroid", "sumc"]);    // List as an Array!
    var tipShort = qsTranslate("InfoSumCentroidsWeighted", "Combine selected 2D Centroid markers weighted");
    var tipLong = qsTranslate("InfoSumCentroidsWeighted", "Combines selected 2D Centroid markers, summing all properties weighted");
    action.setStatusTip(tipLong);    // Overtakes and displays left in the Status Bar
    action.setToolTip(tipShort);    // Displays aside Tool bars
    // # Issue # It required forcing the action button state
    action.setNoState(true);    // Indicates whether this action is stateless (i.e. terminates in beginEvent).
    action.setGroupSortOrder(72100);    // Unconfirmed by Andrew
    action.setSortOrder(100);
    action.setWidgetNames(["MiscInformationCentroidsMenu", "MiscInformationToolBar", "MiscInformationToolsPanel"]);    // List as an Array!
};

