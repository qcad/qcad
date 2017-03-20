function init(basePath) {
    var action = new RGuiAction(qsTranslate("About", "&About..."), RMainWindowQt.getMainWindow());
    action.menuRole = QAction.AboutRole;
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/About.js");
    action.setIcon(basePath + "/../../qcad_icon.png");
    action.setNoState();
    action.setGroupSortOrder(110990);
    action.setSortOrder(100);
    action.setWidgetNames(["HelpMenu", "!HelpToolBar"]);
}
