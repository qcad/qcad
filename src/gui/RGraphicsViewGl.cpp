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
#include <Qt>

// glu.h is required for gluProject / gluUnProject:
#ifdef Q_OS_MAC
#include <glu.h>
#endif

#ifdef Q_OS_WIN32
#include <windows.h>
#include <GL/glu.h>
#endif

#ifdef Q_OS_LINUX
#include <GL/glu.h>
#endif


#include <QDragMoveEvent>
#include <QScrollBar>
#include <QGLPixelBuffer>
#include <QGLFramebufferObject>
#include <QStyle>

#include "RDebug.h"
#include "RDocumentInterface.h"
#include "REntity.h"
#include "RGraphicsSceneQt.h"
#include "RGraphicsViewGl.h"
#include "RLine.h"
#include "RMath.h"
#include "RMouseEvent.h"
#include "RSettings.h"
#include "RTabletEvent.h"
#include "RUnit.h"
#include "RWheelEvent.h"


RGraphicsViewGl::RGraphicsViewGl(QWidget* parent)
    : QGLWidget(parent),
      RGraphicsView(),
      //mainBuffer(NULL),
      //previewBuffer(NULL),
      sceneQt(NULL) {
    
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL overlays: %d", 
        QGLFormat::hasOpenGLOverlays());
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL FBO: %d", 
        QGLFramebufferObject::hasOpenGLFramebufferObjects());
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL pbuffer: %d", 
        QGLPixelBuffer::hasOpenGLPbuffers());

    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version None: %d", 
        (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_None));
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version 1.1: %d", 
        (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_1_1));
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version 1.2: %d", 
        (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_1_2));
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version 1.3: %d", 
        (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_1_3));
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version 1.4: %d", 
        (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_1_4));
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version 1.5: %d", 
        (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_1_5));
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version 2.0: %d", 
        (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_2_0));
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version 2.1: %d", 
        (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_2_1));
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version 3.0: %d",
           (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_3_0));
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version 3.0: %d",
           (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_3_1));
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version 3.1: %d",
           (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_3_2));
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version 3.2: %d",
           (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_3_3));
    qDebug("RGraphicsViewGl::RGraphicsViewGl: OpenGL version 4.0: %d",
           (bool)(QGLFormat::openGLVersionFlags()&QGLFormat::OpenGL_Version_4_0));
    
    setFocusPolicy(Qt::WheelFocus);
    setMouseTracking(true);

    setAutoFillBackground(true);
    QPalette p = palette();
    p.setColor(QPalette::Window, RSettings::getColor("GraphicsViewColors/BackgroundColor"));
    setPalette(p);

    //invalidate();

    lastButtonState = Qt::NoButton;
}



RGraphicsViewGl::~RGraphicsViewGl() {
//    if (mainBuffer!=NULL) {
//        delete mainBuffer;
//    }
//    if (previewBuffer!=NULL) {
//        delete previewBuffer;
//    }
}

void RGraphicsViewGl::setScene(RGraphicsSceneQt* scene) {
    sceneQt = scene;
    RGraphicsView::setScene(scene);
}


/**
 * Invalidates this view to make sure that the main graphics buffer (bitmap)
 * is regenerated on the next \ref paintEvent.
 */
//void RGraphicsViewGl::invalidate() {
//    graphicsBufferNeedsUpdate = true;
//}



void RGraphicsViewGl::regenerate(bool) {
    //invalidate();
    update();
}



void RGraphicsViewGl::repaintView() {
    update();
}



/**
 * Makes the main pbuffer the current OpenGL context.
 */
 /*
void RGraphicsViewGl::makeMainCurrent() {
    if (mainBuffer==NULL) {
        qWarning("RGraphicsViewGl::makeMainCurrent: mainBuffer is NULL");
        return;
    }

    if (mainBuffer->isValid()==false || mainBuffer->makeCurrent()==false) {
        qWarning("RGraphicsViewGl::makeMainCurrent: invalid rendering context");
    }
}
*/



