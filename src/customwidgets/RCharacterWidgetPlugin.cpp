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

#include "RCharacterWidget.h"
#include "RCharacterWidgetPlugin.h"

RCharacterWidgetPlugin::RCharacterWidgetPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RCharacterWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RCharacterWidgetPlugin::isInitialized() const {
    return initialized;
}

QWidget *RCharacterWidgetPlugin::createWidget(QWidget *parent) {
    return new RCharacterWidget(parent);
}

QString RCharacterWidgetPlugin::name() const {
    return "RCharacterWidget";
}

QString RCharacterWidgetPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RCharacterWidgetPlugin::icon() const {
    return QIcon();
}

QString RCharacterWidgetPlugin::toolTip() const {
    return "";
}

QString RCharacterWidgetPlugin::whatsThis() const {
    return "";
}

bool RCharacterWidgetPlugin::isContainer() const {
    return false;
}

QString RCharacterWidgetPlugin::domXml() const {
    return "<ui language=\"c++\">\n"
        " <widget class=\"RCharacterWidget\" name=\"characterWidget\">\n"
        " </widget>\n"
        "</ui>\n";
}

QString RCharacterWidgetPlugin::includeFile() const {
    return "RCharacterWidget.h";
}
