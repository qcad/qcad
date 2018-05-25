include("scripts/EAction.js");

function MyTool(guiAction) {
    EAction.call(this, guiAction);
}

MyTool.prototype = new EAction();

MyTool.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    EAction.handleUserMessage("Hello World");

    this.terminate();
};

MyTool.init = function(basePath) {
    var action = new RGuiAction("&MyTool", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/MyTool.js");
    action.setGroupSortOrder(0);
    action.setSortOrder(0);
    action.setWidgetNames(["MiscMenu"]);
};
