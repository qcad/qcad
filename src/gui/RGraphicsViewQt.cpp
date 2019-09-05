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
#include <QtCore>
#include <QDragMoveEvent>
#include <QPainter>
#include <QScrollBar>
#include <QWheelEvent>

#include "RDebug.h"
#include "RDocument.h"
#include "RDocumentInterface.h"
#include "RFocusFrame.h"
#include "RGuiAction.h"
#include "RGraphicsScene.h"
#include "RGraphicsSceneQt.h"
#include "RGraphicsViewQt.h"
#include "RLine.h"
#include "RMainWindowQt.h"
#include "RMdiChildQt.h"
#include "RMouseEvent.h"
#include "RSettings.h"
#include "RSingleApplication.h"
#include "RSnap.h"
#include "RTerminateEvent.h"
#include "RUnit.h"
#include "RWheelEvent.h"



RGraphicsViewQt::RGraphicsViewQt(QWidget* parent, bool showFocus)
    : QWidget(parent),
      RGraphicsViewImage(),
      showFocus(showFocus),
      focusFrameWidget(NULL),
      gesturesEnabled(true),
      gotMouseButtonPress(false) {

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
}



RGraphicsViewQt::~RGraphicsViewQt() {
}

/**
 * Triggers a paintEvent based on a buffered offscreen bitmap (very fast).
 */
void RGraphicsViewQt::repaintView() {
    update();
}

void RGraphicsViewQt::repaintNow() {
    QWidget::repaint();
}

void RGraphicsViewQt::viewportChangeEvent() {
    RGraphicsViewImage::viewportChangeEvent();
    emit viewportChanged();
}
    
/**
 * Repaints the view. If the view has been invalidated before,
 * the view is redrawn from scratch. Otherwise, only a cached
 * buffer is drawn (very fast).
 *
 * \see invalidate
 */
void RGraphicsViewQt::paintEvent(QPaintEvent* e) {
    RDocumentInterface* di = getDocumentInterface();
    if (di!=NULL && di->isSuspended()) {
        QPainter wPainter(this);
        wPainter.drawImage(getRect(), graphicsBufferWithPreview);
        wPainter.end();
        return;
    }

    updateImage();

    // event is NULL for fake paint events (testing):
    if (e!=NULL) {
        QPainter wPainter(this);
        //wPainter.drawImage(0, 0, graphicsBufferWithPreview);
        wPainter.drawImage(getRect(), graphicsBufferWithPreview);
        //QPixmap pm;
        //pm.convertFromImage(graphicsBufferWithPreview);
        //wPainter.drawPixmap(this->rect(), pm);
        wPainter.end();
    }
}

/**
 * Handle terminate events and gestures.
 */
