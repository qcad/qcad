function init(basePath) {
    var action = new RGuiAction(qsTranslate("About", "&About..."), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/About.js");
    action.setIcon(basePath + "../../qcad_icon.svg");
    action.setSortOrder(999);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false, true);
}
