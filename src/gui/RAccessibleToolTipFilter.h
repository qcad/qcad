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

#ifndef RACCESSIBLETOOLTIPFILTER_H
#define RACCESSIBLETOOLTIPFILTER_H

#include "gui_global.h"

#include <QObject>
#include <QEvent>

/**
 * Application wide event filter which keeps the accessible description
 * of widgets (read by screen readers such as VoiceOver) free of HTML markup.
 *
 * Qt uses the tool tip of a widget as accessible description if no
 * accessible description is set. QCAD uses HTML tool tips in various
 * places (e.g. RMathLineEdit, RGuiAction), which would be read
 * including the markup. This filter sets the accessible description
 * to the plain text of such tool tips whenever a tool tip changes.
 *
 * \ingroup gui
 */
class QCADGUI_EXPORT RAccessibleToolTipFilter : public QObject {
    Q_OBJECT

public:
    RAccessibleToolTipFilter(QObject* parent = NULL);

    static QString toPlainText(const QString& html);

protected:
    virtual bool eventFilter(QObject* obj, QEvent* event);
};

Q_DECLARE_METATYPE(RAccessibleToolTipFilter*)

#endif
