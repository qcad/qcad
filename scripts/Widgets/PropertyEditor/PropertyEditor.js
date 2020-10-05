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

include("scripts/EAction.js");
include("scripts/sprintf.js");
include("../../WidgetFactory.js");

/**
 * Internal helper class. Notified when properties are changed.
 */
function PropertyWatcher(propertyEditor, sender, propertyType) {
    this.propertyEditor = propertyEditor;
    this.sender = sender;
    this.propertyType = propertyType;
}

/**
 * Called when a property has been changed by the user. Triggers
 * a transaction to change the propery of all selected entities
 * that match the current entity type filter.
 */
PropertyWatcher.prototype.propertyChanged = function(value) {
    // TODO:
    // only do something if the value has actually changed
    // remember edited status of widgets

    var attributes = this.propertyEditor.getPropertyAttributes(this.propertyType);

    var typeHint = 0;

    // value is a list property (e.g. x coordinate of a vertex of a polyline):
    if (attributes.isList()) {
        var indexControlObjectName =
            PropertyEditorImpl.getIndexControlObjectName(this.propertyType.getPropertyGroupTitle());
        var indexControl = this.propertyEditor.widget.findChild(indexControlObjectName);
        var index = indexControl.value;
        value = this.sender.getValue();
        if (!isNumber(value)) {
            return;
        }
        this.propertyEditor.listPropertyChanged(this.propertyType, index, value);
        return;
    }

    // value comes from a combo box:
    else if (isComboBox(this.sender)) {

        // value is index of combo box:
        if (isNumber(value)) {
            if (this.sender.itemData(value)===PropertyEditor.varies) {
                return;
            }
            this.propertyEditor.propertyChanged(this.propertyType,
                                                this.sender.itemData(value));
            return;
        }

        if (value===PropertyEditor.varies) {
            return;
        }
    }

    // value is string from a line edit (e.g. text contents):
    else if (this.sender.toString()==="QLineEdit") {
        value = this.sender.text;
        if (value===PropertyEditor.varies) {
            return;
        }
    }

    // value is number from a math line edit:
    else if (this.sender.toString().startsWith("RMathLineEdit")) {
        if (this.sender.text===this.sender.originalText) {
            return;
        }
        this.sender.setProperty("originalText", this.sender.text);
        value = this.sender.getValue();
        if (isNaN(value)) {
            this.propertyEditor.updateGui(true);
            return;
        }
        if (this.sender.isInteger()) {
            typeHint = 2;
        }
    }

    this.propertyEditor.propertyChanged(this.propertyType, value, typeHint);
};

/**
 * Called when a custom property has been deleted by the user. Triggers
 * a transaction to delete the propery from all selected entities
 * that match the current entity type filter.
 */
PropertyWatcher.prototype.propertyRemoved = function() {
    this.propertyEditor.propertyChanged(this.propertyType, null);
    this.propertyEditor.onlyChangesOverride = false;
};




/**
 * Internal helper class. Notified when indices of list properties are changed.
 */
function IndexWatcher(propertyEditor, sender, propertyType) {
    this.propertyEditor = propertyEditor;
    this.sender = sender;
    this.propertyType = propertyType;
}

/**
 * Called when the index of a list property has changed and the list value
 * needs to be changed to show the list entry at the new index.
 */
IndexWatcher.prototype.indexChanged = function(index) {
    var objectName = PropertyEditorImpl.getControlObjectName(this.propertyType);
    var control = this.propertyEditor.widget.findChild(objectName);
    this.propertyEditor.initNumberControls(objectName, this.propertyType, true, control, index);

    var indexControlObjectName =
        PropertyEditorImpl.getIndexControlObjectName(this.propertyType.getPropertyGroupTitle());
    var indexControl = this.propertyEditor.widget.findChild(indexControlObjectName);

    if (isNull(indexControl.controlNames)) {
        return;
    }

    var di = EAction.getDocumentInterface();
    if (isNull(di)) {
        return;
    }

    if (isNull(indexControl.controlNames[0]) || isNull(indexControl.controlNames[1])) {
        return;
    }

    var controlX = this.propertyEditor.widget.findChild(indexControl.controlNames[0]);
    var controlY = this.propertyEditor.widget.findChild(indexControl.controlNames[1]);

    if (isNull(controlX) || isNull(controlY)) {
        return;
    }

    var x = controlX.getValue();
    var y = controlY.getValue();

    var view = di.getLastKnownViewWithFocus();
    if (isNull(view)) {
        return;
    }


    // preview postition in drawing:
    di.clearPreview();
    var r = view.mapDistanceFromView(10);
    di.addAuxShapeToPreview(new RCircle(new RVector(x, y), r));
    di.addAuxShapeToPreview(new RLine(new RVector(x-r, y), new RVector(x+r, y)));
    di.addAuxShapeToPreview(new RLine(new RVector(x, y-r), new RVector(x, y+r)));
    di.repaintViews();
};



/**
 * \class PropertyEditorImpl
 * \brief Property editor implementation.
 * \ingroup ecma_widgets
 */
