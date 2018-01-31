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

#include "RTextEdit.h"
#include "RTextEditPlugin.h"

RTextEditPlugin::RTextEditPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RTextEditPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RTextEditPlugin::isInitialized() const {
    return initialized;
}

QWidget *RTextEditPlugin::createWidget(QWidget *parent) {
    return new RTextEdit(parent);
}

QString RTextEditPlugin::name() const {
    return "RTextEdit";
}

QString RTextEditPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RTextEditPlugin::icon() const {
    return QIcon();
}

QString RTextEditPlugin::toolTip() const {
    return "";
}

QString RTextEditPlugin::whatsThis() const {
    return "";
}

bool RTextEditPlugin::isContainer() const {
    return false;
}

QString RTextEditPlugin::domXml() const {
    return "<ui language=\"c++\">\n"
        " <widget class=\"RTextEdit\" name=\"textEdit\">\n"
        " </widget>\n"
        "</ui>\n";
}

QString RTextEditPlugin::includeFile() const {
    return "RTextEdit.h";
}
