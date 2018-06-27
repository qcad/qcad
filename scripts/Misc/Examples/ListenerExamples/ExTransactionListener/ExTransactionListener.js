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

include("../ListenerExamples.js");


/**
 * \ingroup ecma_misc_examples_listenerexamples
 * \class ExTransactionListener
 *
 * This action installs a transaction listener and prints information about
 * transactions into the QCAD command line history.
 */
function ExTransactionListener(guiAction) {
    ListenerExamples.call(this, guiAction);
}

ExTransactionListener.prototype = new ListenerExamples();

ExTransactionListener.prototype.beginEvent = function() {
    // create a new transaction listener:
    var adapter = new RTransactionListenerAdapter();
    var appWin = EAction.getMainWindow();
    appWin.addTransactionListener(adapter);

    // connect transactionUpdated signal to a function that prints
    // information about the transaction:
    adapter.transactionUpdated.connect(function(document, transaction) {
        if (isNull(document) || isNull(transaction)) {
            return;
        }

        var objIds = transaction.getAffectedObjects();
        EAction.handleUserMessage(qsTr("Transaction affected %n object(s).", "", objIds.length));
        if (objIds.length<10) {
            EAction.handleUserMessage("Object IDs: " + objIds.join(','));
        }

        var i, objId;

        // show property changes of first 10 entities:
        for (i=0; i<objIds.length && i<10; i++) {
            objId = objIds[i];

            EAction.handleUserMessage("Changed object ID: " + objId);

            var pre = "&nbsp;&nbsp;&nbsp;";

            var changes = transaction.getPropertyChanges(objId);
            for (var k=0; k<changes.length; k++) {
                var change = changes[k];
                var pid = change.getPropertyTypeId();

                if (pid.isCustom()) {
                    // custom property was changed:
                    EAction.handleUserMessage(pre + "custom property:" + pid.getPropertyTitle(), false);
                }
                else {
                    // other property:
                    // see RObject::Property*, REntity::Property*, RLineEntity::Property*, etc:
                    EAction.handleUserMessage(pre + "property type:" + pid, false);
                }

                EAction.handleUserMessage(pre + "old value:" + change.getOldValue(), false);
                EAction.handleUserMessage(pre + "new value:" + change.getNewValue(), false);
            }
        }

        // show objects that were created or deleted:
        objIds = transaction.getStatusChanges();
        for (i=0; i<objIds.length && i<10; i++) {
            objId = objIds[i];

            var obj = document.queryObjectDirect(objId);
            if (obj.isUndone()) {
                EAction.handleUserMessage("Deleted object with ID: " + objId);
            }
            else {
                EAction.handleUserMessage("Created object with ID: " + objId);
            }

            if (isLayer(obj)) {
                EAction.handleUserMessage("Object is layer");
            }
            else if (isBlock(obj)) {
                EAction.handleUserMessage("Object is block");
            }
            else if (isEntity(obj)) {
                EAction.handleUserMessage("Object is entity");
            }
        }
    });

    EAction.handleUserMessage("ExTransactionListener.js: Transaction listener installed.");
};

/**
 * Adds a menu for this action to the menu.
 */
ExTransactionListener.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Transaction Listener"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ExTransactionListener.js");
    action.setGroupSortOrder(79500);
    action.setSortOrder(100);
    action.setWidgetNames(["ListenerExamplesMenu"]);
};
