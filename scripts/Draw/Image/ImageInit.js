function init(basePath) {
    var action = new RGuiAction(qsTranslate("Image", "Insert Bitmap"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Image.js");
    action.setIcon(basePath + "/Image.svg");
    action.setDefaultShortcut(new QKeySequence("i,m"));
    action.setDefaultCommands(["insertbitmap", "bitmap", "im"]);
    action.setSortOrder(1300);
    EAction.addGuiActionTo(action, Draw, true, false, true);
}