/**
 * Makes the preview pbuffer the current OpenGL context.
 * This pbuffer is overlayed over the main pbuffer.
 */
 /*
void RGraphicsViewGl::makePreviewCurrent() {
    if (previewBuffer==NULL) {
        qWarning("RGraphicsViewGl::makePreviewCurrent: previewBuffer is NULL");
        return;
    }

    if (previewBuffer->makeCurrent()==false) {
        qWarning("RGraphicsViewGl::makePreviewCurrent: invalid rendering context");
    }
}
*/
    
    

/**
 * Called when this view gets the focus. Highlights the view to show to the user
 * that events go to this view.
 */
void RGraphicsViewGl::focusInEvent(QFocusEvent* /*event*/) {
    /*
    QPalette p = palette();
    p.setColor(QPalette::Window, QColor(backgroundColor).lighter(120));
    setPalette(p);
    update();
    */
    if (getDocumentInterface()!=NULL) {
        getDocumentInterface()->setLastKnownViewWithFocus(this);
    }
}



/**
 * Called when this view lost the focus. Resets the focus highlighting.
 */
void RGraphicsViewGl::focusOutEvent(QFocusEvent* /*event*/) {
    /*
    QPalette p = palette();
    p.setColor(QPalette::Window, QColor(backgroundColor));
    setPalette(p);
    */
    update();
}


void RGraphicsViewGl::initializeGL() {
    qglClearColor(QColor("black"));
//    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);

//    glEnable(GL_LINE_SMOOTH);

    /*
    glViewport(0, 0, getWidth(), getHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        0, getWidth(),
        0, getHeight(),
        -1e6, 1e6
    );
    glMatrixMode(GL_MODELVIEW);
    */

    // clear the screen and the depth buffer:
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
    // reset transformations:
//    glLoadIdentity();

    //glRotated(30.0, 0.0,0.0,1.0);
//    glScaled(factor,factor,factor);
//    glTranslated(offset.x, offset.y, 0.0);
    //glTranslated(offset.x, offset.y, -10.0);
}

void RGraphicsViewGl::resizeGL(int width, int height) {
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        0, getWidth(),
        0, getHeight(),
        -1e6, 1e6
    );
    glMatrixMode(GL_MODELVIEW);
}

