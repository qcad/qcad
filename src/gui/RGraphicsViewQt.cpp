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
#include <QDragMoveEvent>
#include <QFrame>
#include <QGestureEvent>
#include <QPainter>

#include "RDebug.h"
#include "RDocumentInterface.h"
#include "RGraphicsViewQt.h"
#include "RMainWindow.h"
#include "RMainWindowQt.h"
#include "RMouseEvent.h"
#include "RS.h"
#include "RSettings.h"
#include "RTerminateEvent.h"
#include "RWheelEvent.h"

class RGraphicsScene;


RGraphicsViewQt::RGraphicsViewQt(QWidget* parent, bool showFocus)
    : QWidget(parent),
      showFocus(showFocus),
      focusFrameWidget(NULL),
      gesturesEnabled(true),
      gotMouseButtonPress(false),
      imageView(NULL) {

    setFocusPolicy(Qt::WheelFocus);
    setMouseTracking(true);

    // has no effect for now (Qt <= 5.10):
//#if QT_VERSION >= 0x050A00
//    setTabletTracking(true);
//#endif

    lastButtonState = Qt::NoButton;
    setAutoFillBackground(false);

    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);
    setContextMenuPolicy(Qt::PreventContextMenu);

    setImageView(new RGraphicsViewImage(this));

    connect(imageView, &QObject::destroyed, this, &RGraphicsViewQt::imageViewDeleted);
}



RGraphicsViewQt::~RGraphicsViewQt() {
//    if (imageView!=NULL) {
//        delete imageView;
//    }
}

void RGraphicsViewQt::setImageView(RGraphicsViewImage* v) {
    if (imageView!=NULL) {
        delete imageView;
    }
    imageView = v;
    imageView->setParent(this);
    imageView->setWidget(this);
}
    
/**
 * Repaints the view. If the view has been invalidated before,
 * the view is redrawn from scratch. Otherwise, only a cached
 * buffer is drawn (very fast).
 *
 * \see invalidate
 */
void RGraphicsViewQt::paintEvent(QPaintEvent* e) {
    if (imageView==NULL) {
        return;
    }

    double dpr = imageView->getDevicePixelRatio();

    RDocumentInterface* di = imageView->getDocumentInterface();
    if (di!=NULL && di->isSuspended()) {
        QPainter wPainter(this);
        QImage img = imageView->getGraphicsBufferWithPreview();
        if (!RMath::fuzzyCompare(dpr, 0.0)) {
            img.setDevicePixelRatio(dpr);
        }
        wPainter.drawImage(0,0, img);
        wPainter.end();
        return;
    }

    imageView->updateImage();

    // event is NULL for fake paint events (testing):
    if (e!=NULL) {
        QPainter wPainter(this);
        QImage img = imageView->getGraphicsBufferWithPreview();
        if (!RMath::fuzzyCompare(dpr, 0.0)) {
            img.setDevicePixelRatio(dpr);
        }
        wPainter.drawImage(0,0, img);

        wPainter.end();
    }
}

/**
 * Handle terminate events and gestures.
 */
bool RGraphicsViewQt::event(QEvent* e) {
    RTerminateEvent* te = dynamic_cast<RTerminateEvent*>(e);
    if (te!=NULL) {
        if (imageView!=NULL) {
            imageView->handleTerminateEvent(*te);
        }
        else {
            qWarning() << "imageView was deleted";
        }
        return true;
    }

    if (e->type() == QEvent::Gesture) {
        return gestureEvent(static_cast<QGestureEvent*>(e));
    }

#if QT_VERSION >= 0x050A00 && QT_VERSION <= 0x050C00
    // workaround for Qt 5.10.0-5.12.0 bug QTBUG-65559 with Wacom tablets:
    // TabletMove events are triggered instead of mouseMoveEvents if pen does NOT
    // hover over tablet when application is started:
    // convert to mouseMoveEvents here:
    if (e->type() == QEvent::TabletMove) {
        QTabletEvent* tabletEvent = dynamic_cast<QTabletEvent*>(e);
        QMouseEvent* mouseEvent = new QMouseEvent(QEvent::MouseMove, tabletEvent->posF(), tabletEvent->button(), tabletEvent->buttons(), tabletEvent->modifiers());
        QCoreApplication::postEvent(this, mouseEvent);
    }
#endif

    return QWidget::event(e);
}

