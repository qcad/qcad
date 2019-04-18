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
#include <QtPlugin>

#include "RMathComboBox.h"
#include "RMathComboBoxPlugin.h"

RMathComboBoxPlugin::RMathComboBoxPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RMathComboBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RMathComboBoxPlugin::isInitialized() const {
    return initialized;
}

QWidget *RMathComboBoxPlugin::createWidget(QWidget *parent) {
    return new RMathComboBox(parent);
}

QString RMathComboBoxPlugin::name() const {
    return "RMathComboBox";
}

QString RMathComboBoxPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RMathComboBoxPlugin::icon() const {
    return QIcon();
}

QString RMathComboBoxPlugin::toolTip() const {
    return "";
}

QString RMathComboBoxPlugin::whatsThis() const {
    return "";
}

bool RMathComboBoxPlugin::isContainer() const {
    return false;
}

QString RMathComboBoxPlugin::domXml() const {
    return
        "<ui language=\"c++\">\n"
        " <widget class=\"RMathComboBox\" name=\"comboBox\">\n"
        "   <property name=\"angle\" stdset=\"0\">\n"
        "     <bool>false</bool>\n"
        "   </property>\n"
        "   <property name=\"integer\" stdset=\"0\">\n"
        "     <bool>false</bool>\n"
        "   </property>\n"
        " </widget>\n"
        "</ui>\n";
}

QString RMathComboBoxPlugin::includeFile() const {
    return "RMathComboBox.h";
}
