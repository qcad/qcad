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

#include "RShortcutLineEdit.h"
#include "RShortcutLineEditPlugin.h"

RShortcutLineEditPlugin::RShortcutLineEditPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RShortcutLineEditPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RShortcutLineEditPlugin::isInitialized() const {
    return initialized;
}

QWidget *RShortcutLineEditPlugin::createWidget(QWidget *parent) {
    return new RShortcutLineEdit(parent);
}

QString RShortcutLineEditPlugin::name() const {
    return "RShortcutLineEdit";
}

QString RShortcutLineEditPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RShortcutLineEditPlugin::icon() const {
    return QIcon();
}

QString RShortcutLineEditPlugin::toolTip() const {
    return "";
}

QString RShortcutLineEditPlugin::whatsThis() const {
    return "";
}

bool RShortcutLineEditPlugin::isContainer() const {
    return false;
}

QString RShortcutLineEditPlugin::domXml() const {
    return
        "<ui language=\"c++\">\n"
        " <widget class=\"RShortcutLineEdit\" name=\"scLineEdit\">\n"
        " </widget>\n"
        "</ui>\n";
}

QString RShortcutLineEditPlugin::includeFile() const {
    return "RShortcutLineEdit.h";
}
