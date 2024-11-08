
/**
 * Adds a menu for the DrawFromCSV action to Misc | Script Examples | Import/Export menu.
 */
function init(basePath) {
    var action = new RGuiAction(qsTranslate("DrawFromCSV", "&Draw from CSV") + "…", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);    // Can't draw without a document
    action.setRequiresSelection(false);    // No selection required
    action.setScriptFile(basePath + "/DrawFromCSV.js");
//    action.setDefaultShortcut(new QKeySequence("d,c,s,v"));    // Ruled out (no good option)
    action.setDefaultCommands(["drawcsv","dcsv"]);    // An Array!
    var tip = qsTranslate("DrawFromCSV", "Draws entities based on textual entries in a CSV file");
    action.setStatusTip(tip);    // Overtakes and displays left in the Status Bar
    action.setToolTip(tip);    // Displays aside Toolbars
    action.setNoState(true);    // Indicates whether this action is stateless (i.e. terminates in beginEvent).
    action.setGroupSortOrder(52100);
    action.setSortOrder(300);
    action.setWidgetNames(["MiscIOMenu", "MiscIOToolBar", "MiscIOToolsPanel"]);
};

