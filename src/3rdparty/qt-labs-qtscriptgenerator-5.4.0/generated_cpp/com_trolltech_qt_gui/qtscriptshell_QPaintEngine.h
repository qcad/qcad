#ifndef QTSCRIPTSHELL_QPAINTENGINE_H
#define QTSCRIPTSHELL_QPAINTENGINE_H

#include <qpaintengine.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPaintEngine : public QPaintEngine
{
public:
    QtScriptShell_QPaintEngine(QPaintEngine::PaintEngineFeatures  features = 0);
    ~QtScriptShell_QPaintEngine();

    bool  begin(QPaintDevice*  pdev);
    QPoint  coordinateOffset() const;
    void drawEllipse(const QRect&  r);
    void drawEllipse(const QRectF&  r);
    void drawImage(const QRectF&  r, const QImage&  pm, const QRectF&  sr, Qt::ImageConversionFlags  flags = Qt::AutoColor);
    void drawLines(const QLine*  lines, int  lineCount);
    void drawLines(const QLineF*  lines, int  lineCount);
    void drawPath(const QPainterPath&  path);
    void drawPixmap(const QRectF&  r, const QPixmap&  pm, const QRectF&  sr);
    void drawPoints(const QPoint*  points, int  pointCount);
    void drawPoints(const QPointF*  points, int  pointCount);
    void drawPolygon(const QPoint*  points, int  pointCount, QPaintEngine::PolygonDrawMode  mode);
    void drawPolygon(const QPointF*  points, int  pointCount, QPaintEngine::PolygonDrawMode  mode);
    void drawRects(const QRect*  rects, int  rectCount);
    void drawRects(const QRectF*  rects, int  rectCount);
    void drawTextItem(const QPointF&  p, const QTextItem&  textItem);
    void drawTiledPixmap(const QRectF&  r, const QPixmap&  pixmap, const QPointF&  s);
    bool  end();
    QPaintEngine::Type  type() const;
    void updateState(const QPaintEngineState&  state);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPAINTENGINE_H
