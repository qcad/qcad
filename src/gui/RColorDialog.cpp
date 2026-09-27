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
#include <QColor>
#include <QColorDialog>
#include <QStringList>

#include "RColorDialog.h"
#include "RSettings.h"

const QString RColorDialog::settingsKey = "ColorDialog/CustomColors";
bool RColorDialog::loaded = false;

/**
 * Restores the custom colors of the color dialog from the settings.
 * Called once at application startup, before any color dialog is shown.
 */
void RColorDialog::loadCustomColors() {
    QStringList names = RSettings::getStringListValue(settingsKey, QStringList());

    int c = QColorDialog::customCount();
    for (int i=0; i<names.length() && i<c; i++) {
        QColor color(names.at(i).trimmed());
        if (!color.isValid()) {
            continue;
        }
        QColorDialog::setCustomColor(i, color);
    }

    loaded = true;
}

/**
 * Stores the custom colors of the color dialog in the settings.
 * Called whenever a color dialog was closed and at application shutdown.
 */
void RColorDialog::saveCustomColors() {
    if (!loaded) {
        // custom colors were never restored (e.g. -no-gui):
        // don't overwrite the stored colors with Qt's defaults:
        return;
    }

    QStringList names;
    int c = QColorDialog::customCount();
    for (int i=0; i<c; i++) {
        names.append(QColorDialog::customColor(i).name(QColor::HexArgb));
    }

    if (names==RSettings::getStringListValue(settingsKey, QStringList())) {
        // unchanged:
        return;
    }

    RSettings::setValue(settingsKey, names);
}
