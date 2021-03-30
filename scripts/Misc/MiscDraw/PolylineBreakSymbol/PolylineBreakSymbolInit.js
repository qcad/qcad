function init(basePath) {
    var action = new RGuiAction(qsTranslate("PolyLineBreakSymbol", "&PolyLine break symbol from 2 points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PolyLineBreakSymbol.js");
    action.setIcon(basePath + "/PolyLineBreakSymbol.svg");
    action.setStatusTip(qsTranslate("PolyLineBreakSymbol", "Draw a polyline break symbol from 2 points"));
    action.setDefaultShortcut(new QKeySequence("S,3"));
    action.setDefaultCommands(["pbreaksymbol", "pbrksym"]);
    action.setGroupSortOrder(54250);
    action.setSortOrder(300);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
