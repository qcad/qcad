//Based on Dovetail example
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
        //di.setRelativeZero(this.corner1);
        this.setState(InfoBearing.State.SettingCorner2);
        break;

    case InfoBearing.State.SettingCorner2:
        this.corner2 = event.getModelPosition();
        //di.setRelativeZero(this.corner2);
        var op = this.getOperation(false);
        if (!isNull(op)) {
            di.applyOperation(op);
            this.setState(InfoBearing.State.SettingCorner1);
            
            var line = new RLine(this.corner1, this.corner2);
            var distance = line.getLength();
            var resultMessage = qsTr("Distance:") + " " + distance.toFixed(2);
            var dx1 = line.getEndPoint().x - line.getStartPoint().x;
            var dy1 = line.getEndPoint().y - line.getStartPoint().y;
            var dx = Math.abs(this.corner2.x - this.corner1.x);
            var dy = Math.abs(this.corner2.y - this.corner1.y);

           //var angle = rad2deg(line.getAngle());
            if (dx1 > 0 && dy1 > 0){
                var Bear = 90-rad2deg(Math.atan(dy/dx));
                var Az = 90-rad2deg(Math.atan(dy/dx));
                //var c1 = "\u004E";
                //var c2 = "\u00E9";
                var c1 = "N";
                var c2 = "E";

            }
            if (dx1 > 0 && dy1 < 0){
                var Bear = 90-rad2deg(Math.atan(dy/dx));
                var Az = 90+rad2deg(Math.atan(dy/dx));
                //var c1 = "\u004E";
                //var c2 = "\u00E9";
                var c1 = "S";
                var c2 = "E";
            }
            if (dx1 < 0 && dy1 < 0){
                var Bear = 90-rad2deg(Math.atan(dy/dx));
                var Az = 270-rad2deg(Math.atan(dy/dx));
                //var c1 = "\u004E";
                //var c2 = "\u00E9";
                var c1 = "S";
                var c2 = "W";
            }
            if (dx1 < 0 && dy1 > 0){
                var Bear = 90-rad2deg(Math.atan(dy/dx));
                var Az = 270+rad2deg(Math.atan(dy/dx));
                //var c1 = "\u004E";
                //var c2 = "\u00E9";
                var c1 = "N";
                var c2 = "W";
            }
            if (dx1 == 0 && dy1 > 0){
                var Bear = 0;
                var Az = 0;
                var c1 = "";
                var c2 = " ";
            }
            if (dx1 == 0 && dy1 < 0){
                var Bear = 0;
                var Az = 180;
                var c1 = "S";
                var c2 = " ";
            }
            if (dx1 > 0 && dy1 == 0){
                var Bear = 90;
                var Az = 90;
                var c1 = " ";
                var c2 = "E";
            }
            if (dx1 < 0 && dy1 == 0){
                var Bear = 90;
                var Az = 270;
                var c1 = " ";
                var c2 = "W";
            }
            //var angle = rad2deg(Math.atan(dx/dy));
            var BDeg = Math.floor(Bear);
            var BMin = Math.floor((Bear - Math.floor(Bear)) * 60);
            var BSec = (((Bear - Math.floor(Bear)) * 60 - BMin) * 60).toFixed(2);
            var zdeg = Math.floor(Az);
            var zmin = Math.floor((Az - Math.floor(Az)) * 60);
            var zsec = (((Az - Math.floor(Az)) * 60 - zmin) * 60).toFixed(2);
            
            resultMessage += ",\n" + qsTr("Bearing:") + " " + c1 + BDeg + "\u00B0" + BMin + "\u0022" + BSec + "\u0027" + c2 + "[" + Bear.toFixed(4) + "]";
            resultMessage += ",\n" + qsTr("Azimuth:") + " " + zdeg + "\u00B0" + zmin + "\u0022" + zsec + "\u0027" + "[" + Az.toFixed(4) + "]";
            //resultMessage += ",\n" + qsTr("Delta X:") + " " + dx.toFixed(2);
            //resultMessage += ",\n" + qsTr("Delta Y:") + " " + dy.toFixed(2);
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
    //line.scale(len/20);
    //line.move(this.corner1);
    //line.rotate(ang, this.corner1);
    //op.addObject(line);

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
