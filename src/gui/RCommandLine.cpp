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
#include <QClipboard>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

#if QT_VERSION >= 0x050000
  #include <QGuiApplication>
#else
  #include <QApplication>
#endif

#include "RCommandLine.h"
#include "RDebug.h"

RCommandLine::RCommandLine(QWidget* parent) :
    QLineEdit(parent), it(history.end()) {
}

QString RCommandLine::getLastCommand() {
    if (history.isEmpty()) {
        return QString();
    }
    return history.last();
}

void RCommandLine::appendCommand(const QString& cmd) {
    if (!cmd.isEmpty() && (history.isEmpty() || history.last() != cmd)) {
        history.append(cmd);
    }
    it = history.end();
}

QStringList RCommandLine::getHistory() const {
    return history;
}

void RCommandLine::setHistory(QStringList& h) {
    history = h;
    it = history.end();
}

void RCommandLine::paste() {
#if QT_VERSION >= 0x050000
    QClipboard* cb = QGuiApplication::clipboard();
#else
    QClipboard* cb = QApplication::clipboard();
#endif
    //qDebug("pasting: " + cb.text());

    QString text = cb->text();

    // multi line paste and enter:
    if (text.contains("\n")) {
        QStringList lines = text.split('\n');
        for (int i=0; i<lines.length(); i++) {
            //qDebug("line: " + lines[i]);
            emit commandConfirmed(lines[i]);
        }
    }
    else {
        // single line paste only:
        QLineEdit::paste();
    }
}

bool RCommandLine::event(QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* ke = dynamic_cast<QKeyEvent*> (event);
        if (ke->key() == Qt::Key_Tab) {
            emit completeCommand(text());
            return true;
        }
    }
    return QLineEdit::event(event);
}

void RCommandLine::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_L:
        if (event->modifiers() == Qt::ControlModifier) {
            emit clearHistory();
            return;
        }
        break;
    case Qt::Key_V:
        if (event->modifiers() == Qt::ControlModifier) {
            paste();
            return;
        }
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return: {
        QString t = text();
//        if (!t.isEmpty() && (history.isEmpty() || history.last() != t)) {
//            history.append(t);
//        }
        it = history.end();
        emit commandConfirmed(t);
        }
        break;
    case Qt::Key_Up:
        if (it != history.begin()) {
            it--;
            setText(*it);
        }
        return;
        break;
    case Qt::Key_Down:
        if (it != history.end()) {
            it++;
            if (it != history.end()) {
                setText(*it);
            } else {
                clear();
            }
        }
        return;
        break;
    default:
        break;
    }
    QLineEdit::keyPressEvent(event);
}

