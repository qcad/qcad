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

#ifndef REVENTHANDLER_H
#define REVENTHANDLER_H

#include "gui_global.h"

#include <QObject>
#include <QMetaObject>
#include <QMetaType>

class QScrollBar;
class QUrl;
class QWidget;
class QPainter;
class QMimeData;
class QDragEnterEvent;

class RDocumentInterface;
class RGraphicsView;
class RRulerQt;
class RSnap;
class RVector;
class RTextLabel;
class RSnapRestriction;

/**
 * Event handler class. For each new document that is created or
 * opened, an event handler is created to handle various events
 * for the life time of the document.
 *
 * \scriptable
 * \generateScriptShell
 * \ingroup gui
 */
class QCADGUI_EXPORT REventHandler : public QObject {
    Q_OBJECT

public:
    REventHandler(QWidget* widget = NULL, RDocumentInterface* documentInterface = NULL);

    static bool isUrl(const QString& urlString);
    static QList<QUrl> getUrlsFromMimeData(QMimeData* mimeData);

    void drawInfoLabel(QPainter *painter, const RTextLabel &textLabel);
    void drawSnapLabel(QPainter *painter, const RVector &pos, const RVector &posRestriction, const QString &text);

public slots:
    void dragEnter(QDragEnterEvent *event);

    void updateTextLabel(QPainter *painter, const RTextLabel &textLabel);
    void updateSnapInfo(QPainter *painter, RSnap *snap, RSnapRestriction *restriction);
    void viewportChanged();

    void horizontalScrolled(double pos);
    void verticalScrolled(double pos);

private:
    QWidget* widget;
    RDocumentInterface* documentInterface;
    QScrollBar* hsb;
    QScrollBar* vsb;
    RGraphicsView* graphicsView;
    RRulerQt* hruler;
    RRulerQt* vruler;
};

Q_DECLARE_METATYPE(REventHandler*)

#endif
