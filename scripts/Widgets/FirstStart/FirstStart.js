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

include("scripts/Edit/AppPreferences/LanguagePreferences/LanguagePreferences.js");
include("scripts/Edit/AppPreferences/InputPreferences/InputPreferences.js");
include("scripts/Edit/DrawingPreferences/UnitSettings/UnitSettings.js");
include("scripts/Edit/DrawingPreferences/PageSettings/PageSettings.js");
include("scripts/sprintf.js");

function FirstStart() {
}

FirstStart.prototype.showDialog = function() {
    var code;
    
    this.path = autoPath("scripts/Widgets/FirstStart");
    this.dialog = WidgetFactory.createWidget(this.path, "FirstStartDialog.ui", null);

    var pathFi = new QFileInfo(this.path);
    this.dialog.windowTitle = qsTr("%1 First Start").arg(qApp.applicationName);
    if (qApp.applicationName.contains("QCAD")) {
        if (RSettings.hasDarkGuiBackground()) {
            this.dialog.styleSheet =
                 "QDialog { border-image: url(" + pathFi.absoluteFilePath() + "/firststart-inverse.jpg) 0 0 0 0 stretch stretch; border-width: 0px; }";
        }
        else {
            this.dialog.styleSheet =
                 "QDialog { border-image: url(" + pathFi.absoluteFilePath() + "/firststart.jpg) 0 0 0 0 stretch stretch; border-width: 0px; }";
                //"QDialog{ background-image: url(" + pathFi.absoluteFilePath() + "/firststart.png) }";
        }

    }
    else {
        this.dialog.findChild("LanguageBackground").styleSheet = "";
        this.dialog.findChild("Background").styleSheet = "";
        this.dialog.findChild("Left").minimumSize = 0;
    }

    this.widgets = getWidgets(this.dialog);

    // language combo
    var langCombo = this.widgets["Language"];
    langCombo.addItem("English", "en");
    var codes = LanguagePreferences.getLanguages();
    for ( var i = 0; i < codes.length; ++i) {
        code = codes[i];
        langCombo.addItem(LanguagePreferences.codeToString(code), code);
    }

    // try to set the locale from system
    var systemLocale = QLocale.system().name();
    var flags = new Qt.MatchFlags(Qt.MatchExactly);
    var index = langCombo.findData(systemLocale, Qt.UserRole, flags);
    if (index == -1) {
        var re = new RegExp("(.+)_(.+)", "i");
        var found = systemLocale.match(re);
        var lang;
        if (isNull(found) || found.length < 2) {
            lang = "en";
        } else {
            lang = found[1];
        }
        flags = new Qt.MatchFlags(Qt.MatchContains);
        index = langCombo.findData(lang, Qt.UserRole, flags);
    }
    if (index != -1) {
        langCombo.setCurrentIndex(index);
    }
    code = langCombo.itemData(langCombo.currentIndex);
    langCombo.model().sort(0);
    langCombo["currentIndexChanged(int)"].connect(this, function(index) {
        var code = langCombo.itemData(index);
        this.changeLanguage(code);
    });

    this.translators = [];
    this.changeLanguage(code);

    if (QCoreApplication.arguments().contains("-no-initial-dialog") || this.dialog.exec()) {
        // save settings

        // language:
        RSettings.setValue("Language/UiLanguage", langCombo.itemData(langCombo.currentIndex));

        // drawing unit and related settings:
        var drawingUnit = this.widgets["Unit"].currentIndex;
        RSettings.setValue("UnitSettings/Unit", drawingUnit);

        // adjust default dimension settings:
        var dimtxt = 2.5;
        if (drawingUnit===RS.Inch) {
            dimtxt = 1/8;
            RSettings.setValue("DimensionSettings/LinearFormat", RS.Engineering);
        }
        if (drawingUnit===RS.Foot) {
            dimtxt = 1/12;
        }
        RSettings.setValue("DimensionSettings/DIMTXT", dimtxt);
        RSettings.setValue("DimensionSettings/DIMEXE", dimtxt/2);
        RSettings.setValue("DimensionSettings/DIMEXO", dimtxt/4);
        RSettings.setValue("DimensionSettings/DIMGAP", dimtxt/4);
        RSettings.setValue("DimensionSettings/DIMASZ", dimtxt);
        RSettings.setValue("DimensionSettings/DIMDLI", dimtxt*2);

        var paperUnit;
        if (!RUnit.isMetric(drawingUnit)) {
            paperUnit = RS.Inch;
            RSettings.setValue("UnitSettings/Measurement", RS.Imperial);
        }
        else {
            paperUnit = RS.Millimeter;
            RSettings.setValue("UnitSettings/Measurement", RS.Metric);
        }
        RSettings.setValue("UnitSettings/PaperUnit", paperUnit);

        var dps = this.widgets["DefaultPaperSize"];

        var paperSizeName = dps.currentText;
        if (isNull(paperSizeName)) {
            paperSizeName = "";
        }
        RSettings.setValue("PageSettings/PaperSizeName", paperSizeName);

        //var paperSizeEnum = dps.itemData(dps.currentIndex, Qt.UserRole);
        //RSettings.setValue("PageSettings/PaperSizeEnum", paperSizeEnum);

        var paperSize = dps.itemData(dps.currentIndex, Qt.UserRole + 1);
        if (!isNull(paperSize)) {
            RSettings.setValue("PageSettings/PaperWidth", RUnit.convert(paperSize.width(), RS.Millimeter, paperUnit));
            RSettings.setValue("PageSettings/PaperHeight", RUnit.convert(paperSize.height(), RS.Millimeter, paperUnit));
        }

        // adjust page margins to paper unit:
        var margin = RUnit.convert(10.0, RS.Millimeter, paperUnit);
        if (paperUnit == RS.Inch) {
            margin = 0.5;
        }

        RSettings.setValue("MultiPageSettings/GlueMarginsLeft", margin);
        RSettings.setValue("MultiPageSettings/GlueMarginsTop", margin);
        RSettings.setValue("MultiPageSettings/GlueMarginsBottom", margin);
        RSettings.setValue("MultiPageSettings/GlueMarginsRight", margin);

        var dpCombo = this.widgets["DecimalPoint"];
        var dp = dpCombo.itemData(dpCombo.currentIndex);
        RSettings.setValue("Input/DecimalPoint", dp);
        if (dp===",") {
            RSettings.setValue("Input/CartesianCoordinateSeparator", ";");
        }
        var bgClrCombo = this.widgets["BackgroundColor"];
        var bgClr = bgClrCombo.itemData(bgClrCombo.currentIndex);
        RSettings.setValue("GraphicsViewColors/BackgroundColor", bgClr);
        if (bgClrCombo.currentIndex===1) {
            RSettings.setValue("GraphicsViewColors/CrosshairColor", new RColor(178,129,0,192));
            RSettings.setValue("GraphicsViewColors/TextLabelColor", new RColor(178,129,0));
        }
        var settings = RSettings.getQSettings();
        settings.sync();
    }

    this.dialog.destroy();
    EAction.activateMainWindow();
};

