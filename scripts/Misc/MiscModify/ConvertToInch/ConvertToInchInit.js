function init(basePath) {
    var action = new RGuiAction(qsTranslate("ConvertToInch", "Convert Drawing to &Inches"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ConvertToInch.js");
    action.setIcon(basePath + "/ConvertToInch.svg");
    action.setDefaultCommands(["converttoinch"]);
    action.setNoState();
    action.setGroupSortOrder(56100);
    action.setSortOrder(350);
    action.setWidgetNames(["MiscModifyMenu", "MiscModifyToolBar", "MiscModifyToolsPanel"]);
}
