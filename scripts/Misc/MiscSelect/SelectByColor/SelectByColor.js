/**
 * Copyright (c) 2011-2018 by RibbonSoft, GmbH. All rights reserved.
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

include("scripts/EAction.js");

/**
 * \class SelectByColor
 * \ingroup ecma_misc_select
 * \author Stephen Casner (slcasner)
 *
 * \brief Selects entities by their color.
 */
function SelectByColor(guiAction) {
    EAction.call(this, guiAction);
}

SelectByColor.prototype = new EAction();
SelectByColor.includeBasePath = includeBasePath;

SelectByColor.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    var document = this.getDocument();
    var selected = document.querySelectedEntities();
    var desiredColor = undefined;
    var name;
    var localName;
    var e, entityId, entity, color;

    for (e = 0; e < selected.length; ++e) {
        entityId = selected[e];
        entity = document.queryEntityDirect(entityId);
        color = entity.getDisplayColor();
        localName = color.getName();
        name = color.name();
        if (typeof(desiredColor) == 'undefined') {
            desiredColor = name;
        } else {
            if (name != desiredColor) {
                desiredColor = undefined;
                break;
            }
        }
    }

    if (typeof(desiredColor) == 'undefined') {
        EAction.handleUserWarning(qsTr("Select one or more objects only of the desired color"));
    } else {
        var visible = document.queryAllVisibleEntities();
        var entityIdsToSelect = [];
        for (e = 0; e < visible.length; ++e) {
            entityId = visible[e];
            entity = document.queryEntity(entityId);
            color = entity.getDisplayColor();
            name = color.name();
            if (name == desiredColor) {
                entityIdsToSelect.push(entityId);
            }
        }
        if (entityIdsToSelect.length!==0) {
            di.selectEntities(entityIdsToSelect);
        }
        EAction.handleUserMessage(qsTr("Selected all visible entities of color %1").arg(localName));
    }

    EAction.activateMainWindow();
    this.terminate();
};
