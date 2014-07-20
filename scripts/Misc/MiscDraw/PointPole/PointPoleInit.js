function init(basePath) {
    var action = new RGuiAction(qsTranslate("PointPole", "Pole of Line and Circle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PointPole.js");
    action.setIcon(basePath + "/PointPole.svg");
    action.setSortOrder(300);
    EAction.addGuiActionTo(action, MiscDraw, true, true);
}
