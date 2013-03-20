function init(basePath) {
    var action = new RGuiAction(qsTranslate("LinePolygonCP", "Pol&ygon (Center, Point)"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LinePolygonCP.js");
    action.setIcon(basePath + "/LinePolygonCP.svg");
    action.setStatusTip(qsTranslate("LinePolygonCP", "Draw regular polygon from center and corner point"));
    action.setDefaultShortcut(new QKeySequence("p,g,1"));
    action.setDefaultCommands(["linepolygon", "polygon", "pg1"]);
    action.setSortOrder(1400);
    EAction.addGuiActionTo(action, Line, true, true, true, true);
}
