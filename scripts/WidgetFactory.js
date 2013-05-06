/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

include("library.js");
include("map.js");

function WidgetFactory() {
}

/**
 * Creates a dialog with the given \c parent, based on the UI file 
 * named \c uiFile in \c basePath. The dialog has a header area in
 * which a title and (error-)messages can be display through the 
 * functions \c setTitle(title) and \c setText(text, error).
 */
WidgetFactory.createHeaderDialog = function(basePath, uiFile, parent) {
    var dlg = WidgetFactory.createDialog("scripts/Widgets", "Dialog.ui", parent);
    var header = dlg.findChild("header");
    dlg.textFormat = header.text;
    dlg.setTitle = function(title) {
        var header = dlg.findChild("header");
        header.text = dlg.textFormat.arg(title).arg(dlg.text);
        dlg.title = title;
    };
    dlg.setText = function(text, error) {
        if (isNull(error)) {
            error = false;
        }
        var header = dlg.findChild("header");
        var t = text;
        if (error) {
            t = "<font color='red'>%1</font>".arg(text);
        }
        header.text = dlg.textFormat.arg(dlg.title).arg(t);
        dlg.text = text;
    };
    var inner = WidgetFactory.createWidget(basePath, uiFile, dlg);
    var w = dlg.findChild("inner");
    var sizePolicy = w.sizePolicy;
    var layout = dlg.findChild("layout");
    var i = layout.indexOf(w);
    layout.removeWidget(w);
    layout.insertWidget(i, inner);
    inner.sizePolicy = sizePolicy;
    return dlg;
};

/**
 * Creates a widget with the given \c parent, based on the UI file 
 * named \c uiFile in \c basePath.
 */
WidgetFactory.createWidget = function(basePath, uiFile, parent) {
    if (isNull(parent)) {
        parent = RMainWindowQt.getMainWindow();
    }

    var fileInfo = new QFileInfo(uiFile);
    if (!fileInfo.exists() && !fileInfo.isAbsolute()) {
        uiFile = basePath + "/" + uiFile;
    }

    fileInfo = new QFileInfo(uiFile);
    if (!fileInfo.exists()) {
        qWarning("WidgetFactory: File %1 does not exist".arg(uiFile));
        return undefined;
    }

    var buf = RFileCache.getBuffer(uiFile);

    if (isNull(buf)) {
        return undefined;
    }

    //buf.open(new QIODevice.OpenMode(QIODevice.ReadOnly));

    var loader = new QUiLoader();
    loader.setWorkingDirectory(fileInfo.dir());

    var formWidget = loader.load(buf, parent);
    buf.close();
    loader.destroy();
    return formWidget;
};

/**
 * Creates a dialog from the given UI file.
 * Overrides exec for testing dashboard mode.
 */
WidgetFactory.createDialog = function(basePath, uiFile, parent) {
    var dialog = WidgetFactory.createWidget(basePath, uiFile, parent);

    // a global function might be defined to do additional
    // initilization for all dialogs (e.g. for testing purposes):
    if (typeof(initDialog)!=="undefined") {
        initDialog(dialog);
    }

    return dialog;
};

/**
 * \return Settings key for the given group / object. Usually that is
 * [group, object name]. An array with two items is returned for group / name.
 */
WidgetFactory.getKey = function(group, obj) {
    if (isDeleted(obj)) {
        return ["", ""];
    }

    var g = group;
    if (typeof(obj["SettingsGroup"])!="undefined") {
        g = obj["SettingsGroup"];
    }
    var key = [g, obj.objectName];

    // correct key:
    if (obj.toString() === "QRadioButton" || obj.toString() === "QToolButton") {
        // correct to button group name:
        if (isFunction(obj.group) && obj.group()) {
            key = [g, obj.group().objectName];
        }
        else {
            var parent = obj.parent();
            // correct to group box (parent) name:
            if (parent && parent.toString()=="QGroupBox") {
                key = [g, parent.objectName];
            }
        }
    }

    return key;
};

