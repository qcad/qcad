function init(basePath) {
    var action = new RGuiAction(qsTranslate("Scale", "&Scale"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Scale.js");
    action.setDefaultShortcut(new QKeySequence("s,z"));
    action.setDefaultCommands(["scale", "sz"]);
    action.setGroupSortOrder(13100);
    action.setSortOrder(300);
    action.setWidgetNames(["ModifyTransformMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
