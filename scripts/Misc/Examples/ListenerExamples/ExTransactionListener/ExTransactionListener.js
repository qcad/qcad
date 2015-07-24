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

include("../ListenerExamples.js");


/**
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
        EAction.handleUserMessage("Transaction affected %1 objects.".arg(objIds.length));
        if (objIds.length<50) {
            EAction.handleUserMessage("Object IDs: " + objIds.join(','));
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
