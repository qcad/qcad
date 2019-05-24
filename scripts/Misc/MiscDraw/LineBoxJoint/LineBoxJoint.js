/**
 * Copyright (c) 2013 by Matthias Melcher. All rights reserved.
 *
 * This file is an extension of the QCAD project.
 *
 * LineBoxJoint is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LineBoxJoint is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

include("script/EAction.js");

/**
 * \class LineBoxJoint
 * \brief Box joint line between two points.
 * \ingroup ecma_misc_draw
 */
function LineBoxJoint(guiAction) {
  EAction.call(this, guiAction);
  
  this.corner1 = undefined;
  this.corner2 = undefined;
  
  this.fingerHeight = undefined;
  this.fingerLength = undefined;
  this.slotRatio = undefined;
  this.fingerStyle = undefined;

  this.setUiOptions("LineBoxJoint.ui");
}

LineBoxJoint.prototype = new EAction();

LineBoxJoint.State = {
  SettingCorner1 : 0,
  SettingCorner2 : 1
};

LineBoxJoint.prototype.beginEvent = function() {
  EAction.prototype.beginEvent.call(this);
  
  this.setState(LineBoxJoint.State.SettingCorner1);
};

LineBoxJoint.prototype.setState = function(state) {
  EAction.prototype.setState.call(this, state);
  
  this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
  this.setCrosshairCursor();
  
  var appWin = RMainWindowQt.getMainWindow();
  switch (this.state) {
    case LineBoxJoint.State.SettingCorner1:
      var trCorner1 = qsTr("First point");
      this.setCommandPrompt(trCorner1);
      this.setLeftMouseTip(trCorner1);
      this.setRightMouseTip(EAction.trCancel);
      break;
      
    case LineBoxJoint.State.SettingCorner2:
      var trCorner2 = qsTr("Second point");
      this.setCommandPrompt(trCorner2);
      this.setLeftMouseTip(trCorner2);
      this.setRightMouseTip(EAction.trDone);
      break;
  }
  
  EAction.showSnapTools();
};

LineBoxJoint.prototype.escapeEvent = function() {
  switch (this.state) {
    case LineBoxJoint.State.SettingCorner1:
      EAction.prototype.escapeEvent.call(this);
      break;
      
    case LineBoxJoint.State.SettingCorner2:
      this.setState(LineBoxJoint.State.SettingCorner1);
      break;
  }
};

LineBoxJoint.prototype.pickCoordinate = function(event, preview) {
  var di = this.getDocumentInterface();
  
  switch (this.state) {
    case LineBoxJoint.State.SettingCorner1:
      this.corner1 = event.getModelPosition();
      if (!preview) {
        di.setRelativeZero(this.corner1);
        //di.repaintViews();
        this.setState(LineBoxJoint.State.SettingCorner2);
      }
      break;
      
    case LineBoxJoint.State.SettingCorner2:
      this.corner2 = event.getModelPosition();
      if (preview) {
        this.updatePreview();
      }
      else {
        var op = this.getOperation(false);
        if (!isNull(op)) {
          di.applyOperation(op);
          di.setRelativeZero(this.corner2);
          this.setState(LineBoxJoint.State.SettingCorner1);
        }
      }
      break;
  }
};

LineBoxJoint.prototype.getOperation = function(preview) {
  if (isNull(this.corner1) || isNull(this.corner2)) {
    return undefined;
  }
  
  var c1 = this.corner1;
  var c2 = this.corner2;
  var c3 = c2;
  
  var len = this.corner1.getDistanceTo(this.corner2);
  var ang = this.corner1.getAngleTo(this.corner2);
  
  var slotLength = this.fingerLength * this.slotRatio;
  var nFingers = Math.ceil((len-slotLength)/(this.fingerLength+slotLength));
  slotLength = (len-(nFingers*this.fingerLength))/(nFingers+1);

  var op = new RAddObjectsOperation();

  var fingerIn = new RVector();
  fingerIn.setPolar(this.fingerHeight, ang-Math.PI/2.0);
  
  var fingerOut = new RVector();
  fingerOut.setPolar(this.fingerHeight, ang+Math.PI/2.0);

  var fingerEdge = new RVector();
  fingerEdge.setPolar(this.fingerLength, ang);
  
  var slotEdge = new RVector();
  slotEdge.setPolar(slotLength, ang);
  
  
  switch (this.fingerStyle) {
    case 0:
      c2 = c1;
      for (var n=nFingers; n>0; n--) {
        c1 = c2; c2 = c2.operator_add(slotEdge);
        op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
        c1 = c2; c2 = c2.operator_add(fingerIn);
        op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
        c1 = c2; c2 = c2.operator_add(fingerEdge);
        op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
        c1 = c2; c2 = c2.operator_add(fingerOut);
        op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
      }
      c1 = c2; c2 = c2.operator_add(slotEdge);
      op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
      break;
    case 1:
      c2 = c1;
      c1 = c2; c2 = c2.operator_add(fingerIn);
      for (var n=nFingers; n>0; n--) {
        c1 = c2; c2 = c2.operator_add(slotEdge);
        op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
        c1 = c2; c2 = c2.operator_add(fingerOut);
        op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
        c1 = c2; c2 = c2.operator_add(fingerEdge);
        op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
        c1 = c2; c2 = c2.operator_add(fingerIn);
        op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
      }
      c1 = c2; c2 = c2.operator_add(slotEdge);
      op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
      break;
    case 2:
      c2 = c1;
      for (var n=nFingers; n>0; n--) {
        c1 = c2; c2 = c2.operator_add(slotEdge);
        c1 = c2; c2 = c2.operator_add(fingerEdge);
        op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));        
        c3 = c1; c3 = c3.operator_add(fingerIn);
        op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c3)));
        c1 = c3; c3 = c3.operator_add(fingerEdge);
        op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c3)));
        op.addObject(new RLineEntity(this.getDocument(), new RLineData(c3, c2)));
      }
      break;
  }
  
  return op;
};

LineBoxJoint.prototype.slotFingerHeightChanged = function(value) {
  this.fingerHeight = value;
  this.updatePreview(true);
};

LineBoxJoint.prototype.slotFingerLengthChanged = function(value) {
  this.fingerLength = value;
  this.updatePreview(true);
};

LineBoxJoint.prototype.slotSlotRatioChanged = function(value) {
  this.slotRatio = value;
  this.updatePreview(true);
};

LineBoxJoint.prototype.slotFingerStyleChanged = function(value) {
  this.fingerStyle = value;
  this.updatePreview(true);
};


