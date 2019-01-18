include("scripts/EAction.js");

function ExMinimal(guiAction) {
    EAction.call(this, guiAction);
}

ExMinimal.prototype = new EAction();

ExMinimal.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    EAction.handleUserMessage(qsTr("Hello World."));

    this.terminate();
};

ExMinimal.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Minimal Example"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExMinimal.js");
    action.setGroupSortOrder(100000);
    action.setSortOrder(0);
    action.setWidgetNames(["ExamplesMenu"]);
};


