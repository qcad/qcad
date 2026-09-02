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

#include <QTextDocument>
#include <QTextDocumentFragment>
#include <QWidget>

#include "RAccessibleToolTipFilter.h"

RAccessibleToolTipFilter::RAccessibleToolTipFilter(QObject* parent) : QObject(parent) {
}

/**
 * \return Plain text version of the given HTML (tags removed, entities
 * decoded, line breaks replaced by ", ").
 */
QString RAccessibleToolTipFilter::toPlainText(const QString& html) {
    QString ret = QTextDocumentFragment::fromHtml(html).toPlainText();
    ret.replace(QChar::ParagraphSeparator, ", ");
    ret.replace(QChar::LineSeparator, ", ");
    ret.replace("\n", ", ");
    return ret.simplified();
}

bool RAccessibleToolTipFilter::eventFilter(QObject* obj, QEvent* event) {
    if (event->type()!=QEvent::ToolTipChange) {
        return false;
    }

    QWidget* w = qobject_cast<QWidget*>(obj);
    if (w==NULL) {
        return false;
    }

    static const char* propName = "AccessibleDescriptionFromToolTip";
    bool fromToolTip = w->property(propName).toBool();

    QString toolTip = w->toolTip();
    if (Qt::mightBeRichText(toolTip)) {
        // HTML tool tip: use plain text as accessible description
        // (unless an accessible description was set explicitly):
        if (fromToolTip || w->accessibleDescription().isEmpty()) {
            w->setAccessibleDescription(toPlainText(toolTip));
            w->setProperty(propName, true);
        }
    }
    else if (fromToolTip) {
        // tool tip changed back to plain text: let Qt use the tool tip:
        w->setAccessibleDescription(QString());
        w->setProperty(propName, false);
    }

    return false;
}
