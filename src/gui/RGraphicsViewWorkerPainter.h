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

#ifndef RGRAPHICSVIEWWORKERPAINTER_H
#define RGRAPHICSVIEWWORKERPAINTER_H

#include "gui_global.h"

#include "RGraphicsViewWorker.h"

class QPainter;

class QCADGUI_EXPORT RGraphicsViewWorkerPainter : public RGraphicsViewWorker {
    Q_OBJECT

public:
    RGraphicsViewWorkerPainter(RGraphicsViewImage& imageView, int threadId) : RGraphicsViewWorker(imageView, threadId), painter(NULL) {}
    virtual ~RGraphicsViewWorkerPainter();

    virtual void begin();
    virtual void end();

    virtual QImage getImage() const;
    virtual void setImage(const QImage& img);
    virtual void setPainter(QPainter* p);

    virtual QSize getImageSize() const;
    virtual void initImageBuffer(const QSize& size);

    virtual void paint();

    virtual void clear();

    virtual void setAntialiasing(bool on);
    virtual void setBackground(const QColor& col);
    virtual void setCompositionMode(QPainter::CompositionMode mode);
    virtual void setFont(const QFont& font);

    virtual void eraseRect(const QRectF& rect);

    virtual void setClipRect(const QRectF& rect);
    virtual void setClipping(bool on);
    virtual void setOpacity(double opacity);
    virtual void save();
    virtual void restore();

    virtual QTransform getTransform();
    virtual void setTransform(const QTransform& t, bool combine = false);

    virtual void translate(double x, double y);
    virtual void scale(double x, double y);

    virtual QTransform getWorldTransform() const;
    virtual void setWorldTransform(const QTransform& t, bool combine = false);


    virtual void setBrush(const QBrush& brush);
    virtual QPen getPen() const;
    virtual void setPen(const QPen& pen);

    virtual void drawPoint(const QPointF& p);

    //virtual void paintImage(const RImageData& img, bool workingSet);
    virtual void drawImage(int x, int y, const QImage& image);

    //virtual void paintText(const RTextBasedData& text, bool workingSet);
    virtual void drawText(const QRectF& rectangle, int flags, const QString& text);
    virtual void drawTextLayout(const QTextLayout& textLayout);

    virtual void fillPath(const RPainterPath& path, const QBrush& brush);
    virtual void drawPath(const RPainterPath& path);
    virtual void drawLine(const QLineF& line);
    virtual void strokePath(const QPainterPath& path, const QPen& pen);

    virtual void drawEllipse(const QRectF& rectangle);

    virtual void drawRect(const QRectF& rectangle);
    virtual void fillRect(const QRectF& rectangle, const QBrush& brush);

protected:
    QPainter* painter;
    QImage image;
};

#endif
