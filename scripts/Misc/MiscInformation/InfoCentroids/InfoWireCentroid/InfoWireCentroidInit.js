/**
 * Adds a PRO menu for the InfoWireCentroid action to Misc .. Information menu.
 */
function init(basePath) {
    // Prevent InfoWireCentroid to be loaded without PRO resources
    if (!hasPlugin("PROTOOLS")) {
        return;    // Don't initiate the Addon
    }
    // -> Continue with PRO recourses

    var action = new RGuiAction(qsTranslate("InfoWireCentroid", "&Wire Centroid"), RMainWindowQt.getMainWindow());    // '&' Indicates the key letter
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/InfoWireCentroid.js");
    action.setIcon(basePath + "/InfoWireCentroid.svg");
    action.setDefaultCommands(["wcentroid", "getwc"]);    // List as an Array!
    var tipShort = qsTranslate("InfoWireCentroid", "Add 2D wire centroid for a selection.");   // In an init section in the script mostly qsTr() is used
    var tipLong = qsTranslate("InfoWireCentroid", "Add 2D uniform density wire centroid marker and values for a selection of entities.");
    action.setStatusTip(tipLong);    // Overtakes and displays left in the Status Bar
    action.setToolTip(tipShort);    // Displays aside Tool bars
    action.setNoState(true);    // Indicates whether this action is stateless (i.e. terminates in beginEvent).
    action.setGroupSortOrder(71050);    // Confirmed by Andrew, PM Thu Nov 11, 2021 11:25 am 
    action.setSortOrder(200);
    action.setWidgetNames(["MiscInformationMenu", "!MiscInformationToolBar", "!MiscInformationToolsPanel"]);
    //action.setWidgetNames(["InformationMenu", "InformationMatrixPanel", "MiscInformationMenu", "!MiscInformationToolBar", "!MiscInformationToolsPanel"]);
};