void RGraphicsViewGl::paintGL() {
    updateTextHeightThreshold();

    RDebug::startTimer(100);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //glRotated(30.0, 0.0,0.0,1.0);
    glScaled(factor,factor,factor);
    glTranslated(offset.x, offset.y, 0.0);

    glLineWidth(1);
    qglColor(QColor("white"));
//    glBegin(GL_LINES);
//    glVertex3f(0,0,0);
//    glVertex3f(100,50,0);
//    glEnd();

    RDocument* document = getDocument();
    if (document==NULL) {
        return;
    }

    // find out which entities might be visible:
    QRect r(0,0,getWidth(),getHeight());
    RVector c1 = mapFromView(RVector(r.left()-1,r.bottom()+1), -1e6);
    RVector c2 = mapFromView(RVector(r.right()+1,r.top()-1), 1e6);
    RBox queryBox(c1, c2);
    queryBox.growXY(
        RUnit::convert(
            document->getMaxLineweight()/100.0,
            RS::Millimeter,
            document->getUnit()
        )
    );

    RDebug::startTimer(101);
//    QSet<RObject::Id> ids = document->queryAllEntities();
    QSet<RObject::Id> ids = document->queryIntersectedEntitiesXY(queryBox, true);
    RDebug::stopTimer(101, "paintGL: query");

    RDebug::startTimer(101);
    QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);
    RDebug::stopTimer(101, "paintGL: reorder");

    QListIterator<REntity::Id> it(list);
    while (it.hasNext()) {
        RObject::Id id = it.next();

        QList<RPainterPath> pps = sceneQt->getPainterPaths(id);
        for (int i=0; i<pps.count(); i++) {
            RPainterPath path = pps[i];

            // for texts:
            if (!isPathVisible(path)) {
                continue;
            }

            QPointF cursor;
            for (int k = 0; k < path.elementCount(); ++k) {
                QPainterPath::Element el = path.elementAt(k);

                // line element in path:
                if (el.isLineTo()) {
                    glBegin(GL_LINES);
                    glVertex3f(cursor.x(), cursor.y(), 0);
                    glVertex3f(el.x, el.y, 0);
                    glEnd();
                }

                // curve element in path:
                else if (el.isCurveTo()) {
                    QPainterPath::Element el2 = path.elementAt(k+1);
                    QPainterPath::Element el3 = path.elementAt(k+2);
                    GLfloat ctrlpoints[4][3] = {
                        {cursor.x(), cursor.y(), 0.0},
                        {el.x, el.y, 0.0},
                        {el2.x, el2.y, 0.0},
                        {el3.x, el3.y, 0.0}
                    };
                    k+=2;
                    el = el3;

//                    qDebug() << "curve: start: " << ctrlpoints[0][0] << ctrlpoints[0][1];
//                    qDebug() << "curve: cp1:   " << ctrlpoints[1][0] << ctrlpoints[1][1];
//                    qDebug() << "curve: cp2:   " << ctrlpoints[2][0] << ctrlpoints[2][1];
//                    qDebug() << "curve: end:   " << ctrlpoints[3][0] << ctrlpoints[3][1];

                    //qDebug() << "curve: map";
                    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
                    glEnable(GL_MAP1_VERTEX_3);

                    //qDebug() << "curve: line strip";
                    glBegin(GL_LINE_STRIP);
                    for (int n = 0; n <= 16; n++) {
                        //qDebug() << "curve: line strip: eval: " << n/30.0;
                        glEvalCoord1f((GLfloat) n/16.0);
                    }
                    glEnd();
                }

                cursor = el;
            }
        }
    }

    RDebug::stopTimer(100, "paintGL");
}

/**
 * Called for every window resize. Resizes the OpenGL pbuffers.
 */
 /*
void RGraphicsViewGl::resizeEvent(QResizeEvent* event) {
    if (mainBuffer != NULL) {
        delete mainBuffer;
    }
    if (previewBuffer != NULL) {
        delete previewBuffer;
    }

    int w = getWidth();
    int h = getHeight();

    //mainBuffer = new QGLPixelBuffer(w, h, QGLFormat(QGL::AlphaChannel));
    mainBuffer = new QGLPixelBuffer(w, h);
    //assert(mainBuffer->format().alpha());
    previewBuffer = new QGLPixelBuffer(w, h, QGLFormat(QGL::AlphaChannel));
    //assert(previewBuffer->format().alpha());

    makeMainCurrent();
    setupViewport();

    makePreviewCurrent();
    setupViewport();

    if (scene != NULL) {
        scene->exportEntities(false);
        regenerate();
    }
}
*/



/**
 * Called when the viewport needs to be repainted.
 * If the current main graphics buffer is valid, the buffer (bitmap) is drawn (very fast).
 * If the current main graphics buffer is not valid, all display lists are called to 
 * regenerate the buffer.
 */
/*
void RGraphicsViewGl::paintEvent(QPaintEvent* event) {
    if (graphicsBufferNeedsUpdate) {
        RDebug::startTimer(67);
        updateMainBuffer();
        RDebug::stopTimer(67, "upd buffer");
    }
    
//    RDebug::startTimer(67);
    paintMainBuffer();
//    RDebug::stopTimer(67, "main buffer");

//    RDebug::startTimer(67);
    // TODO: enable preview:
//    paintPreviewBuffer();
//    RDebug::stopTimer(67, "prev buffer");
    
    // draw border around view with focus:
    if (hasFocus() || 
        (getDocumentInterface()!=NULL && 
         this==getDocumentInterface()->getLastKnownViewWithFocus())) {

        QPainter painter(this);
        QStyleOptionFrame opt2;
        opt2.initFrom(this);
        style()->drawPrimitive(QStyle::PE_FrameLineEdit, &opt2, &painter,
                this);
    }
}
*/


