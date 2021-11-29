/**
 * Adds a PRO menu for the InfoSumCentroidsWeighted action to Misc .. Information menu.
 */
function init(basePath) {
    // Prevent InfoWireCentroid to be loaded without PRO resources
    if (!hasPlugin("PROTOOLS")) {
        return;    // Don't initiate the Addon
    }
    // -> Continue with PRO recourses

    var action = new RGuiAction("&Sum centroids weighted", RMainWindowQt.getMainWindow());    // '&' Indicates the key letter
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/InfoSumCentroidsWeighted.js");
    action.setIcon(basePath + "/InfoSumCentroidsWeighted.svg");
    action.setDefaultShortcut(new QKeySequence("c,m"));
    action.setDefaultCommands(["sumcentroid", "sumc"]);    // List as an Array!
    var tipShort = qsTranslate("InfoSumCentroidsWeighted", "Sum selected 2D centroid markers weighted.");   // In an init section in the script mostly qsTr() is used
    var tipLong = qsTranslate("InfoSumCentroidsWeighted", "Sum selected 2D centroid markers weighted by their individual custom density.");
    action.setStatusTip(tipLong);    // Overtakes and displays left in the Status Bar
    action.setToolTip(tipShort);    // Displays aside Tool bars
    action.setNoState(true);    // Indicates whether this action is stateless (i.e. terminates in beginEvent).
    action.setGroupSortOrder(71050);    // Confirmed by Andrew, PM Thu Nov 11, 2021 11:25 am 
    action.setSortOrder(300);
    action.setWidgetNames(["MiscInformationMenu", "!MiscInformationToolBar", "!MiscInformationToolsPanel"]);
    //action.setWidgetNames(["InformationMenu", "InformationMatrixPanel", "MiscInformationMenu", "!MiscInformationToolBar", "!MiscInformationToolsPanel"]);
};

