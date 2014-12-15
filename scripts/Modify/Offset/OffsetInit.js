function init(basePath) {
    var action = new RGuiAction(qsTranslate("Offset", "Offset (with Distance)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Offset.js");
    action.setIcon(basePath + "/Offset.svg");
    action.setStatusTip(qsTranslate("Offset", "Draw parallel to existing line or concentric arc, circle"));
    action.setDefaultShortcuts([ new QKeySequence("l,p"), new QKeySequence("p,a"), new QKeySequence("o,f") ]);
    action.setDefaultCommands([
        "lineparallel", "lineoffset", "offset",
        "o", "parallel", "par",
        "lp", "pa", "of"
    ]);
    action.setGroupSortOrder(13150);
    action.setSortOrder(100);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel"]);
}
