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

#include "RAccessibleToolButton.h"

#include <QAccessible>
#include <QAccessibleWidget>
#include <QAction>
#include <QMenu>
#include <QToolButton>

#include "RGuiAction.h"

namespace {

/**
 * Removes the accelerator markers from the given button text
 * ("&Line" -> "Line", "AT&&T" -> "AT&T"). Qt does this internally with
 * qt_accStripAmp(), which is not exported.
 */
QString stripAmp(const QString& text) {
    QString ret;
    ret.reserve(text.length());
    for (int i = 0; i < text.length(); i++) {
        if (text.at(i) == QLatin1Char('&')) {
            if (i + 1 < text.length() && text.at(i + 1) == QLatin1Char('&')) {
                // "&&" is a literal ampersand:
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
 * Accessible interface of a tool button that triggers an action.
 * See RAccessibleToolButton for the rationale.
 */
class RAccessibleToolButtonInterface : public QAccessibleWidget {
public:
    explicit RAccessibleToolButtonInterface(QToolButton* button)
        : QAccessibleWidget(button, QAccessible::Button) {
    }

    QToolButton* getToolButton() const {
        return qobject_cast<QToolButton*>(object());
    }

    /**
     * \return Action the button triggers or NULL.
     */
    QAction* getDefaultAction() const {
        QToolButton* button = getToolButton();
        if (button == NULL) {
            return NULL;
        }
        return button->defaultAction();
    }

    QAccessible::Role role() const override {
        QToolButton* button = getToolButton();
        if (button == NULL) {
            return QAccessible::Button;
        }
        RGuiAction* action = dynamic_cast<RGuiAction*>(getDefaultAction());
        if (action != NULL && action->isToggleable()) {
            // action really switches something on and off:
            return QAccessible::CheckBox;
        }
        // every RGuiAction is checkable (a tool button stays checked while
        // its tool is running), but starting a tool is a command:
        return QAccessible::Button;
    }

    QString text(QAccessible::Text t) const override {
        QToolButton* button = getToolButton();
        if (button == NULL) {
            return QAccessibleWidget::text(t);
        }

        switch (t) {
        case QAccessible::Name: {
            QString str = button->accessibleName();
            if (str.isEmpty()) {
                str = button->text();
            }
            if (str.isEmpty()) {
                QAction* action = getDefaultAction();
                if (action != NULL) {
                    str = action->text();
                }
            }
            if (!str.isEmpty()) {
                return stripAmp(str);
            }
            break;
        }
        case QAccessible::Accelerator: {
            QAction* action = getDefaultAction();
            if (action != NULL && !action->shortcut().isEmpty()) {
                return action->shortcut().toString(QKeySequence::NativeText);
            }
            break;
        }
        default:
            break;
        }

        return QAccessibleWidget::text(t);
    }

    QAccessible::State state() const override {
        QAccessible::State s = QAccessibleWidget::state();
        QToolButton* button = getToolButton();
        if (button == NULL) {
            return s;
        }
        // the checked state is kept for the Button role, too: the value of
        // the element tells a screen reader which tool is running:
        s.checkable = button->isCheckable();
        s.checked = button->isChecked();
        s.pressed = button->isDown();
        return s;
    }

    QStringList actionNames() const override {
        QStringList names;
        QToolButton* button = getToolButton();
        if (button != NULL && button->isEnabled()) {
            // press first: the Cocoa plugin maps both "Press" and "Toggle"
            // to AXPress and uses the first action it finds:
            names << pressAction();
            if (role() == QAccessible::CheckBox) {
                names << toggleAction();
            }
            if (button->menu() != NULL) {
                names << showMenuAction();
            }
        }
        names << QAccessibleWidget::actionNames();
        names.removeDuplicates();
        return names;
    }

    void doAction(const QString& actionName) override {
        QToolButton* button = getToolButton();
        if (button == NULL || !button->isEnabled()) {
            return;
        }

        if (actionName == showMenuAction() && button->menu() != NULL) {
            button->showMenu();
            return;
        }

        if (actionName == pressAction() || actionName == toggleAction()) {
            // same code path as a mouse click: QToolButton::nextCheckState()
            // triggers the default action of the button:
            button->click();
            return;
        }

        QAccessibleWidget::doAction(actionName);
    }

    QStringList keyBindingsForAction(const QString& actionName) const override {
        if (actionName == pressAction()) {
            QAction* action = getDefaultAction();
            if (action != NULL && !action->shortcut().isEmpty()) {
                return QStringList(action->shortcut().toString(QKeySequence::NativeText));
            }
            return QStringList();
        }
        return QAccessibleWidget::keyBindingsForAction(actionName);
    }
};

QAccessibleInterface* raccessibleToolButtonFactory(const QString& classname, QObject* object) {
    Q_UNUSED(classname)

    QToolButton* button = qobject_cast<QToolButton*>(object);
    if (button == NULL) {
        return NULL;
    }
    if (button->defaultAction() == NULL) {
        // plain tool button, not backed by an action:
        return NULL;
    }
    if (!button->isCheckable() || button->autoExclusive()) {
        // Qt does not report these as check boxes, the default
        // implementation works:
        return NULL;
    }
    return new RAccessibleToolButtonInterface(button);
}

} // namespace

bool RAccessibleToolButton::installed = false;

void RAccessibleToolButton::install() {
    if (installed) {
        return;
    }
    installed = true;
    // factories are queried last installed first, so this one is asked
    // before the default implementation of Qt:
    QAccessible::installFactory(raccessibleToolButtonFactory);
}
