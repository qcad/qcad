/**
 * Copyright (c) 2017 by Christian Aigner, inspired by Matthias Melcher's LineDove script. All rights reserved.
 * 
 * This file is an extension of the QCAD project.
 *
 * LineDove is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LineDove is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

include("scripts/EAction.js");

/**
 * \class LineDove
 * \brief Dovetail joint line between two points.
 * \ingroup ecma_misc_draw
 */
function LineDove(guiAction) {
    EAction.call(this, guiAction);

    this.corner1 = undefined;
    this.corner2 = undefined;
    
    this.dovetailNumber   = undefined;
    this.dovetailHeight   = undefined;
    this.dovetailGradient = undefined;
    this.pinRatio         = undefined;
    
    this.setUiOptions("LineDove.ui");
}

LineDove.prototype = new EAction();

LineDove.State = {
  SettingCorner1 : 0,
  SettingCorner2 : 1
};

LineDove.prototype.beginEvent = function() {
  EAction.prototype.beginEvent.call(this);
  
  this.setState(LineDove.State.SettingCorner1);
};

LineDove.prototype.setState = function(state) {
  EAction.prototype.setState.call(this, state);
  
  this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
  this.setCrosshairCursor();
  
  var appWin = RMainWindowQt.getMainWindow();
  switch (this.state) {
    case LineDove.State.SettingCorner1:
      var trCorner1 = qsTr("First point");
      this.setCommandPrompt(trCorner1);
      this.setLeftMouseTip(trCorner1);
      this.setRightMouseTip(EAction.trCancel);
      break;
      
    case LineDove.State.SettingCorner2:
      var trCorner2 = qsTr("Second point");
      this.setCommandPrompt(trCorner2);
      this.setLeftMouseTip(trCorner2);
      this.setRightMouseTip(EAction.trDone);
      break;
  }
  
  EAction.showSnapTools();
};

LineDove.prototype.escapeEvent = function() {
  switch (this.state) {
    case LineDove.State.SettingCorner1:
      EAction.prototype.escapeEvent.call(this);
      break;
      
    case LineDove.State.SettingCorner2:
      this.setState(LineDove.State.SettingCorner1);
      break;
  }
};

LineDove.prototype.pickCoordinate = function(event, preview) {
  var di = this.getDocumentInterface();
  
  switch (this.state) {
    case LineDove.State.SettingCorner1:
      this.corner1 = event.getModelPosition();
      if (!preview) {
        di.setRelativeZero(this.corner1);
        //di.repaintViews();
        this.setState(LineDove.State.SettingCorner2);
      }
      break;
      
    case LineDove.State.SettingCorner2:
      this.corner2 = event.getModelPosition();
      if (preview) {
        this.updatePreview();
      }
      else {
        var op = this.getOperation(false);
        if (!isNull(op)) {
          di.applyOperation(op);
          di.setRelativeZero(this.corner2);
          this.setState(LineDove.State.SettingCorner1);
        }
      }
      break;
  }
};

