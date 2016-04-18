function init(basePath) {
    var action = new RGuiAction(qsTranslate("InsertBlockItem", "&Insert Block"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setUniqueGroup("InsertBlockItem");
    action.setScriptFile(basePath + "/InsertBlockItem.js");
    action.setIcon(basePath + "/InsertBlockItem.svg");
}