WidgetFactory.getKeyString = function(group, obj) {
    var keyTuple = WidgetFactory.getKey(group, obj);
    if (keyTuple[0].length===0) {
        return keyTuple[1];
    }
    else {
        return keyTuple[0] + "/" + keyTuple[1];
    }
};

/**
 * Saves the current state of the given \c widget and all its child widgets.
 *
 * \param group Used internally for recursive calls.
 * \param document RDocument object to store settings or \c undefined to store
 *          settings in RSettings (user scope, config file).
 * \param map Array to use to store settings in. Used by the testing dashboard
 *          recorder only.
 */
WidgetFactory.saveState = function(widget, group, document, map) {
    if (!widget) {
        return;
    }

    if (typeof(WidgetFactory.requiresRestart) === "undefined") {
        WidgetFactory.requiresRestart = false;
    }
    group = (isNull(group) ? widget.objectName : group);

    var value;
    var data;
    var children = widget.children();
    for (var i = 0; i < children.length; ++i) {
        var c = children[i];

        if (!c || isDeleted(c) || c.toString()==="QVariantAnimation" ||
                c.toString()==="QWidgetAction" || c.objectName==="" ||
                c.objectName==="Icon" || c.objectName==="qt_toolbar_ext_button") {
            continue;
        }

        // ignore Qt internal widgets:
        if (typeof(c.objectName)!="undefined" &&
            c.objectName=="qt_toolbar_ext_button") {
            continue;
        }

        // ignore widgets that have been saved elsewhere (e.g. plugins might
        // save widgets contents by themselves in savePreferences):
        if (typeof(c["Saved"]) != "undefined" && c["Saved"]===true) {
            continue;
        }

        // skip children from other groups in this widget (for options toolbar):
        if (typeof(c["SettingsGroup"]) != "undefined" && c["SettingsGroup"] != group) {
            if (isNull(map)) {
                continue;
            }
        }

        var key = WidgetFactory.getKeyString(group, c);
        value = undefined;
        if (isOfType(c, QLineEdit)) {
            value = c.text;
        }
        if (isOfType(c, QPlainTextEdit)) {
            value = c.plainText;
        }
        if (isOfType(c, RMathLineEdit)) {
            //value = [c.text, c.getDefaultUnit()];
            value = c.text;
        }
        if (isOfType(c, QCheckBox)) {
            value = c.checked;
        }
        if (isOfType(c, QRadioButton) ||
            isOfType(c, QToolButton) ||
            isOfType(c, QPushButton)) {

            if (!c.group() && !c.autoExclusive) {
                if (c.checkable) {
                    value = c.checked;
                }
            }
            else {
                if (c.checked) {
                    // if tool button or radio button is in a group,
                    // the button group or group box handles the value:
                    value = c.objectName;
                }
            }
        }
        /*
        if (c.toString() == "QButtonGroup") {
            value = c.checkedButton().objectName;
        }
        */
        if (isOfType(c, QComboBox)) {
            var forceSaveText = false;
            var forceSaveIndex = false;
            if (typeof(c["ForceSaveText"]) != "undefined"
                    && c["ForceSaveText"] === true) {
                forceSaveText = true;
            }
            if (typeof(c["ForceSaveIndex"]) != "undefined"
                    && c["ForceSaveIndex"] === true) {
                forceSaveIndex = true;
            }
            if (forceSaveIndex == true) {
                value = c.currentIndex;
            }
            else if (forceSaveText === true || isNull(c.itemData(c.currentIndex))) {
                value = c.currentText;
            } else {
                value = c.itemData(c.currentIndex);
            }
        }
        if (isOfType(c, RColorCombo)) {
            value = c.getColor();
        }
        if (isOfType(c, RLineweightCombo)) {
            value = c.getLineweight();
        }
        if (isOfType(c, RLinetypeCombo)) {
            value = c.getLinetype();
        }
        if (isOfType(c, QSpinBox)) {
            value = c.value;
        }
        if (isOfType(c, QListWidget)) {
            var items = new Array();
            if (c.count != 0) {
                for ( var j = 0; j < c.count; ++j) {
                    items.push(c.item(j).text());
                }
            }
            value = items;

            // save user data of current item
            data = undefined;
            if (!isNull(c.currentItem())) {
                data = c.currentItem().data(Qt.UserRole);
            }
            if (!isNull(data)) {
                var dataKey = key + ".data";
                if (document) {
                    document.setVariable(dataKey, data);
                } else {
                    RSettings.setValue(dataKey, data);
                }
            }
        }
        if (c.toString().startsWith("RFontChooserWidget")) {
            value = c.getFont();
        }

        if (isNull(value)) {
            WidgetFactory.saveState(c, group, document, map);
            continue;
        }

        // save property
        if (typeof(c["SaveProperty"]) != "undefined") {
            var prop = c["SaveProperty"];
            RSettings.setValue(key + "." + prop, c[prop]);
        }

        // widgets with dynamic property "RequiresRestart" trigger a
        // restart application warning after changing preferences:
        if (typeof(c["RequiresRestart"]) != "undefined"
            && c["RequiresRestart"] === true) {
            WidgetFactory.requiresRestart = true;
        }

        // widgets can be ignored by setting the dynamic property
        // "SaveContents" = false
        var saveContents = true;
        if (typeof(c["SaveContents"]) != "undefined"
                && c["SaveContents"] === false) {
            saveContents = false;
        }

        if (saveContents) {
            if (document) {
                // save key / value pair to document:
                document.setVariable(key, value);
            } else if (map) {
                // save key / value pair to map:
                map.put(key, value);
            } else {
                // save key / value pair to settings (e.g. ini file):
                RSettings.setValue(key, value);
            }
        }
    }
};

