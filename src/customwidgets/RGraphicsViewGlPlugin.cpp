/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

#include "RGraphicsViewGl.h"
#include "RGraphicsViewGlPlugin.h"

RGraphicsViewGlPlugin::RGraphicsViewGlPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RGraphicsViewGlPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RGraphicsViewGlPlugin::isInitialized() const {
    return initialized;
}

QWidget *RGraphicsViewGlPlugin::createWidget(QWidget *parent) {
    return new RGraphicsViewGl(parent);
}

QString RGraphicsViewGlPlugin::name() const {
    return "RGraphicsViewGl";
}

QString RGraphicsViewGlPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RGraphicsViewGlPlugin::icon() const {
    return QIcon();
}

QString RGraphicsViewGlPlugin::toolTip() const {
    return "";
}

QString RGraphicsViewGlPlugin::whatsThis() const {
    return "";
}

bool RGraphicsViewGlPlugin::isContainer() const {
    return false;
}

QString RGraphicsViewGlPlugin::domXml() const {
    return "<ui language=\"c++\">\n"
        " <widget class=\"RGraphicsViewGl\" name=\"graphicsView\">\n"
        " </widget>\n"
        "</ui>\n";
}

QString RGraphicsViewGlPlugin::includeFile() const {
    return "RGraphicsViewGl.h";
}
