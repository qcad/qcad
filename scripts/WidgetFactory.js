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

include("scripts/library.js");
include("scripts/map.js");

function WidgetFactory() {
}

WidgetFactory.includeBasePath = includeBasePath;

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

    var candidates;
    if (!new QFileInfo(uiFile).isAbsolute()) {
        candidates = [
            uiFile,
            basePath + "/" + uiFile
        ];
        if (!uiFile.startsWith(":")) {
            candidates.push(":" + uiFile);
        }
        if (!basePath.startsWith(":")) {
            candidates.push(":" + basePath + "/" + uiFile);
        }
    }
    else {
        candidates = [
            uiFile
        ];
    }

    for (var i=0; i<candidates.length; i++) {
        var candidate = candidates[i];
        var fileInfo = new QFileInfo(candidate);
        if (fileInfo.exists()) {
            uiFile = candidate;
        }
    }

    var fileInfo = new QFileInfo(uiFile);
    if (!fileInfo.exists()) {
        qWarning("WidgetFactory: File %1 does not exist".arg(uiFile));
        return undefined;
    }

    var buf = RFileCache.getBuffer(uiFile);

    if (isNull(buf)) {
        return undefined;
    }

    //buf.open(makeQIODeviceOpenMode(QIODevice.ReadOnly));

    var loader = new QUiLoader();
    loader.setWorkingDirectory(fileInfo.dir());

    var formWidget = loader.load(buf, parent);
    buf.close();
    destr(loader);

    if (isNull(formWidget)) {
        qDebug("WidgetFactory.createWidget: widget is NULL");
    }

    if (RS.getSystemId()==="osx") {
        WidgetFactory.installComboBoxEventFilter(formWidget);
    }

    WidgetFactory.adjustIcons(fileInfo.absolutePath(), formWidget);

    return formWidget;
};

/**
 * Creates a dialog from the given UI file.
 * Overrides exec for testing dashboard mode.
 */
