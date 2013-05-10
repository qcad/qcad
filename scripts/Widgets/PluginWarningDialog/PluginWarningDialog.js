/*
 * Copyright (c) 2013 by RibbonSoft, GmbH. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * Licensees holding valid QCAD Professional Edition licenses 
 * may use this file in accordance with the QCAD License
 * Agreement provided with the Software.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, 
 * INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE.
 * 
 * See http://www.ribbonsoft.com for further details.
 */

include("scripts/EAction.js");

/**
 * \class PluginWarningDialog
 * \brief Shows a warning that is plugin specific and optionally tool specific
 *  and identifies the warning accordingly.
 */
function PluginWarningDialog(guiAction) {
    EAction.call(this, guiAction);

    if (!isNull(guiAction)) {
        this.plugin = guiAction["Plugin"];
        if (isNull(this.plugin)) {
            this.plugin = qsTr("Unknown");
        }
        this.tool = guiAction["Tool"];
        if (isNull(this.tool)) {
            this.tool = "";
        }
    }
}

PluginWarningDialog.prototype = new EAction();

/**
 * Overwrite in implementations to provide a list of strings to display.
 * The first string in the list is the dialog title.
 * %1 is replaced by the plugin name
 * %2 is replaced by the tool name
 */
PluginWarningDialog.prototype.getStrings = function() {
    return [];
};

PluginWarningDialog.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);
    var appWin = EAction.getMainWindow();

    var str = this.getStrings();

    var s = str.slice(1).join("<br/>").arg(this.plugin).arg(this.tool);

    var commandLineDock = appWin.findChild("CommandLineDock");

    if (RSettings.getBoolValue("PluginWarningDialog/DontShow", false)===true &&
        commandLineDock.visible) {

        EAction.handleUserMessage(s);
    }
    else {
        var dlg = WidgetFactory.createDialog(":scripts/Widgets/PluginWarningDialog", "PluginWarningDialog.ui", appWin);
        dlg.windowTitle = str[0];
        var label = dlg.findChild("Text");
        label.text = s;
        WidgetFactory.restoreState(dlg);
        dlg.exec();
        WidgetFactory.saveState(dlg);
    }

    this.terminate();
};


