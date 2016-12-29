function init(basePath) {
    var action = new RGuiAction(qsTranslate("FlipVertical", "Flip Verti&cal"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/FlipVertical.js");
    action.setIcon(basePath + "/FlipVertical.svg");
    action.setDefaultShortcut(new QKeySequence("f,v"));
    action.setDefaultCommands(["flipvertically", "fv"]);
    action.setGroupSortOrder(13100);
    action.setSortOrder(420);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "!ModifyToolsPanel", "ModifyMatrixPanel"]);
}
