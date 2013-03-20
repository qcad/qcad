function init(basePath) {
    var action = new RGuiAction(qsTranslate("Paste", "&Paste"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Paste.js");
    action.setIcon(basePath + "/Paste.svg");
    action.setDefaultShortcuts([
        new QKeySequence(QKeySequence.Paste),
        new QKeySequence("p,s")
    ]);
    action.setDefaultCommands(["paste", "ps"]);
    action.setSortOrder(800);
    EAction.addGuiActionTo(action, Edit, true, true, false);
}
