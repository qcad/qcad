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

Kms.schemeDir = "scripts/Edit/AppPreferences/ShortcutPreferences/Schemas";

/**
 * \brief Represents a key code scheme configuration file (.kms).
 */
function Kms(schemeName) {
    var item, index, model, value, subquery, subri, subitem;
    
    var fi = new QFileInfo(Kms.getKmsFile(schemeName));
    if (!fi.isFile()) {
        this.valid = false;
        return;
    }

    this.valid = true;

    this.scMap = new Array();
    this.cmdMap = new Array();

    var query = new QXmlQuery();
    var file = fi.absoluteFilePath();
    query.setQuery("doc('file://" + file + "')/mapping/shortcut/@id");
    var ri = new QXmlResultItems();
    query.evaluateTo(ri);
    while (!(item = ri.next()).isNull()) {
        index = item.toNodeModelIndex();
        if (index.isNull()) {
            continue;
        }
        model = index.model();
        var id = model.stringValue(index);
        
        // get keys
        subquery = Kms.xmlQuery;
        // /mapping/shortcut[@id='scripts/File/Open/Open.js']/key/@value
        subquery.setQuery("doc('file://" + file + "')/mapping/shortcut[@id='"
                + id + "']/key/@value");
        subri = new QXmlResultItems();
        subquery.evaluateTo(subri);
        var shortcuts = new Array();
        while (!(subitem = subri.next()).isNull()) {
            index = subitem.toNodeModelIndex();
            if (index.isNull()) {
                continue;
            }
            model = index.model();
            value = model.stringValue(index);
            shortcuts.push(value);
        }
        subri.destroy();
        this.scMap[id] = shortcuts;

        // get commands
        subquery = Kms.xmlQuery;
        // /mapping/shortcut[@id='scripts/File/Open/Open.js']/command/@value
        subquery.setQuery("doc('file://" + file + "')/mapping/shortcut[@id='"
                + id + "']/command/@value");
        subri = new QXmlResultItems();
        subquery.evaluateTo(subri);
        subitem = undefined;
        var commands = new Array();
        while (!(subitem = subri.next()).isNull()) {
            index = subitem.toNodeModelIndex();
            if (index.isNull()) {
                continue;
            }
            model = index.model();
            value = model.stringValue(index);
            commands.push(value);
        }
        subri.destroy();
        this.cmdMap[id] = commands;
    }
    ri.destroy();
}

Kms.xmlQuery = new QXmlQuery();

/**
 * Assigns the appropriate shortcuts from the KMS file to the given action.
 * If no shortcuts are defined in this KMS file, this function does nothing.
 *
 * \return true if key codes from KMS were assigned, false otherwise.
 */
Kms.prototype.bindShortcutsToAction = function(action) {
    if (!this.valid || isNull(action)) {
        return false;
    }
    var ksStrings = this.scMap[action.getScriptFile()];
    var keysequences = Kms.stringArraytoKsArray(ksStrings);
    if (!isNull(ksStrings) /*&& keysequences.length > 0*/) {
        action.setShortcuts(keysequences);
        return true;
    }
    else {
        return false;
    }
};

/**
 * Assigns the appropriate commands from the KMS file to the given action.
 * If no commands are defined in this KMS file, this function does nothing.
 *
 * \return true if commands from KMS were assigned, false otherwise.
 */
Kms.prototype.bindCommandsToAction = function(action) {
    if (!this.valid || isNull(action)) {
        return false;
    }
    var commands = this.cmdMap[action.getScriptFile()];
    if (!isNull(commands)) {
        action.setCommands(commands);
        return true;
    }
    else {
        return false;
    }
};

Kms.prototype.getShortcutMap = function() {
    return this.scMap;
};

Kms.prototype.getCommandMap = function() {
    return this.cmdMap;
};

Kms.loadShortcutsFromSettings = function(action) {
    var ret = RSettings.getValue("Shortcuts/" + action.getScriptFile(), -1);
    // key not found: use default shortcuts
    if (ret===-1) {
        return undefined;
    }
    else {
        // key found, list empty: no shortcuts
        if (isNull(ret)) {
            return [];
        }
        else {
            return ret;
        }
    }
};

Kms.loadCommandsFromSettings = function(action) {
    var ret = RSettings.getValue("Commands/" + action.getScriptFile(), -1);
    // key not found: use default commands
    if (ret===-1) {
        return undefined;
    }
    else {
        // key found, list empty: no commands
        if (isNull(ret)) {
            return [];
        }
        else {
            return ret;
        }
    }
};

Kms.saveToSettings = function(action) {
    RSettings.setValue("Shortcuts/" + action.getScriptFile(), action
            .shortcuts());
    RSettings.setValue("Commands/" + action.getScriptFile(), action
            .getCommands());
};

Kms.removeFromSettings = function(action) {
    RSettings.getQSettings().remove("Shortcuts/" + action.getScriptFile());
    RSettings.getQSettings().remove("Commands/" + action.getScriptFile());
};

Kms.stringArraytoKsArray = function(ksStrings) {
    var keysequences = new Array();
    if (isNull(ksStrings)) {
        return keysequences;
    }

    for ( var i = 0; i < ksStrings.length; ++i) {
        var ks;
        if (ksStrings[i].contains("QKeySequence")) {
            try {
                eval("ks = new QKeySequence(" + ksStrings[i] + ")");
            } catch (e) {
                qWarning("Kms.js:", "stringArraytoKsArray(): exception:", e);
            }
        } else {
            ks = new QKeySequence(ksStrings[i]);
        }
        keysequences.push(ks);
    }
    return keysequences;
};

Kms.getSchemeDirectory = function() {
    return Kms.schemeDir;
};

Kms.getKmsFile = function(schemeName) {
    return Kms.getSchemeDirectory() + QDir.separator + schemeName + ".kms";
};

Kms.getKsListHumanReadable = function(ksList) {
    if (isNull(ksList)) {
        return "";
    }

    var ret = "";
    for (var i=0; i<ksList.length; ++i) {
        ret += ksList[i].toString(QKeySequence.NativeText);
        if (i<ksList.length-1) {
            ret += "\n";
        }
    }

    return ret;

    // does not take platforms into account (ctrl vs command on mac):
    //return new String(ksList.join(" -- "));
};
