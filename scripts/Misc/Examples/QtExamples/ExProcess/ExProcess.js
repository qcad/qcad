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

include("../QtExamples.js");

/**
 * \ingroup ecma_misc_examples_qtexamples
 * \class ExProcess
 * This action runs an external process
 */
function ExProcess(guiAction) {
    QtExamples.call(this, guiAction);
}

ExProcess.prototype = new QtExamples();
ExProcess.includeBasePath = includeBasePath;

ExProcess.prototype.beginEvent = function() {
    QtExamples.prototype.beginEvent.call(this);

    // application binary:
    var program = "ls";
    // arguments:
    var args = [ "-la" ];
    // additional environment variables:
    var environment = [ ["MYENVVAR", 1] ];

    var process = new QProcess();

    // error handling:
    process.error.connect(function(e) { qDebug("Error: ", e); });

    // buffer stdout, stderr for later output:
    var stdout = "";
    var stderr = "";
    process.readyReadStandardOutput.connect(function() { stdout += process.readAllStandardOutput(); });
    process.readyReadStandardError.connect(function() { stderr += process.readAllStandardError(); });

    // set enviromnet to current environment, add custom environment:
    if (environment!==undefined) {
        var env = QProcessEnvironment.systemEnvironment();
        for (var i=0; i<environment.length; i++) {
            env.insert(environment[i][0], environment[i][1]);
        }
        process.setProcessEnvironment(env);
    }

    // start process:
    process.start(program, args);

    // wait for process to finish:
    process.waitForFinished(-1);   // no timeout

    // output buffered stdout, stderr:
    qDebug(stdout);
    qDebug(stderr);

    this.terminate();
};

/**
 * Adds a menu for this action to Examples/Math Examples/ExProcess.
 */
ExProcess.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Run Process"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ExProcess.js");
    action.setGroupSortOrder(79600);
    action.setSortOrder(300);
    action.setWidgetNames(["QtExamplesMenu"]);
};
