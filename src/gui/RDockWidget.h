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

#ifndef RDOCKWIDGET_H_
#define RDOCKWIDGET_H_

#include "gui_global.h"

#include <QMetaType>
#include <QDockWidget>

#include "RFlowLayout.h"

/**
 * \scriptable
 * \ingroup gui
 */
class QCADGUI_EXPORT RDockWidget: public QDockWidget {

Q_OBJECT

public:
    RDockWidget(const QString& title, QWidget* parent = NULL, Qt::WindowFlags flags = 0);
    RDockWidget(QWidget* parent = NULL, Qt::WindowFlags flags = 0);

signals:
    void shown();
    void hidden();

protected:
    virtual void showEvent(QShowEvent* event);
    virtual void hideEvent(QHideEvent* event);
#ifdef Q_OS_MAC
#if QT_VERSION >= 0x050601 && QT_VERSION <= 0x050602
    virtual void closeEvent(QCloseEvent* event);
#endif
#endif
    virtual void actionEvent(QActionEvent *event);

    virtual bool event(QEvent* e);

private:
    RFlowLayout* layout;
};

Q_DECLARE_METATYPE(RDockWidget*)

#endif