function PropertyEditorImpl(basePath) {
    RPropertyEditor.call(this);

    this.setEntityTypeFilter(RS.EntityAll);
    this.widget = WidgetFactory.createWidget(basePath, "PropertyEditor.ui");
    this.basePath = basePath;

    this.colon = qsTr(":");

    this.widget.findChild("LabelLayer").text = RSettings.translate("REntity", "Layer") + this.colon;
    this.widget.findChild("LabelColor").text = RSettings.translate("REntity", "Color") + this.colon;
    this.widget.findChild("LabelLineweight").text = RSettings.translate("REntity", "Lineweight") + this.colon;
    this.widget.findChild("LabelLinetype").text = RSettings.translate("REntity", "Linetype") + this.colon;
    this.widget.findChild("LabelLinetypeScale").text = RSettings.translate("REntity", "Linetype Scale") + this.colon;
    this.widget.findChild("LabelDrawOrder").text = RSettings.translate("REntity", "Draw Order") + this.colon;
    this.widget.findChild("LabelHandle").text = RSettings.translate("REntity", "Handle") + this.colon;
    this.widget.findChild("LabelProtected").text = RSettings.translate("REntity", "Protected") + this.colon;

    var selectionCombo = this.widget.findChild("Selection");
    selectionCombo["activated(int)"].connect(this, "filterChanged");
    selectionCombo.installEventFilter(new REventFilter(QEvent.Wheel.valueOf(), true));
    selectionCombo.focusPolicy = Qt.ClickFocus;

    // initialize fixed general properties at the top:
    var layerCombo = this.widget.findChild("Layer");
    layerCombo['activated(QString)'].connect(
                new PropertyWatcher(this, layerCombo, REntity.PropertyLayer),
                'propertyChanged');
    layerCombo.installEventFilter(new REventFilter(QEvent.Wheel.valueOf(), true));
    layerCombo.focusPolicy = Qt.ClickFocus;

    var colorCombo = this.widget.findChild("Color");
    colorCombo['activated(int)'].connect(
                new PropertyWatcher(this, colorCombo, REntity.PropertyColor),
                'propertyChanged');
    colorCombo.installEventFilter(new REventFilter(QEvent.Wheel.valueOf(), true));
    colorCombo.focusPolicy = Qt.ClickFocus;

    var lineweightCombo = this.widget.findChild("Lineweight");
    lineweightCombo['activated(int)'].connect(
                new PropertyWatcher(this, lineweightCombo, REntity.PropertyLineweight),
                'propertyChanged');
    lineweightCombo.installEventFilter(new REventFilter(QEvent.Wheel.valueOf(), true));
    lineweightCombo.focusPolicy = Qt.ClickFocus;

    var linetypeCombo = this.widget.findChild("Linetype");
    linetypeCombo['activated(int)'].connect(
                new PropertyWatcher(this, linetypeCombo, REntity.PropertyLinetype),
                'propertyChanged');
    linetypeCombo.installEventFilter(new REventFilter(QEvent.Wheel.valueOf(), true));
    linetypeCombo.focusPolicy = Qt.ClickFocus;


    //var itemDelegate = new QStyledItemDelegate();
    //linetypeCombo.setItemDelegate(itemDelegate);
//    linetypeCombo.styleSheet = ""
//        + "QComboBox QAbstractItemView::text "
//        + "{ "
//        + "  image-position: bottom center; "
//        + "  image: url(:/scripts/Pro/File/SvgExport/SvgExport.svg)"
//        + "}"
//        + "QComboBox QAbstractItemView::item "
//        + "{ "
//        + "  min-height: 50px; "
//        + "  image-position: bottom center; "
//        + "  image: url(:/scripts/Pro/File/SvgExport/SvgExport.svg)"
//        + "}";


    var linetypeScaleEdit = this.widget.findChild("LinetypeScale");
    linetypeScaleEdit.editingFinished.connect(
                new PropertyWatcher(this, linetypeScaleEdit, REntity.PropertyLinetypeScale),
                'propertyChanged');

    var drawOrderEdit = this.widget.findChild("DrawOrder");
    drawOrderEdit.editingFinished.connect(
                new PropertyWatcher(this, drawOrderEdit, REntity.PropertyDrawOrder),
                'propertyChanged');

    this.geometryGroup = undefined;
    this.childGroup = undefined;
    this.customGroup = undefined;
    this.onlyChangesOverride = undefined;
}

PropertyEditorImpl.prototype = new RPropertyEditor();

/**
 * Implementation from RPropertyEditor to update the property editor GUI.
 */
