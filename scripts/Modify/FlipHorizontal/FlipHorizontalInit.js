function init(basePath) {
    var action = new RGuiAction(qsTranslate("FlipHorizontal", "Flip Hori&zontal"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/FlipHorizontal.js");
    action.setIcon(basePath + "/FlipHorizontal.svg");
    action.setDefaultShortcut(new QKeySequence("f,h"));
    action.setDefaultCommands(["fliphorizontally", "fh"]);
    action.setGroupSortOrder(13100);
    action.setSortOrder(410);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "!ModifyToolsPanel", "ModifyMatrixPanel"]);
}
