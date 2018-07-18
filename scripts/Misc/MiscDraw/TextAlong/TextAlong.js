/**
 * Copyright (c) 2017 by Robert S. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

/**
 * \defgroup ecma_draw_text TextAlong Drawing Tool
 * \ingroup ecma_draw
 *
 * \brief This module contains the ECMAScript implementation of the text along an entity
 * drawing tool.
 */
include("scripts/Draw/Draw.js");
include("scripts/WidgetFactory.js");
include("scripts/Draw/Text/TextDialog/TextDialog.js");

/**
 * \class TextAlong
 * \brief Insert text along an entity.
 * \ingroup ecma_misc_draw
 */
function TextAlong(guiAction, mode) {
    if (isNull(mode)) {
        mode = TextDialog.Mode.Text;
    }

    Draw.call(this, guiAction);

    this.textData = undefined;
    this.mode = mode;
    this.shape = undefined;
    this.text = undefined;
    this.height = 1.0;
    this.spacing = 0.0;
    this.pos = undefined;
    this.ccw = false;
    this.fit = false;
    this.CharWidths = [];
    this.totalCharWidth = 0.0;

    this.setUiOptions("TextAlong.ui");
}

TextAlong.prototype = new Draw();

TextAlong.State = {
    ChoosingEntity : 0,
    SettingPosition : 1
};

TextAlong.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    var dialog = new TextDialog(this.mode);
    this.textData = dialog.show();
    if (isNull(this.textData)) {
        this.terminate();
        return;
    }

    var optionsToolBar = EAction.getOptionsToolBar();

    var contentsEdit = optionsToolBar.findChild("Contents");
    WidgetFactory.initLineEdit(contentsEdit, false);
    contentsEdit.text = this.textData.getEscapedText();
    var heightEdit = optionsToolBar.findChild("Height");
    var ht = heightEdit.getValue();
    this.textData.setTextHeight(ht);

    // generate list of char widths
    this.getCharWidths();

    this.setState(TextAlong.State.ChoosingEntity);
};

TextAlong.prototype.setState = function(state) {
    Draw.prototype.setState.call(this, state);

    var appWin = RMainWindowQt.getMainWindow();
    this.setCrosshairCursor();

    switch (this.state) {
    case TextAlong.State.ChoosingEntity :
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.setCommandPrompt(qsTr("Select Entity"));
        this.setLeftMouseTip(qsTr("Select Entity"));
        this.setRightMouseTip(EAction.trCancel);
        EAction.showSnapTools();
        break;
    case TextAlong.State.SettingPosition :
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        this.setCommandPrompt(qsTr("Position"));
        this.setLeftMouseTip(qsTr("Position"));
        this.setRightMouseTip(EAction.trCancel);
        EAction.showSnapTools();
        break;
    }
};

TextAlong.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    this.pos = event.getModelPosition();

    if (isNull(entity)) {
        this.shape = undefined;
        return;
    } else {
        if (!preview) {
            this.shape = getClosestSimpleShape(entity, this.pos);
            if (!isNull(this.shape)) {
                var type = this.shape.getShapeType();
                if (type !== RShape.Line && type !== RShape.Arc && type !== RShape.Circle) {
                    EAction.warnNotLineArcCircle();
                    return;
                }

                this.setState(TextAlong.State.SettingPosition);
            }
        }
    }
};

TextAlong.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    this.pos = event.getModelPosition();
    if (!preview) {
        di.setRelativeZero(this.pos);
    }
    this.textData.setAlignmentPoint(this.pos);

    this.text = new RTextEntity(this.getDocument(), this.textData);

    var op = this.getOperation(preview);
    if (preview) {
        di.previewOperation(op);
    }
    else {
        if (!isNull(op)) {
            di.applyOperation(op);
        }
    }
};