LineDove.prototype.getOperation = function(preview) {

  if (isNull(this.corner1) || isNull(this.corner2)) {
    return undefined;
  }
  
  var c1 = this.corner1;
  var c2 = this.corner2;


  // get values from UI
  var nDovetails = this.dovetailNumber;
  var hDovetail  = this.dovetailHeight;
  var gradient   = this.dovetailGradient;
  var ratio      = this.pinRatio;

/*
qDebug("nDovetails", nDovetails);
qDebug("hDovetail", hDovetail);
qDebug("gradient", gradient);
qDebug("ratio", ratio);
qDebug("-------------------------------------------------------");
*/

  // distance and angle between start and end point
  var boardwidth = this.corner1.getDistanceTo(this.corner2);
  var angle = this.corner1.getAngleTo(this.corner2);     
 
  // distance from start of one dovetail to the next dovetail
  var period = boardwidth/nDovetails;

  // length under dovetail slope
  var lUnderDovetailSlope = hDovetail/gradient;
 
  // length of dovetail top
  var lDovetailTop = (period+2*lUnderDovetailSlope)/(1+1/ratio);

  // length of pin bottom
  var lPinBottom = lDovetailTop/ratio;
  
  // length of pin top
  var lPinTop = lPinBottom-2*lUnderDovetailSlope;

  // distance from Dovetail Bottom to Border
  var ldovetailBottomToBorder = lPinBottom/2;

  // distance from Dovetail Top to Border
  var ldovetailTopToBorder = ldovetailBottomToBorder-lUnderDovetailSlope;

  // length of dovetail slope
  var lDovetailSlope = Math.sqrt(hDovetail*hDovetail + lUnderDovetailSlope*lUnderDovetailSlope); 

/*
qDebug("boardwidth = ", boardwidth);
qDebug("period = ", period);
qDebug("lUnderDovetailSlope = ", lUnderDovetailSlope);
qDebug("lDovetailTop = ", lDovetailTop);
qDebug("lPinBottom = ", lPinBottom);
qDebug("lPinTop = ", lPinTop);
qDebug("ldovetailBottomToBorder = ", ldovetailBottomToBorder);
qDebug("ldovetailTopToBorder = ", ldovetailTopToBorder);
qDebug("lDovetailSlope = ", lDovetailSlope);
qDebug("=========================================================");
*/

  // Some sanity check
  if (Math.abs(period-(lDovetailTop+lPinTop)) > 0.001) {
    // something is wrong with the calculation
    qDebug("=== WARNING Calculation Error ===");
    qDebug("period = ", period);
    qDebug("lDovetailTop+lPinTop = ", lDovetailTop+lPinTop);
    qDebug("=================================");
    return undefined;
  }

  /*
   * Prepare the vectors for all edges of the dovetail...
   */
  var dovetailBottomToBorderEdge = new RVector();
  dovetailBottomToBorderEdge.setPolar(ldovetailBottomToBorder, angle);

  var dovetailSlopeLeft = new RVector();
  dovetailSlopeLeft.setPolar(lDovetailSlope, angle+Math.atan(1/gradient)+Math.PI/2.0);

  var dovetailTop = new RVector();
  dovetailTop.setPolar(lDovetailTop, angle);
  
  var dovetailSlopeRight = new RVector();
  dovetailSlopeRight.setPolar(lDovetailSlope, angle-Math.atan(1/gradient)-Math.PI/2.0);
  
  var dovetailPinBottom = new RVector();
  dovetailPinBottom.setPolar(lPinBottom, angle);

  // let's draw some dovetails...
  var op = new RAddObjectsOperation();
  
  // First draw lead-in
  c2 = c1.operator_add(dovetailBottomToBorderEdge);
  op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
  
  // now draw all dovetails

  for (var i=nDovetails; i>0; i--) {
    c1 = c2; 
    c2 = c2.operator_add(dovetailSlopeLeft);
    op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
  
    c1 = c2; 
    c2 = c2.operator_add(dovetailTop);
    op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2))); 
  
    c1 = c2; 
    c2 = c2.operator_add(dovetailSlopeRight);
    op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2))); 

    if (i>1) {
      c1 = c2; 
      c2 = c2.operator_add(dovetailPinBottom);
      op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2))); 
    }
  }

  // Lastly draw lead-out
  c1 = c2; 
  c2 = c2.operator_add(dovetailBottomToBorderEdge);
  op.addObject(new RLineEntity(this.getDocument(), new RLineData(c1, c2)));
    
  return op;
};


LineDove.prototype.slotDovetailNumberChanged = function(value) {
  this.dovetailNumber = value;
  this.updatePreview(true);
};

LineDove.prototype.slotDovetailHeightChanged = function(value) {
  this.dovetailHeight = value;
  this.updatePreview(true);
};

LineDove.prototype.slotDovetailGradientChanged = function(value) {
  this.dovetailGradient = value;
  this.updatePreview(true);
};

LineDove.prototype.slotPinRatioChanged = function(value) {
  this.pinRatio = value;
  this.updatePreview(true);
};

