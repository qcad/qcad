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

#ifndef RMACMODALMENUGUARD_H
#define RMACMODALMENUGUARD_H

#include "gui_global.h"

/**
 * Keeps the key equivalents of the native menu bar from reaching the
 * application while a native modal panel (open / save file dialog, ...)
 * is shown (macOS only).
 *
 * AppKit dispatches key equivalents to the menu bar even when the key
 * window is a native panel. Qt's menu items validate as enabled in that
 * case and the QCAD action is triggered behind the panel: Cmd-Left /
 * Cmd-Right typed into the file name field of the save dialog switch the
 * current document (the following save then overwrites the wrong
 * document), Cmd-A runs Select All on the drawing instead of selecting
 * the file name, etc.
 *
 * While a native modal panel is the key window, menu items of the
 * application are disabled, except for the standard editing shortcuts
 * (Cmd-X, Cmd-C, Cmd-V, Cmd-A, Cmd-Z, Shift-Cmd-Z) which are forwarded to
 * the responder chain of the panel (cut:, copy:, paste:, selectAll:, undo:,
 * redo:), as in any native application. Other key strokes fall through
 * to the panel (e.g. Cmd-Left / Cmd-Right move the cursor in the file
 * name field).
 *
 * \ingroup gui
 */
class QCADGUI_EXPORT RMacModalMenuGuard {
public:
    /**
     * Installs the guard (once). No-op if the Cocoa platform plugin is
     * not in use.
     */
    static void install();

    /**
     * \return True if a native (non Qt) modal panel is the key window.
     */
    static bool isNativeModalPanelActive();
};

#endif
