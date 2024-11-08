function init(basePath) {
    var action = new RGuiAction(qsTranslate("Image", "&Insert Bitmap") + "…", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Image.js");
    action.setDefaultShortcut(new QKeySequence("i,m"));
    action.setDefaultCommands(["insertbitmap", "bitmap", "im"]);
    action.setGroupSortOrder(30);
    action.setSortOrder(400);
    action.setWidgetNames(["DrawMenu", "DrawToolBar", "MainToolsPanel", "DrawMatrixPanel"]);
}
