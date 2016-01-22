function init(basePath) {
    var action = new RGuiAction(qsTranslate("TranslateRotate", "M&ove and Rotate"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/TranslateRotate.js");
    action.setIcon(basePath + "/TranslateRotate.svg");
    action.setDefaultShortcut(new QKeySequence("m,r"));
    action.setDefaultCommands(["moverotate", "mr"]);
    action.setGroupSortOrder(13100);
    action.setSortOrder(500);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