PropertyEditorImpl.prototype.updateGui = function(onlyChanges) {
    var row;
    
//    if (!isNull(entityTypeFilter)) {
//        this.entityTypeFilter=entityTypeFilter;
//    }

//    if (isNull(this.entityTypeFilter)) {
//        debugger;
//    }

    if (!isNull(this.onlyChangesOverride)) {
        onlyChanges = this.onlyChangesOverride;
        this.onlyChangesOverride = undefined;
    }

    this.widget.updatesEnabled = false;
    if (!onlyChanges) {
        if (!isNull(this.geometryGroup)) {
            this.geometryGroup.destroy();
            this.geometryGroup = undefined;
        }
        if (!isNull(this.childGroup)) {
            this.childGroup.destroy();
            this.childGroup = undefined;
        }
        if (!isNull(this.customGroup)) {
            this.customGroup.destroy();
            this.customGroup = undefined;
        }
    }

    var selectionCombo = this.widget.findChild("Selection");

    var generalGroup = this.widget.findChild("General");
    var layerCombo = this.widget.findChild("Layer");
    var colorCombo = this.widget.findChild("Color");
    var lineweightCombo = this.widget.findChild("Lineweight");
    var linetypeCombo = this.widget.findChild("Linetype");
    var doc = EAction.getDocument();
    linetypeCombo.init(isNull(doc) ? null : doc);

    var linetypeScaleEdit = this.widget.findChild("LinetypeScale");
    var drawOrderEdit = this.widget.findChild("DrawOrder");
    var handleEdit = this.widget.findChild("Handle");
    this.makeReadOnly(handleEdit);
    var protectedLabel = this.widget.findChild("LabelProtected");
    var protectedCombo = this.widget.findChild("Protected");
    this.makeReadOnly(protectedCombo);

    // comment out to to inspect protected property (debugging):
    protectedLabel.visible = false;
    protectedCombo.visible = false;

    var scrollArea = this.widget.findChild("ScrollArea");
    var layout = scrollArea.layout();

    //if (!onlyChanges) {
        selectionCombo.clear();
        // TODO: add 'no selection' item to choose current pen:
        //selectionCombo.addItem(qsTr("No Selection"), -2);
    //}

    var groups = this.getGroupTitles();

    // no properties to show or 'No Selection' chosen:
    if (groups.length===0 /*|| selectionCombo.currentIndex===0*/) {
        selectionCombo.clear();
        selectionCombo.insertItem(0, qsTr("No Selection"));
        layerCombo.clear();
        colorCombo.currentIndex = 0;
        lineweightCombo.currentIndex = 0;
        linetypeCombo.currentIndex = 0;
        linetypeScaleEdit.text = "";
        drawOrderEdit.text = "";
        handleEdit.text = "";
        protectedCombo.clear();
        generalGroup.enabled = false;
        this.widget.updatesEnabled = true;
        return;
    }

    var gridLayoutGeometry = undefined;
    var gridLayoutChild = undefined;
    var gridLayoutCustom = undefined;

    if (!onlyChanges) {
        // create geometry group box with grid layout:
        this.geometryGroup = new QGroupBox(qsTr("Specific Properties"), this.widget);
        layout.insertWidget(2, this.geometryGroup);

        // grid layout with three columns and N rows for N property controls:
        gridLayoutGeometry = new QGridLayout(this.geometryGroup);
        gridLayoutGeometry.setVerticalSpacing(2);
        gridLayoutGeometry.setColumnStretch(0,0);
        gridLayoutGeometry.setColumnStretch(1,1);
        gridLayoutGeometry.setColumnStretch(2,0);
        this.geometryGroup.setLayout(gridLayoutGeometry);

        // child properties
        // (block attributes shown when block reference is selected):
        // create child property group box with grid layout:
        this.childGroup = new QGroupBox(qsTr("Dependent Entities"), this.widget);
        layout.insertWidget(3, this.childGroup);

        // grid layout with four columns and N rows for N property controls:
        // (the fourth column is for the 'remove property' button)
        gridLayoutChild = new QGridLayout(this.childGroup);
        gridLayoutChild.setVerticalSpacing(2);
        gridLayoutChild.setColumnStretch(0,0);
        gridLayoutChild.setColumnStretch(1,1);
        gridLayoutChild.setColumnStretch(2,0);
        gridLayoutChild.setColumnStretch(3,0);
        this.childGroup.setLayout(gridLayoutChild);
        this.childGroup.visible = false;

        // custom properties:
        if (RSettings.isXDataEnabled()) {
            // create custom property group box with grid layout:
            this.customGroup = new QGroupBox(qsTr("Custom"), this.widget);
            layout.insertWidget(4, this.customGroup);

            // grid layout with four columns and N rows for N property controls:
            // (the fourth column is for the 'remove property' button)
            gridLayoutCustom = new QGridLayout(this.customGroup);
            gridLayoutCustom.setVerticalSpacing(2);
            gridLayoutCustom.setColumnStretch(0,0);
            gridLayoutCustom.setColumnStretch(1,1);
            gridLayoutCustom.setColumnStretch(2,0);
            gridLayoutCustom.setColumnStretch(3,0);
            this.customGroup.setLayout(gridLayoutCustom);
        }
    }
    else {
        if (!isNull(this.geometryGroup)) {
            gridLayoutGeometry = this.geometryGroup.layout();
        }
        if (!isNull(this.childGroup)) {
            gridLayoutChild = this.childGroup.layout();
        }
        if (!isNull(this.customGroup)) {
            gridLayoutCustom = this.customGroup.layout();
        }
    }

    // clear custom property group and child (block attributes) groups:
    // these are always rebuilt:
    var groupsToClear = [this.customGroup, this.childGroup];
    for (var gtci=0; gtci<groupsToClear.length; gtci++) {
        var groupToClear = groupsToClear[gtci];
        if (!isNull(groupToClear)) {
            var children = groupToClear.children();
            for (var i=0; i<children.length; i++) {
                var child = children[i];
                if (isOfType(child, QGridLayout)) {
                    // don't destroy layout:
                    continue;
                }
                children[i].destroy();
            }
        }
    }

    var firstEntry = true;
    var gotLayerProperty = false;
    var gotLinetypeScaleProperty = false;
    var gotDrawOrderProperty = false;

    // for all property groups:
    for (var gi=0; gi<groups.length; ++gi) {
        var group = groups[gi];
        //qDebug("group: ", group);

        // for all properties in that group:
        var titles = this.getPropertyTitles(group);
        for (var pi=0; pi<titles.length; ++pi) {
            var title = titles[pi];
            //qDebug("title: ", title);

            var value = this.getPropertyValue(group, title);
            //qDebug("value: ", value);

            var attributes = this.getPropertyAttributes(group, title);
            //var propertyTypeId = attributes.getPropertyTypeId();
            var propertyTypeId = RPropertyTypeId.getPropertyTypeId(group, title);

            var onlyChangesProp = onlyChanges;

            // don't use isCustom here:
            if (propertyTypeId.getId()===-1) {
                // property is custom property
                // make sure it knows it's titles, etc:
                propertyTypeId.setCustomPropertyTitle(group);
                propertyTypeId.setCustomPropertyName(title);
                onlyChangesProp = false;
            }

            //qDebug("isMixed: ", attributes.isMixed());

            if (isNull(value)) {
                // invalid value means no property found:
                continue;
            }

//            qDebug("\tproperty: ", title, ": ", value);
//            qDebug("\tproperty type id: ", propertyTypeId);

//            if (attributes.hasEnumChoices()) {
//                var ec = attributes.getEnumChoices();
//                qDebug("enumChoices: ", ec.length);
//                qDebug("enumChoices: ", ec[0]);
//                qDebug("enumChoices: ", ec[1]);
//                qDebug("enumChoices: ", ec[2]);
//                debugger;
//            }

            // ignore entity type:
            if (propertyTypeId.getId()===REntity.PropertyType.getId()) {
                // ignore
            }

            // ignore block ID:
            else if (propertyTypeId.getId()===REntity.PropertyBlock.getId()) {
                // ignore
            }

            // layer:
            else if (propertyTypeId.getId()===REntity.PropertyLayer.getId()) {
                this.initControls(propertyTypeId, true, layerCombo);
                gotLayerProperty = true;
            }

            // color:
            else if (propertyTypeId.getId()===REntity.PropertyColor.getId()) {
                this.initControls(propertyTypeId, true, colorCombo);
            }

            // lineweight:
            else if (propertyTypeId.getId()===REntity.PropertyLineweight.getId()) {
                this.initControls(propertyTypeId, true, lineweightCombo);
            }

            // linetype:
            else if (propertyTypeId.getId()===REntity.PropertyLinetype.getId()) {
                this.initControls(propertyTypeId, true, linetypeCombo);
            }

            // linetype scale:
            else if (propertyTypeId.getId()===REntity.PropertyLinetypeScale.getId()) {
                this.initControls(propertyTypeId, true, linetypeScaleEdit);
                gotLinetypeScaleProperty = true;
            }

            // draw order:
            else if (propertyTypeId.getId()===REntity.PropertyDrawOrder.getId()) {
                this.initControls(propertyTypeId, true, drawOrderEdit);
                gotDrawOrderProperty = true;
            }

            // handle:
            else if (propertyTypeId.getId()===RObject.PropertyHandle.getId()) {
                this.initControls(propertyTypeId, true, handleEdit);
            }

            // protected:
            else if (propertyTypeId.getId()===RObject.PropertyProtected.getId()) {
                this.initControls(propertyTypeId, true, protectedCombo);
            }

            // other properties:
            else {
                var gridLayout = undefined;
                var groupBox = undefined;
                if (propertyTypeId.isCustom()) {
                    // block reference attributes:
                    if (propertyTypeId.getCustomPropertyTitle()==="Attributes") {
                        gridLayout = gridLayoutChild;
                        groupBox = this.childGroup;
                        // only show group with dependent entities if needed:
                        if (!isNull(this.childGroup)) {
                            this.childGroup.visible = true;
                        }
                    }
                    // custom properties:
                    else {
                        gridLayout = gridLayoutCustom;
                        groupBox = this.customGroup;
                    }
                }
                // geometric properties:
                else {
                    gridLayout = gridLayoutGeometry;
                    groupBox = this.geometryGroup;
                }

                // for the first property of a new property group,
                // add group title and index controls if the property is a list:
                if (pi===0 && !isNull(gridLayout) && !isNull(groupBox)) {
                    // create group label:
                    if (!onlyChangesProp && group.length!==0 &&
                        // situation with two splines, one with fit points,
                        // one with control points: no group label for fit points:
                        attributes.isList()===isArray(value)) {

                        var groupLabel = new QLabel(RSettings.translate("REntity", group), groupBox);
                        groupLabel.styleSheet = "margin-bottom:0px;font-weight:bold;";
                        if (!firstEntry) {
                            groupLabel.styleSheet += "margin-top:0px;";
                            firstEntry = false;
                        }
                        gridLayout.addWidget(groupLabel, gridLayout.rowCount(),0, 1,3);
                    }

                    // if property is a list, add list index control:
                    if (!onlyChangesProp && attributes.isList()) {
                        row = gridLayout.rowCount();
                        var indexLabel = new QLabel(qsTr("Index"), groupBox);
                        indexLabel.alignment = Qt.AlignRight | Qt.AlignVCenter;
                        gridLayout.addWidget(indexLabel, row,0);
                        var indexControl = new QSpinBox(groupBox);
                        indexControl.setRange(0, value.length-1);
                        indexControl.objectName = PropertyEditorImpl.getIndexControlObjectName(group);
                        //gridLayout.addWidget(indexControl, row,1, 1,2);
                        gridLayout.addWidget(indexControl, row,1);
                        var totalLabel = new QLabel("(%1)".arg(value.length), groupBox);
                        gridLayout.addWidget(totalLabel, row,2);
                    }
                }

                var controls = undefined;
                if (!isNull(gridLayout)) {
                    // don't display any Z values or polyline elevation:
                    var hide = false;
                    if (!propertyTypeId.isCustom()) {
                        if (RSettings.getBoolValue("PropertyEditor/ShowZCoordinates", false)===false) {
                            if (title===RPolylineEntity.PropertyVertexNZ.getPropertyTitle() ||
                                title===RPolylineEntity.PropertyElevation.getPropertyTitle()) {
                                hide = true;
                            }
                        }
                    }

                    if (hide) {
                        controls = undefined;
                    }
                    else {
                        controls = this.initControls(propertyTypeId, onlyChangesProp);
                    }
                }

                // add property name and controls to layout:
                if (!onlyChangesProp) {
                    if (!isNull(controls) && !isNull(gridLayout)) {
                        row = gridLayout.rowCount();
                        var localTitle = title;
                        if (propertyTypeId.isCustom() && group!==RSettings.getAppId() &&
                            propertyTypeId.getCustomPropertyTitle()!=="Attributes") {

                            var pos = title.indexOf("_");
                            if (pos!==-1) {
                                localTitle = title.mid(pos+1);
                            }
                        }
                        else {
                            localTitle = RSettings.translate("REntity", title);
                        }

                        var l = attributes.getLabel();
                        if (l.length>0) {
                            localTitle = l;
                        }

                        var label = new QLabel(localTitle + this.colon, groupBox);
                        label.textInteractionFlags = Qt.TextSelectableByMouse;
                        label.alignment = Qt.AlignRight | Qt.AlignVCenter;

                        gridLayout.addWidget(label, row,0);
                        if (controls.length===1) {
                            gridLayout.addWidget(controls[0], row,1, 1,2);
                        }
                        else if (controls.length===2) {
                            gridLayout.addWidget(controls[0], row,1);
                            gridLayout.addWidget(controls[1], row,2);
                        }
                        else {
                            debugger;
                        }

                        // 'remove custom property' button:
                        if (propertyTypeId.isCustom() && !isNull(gridLayoutCustom) &&
                            group===RSettings.getAppId() && !attributes.isUndeletable()) {

                            var removeCustomPropertyButton = new QToolButton(this.widget);
                            removeCustomPropertyButton.icon = new QIcon(this.basePath + "/RemoveCustomProperty.svg");
                            removeCustomPropertyButton.iconSize = new QSize(12,12);
                            removeCustomPropertyButton.toolTip = qsTr("Remove this property from selected objects");
                            var name = propertyTypeId.getCustomPropertyName();
                            removeCustomPropertyButton.objectName = "DeleteCustomProperty" + name;
                            //qDebug("adding button to remove custom property named: ", name);
                            var propertyEditor = this;
                            removeCustomPropertyButton.clicked.connect(
                                        new PropertyWatcher(this, removeCustomPropertyButton, propertyTypeId),
                                        'propertyRemoved');
                            gridLayoutCustom.addWidget(removeCustomPropertyButton, row,3);
                        }

                        firstEntry = false;
                    }
                }
            }
        }
    }

    // enable / disable used / unused fixed controls
    var w;
    this.widget.findChild("LabelLayer").enabled = gotLayerProperty;
    w = this.widget.findChild("Layer");
    w.enabled = gotLayerProperty;
    if (!gotLayerProperty) {
        w.currentIndex = -1;
    }

    var gl = this.widget.findChild("General");
    if (!isNull(gl)) {
        var l = gl.layout();
        if (!isNull(l)) {
            var li = l.itemAtPosition(0, 2);
            if (!isNull(li)) {
                w = li.widget();
                if (!isNull(w)) {
                    w.enabled = gotLayerProperty;
                }
            }
        }
    }

    this.widget.findChild("LabelLinetypeScale").enabled = gotLinetypeScaleProperty;
    w = this.widget.findChild("LinetypeScale");
    w.enabled = gotLinetypeScaleProperty;
    w.setTextColor(false);
    if (!gotLinetypeScaleProperty) {
        w.text = "";
    }
    this.widget.findChild("LabelDrawOrder").enabled = gotDrawOrderProperty;
    w = this.widget.findChild("DrawOrder");
    w.enabled = gotDrawOrderProperty;
    if (!gotDrawOrderProperty) {
        w.text = "";
    }

    // update selection combo box at the top for entity filters:
    //if (!onlyChanges) {
        var types = this.getTypes();
        var totalCount = 0;
        for (var ti=0; ti<types.length; ti++) {
            var type = types[ti];
            var typeCount = this.getTypeCount(type);
            totalCount += typeCount;

            //qDebug("type: ", type, " / count: ", typeCount);
            selectionCombo.addItem(entityTypeToString(type) + " [" + typeCount + "]", type);
        }
        if (types.length!==1) {
            // TODO: add at 0 if 'no selection' item present at 0:
            selectionCombo.insertItem(0, qsTr("All") + " (" + totalCount + ")", RS.EntityAll);
        }

        var index = selectionCombo.findData(this.getEntityTypeFilter());
        if (index===-1) {
            // TODO: change to 1 if 'no selection' item present at 0:
            selectionCombo.currentIndex = 0;
        }
        else {
            selectionCombo.currentIndex = index;
        }

        generalGroup.enabled = true;
        if (!isNull(this.geometryGroup)) {
            this.geometryGroup.enabled = true;
        }
    //}

    // add custom property button:
    if (!isNull(gridLayoutCustom)) {
        if (RSettings.isXDataEnabled() && RSettings.getBoolValue("PropertyEditor/AddCustomProperties", true)!==false) {
            var addCustomPropertyButton = new QToolButton(this.widget);
            addCustomPropertyButton.icon = new QIcon(this.basePath + "/AddCustomProperty.svg");
            addCustomPropertyButton.iconSize = new QSize(12,12);
            addCustomPropertyButton.toolTip = qsTr("Add custom property to selected objects");
            addCustomPropertyButton.objectName = "AddCustomProperty";
            addCustomPropertyButton.clicked.connect(this, "addCustomProperty");
            gridLayoutCustom.addWidget(addCustomPropertyButton, gridLayoutCustom.rowCount(),3, 1,1);
        }
    }

    this.widget.updatesEnabled = true;
};

