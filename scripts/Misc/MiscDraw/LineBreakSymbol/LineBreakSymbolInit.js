function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineBreakSymbol", "&Line break symbol from 2 points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineBreakSymbol.js");
    action.setIcon(basePath + "/LineBreakSymbol.svg");
    action.setStatusTip(qsTranslate("LineBreakSymbol", "Draw a line break symbol from 2 points"));
    action.setDefaultShortcut(new QKeySequence("S,2"));
    action.setDefaultCommands(["breaksymbol", "brksym"]);
    action.setGroupSortOrder(54250);
    action.setSortOrder(300);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
