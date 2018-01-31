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

#include "RGraphicsViewQt.h"
#include "RGraphicsViewQtPlugin.h"

RGraphicsViewQtPlugin::RGraphicsViewQtPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RGraphicsViewQtPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RGraphicsViewQtPlugin::isInitialized() const {
    return initialized;
}

QWidget *RGraphicsViewQtPlugin::createWidget(QWidget *parent) {
    return new RGraphicsViewQt(parent);
}

QString RGraphicsViewQtPlugin::name() const {
    return "RGraphicsViewQt";
}

QString RGraphicsViewQtPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RGraphicsViewQtPlugin::icon() const {
    return QIcon();
}

QString RGraphicsViewQtPlugin::toolTip() const {
    return "";
}

QString RGraphicsViewQtPlugin::whatsThis() const {
    return "";
}

bool RGraphicsViewQtPlugin::isContainer() const {
    return false;
}

QString RGraphicsViewQtPlugin::domXml() const {
    return "<ui language=\"c++\">\n"
        " <widget class=\"RGraphicsViewQt\" name=\"graphicsView\">\n"
        " </widget>\n"
        "</ui>\n";
}

QString RGraphicsViewQtPlugin::includeFile() const {
    return "RGraphicsViewQt.h";
}
