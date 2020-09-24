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
    viewportChanged(false),
    darkGuiBackground(-1) {

    qreal dpr = 1.0;
#if QT_VERSION >= 0x050000
    dpr = devicePixelRatio();
#endif
    cursorArrow.moveTo(0,0);
    cursorArrow.lineTo(-3*dpr,-3*dpr);
    cursorArrow.lineTo(3*dpr,-3*dpr);
}


/**
 * Destructor
 */
RRulerQt::~RRulerQt() {}


QSize RRulerQt::sizeHint() const {
    if (hint.isValid()) {
        return hint;
    }

    qreal dpr = 1.0;
#if QT_VERSION >= 0x050000
    dpr = devicePixelRatio();
#endif

    QFontMetrics fm(getFont());
    int pixelSize = fm.height();

#ifdef Q_OS_MAC
    int offset = pixelSize>8*dpr ? 12*dpr : 10*dpr;
#else
    int offset = pixelSize>8*dpr ? 8*dpr : 6*dpr;
#endif

//#if QT_VERSION >= 0x050000
//    pixelSize *= devicePixelRatio();
//    offset *= devicePixelRatio();
//#endif

    QSize size(100, pixelSize + offset);
    if (orientation == Qt::Vertical) {
        size.transpose();
    }
    hint = size/dpr;
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
    qreal dpr = 1.0;
#if QT_VERSION >= 0x050000
    dpr = devicePixelRatio();
#endif
    int lineLength = 3*dpr;
    if (major) {
        lineLength = 7*dpr;
    }

    if (RSettings::getHighResolutionGraphicsView()) {
        pos /= dpr;
    }

    if (orientation == Qt::Horizontal) {
        painter->setPen(darkGuiBackground==1 ? Qt::black : Qt::white);
        painter->drawLine(pos + 1, height()*dpr - lineLength, pos + 1, height()*dpr);
        painter->setPen(darkGuiBackground==1 ? Qt::white : Qt::black);
        painter->drawLine(pos, height()*dpr - lineLength, pos, height()*dpr);
        if (!label.isEmpty()) {
            QRect rect(pos - 250, top, 500, 500);
            painter->drawText(rect, Qt::AlignTop | Qt::AlignHCenter, label);
        }
    } else {
        painter->setPen(darkGuiBackground==1 ? Qt::black : Qt::white);
        painter->drawLine(width()*dpr - lineLength, pos + 1, width()*dpr, pos + 1);
        painter->setPen(darkGuiBackground==1 ? Qt::white : Qt::black);
        painter->drawLine(width()*dpr - lineLength, pos, width()*dpr, pos);
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
    qreal dpr = 1.0;
#if QT_VERSION >= 0x050000
    dpr = devicePixelRatio();
#endif

    darkGuiBackground = RSettings::hasDarkGuiBackground();

    if (orientation == Qt::Horizontal) {
        if (sizeHint().height()*dpr != lastSize.height()) {
            lastSize.setHeight(sizeHint().height()*dpr);
            updateViewport();
            return;
        }
    } else {
        if (sizeHint().width()*dpr != lastSize.width()) {
            lastSize.setWidth(sizeHint().width()*dpr);
            updateViewport();
            return;
        }
    }

    QFrame::paintEvent(e);
    if (view==NULL) {
        return;
    }

    QSize newSize = size()*dpr;
    if (lastSize != newSize) {
        buffer = QImage(newSize, QImage::Format_ARGB32);
        lastSize = newSize;
        viewportChanged = true;
    }

    if (viewportChanged) {
        // 20190515: bug with rulers displayed on top of each other:
        //buffer.fill(Qt::transparent);
        buffer.fill(palette().color(QPalette::Window));

        painter = new QPainter(&buffer);
        painter->setPen(Qt::black);
        painter->setFont(getFont());

        RGrid* grid = view->getGrid();
        if (grid == NULL) {
            return;
        }

        grid->paintRuler(*this, dpr);

        delete painter;
        painter = NULL;
    }

    QPainter wPainter(this);
    //wPainter.drawImage(0,0,buffer);
    wPainter.drawImage(rect(), buffer);
    RVector p = view->mapToView(cursorPosition);
    if (RSettings::getHighResolutionGraphicsView()) {
        p /= dpr;
    }
    if (orientation==Qt::Horizontal) {
        wPainter.translate(p.x, height()-4);
        wPainter.fillPath(cursorArrow, darkGuiBackground==1 ? Qt::white : Qt::black);
    }
    else {
        wPainter.rotate(-90);
        wPainter.translate(-p.y+1, width()-4);
        wPainter.fillPath(cursorArrow, darkGuiBackground==1 ? Qt::white : Qt::black);
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