/**
 * Initializes a control for the given property.
 *
 * \param propertyTypeId The propery the returned control edits.
 * \param onlyChanges Control already exists and only need to be re-initialized.
 * \param control The control to initialize if it is already known by the caller.
 *
 * \return The control(s) as array.
 */
PropertyEditorImpl.prototype.initControls = function(propertyTypeId, onlyChanges, control) {
    var value = this.getAdjustedPropertyValue(propertyTypeId);
    var attributes = this.getPropertyAttributes(propertyTypeId);
    var controls;

    // used for custom properties only:
    // invisible flag of other properties is handled in RPropertyEditor:
    if (attributes.isInvisible()) {
        return undefined;
    }

    var objectName = PropertyEditorImpl.getControlObjectName(propertyTypeId);
    if (isNull(control) && onlyChanges) {
        // find existing control:
        control = this.widget.findChild(objectName);
        if (isNull(control)) {
            // no control available for this property (e.g. fit point of spline with control points):
            return undefined;
        }
    }

    // property available on request:
    // add button to request all properties:
    if (attributes.isOnRequest()) {
        var requestAllButton = new QToolButton(this.geometryGroup);
        requestAllButton.objectName = objectName + "_request";
        requestAllButton.text = qsTr("Show");
        requestAllButton.toolTip = qsTr("Show all properties");
        requestAllButton.clicked.connect(this, "requestAllProperties");
        requestAllButton.setSizePolicy(QSizePolicy.Ignored, QSizePolicy.Preferred);

        return new Array(requestAllButton);
    }


    // Layer:
//    if (propertyTypeId.getId()===REntity.PropertyLayer.getId()) {
//        WidgetFactory.initLayerCombo(control, EAction.getDocument());
//    }

    // Horizontal alignment: combo box:
    //else
    if (propertyTypeId.getId()===RTextEntity.PropertyHAlign.getId()) {
        controls = this.initChoiceControls(
                    objectName, propertyTypeId, onlyChanges, control, false, true);
    }

    // Vertical alignment: combo box:
    else if (propertyTypeId.getId()===RTextEntity.PropertyVAlign.getId()) {
        controls = this.initChoiceControls(
                    objectName, propertyTypeId, onlyChanges, control, false, true);
    }

    // Polyline orientation: combo box:
    else if (propertyTypeId.getId()===RPolylineEntity.PropertyOrientation.getId()) {
        controls = this.initChoiceControls(
                    objectName, propertyTypeId, onlyChanges, control, false, true);
    }

    // Arc dimension arc symbol type: combo box:
    else if (propertyTypeId.getId()===RDimArcLengthEntity.PropertyDimArcSymbolType.getId()) {
        controls = this.initChoiceControls(
                    objectName, propertyTypeId, onlyChanges, control, false, true);
    }


    // Hatch pattern: combo box with hatch names:
    else if (propertyTypeId.getId()===RHatchEntity.PropertyPatternName.getId()) {
        var patternNames = undefined;
        if (RUnit.isMetric(EAction.getDocument().getUnit())) {
            patternNames = RPatternListMetric.getNames();
        }
        else {
            patternNames = RPatternListImperial.getNames();
        }

        controls = this.initChoiceControls(
                    objectName, propertyTypeId, onlyChanges, control,
                    patternNames);
    }

    // Font: combo box with font names:
    else if (propertyTypeId.getId()===RTextEntity.PropertyFontName.getId()) {
//        var fontNames = undefined;
//        if (RUnit.isMetric(EAction.getDocument().getUnit())) {
//            patternNames = RPatternListMetric.getNames();
//        }
//        else {
//            patternNames = RPatternListImperial.getNames();
//        }

        controls = this.initChoiceControls(
                    objectName, propertyTypeId, onlyChanges, control);
    }

    // List:
    else if (getTypeOf(value)==="array") {
        var indexControlObjectName = PropertyEditorImpl.getIndexControlObjectName(propertyTypeId.getPropertyGroupTitle());
        var indexControl = this.widget.findChild(indexControlObjectName);
        if (!isNull(indexControl)) {
            var index = indexControl.value;
            controls = this.initNumberControls(objectName, propertyTypeId, onlyChanges, control, index);
            if (!onlyChanges) {
                var a;
                if (isNull(indexControl['controlNames'])) {
                    a = new Array(objectName);
                }
                else {
                    a = indexControl['controlNames'];
                    a.push(objectName);
                }
                indexControl.setProperty('controlNames', a);

                indexControl["valueChanged(int)"].connect(new IndexWatcher(this, indexControl, propertyTypeId), "indexChanged");
            }
            else {
                // make sure that the values for the current list index are updated:
                indexControl.valueChanged(index);
            }
        }
    }

    // Number: math line edit:
    else if (!isComboBox(control) && typeof(value)==="number") {
        // TODO: handle int / double differently:
        controls = this.initNumberControls(objectName, propertyTypeId, onlyChanges, control);
    }

    // Boolean: combo box with Yes, No, *VARIES*:
    else if (typeof(value)==="boolean") {
        controls = this.initBooleanControls(objectName, propertyTypeId, onlyChanges, control);
    }

    // Choices: combo box:
    else if (attributes.hasChoices() || isComboBox(control)) {
        controls = this.initChoiceControls(objectName, propertyTypeId, onlyChanges, control);
    }

    // String: line edit:
    else if (typeof(value)==="string") {
        controls = this.initStringControls(objectName, propertyTypeId, onlyChanges, control);
        if (!onlyChanges) {
            if (attributes.isDimensionLabel()) {
                WidgetFactory.initLineEdit(controls[0], true);
                controls[0].placeholderText = qsTr("Auto");
            }
            else if (attributes.isLabel()) {
                if (!attributes.isReadOnly()) {
                    WidgetFactory.initLineEdit(controls[0], false);
                }
            }
        }
    }

    if (isNull(controls) || controls.length===0) {
        return undefined;
    }

    control = controls[0];

    if (attributes.isReadOnly()) {
        this.makeReadOnly(control);
    }
    else {
        this.makeReadWrite(control);
    }

    return controls;
};

