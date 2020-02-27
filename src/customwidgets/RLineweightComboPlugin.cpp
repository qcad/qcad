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

#include "RLineweightComboPlugin.h"
#include "RLineweightCombo.h"

RLineweightComboPlugin::RLineweightComboPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RLineweightComboPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RLineweightComboPlugin::isInitialized() const {
    return initialized;
}

QWidget *RLineweightComboPlugin::createWidget(QWidget *parent) {
    return new RLineweightCombo(parent);
}

QString RLineweightComboPlugin::name() const {
    return "RLineweightCombo";
}

QString RLineweightComboPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RLineweightComboPlugin::icon() const {
    return QIcon();
}

QString RLineweightComboPlugin::toolTip() const {
    return "";
}

QString RLineweightComboPlugin::whatsThis() const {
    return "";
}

bool RLineweightComboPlugin::isContainer() const {
    return false;
}

QString RLineweightComboPlugin::domXml() const {
    return "<ui language=\"c++\"> \
        <widget class=\"RLineweightCombo\" name=\"lineweightCombo\"> \
            <property name=\"onlyFixed\" stdset=\"0\"> \
                <bool>false</bool> \
            </property> \
            <property name=\"noDefault\" stdset=\"0\"> \
                <bool>false</bool> \
            </property> \
        </widget> \
    </ui>\n";
}

QString RLineweightComboPlugin::includeFile() const {
    return "RLineweightCombo.h";
}
