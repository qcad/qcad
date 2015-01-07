function init(basePath) {
    var action = new RGuiAction(qsTranslate("OffsetThrough", "Offset (through Point)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/OffsetThrough.js");
    action.setIcon(basePath + "/OffsetThrough.svg");
    action.setStatusTip(qsTranslate("OffsetThrough", "Offset line, arc, circle, ellipse or polyline through a given point"));
    action.setDefaultShortcut(new QKeySequence("l,g"));
    action.setDefaultCommands(["lineparallelthrough", "lineoffsetthrough", "offsetthrough", "parallelthrough", "lg"]);
    action.setGroupSortOrder(13150);
    action.setSortOrder(200);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel"]);
}