/**
 * Paints the graphics scene into a pbuffer and copies it into the
 * member variable \c buffer for later use by \ref RGraphicsViewGl::paintMainBuffer.
 */
/*
void RGraphicsViewGl::updateMainBuffer() {
    if (scene == NULL) {
        return;
    }

    RDebug::startTimer(68);
    makeMainCurrent();
    RDebug::stopTimer(68, "main current");

    glClearColor(0.0f,0.0f,0.0f,0.0f);
    setupViewport();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    RDocument& document = scene->getDocument();
    QSet<REntity::Id> ids;

    / *
    if (displayOnlyCurrentUcs) {
        RDocumentInterface& documentInterface = scene->getDocumentInterface();
        RUcs ucs = documentInterface.getCurrentUcs();

        // A UCS does not have a height, however, we can use the Z-vector component
        // of the UCS as height indication for UCS based floors.
        RBox box(
            RVector(
                RMINDOUBLE, 
                RMINDOUBLE, 
                ucs.origin.z + 1.0e-6
            ),
            RVector(
                RMAXDOUBLE, 
                RMAXDOUBLE, 
                ucs.origin.z + ucs.getZAxisDirection().getMagnitude() - 1.0e-6
            )
        );

        ids = document.queryIntersectedEntities(box, true);
    }
    else {
    * /
        ids = document.queryAllEntities();
        QList<REntity::Id> list = document.getStorage().orderBackToFront(ids);
    //}

    // For every entity a display list is called.
    // The display list has the same ID as the entity.
    // TODO: potential performance improvement with glCallLists()
    QListIterator<RObject::Id> it(list);
    while (it.hasNext()) {
        RObject::Id id = it.next();
        if (glIsList(id)==false) {
            qWarning("RGraphicsViewGl::updateMainBuffer(): OpenGL error: no such list: %d", id  );
            continue;
        }
        glCallList(id);
    }
    //QSet<REntity::Id>::iterator it;
//    for (it=ids.begin(); it!=ids.end(); it++) {
//        //qDebug("RGraphicsViewGl::updateMainBuffer: glCallList(%d)", *it);
//        if (glIsList(*it)==false) {
//            qWarning("RGraphicsViewGl::updateMainBuffer(): OpenGL error: no such list: %d", *it);
//            continue;
//        }
//        glCallList(*it);
//    }

    callZero();

//    RDebug::startTimer(68);
//    callGrid();
//    RDebug::stopTimer(68, "grid");
    
    RDebug::startTimer(68);
    callReferencePoints();
    RDebug::stopTimer(68, "ref points");
    
    glFlush();

    if (mainBuffer!=NULL) {
        RDebug::startTimer(68);
        buffer = mainBuffer->toImage();
        RDebug::stopTimer(68, "toImage");
    }
    
    graphicsBufferNeedsUpdate = false;
}
*/



/**
 * Redraws the view by simply drawing the cached \c buffer (very fast).
 */
 /*
void RGraphicsViewGl::paintMainBuffer() {
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), buffer);
    painter.end();
}
*/



/**
 * Paints the current preview as overlayed OpenGL pbuffer. This is called
 * by \ref paintEvent after the main buffer has been regenerated and drawn.
 * In other words: the preview is always on top of the main document and
 * always visible, regardless of the Z-levels in the preview.
 *
 * Note that this function also draws the cursor into the same OpenGL 
 * context as the preview.
 */
/*
void RGraphicsViewGl::paintPreviewBuffer() {
    if (sceneQt == NULL) {
        return;
    }
    makePreviewCurrent();
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    setupViewport();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    for (uint i = 1; i < sceneQt->getMaxPreviewListIndex(); i++) {
        glCallList(i);
    }
    
    callCursor();

    if (previewBuffer!=NULL) {
        // keep this before QPainter instantiation. QPainter does
        //   some magic that prevents this from working:
        QImage image = previewBuffer->toImage();

        QPainter painter(this);
        painter.drawImage(QPoint(0,0), image);
        painter.end();
    }
    else {
        qWarning("RGraphicsViewGl::paintPreviewBuffer: previewBuffer is NULL");
    }
}
*/



