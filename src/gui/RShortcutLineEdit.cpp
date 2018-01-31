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
#include "RShortcutLineEdit.h"
#include <QKeyEvent>
#include <QKeySequence>
#include <QDebug>

RShortcutLineEdit::RShortcutLineEdit(QWidget* parent) :
    QLineEdit(parent), m_keyNum(0) {
    m_key[0] = m_key[1] = m_key[2] = m_key[3] = 0;
    installEventFilter(this);
}

bool RShortcutLineEdit::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *> (event);
        int nextKey = keyEvent->key();
        if (m_keyNum > 3 || nextKey == Qt::Key_Control || nextKey
                == Qt::Key_Shift || nextKey == Qt::Key_Meta || nextKey
                == Qt::Key_Alt)
            return true;

        nextKey |= translateModifiers(keyEvent->modifiers(), keyEvent->text());
        switch (m_keyNum) {
        case 0:
            m_key[0] = nextKey;
            break;
        case 1:
            m_key[1] = nextKey;
            break;
        case 2:
            m_key[2] = nextKey;
            break;
        case 3:
            m_key[3] = nextKey;
            break;
        default:
            break;
        }
        m_keyNum++;
        QKeySequence ks(m_key[0], m_key[1], m_key[2], m_key[3]);
        setText(ks);
        keyEvent->accept();
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

int RShortcutLineEdit::translateModifiers(Qt::KeyboardModifiers state,
        const QString &text) {
    int result = 0;
    // The shift modifier only counts when it is not used to type a symbol
    // that is only reachable using the shift key anyway
    if ((state & Qt::ShiftModifier) && (text.size() == 0
            || !text.at(0).isPrint() || text.at(0).isLetter()
            || text.at(0).isSpace()))
        result |= Qt::SHIFT;
    if (state & Qt::ControlModifier)
        result |= Qt::CTRL;
    if (state & Qt::MetaModifier)
        result |= Qt::META;
    if (state & Qt::AltModifier)
        result |= Qt::ALT;
    return result;
}

void RShortcutLineEdit::clear() {
    m_keyNum = 0;
    m_key[0] = m_key[1] = m_key[2] = m_key[3] = 0;
    QLineEdit::clear();
}
