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

#include "RCommandLinePlugin.h"
#include "RCommandLine.h"

RCommandLinePlugin::RCommandLinePlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RCommandLinePlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RCommandLinePlugin::isInitialized() const {
    return initialized;
}

QWidget *RCommandLinePlugin::createWidget(QWidget *parent) {
    return new RCommandLine(parent);
}

QString RCommandLinePlugin::name() const {
    return "RCommandLine";
}

QString RCommandLinePlugin::group() const {
    return "RCustomWidgets";
}

QIcon RCommandLinePlugin::icon() const {
    return QIcon();
}

QString RCommandLinePlugin::toolTip() const {
    return "";
}

QString RCommandLinePlugin::whatsThis() const {
    return "";
}

bool RCommandLinePlugin::isContainer() const {
    return false;
}

QString RCommandLinePlugin::domXml() const {
    return "<ui language=\"c++\">\n"
        " <widget class=\"RCommandLine\" name=\"commandLine\">\n"
        " </widget>\n"
        "</ui>\n";
}

QString RCommandLinePlugin::includeFile() const {
    return "RCommandLine.h";
}
