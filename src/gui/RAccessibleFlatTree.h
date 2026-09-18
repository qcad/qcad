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

#ifndef RACCESSIBLEFLATTREE_H
#define RACCESSIBLEFLATTREE_H

#include "gui_global.h"

/**
 * Alternative accessibility implementation for tree widgets, exposing a
 * tree as a flat list of items to screen readers (e.g. macOS VoiceOver).
 *
 * Qt exposes a QTreeWidget through QAccessibleTable, which does not work
 * with VoiceOver on macOS (Qt 6.12, also in Qt dev):
 *
 * - While the keyboard focus is inside the tree, the application reports
 *   no focused accessibility element at all: creating the element of the
 *   focused cell tears down and rebuilds the accessible interface of the
 *   tree itself, which deletes the cell interface that was just created.
 *   VoiceOver asks what is focused, gets nothing and only beeps.
 * - QAccessible::TreeItem is missing from the role map of the Cocoa
 *   plugin, so items are exposed as plain groups, and a group is not
 *   covered by QCocoaAccessible::hasValueAttribute(), so an item has no
 *   value a screen reader could read.
 * - The Cocoa plugin does not implement accessibilitySelectedRows for
 *   the synthesized table rows, so VoiceOver cannot track the selection.
 *
 * A tree that opts in (see propertyName()) is therefore exposed as a
 * QAccessible::List of QAccessible::ListItem instead. That bypasses the
 * table code path completely: list items map to AXStaticText, which does
 * have a value, the interfaces are stable, and the selection is provided
 * through QAccessibleSelectionInterface.
 *
 * The price is that the tree structure is flattened: items are reported
 * in the order in which they are displayed, without their nesting.
 *
 * Opt in per widget, before the widget is shown (in the .ui file or with
 * setProperty()), so that no accessible interface exists for it yet:
 *
 * \code
 * treeWidget->setProperty(RAccessibleFlatTree::propertyName(), true);
 * \endcode
 *
 * One item of the tree is reported as one element, no matter how many
 * columns the tree has. The text of the item is read from the column
 * given by the property columnPropertyName() (column 0 by default):
 *
 * \code
 * // e.g. block list: the block name is in column 2:
 * treeWidget->setProperty(RAccessibleFlatTree::columnPropertyName(), 2);
 * \endcode
 *
 * The text a screen reader reads for an item is Qt::AccessibleTextRole of
 * that column if set, the displayed text of that column otherwise. Trees
 * which show information as icons in other columns (layer list, block
 * list) should set Qt::AccessibleTextRole to a text which also describes
 * the state shown by those icons.
 *
 * Items may be added, removed and replaced at any time: the interfaces of
 * removed items are dropped before the items are deleted.
 *
 * \ingroup gui
 */
class QCADGUI_EXPORT RAccessibleFlatTree {
public:
    /**
     * Installs the accessibility factory (once). Called by RMainWindowQt.
     */
    static void install();

    /**
     * \return Name of the widget property a tree widget sets to true to
     * be exposed as a flat list.
     */
    static const char* propertyName() {
        return "RAccessibleFlatTree";
    }

    /**
     * \return Name of the widget property a tree widget sets to the index
     * of the column which holds the text of an item (0 if not set).
     */
    static const char* columnPropertyName() {
        return "RAccessibleFlatTreeColumn";
    }

private:
    static bool installed;
};

#endif