/**
 * Initializes a number control (RMathLineEdit) for the given property.
 * \internal
 */
PropertyEditorImpl.prototype.initNumberControls = function(objectName, propertyTypeId, onlyChanges, control, index) {
    var value = this.getAdjustedPropertyValue(propertyTypeId);
    if (isNumber(index)) {
        value = value[index];
    }
    var attributes = this.getPropertyAttributes(propertyTypeId);

    if (isNull(control)) {
        control = new RMathLineEdit(this.geometryGroup);
        if (attributes.isAngleType()) {
            control.setAngle(true);
        }
        // TODO: support scale in RMathLineEdit:
//        if (attributes.isScaleType()) {
//            control.setScale(true);
//        }
        control.objectName = objectName;
    }

    var newText;
    if (attributes.isMixed()) {
        newText = PropertyEditor.varies;
    }
    else {
        if (!isNull(value)) {
            if (attributes.isAngleType()) {
                value = RMath.rad2deg(value);
            }
            var document = EAction.getDocument();
            if (RSettings.getBoolValue("PropertyEditor/FormatAsDecimal", false)!==true &&
                !attributes.isAngleType() &&
                !attributes.isAreaType() &&
                !attributes.isUnitLess() /*&&
                (document.getLinearFormat()===RS.Fractional ||
                 document.getLinearFormat()===RS.FractionalStacked)*/) {

                newText = RUnit.getLabel(value, document, 8);

                if (document.getLinearFormat()===RS.Architectural ||
                    document.getLinearFormat()===RS.ArchitecturalStacked ||
                    document.getLinearFormat()===RS.Engineering) {

                    // show 3'-4" as 3' 4" to avoid ambiguous expressions:
                    newText = newText.replace("'-", "' ");
                }

            }
            else {
                newText = sprintf("%.6f", value);
            }
        }
    }

    if (control.text !== newText) {
        control.text = newText;
        control.setProperty("originalText", newText);
        if (isFunction(control.clearError)) {
            control.clearError();
        }
    }

    if (attributes.isInteger()) {
        if (isOfType(control, RMathLineEdit)) {
            control.setInteger(true);
        }
    }

    if (!onlyChanges) {
        control.editingFinished.connect(
                    new PropertyWatcher(this, control, propertyTypeId),
                    'propertyChanged');
    }

    return new Array(control);
};

