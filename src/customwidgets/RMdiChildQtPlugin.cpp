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

#include "RMdiChildQt.h"
#include "RMdiChildQtPlugin.h"

RMdiChildQtPlugin::RMdiChildQtPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RMdiChildQtPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RMdiChildQtPlugin::isInitialized() const {
    return initialized;
}

QWidget *RMdiChildQtPlugin::createWidget(QWidget *parent) {
    return new RMdiChildQt(parent);
}

QString RMdiChildQtPlugin::name() const {
    return "RMdiChildQt";
}

QString RMdiChildQtPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RMdiChildQtPlugin::icon() const {
    return QIcon();
}

QString RMdiChildQtPlugin::toolTip() const {
    return "";
}

QString RMdiChildQtPlugin::whatsThis() const {
    return "";
}

bool RMdiChildQtPlugin::isContainer() const {
    return true;
}

QString RMdiChildQtPlugin::domXml() const {
    return "<ui language=\"c++\">\n"
        " <widget class=\"RMdiChildQt\" name=\"mdiChild\">\n"
        " </widget>\n"
        "</ui>\n";
}

QString RMdiChildQtPlugin::includeFile() const {
    return "RMdiChildQt.h";
}
