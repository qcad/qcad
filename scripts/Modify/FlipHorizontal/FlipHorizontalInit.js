function init(basePath) {
    var action = new RGuiAction(qsTranslate("FlipHorizontal", "Flip Hori&zontal"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/FlipHorizontal.js");
    action.setDefaultShortcut(new QKeySequence("f,h"));
    action.setDefaultCommands(["fliphorizontally", "fh"]);
    action.setGroupSortOrder(13100);
    action.setSortOrder(410);
    action.setWidgetNames(["ModifyTransformMenu", "ModifyToolBar", "!ModifyToolsPanel", "ModifyMatrixPanel"]);
}