/**
 * Initializes a string control (QLineEdit) for the given property.
 * \internal
 */
PropertyEditorImpl.prototype.initStringControls = function(objectName, propertyTypeId, onlyChanges, control) {
    var value = this.getAdjustedPropertyValue(propertyTypeId);
    var attributes = this.getPropertyAttributes(propertyTypeId);
    //var editAsRichTextButton;
    var clearButton = undefined;

    if (isNull(control)) {
        control = new QLineEdit(value, this.geometryGroup);
        control.objectName = objectName;
        /*if (attributes.isRichText()) {
            editAsRichTextButton = new QToolButton(this.geometryGroup);
            editAsRichTextButton.iconSize = new QSize(12,12);
            var action = RGuiAction.getByScriptFile("scripts/Modify/EditText/EditText.js");
            action.setProperty("");
            editAsRichTextButton.setDefaultAction(action);
        }*/
    }

    if (attributes.isMixed()) {
        control.text = PropertyEditor.varies;
        // TODO: make sure that the start of the text is shown:
        //control.home(false);
    }
    else {
        if (control.text!=value) {
            control.text = value;
        }
    }

    if (!onlyChanges && attributes.isDimensionLabel()) {
        clearButton = new QToolButton(this.geometryGroup);
        clearButton.objectName = objectName + "_clear";
        clearButton.iconSize = new QSize(12,12);
        clearButton.icon = new QIcon(this.basePath + "/Clear.svg");
        clearButton.toolTip = qsTr("Use auto measurement");
        clearButton.clicked.connect(function() {
            control.text = "";
            control.editingFinished();
        });
    }

    if (!onlyChanges) {
        control.editingFinished.connect(
                    new PropertyWatcher(this, control, propertyTypeId),
                    'propertyChanged');
    }

    if (isNull(clearButton)) {
        return new Array(control);
    }
    else {
        return new Array(control, clearButton);
    }
};

/**
 * Initializes a boolean control (combo box with yes / no) for the given property.
 * \internal
 */
PropertyEditorImpl.prototype.initBooleanControls = function(objectName, propertyTypeId, onlyChanges, control) {
    var value = this.getAdjustedPropertyValue(propertyTypeId);
    var attributes = this.getPropertyAttributes(propertyTypeId);

    if (isNull(control)) {
        control = new QComboBox(this.geometryGroup);
        control.objectName = objectName;
        control.installEventFilter(new REventFilter(QEvent.Wheel.valueOf(), true));
        control.focusPolicy = Qt.ClickFocus;
        control.minimumWidth = 50;
        control.setSizePolicy(QSizePolicy.Ignored, QSizePolicy.Preferred);
    }

    if (control.count<2) {
        control.addItem(qsTr("Yes"), true);
        control.addItem(qsTr("No"), false);
    }

    if (attributes.isMixed()) {
        if (!onlyChanges) {
            control.insertItem(0, PropertyEditor.varies, PropertyEditor.varies);
        }
        control.currentIndex = 0;
    }
    else {
        // not varies anymore:
        var variesIndex = control.findText(PropertyEditor.varies);
        if (variesIndex!==-1) {
            control.removeItem(variesIndex);
        }
        control.currentIndex = control.findData(value);
    }

    // read only:
    if (attributes.isReadOnly()) {
        control.enabled = false;
    }

    if (!onlyChanges) {
        control['activated(int)'].connect(
                    new PropertyWatcher(this, control, propertyTypeId),
                    'propertyChanged');
    }

    return new Array(control);
};