/**
 * Restores the state of the given \c widget to a previously saved state.
 *
 * \param group Used internally for recursive calls.
 * \param signalReceiver Object that receives signals whenever a child widget
 *      changes its value.
 * \param reset True: Reset values to original values as defined in
 *      designer (.ui file). \see resetState
 * \param document RDocument object to restore settings from or \c undefined
 *      to restore settings from RSettings (user scope, config file).
 * \param map Map object to restore settings from.
 */
WidgetFactory.restoreState = function(widget, group, signalReceiver, reset, document, map) {
    var f, index, j, hasData;
    
    var topLevelSet = false;
    if (isNull(WidgetFactory.topLevelWidget)) {
        widget.slotSettingChanged = function() {
            if (isFunction(this.settingChangedEvent)) {
                this.settingChangedEvent();
            }
            this.setProperty("hasChanged", true);
        };
        WidgetFactory.topLevelWidget = widget;
        topLevelSet = true;
    }
    group = (isNull(group) ? widget.objectName : group);
    reset = (isNull(reset) ? false : reset);

    if (isDeleted(widget)) {
        return;
    }

    var children = widget.children();
    for ( var i = 0; i < children.length; ++i) {
        var c = children[i];
        
        if (!c || isDeleted(c)) {
            break;
        }

        // ignore widgets without name:
        if (isNull(c.objectName) || c.objectName==="") {
            continue;
        }

        // ignore Qt internal widgets:
        if (c.objectName==="qt_toolbar_ext_button") {
            continue;
        }

        // skip children from other groups in this widget (for options toolbar):
        // but not if used from a test [map != undefined]
        if (isNull(map) && typeof (c["SettingsGroup"]) != "undefined"
                && c["SettingsGroup"] !== group) {
            continue;
        }

        // skip ignored children (future need?):
        //if (typeof(c["Ignore"])!="undefined" && c["Ignore"]==true) {
        //    continue;
        //}

        // handle widgets which have their own reset method
        var hasOwnReset = false;
        if (typeof(c["hasOwnReset"]) != "undefined" && c["hasOwnReset"] == true) {
            hasOwnReset = true;
        }
        if (reset && hasOwnReset) {
            if (isFunction(c.resetState)) {
                c.resetState();
            }
            continue;
        }
        
        var key = WidgetFactory.getKeyString(group, c);
        var value;
        if (reset && !isNull(c.defaultValue) && (typeof(c["SettingsGroup"])=="undefined" ||
                c["SettingsGroup"]===group)) {
            value = c.defaultValue;
        } else {
            if (!isNull(map)) {
                value = map.get(key);                
            } else {
                if (!isNull(document)) {
                    value = document.getVariable(key);
                }
                // document has no value for key, try settings for default value:
                if (isNull(document) || isNull(value)) {
                    value = RSettings.getValue(key);
                }
            }
        }

        // only process children if key delivered no value:
        if (isNull(value) || isOfType(c, QGroupBox)) {
            // never process internal children of these widgets:
            if (!isOfType(c, QSpinBox) &&
                !isOfType(c, QComboBox) &&
                !isOfType(c, QPlainTextEdit) &&
                !isOfType(c, RMathLineEdit)) {

                WidgetFactory.restoreState(c, group, signalReceiver, reset,
                        document, map);
            }
        }

        // don't restore widgets that have been restored elsewhere (e.g. script
        // add-ons might load widgets contents by themselves in initPreferences):
        // [but always restore widgets if used from a test (map != undefined)]
        if (isNull(map) && !reset && typeof (c["Loaded"]) != "undefined"
                && c["Loaded"] === true) {
            value = undefined;
        }

        // restore property
        if (typeof(c["SaveProperty"]) != "undefined") {
            var prop = c["SaveProperty"];
            var val = RSettings.getValue(key + "." + prop);
            if (!isNull(val)) {
                c[prop] = val;
            }
        }
        
        if (isOfType(c, QLabel)) {
            continue;
        }

//        qDebug("restoring: ", c.objectName);
//        qDebug("  value: ", value);

//        if (c.objectName==="RampOn") {
//            debugger;
//        }

        if (isOfType(c, QLineEdit)) {
            WidgetFactory.connect(c.textChanged, signalReceiver, c.objectName);
            c.textChanged.connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
            if (isNull(c.defaultValue)) {
                c.setProperty("defaultValue", c.text);
            }
            if (!isNull(value)) {
                c.text = value;
            }
            continue;
        }
        if (isOfType(c, QPlainTextEdit)) {
            WidgetFactory.connect(c.textChanged, signalReceiver, c.objectName);
            c.textChanged.connect(WidgetFactory.topLevelWidget,
                    "slotSettingChanged");
            if (isNull(c.defaultValue)) {
                c.setProperty("defaultValue", c.plainText);
            }
            if (!isNull(value)) {
                c.plainText = value;
            }
            continue;
        }        
        if (isOfType(c, RMathLineEdit)) {
            WidgetFactory.connect(c.valueChanged, signalReceiver, c.objectName);
            c.valueChanged.connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
            if (isNull(c.defaultValue)) {
                //c.defaultValue = [c.text, c.getDefaultUnit()];
                c.defaultValue = c.text;
                c.slotTextChanged(c.text);
            }
            if (!isNull(value)) {
                // deprecated: value and default unit:
                if (isArray(value) && value.length===2) {
                    c.text = value[0];
                }
                else {
                    if (isString(value)) {
                        c.text = value;
                    }
                    else {
                        c.text = "%1".arg(value);
                    }
                }
            }
            continue;
        }
        if (isOfType(c, QToolButton) || isOfType(c, QPushButton)) {

            if (!c.group() && !c.autoExclusive) {
                if (c.checkable) {
                    WidgetFactory.connect(c.toggled, signalReceiver, c.objectName);
                    c.toggled.connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
                    if (isNull(c.defaultValue)) {
                        c.defaultValue = c.checked;
                    }
                    if (!isNull(value)) {
                        c.checked = (value === true || value === "true");
                    }
                }
                else {
                    WidgetFactory.connect(c.clicked, signalReceiver, c.objectName, false);
                }
            }
            else {
                WidgetFactory.connect(c.toggled, signalReceiver, c.objectName);
            }
            continue;
        }
        if (isOfType(c, QCheckBox)) {
            WidgetFactory.connect(c.toggled, signalReceiver, c.objectName);
            c.stateChanged.connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
            if (isNull(c.defaultValue)) {
                c.defaultValue = c.checked;
                if (!isNull(signalReceiver)) {
                    f = signalReceiver["slot"+c.objectName+"Changed"];
                    if (isFunction(f)) {
                        f.call(signalReceiver, c.checked);
                    }
                }
            }
            if (!isNull(value)) {
                c.checked = (value === true || value == "true");
            }
            continue;
        }
        if (isOfType(c, QRadioButton)) {
            if (!c.group() && !c.autoExclusive) {
                WidgetFactory.connect(c.toggled, signalReceiver, c.objectName);
                c.toggled.connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
                if (isNull(c.defaultValue)) {
                    c.defaultValue = c.checked;
                }
                if (!isNull(value)) {
                    c.checked = (value === true || value == "true");
                }
            }
            else {
                WidgetFactory.connect(c.toggled, signalReceiver, c.objectName);
                c.toggled.connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
                c.checked = (c.objectName == value);
            }
            continue;
        }
        if (isOfType(c, QButtonGroup)) {
            WidgetFactory.connect(c["buttonClicked(QAbstractButton*)"], signalReceiver, c.objectName);
            if (isNull(c.defaultValue)) {
                var button = c.checkedButton();
                if (button) {
                    c.defaultValue = button.objectName;
                    if (!isNull(signalReceiver)) {
                        f = signalReceiver["slot"+c.objectName+"Changed"];
                        if (isFunction(f)) {
                            f.call(signalReceiver, button);
                        }
                    }
                }
            }
            if (!isNull(value)) {
                var buttons = c.buttons();
                for (var k=0; k<buttons.length; k++) {
                    if (buttons[k].objectName==value) {
                        buttons[k].checked = true;
                        if (!isNull(signalReceiver)) {
                            f = signalReceiver["slot"+c.objectName+"Changed"];
                            if (isFunction(f)) {
                                f.call(signalReceiver, buttons[k]);
                            }
                        }
                        break;
                    }
                }
            }
        }
        if (isOfType(c, QComboBox) && c.editable) {
            WidgetFactory.connect(c.editTextChanged, signalReceiver, c.objectName);
            c.editTextChanged.connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
            if (isNull(c.defaultValue)) {
                c.defaultValue = c.currentText;
                if (!isNull(signalReceiver)) {
                    f = signalReceiver["slot" + c.objectName + "Changed"];
                    if (isFunction(f)) {
                        f.call(signalReceiver, c.currentText);
                    }
                }
            }
            if (!isNull(value)) {
                index = c.findText(value);
                if (index !== -1) {
                    c.currentIndex = index;
                    continue;
                }
                qDebug("setting text of " + c.objectName + " to: " + value);
                c.setEditText(value);
            }
            continue;
        }
        if (isOfType(c, QComboBox) && !c.editable) {
            WidgetFactory.connect(c['currentIndexChanged(int)'], signalReceiver, c.objectName);
            c["currentIndexChanged(int)"].connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
            hasData = false;
            if (c.itemData(c.currentIndex)!=undefined) {
                hasData = true;
            }
            if (isNull(c.defaultValue)) {
                if (hasData) {
                    c.defaultValue = c.itemData(c.currentIndex);
                } else {
                    c.defaultValue = c.currentText;
                }
                if (signalReceiver!=undefined) {
                    f = signalReceiver["slot" + c.objectName + "Changed"];
                    if (typeof(f)=="function") {
                        f.call(signalReceiver, c.currentIndex);
                    }
                }
            }
            var forceSaveText = false;
            var forceSaveIndex = false;
            if (typeof(c["ForceSaveText"]) != "undefined"
                    && c["ForceSaveText"] == true) {
                forceSaveText = true;
            }
            if (typeof(c["ForceSaveIndex"]) != "undefined"
                    && c["ForceSaveIndex"] == true) {
                forceSaveIndex = true;
            }
            if (!isNull(value)) {
                if (forceSaveIndex == true) {
                    index = value;
                }
                else if (forceSaveText == false && hasData) {
                    index = c.findData(value);
                } else {
                    index = c.findText(value);
                }
                if (index !== -1) {
                    c.currentIndex = index;
                    continue;
                }
            }
            continue;
        }
        if (isOfType(c, RColorCombo)) {
            WidgetFactory.connect(c.editTextChanged, signalReceiver, c.objectName);
            c["currentIndexChanged(int)"].connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
            if (isNull(c.defaultValue)) {
                c.defaultValue = c.getColor();
            }
            if (!isNull(value)) {
                // color name given:
                if (isString(value)) {
                    c.setColor(new RColor(value));
                }

                // color object given:
                else {
                    c.setColor(value);
                }
            }
            continue;
        }
        if (isOfType(c, RLineweightCombo)) {
            WidgetFactory.connect(c.editTextChanged, signalReceiver, c.objectName);
            c["currentIndexChanged(int)"].connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
            if (isNull(c.defaultValue)) {
                c.defaultValue = c.getLineweight();
            }
            if (!isNull(value)) {
                c.setLineweight(value);
            }
            continue;
        }
        if (isOfType(c, RLinetypeCombo)) {
            WidgetFactory.connect(c.editTextChanged, signalReceiver, c.objectName);
            c["currentIndexChanged(int)"].connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
            if (isNull(c.defaultValue)) {
                c.defaultValue = c.getLinetype();
            }
            if (!isNull(value)) {
                c.setLinetype(value);
            }
            continue;
        }
        if (isOfType(c, QSpinBox)) {
            WidgetFactory.connect(c["valueChanged(int)"], signalReceiver, c.objectName);
            c["valueChanged(int)"].connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
            if (isNull(c.defaultValue)) {
                c.defaultValue = c.value;
                if (signalReceiver!=undefined) {
                    f = signalReceiver["slot" + c.objectName + "Changed"];
                    if (isFunction(f)) {
                        f.call(signalReceiver, c.value);
                    }
                }
            }
            if (!isNull(value)) {
                c.value = value;
            }
            continue;
        }
        if (isOfType(c, QListWidget)) {
            // the SaveContents property is set to false
            // if the list contents should not be saved to
            // the configuration file or document:
            var saveContents = true;
            if (typeof(c["SaveContents"]) != "undefined"
                    && c["SaveContents"] == false) {
                saveContents = false;
            }

            if (saveContents) {
                if (isNull(c.defaultValue)) {
                    var items = new Array();
                    for (j = 0; j < c.count; ++j) {
                        items.push(c.item(j).text());
                    }
                    c.defaultValue = items;
                }
                if (!isNull(value)) {
                    c.addItems(value);
                }
            } else {
                if (isNull(c.defaultValue) && !isNull(c.currentItem())) {
                    c.defaultValue = c.currentItem().data(Qt.UserRole);
                }
                if (!isNull(value)) {
                    for (j=0; j<c.count; ++j) {
                        if (c.item(j).data(Qt.UserRole) == value) {
                            c.currentRow = j;
                            break;
                        }
                    }
                }
            }

            if (reset===false) {
                // restore user data of selected row
                hasData = false;
                if (!isNull(c.item(0)) && !isNull(c.item(0).data(Qt.UserRole))) {
                    hasData = true;
                }
                if (hasData) {
                    var data;
                    var dataKey = key + ".data";
                    if (!isNull(document)) {
                        data = document.getVariable(dataKey);
                    }
                    // document has no value for key,
                    // try settings for default value
                    if (isNull(document) || isNull(data)) {
                        data = RSettings.getValue(dataKey);
                    }
                    if (!isNull(data)) {
                        for (j = 0; j < c.count; ++j) {
                            if (c.item(j).data(Qt.UserRole) == data.toString()) {
                                c.currentRow = j;
                                break;
                            }
                        }
                    }
                }
            }

            WidgetFactory.connect(c.itemChanged, signalReceiver, c.objectName);
            c.itemSelectionChanged.connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
            c.model().rowsInserted.connect(WidgetFactory.topLevelWidget, "slotSettingChanged");            
            
            continue;
        }
        if (isOfType(c, RFontChooserWidget)) {
            WidgetFactory.connect(c.valueChanged, signalReceiver, c.objectName);
            c.valueChanged.connect(WidgetFactory.topLevelWidget, "slotSettingChanged");
            if (isNull(c.defaultValue)) {
                c.defaultValue = c.getFont();
            }
            if (!isNull(value)) {
                if (isString(value)) {
                    var fnt = new QFont();
                    fnt.fromString(value);
                    value = fnt;
                }

                c.setFont(value);
            }
            continue;
        }
    }
    
    if (topLevelSet) {
        WidgetFactory.topLevelWidget = undefined;
    }
};

