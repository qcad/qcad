function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineParallelThrough", "Par&allel (through Point)"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineParallelThrough.js");
    action.setIcon(basePath + "/LineParallelThrough.svg");
    action.setStatusTip(qsTranslate("LineParallelThrough", "Draw parallel line or concentric arc or circle through a given point"));
    action.setDefaultShortcut(new QKeySequence("l,g"));
    action.setDefaultCommands(["lineparallelthrough,lineoffsetthrough,"
        + "offsetthrough", "parallelthrough", "lg"]);
    action.setSortOrder(900);
    EAction.addGuiActionTo(action, Line, true, true, true);
}
