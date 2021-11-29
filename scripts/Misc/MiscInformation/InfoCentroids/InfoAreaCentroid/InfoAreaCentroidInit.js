/**
 * Adds a PRO menu for the InfoAreaCentroid action to Misc .. Information menu.
 */
function init(basePath) {
    // Prevent InfoAreaCentroid to be loaded without PRO resources
    if (!hasPlugin("PROTOOLS")) {
        return;    // Don't initiate the Addon
    }
    // -> Continue with PRO recourses

    var action = new RGuiAction("&Area Centroid", RMainWindowQt.getMainWindow());    // '&' Indicates the key letter
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/InfoAreaCentroid.js");
    action.setIcon(basePath + "/InfoAreaCentroid.svg");
    action.setDefaultShortcut(new QKeySequence("a,m"));
    action.setDefaultCommands(["acentroid", "getac"]);    // List as an Array!
    var tipShort = qsTranslate("InfoAreaCentroid", "Add 2D area centroid for a selected entity.");   // In an init section in the script mostly qsTr() is used
    var tipLong = qsTranslate("InfoAreaCentroid", "Add 2D uniform density area centroid marker and values for a selected entity.");
    action.setStatusTip(tipLong);    // Overtakes and displays left in the Status Bar
    action.setToolTip(tipShort);    // Displays aside Tool bars
    action.setNoState(true);    // Indicates whether this action is stateless (i.e. terminates in beginEvent).
    action.setGroupSortOrder(71050);    // Confirmed by Andrew, PM Thu Nov 11, 2021 11:25 am 
    action.setSortOrder(100);
    action.setWidgetNames(["MiscInformationMenu", "!MiscInformationToolBar", "!MiscInformationToolsPanel"]);
    //action.setWidgetNames(["InformationMenu", "InformationMatrixPanel", "MiscInformationMenu", "!MiscInformationToolBar", "!MiscInformationToolsPanel"]);
};