/**
 * Resets values to original values as defined in designer (.ui file).
 */
WidgetFactory.resetState = function(widget, group) {
    WidgetFactory.restoreState(widget, group, undefined, true);
};

/**
 * \internal
 */
WidgetFactory.connect = function(sig, signalReceiver, objectName, isValue) {
    if (isNull(signalReceiver)) {
        return;
    }

    // connect signal to given function:
    if (isFunction(signalReceiver)) {
        sig.connect(signalReceiver);
        return;
    }

    // connect signal to automatically named slot of receiver object:
    var slot;
    if (isNull(isValue) || isValue===true) {
        slot = "slot" + objectName + "Changed";
    }
    else {
        slot = "slot" + objectName;
    }

    //if (eval("signalReceiver." + slot) != undefined) {
    if (!isNull(signalReceiver[slot])) {
        sig.connect(signalReceiver, slot);
    }
};

/**
 * Moves all child objects from sourceWidget to targetWidget (usually a toolbar).
 *
 * \return Array of actions that were added to targetWidget.
 */
WidgetFactory.moveChildren = function(sourceWidget, targetWidget, settingsGroup) {
    var ret = new Array();

    // move child widgets of UI file based widget directly to
    // options toolbar. rendering of tool buttons greatly depends
    // on this (especially on Mac OS X):
    var children = sourceWidget.children();
    for(var i=0;i<children.length;++i) {
        var w=children[i];
        w.setProperty("SettingsGroup", settingsGroup);

        // add separator:
        if (isOfType(w, QFrame) && w.frameShape==QFrame.VLine) {
            ret.push(targetWidget.addSeparator());
        }

        // reparent required for non-widgets (e.g. QButtonGroup):
        else if (!isFunction(w.show)) {
            // these children would crash QCAD on exit if they are reparented:
            if (!w.toString().startsWith("QBoxLayout") &&
                !w.toString().startsWith("QFormInternal") &&
                !w.toString().startsWith("QVariantAnimation")) {

                w.setParent(targetWidget);
            }
        }

        // add widgets:
        else {
            if (isOfType(w, QLabel) || isOfType(w, QCheckBox)) {
                // prevent styles from overriding fixed size (e.g. for icon labels):
                if (w.sizePolicy.horizontalPolicy()!==QSizePolicy.Fixed) {
                    w.styleSheet = "margin-left: 5px;  margin-right: 5px;" + w.styleSheet;
                }
            }
            // add line edit or math edit with maximum width:
            if (isOfType(w, QLineEdit) || isOfType(w, RMathLineEdit)) {
                if (w.maximumWidth>=1024) {
                    w.maximumWidth = 100;
                }
            }
            var a = targetWidget.addWidget(w);
            a.objectName = w.objectName + "Action";
            ret.push(a);
        }

        // automatically set tool tip and icon for reset button:
        if (w.objectName==="Reset") {
            w.icon = new QIcon("scripts/ResetToDefaults.svg");
            w.toolTip = qsTr("Restore defaults");
        }
    }

    return ret;
};