/**
 * Calls the OpenGL commands to paint the grid based on the information 
 * from \ref RGrid.
 * 
 * Which grid is painted depends on the current projection
 * rendering hint (\ref RExporter::setProjectionRenderingHint()).
 */
void RGraphicsViewGl::callGrid() {
    if (grid==NULL) {
        return;
    }

    grid->update();

    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_POINTS);

    grid->paint();

    glEnd();

    /*
    
    RDocumentInterface& documentInterface = getDocumentInterface();
    RUcs ucs = documentInterface.getCurrentUcs();
    
    RBox gridBox = grid->getRegion();
    RVector gridBoxC1 = gridBox.getDefiningCorner1();
    RVector gridBoxC2 = gridBox.getDefiningCorner2();

    RS::ProjectionRenderingHint projection = 
        scene.getProjectionRenderingHint();
    
    RVector min;
    RVector max;
    RVector spacing;

    // The grid is always displayed orthogonal to the model coordinate system.
    // The projection rendering hint defines which of the three possible grids
    // we show.
    switch (projection) {
    case RS::ThreeD:
    case RS::RenderTop:
        min.x = gridBoxC1.x;
        max.x = gridBoxC2.x;
        min.y = gridBoxC1.y;
        max.y = gridBoxC2.y;
        spacing.x = grid->getSpacing().x;
        spacing.y = grid->getSpacing().y;
        break;

    / *
    case RS::Front:
        min.x = gridBoxC1.x;
        max.x = gridBoxC2.x;
        min.y = gridBoxC1.z;
        max.y = gridBoxC2.z;
        spacing.x = grid.getSpacing().x;
        spacing.y = grid.getSpacing().z;
        break;

    case RS::Side:
        min.x = gridBoxC1.y;
        max.x = gridBoxC2.y;
        min.y = gridBoxC1.z;
        max.y = gridBoxC2.z;
        spacing.x = grid.getSpacing().y;
        spacing.y = grid.getSpacing().z;
        break;
    * /
    
    default:
        qWarning("RGraphicsViewGl::callGrid: "
            "invalid projection: %d", (int)projection);
        break;
    }

    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_POINTS);

    RVector gridPointUcs;
    RVector gridPointWcs;
    for (gridPointUcs.x=min.x; gridPointUcs.x<max.x; gridPointUcs.x+=spacing.x) {
        for (gridPointUcs.y=min.y; gridPointUcs.y<max.y; gridPointUcs.y+=spacing.y) {
            gridPointWcs = ucs.mapFromUcs(gridPointUcs);
            glVertex3f(gridPointWcs.x, gridPointWcs.y, gridPointWcs.z);
        }
    }
            
    glEnd();
    */
}



/**
 *
 */
void RGraphicsViewGl::paintGridPoint(const RVector& ucsPosition) {
    if (scene == NULL) {
        return;
    }
    RDocumentInterface& documentInterface = scene->getDocumentInterface();
    RUcs ucs = documentInterface.getCurrentUcs();
    RVector gridPointWcs = ucs.mapFromUcs(ucsPosition);
    glVertex3f(gridPointWcs.x, gridPointWcs.y, gridPointWcs.z);
}



/**
 * Calls the OpenGL commands to draw the cross hair for the absolute zero point.
 */
void RGraphicsViewGl::callZero() {
    double size = mapDistanceFromView(20);

    if (scene == NULL) {
        return;
    }
    if (scene->getProjectionRenderingHint()==RS::RenderThreeD) {
        size = 1000.0;
    }

    glColor3f(1.0f,0.0f,0.0f);
    glLineWidth(1.0f);

    glBegin(GL_LINES);
    glVertex3f(-size,0,0);
    glVertex3f(size,0,0);
    glVertex3f(0,-size,0);
    glVertex3f(0,size,0);
    glVertex3f(0,0,-size);
    glVertex3f(0,0,size);
    glEnd();
}



