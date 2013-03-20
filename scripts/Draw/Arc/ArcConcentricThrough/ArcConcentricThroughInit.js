function init(basePath) {
    var action = new RGuiAction(qsTranslate("ArcConcentricThrough", "Concentric (&through Point)"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ArcConcentricThrough.js");
    action.setIcon(basePath + "/ArcConcentricThrough.svg");
    action.setStatusTip(qsTranslate("ArcConcentricThrough", "Draw concentric arc through point"));
    action.setDefaultShortcut(new QKeySequence("a,g"));
    action.setDefaultCommands(["arcconcentricthrough", "ag"]);
    action.setSortOrder(600);
    EAction.addGuiActionTo(action, Arc, true, true, true);
}