/**
 * Handle gesture events.
 */
bool RGraphicsViewQt::gestureEvent(QGestureEvent* event) {
    if (imageView==NULL) {
        return true;
    }

    if (QGesture* swipe = event->gesture(Qt::SwipeGesture)) {
        imageView->handleSwipeGestureEvent(*static_cast<QSwipeGesture *>(swipe));
    }

    else if (QGesture* pan = event->gesture(Qt::PanGesture)) {
        imageView->handlePanGestureEvent(*static_cast<QPanGesture *>(pan));
    }

    else if (QGesture* pinch = event->gesture(Qt::PinchGesture)) {
        imageView->handlePinchGestureEvent(*static_cast<QPinchGesture *>(pinch));
    }

    event->accept();

    return true;
}

void RGraphicsViewQt::tabletEvent(QTabletEvent* event) {
    if (imageView==NULL) {
        return;
    }

    RGraphicsScene* s = imageView->getScene();

    if (event == NULL || s==NULL) {
        return;
    }

#if QT_VERSION < 0x050C00
    // Qt 5.12, 5.13 crashes:
    RTabletEvent e(*event, *s, *imageView);
    imageView->handleTabletEvent(e);
#endif

    // needed for some types of Wacom tablets under Windows:
    event->ignore();
}

/**
 * Relays the Qt mouse event to the scene.
 */
void RGraphicsViewQt::mouseMoveEvent(QMouseEvent* event) {
    if (imageView==NULL) {
        return;
    }

    if (event==NULL || imageView->getScene()==NULL) {
        return;
    }

    RGraphicsScene* s = imageView->getScene();

    RMouseEvent e(*event, *s, *imageView, imageView->getDevicePixelRatio());
    imageView->handleMouseMoveEvent(e);

 #if (QT_VERSION < QT_VERSION_CHECK(4, 8, 0))
    // workaround for wacom tablets bug: wacom tablets don't fire a mouseReleaseEvent
    // if a mouse button is pressed, the mouse dragged and then the mouse button
    // is released:
    // bug present in Qt 4.7.4
    // bug fixed in Qt 4.8.3, possibly earlier
    if (lastButtonState!=event->buttons()) {
        if (lastButtonState.testFlag(Qt::LeftButton)==true && 
            event->buttons().testFlag(Qt::LeftButton)==false) {

            QMouseEvent e(
                QEvent::MouseButtonRelease,
                event->pos(),
                Qt::LeftButton,
                event->buttons(),
                event->modifiers()
            );
            mouseReleaseEvent(&e);
        }
        if (lastButtonState.testFlag(Qt::MidButton)==true && 
            event->buttons().testFlag(Qt::MidButton)==false) {

            QMouseEvent e(
                QEvent::MouseButtonRelease,
                event->pos(),
                Qt::MidButton,
                event->buttons(),
                event->modifiers()
            );
            mouseReleaseEvent(&e);
        }
        if (lastButtonState.testFlag(Qt::RightButton)==true && 
            event->buttons().testFlag(Qt::RightButton)==false) {

            QMouseEvent e(
                QEvent::MouseButtonRelease,
                event->pos(),
                Qt::RightButton,
                event->buttons(),
                event->modifiers()
            );
            mouseReleaseEvent(&e);
        }
        lastButtonState = event->buttons();
    }
#endif
    event->accept();
}

void RGraphicsViewQt::mousePressEvent(QMouseEvent* event) {
    if (imageView==NULL) {
        return;
    }

    gotMouseButtonPress = true;
    RGraphicsScene* s = imageView->getScene();
    if (event==NULL || s==NULL) {
        return;
    }

//#if (QT_VERSION == QT_VERSION_CHECK(5, 7, 0))
//    if (event->button()!=qApp->property("MOUSEBUTTON")) {
//        // eat phantom wacom tablet click:
//        event->accept();
//        return;
//    }
//#endif

    RMouseEvent e(*event, *s, *imageView, imageView->getDevicePixelRatio());
    mousePressScreenPosition = e.getScreenPosition();
    mousePressModelPosition = e.getModelPosition();
    mouseClickTimer.start();
    imageView->handleMousePressEvent(e);
    lastButtonState = event->buttons();
    event->accept();
}