/**
 * Calls the OpenGL commands to draw the cross hair for the mouse cursor.
 */
void RGraphicsViewGl::callCursor() {
    if (scene == NULL) {
        return;
    }
    RVector cursorPosition = scene->getDocumentInterface().getCursorPosition();
    RVector position = mapToView(cursorPosition);

    if (position.valid) {
//        setupScreenViewport();

        // cursor size in pixels:
        double size = 10.0;

        glColor3f(1.0f,0.75f,0.0f);
        glLineWidth(1.0f);
        glDisable(GL_LINE_STIPPLE);

        // draw 3d crosshairs:
        glBegin(GL_LINES);
        glVertex3f(position.x-size, position.y, position.z);
        glVertex3f(position.x+size, position.y, position.z);
        glVertex3f(position.x, position.y-size, position.z);
        glVertex3f(position.x, position.y+size, position.z);
        glVertex3f(position.x, position.y, position.z-size);
        glVertex3f(position.x, position.y, position.z+size);
        glEnd();
    }
}



/**
 * Calls OpenGL commands to paint the reference points of all selected
 * entities. The reference points are stored in the scene and updated
 * whenever selected entities are exported to the scene.
 */
void RGraphicsViewGl::callReferencePoints() {
    if (scene == NULL) {
        return;
    }
    QMultiMap<REntity::Id, RVector>& referencePoints = 
        scene->getReferencePoints();

    QMultiMap<REntity::Id, RVector>::iterator it;
    for (it=referencePoints.begin(); it!=referencePoints.end(); ++it) {
        RVector position = mapToView(it.value());
        callReferencePoint(position, false);
    }
}



/**
 * Calls the OpenGL commands to draw a reference point at the given screen position.
 *
 * \param highlighted True to highlight the reference point (e.g. on mouse over)
 */
void RGraphicsViewGl::callReferencePoint(const RVector& screenPosition, bool highlighted) {
//    setupScreenViewport();

    // note that these commands use screen coordiantes
    // to ensure that reference points have a constant size:
    if (highlighted) {
        glColor4f(1.0f,1.0f,1.0f,1.0f);
    }
    else {
        glColor4f(1.0f,0.0f,0.0f,0.5f);
    }
    glLineWidth(1.0f);

    glBegin(GL_LINE_LOOP);
    glVertex3f(screenPosition.x-3, screenPosition.y-3, 0);
    glVertex3f(screenPosition.x+3, screenPosition.y-3, 0);
    glVertex3f(screenPosition.x+3, screenPosition.y+3, 0);
    glVertex3f(screenPosition.x-3, screenPosition.y+3, 0);
    glEnd();
    
//    setupViewport();
}



/**
 * Sets up the OpenGL viewport and transformations for the current
 * OpenGL context. This can be the OpenGL view or the pbuffer for
 * the preview.
 */
/*
void RGraphicsViewGl::setupViewport() const {
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);

    glEnable(GL_LINE_SMOOTH);

    glViewport(0, 0, getWidth(), getHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        0, getWidth(), 
        0, getHeight(), 
        -1e6, 1e6
    );
    glMatrixMode(GL_MODELVIEW);
    
    // clear the screen and the depth buffer:
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
    // reset transformations:
    glLoadIdentity();

    //glRotated(30.0, 0.0,0.0,1.0);
    glScaled(factor,factor,factor);
    glTranslated(offset.x, offset.y, 0.0);
    //glTranslated(offset.x, offset.y, -10.0);
}
*/



/**
 * Sets up the OpenGL viewport and transformations for the current
 * OpenGL context for 2d screen coordinate based rendering. 
 * This is typically used for overlay information such as reference
 * points, fixed size text labels, etc.
 */
