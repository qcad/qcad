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

#include "RAccessibleContainers.h"

#include <QAccessible>
#include <QAccessibleWidget>
#include <QDockWidget>
#include <QMdiArea>
#include <QStatusBar>
#include <QToolBar>

namespace {

/**
 * Removes the accelerator markers from the given text ("&File" -> "File").
 */
QString stripAmp(const QString& text) {
    QString ret;
    ret.reserve(text.length());
    for (int i = 0; i < text.length(); i++) {
        if (text.at(i) == QLatin1Char('&')) {
            if (i + 1 < text.length() && text.at(i + 1) == QLatin1Char('&')) {
                ret += QLatin1Char('&');
                i++;
            }
            continue;
        }
        ret += text.at(i);
    }
    return ret;
}

/**
 * Group with a name: accessible name of the widget if set, its window
 * title otherwise (tool bars and dock widgets carry their title there).
 */
class RAccessibleGroupInterface : public QAccessibleWidget {
public:
    RAccessibleGroupInterface(QWidget* w, QAccessible::Role role)
        : QAccessibleWidget(w, role) {
    }

    QString text(QAccessible::Text t) const override {
        if (t == QAccessible::Name) {
            QString name;
            if (widget() != NULL) {
                name = widget()->accessibleName();
                if (name.isEmpty()) {
                    name = widget()->windowTitle();
                }
            }
            if (!name.isEmpty()) {
                return stripAmp(name);
            }
        }
        return QAccessibleWidget::text(t);
    }
};

QAccessibleInterface* raccessibleContainersFactory(const QString& classname, QObject* object) {
    QWidget* widget = qobject_cast<QWidget*>(object);
    if (widget == NULL) {
        return NULL;
    }

    // graphics views are identified by their class name: RGraphicsViewQt
    // lives in this library, the RHI based view (RGraphicsViewRhi3D, 2D
    // and 3D mode) in the qcadrhi3d module. Not the viewport
    // widgets around them (RGraphicsViewportRhi2D: view, scroll bars and
    // grid info label), those stay transparent:
    if (classname == "RGraphicsViewQt" || classname.startsWith("RGraphicsViewRhi")) {
        return new QAccessibleWidget(widget, QAccessible::Graphic);
    }

#ifdef Q_OS_MACOS
    // macOS only: the Cocoa plugin ignores tool bars and reports dock
    // widgets as windows and the status bar as static text (see
    // RAccessibleContainers). Windows (UI Automation) and Linux (AT-SPI)
    // present the native roles of Qt correctly:
    if (qobject_cast<QToolBar*>(widget) != NULL ||
        qobject_cast<QDockWidget*>(widget) != NULL ||
        qobject_cast<QStatusBar*>(widget) != NULL) {
        return new RAccessibleGroupInterface(widget, QAccessible::Grouping);
    }
#endif

    if (qobject_cast<QMdiArea*>(widget) != NULL) {
        // QAccessibleMdiArea only lists the sub windows: use the generic
        // widget implementation which lists all child widgets (document
        // tab bar, viewport with the sub windows):
        return new QAccessibleWidget(widget, QAccessible::Client);
    }

    return NULL;
}

} // namespace

bool RAccessibleContainers::installed = false;

void RAccessibleContainers::install() {
    if (installed) {
        return;
    }
    installed = true;
    QAccessible::installFactory(raccessibleContainersFactory);
}