bool RGraphicsViewQt::event(QEvent* e) {
    RTerminateEvent* te = dynamic_cast<RTerminateEvent*>(e);
    if (te!=NULL) {
        RGraphicsView::handleTerminateEvent(*te);
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
    if (QGesture* swipe = event->gesture(Qt::SwipeGesture)) {
        RGraphicsView::handleSwipeGestureEvent(*static_cast<QSwipeGesture *>(swipe));
    }

    else if (QGesture* pan = event->gesture(Qt::PanGesture)) {
        RGraphicsView::handlePanGestureEvent(*static_cast<QPanGesture *>(pan));
    }

    else if (QGesture* pinch = event->gesture(Qt::PinchGesture)) {
        RGraphicsView::handlePinchGestureEvent(*static_cast<QPinchGesture *>(pinch));
    }

    event->accept();

    return true;
}

void RGraphicsViewQt::tabletEvent(QTabletEvent* event) {
    if (event == NULL || scene==NULL) {
        return;
    }

#if QT_VERSION < 0x050C00
    // Qt 5.12, 5.13 crashes:
    RTabletEvent e(*event, *scene, *this);
    RGraphicsView::handleTabletEvent(e);
#endif

    // needed for some types of Wacom tablets under Windows:
    event->ignore();
}

/**
 * Relays the Qt mouse event to the scene.
 */
void RGraphicsViewQt::mouseMoveEvent(QMouseEvent* event) {
    if (event==NULL || scene==NULL) {
        return;
    }

    RMouseEvent e(*event, *scene, *this, getDevicePixelRatio());
    RGraphicsView::handleMouseMoveEvent(e);

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
    gotMouseButtonPress = true;
    if (event==NULL || scene==NULL) {
        return;
    }

//#if (QT_VERSION == QT_VERSION_CHECK(5, 7, 0))
//    if (event->button()!=qApp->property("MOUSEBUTTON")) {
//        // eat phantom wacom tablet click:
//        event->accept();
//        return;
//    }
//#endif

    RMouseEvent e(*event, *scene, *this, getDevicePixelRatio());
    mousePressScreenPosition = e.getScreenPosition();
    mousePressModelPosition = e.getModelPosition();
    mouseClickTimer.start();
    RGraphicsView::handleMousePressEvent(e);
    lastButtonState = event->buttons();
    event->accept();
}

void RGraphicsViewQt::mouseReleaseEvent(QMouseEvent* event) {
    static int ignoreTimeThreshold = RSettings::getIntValue("GraphicsView/IgnoreTimeThreshold", 150);
    static int ignoreDeltaThreshold = RSettings::getIntValue("GraphicsView/IgnoreDeltaThreshold", 100);

    if (gotMouseButtonPress) {
        // everything OK, got press, followed by release
    }
    else {
        // Qt/Wacom bug workaround for omitted mouse press events:
        // got release but no press (Qt / Wacom bug), simulate press:
        if (event->button()==Qt::MidButton) {
            mousePressEvent(event);
        }
    }
    gotMouseButtonPress = false;

    if (event==NULL || scene==NULL) {
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

    RMouseEvent e(*event, *scene, *this, getDevicePixelRatio());

    // if mouse press and mouse release happend within a short time span and the
    // mouse movement was small, use the mouse press location
    // otherwise use mouse release location to define point:
    if (mouseClickTimer.elapsed()<ignoreTimeThreshold &&
        e.getScreenPosition().getDistanceTo(mousePressScreenPosition) < ignoreDeltaThreshold) {
        e.setScreenPosition(mousePressScreenPosition);
        e.setModelPosition(mousePressModelPosition);
    }
    RGraphicsView::handleMouseReleaseEvent(e);
    lastButtonState = event->buttons();
    event->accept();
}

void RGraphicsViewQt::mouseDoubleClickEvent(QMouseEvent* event) {
    if (event==NULL || scene==NULL) {
        return;
    }

//#if (QT_VERSION == QT_VERSION_CHECK(5, 7, 0))
//    if (event->button()!=qApp->property("MOUSEBUTTON")) {
//        // eat phantom wacom tablet click:
//        event->accept();
//        return;
//    }
//#endif

    RMouseEvent e(*event, *scene, *this, getDevicePixelRatio());
    RGraphicsView::handleMouseDoubleClickEvent(e);
    lastButtonState = event->buttons();
    event->accept();
}

void RGraphicsViewQt::wheelEvent(QWheelEvent* event) {
    if (event==NULL || scene==NULL) {
        return;
    }
    RWheelEvent e(*event, *scene, *this, getDevicePixelRatio());
    RGraphicsView::handleWheelEvent(e);
    event->accept();
}

void RGraphicsViewQt::keyPressEvent(QKeyEvent* event) {
    if (event==NULL) {
        return;
    }
    event->ignore();

    RGraphicsView::handleKeyPressEvent(*event);

    // we're NOT accepting the event here to make sure the
    // event handler of the main window has a chance to
    // handle key press events (e.g. enter to show tool dialog)
}

void RGraphicsViewQt::keyReleaseEvent(QKeyEvent* event) {
    if (event==NULL) {
        return;
    }
    event->ignore();

    RGraphicsView::handleKeyReleaseEvent(*event);

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
    regenerate();
}

int RGraphicsViewQt::getWidth() const {
    return width() * getDevicePixelRatio();
}

int RGraphicsViewQt::getHeight() const {
    return height() * getDevicePixelRatio();
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

QCursor RGraphicsViewQt::getCursor() {
    return QWidget::cursor();
}

void RGraphicsViewQt::setCursor(Qt::CursorShape cursorShape) {
    QWidget::setCursor(cursorShape);
}

void RGraphicsViewQt::setCursor(const QCursor& cursor) {
    QWidget::setCursor(cursor);
}

QSize RGraphicsViewQt::sizeHint() const {
    return QSize(200, 200);
}

/**
 * Called when this view gets the focus. Highlights the view to show to the user
 * that events go to this view.
 */
void RGraphicsViewQt::focusInEvent(QFocusEvent* event) {
    if (getDocumentInterface()!=NULL) {
        RGraphicsViewQt* other =
                dynamic_cast<RGraphicsViewQt*>(
                    getDocumentInterface()->getLastKnownViewWithFocus()
                );
        if (other!=NULL) {
            other->removeFocus();
        }

        getDocumentInterface()->setLastKnownViewWithFocus(this);

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
            mainWindow->notifyViewFocusListeners(this);
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

void RGraphicsViewQt::giveFocus() {
    QWidget::setFocus(Qt::OtherFocusReason);
}

bool RGraphicsViewQt::hasFocus() {
    return QWidget::hasFocus();
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

void RGraphicsViewQt::emitUpdateSnapInfo(RSnap* snap, RSnapRestriction* restriction) {
    if (receivers(SIGNAL(updateSnapInfo(QPainter*, RSnap*, RSnapRestriction*))) > 0) {
        QPainter gbPainter(&graphicsBufferWithPreview);
        emit(updateSnapInfo(&gbPainter, snap, restriction));
        gbPainter.end();
    }
}

void RGraphicsViewQt::emitUpdateTextLabel(const RTextLabel& textLabel) {
    if (receivers(SIGNAL(updateTextLabel(QPainter*, const RTextLabel&))) > 0) {
        QPainter gbPainter(&graphicsBufferWithPreview);
        emit(updateTextLabel(&gbPainter, textLabel));
        gbPainter.end();
    }
}

void RGraphicsViewQt::simulateMouseMoveEvent() {
    if (!lastKnownScreenPosition.isValid() && isVisible()) {
        QPoint p = mapFromGlobal(QCursor::pos());
        if (p.x()>width() || p.x()<0 || p.y()<0 || p.y()>height()) {
            p = QPoint(width()/2, height()/2);
        }
        lastKnownScreenPosition = RVector(p.x(), p.y());
        lastKnownModelPosition = mapFromView(lastKnownScreenPosition);
    }
    RGraphicsView::simulateMouseMoveEvent();
}

double RGraphicsViewQt::getDevicePixelRatio() const {
    if (RSettings::getHighResolutionGraphicsView()) {
#if QT_VERSION >= 0x050000
        return devicePixelRatio();
#else
        return 1;
#endif
    }
    else {
        return 1;
    }
}