void RGraphicsViewQt::mouseReleaseEvent(QMouseEvent* event) {
    static int ignoreTimeThreshold = RSettings::getIntValue("GraphicsView/IgnoreTimeThreshold", 150);
    static int ignoreDeltaThreshold = RSettings::getIntValue("GraphicsView/IgnoreDeltaThreshold", 100);

    if (imageView==NULL) {
        return;
    }

    if (gotMouseButtonPress) {
        // everything OK, got press, followed by release
    }
    else {
        // Qt/Wacom bug workaround for omitted mouse press events:
        // got release but no press (Qt / Wacom bug), simulate press:
        if (event->button()==RS::MiddleButton) {
            mousePressEvent(event);
        }
    }
    gotMouseButtonPress = false;

    RGraphicsScene* s = imageView->getScene();

    if (event==NULL || s==NULL) {
        return;
    }

//#if (QT_VERSION == QT_VERSION_CHECK(5, 7, 0))
//    if (event->button()!=qApp->property("MOUSEBUTTON")) {
//        // eat phantom wacom tablet click:
//        event->accept();
//        return;
//    }
//#endif

    event->ignore();


    RMouseEvent e(*event, *s, *imageView, imageView->getDevicePixelRatio());

    // if mouse press and mouse release happened within a short time span and the
    // mouse movement was small, use the mouse press location
    // otherwise use mouse release location to define point:
    if (mouseClickTimer.elapsed()<ignoreTimeThreshold &&
        e.getScreenPosition().getDistanceTo(mousePressScreenPosition) < ignoreDeltaThreshold) {
        e.setScreenPosition(mousePressScreenPosition);
        e.setModelPosition(mousePressModelPosition);
    }
    imageView->handleMouseReleaseEvent(e);
    lastButtonState = event->buttons();
    event->accept();
}

void RGraphicsViewQt::mouseDoubleClickEvent(QMouseEvent* event) {
    if (imageView==NULL) {
        return;
    }

    RGraphicsScene* s = imageView->getScene();

    if (event==NULL || s==NULL) {
        return;
    }

//#if (QT_VERSION == QT_VERSION_CHECK(5, 7, 0))
//    if (event->button()!=qApp->property("MOUSEBUTTON")) {
//        // eat phantom wacom tablet click:
//        event->accept();
//        return;
//    }
//#endif

    RMouseEvent e(*event, *s, *imageView, imageView->getDevicePixelRatio());
    imageView->handleMouseDoubleClickEvent(e);
    lastButtonState = event->buttons();
    event->accept();
}

void RGraphicsViewQt::wheelEvent(QWheelEvent* event) {
    if (imageView==NULL) {
        return;
    }

    RGraphicsScene* s = imageView->getScene();

    if (event==NULL || s==NULL) {
        return;
    }
    RWheelEvent e(*event, *s, *imageView, imageView->getDevicePixelRatio());
    imageView->handleWheelEvent(e);
    event->accept();
}

void RGraphicsViewQt::keyPressEvent(QKeyEvent* event) {
    if (imageView==NULL) {
        return;
    }

    if (event==NULL) {
        return;
    }
    event->ignore();

    imageView->handleKeyPressEvent(*event);

    if (event->key()==Qt::Key_Tab) {
        RMainWindowQt* appWin = RMainWindowQt::getMainWindow();
        if (appWin!=NULL) {
            if (appWin->handleTabKey(NULL)) {
                event->accept();
            }
        }
    }

    // we're NOT accepting the event here to make sure the
    // event handler of the main window has a chance to
    // handle key press events (e.g. enter to show tool dialog)
}

