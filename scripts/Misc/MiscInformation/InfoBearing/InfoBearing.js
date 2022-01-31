// Based on Dovetail example
// By gmpowell71

include("scripts/EAction.js");


/**
 * \class InfoBearing
 * \brief Bearing and azimuth.
 * \ingroup ecma_misc_info
 */
function InfoBearing(guiAction) {
    EAction.call(this, guiAction);

    this.corner1 = undefined;
    this.corner2 = undefined;
}

InfoBearing.prototype = new EAction();

InfoBearing.State = {
    SettingCorner1 : 0,
    SettingCorner2 : 1
};

InfoBearing.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(InfoBearing.State.SettingCorner1);
};

InfoBearing.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case InfoBearing.State.SettingCorner1:
        var trReference = qsTr("Reference");
        this.setCommandPrompt(trReference);
        this.setLeftMouseTip(trReference);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case InfoBearing.State.SettingCorner2:
        var trDirection = qsTr("Direction");
        this.setCommandPrompt(trDirection);
        this.setLeftMouseTip(trDirection);
        this.setRightMouseTip(EAction.trCancel);
        break;
    }

    EAction.showSnapTools();
};

InfoBearing.prototype.escapeEvent = function() {
    switch (this.state) {
    case InfoBearing.State.SettingCorner1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case InfoBearing.State.SettingCorner2:
        this.setState(InfoBearing.State.SettingCorner1);
        break;
    }
};

InfoBearing.prototype.coordinateEvent = function(event) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case InfoBearing.State.SettingCorner1:
        this.corner1 = event.getModelPosition();
        this.setState(InfoBearing.State.SettingCorner2);
        break;

    case InfoBearing.State.SettingCorner2:
        this.corner2 = event.getModelPosition();
        var op = this.getOperation(false);
        if (!isNull(op)) {
            di.applyOperation(op);
            this.setState(InfoBearing.State.SettingCorner1);
            
            var line = new RLine(this.corner1, this.corner2);
            var distance = line.getLength();
            var resultMessage = qsTr("Distance:") + " " + distance;
            var dx1 = line.getEndPoint().x - line.getStartPoint().x;
            var dy1 = line.getEndPoint().y - line.getStartPoint().y;
            var dx = Math.abs(this.corner2.x - this.corner1.x);
            var dy = Math.abs(this.corner2.y - this.corner1.y);

            var bear = undefined;
            var az = undefined;

            if (dx1 >= 0 && dy1 >= 0){
                bear = 90-rad2deg(Math.atan(dy/dx));
                az = 90-rad2deg(Math.atan(dy/dx));
            }
            if (dx1 >= 0 && dy1 < 0){
                bear = 90-rad2deg(Math.atan(dy/dx));
                az = 90+rad2deg(Math.atan(dy/dx));
            }
            if (dx1 < 0 && dy1 < 0){
                bear = 90-rad2deg(Math.atan(dy/dx));
                az = 270-rad2deg(Math.atan(dy/dx));
            }
            if (dx1 < 0 && dy1 >= 0){
                bear = 90-rad2deg(Math.atan(dy/dx));
                az = 270+rad2deg(Math.atan(dy/dx));
            }
            //var angle = rad2deg(Math.atan(dx/dy));
            resultMessage += ",\n" + qsTr("Delta X:") + " " + dx;
            resultMessage += ",\n" + qsTr("Delta Y:") + " " + dy;
            resultMessage += ",\n" + qsTr("Bearing:") + " " + bear;
            resultMessage += ",\n" + qsTr("Azimuth:") + " " + az;

            EAction.handleUserMessage(resultMessage);
        }
        break;
    }
};

InfoBearing.prototype.coordinateEventPreview = function(event) {
    switch (this.state) {
    case InfoBearing.State.SettingCorner2:
        this.corner2 = event.getModelPosition();
        this.updatePreview();
        break;
    default:
        break;

    }
};

InfoBearing.prototype.getOperation = function(preview) {
    var len = this.corner1.getDistanceTo(this.corner2);
    var ang = this.corner1.getAngleTo(this.corner2);
    var op = new RAddObjectsOperation();
    var lineData = new RLineData(this.corner1,this.corner2);
    var line = new RLineEntity(this.getDocument(), lineData);
    return op; 
};

InfoBearing.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Bearing / Azimuth"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InfoBearing.js");
    action.setGroupSortOrder(72500);
    action.setSortOrder(100);
    action.setWidgetNames(["MiscInformationMenu", "MiscInformationToolBar", "MiscInformationToolsPanel"]);
};