/**
 * Initializes a choice control (combo box) for the given property.
 * \internal
 */
PropertyEditorImpl.prototype.initChoiceControls = function(
    objectName, propertyTypeId, onlyChanges, control, choices, choicesData) {
    
    var i;

    var value = this.getAdjustedPropertyValue(propertyTypeId);
    var attributes = this.getPropertyAttributes(propertyTypeId);

    if (isNull(control)) {
        //if (propertyTypeId.getId()===RTextEntity.PropertyFontName.getId()) {
        if (attributes.isStyle()) {
//            control = new QComboBox(this.geometryGroup);
            control = new QFontComboBox(this.geometryGroup);
            //control.sizeAdjustPolicy = QComboBox.AdjustToContentsOnFirstShow;
            control.setSizePolicy(QSizePolicy.Ignored, QSizePolicy.Preferred);
            //control.maxWidth = 100;
            control.editable = false;
            control.installEventFilter(new REventFilter(QEvent.Wheel.valueOf(), true));
            control.focusPolicy = Qt.ClickFocus;
            initFontComboBox(control);
        }
        else {
            control = new QComboBox(this.geometryGroup);
            control.installEventFilter(new REventFilter(QEvent.Wheel.valueOf(), true));
            control.focusPolicy = Qt.ClickFocus;
            control.minimumWidth = 50;
            control.setSizePolicy(QSizePolicy.Ignored, QSizePolicy.Preferred);
        }

        control.objectName = objectName;

        if (isNull(choicesData)/* && propertyTypeId.getId()!==REntity.PropertyLayer.getId()*/) {
            control['activated(QString)'].connect(
                        new PropertyWatcher(this, control, propertyTypeId),
                        'propertyChanged');
        }
        else {
            control['activated(int)'].connect(
                        new PropertyWatcher(this, control, propertyTypeId),
                        'propertyChanged');
        }
    }

    if (propertyTypeId.getId()===REntity.PropertyLayer.getId()) {
        WidgetFactory.initLayerCombo(control, EAction.getDocument());
    }
    else if (propertyTypeId.getId()===RTextEntity.PropertyHAlign.getId()) {
        WidgetFactory.initHAlignCombo(control);
    }
    else if (propertyTypeId.getId()===RTextEntity.PropertyVAlign.getId()) {
        WidgetFactory.initVAlignCombo(control);
    }
    else if (propertyTypeId.getId()===RPolylineEntity.PropertyOrientation.getId()) {
        WidgetFactory.initOrientationCombo(control);
    }
    else if (propertyTypeId.getId()===RDimArcLengthEntity.PropertyDimArcSymbolType.getId()) {
        WidgetFactory.initArcSymbolTypeCombo(control);
    }
    else if (isOfType(control, QComboBox) /*&& propertyTypeId.getId()!==REntity.PropertyLayer.getId()*/) {
        control.clear();
        if (isNull(choices)) {
            if (attributes.isNumericallySorted()) {
                var cs = attributes.getChoices();
                cs.sort(function(a,b) { return parseInt(a) - parseInt(b) });
                control.addItems(cs);
            }
            else {
                control.addItems(attributes.getChoices());
                control.model().sort(0);
            }
        }
        else {
            if (isNull(choicesData)) {
                control.addItems(choices);
            }
            else {
                for (i=0; i<choices.length && i<choicesData.length; ++i) {
                    control.addItem(choices[i], choicesData[i]);
                }
            }
        }
    }

    // mixed:
    var variesIndex = control.findText(PropertyEditor.varies);
    if (attributes.isMixed()) {
        if (variesIndex!==-1) {
            control.currentIndex = variesIndex;
        }
        else {
            control.insertItem(0, PropertyEditor.varies, PropertyEditor.varies);
            control.currentIndex = 0;
        }
        return new Array(control);
    }

    // not mixed anymore, remove mixed option:
    if (variesIndex!==-1) {
        control.removeItem(variesIndex);
    }

    var index = -1;
    if (typeof(value)==="string") {
        index = control.findText(value);
        if (index===-1) {
            control.addItem(value);
            index = control.findText(value);
        }
    }
    else {
        for (i=0; i<control.count; ++i) {
            var data = control.itemData(i);
            var match = false;

            // for some types (e.g. RColor, RLinetype), we have to use equals here:
            if (!isNull(data) && isFunction(data.equals)) {
                if (data.equals(value)) {
                    match = true;
                }
            }
            else {
                if (data===value) {
                    match = true;
                }
            }

            if (match) {
                index = i;
                break;
            }
        }
    }

    if (index===-1) {
        // handle custom color:
        if (isOfType(control, RColorCombo)) {
            control.setColor(value);
        }
        else if (isOfType(control, QFontComboBox)) {
            activateFont(control, value);
        }
        else if (isOfType(control, RLineweightCombo)) {
            // custom lineweight: default to ByLayer:
            control.currentIndex = 0;
        }
        else if (isOfType(control, RLinetypeCombo)) {
            // custom linetype: default to ByLayer:
            control.currentIndex = 0;
        }
        else {
            // custom something, cannot handle this:
            debugger;
        }
    }
    else {
        control.currentIndex = index;
    }

    return [ control ];
};

PropertyEditorImpl.getControlObjectName = function(propertyTypeId) {
    if (propertyTypeId.isCustom()) {
        return "Control" + propertyTypeId.getCustomPropertyName();
    }
    else {
        return "Control" + propertyTypeId.getId();
    }
};

PropertyEditorImpl.getIndexControlObjectName = function(group) {
    return "IndexControl" + group.replace(" ", "_");
};

/**
 * Called when user changes entity filter at the top of the property editor.
 */
PropertyEditorImpl.prototype.filterChanged = function() {
    var doc = EAction.getDocument();
    if (isNull(doc)) {
        return;
    }

    var selectionCombo = this.widget.findChild("Selection");
    var entityTypeFilter = selectionCombo.itemData(selectionCombo.currentIndex);
    if (isNull(entityTypeFilter)) {
        entityTypeFilter = RS.EntityAll;
    }

    this.updateFromDocument(doc, false, entityTypeFilter, true);
};

/**
 * Called when the user requests all properties to be shown.
 */
PropertyEditorImpl.prototype.requestAllProperties = function() {
    var doc = EAction.getDocument();
    if (isNull(doc)) {
        return;
    }

    var selectionCombo = this.widget.findChild("Selection");
    var entityTypeFilter = selectionCombo.itemData(selectionCombo.currentIndex);
    if (isNull(entityTypeFilter)) {
        entityTypeFilter = RS.EntityAll;
    }

    this.updateFromDocument(doc, false, entityTypeFilter, true, true);
};

