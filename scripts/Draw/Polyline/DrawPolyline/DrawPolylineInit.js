function init(basePath) {
    var action = new RGuiAction(qsTranslate("DrawPolyline", "&Draw Polyline"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DrawPolyline.js");
    action.setIcon(basePath + "/DrawPolyline.svg");
    action.setStatusTip(qsTranslate("DrawPolyline", "Draw polyline with line and arc segments"));
    action.setDefaultShortcut(new QKeySequence("p,l"));
    action.setDefaultCommands(["polyline", "pl"]);
    action.setGroupSortOrder(11010);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawPolylineMenu", "PolylineToolBar", "PolylineToolsPanel", "PolylineMatrixPanel"]);
}
