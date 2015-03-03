/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
#include "RDocumentInterface.h"
#include "RGraphicsView.h"
#include "RGrid.h"
#include "RRulerQt.h"
#include "RSettings.h"
#include "RMainWindowQt.h"
#include "RMdiChildQt.h"

#include <QPainter>

/**
 * Constructor
 */
RRulerQt::RRulerQt(QWidget* parent) :
    QFrame(parent),
    RRuler(),
    painter(NULL),
    lastSize(0,0),
    viewportChanged(false) {
    
    //QPalette p = palette();
    //QColor bg = p.color(QPalette::Window);
    //p.setColor(QPalette::Window, bg.darker(120));
    //setPalette(p);
    
    //setAutoFillBackground(false);

    cursorArrow.moveTo(0,0);
    cursorArrow.lineTo(-3,-3);
    cursorArrow.lineTo(3,-3);
}


/**
 * Destructor
 */
RRulerQt::~RRulerQt() {}


QSize RRulerQt::sizeHint() const {
    if (hint.isValid()) {
        return hint;
    }

    QFontMetrics fm(getFont());
    int pixelSize = fm.height();
    // approximation:
    //double pixelSize = getFont().pointSize()/72.0*96.0;
#ifdef Q_OS_MAC
    int offset = pixelSize>8 ? 12 : 10;
#else
    int offset = pixelSize>8 ? 8 : 6;
#endif
    QSize size(100, pixelSize + offset);
    if (orientation == Qt::Vertical) {
        size.transpose();
    }
    hint = size;
    return hint;
}

void RRulerQt::setOrientation(Qt::Orientation orientation) {
    RRuler::setOrientation(orientation);
    if (orientation == Qt::Horizontal) {
        setFixedHeight(sizeHint().height());
    }
    else {
        setFixedWidth(sizeHint().width());
    }
}

QFont RRulerQt::getFont() const {
    return RSettings::getRulerFont();
}

void RRulerQt::paintTick(int pos, bool major, const QString& label) {
    if (painter == NULL) {
        return;
    }
#ifdef Q_OS_MAC
    int top = 1;
#else
    int top = 0;
#endif
    int lineLength = 3;
    if (major) {
        lineLength = 7;
    }
    if (orientation == Qt::Horizontal) {
        painter->setPen(Qt::white);
        painter->drawLine(pos + 1, height() - lineLength, pos + 1, height());
        painter->setPen(Qt::black);
        painter->drawLine(pos, height() - lineLength, pos, height());
        if (!label.isEmpty()) {
            QRect rect(pos - 250, top, 500, 500);
            painter->drawText(rect, Qt::AlignTop | Qt::AlignHCenter, label);
        }
    } else {
        painter->setPen(Qt::white);
        painter->drawLine(width() - lineLength, pos + 1, width(), pos + 1);
        painter->setPen(Qt::black);
        painter->drawLine(width() - lineLength, pos, width(), pos);
        if (!label.isEmpty()) {
            painter->save();
            painter->rotate(-90);
            painter->translate(-pos, 0);
            QRect rect(- 250, top, 500, 500);
            painter->drawText(rect, Qt::AlignTop | Qt::AlignHCenter, label);
            painter->restore();
        }
    }
}
    
void RRulerQt::paintEvent(QPaintEvent* e) {
//    RMdiChildQt* mdiChild = RMdiChildQt::getMdiChild(this);
//    if (mdiChild!=NULL) {
//        if (mdiChild->isInBackground()) {
//            return;
//        }
//    }

    if (orientation == Qt::Horizontal) {
        if (sizeHint().height() != lastSize.height()) {
            lastSize.setHeight(sizeHint().height());
            updateViewport();
            return;
        }
    } else {
        if (sizeHint().width() != lastSize.width()) {
            lastSize.setWidth(sizeHint().width());
            updateViewport();
            return;
        }
    }

    QFrame::paintEvent(e);
    if (view==NULL) {
        return;
    }

//    RDocumentInterface* di = view->getDocumentInterface();
//    if (di==NULL) {
//        return;
//    }

    QSize newSize = size();
    if (lastSize != newSize) {
        buffer = QImage(newSize, QImage::Format_ARGB32);
        lastSize = newSize;
        viewportChanged = true;
    }

    if (viewportChanged) {
        painter = new QPainter(&buffer);
        //painter->setCompositionMode(QPainter::CompositionMode_Clear);
        //painter->eraseRect(QRect(QPoint(0, 0), size()));
        //painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
#ifdef Q_OS_MAC
        QLinearGradient fade;
        fade.setStart(0, 0);
        if (orientation==Qt::Horizontal) {
            fade.setFinalStop(0, height());
        }
        else {
            fade.setFinalStop(width(), 0);
        }
        fade.setColorAt(0, QColor(0xe5, 0xe5, 0xe5));
        fade.setColorAt(1, QColor(0xc2, 0xc2, 0xc2));
        painter->fillRect(rect(), fade);
#else
        painter->fillRect(rect(), palette().color(QPalette::Window));
#endif

        painter->setPen(Qt::black);
        painter->setFont(getFont());

        RGrid* grid = view->getGrid();
        if (grid == NULL) {
            return;
        }

        grid->paintRuler(*this);

        delete painter;
        painter = NULL;
    }

    QPainter wPainter(this);
    wPainter.drawImage(0,0,buffer);
    RVector p = view->mapToView(cursorPosition);
    if (orientation==Qt::Horizontal) {
        wPainter.translate(p.x, height()-4);
        wPainter.fillPath(cursorArrow, Qt::black);
    }
    else {
        wPainter.rotate(-90);
        wPainter.translate(-p.y+1, width()-4);
        wPainter.fillPath(cursorArrow, Qt::black);
    }
    wPainter.end();

    viewportChanged = false;
}

void RRulerQt::updateViewport() {
//    RMdiChildQt* mdiChild = RMdiChildQt::getMdiChild(this);
//    if (mdiChild!=NULL) {
//        if (mdiChild->isInBackground()) {
//            return;
//        }
//    }

    viewportChanged = true;
    QSize h = sizeHint();
    if (orientation==Qt::Horizontal) {
        resize(width(), h.height());
        setMinimumHeight(h.height());
        setMaximumHeight(h.height());
    }
    else {
        resize(h.width(), height());
        setMinimumWidth(h.width());
        setMaximumWidth(h.width());
    }
    update();
}

void RRulerQt::updateCoordinate(RDocumentInterface* documentInterface) {
    //cursorPosition = wcsPosition;
    cursorPosition = documentInterface->getCursorPosition();
}
