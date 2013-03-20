function init(basePath) {
    var action = new RGuiAction(qsTranslate("SvgImport", "SVG &Import..."), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SvgImport.js");
    action.setIcon(basePath + "/SvgImport.svg");
    action.setDefaultCommands( [ "svgimport" ]);
    action.setSortOrder(2300);
    //action.setNoState();
    EAction.addGuiActionTo(action, File, true, false, false, false);
}
