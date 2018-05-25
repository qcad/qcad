include("scripts/EAction.js");
include("MyWidget.js");

/**
 * \ingroup ecma_misc_examples_qtexamples
 * \class ExWidget
 * This action creates a Qt widget with a GUI loaded from an UI file.
 */
function ExWidget(guiAction) {
    EAction.call(this, guiAction);
}

ExWidget.prototype = new EAction();

ExWidget.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var w = new MyWidget();
    w.show();

    this.terminate();
};

/**
 * Adds a menu for this action to Examples/Math Examples/ExWidget.
 */
ExWidget.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Widget"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ExWidget.js");
    action.setGroupSortOrder(79600);
    action.setSortOrder(250);
    action.setWidgetNames(["QtExamplesMenu"]);
};

