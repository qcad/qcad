/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

#ifndef RGRAPHICSVIEWGL_H
#define RGRAPHICSVIEWGL_H

#include <QGLWidget>

#include "RGraphicsView.h"

class QGLPixelBuffer;
class RAction;
class RDocument;
class RDocumentInterface;
class RGraphicsSceneQt;
class RLine;
    
    

/**
 * \brief OpenGL 2d or 3d graphics view.
 *
 * An OpenGL graphics view displays a rectangular area of an
 * \ref RGraphicsSceneGl "OpenGL graphics scene".
 *
 * \ingroup qcadguiqt
 *
 * \scriptable
 */
class RGraphicsViewGl : public QGLWidget, public RGraphicsView {
    Q_OBJECT

public:
    RGraphicsViewGl(QWidget* parent = NULL);
    virtual ~RGraphicsViewGl();

    virtual void setScene(RGraphicsSceneQt* scene);

    virtual void regenerate(bool force=false);
    virtual void repaintView();

//    void makeMainCurrent();
//    void makePreviewCurrent();
//    void invalidate();
    
    virtual bool hasFocus() {
        return QWidget::hasFocus();
    }
    virtual void removeFocus() {}

    virtual RVector mapFromView(const RVector& v, double z=0.0) const;
    virtual RVector mapToView(const RVector& v) const;
    virtual double mapDistanceFromView(double d) const;
    virtual double mapDistanceToView(double d) const;

    virtual int getWidth() const;
    virtual int getHeight() const;
    
    virtual void setCursor(Qt::CursorShape cursorShape);
    virtual void setCursor(const QCursor& cursor);
    
    void callReferencePoint(const RVector& screenPosition, bool highlighted=false);

    virtual void paintGridPoint(const RVector& ucsPosition);
    
public slots:
    void slotReset();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();

    virtual void focusInEvent(QFocusEvent* event);
    virtual void focusOutEvent(QFocusEvent* event);
    //virtual void resizeEvent(QResizeEvent* event);
    //virtual void paintEvent(QPaintEvent* event);

//    void updateMainBuffer();
//    void paintMainBuffer();
//    void paintPreviewBuffer();
    void callGrid();
    void callZero();
    void callCursor();
    void callReferencePoints();

//    virtual void setupViewport() const;
//    virtual void setupScreenViewport();

    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* e);
    virtual void tabletEvent(QTabletEvent* e);

protected:
//    QImage buffer;
//    QGLPixelBuffer* mainBuffer;
//    QGLPixelBuffer* previewBuffer;
    RGraphicsSceneQt* sceneQt;
//    bool graphicsBufferNeedsUpdate;

    //! remember last mouse button state for wacom bug workaround
    Qt::MouseButtons lastButtonState;
};

Q_DECLARE_METATYPE(RGraphicsViewGl*)

#endif
