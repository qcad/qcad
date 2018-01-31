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

#ifndef RCOMMANDLINE_H_
#define RCOMMANDLINE_H_

#include "gui_global.h"

#include <QEvent>
#include <QLineEdit>
#include <QMetaType>
#include <QStringList>

/**
 * \scriptable
 * \ingroup gui
 */
class QCADGUI_EXPORT RCommandLine: public QLineEdit {

Q_OBJECT

signals:
    void clearHistory();
    void commandConfirmed(const QString& command);
    void completeCommand(const QString& command);
    void escape();

public:
    RCommandLine(QWidget* parent = 0);
    QString getLastCommand();
    void appendCommand(const QString& cmd);
    QStringList getHistory() const;
    void setHistory(QStringList& h);
    void triggerCommand(const QString& cmd) {
        emit commandConfirmed(cmd);
    }

public slots:
    void paste();

protected:
    virtual void keyPressEvent(QKeyEvent* event);
    virtual bool event(QEvent* event);

private:
    QStringList history;
    QStringList::iterator it;
};

Q_DECLARE_METATYPE(RCommandLine*)

#endif
