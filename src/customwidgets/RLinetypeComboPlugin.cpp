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

#include "RLinetypeComboPlugin.h"
#include "RLinetypeCombo.h"

RLinetypeComboPlugin::RLinetypeComboPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RLinetypeComboPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RLinetypeComboPlugin::isInitialized() const {
    return initialized;
}

QWidget *RLinetypeComboPlugin::createWidget(QWidget *parent) {
    return new RLinetypeCombo(parent);
}

QString RLinetypeComboPlugin::name() const {
    return "RLinetypeCombo";
}

QString RLinetypeComboPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RLinetypeComboPlugin::icon() const {
    return QIcon();
}

QString RLinetypeComboPlugin::toolTip() const {
    return "";
}

QString RLinetypeComboPlugin::whatsThis() const {
    return "";
}

bool RLinetypeComboPlugin::isContainer() const {
    return false;
}

QString RLinetypeComboPlugin::domXml() const {
    return "<ui language=\"c++\"> \
        <widget class=\"RLinetypeCombo\" name=\"linetypeCombo\"> \
            <property name=\"onlyFixed\" stdset=\"0\"> \
                <bool>false</bool> \
            </property> \
        </widget> \
    </ui>\n";
}

QString RLinetypeComboPlugin::includeFile() const {
    return "RLinetypeCombo.h";
}
