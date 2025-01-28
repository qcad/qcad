/**
 * Copyright (c) 2011-2024 by Andrew Mustun. All rights reserved.
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
#include "RComboBoxPlugin.h"
#include "RComboBox.h"

RComboBoxPlugin::RComboBoxPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RComboBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RComboBoxPlugin::isInitialized() const {
    return initialized;
}

QWidget *RComboBoxPlugin::createWidget(QWidget *parent) {
    return new RComboBox(parent);
}

QString RComboBoxPlugin::name() const {
    return "RComboBox";
}

QString RComboBoxPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RComboBoxPlugin::icon() const {
    return QIcon();
}

QString RComboBoxPlugin::toolTip() const {
    return "";
}

QString RComboBoxPlugin::whatsThis() const {
    return "";
}

bool RComboBoxPlugin::isContainer() const {
    return false;
}

QString RComboBoxPlugin::domXml() const {
    return "\
<ui language=\"c++\"> \
    <widget class=\"RComboBox\" name=\"combo\"> \
    </widget> \
</ui>\n";
}

QString RComboBoxPlugin::includeFile() const {
    return "RComboBox.h";
}
