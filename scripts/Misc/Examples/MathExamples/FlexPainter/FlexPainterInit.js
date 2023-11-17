/**
 * Adds a menu for this action to Examples/Math Examples/FlexPainter.
 */
// Based on both Math Examples and other snips
function init(basePath) {
    // Prevent FlexPainter to be loaded without PRO resources
    if (!hasPlugin("PROTOOLS")) { return; };
    // -> Continue with PRO resources

    var action = new RGuiAction(qsTr("&FlexPainter"), RMainWindowQt.getMainWindow());
    var tip = qsTranslate("FlexPainter", "Paints over selection mimicking a roller stamp");
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/FlexPainter.js");
    action.setDefaultShortcut(new QKeySequence("f,p")); 
    action.setDefaultCommands(["flexpainter", "fp"]);    // A list array separated by comma + space
    action.setStatusTip(tip);    // Overtakes and displays left in the Status Bar
    action.setToolTip(tip);    // Displays aside near Toolbars
    action.setNoState(true);    // Indicates whether this action is stateless (i.e. terminates in beginEvent).
    action.setGroupSortOrder(79700);
    action.setSortOrder(300);
    action.setWidgetNames(["MathExamplesMenu"]);
};