FirstStart.prototype.changeLanguage = function(code) {
    var i;
    for (i = 0; i < this.translators.length; ++i) {
        QCoreApplication.removeTranslator(this.translators[i]);
    }
    
    if (code !== "en") {
        var translators = [
            [ "scripts", "ts" ],
            [ "scripts", ":/ts" ]
        ];

        for (i=0; i<translators.length; i++) {
            var translator = new QTranslator(qApp);
            if (translator.load(translators[i][0] + "_" + code, translators[i][1])) {
                QCoreApplication.installTranslator(translator);
                this.translators.push(translator);
            }
            else {
                qDebug("FirstStart.js: cannot load translation for module: " + translators[i][0] + " / language " + code);
            }
        }
    }

    var locale = new QLocale(code);
    QLocale.setDefault(locale);
    this.retranslateStrings();

    // unit combo
    UnitSettings.initUnitCombo(this.widgets["Unit"]);
    var systemLocale = QLocale.system();
    var msys = systemLocale.measurementSystem();
    if (msys.valueOf() != QLocale.MetricSystem.valueOf()) {
        // imperial system:
        this.widgets["Unit"].currentIndex = 1;
    } else {
        // metrics system (fall back):
        this.widgets["Unit"].currentIndex = 4;
    }

    // paper size combo
    var paperSizeCombo = this.widgets["DefaultPaperSize"];
    PageSettings.initPaperSizeNameCombo(paperSizeCombo);

    // default paper size
    var paperSizeOverride = qApp.property("FirstStartPaperSizeOverride");
    var index = paperSizeCombo.findText(paperSizeOverride);
    if (index===-1) {
        var defaultPrinter = new QPrinter();
        var paperSize = defaultPrinter.paperSize(QPrinter.Millimeter);
        defaultPrinter.destroy();
        index = paperSizeCombo.findData(paperSize, Qt.UserRole + 1);
        if (index===-1) {
            index = paperSizeCombo.findText("ISO A4");
        }
    }
    if (index===-1) {
        index = 0;
    }
    paperSizeCombo.currentIndex = index;

    // decimal point combo
    var dpCombo = this.widgets["DecimalPoint"];
    InputPreferences.updateDecimalPointCombo(dpCombo);
    var dp = sprintf("%c", systemLocale.decimalPoint());
    for (i = 0; i < dpCombo.count; ++i) {
        var data = dpCombo.itemData(i);
        if (dp == data) {
            dpCombo.currentIndex = i;
        }
    }

    // background color combo
    var bgClrCombo = this.widgets["BackgroundColor"];
    bgClrCombo.clear();
    bgClrCombo.addItem(qsTr("Black"), new RColor("black"));
    bgClrCombo.addItem(qsTr("White"), new RColor("white"));
};

FirstStart.prototype.retranslateStrings = function() {
    this.dialog.windowTitle = qsTr("%1 First Start").arg(qApp.applicationName);
    this.widgets["LanguageLabel"].text = qsTr("Language:");
    var title = qsTr("Welcome to %1").arg(qApp.applicationName);
    var text = qsTr("Please choose the settings used for new drawings. "
            + "All these settings can be changed later in the Preference Dialog.");
    this.widgets["Text"].html = "<html><head><meta name=\"qrichtext\" content=\"1\" />"
            + "<style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head>"
            + "<body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">"
            + "\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
            + "<span style=\" font-weight:600;\">"
            + title
            + "</span></p>"
            + "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>"
            + "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
            + text
            + "</p><p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>"
            + "</body></html>";
    this.widgets["UnitLabel"].text = qsTr("Unit:");
    this.widgets["DefaultPaperSizeLabel"].text = qsTr("Default Paper Size:");
    this.widgets["DecimalPointLabel"].text = qsTr("Decimal Point:");
    this.widgets["BackgroundColorLabel"].text = qsTr("Background Color:");
};
