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
#include <QListView>

#include "RListViewPlugin.h"
#include "RListView.h"

RListViewPlugin::RListViewPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RListViewPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RListViewPlugin::isInitialized() const {
    return initialized;
}

QWidget *RListViewPlugin::createWidget(QWidget *parent) {
    // Return a new instance of your widget here.
    return new RListView(parent);
}

QString RListViewPlugin::name() const {
    // Change the value to return a suitable name.
    return "RListView";
}

QString RListViewPlugin::group() const {
    // The group where the plugins is shown in Designer.
    return "RCustomWidgets";
}

QIcon RListViewPlugin::icon() const {
    // If you want to have a own icon shown in Designer,
    // provide it here.
    return QIcon();
}

QString RListViewPlugin::toolTip() const {
    return "";
}

QString RListViewPlugin::whatsThis() const {
    return "";
}

bool RListViewPlugin::isContainer() const {
    return false;
}

QString RListViewPlugin::domXml() const {
    // Change the class and the default object name here.
    // Note: If your plugin has properties, they must be defined here.
    // See RColorComboPlugin.cpp and RColorCombo.h for an example.
    return "\
<ui language=\"c++\"> \
    <widget class=\"RListView\" name=\"listView\"> \
    </widget> \
</ui>\n";
}

QString RListViewPlugin::includeFile() const {
    // Return the header file of your class here.
    return "RListView.h";
}