PropertyEditorImpl.prototype.getAdjustedPropertyValue = function(propertyTypeId) {
    // show handle as hex reprensentation (string):
    if (propertyTypeId.getId()===RObject.PropertyHandle.getId()) {
        var value = this.getPropertyValue(propertyTypeId);
        if (value===RObject.INVALID_HANDLE) {
            return "-";
        }
        return sprintf("0x%x", value);
    }

    return this.getPropertyValue(propertyTypeId);
};

/**
 * Make given control read-only and more visibly so.
 */
PropertyEditorImpl.prototype.makeReadOnly = function(control) {
    if (isNull(control)) {
        return;
    }

    var p = control.palette;
    if (isNull(control.oriPalette)) {
        control.setProperty("oriPalette", control.palette);
    }

    p.setColor(QPalette.Active, QPalette.Text, control.oriPalette.color(QPalette.Disabled, QPalette.WindowText));
    p.setColor(QPalette.Inactive, QPalette.Text, control.oriPalette.color(QPalette.Disabled, QPalette.WindowText));

//    if (RSettings.hasDarkGuiBackground()) {
//        p.setColor(QPalette.Base, new QColor("#0a0a0a"));
//    }
//    else {
//        p.setColor(QPalette.Base, new QColor("#eeeeee"));
//    }
    control.palette = p;

    control.readOnly = true;
    // leave enabled to allow copy / page (20140411):
    //control.enabled = false;
};

/**
 * Make given control read-write again.
 */
PropertyEditorImpl.prototype.makeReadWrite = function(control) {
    if (isNull(control)) {
        return;
    }

    var p = control.palette;
    if (isNull(control.oriPalette)) {
        control.setProperty("oriPalette", control.palette);
    }

    p.setColor(QPalette.Active, QPalette.Text, control.oriPalette.color(QPalette.Active, QPalette.WindowText));
    p.setColor(QPalette.Inactive, QPalette.Text, control.oriPalette.color(QPalette.Inactive, QPalette.WindowText));
//    //if (RSettings.hasDarkGuiBackground()) {
//        p.setColor(QPalette.Base, control.oriBase);
////    }
////    else {
////        p.setColor(QPalette.Base, new QColor("#ffffff"));
////    }
    control.palette = p;

    control.readOnly = false;
    control.enabled = true;
};

PropertyEditorImpl.prototype.addCustomProperty = function() {
    var dialog = WidgetFactory.createDialog(this.basePath, "AddCustomPropertyDialog.ui");

    var buttonBox = dialog.findChild("ButtonBox");
    buttonBox.button(QDialogButtonBox.Ok).enabled = false;

    var nameEdit = dialog.findChild("Name");
    var rx = new RegExp("[^<>\\\\\":;\?\*|,=`]{1,255}");
    var validator = new QRegExpValidator(rx, nameEdit);
    nameEdit.setValidator(validator);
    nameEdit.textChanged.connect(
        function(text) {
            buttonBox.button(QDialogButtonBox.Ok).enabled = !text.isEmpty();
        }
    );

    var valueEdit = dialog.findChild("Value");

    if (!dialog.exec()) {
        dialog.destroy();
        EAction.activateMainWindow();
        return;
    }

    var name = nameEdit.text;
    var value = valueEdit.text;

    // trigger change property operation for custom property:
    this.propertyChanged(new RPropertyTypeId(RSettings.getAppId(), name), value, this.getEntityTypeFilter());
    this.onlyChangesOverride = false;

    dialog.destroy();
    EAction.activateMainWindow();
};



function PropertyEditor(guiAction) {
    EAction.call(this, guiAction);
}

PropertyEditor.prototype = new EAction();

PropertyEditor.varies = qsTr("*VARIES*");

PropertyEditor.getPreferencesCategory = function() {
    return [ qsTr("Widgets"), qsTr("Property Editor") ];
};

PropertyEditor.applyPreferences = function(doc, mdiChild) {
    var appWin = RMainWindowQt.getMainWindow();
    appWin.notifyPropertyListeners(EAction.getDocument());
};

/**
 * Shows / hides the property editor.
 */
PropertyEditor.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("PropertyEditorDock");
    if (!QCoreApplication.arguments().contains("-no-show")) {
        dock.visible = !dock.visible;
        if (dock.visible) dock.raise();
    }
    var linetypeCombo = dock.findChild("Linetype");
    linetypeCombo.init(EAction.getDocument());

    appWin.notifyPropertyListeners(EAction.getDocument());
};

PropertyEditor.prototype.finishEvent = function() {
    EAction.prototype.finishEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("PropertyEditorDock");
    this.getGuiAction().setChecked(dock.visible);
};

/**
 * Static function to get current entity filter (useful when triggering actions which change properties).
 */
PropertyEditor.getEntityTypeFilter = function() {
    var appWin = EAction.getMainWindow();
    var widget = appWin.findChild("PropertyEditor");
    var selectionCombo = widget.findChild("Selection");
    return selectionCombo.itemData(selectionCombo.currentIndex);
};

/**
 * Static function to get current layer displayed in the property editor.
 */
PropertyEditor.getCurrentLayerName = function() {
    var appWin = EAction.getMainWindow();
    var widget = appWin.findChild("PropertyEditor");
    var layerCombo = widget.findChild("Layer");
    return layerCombo.itemText(layerCombo.currentIndex);
};

PropertyEditor.init = function(basePath) {
    var appWin = EAction.getMainWindow();

    var action = new RGuiAction(qsTr("Property Editor"), appWin);
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/PropertyEditor.js");
    action.setIcon(basePath + "/PropertyEditor.svg");
    action.setDefaultShortcut(new QKeySequence("g,p"));
    action.setDefaultCommands(["gp"]);
    action.setGroupSortOrder(3700);
    action.setSortOrder(100);
    action.setWidgetNames(["ViewMenu", "WidgetsToolBar", "ViewToolsPanel", "WidgetsMatrixPanel"]);

    var pe = new PropertyEditorImpl(basePath);
    var dock = new RDockWidget(qsTr("Property Editor"), appWin);
    dock.objectName = "PropertyEditorDock";
    dock.setWidget(pe.widget);
    appWin.addPropertyListener(pe);
    appWin.addLayerListener(pe.getRLayerListener());
    appWin.addDockWidget(Qt.RightDockWidgetArea, dock);
    PropertyEditor.instance = pe;

    dock.shown.connect(function() { action.setChecked(true); });
    dock.hidden.connect(function() { action.setChecked(false); });
};
