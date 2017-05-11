function init(basePath) {
    var action = new RGuiAction(qsTranslate("InsertScriptItem", "Insert &Script"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setUniqueGroup("InsertBlockItem");
    action.setScriptFile(basePath + "/InsertScriptItem.js");
    action.setIcon(basePath + "/InsertScriptItem.svg");
}
