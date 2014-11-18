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

include("../../WidgetFactory.js");

function ProgressBar() {
    ProgressBar.formWidget = undefined;
    ProgressBar.progressBar = undefined;
}

/**
 * Disabled for now. Does not update without calling processEvents which
 * causes problems.
 */
ProgressBar.init = function(basePath) {
    ProgressBar.formWidget = WidgetFactory.createWidget(basePath, "ProgressBar.ui");
    ProgressBar.progressBar = ProgressBar.formWidget.findChild("ProgressBar");
    ProgressBar.progressBar.visible = false;
//    ProgressBar.cancel = ProgressBar.formWidget.findChild("btCancel");
//    // ProgressBar.cancel.mouseTracking = true;
//    ProgressBar.cancel.cursor = new QCursor(Qt.ArrowCursor);
//    ProgressBar.cancel.visible = false;
//    ProgressBar.cancel.clicked.connect(function() {
//        appWin.cancelProgress();
//    });
    var appWin = EAction.getMainWindow();
    appWin.progress.connect(this, "progress");
    appWin.progressEnd.connect(this, "progressEnd");
    appWin.progressText.connect(this, "progressText");
    EAction.addToStatusBar(ProgressBar.formWidget, 1000);
};

//ProgressBar.progressStart = function(allowCancel) {
//    if (isNull(ProgressBar.formWidget)) {
//        return;
//    }
////    if (allowCancel == undefined) {
////        allowCancel = false;
////    }
    
////    ProgressBar.allowCancel = allowCancel;
////    if (ProgressBar.allowCancel) {
////        ProgressBar.formWidget = objectFromPath("MainWindow::ProgressBarForm",
////                ProgressBar.formWidget);
////        ProgressBar.cancel = ProgressBar.formWidget.findChild("btCancel");
////        if (!QCoreApplication.arguments().contains("-no-show")) {
////            ProgressBar.cancel.visible = true;
////        }
////    }

//    ProgressBar.progress(0);
//    //ProgressBar.formWidget.repaint();
//};

ProgressBar.progress = function(value) {
    if (isNull(ProgressBar.formWidget)) {
        return;
    }

    ProgressBar.progressBar = objectFromPath("MainWindow::ProgressBar",
            ProgressBar.progressBar);
    if (!QCoreApplication.arguments().contains("-no-show")) {
        ProgressBar.progressBar.visible = true;
    }
    ProgressBar.progressBar.value = value;

    var appWin = EAction.getMainWindow();
    appWin.enabled = false;
};

ProgressBar.progressEnd = function() {
    if (isNull(ProgressBar.formWidget)) {
        return;
    }

    ProgressBar.progressBar = objectFromPath("MainWindow::ProgressBar", ProgressBar.progressBar);
    ProgressBar.progressBar.reset();
    ProgressBar.progressText("");
    ProgressBar.progressBar.visible = false;
    //ProgressBar.cancel.visible = false;
    var appWin = EAction.getMainWindow();
    appWin.enabled = true;
};

ProgressBar.progressText = function(text) {
    var lb = objectFromPath("MainWindow::ProgressText");
    if (!isNull(lb)) {
        lb.text = text;
    }
};