/*
void RGraphicsViewGl::setupScreenViewport() {
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glViewport(0, 0, getWidth(), getHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        0, getWidth(), 
        0, getHeight(), 
        0, 1e6
    );
    glMatrixMode(GL_MODELVIEW);
    
    // clear the screen and the depth buffer:
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
    // reset transformations:
    glLoadIdentity();

    glScaled(1.0, -1.0, 1.0);
    glTranslated(0.0, -getHeight(), 0.0);
}
*/


void RGraphicsViewGl::keyPressEvent(QKeyEvent* event) {
    if (event == NULL) {
        return;
    }
    RGraphicsView::handleKeyPressEvent(*event);
}

void RGraphicsViewGl::keyReleaseEvent(QKeyEvent* event) {
    if (event == NULL) {
        return;
    }
    RGraphicsView::handleKeyReleaseEvent(*event);
}


/**
 * Relays the Qt mouse event to the scene.
 */
void RGraphicsViewGl::mousePressEvent(QMouseEvent* event) {
    if (event==NULL || scene==NULL) {
        return;
    }
    RMouseEvent e(*event, *scene, *this);
    RGraphicsView::handleMousePressEvent(e);
    lastButtonState = event->buttons();
}



/**
 * Relays the Qt mouse event to the scene.
 */
void RGraphicsViewGl::mouseReleaseEvent(QMouseEvent* event) {
    if (event==NULL || scene==NULL) {
        return;
    }
    RMouseEvent e(*event, *scene, *this);
    RGraphicsView::handleMouseReleaseEvent(e);
    lastButtonState = event->buttons();
}



/**
 * Relays the Qt mouse event to the scene.
 */
void RGraphicsViewGl::mouseMoveEvent(QMouseEvent* event) {
    if (event==NULL || scene==NULL) {
        return;
    }
    RMouseEvent e(*event, *scene, *this);
    RGraphicsView::handleMouseMoveEvent(e);

    // workaround for wacom tablets bug: wacom tablets don't fire a mouseReleaseEvent
    // if a mouse button is pressed, the mouse dragged and then the mouse button
    // is released:
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
}



/**
 * Relays the Qt mouse event to the scene.
 */
void RGraphicsViewGl::wheelEvent(QWheelEvent* event) {
    if (event==NULL || scene==NULL) {
        return;
    }
    RWheelEvent e(*event, *scene, *this);
    RGraphicsView::handleWheelEvent(e);
}

/**
 * Relays the Qt tablet event to the scene.
 */
void RGraphicsViewGl::tabletEvent(QTabletEvent* event) {
    if (event == NULL || scene==NULL) {
        return;
    }
    RTabletEvent e(*event, *scene, *this);
    RGraphicsView::handleTabletEvent(e);
    event->ignore();
}


/**
 * Sets the current zoom factor.
 */
/*
void RGraphicsViewGl::setZoom(float z) {
    if (z!=factor) {
        factor = z;
        update();
    }
}
*/



/**
 * Resets the viewport (factor 1 and no offset.
 */
void RGraphicsViewGl::slotReset() {
    factor = 1.0;
    offset = RVector(0,0);
    update();
}



/**
 * Maps the given absolute (WCS) 3d model coordinate into 2d screen coordinates.
 */
RVector RGraphicsViewGl::mapToView(const RVector& v) const {
    // let's not change the context when mapping coordinates:
    //makeMainCurrent();
//    setupViewport();

    double modelview[16], projection[16];
    GLint viewport[4];

    // get the projection matrix:
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    // get the modelview matrix:
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    // get the viewport:
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    // unproject the window coordinates to find the world coordinates:
    RVector ret;
    gluProject(v.x, v.y, v.z, modelview,
        projection, viewport, &ret.x, &ret.y, &ret.z);

    return RVector(ret.x, viewport[3]-ret.y, 0.0, v.valid);
}



/**
 * Maps the given 2d screen (view) coordinates in Pixels to absolute
 * (WCS) model coordinates on the current UCS plane.
 */
