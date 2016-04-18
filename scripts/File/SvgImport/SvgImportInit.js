function init(basePath) {
    var action = new RGuiAction(qsTranslate("SvgImport", "SVG &Import..."), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SvgImport.js");
    action.setIcon(basePath + "/SvgImport.svg");
    action.setDefaultCommands( [ "svgimport" ]);
    action.setGroupSortOrder(1300);
    action.setSortOrder(300);
    action.setWidgetNames(["FileMenu", "!FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