TextAlong.prototype.getOperation = function(preview) {
    var di = this.getDocumentInterface();
    var type;

    if (!isNull(this.shape)) {
        type = this.shape.getShapeType();
    } else {
        return undefined;
    }

    var op = undefined;
    var arc;
    switch(type) {
    case RShape.Line:
        op = this.alongLine();
        break;
    case RShape.Arc:
        // 'this.shape' is a pointer to the arc, so get the actual arc object
        arc = this.shape;
        op = this.alongArc(arc);
        break;
    case RShape.Circle:
        // create a circular arc and use 'alongArc'.
        // when using 'fit', add one or more spaces to the start or end of the text
        arc = new RArc(this.shape.getCenter(), this.shape.getRadius(), 0.0, 0.0);
        op = this.alongArc(arc);
        break;
    default :
        break;
    }
    return op;
}

TextAlong.prototype.getCharWidths = function() {
    if (isNull(this.textData)) {
        return;
    }

    this.text = new RTextEntity(this.getDocument(), this.textData);
    var txt = this.text.getPlainText();
    var num = txt.length;
    this.CharWidths = [];
    this.totalCharWidth = 0.0;

    for (var i = 0; i < num; i++) {
        var char = txt[i];
        // A space character is returned as zero width
        if (char === " ") {
            char = "-";
        }
        var td = this.getTextData(char);
        var wid = td.getWidth();
        this.CharWidths.push(wid + this.spacing);
        this.totalCharWidth += wid + this.spacing;
    }
}

TextAlong.prototype.getTextData = function(txt) {
    var td = new RTextData();
    if (this.pos !== undefined) {
        td.setAlignmentPoint(this.pos);
    }
    td.setVAlign(this.textData.getVAlign());
    td.setHAlign(this.textData.getHAlign());
    td.setText(txt);
    td.setTextHeight(this.textData.getTextHeight());
    td.setTextWidth(this.textData.getTextWidth());
    td.setFontName(this.textData.getFontName());
    td.setAngle(this.textData.getAngle());
    td.setBold(this.textData.isBold());
    td.setItalic(this.textData.isItalic());
    td.setLineSpacingFactor(this.textData.getLineSpacingFactor());
    return td;
}

TextAlong.prototype.slotContentsChanged = function(value) {
    if (isNull(this.textData)) {
        return;
    }

    this.textData.setText(value);
    // change list of char widths
    this.getCharWidths();

};

TextAlong.prototype.slotHeightChanged = function(value) {
    if (isNull(this.textData)) {
        return;
    }

    this.height = value;
    this.textData.setTextHeight(this.height);
    // change list of char widths
    this.getCharWidths();

};

TextAlong.prototype.slotSpacingChanged = function(value) {
    this.spacing = value;
    this.getCharWidths();
};

TextAlong.prototype.slotDirectionChanged = function(button) {
    if (!isQObject(button) || button.checked !== true) {
        return;
    }

    if (button.objectName === "Clockwise") {
        this.ccw = false;
    }
    else {
        this.ccw = true;
    }
};

TextAlong.prototype.slotFitChanged = function(value) {
    this.fit = value;
};

TextAlong.prototype.alongLine = function() {
    var ang, len, op, h, v;

    ang = this.shape.getAngle();
    len = this.shape.getLength();
    if (!isNull(this.textData)) {
        if (this.ccw) {
            this.textData.setAngle(ang + Math.PI);
        } else {
            this.textData.setAngle(ang);
        }
    }
    op = new RAddObjectsOperation();
    if (this.fit) {
        var txt = this.text.getPlainText();
        var num = txt.length;
        var firstCharWidth = this.CharWidths[0];
        var lastCharWidth = this.CharWidths[num - 1];
        var dist = (len - firstCharWidth) / (num - 1);

        // now position 'this.pos'
        v = new RVector();
        h = this.textData.getHAlign();
        if (h === RS.HAlignRight) {
            v.setPolar(len, this.textData.getAngle() + Math.PI);
            this.pos = this.pos.operator_add(v);
        } else if (h === RS.HAlignCenter) {
            v.setPolar(len / 2.0, this.textData.getAngle() + Math.PI);
            this.pos = this.pos.operator_add(v);
        }

        for (var i = 0; i < num; i++) {
            var td = this.getTextData(txt[i]);
            var te = new RTextEntity(this.getDocument(), td);

            te.setSimple(true);     // This is required so 'base' and 'bottom' points are correct

            te.setVAlign(this.textData.getVAlign());
            te.setHAlign(RS.HAlignCenter);
            v.setPolar((dist * i) + (firstCharWidth / 2.0), te.getAngle());
            var pt = this.pos.operator_add(v);
            te.setAlignmentPoint(pt);
            op.addObject(te);

        }
    } else {
        op.addObject(this.text);
    }
    return op;
}

