function init(basePath) {
    var action = new RGuiAction(qsTranslate("AttributeDefinition", "&Attribute Definition"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/AttributeDefinition.js");
    action.setIcon(basePath + "/AttributeDefinition.svg");
    action.setStatusTip(qsTranslate("AttributeDefinition", "Add an attribute definition"));
    action.setDefaultShortcut(new QKeySequence("b,b"));
    action.setDefaultCommands(["attributedefinition", "attdef", "bb"]);
    action.setSortOrder(1500);
    EAction.addGuiActionTo(action, Draw, true, false, true, true);
}
