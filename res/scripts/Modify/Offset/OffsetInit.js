function init(basePath) {
    var action = new RGuiAction(qsTranslate("Offset", "Offset (with Distance)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Offset.js");
    action.setIcon(basePath + "/Offset.svg");
    action.setStatusTip(qsTranslate("Offset", "Offset line, arc, circle or ellipse"));
    action.setDefaultShortcut(new QKeySequence("o,f"));
    action.setDefaultCommands(["offset", "of"]);
    action.setGroupSortOrder(13150);
    action.setSortOrder(100);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
