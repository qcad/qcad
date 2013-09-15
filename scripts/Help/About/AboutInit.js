function init(basePath) {
    var action = new RGuiAction(qsTranslate("About", "&About..."), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/About.js");
    action.setIcon(basePath + "/../../qcad_icon.png");
    action.setSortOrder(2000);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false, true);
}