TextAlong.prototype.alongArc = function(arc) {
    var ang, op;

    op = new RAddObjectsOperation();
    var txt = this.text.getPlainText();
    var num = txt.length;

    // use distance from 'this.pos' to centre point of arc, as radius
    arc.setRadius(arc.center.getDistanceTo(this.pos));
    var pt = this.pos;
    ang = arc.center.getAngleTo(this.pos);

    var arcrad = arc.getRadius();

    // calculate spacing for 'Fit' option
    if (this.fit) {
        // subtract half the width of first character and last character
        var firstcharAngle = ((this.CharWidths[0]) / arcrad) / 2.0;
        var lastcharAngle = ((this.CharWidths[num - 1]) / arcrad) / 2.0;
        var fitAngle = (arc.getSweep() - firstcharAngle - lastcharAngle) / (num - 1);
    }

    var td = this.getTextData(txt[0]);
    var te = new RTextEntity(this.getDocument(), td);
    var h = te.getHAlign();
    var v = te.getVAlign();

    // set rotation angle for first character
    var rotateAngle, sweep;
    var width = this.totalCharWidth;
    if (this.fit) {
        sweep = arc.getSweep();
    } else {
        sweep = width / arcrad;
    }
    if (h === RS.HAlignLeft) {
        rotateAngle = 0.0;
    } else if (h === RS.HAlignCenter) {
        rotateAngle = sweep / 2.0;
    } else {
        rotateAngle = sweep;
    }

    // get angle for half the first characters width
    // and subtract from rotateAngle
    var halfAngle = ((this.CharWidths[0]) / arcrad) / 2.0;
    rotateAngle -= halfAngle;

    if (this.ccw) {
        rotateAngle = -rotateAngle;
    }

    for (var i = 0; i < num; i++) {
        td = this.getTextData(txt[i]);
        te = new RTextEntity(this.getDocument(), td);
        h = te.getHAlign();
        v = te.getVAlign();

        te.setHAlign(RS.HAlignCenter);
        te.setSimple(true);     // This is required so 'base' and 'bottom' points are correct
        te.setAlignmentPoint(pt);
        if (this.ccw) {
            te.setAngle(ang + (Math.PI / 2.0));
        } else {
            te.setAngle(ang - (Math.PI / 2.0));
        }

        // draw each character at 'this.pos', and rotate to match alignment point
        te.rotate(rotateAngle, arc.center);

        op.addObject(te);

        // adjust point and angle for next character
        // function 'getCharWidths' handles spacing
        var currentcharAngle = (this.CharWidths[i]) / arcrad;
        var nextcharAngle = (this.CharWidths[i + 1]) / arcrad;
        var charAngle = (currentcharAngle / 2.0) + (nextcharAngle / 2.0);

        if (this.ccw) {
            if (this.fit) {
                rotateAngle = rotateAngle + fitAngle;
            } else {
                rotateAngle = rotateAngle + charAngle;
            }
        } else {
            if (this.fit) {
                rotateAngle = rotateAngle - fitAngle;
            } else {
                rotateAngle = rotateAngle - charAngle;
            }
        }
    }

    return op;
}