WidgetFactory.createDialog = function(basePath, uiFile, parent) {
    var dialog = WidgetFactory.createWidget(basePath, uiFile, parent);

    var flags = dialog.windowFlags();
    flags = makeQtWindowFlags(flags & ~(Qt.WindowContextHelpButtonHint));
    dialog.setWindowFlags(flags);

    // a global function might be defined to do additional
    // initialization for all dialogs (e.g. for testing purposes):
    if (typeof(initDialog)!=="undefined") {
        for (var i=0; i<initDialog.length; i++) {
            initDialog[i](dialog);
        }
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
    if (typeof(obj.property("SettingsGroup"))!="undefined") {
        g = obj.property("SettingsGroup");
    }
    var key = [g, obj.objectName];

    // correct key:
    if (isOfType(obj, QRadioButton) || isOfType(obj, QToolButton)) {
        // correct to button group name:
        if (isFunction(obj.group) && !isNull(obj.group())) {
            key = [g, obj.group().objectName];
        }
        else {
            var parent = obj.parent();
            // correct to group box (parent) name:
            if (parent && isOfType(parent, QGroupBox)) {
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

WidgetFactory.saveSize = function(widget) {
    if (!widget) {
        return;
    }
    var name = widget.objectName;
    if (name.length===0) {
        return;
    }
    RSettings.setValue(name + "/Width", widget.width);
    RSettings.setValue(name + "/Height", widget.height);
};

WidgetFactory.restoreSize = function(widget) {
    if (!widget) {
        return;
    }
    var name = widget.objectName;
    if (name.length===0) {
        return;
    }
    var w = RSettings.getIntValue(name + "/Width", widget.width);
    var h = RSettings.getIntValue(name + "/Height", widget.height);
    widget.resize(w, h);
};

/**
 * Saves the current state of the given \c widget and all its child widgets.
 *
 * \param group Used internally for recursive calls.
 * \param document RDocument or RObject to store settings or \c undefined to store
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

    // Qt5: QWebView has no scriptable children method:
    if (!isFunction(widget["children"])) {
        return;
    }

    var value;
    var data;
    var children = widget.children();
    for (var i = 0; i < children.length; ++i) {
        var c = children[i];


        if (!c || isDeleted(c) || c.toString().startsWith("QVariantAnimation") ||
                c.toString().startsWith("QWidgetAction") || c.objectName==="" ||
                c.objectName==="Icon" || c.objectName==="qt_toolbar_ext_button") {
            continue;
        }

        // ignore Qt internal widgets:
        if (typeof(c.objectName)!="undefined" &&
            c.objectName==="qt_toolbar_ext_button") {
            continue;
        }

        // ignore widgets that have been saved elsewhere (e.g. plugins might
        // save widgets contents by themselves in savePreferences):
        if (typeof(c.property("Saved")) != "undefined" && c.property("Saved")===true) {
            continue;
        }

        // skip children from other groups in this widget (for options toolbar):
        if (typeof(c.property("SettingsGroup")) != "undefined" && c.property("SettingsGroup") != group) {
            if (isNull(map)) {
                continue;
            }
        }

        var key = WidgetFactory.getKeyString(group, c);
        value = undefined;
        if (isOfType(c, QLineEdit)) {
            value = c.text;
        }
        else if (isOfType(c, QPlainTextEdit)) {
            value = c.toPlainText();
        }
        else if (isOfType(c, RMathLineEdit)) {
            //value = [c.text, c.getDefaultUnit()];
            value = c.text;
        }
        else if (isOfType(c, RMathComboBox)) {
            value = c.currentText;
        }
        else if (isOfType(c, QCheckBox)) {
            value = c.checked;
        }
        else if (isOfType(c, QRadioButton) ||
            isOfType(c, QToolButton) ||
            isOfType(c, QPushButton)) {

            if (isNull(c.group()) && !c.autoExclusive) {
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
        else if (isOfType(c, QComboBox) || isOfType(c, QFontComboBox)) {
            var forceSaveText = false;
            var forceSaveIndex = false;
            if (typeof(c.property("ForceSaveText")) != "undefined"
                    && c.property("ForceSaveText") === true) {
                forceSaveText = true;
            }
            if (typeof(c.property("ForceSaveIndex")) != "undefined"
                    && c.property("ForceSaveIndex") === true) {
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
        else if (isOfType(c, RColorCombo)) {
            value = c.getColor();
        }
        else if (isOfType(c, RLineweightCombo)) {
            value = c.getLineweight();
        }
        else if (isOfType(c, RLinetypeCombo)) {
            value = c.getLinetypePattern();
        }
        else if (isOfType(c, QSpinBox) || isOfType(c, QDoubleSpinBox)) {
            value = c.value;
        }
        else if (isOfType(c, QSlider)) {
            value = c.value;
        }
        else if (isOfType(c, QListWidget)) {
            var items = [];
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
                    if (isObject(document)) {
                        document.setCustomProperty("QCAD", dataKey, data);
                    }
                    else {
                        document.setVariable(dataKey, data);
                    }
                } else {
                    RSettings.setValue(dataKey, data);
                }
            }
        }
        else if (isOfType(c, RFontChooserWidget)) {
            value = c.getChosenFont();
        }

        if (isNull(value)) {
            WidgetFactory.saveState(c, group, document, map);
            continue;
        }

        // save property
        if (typeof(c.property("SaveProperty")) != "undefined") {
            var prop = c.property("SaveProperty");
            RSettings.setValue(key + "." + prop, c[prop]);
        }

        // widgets with dynamic property "RequiresRestart" trigger a
        // restart application warning after changing preferences:
        if (typeof(c.property("RequiresRestart")) != "undefined"
            && c.property("RequiresRestart") === true) {
            WidgetFactory.requiresRestart = true;
        }

        // widgets can be ignored by setting the dynamic property
        // "SaveContents" = false
        var saveContents = true;
        if (typeof(c.property("SaveContents")) != "undefined"
                && c.property("SaveContents") === false) {
            saveContents = false;
        }

        if (saveContents) {
            if (document) {
                if (isObject(document)) {
                    // make sure value of custom property is string, not QColor or RColor:
                    // ensures that it can be stored in DXF/DWG and displayed in property editor:
                    if (isOfType(value, QColor) || isOfType(value, RColor)) {
                        value = value.name();
                    }

                    // save key / value pair to object (e.g. layout block):
                    document.setCustomProperty("QCAD", key, value);
                }
                else {
                    // save key / value pair to document:
                    document.setVariable(key, value);
                }
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
 * \param document RDocument object or RObject to restore settings from or \c undefined
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

    // Qt5: QWebView has no scriptable children method:
    if (!isFunction(widget.children)) {
        return;
    }

    var children = widget.children();
    for ( var i = 0; i < children.length; ++i) {
        var c = children[i];
        
        if (!c || isDeleted(c)) {
            continue;
        }

        // ignore widgets without name:
        if (isNull(c.objectName) || c.objectName==="") {
            continue;
        }

        // ignore Qt internal widgets:
        if (c.objectName==="qt_toolbar_ext_button") {
            continue;
        }

        // ignore labels, widget actions:
        if (isOfType(c, QLabel) || isOfType(c, QWidgetAction)) {
            continue;
        }

        // skip children from other groups in this widget (for options toolbar):
        // but not if used from a test [map != undefined]
        if (isNull(map) && typeof (c.property("SettingsGroup")) != "undefined" && c.property("SettingsGroup") !== group) {
            continue;
        }

        // skip ignored children (future need?):
        //if (typeof(c["Ignore"])!="undefined" && c["Ignore"]==true) {
        //    continue;
        //}

        // handle widgets which have their own reset method
        var hasOwnReset = false;
        if (typeof(c.property("hasOwnReset")) != "undefined" && c.property("hasOwnReset") == true) {
            hasOwnReset = true;
        }
        if (reset && hasOwnReset) {
            if (isFunction(c.resetState)) {
                c.resetState();
            }
            continue;
        }
        
        var key = WidgetFactory.getKeyString(group, c);
        var value = undefined;
        if (reset && !isNull(c.property("defaultValue")) && (typeof(c.property("SettingsGroup"))=="undefined" || c.property("SettingsGroup")===group)) {
            value = c.property("defaultValue");
        } else {
            if (!isNull(map)) {
                value = map.get(key);
            } else {
                if (!isNull(document)) {
                    if (isObject(document)) {
                        value = document.getCustomProperty("QCAD", key, undefined);
                    }
                    else {
                        value = document.getVariable(key);
                    }
                }
                // document / object has no value for key, try settings for default value:
                if (isNull(document) || isNull(value)) {
                    value = RSettings.getValue(key);
                }
            }
        }

        // only process children if key delivered no value:
        if (isNull(value) || isOfType(c, QGroupBox)) {
            // never process internal children of these widgets:
            if (WidgetFactory.processChildren(c)) {
                WidgetFactory.restoreState(c, group, signalReceiver, reset, document, map);
            }
        }

        // don't restore widgets that have been restored elsewhere (e.g. script
        // add-ons might load widgets contents by themselves in initPreferences):
        // [but always restore widgets if used from a test (map != undefined)]
        if (isNull(map) && !reset && c.property("Loaded")===true) {
            value = undefined;
        }

        // restore property
        if (typeof(c.property("SaveProperty")) != "undefined") {
            var prop = c.property("SaveProperty");
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

        if (isOfType(c, QPlainTextEdit)) {
            if (!reset) {
                WidgetFactory.connectSignal(c.textChanged, signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c.textChanged, WidgetFactory.topLevelWidget, "Setting");
            }
            if (isNull(c.property("defaultValue"))) {
                c.setProperty("defaultValue", c.toPlainText());
            }
            if (!isNull(value)) {
                c.setPlainText(value);
            }
            continue;
        }
        if (isOfType(c, RMathLineEdit)) {
            if (!reset) {
                WidgetFactory.connectSignal(c.valueChanged, signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c.valueChanged, WidgetFactory.topLevelWidget, "Setting");
            }
            if (isNull(c.property("defaultValue"))) {
                //c.defaultValue = [c.text, c.getDefaultUnit()];
                c.setProperty("defaultValue", c.text);
                c.slotTextChanged(c.text);
            }
            if (!isNull(value)) {
                // deprecated: value and default unit:
                if (isArray(value) && value.length===2) {
                    if (isNull(value[0])) {
                        c.text = "";
                    }
                    else {
                        c.text = value[0].toString();
                    }
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
        if (isOfType(c, RMathComboBox)) {
            if (!reset) {
                WidgetFactory.connectSignal(c.valueChanged, signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c.valueChanged, WidgetFactory.topLevelWidget, "Setting");
            }
            if (isNull(c.property("defaultValue"))) {
                //c.defaultValue = [c.text, c.getDefaultUnit()];
                c.setProperty("defaultValue", c.currentText);
                c.slotTextChanged(c.currentText);
            }
            if (!isNull(value)) {
                if (isString(value)) {
                    c.currentText = value;
                }
                else {
                    c.currentText = "%1".arg(value);
                }
            }
            continue;
        }
        if (isOfType(c, QLineEdit)) {
            if (!reset) {
                WidgetFactory.connectSignal(c.textChanged, signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c.textChanged, WidgetFactory.topLevelWidget, "Setting");
            }

            if (isNull(c.property("defaultValue"))) {
                c.setProperty("defaultValue", c.text);
            }
            if (!isNull(value)) {
                c.text = value.toString();
            }
            continue;
        }
        if (isOfType(c, QToolButton) || isOfType(c, QPushButton)) {

            if (isNull(c.group()) && !c.autoExclusive) {
                if (c.checkable) {
                    if (!reset) {
                        WidgetFactory.connectSignal(c.toggled, signalReceiver, c.objectName);
                        WidgetFactory.connectSignal(c.toggled, WidgetFactory.topLevelWidget, "Setting");
                    }
                    if (isNull(c.property("defaultValue"))) {
                        c.setProperty("defaultValue", c.checked);
                    }
                    if (!isNull(value)) {
                        c.checked = (value === true || value === "true");
                    }
                }
                else {
                    if (!reset) {
                        WidgetFactory.connectSignal(c.clicked, signalReceiver, c.objectName, false);
                    }
                }
            }
            else {
                if (!reset) {
                    WidgetFactory.connectSignal(c.toggled, signalReceiver, c.objectName);
                }
            }
            continue;
        }
        if (isOfType(c, QCheckBox)) {
            if (!reset) {
                WidgetFactory.connectSignal(c.toggled, signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c.stateChanged, WidgetFactory.topLevelWidget, "Setting");
            }
            if (isNull(c.property("defaultValue"))) {
                c.setProperty("defaultValue", c.checked);
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
                WidgetFactory.connectSignal(c.toggled, signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c.toggled, WidgetFactory.topLevelWidget, "Setting");
                if (isNull(c.property("defaultValue"))) {
                    c.setProperty("defaultValue", c.checked);
                }
                if (!isNull(value)) {
                    c.checked = (value === true || value == "true");
                }
            }
            else {
                WidgetFactory.connectSignal(c.toggled, signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c.toggled, WidgetFactory.topLevelWidget, "Setting");
                if (value==="true") {
                    c.checked = true;
                }
                else {
                    c.checked = (c.objectName == value);
                }
            }
            continue;
        }
        if (isOfType(c, QButtonGroup)) {
            if (!reset) {
                WidgetFactory.connectSignal(c["buttonClicked(QAbstractButton*)"], signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c["buttonClicked(QAbstractButton*)"], WidgetFactory.topLevelWidget, "Setting");
            }
            if (isNull(c.property("defaultValue"))) {
                var button = c.checkedButton();
                if (!isNull(button) && !isNull(button.objectName)) {
                    c.setProperty("defaultValue", button.objectName);
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
        if ((isOfType(c, QComboBox) /*|| isOfType(c, RComboBox)*/) && c.editable) {
            if (!reset) {
                WidgetFactory.connectSignal(c.editTextChanged, signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c.editTextChanged, WidgetFactory.topLevelWidget, "Setting");
            }
            if (isNull(c.property("defaultValue"))) {
                c.setProperty("defaultValue", c.currentText);
                if (!isNull(signalReceiver)) {
                    f = signalReceiver["slot" + c.objectName + "Changed"];
                    if (isFunction(f)) {
                        f.call(signalReceiver, c.currentText);
                    }
                }
            }
            if (!isNull(value)) {
                index = c.findText(value.toString());
                if (index !== -1) {
                    c.currentIndex = index;
                    continue;
                }
                c.setEditText(value.toString());
            }
            continue;
        }
        if (((isOfType(c, QComboBox) /*|| isOfType(c, RComboBox)*/) && !c.editable) || isOfType(c, QFontComboBox)) {
            if (!reset) {
                WidgetFactory.connectSignal(c['currentIndexChanged(int)'], signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c['currentIndexChanged(int)'], WidgetFactory.topLevelWidget, "Setting");
            }
            hasData = false;
            if (c.itemData(c.currentIndex)!=undefined || (c.count>0 && c.itemData(0)!=undefined)) {
                hasData = true;
            }
            if (isNull(c.property("defaultValue"))) {
                if (hasData) {
                    if (c.currentIndex>=0 && c.currentIndex<c.count) {
                        c.setProperty("defaultValue", c.itemData(c.currentIndex));
                    }
                } else {
                    c.setProperty("defaultValue", c.currentText);
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
            if (typeof(c.property("ForceSaveText")) != "undefined"
                    && c.property("ForceSaveText") == true) {
                forceSaveText = true;
            }
            if (typeof(c.property("ForceSaveIndex")) != "undefined"
                    && c.property("ForceSaveIndex") == true) {
                forceSaveIndex = true;
            }
            if (!isNull(value)) {
                index = -1;
                if (forceSaveIndex == true) {
                    index = parseInt(value);
                }
                else if (forceSaveText == false && hasData) {
                    index = c.findData(value);
                } else {
                    if (isString(value)) {
                        index = c.findText(value);
                    }
                }
                if (index !== -1) {
                    c.currentIndex = index;
                    continue;
                }
            }
            continue;
        }
        if (isOfType(c, RColorCombo)) {
            if (!reset) {
                WidgetFactory.connectSignal(c.editTextChanged, signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c["currentIndexChanged(int)"], WidgetFactory.topLevelWidget, "Setting");
            }
            if (isNull(c.property("defaultValue"))) {
                c.setProperty("defaultValue", c.getColor());
            }
            if (!isNull(value)) {
                // color name given:
                if (isString(value)) {
                    c.setColor(new RColor(value));
                }

                // color object given:
                else {
                    if (isOfType(value, RColor)) {
                        c.setColor(value);
                    }
                    else {
                        qWarning("value is not of type RColor:", value);
                    }
                }
            }
            continue;
        }
        if (isOfType(c, RLineweightCombo)) {
            if (!reset) {
                WidgetFactory.connectSignal(c.editTextChanged, signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c["currentIndexChanged(int)"], WidgetFactory.topLevelWidget, "Setting");
            }
            if (isNull(c.property("defaultValue"))) {
                c.setProperty("defaultValue", c.getLineweight());
            }
            if (!isNull(value)) {
                if (isString(value)) {
                    value = parseInt(value, 10);
                }
                c.setLineweight(value);
            }
            continue;
        }
        if (isOfType(c, RLinetypeCombo)) {
            if (!reset) {
                WidgetFactory.connectSignal(c.editTextChanged, signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c["currentIndexChanged(int)"], WidgetFactory.topLevelWidget, "Setting");
            }
            if (isNull(c.property("defaultValue"))) {
                c.setProperty("defaultValue", c.getLinetypePattern());
            }
            if (!isNull(value)) {
                c.setLinetypePattern(value);
            }
            continue;
        }
        if (isOfType(c, QSpinBox) || isOfType(c, QDoubleSpinBox)) {
            if (!reset) {
                if (isOfType(c, QSpinBox)) {
                    WidgetFactory.connectSignal(c["valueChanged(int)"], signalReceiver, c.objectName);
                    WidgetFactory.connectSignal(c["valueChanged(int)"], WidgetFactory.topLevelWidget, "Setting");
                }
                else {
                    WidgetFactory.connectSignal(c["valueChanged(double)"], signalReceiver, c.objectName);
                    WidgetFactory.connectSignal(c["valueChanged(double)"], WidgetFactory.topLevelWidget, "Setting");
                }
            }
            if (isNull(c.property("defaultValue"))) {
                c.setProperty("defaultValue", c.value);
                if (signalReceiver!=undefined) {
                    f = signalReceiver["slot" + c.objectName + "Changed"];
                    if (isFunction(f)) {
                        f.call(signalReceiver, c.value);
                    }
                }
            }
            if (!isNull(value)) {
                if (isOfType(c, QSpinBox)) {
                    c.value = parseInt(value);
                }
                else {
                    c.value = parseFloat(value);
                }
            }
            continue;
        }
        if (isOfType(c, QSlider)) {
            if (!reset) {
                WidgetFactory.connectSignal(c["valueChanged(int)"], signalReceiver, c.objectName);
                WidgetFactory.connectSignal(c["valueChanged(int)"], WidgetFactory.topLevelWidget, "Setting");
            }
            if (isNull(c.property("defaultValue"))) {
                c.setProperty("defaultValue", c.value);
                if (signalReceiver!=undefined) {
                    f = signalReceiver["slot" + c.objectName + "Changed"];
                    if (isFunction(f)) {
                        f.call(signalReceiver, c.value);
                    }
                }
            }
            if (!isNull(value)) {
                c.value = parseInt(value);
            }
            continue;
        }
        if (isOfType(c, QListWidget)) {
            // the SaveContents property is set to false
            // if the list contents should not be saved to
            // the configuration file or document:
            var saveContents = true;
            if (typeof(c.property("SaveContents")) != "undefined"
                    && c.property("SaveContents") == false) {
                saveContents = false;
            }

            if (saveContents) {
                if (isNull(c.property("defaultValue"))) {
                    var items = [];
                    for (j = 0; j < c.count; ++j) {
                        items.push(c.item(j).text());
                    }
                    c.setProperty("defaultValue", items);
                }
                if (!isNull(value)) {
                    c.addItems(value);
                }
            } else {
                if (isNull(c.property("defaultValue")) && !isNull(c.currentItem())) {
                    c.setProperty("defaultValue", c.currentItem().data(Qt.UserRole));
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
                        if (isObject(document)) {
                            data = document.getCustomProperty("QCAD", key, undefined);
                        }
                        else {
                            data = document.getVariable(dataKey);
                        }
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

            if (!reset) {
                WidgetFactory.connectSignal(c.itemChanged, signalReceiver, c.objectName);
                c.itemSelectionChanged.connect(WidgetFactory.topLevelWidget, WidgetFactory.topLevelWidget.slotSettingChanged);
                c.model().rowsInserted.connect(WidgetFactory.topLevelWidget, WidgetFactory.topLevelWidget.slotSettingChanged);
            }
            
            continue;
        }
        if (isOfType(c, RFontChooserWidget)) {
            if (!reset) {
                WidgetFactory.connectSignal(c.valueChanged, signalReceiver, c.objectName);
                c.valueChanged.connect(WidgetFactory.topLevelWidget, WidgetFactory.topLevelWidget.slotSettingChanged);
            }
            if (isNull(c.property("defaultValue"))) {
                c.setProperty("defaultValue", c.getChosenFont());
            }
            if (!isNull(value)) {
                if (isString(value)) {
                    var fnt = new QFont();
                    fnt.fromString(value);
                    value = fnt;
                }

                c.setChosenFont(value);
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

WidgetFactory.processChildren = function(c) {
    if (isOfType(c, QSpinBox) ||
        isOfType(c, QDoubleSpinBox) ||
        isOfType(c, QComboBox) ||
        isOfType(c, QFontComboBox) ||
        isOfType(c, QPlainTextEdit) ||
        isOfType(c, RMathLineEdit) ||
        isOfType(c, RMathComboBox)) {

        return false;
    }

    return true;
};

/**
 * \internal
 */
WidgetFactory.connectSignal = function(sig, signalReceiver, objectName, isValue) {
    if (isNull(signalReceiver)) {
        return;
    }

    // connect signal to given function:
    // obsolete?
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
        if (RSettings.getQtVersion() >= 0x060000) {
            sig.connect(signalReceiver, signalReceiver[slot]);
        }
        else {
            sig.connect(signalReceiver, slot);
        }
    }
};

/**
 * Moves all child objects from sourceWidget to targetWidget (usually a toolbar).
 *
 * \return Array of actions that were added to targetWidget.
 */
WidgetFactory.moveChildren = function(sourceWidget, targetWidget, settingsGroup) {
    var ret = [];

    var a;

    // move child widgets of UI file based widget directly to
    // options toolbar. rendering of tool buttons greatly depends
    // on this (especially on macOS):
    var children = sourceWidget.children();
    for(var i=0;i<children.length;++i) {
        var w = children[i];
        if (isNull(w)) {
            continue;
        }

        w.setProperty("SettingsGroup", settingsGroup);

        // add separator:
        if (isSeparator(w)) {
            a = targetWidget.addSeparator();
            a.objectName = w.objectName + "Action";
            ret.push(a);
        }

        // reparent required for non-widgets (e.g. QButtonGroup):
        else if (!isFunction(w.show)) {
            // these children would crash QCAD on exit if they are reparented:
            if (!w.toString().startsWith("QBoxLayout") &&
                !w.toString().startsWith("QFormInternal") &&
                !w.toString().startsWith("QVariantAnimation")) {

                w.setParent(targetWidget);

                // make sure QButtonGroup is cleaned up when tool exits:
                if (w.toString().startsWith("QButtonGroup")) {
                    ret.push(w);
                }
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
            if (isOfType(w, QLineEdit) || isOfType(w, RMathLineEdit) || isOfType(w, RMathComboBox)) {
                if (w.maximumWidth>=1024) {
                    w.maximumWidth = 75;
                }
            }

            if (isOfType(w, RMathLineEdit) || isOfType(w, RMathComboBox)) {
                WidgetFactory.initLineEditInfoTools(w);
            }

            a = targetWidget.addWidget(w);
            a.objectName = w.objectName + "Action";
            ret.push(a);
        }

        // automatically set tool tip and icon for reset button:
        if (w.objectName==="Reset") {
            w.icon = new QIcon(WidgetFactory.includeBasePath + "/ResetToDefaults.svg");
            w.toolTip = qsTr("Restore defaults");
        }
    }

    return ret;
};

WidgetFactory.adjustIcons = function(includeBasePath, widget) {
    if (isNull(widget) || !isFunction(widget.children)) {
        return;
    }

    var children = widget.children();
    for(var i=0;i<children.length;++i) {
        var w=children[i];

        // adjust icon for theme / dark mode:
        if (isOfType(w, QToolButton)) {
            var iconFile = autoIconPath(includeBasePath + "/" + w.objectName + ".svg");
            if (iconFile.length!==0) {
                w.icon = new QIcon(iconFile);
            }
        }
        else {
            WidgetFactory.adjustIcons(includeBasePath, w);
        }
    }
};

WidgetFactory.initLineEditInfoTools = function(mathLineEdit) {
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
        var menu = WidgetFactory.createLineEditContextMenu(lineEdit, dimension);
        menu.exec(QCursor.pos());
        if (!isDeleted(menu)) {
            destr(menu);
        }
    });
};

WidgetFactory.createLineEditContextMenu = function(lineEdit, dimension) {
    var menu = lineEdit.createStandardContextMenu();

    var subMenu = new QMenu(qsTr("Insert Symbol"));

    // TODO: split into submenus (math, greek, ...):
    var symbols = [
                [0x00B0, qsTr("Degrees")],
                [0x00B1, qsTr("Plus/Minus")],
                [0x00F8, qsTr("Diameter")],
                [0x00F7, qsTr("Division")],
                [0x2248, qsTr("Almost Equal")],
                [0x2220, qsTr("Angle")],
                [0x2312, qsTr("Arc")],
                [0x2243, qsTr("Asymptotically Equal")],
                //[0xE100, qsTr("Boundary Line")],
                [0x2104, qsTr("Center Line")],
                [0x0394, qsTr("Delta")],
                [0x0278, qsTr("Electrical Phase")],
                //[0xE101, qsTr("Flow Line")],
                [0x2261, qsTr("Identity")],
                //[0xE200, qsTr("Initial Length")],
                //[0xE102, qsTr("Monument Line")],
                [0x00D7, qsTr("Multiplication")],
                [0x2260, qsTr("Not Equal")],
                [0x2126, qsTr("Ohm")],
                [0x03A9, qsTr("Omega")],
                [0x03C9, qsTr("omega")],
                [0x03A6, qsTr("Phi")],
                [0x0278, qsTr("phi")],
                [0x03C6, qsTr("Alt phi")],
                [0x03C0, qsTr("Pi")],
                [0x214A, qsTr("Property Line")],
                [0x2082, qsTr("Subscript 2")],
                [0x221A, qsTr("Square Root")],
                [0x25FB, qsTr("Square")],
                [0x00B2, qsTr("Squared")],
                [0x00B3, qsTr("Cubed")],
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

        var symbolCode = symbol[0];
        var symbolCodeStr;
        var symbolSelf;

        if (isNumber(symbolCode)) {
            symbolCodeStr = symbolCode.toString(16);
            // pad code string with zeroes: e.g. 03A9:
            while (symbolCodeStr.length<4) {
                symbolCodeStr = "0" + symbolCodeStr;
            }
            symbolCodeStr = " - \\U+" + symbolCodeStr;

            symbolSelf = String.fromCharCode(symbolCode);
        }
        else {
            symbolCodeStr = "";
            symbolSelf = symbolCode;
        }

        var insertion;
        if (symbol.length===3) {
            // insertion from third column of list:
            insertion = symbol[2];
        }
        else if (isNumber(symbolCode)) {
            // insertion is single char:
            insertion = String.fromCharCode(symbol[0]);
        }
        else {
            // insertion is string (first column):
            insertion = symbol[0];
        }

        var symbolText = symbol[1];

        var action = subMenu.addAction(symbolSelf + "\t(" + symbolText + symbolCodeStr + ")");
        eval("action.triggered.connect(function() { lineEdit.setFocus(Qt.OtherFocusReason); lineEdit.insert(\"" + insertion + "\"); });");
    }

    var actions = menu.actions();
    menu.removeAction(actions[actions.length-1]);
    menu.removeAction(actions[actions.length-2]);
    var separatorAction = menu.insertSeparator(actions[0]);
    menu.insertMenu(separatorAction, subMenu);

    return menu;
};

WidgetFactory.initTextBrowser = function(textBrowser, slot) {
    textBrowser.openLinks = false;
    textBrowser.anchorClicked.connect(slot);
};

//WidgetFactory.initWebView = function(webView, linkHandler, slot) {
//    var webPage = webView.page();
//    webPage.linkDelegationPolicy = QWebPage.DelegateExternalLinks;
//    webPage.linkClicked.connect(linkHandler, slot);
//    var webSettings = webView.settings();
//    webSettings.setFontFamily(QWebSettings.StandardFont, EAction.getMainWindow().font.family());
//    if (RS.getSystemId()==="osx") {
//        webSettings.setFontSize(QWebSettings.DefaultFontSize, EAction.getMainWindow().font.pointSize());
//    }

//    if (!RSettings.isQt(5)) {
//        // make web view transparent:
//        var palette = webView.palette;
//        palette.setBrush(QPalette.Base, new QColor(0,0,0,0));
//        webPage.palette = palette;

//        webView.setAttribute(Qt.WA_OpaquePaintEvent, false);
//    }
//};

WidgetFactory.initLayerCombo = function(comboBox, doc, clear) {
    var i;

    if (isNull(doc)) {
        return;
    }
    if (isNull(clear)) {
        clear = true;
    }

    var existingLayerNames = [];
    if (clear) {
        comboBox.clear();
    }
    else {
        for (i=0; i<comboBox.count; i++) {
            var t = comboBox.itemText(i);
            existingLayerNames.push(t);
        }
    }

    comboBox.iconSize = new QSize(16, 10);
    var names = doc.getLayerNames();
    //names = RS.sortAlphanumerical(names);
    names.sort(Array.alphaNumericalSorter);
    for (i=0; i<names.length; i++) {
        var name = names[i];
        var layer = doc.queryLayer(name);

        if (existingLayerNames.containsIgnoreCase(layer.getName())) {
            // don't overwrite existing layers:
            continue;
        }

        var icon = RColor.getIcon(layer.getColor(), new QSize(comboBox.iconSize.width(),10));
        comboBox.addItem(icon, layer.getName());
    }
};

WidgetFactory.initBlockCombo = function(comboBox, doc, showSpaces) {
    if (isNull(doc)) {
        return;
    }
    if (isNull(showSpaces)) {
        showSpaces = false;
    }

    comboBox.clear();
    var names = doc.getBlockNames();
    names.sort(Array.alphaNumericalSorter);
    //names = RS.sortAlphanumerical(names);
    for (var i=0; i<names.length; i++) {
        var name = names[i];
        if (showSpaces || !name.startsWith("*")) {
            comboBox.addItem(name);
        }
    }
};

WidgetFactory.initList = function(list, groupName) {
    if (isNull(list)) {
        return;
    }

    if (RSettings.getBoolValue(groupName + "/EnableAlternatingRowColor", false)===true) {
        list.alternatingRowColors = true;
        var p = list.palette;
        var col = RSettings.getColorValue(groupName + "/AlternatingRowColor", new RColor(230, 235, 250));
        p.setColor(QPalette.AlternateBase, new QColor(col.red(), col.green(), col.blue(), col.alpha()));
        list.palette = p;
    }
    else {
        list.alternatingRowColors = false;
    }
};

WidgetFactory.initHAlignCombo = function(comboBox) {
    comboBox.clear();
    comboBox.addItem(qsTr("Left"), RS.HAlignLeft);
    comboBox.addItem(qsTr("Center"), RS.HAlignCenter);
    comboBox.addItem(qsTr("Right"), RS.HAlignRight);
    comboBox.addItem(qsTr("Aligned"), RS.HAlignAlign);
    comboBox.addItem(qsTr("Middle"), RS.HAlignMid);
    comboBox.addItem(qsTr("Fit"), RS.HAlignFit);
};

WidgetFactory.initVAlignCombo = function(comboBox) {
    comboBox.clear();
    comboBox.addItem(qsTr("Top"), RS.VAlignTop);
    comboBox.addItem(qsTr("Middle"), RS.VAlignMiddle);
    comboBox.addItem(qsTr("Base"), RS.VAlignBase);
    comboBox.addItem(qsTr("Bottom"), RS.VAlignBottom);
};

WidgetFactory.initDimlunitCombo = function(comboBox) {
    comboBox.clear();
    comboBox.addItem(qsTr("Scientific"), RS.Scientific);
    comboBox.addItem(qsTr("Decimal"), RS.Decimal);
    comboBox.addItem(qsTr("Engineering"), RS.Engineering);
    comboBox.addItem(qsTr("Architectural"), RS.ArchitecturalStacked);
    comboBox.addItem(qsTr("Fractional"), RS.FractionalStacked);
};

WidgetFactory.initDimtadCombo = function(comboBox) {
    comboBox.clear();
    comboBox.addItem(qsTr("Centered"), 0);
    comboBox.addItem(qsTr("Above"), 1);
};

WidgetFactory.initDimdsepCombo = function(comboBox) {
    comboBox.clear();
    comboBox.addItem(".", '.');
    comboBox.addItem(",", ',');
};

WidgetFactory.initDimzinCombo = function(comboBox) {
    comboBox.clear();
    //comboBox.addItem(qsTr("Suppress 0'0\" (unsupported)"), 0);
    comboBox.addItem(qsTr("Show trailing zeroes"), 0);
    comboBox.addItem(qsTr("Include 0'0\"") + " " + qsTr("(unsupported)"), 1);
    comboBox.addItem(qsTr("Include 0', suppress 0\"") + " " + qsTr("(unsupported)"), 2);
    comboBox.addItem(qsTr("Include 0\", suppress 0'") + " " + qsTr("(unsupported)"), 3);
    comboBox.addItem(qsTr("Suppress leading zeroes") + " " + qsTr("(unsupported)"), 4);
    comboBox.addItem(qsTr("Suppress trailing zeroes"), 8);
    comboBox.addItem(qsTr("Suppress leading / trailing zeroes") + " " + qsTr("(unsupported)"), 12);

//    comboBox.addItem(qsTr("Suppress 0'0\""), 0);
//    comboBox.addItem(qsTr("Include 0'0\""), 1);
//    comboBox.addItem(qsTr("Include 0', suppress 0\""), 2);
//    comboBox.addItem(qsTr("Include 0\", suppress 0'"), 3);
};

WidgetFactory.initDimdecCombo = function(comboBox) {
    comboBox.clear();
    comboBox.addItem("0", 0);
    comboBox.addItem("1", 1);
    comboBox.addItem("2", 2);
    comboBox.addItem("3", 3);
    comboBox.addItem("4", 4);
    comboBox.addItem("5", 5);
    comboBox.addItem("6", 6);
    comboBox.addItem("7", 7);
    comboBox.addItem("8", 8);

};
WidgetFactory.initDimaunitCombo = function(comboBox) {
    comboBox.clear();
    comboBox.addItem(qsTr("Decimal Degrees"), RS.DegreesDecimal);
    comboBox.addItem(qsTr("Deg/min/sec"), RS.DegreesMinutesSeconds);
    comboBox.addItem(qsTr("Gradians"), RS.Gradians);
    comboBox.addItem(qsTr("Radians"), RS.Radians);
    comboBox.addItem(qsTr("Surveyor's units"), RS.Surveyors);
};

WidgetFactory.initDimazinCombo = function(comboBox) {
    comboBox.clear();
    comboBox.addItem(qsTr("Show trailing zeroes"), 0);
    comboBox.addItem(qsTr("Suppress leading zeroes") + " " + qsTr("(unsupported)"), 1);
    comboBox.addItem(qsTr("Suppress trailing zeroes"), 2);
    comboBox.addItem(qsTr("Suppress leading / trailing zeroes") + " " + qsTr("(unsupported)"), 3);
};

WidgetFactory.initDimadecCombo = function(comboBox) {
    comboBox.clear();
    comboBox.addItem("0", 0);
    comboBox.addItem("1", 1);
    comboBox.addItem("2", 2);
    comboBox.addItem("3", 3);
    comboBox.addItem("4", 4);
    comboBox.addItem("5", 5);
    comboBox.addItem("6", 6);
    comboBox.addItem("7", 7);
    comboBox.addItem("8", 8);
};


WidgetFactory.initOrientationCombo = function(comboBox) {
    comboBox.clear();

    if (RSettings.isQt(5)) {
        comboBox.addItem("↻ " + qsTr("Clockwise"), RS.CW);
        comboBox.addItem("↺ " + qsTr("Counterclockwise"), RS.CCW);
    }
    else {
        comboBox.addItem(qsTr("Clockwise"), RS.CW);
        comboBox.addItem(qsTr("Counterclockwise"), RS.CCW);
    }
};

WidgetFactory.initArcSymbolTypeCombo = function(comboBox) {
    comboBox.clear();

    comboBox.addItem(qsTr("Preceding"), 0);
    comboBox.addItem(qsTr("Above"), 1);
    comboBox.addItem(qsTr("None"), 2);
};

WidgetFactory.installComboBoxEventFilter = function(widget) {
    if (isNull(widget)) {
        return;
    }
    if (!isQWidget(widget) || !isFunction(widget.children)) {
        return;
    }

    var children = widget.children();
    for ( var i = 0; i < children.length; ++i) {
        var c = children[i];

        if (!c || isDeleted(c)) {
            break;
        }

        if (isOfType(c, QSpinBox) ||
            isOfType(c, QComboBox) ||
            isOfType(c, QFontComboBox) ||
            isOfType(c, RColorCombo) ||
            isOfType(c, RLineweightCombo) ||
            isOfType(c, RLinetypeCombo)) {

            if (isFunction(c.installEventFilter)) {
                c.installEventFilter(new REventFilter(QEvent.Wheel.valueOf(), true));
            }
            c.focusPolicy = Qt.ClickFocus;
            continue;
        }

        WidgetFactory.installComboBoxEventFilter(c);
    }
};
