/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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

include("../../WidgetFactory.js");
include("../../Layer/AddLayer/AddLayer.js");

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
        this.propertyEditor.listPropertyChanged(this.propertyType, index, value,
                                                this.propertyEditor.entityTypeFilter);
        return;
    }

    // value comes from a combo box:
    else if (isComboBox(this.sender)) {

        // value is index of combo box:
        if (isNumber(value)) {
            if (this.sender.itemData(value)===this.propertyEditor.varies) {
                return;
            }
            this.propertyEditor.propertyChanged(this.propertyType,
                                                this.sender.itemData(value),
                                                this.propertyEditor.entityTypeFilter);
            return;
        }

        if (value===this.propertyEditor.varies) {
            return;
        }
    }

    // value is string from a line edit (e.g. text contents):
    else if (this.sender.toString()==="QLineEdit") {
        value = this.sender.text;
        if (value===this.propertyEditor.varies) {
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

    this.propertyEditor.propertyChanged(this.propertyType, value, this.propertyEditor.entityTypeFilter, typeHint);
};

/**
 * Called when a custom property has been deleted by the user. Triggers
 * a transaction to delete the propery from all selected entities
 * that match the current entity type filter.
 */
PropertyWatcher.prototype.propertyRemoved = function() {
    this.propertyEditor.propertyChanged(this.propertyType, null, this.propertyEditor.entityTypeFilter);
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

    this.entityTypeFilter = RS.EntityAll;
    this.varies = qsTr("*VARIES*");
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

    var addLayerButton = this.widget.findChild("MoveToNewLayer");
    var propertyEditor = this;
    addLayerButton.clicked.connect(function() {
        var di = EAction.getDocumentInterface();
        if (isNull(di)) {
            return;
        }
        var action = RGuiAction.getByScriptFile("scripts/Layer/AddLayer/AddLayer.js");
        if (isNull(action)) {
            return;
        }
        action.trigger();
        var doc = di.getDocument();
        var layer = doc.queryCurrentLayer();
        //var action = new AddLayer();
        //di.setCurrentAction(action);
        //var layer = action.getAddedLayer();
        if (!isNull(layer)) {
            var pw = new PropertyWatcher(propertyEditor, layerCombo, REntity.PropertyLayer);
            pw.propertyChanged(layer.getName());
        }
    });

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
PropertyEditorImpl.prototype.updateGui = function(onlyChanges, entityTypeFilter) {
    var row;
    
    if (!isNull(entityTypeFilter)) {
        this.entityTypeFilter=entityTypeFilter;
    }

    if (isNull(this.entityTypeFilter)) {
        debugger;
    }

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

    if (!onlyChanges) {
        selectionCombo.clear();
    }

    var groups = this.getGroupTitles();

    // no properties to show:
    if (groups.length===0) {
        layerCombo.clear();
        selectionCombo.insertItem(0, qsTr("No Selection"));
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
        this.geometryGroup = new QGroupBox(qsTr("Geometry"), this.widget);
        layout.insertWidget(2, this.geometryGroup);

        // grid layout with three columns and N rows for N property controls:
        gridLayoutGeometry = new QGridLayout(this.geometryGroup);
        gridLayoutGeometry.setVerticalSpacing(4);
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
        gridLayoutChild.setVerticalSpacing(4);
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
            gridLayoutCustom.setVerticalSpacing(4);
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

    var firstEntry = true;

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
            var propertyTypeId = attributes.getPropertyTypeId();

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
                this.initControls(propertyTypeId, onlyChanges, layerCombo);
            }

            // color:
            else if (propertyTypeId.getId()===REntity.PropertyColor.getId()) {
                this.initControls(propertyTypeId, onlyChanges, colorCombo);
            }

            // lineweight:
            else if (propertyTypeId.getId()===REntity.PropertyLineweight.getId()) {
                this.initControls(propertyTypeId, onlyChanges, lineweightCombo);
            }

            // linetype:
            else if (propertyTypeId.getId()===REntity.PropertyLinetype.getId()) {
                this.initControls(propertyTypeId, onlyChanges, linetypeCombo);
            }

            // linetype scale:
            else if (propertyTypeId.getId()===REntity.PropertyLinetypeScale.getId()) {
                this.initControls(propertyTypeId, onlyChanges, linetypeScaleEdit);
            }

            // draw order:
            else if (propertyTypeId.getId()===REntity.PropertyDrawOrder.getId()) {
                this.initControls(propertyTypeId, onlyChanges, drawOrderEdit);
            }

            // handle:
            else if (propertyTypeId.getId()===RObject.PropertyHandle.getId()) {
                this.initControls(propertyTypeId, onlyChanges, handleEdit);
            }

            // protected:
            else if (propertyTypeId.getId()===RObject.PropertyProtected.getId()) {
                this.initControls(propertyTypeId, onlyChanges, protectedCombo);
            }

            // other properties:
            else {
                var gridLayout;
                var groupBox = undefined;
                if (propertyTypeId.isCustom()) {
                    // block reference attributes:
                    if (propertyTypeId.getCustomPropertyTitle()==="Attributes") {
                        gridLayout = gridLayoutChild;
                        groupBox = this.childGroup;
                        // only show group with dependent entities if needed:
                        this.childGroup.visible = true;
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
                    if (!onlyChanges && group.length!==0 &&
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
                    if (!onlyChanges && attributes.isList()) {
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
                    // don't display any Z values:
                    if (RSettings.getBoolValue("PropertyEditor/ShowZCoordinates", false)===false && title==="Z" && !propertyTypeId.isCustom()) {
                        controls = undefined;
                    }
                    else {
                        controls = this.initControls(propertyTypeId, onlyChanges);
                    }
                }

                // add property name and controls to layout:
                if (!onlyChanges) {
                    if (!isNull(controls) && !isNull(gridLayout)) {
                        row = gridLayout.rowCount();
                        var localTitle = title;
                        if (propertyTypeId.isCustom() && group!==RSettings.getAppId()) {
                            var pos = title.indexOf("_");
                            if (pos!==-1) {
                                localTitle = title.mid(pos+1);
                            }
                        }
                        else {
                            localTitle = RSettings.translate("REntity", title);
                        }

                        var label = new QLabel(localTitle + this.colon, groupBox);
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
                        if (propertyTypeId.isCustom() && !isNull(gridLayoutCustom) && group===RSettings.getAppId()) {
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

    // update selection combo box at the top for entity filters:
    if (!onlyChanges) {
        var types = this.getTypes();
        var totalCount = 0;
        for (var ti=0; ti<types.length; ti++) {
            var type = types[ti];
            var typeCount = this.getTypeCount(type);
            totalCount += typeCount;

            //qDebug("type: ", type, " / count: ", typeCount);
            selectionCombo.addItem(entityTypeToString(type) + " (" + typeCount + ")", type);
        }
        if (types.length!==1) {
            selectionCombo.insertItem(0, qsTr("All") + " (" + totalCount + ")", RS.EntityAllManual);
        }

        var index = selectionCombo.findData(this.entityTypeFilter);
        if (index===-1) {
            selectionCombo.currentIndex = 0;
        }
        else {
            selectionCombo.currentIndex = index;
        }

        generalGroup.enabled = true;
        this.geometryGroup.enabled = true;
    }

    // add custom property button:
    if (!onlyChanges) {
        if (RSettings.isXDataEnabled()) {
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

    var objectName = PropertyEditorImpl.getControlObjectName(propertyTypeId);
    if (isNull(control) && onlyChanges) {
        // find existing control:
        control = this.widget.findChild(objectName);
        if (isNull(control)) {
            // no control available for this property (e.g. fit point of spline with control points):
            return undefined;
        }
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
//                    [ qsTr("Left"), qsTr("Center"), qsTr("Right"),
//                      qsTr("Aligned"), qsTr("Middle"), qsTr("Fit")],
//                    [ RS.HAlignLeft, RS.HAlignCenter, RS.HAlignRight,
//                      RS.HAlignAlign, RS.HAlignMid, RS.HAlignFit]);
    }

    // Vertical alignment: combo box:
    else if (propertyTypeId.getId()===RTextEntity.PropertyVAlign.getId()) {
        controls = this.initChoiceControls(
                    objectName, propertyTypeId, onlyChanges, control, false, true);
//                    [qsTr("Top"), qsTr("Middle"), qsTr("Base"), qsTr("Bottom")],
//                    [RS.VAlignTop, RS.VAlignMiddle, RS.VAlignBase, RS.VAlignBottom]);
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
        control.objectName = objectName;
    }

    var newText;
    if (attributes.isMixed()) {
        newText = this.varies;
    }
    else {
        if (attributes.isAngleType()) {
            value = RMath.rad2deg(value);
        }
        var document = EAction.getDocument();
        if (!attributes.isAngleType() && (document.getLinearFormat()===RS.Fractional || document.getLinearFormat()===RS.FractionalStacked)) {
            newText = RUnit.getLabel(value, document, true);
        }
        else {
            newText = sprintf("%.6f", value);
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
        control.setInteger(true);
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
        control.text = this.varies;
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
            control.insertItem(0, this.varies, this.varies);
        }
        control.currentIndex = 0;
    }
    else {
        // not varies anymore:
        var variesIndex = control.findText(this.varies);
        if (variesIndex!==-1) {
            control.removeItem(variesIndex);
        }
        control.currentIndex = control.findData(value);
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
    var variesIndex = control.findText(this.varies);
    if (attributes.isMixed()) {
        if (variesIndex!==-1) {
            control.currentIndex = variesIndex;
        }
        else {
            control.insertItem(0, this.varies, this.varies);
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
    this.entityTypeFilter = selectionCombo.itemData(selectionCombo.currentIndex);

    if (!isNumber(this.entityTypeFilter)) {
        this.updateFromDocument(doc, false, RS.EntityAll, true);
    }
    else {
        this.updateFromDocument(doc, false, this.entityTypeFilter, true);
    }
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
    p.setColor(QPalette.Base, new QColor("#eeeeee"));
    control.palette = p;
    control.readOnly = true;
    // leave enebaled to allow copy / page (20140411):
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
    p.setColor(QPalette.Base, new QColor("#ffffff"));
    control.palette = p;
    control.readOnly = false;
    control.enabled = true;
};

PropertyEditorImpl.prototype.addCustomProperty = function() {
    var dialog = WidgetFactory.createDialog(this.basePath, "AddCustomPropertyDialog.ui");

    var buttonBox = dialog.findChild("ButtonBox");
    buttonBox.button(QDialogButtonBox.Ok).enabled = false;

    var nameEdit = dialog.findChild("Name");
    var rx = new RegExp("[^<>/\\\\\":;\?\*|,=`]{1,255}");
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
        return;
    }

    var name = nameEdit.text;
    var value = valueEdit.text;

    // trigger change property operation for custom property:
    this.propertyChanged(new RPropertyTypeId(RSettings.getAppId(), name), value, this.entityTypeFilter);
    this.onlyChangesOverride = false;

    dialog.destroy();
};



function PropertyEditor(guiAction) {
    Widgets.call(this, guiAction);
}

PropertyEditor.prototype = new Widgets();

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
    Widgets.prototype.beginEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("PropertyEditorDock");
    if (!QCoreApplication.arguments().contains("-no-show")) {
        dock.visible = !dock.visible;
    }
    var linetypeCombo = dock.findChild("Linetype");
    linetypeCombo.init(EAction.getDocument());

};

PropertyEditor.prototype.finishEvent = function() {
    Widgets.prototype.finishEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    var dock = appWin.findChild("PropertyEditorDock");
    this.getGuiAction().setChecked(dock.visible);
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
    action.setWidgetNames(["ViewMenu", "WidgetsToolBar", "ViewToolsPanel"]);

    var pe = new PropertyEditorImpl(basePath);
    var dock = new RDockWidget(qsTr("Property Editor"), appWin);
    dock.objectName = "PropertyEditorDock";
    dock.setWidget(pe.widget);
    appWin.addPropertyListener(pe);
    appWin.addDockWidget(Qt.RightDockWidgetArea, dock);
    PropertyEditor.instance = pe;

    dock.shown.connect(function() { action.setChecked(true); });
    dock.hidden.connect(function() { action.setChecked(false); });
};
