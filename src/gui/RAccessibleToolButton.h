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

#ifndef RACCESSIBLETOOLBUTTON_H
#define RACCESSIBLETOOLBUTTON_H

#include "gui_global.h"

/**
 * Accessibility implementation for tool buttons that represent an action
 * (tool buttons of tool bars, of the CAD tool bar and of tool button
 * panels).
 *
 * Every tool of QCAD is an RGuiAction and every RGuiAction is checkable,
 * since a tool button stays checked while its tool is running. Qt derives
 * the accessible role of a button from exactly that property: a checkable
 * button that is not auto exclusive is reported as QAccessible::CheckBox
 * (QAccessibleButton::role()), and a check box offers the accessible
 * actions "Toggle" and "Press", in that order.
 *
 * On macOS, both actions are mapped to AXPress by the Cocoa plugin and
 * the first one wins, so a screen reader that presses a tool button
 * (VoiceOver: Control+Option+Space) ends up in
 * QAccessibleButton::doAction("Toggle"), which calls
 * QAbstractButton::toggle(). That sets the checked state of the button
 * directly, bypassing QToolButton::nextCheckState() and therefore the
 * default action of the button: the button appears checked, but the tool
 * is never started.
 *
 * Tool buttons with a default action are therefore exposed as:
 *
 * - QAccessible::Button (not CheckBox), since starting a tool is a
 *   command and not an on/off setting. The checkable / checked state is
 *   kept, so the running tool is still reported (AXValue).
 *   Actions that really toggle something (RGuiAction::isToggleable())
 *   keep the check box role.
 * - a single "Press" action that goes through QAbstractButton::click(),
 *   i.e. through exactly the same code path as a mouse click.
 *
 * \ingroup gui
 */
class QCADGUI_EXPORT RAccessibleToolButton {
public:
    /**
     * Installs the accessibility factory (once). Called by RMainWindowQt.
     */
    static void install();

private:
    static bool installed;
};

#endif
