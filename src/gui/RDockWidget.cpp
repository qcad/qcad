/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
#include <QActionEvent>
#include <QDebug>
#include <QWidgetAction>

#include "RDockWidget.h"


RDockWidget::RDockWidget(const QString& title, QWidget* parent, Qt::WindowFlags flags) :
    QDockWidget(title, parent, flags), layout(NULL) {
}

RDockWidget::RDockWidget(QWidget* parent, Qt::WindowFlags flags) :
    QDockWidget(parent, flags) {
}

void RDockWidget::showEvent(QShowEvent* event) {
    emit shown();
    QDockWidget::showEvent(event);
}

void RDockWidget::hideEvent(QHideEvent* event) {
    emit hidden();
    QDockWidget::hideEvent(event);
}

void RDockWidget::actionEvent(QActionEvent* event) {
    QAction* action = event->action();

    if (layout==NULL) {
        // first action added: add widget with flow layout to dock:
        QWidget* w = new QWidget();
        layout = new RFlowLayout(2,2,2);
        w->setLayout(layout);
        setWidget(w);
    }

    switch (event->type()) {
        case QEvent::ActionAdded: {
            Q_ASSERT_X(qobject_cast<QWidgetAction*>(action) == 0 || layout->indexOf(qobject_cast<QWidgetAction*>(action)) == -1,
                        "RDockWidget", "widgets cannot be inserted multiple times");

            int index = layout->count();
            if (event->before()) {
                index = layout->indexOf(event->before());
                Q_ASSERT_X(index != -1, "RDockWidget::insertAction", "internal error");
            }
            layout->insertAction(index, action);
            break;
        }

        case QEvent::ActionChanged:
            layout->invalidate();
            break;

        case QEvent::ActionRemoved: {
            int index = layout->indexOf(action);
            if (index != -1) {
                delete layout->takeAt(index);
            }
            break;
        }

        default:
            Q_ASSERT_X(false, "RDockWidget::actionEvent", "internal error");
    }
}