/**
 * Adds an "insert symbol" menu entry to the context menu of the given
 * line edit.
 *
 * \param lineEdit QLineEdit object
 * \param dimension bool Add symbols that are only appropriate for
 *    dimension labels (<> for measured value).
 */
WidgetFactory.initLineEdit = function(lineEdit, dimension) {
    lineEdit.contextMenuPolicy = Qt.CustomContextMenu;
    lineEdit.customContextMenuRequested.connect(function(pos) {
        var menu = lineEdit.createStandardContextMenu();

        var subMenu = new QMenu(qsTr("Insert Symbol"));

        var symbols = [
                ["\u00F8", qsTr("Diameter")],
                ["\u00B0", qsTr("Degree")],
                ["\u00B1", qsTr("Plus/Minus")],
                ["\u2248", qsTr("Almost equal to")],
                ["\u2243", qsTr("Asymptotically equal to")],
                ["\u03C0", qsTr("Pi")],
                ["\u00D7", qsTr("Multiplication")],
                ["\u00F7", qsTr("Division")],
                ["\u25FB", qsTr("Square")],
                ["\u0394", qsTr("Delta")],
                ["\\SA^B;", qsTr("Stacked text"), "\\\\SA^B;"]
        ];

        if (dimension===true) {
            symbols.unshift([]);
            symbols.unshift(["<>", qsTr("Measured value")]);
        }

        for (var i=0; i<symbols.length; ++i) {
            var symbol = symbols[i];

            if (symbol.length===0) {
                subMenu.addSeparator();
                continue;
            }

            var symbolSelf = symbol[0];
            var symbolText = symbol[1];
            var insertion = symbol[0];
            if (symbol.length===3) {
                insertion = symbol[2];
            }

            var action = subMenu.addAction(symbolSelf + "\t(" + symbolText + ")");
            eval("action.triggered.connect(function() { lineEdit.setFocus(Qt.OtherFocusReason); lineEdit.insert(\"" + insertion + "\"); });");
        }

        var actions = menu.actions();
        menu.removeAction(actions[actions.length-1]);
        menu.removeAction(actions[actions.length-2]);
        var separatorAction = menu.insertSeparator(actions[0]);
        menu.insertMenu(separatorAction, subMenu);
        menu.exec(QCursor.pos());
        if (!isDeleted(menu)) {
            menu.destroy();
        }
    });
};

WidgetFactory.initWebView = function(webView, linkHandler, slot) {
    var webPage = webView.page();
    webPage.linkDelegationPolicy = QWebPage.DelegateExternalLinks;
    webPage.linkClicked.connect(linkHandler, slot);
    var webSettings = webView.settings();
    webSettings.setFontFamily(QWebSettings.StandardFont, EAction.getMainWindow().font.family());
    if (RS.getSystemId()==="osx") {
        webSettings.setFontSize(QWebSettings.DefaultFontSize, EAction.getMainWindow().font.pointSize());
    }

    // make web view transparent:
    var palette = webView.palette;
    palette.setBrush(QPalette.Base, new QColor(0,0,0,0));
    webPage.palette = palette;
    webView.setAttribute(Qt.WA_OpaquePaintEvent, false);
};
