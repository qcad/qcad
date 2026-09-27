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

#ifndef RCOLORDIALOG_H_
#define RCOLORDIALOG_H_

#include "gui_global.h"

#include <QString>

/**
 * Persistence of the custom colors of the Qt color dialog (QColorDialog).
 *
 * Qt only remembers the custom colors a user adds to the palette of the
 * color dialog for the duration of the program run. loadCustomColors()
 * restores them from the settings (QCAD3.ini), saveCustomColors() stores
 * them back. All color dialogs of the application share the same custom
 * colors.
 *
 * \ingroup gui
 */
class QCADGUI_EXPORT RColorDialog {
public:
    static void loadCustomColors();
    static void saveCustomColors();

private:
    static const QString settingsKey;
    static bool loaded;
};

#endif /* RCOLORDIALOG_H_ */