RVector RGraphicsViewGl::mapFromView(const RVector& v, double /*z*/) const {
    // We're producing a ray here that goes from the mouse position at the
    // front clipping plane to the mouse position at the back clipping plane.
    // The intersection of that ray with the current UCS plane is the 
    // coordinate that interests us.

    if (scene == NULL) {
        return RVector::invalid;
    }

    // let's not change the context when mapping coordinates:
    //makeMainCurrent();
//    setupViewport();

    double modelview[16];
    double projection[16];
    GLint viewport[4];
    
    // get the projection matrix     
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    // get the modelview matrix      
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    // get the viewport      
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    int success;

    // unproject the window coordinates on the front clipping plane:
    RVector mouseFront;
    success = gluUnProject(
        v.x, viewport[3]-v.y, 0.0, 
        modelview, projection, viewport, 
        &mouseFront.x, &mouseFront.y, &mouseFront.z
    );
    
    if (success!=GL_TRUE) {
        qDebug("RGraphicsViewGl::mapFromView: "
            "coordinate mapping failed");
    }
    
    // unproject the window coordinates on the back clipping plane:
    RVector mouseBack;
    success = gluUnProject(
        v.x, viewport[3]-v.y, 1.0, 
        modelview, projection, viewport, 
        &mouseBack.x, &mouseBack.y, &mouseBack.z
    );

    if (success!=GL_TRUE) {
        qDebug("RGraphicsViewGl::mapFromView: "
            "coordinate mapping failed");
    }

    RLine ray(mouseFront, mouseBack);

    RUcs ucs = scene->getDocumentInterface().getCurrentUcs();

//    qDebug() << "UCS: " << ucs;

    // create plane for current UCS:
    RTriangle plane(
        ucs.origin,
        ucs.origin + ucs.xAxisDirection,
        ucs.origin + ucs.yAxisDirection
    );

//    QList<RVector> retList = plane.getIntersectionPoints(ray, false);
    QList<RVector> retList = RShape::getIntersectionPoints(plane, ray, false);
    if (retList.size()==0) {
        qDebug("RGraphicsViewGl::mapFromView: ret: invalid");
        return RVector::invalid;
    }

    RVector ret = retList.front();
    
    /*
    RVector v2 = mouseBack - mouseFront;

    double f = - mouseFront.z / v2.z;

    RVector ret = mouseFront + v2 * f;
    */

//    qDebug("RGraphicsViewGl::mapFromView: front: %f/%f/%f", mouseFront.x, mouseFront.y, mouseFront.z);
//    qDebug("RGraphicsViewGl::mapFromView: back: %f/%f/%f", mouseBack.x, mouseBack.y, mouseBack.z);
//    qDebug("RGraphicsViewGl::mapFromView: ret: %f/%f/%f", ret.x, ret.y, ret.z);

    return ret;
}



/**
 * \todo Implement
 */
double RGraphicsViewGl::mapDistanceToView(double /*d*/) const {
    // todo: refactor into something more straight to the point
    /*
    QPointF point1 = mapToView(RVector(0,0,0));
    QPointF point2 = mapToView(RVector(d,0,0));
    QPointF point3 = mapToView(RVector(0,d,0));

    RVector p1(point1.x(), point1.y());
    RVector p2(point2.x(), point2.y());
    RVector p3(point3.x(), point3.y());

    double d1 = p1.getDistanceTo(p2);
    double d2 = p1.getDistanceTo(p3);

    return std::max(d1, d2);
    */
    return 0.0;
}



double RGraphicsViewGl::mapDistanceFromView(double d) const {
    RVector point1 = mapFromView(RVector(0,0));
    RVector point2 = mapFromView(RVector(1,0));
    return d * (point1.getDistanceTo(point2));
}



int RGraphicsViewGl::getWidth() const {
    return width();
}



int RGraphicsViewGl::getHeight() const {
    return height();
}



void RGraphicsViewGl::setCursor(Qt::CursorShape cursorShape) {
    QWidget::setCursor(cursorShape);
}

void RGraphicsViewGl::setCursor(const QCursor& cursor) {
    QWidget::setCursor(cursor);
}
