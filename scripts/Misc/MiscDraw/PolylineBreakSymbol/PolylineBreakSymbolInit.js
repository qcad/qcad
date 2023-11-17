function init(basePath) {
    var action = new RGuiAction(qsTranslate("PolylineBreakSymbol", "&Polyline break symbol from 2 points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PolylineBreakSymbol.js");
    action.setStatusTip(qsTranslate("PolylineBreakSymbol", "Draw a polyline break symbol from 2 points"));
    action.setDefaultShortcut(new QKeySequence("S,3"));
    action.setDefaultCommands(["pbreaksymbol", "pbrksym"]);
    action.setGroupSortOrder(54250);
    action.setSortOrder(300);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
