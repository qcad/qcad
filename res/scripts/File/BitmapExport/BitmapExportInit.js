function init(basePath) {
    var action = new RGuiAction(qsTranslate("BitmapExport", "Bit&map Export..."), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/BitmapExport.js");
    action.setIcon(basePath + "/BitmapExport.svg");
    action.setDefaultShortcut(new QKeySequence("x,b"));
    action.setDefaultCommands( [ "bitmapexport" ]);
    action.setGroupSortOrder(1200);
    action.setSortOrder(100);
    action.setWidgetNames(["FileMenu", "!FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
