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
#include <QComboBox>

#include "RColorComboPlugin.h"
#include "RColorCombo.h"

RColorComboPlugin::RColorComboPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RColorComboPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RColorComboPlugin::isInitialized() const {
    return initialized;
}

QWidget *RColorComboPlugin::createWidget(QWidget *parent) {
    return new RColorCombo(parent);
}

QString RColorComboPlugin::name() const {
    return "RColorCombo";
}

QString RColorComboPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RColorComboPlugin::icon() const {
    return QIcon();
}

QString RColorComboPlugin::toolTip() const {
    return "";
}

QString RColorComboPlugin::whatsThis() const {
    return "";
}

bool RColorComboPlugin::isContainer() const {
    return false;
}

QString RColorComboPlugin::domXml() const {
    return "\
<ui language=\"c++\"> \
    <widget class=\"RColorCombo\" name=\"colorCombo\"> \
        <property name=\"onlyFixed\" stdset=\"0\"> \
            <bool>false</bool> \
        </property> \
        <property name=\"blackWhite\" stdset=\"1\"> \
            <bool>true</bool> \
        </property> \
        <property name=\"showAlphaChannel\" stdset=\"0\"> \
            <bool>false</bool> \
        </property> \
        <property name=\"color\" stdset=\"\"> \
            <string/> \
        </property> \
    </widget> \
</ui>\n";
}

QString RColorComboPlugin::includeFile() const {
    return "RColorCombo.h";
}