void RGraphicsViewQt::keyReleaseEvent(QKeyEvent* event) {
    if (imageView==NULL) {
        return;
    }
    if (event==NULL) {
        return;
    }
    event->ignore();

    imageView->handleKeyReleaseEvent(*event);

    // we're NOT accepting the event here to make sure the
    // event handler of the main window has a chance to
    // handle key press events (e.g. enter to show tool dialog)
}

void RGraphicsViewQt::dragEnterEvent(QDragEnterEvent* event) {
    emit dragEnter(event);
    event->accept();
}

void RGraphicsViewQt::dropEvent(QDropEvent* event) {
    emit drop(event);
    event->accept();
}

void RGraphicsViewQt::resizeEvent(QResizeEvent* ) {
    if (imageView==NULL || imageView->getDocument()==NULL) {
        return;
    }
    double dpr = imageView->getDevicePixelRatio();
    imageView->resizeImage((int)(width()*dpr), (int)(height()*dpr));
    imageView->regenerate();
}

int RGraphicsViewQt::getWidth() const {
    return width();
}

int RGraphicsViewQt::getHeight() const {
    return height();
}

QRect RGraphicsViewQt::getRect() const {
    return QRect(0,0,getWidth(),getHeight());
}

bool RGraphicsViewQt::getSignalsBlocked() const {
    return signalsBlocked();
}

void RGraphicsViewQt::setSignalsBlocked(bool on) {
    blockSignals(on);
}

QSize RGraphicsViewQt::sizeHint() const {
    return QSize(200, 200);
}

/**
 * Called when this view gets the focus. Highlights the view to show to the user
 * that events go to this view.
 */
void RGraphicsViewQt::focusInEvent(QFocusEvent* event) {
    if (imageView==NULL) {
        return;
    }

    RDocumentInterface* di = imageView->getDocumentInterface();
    if (di!=NULL) {
        RGraphicsViewQt* other =
                dynamic_cast<RGraphicsViewQt*>(
                    di->getLastKnownViewWithFocus()
                );
        if (other!=NULL) {
            other->removeFocus();
        }

        di->setLastKnownViewWithFocus(imageView);

        if (focusFrameWidget!=NULL) {
            QPalette p = focusFrameWidget->palette();
#ifdef Q_OS_MAC
            QColor light("#adc2d9");
            QColor dark("#adc2d9");
#else
            QColor light("#2d2d92");
            QColor dark("#2d2d92");
#endif
            p.setColor(QPalette::Light, light);
            p.setColor(QPalette::Dark, dark);
            focusFrameWidget->setPalette(p);
        }

        RMainWindow* mainWindow = RMainWindow::getMainWindow();
        if (mainWindow!=NULL) {
            mainWindow->notifyViewFocusListeners(imageView);
        }
    }

    QWidget::focusInEvent(event);
}

/**
 * Called when this view lost the focus. Resets the focus highlighting.
 */
void RGraphicsViewQt::focusOutEvent(QFocusEvent* event) {
    QWidget::focusOutEvent(event);
}

void RGraphicsViewQt::removeFocus() {
    if (showFocus && focusFrameWidget!=NULL) {
        QPalette p = focusFrameWidget->parentWidget()->palette();
        focusFrameWidget->setPalette(p);
    }
}

void RGraphicsViewQt::setFocusFrameWidget(QFrame* w) {
    focusFrameWidget = w;
}

void RGraphicsViewQt::simulateMouseMoveEvent() {
    if (imageView==NULL) {
        return;
    }

    if (!imageView->getLastKnownScreenPosition().isValid() && isVisible()) {
        QPoint p = mapFromGlobal(QCursor::pos());
        if (p.x()>width() || p.x()<0 || p.y()<0 || p.y()>height()) {
            p = QPoint(width()/2, height()/2);
        }
        imageView->setLastKnownScreenPosition(RVector(p.x(), p.y()));
        imageView->setLastKnownModelPosition(imageView->mapFromView(RVector(p.x(), p.y())));
    }
    //imageView->simulateMouseMoveEvent();
}

void RGraphicsViewQt::imageViewDeleted() {
    imageView = NULL;
}
