/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
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

include("../Translate/Translate.js");

/**
 * \class TranslateRotate
 * \brief Translates and rotates selected entities. Supports multiple copies.
 * \ingroup ecma_modify
 */
function TranslateRotate(guiAction) {
    Translate.call(this, guiAction);

    this.angle = 0.0;

    this.setUiOptions("TranslateRotate.ui");
}

TranslateRotate.prototype = new Translate();

TranslateRotate.includeBasePath = includeBasePath;

/**
 * Shows the translation rotation dialog.
 *
 * \return True if the dialog was accepted, false if it was canceled.
 */
TranslateRotate.prototype.showDialog = function() {
    var dialog = WidgetFactory.createDialog(TranslateRotate.includeBasePath, "TranslateRotateDialog.ui");
    WidgetFactory.restoreState(dialog);

    var widgets = getWidgets(dialog);

    // initialize dialog angle to angle used in tool options toolbar:
    widgets["Angle"].setValue(this.angle);

    if (!dialog.exec()) {
        dialog.destroy();
        EAction.activateMainWindow();
        return false;
    }

    if (widgets["DeleteOriginal"].checked===true) {
        this.copies = 0;
    }
    else if (widgets["KeepOriginal"].checked===true) {
        this.copies = 1;
    }
    else {
        this.copies = widgets["NumberOfCopies"].getValue();
    }

    this.angle = widgets["Angle"].getValue();
    this.useCurrentAttributes = (widgets["UseCurrentAttributes"].checked===true);

    WidgetFactory.saveState(dialog);

    dialog.destroy();
    EAction.activateMainWindow();
    return true;
};

TranslateRotate.prototype.getOperation = function(preview, selectResult) {
    // skip implementation from class Translate and use
    // Transform implementaiton instead:
    return Transform.prototype.getOperation.call(this, preview, selectResult);
};

/**
 * Callback function for Transform.getOperation.
 */
TranslateRotate.prototype.transform = function(entity, k, op, preview, flags) {
    entity.rotate(this.angle * k, this.referencePoint);
    var delta = this.targetPoint.operator_subtract(this.referencePoint);
    entity.move(delta.operator_multiply(k));
    op.addObject(entity, flags);
};

TranslateRotate.prototype.slotAngleChanged = function(value) {
    this.angle = value;
};

