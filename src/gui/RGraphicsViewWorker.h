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

#ifndef RGRAPHICSVIEWWORKER_H
#define RGRAPHICSVIEWWORKER_H

#include "gui_global.h"

#include <QThread>

#include "RGraphicsViewImage.h"

class QCADGUI_EXPORT RGraphicsViewWorker : public QThread {
    Q_OBJECT

public:
    RGraphicsViewWorker(RGraphicsViewImage& imageView, int threadId) : imageView(imageView), threadId(threadId), list(nullptr), startIndex(-1), endIndex(-1) {}
    virtual ~RGraphicsViewWorker();

    enum ClearMode {
        NoClear = 0,
        ClearToTransparent = 1,
        ClearToBackground = 2
    };

    void run();

    virtual void init(QList<REntity::Id>& list, int start, int end);

    void setClearMode(ClearMode m) {
        clearMode = m;
    }

    ClearMode getClearMode() const {
        return clearMode;
    }

    QImage getImage() const {
        return image;
    }
    virtual void setImage(const QImage& img) {
        image = img;
    }

    bool hasTransforms() const {
        return !entityTransformStack.isEmpty();
    }

    QStack<RTransform> getEntityTransformStack() const {
        return entityTransformStack;
    }

    void pushTransform(const RTransform& t) {
        entityTransformStack.push(t);
    }

    void popTransform() {
        entityTransformStack.pop();
    }

    virtual void paint();

    virtual void begin() = 0;
    virtual void end() = 0;

    virtual void clear() = 0;

    virtual void setAntialiasing(bool on) = 0;
    virtual void setBackground(const QColor& col) = 0;
    virtual void setCompositionMode(QPainter::CompositionMode mode) = 0;
    virtual void setFont(const QFont& font) = 0;

    virtual void eraseRect(const QRectF& rect) = 0;

    virtual void setClipRect(const QRectF& rect) = 0;
    virtual void setClipping(bool on) = 0;
    virtual void setOpacity(double opacity) = 0;
    virtual void save() = 0;
    virtual void restore() = 0;

    virtual QTransform getTransform() = 0;
    virtual void setTransform(const QTransform& t, bool combine = false) = 0;

    virtual void translate(double x, double y) = 0;
    virtual void scale(double x, double y) = 0;

    virtual QTransform getWorldTransform() const = 0;
    virtual void setWorldTransform(const QTransform& t, bool combine = false) = 0;

    virtual void setBrush(const QBrush& brush) = 0;
    virtual QPen getPen() const = 0;
    virtual void setPen(const QPen& pen) = 0;

    virtual void drawPoint(const QPointF& p) = 0;

    virtual void paintImage(const RImageData& img, bool workingSet);
    virtual void drawImage(int x, int y, const QImage& image) = 0;

    virtual void paintText(const RTextBasedData& text, bool workingSet);
    virtual void drawText(const QRectF& rectangle, int flags, const QString& text) = 0;
    virtual void drawTextLayout(const QTextLayout& textLayout) = 0;

    virtual void fillPath(const RPainterPath& path, const QBrush& brush) = 0;
    virtual void drawPath(const RPainterPath& path) = 0;
    virtual void drawLine(const QPointF& p1, const QPointF& p2) {
        drawLine(QLineF(p1, p2));
    }
    virtual void drawLine(const QLineF& line) = 0;
    virtual void strokePath(const QPainterPath& path, const QPen& pen) = 0;

    virtual void drawEllipse(const QPointF& center, double rx, double ry) {
        drawEllipse(QRectF(center.x()-rx, center.y()-ry, rx*2, ry*2));
    }
    virtual void drawEllipse(const QRectF& rectangle) = 0;

    virtual void drawRect(const QRectF& rectangle) = 0;
    virtual void fillRect(const QRectF& rectangle, const QBrush& brush) = 0;


signals:
    void finished();

protected:
    int threadId;
    QList<REntity::Id>* list;
    int startIndex;
    int endIndex;
    ClearMode clearMode;

    QImage image;
    RGraphicsViewImage& imageView;
    QStack<RTransform> entityTransformStack;
};

#endif
