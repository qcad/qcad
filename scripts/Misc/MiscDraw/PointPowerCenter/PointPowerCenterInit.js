function init(basePath) {
    var action = new RGuiAction(qsTranslate("PointPowerCenter", "Power center of three circles"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PointPowerCenter.js");
    action.setIcon(basePath + "/PointPowerCenter.svg");
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, MiscDraw, true, true);
}
