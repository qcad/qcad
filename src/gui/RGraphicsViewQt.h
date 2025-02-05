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

#ifndef RGRAPHICSVIEWQT_H
#define RGRAPHICSVIEWQT_H

#include "gui_global.h"

#include <QElapsedTimer>
#include <QWidget>

#include "RVector.h"

class QFrame;
class QGestureEvent;
class RGraphicsViewImage;

/**
 * \brief QWidget based 2d graphics view.
 *
 * This graphics view displays a rectangular area of a
 * RGraphicsSceneQt.
 *
 * \ingroup gui
 * \scriptable
 * \generateScriptShell
 */
class QCADGUI_EXPORT RGraphicsViewQt : public QWidget {
    Q_OBJECT

public:
    RGraphicsViewQt(QWidget* parent=NULL, bool showFocus=true);
    virtual ~RGraphicsViewQt();

    void setImageView(RGraphicsViewImage* v);

    RGraphicsViewImage* getImageView() const {
        return imageView;
    }
    
    void disableGestures() {
        gesturesEnabled = false;
        ungrabGesture(Qt::PanGesture);
        ungrabGesture(Qt::PinchGesture);
    }

    virtual void removeFocus();

    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual QRect getRect() const;

    virtual bool getSignalsBlocked() const;
    virtual void setSignalsBlocked(bool on);
    
    void setFocusFrameWidget(QFrame* w);

    virtual void simulateMouseMoveEvent();

    virtual QSize sizeHint() const;

signals:
    void drop(QDropEvent* event);
    void dragEnter(QDragEnterEvent* event);

protected:

    bool event(QEvent* e);

    bool gestureEvent(QGestureEvent* event);

    virtual void focusInEvent(QFocusEvent* event);
    virtual void focusOutEvent(QFocusEvent* event);

    virtual void tabletEvent(QTabletEvent *event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void paintEvent(QPaintEvent*);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
    virtual void dragEnterEvent(QDragEnterEvent* event);
    virtual void dropEvent(QDropEvent* event);
    virtual bool focusNextPrevChild(bool next) {
        // ignore tab key:
        return false;
    }

private slots:
    void imageViewDeleted();

private:
    //! remember last mouse button state for wacom bug workaround
    Qt::MouseButtons lastButtonState;

    bool showFocus;

    QFrame* focusFrameWidget;

    bool gesturesEnabled;
    QElapsedTimer mouseClickTimer;
    RVector mousePressScreenPosition;
    RVector mousePressModelPosition;
    bool gotMouseButtonPress;

    // backend to render to bitmap (can be QPainter or Skia):
    RGraphicsViewImage* imageView;
};

Q_DECLARE_METATYPE(RGraphicsViewQt*)

#endif
