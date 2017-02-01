/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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

#include "RMathLineEdit.h"
#include "RMathLineEditPlugin.h"

RMathLineEditPlugin::RMathLineEditPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RMathLineEditPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RMathLineEditPlugin::isInitialized() const {
    return initialized;
}

QWidget *RMathLineEditPlugin::createWidget(QWidget *parent) {
    return new RMathLineEdit(parent);
}

QString RMathLineEditPlugin::name() const {
    return "RMathLineEdit";
}

QString RMathLineEditPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RMathLineEditPlugin::icon() const {
    return QIcon();
}

QString RMathLineEditPlugin::toolTip() const {
    return "";
}

QString RMathLineEditPlugin::whatsThis() const {
    return "";
}

bool RMathLineEditPlugin::isContainer() const {
    return false;
}

QString RMathLineEditPlugin::domXml() const {
    return
        "<ui language=\"c++\">\n"
        " <widget class=\"RMathLineEdit\" name=\"lineEdit\">\n"
        "   <property name=\"angle\" stdset=\"0\">\n"
        "     <bool>false</bool>\n"
        "   </property>\n"
        "   <property name=\"integer\" stdset=\"0\">\n"
        "     <bool>false</bool>\n"
        "   </property>\n"
        "   <property name=\"defaultUnit\">\n"
        "     <number>0</number>\n"
        "   </property>\n"
        " </widget>\n"
        "</ui>\n";
}

QString RMathLineEditPlugin::includeFile() const {
    return "RMathLineEdit.h";
}
