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

#include "RFontChooserWidgetPlugin.h"
#include "RFontChooserWidget.h"

RFontChooserWidgetPlugin::RFontChooserWidgetPlugin(QObject *parent) :
    QObject(parent) {
    initialized = false;
}

void RFontChooserWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (initialized) {
        return;
    }
    initialized = true;
}

bool RFontChooserWidgetPlugin::isInitialized() const {
    return initialized;
}

QWidget *RFontChooserWidgetPlugin::createWidget(QWidget *parent) {
    return new RFontChooserWidget(parent);
}

QString RFontChooserWidgetPlugin::name() const {
    return "RFontChooserWidget";
}

QString RFontChooserWidgetPlugin::group() const {
    return "RCustomWidgets";
}

QIcon RFontChooserWidgetPlugin::icon() const {
    return QIcon();
}

QString RFontChooserWidgetPlugin::toolTip() const {
    return "";
}

QString RFontChooserWidgetPlugin::whatsThis() const {
    return "";
}

bool RFontChooserWidgetPlugin::isContainer() const {
    return false;
}

QString RFontChooserWidgetPlugin::domXml() const {
    return "\
<ui language=\"c++\"> \
    <widget class=\"RFontChooserWidget\" name=\"fontChooser\"> \
        <property name=\"font\" stdset=\"\"> \
            <string/> \
        </property> \
    </widget> \
</ui>\n";
}

QString RFontChooserWidgetPlugin::includeFile() const {
    return "RFontChooserWidget.h";
}
