function init(basePath) {
    var action = new RGuiAction(qsTranslate("OffsetThrough", "Offset (through Point)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/OffsetThrough.js");
    action.setIcon(basePath + "/OffsetThrough.svg");
    action.setStatusTip(qsTranslate("OffsetThrough", "Offset line, arc, circle or ellipse through point"));
    action.setDefaultShortcut(new QKeySequence("o,h"));
    action.setDefaultCommands(["offsetthrough", "oh"]);
    action.setGroupSortOrder(13150);
    action.setSortOrder(200);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
