/**
 * Copyright (c) 2011-2026 by Andrew Mustun. All rights reserved.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

#ifndef RMACMENUACCESSIBILITY_H
#define RMACMENUACCESSIBILITY_H

#include "gui_global.h"

#include <QString>

/**
 * Spoken titles for the native macOS menu items (VoiceOver).
 *
 * On macOS, RGuiAction appends the key code of a tool to the menu text
 * ("Delete (ER)") and the undo / redo actions show the transaction they
 * undo ("Undo [Draw line]" or "Undo [-]"). VoiceOver reads the title of a
 * menu item literally: "Undo bracket dash bracket paren O O paren".
 *
 * An NSMenuItem can carry an accessibility label that is read instead of
 * its title. This class observes every menu of the application
 * (NSMenuDidAddItemNotification, NSMenuDidChangeItemNotification) and
 * gives each item whose title contains such decorations a spoken form:
 * "Delete, E R", "Undo: Draw line, O O", "Undo, O O". The visible text is
 * not changed. Key codes are spelled letter by letter so that they are not
 * read as words ("er").
 *
 * The same observer keeps menu icons visible on macOS 27 and later, where
 * AppKit hides menu item images unless the item's preferredImageVisibility
 * is set to visible.
 *
 * Installed by RMainWindowQt on macOS.
 */
class QCADGUI_EXPORT RMacMenuAccessibility {
public:
    /**
     * Installs the menu observer (once).
     */
    static void install();

    /**
     * \return Spoken form of the given menu item title, or the title itself
     * if it carries no key code or undo description.
     */
    static QString getSpokenTitle(const QString& title);
};

#endif
