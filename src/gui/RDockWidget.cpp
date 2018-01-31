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
#include <QActionEvent>
#include <QDebug>
#include <QWidgetAction>

#include "RDockWidget.h"
#include "RMainWindowQt.h"


RDockWidget::RDockWidget(const QString& title, QWidget* parent, Qt::WindowFlags flags) :
    QDockWidget(title, parent, flags), layout(NULL) {

    // avoid document drag error when dragging icon under macOS:
    setWindowIcon(QIcon());
}

RDockWidget::RDockWidget(QWidget* parent, Qt::WindowFlags flags) :
    QDockWidget(parent, flags) {

    // avoid document drag error when dragging icon under macOS:
    setWindowIcon(QIcon());
}

void RDockWidget::showEvent(QShowEvent* event) {
    emit shown();
    QDockWidget::showEvent(event);
}

void RDockWidget::hideEvent(QHideEvent* event) {
    emit hidden();
    QDockWidget::hideEvent(event);
}

// workaround for Qt 5.6.1, 5.6.2 bug:
// dock widget closes before close dialog is shown
// dock widget state not persistent between sessions
// dock widget closes if user cancels close dialog
#ifdef Q_OS_MAC
#if QT_VERSION >= 0x050601 && QT_VERSION <= 0x050602
void RDockWidget::closeEvent(QCloseEvent* event) {
    // remember that this dock was closed by this event:
    RMainWindowQt* mw = RMainWindowQt::getMainWindow();
    if (mw) {
        QStringList closedDocks = mw->property("ClosedDocks").toStringList();
        closedDocks.append(QString("0x%1|%2").arg((qulonglong)event, 0, 16).arg(objectName()));
        mw->setProperty("ClosedDocks", closedDocks);
    }
    QDockWidget::closeEvent(event);
}
#endif
#endif

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

bool RDockWidget::event(QEvent* e) {
    if (e->type()==QEvent::KeyPress || e->type()==QEvent::KeyRelease) {
        //if (!appWin->isAncestorOf(this)) {
        if (isFloating()) {
            // dock widget is in undocked, floating:
            // forward event to main window:
            QKeyEvent* ke = dynamic_cast<QKeyEvent*>(e);
            RMainWindowQt* appWin = RMainWindowQt::getMainWindow();
            qApp->postEvent(appWin, new QKeyEvent(ke->type(), ke->key(), ke->modifiers(), ke->text(), ke->isAutoRepeat(), ke->count()));
            e->accept();
            return true;
        }

        e->ignore();
        return false;
    }

    return QDockWidget::event(e);
}
