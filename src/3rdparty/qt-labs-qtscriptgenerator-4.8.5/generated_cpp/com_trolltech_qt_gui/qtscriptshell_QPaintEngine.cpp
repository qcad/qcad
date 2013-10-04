#include "qtscriptshell_QPaintEngine.h"

#include <QtScript/QScriptEngine>
#include <QVarLengthArray>
#include <QVariant>
#include <qimage.h>
#include <qline.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QPaintDevice*)
Q_DECLARE_METATYPE(QFlags<Qt::ImageConversionFlag>)
Q_DECLARE_METATYPE(QLine*)
Q_DECLARE_METATYPE(QLineF*)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QPoint*)
Q_DECLARE_METATYPE(QPointF*)
Q_DECLARE_METATYPE(QPaintEngine::PolygonDrawMode)
Q_DECLARE_METATYPE(QRect*)
Q_DECLARE_METATYPE(QRectF*)
Q_DECLARE_METATYPE(QTextItem)
Q_DECLARE_METATYPE(QPaintEngine::Type)
Q_DECLARE_METATYPE(QPaintEngineState)

QtScriptShell_QPaintEngine::QtScriptShell_QPaintEngine(QPaintEngine::PaintEngineFeatures  features)
    : QPaintEngine(features) {}

QtScriptShell_QPaintEngine::~QtScriptShell_QPaintEngine() {}

bool  QtScriptShell_QPaintEngine::begin(QPaintDevice*  pdev)
{
    QScriptValue _q_function = __qtscript_self.property("begin");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("begin") & QScriptValue::QObjectMember)) {
        qFatal("QPaintEngine::begin() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pdev)));
    }
}

QPoint  QtScriptShell_QPaintEngine::coordinateOffset() const
{
    QScriptValue _q_function = __qtscript_self.property("coordinateOffset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("coordinateOffset") & QScriptValue::QObjectMember)) {
        return QPaintEngine::coordinateOffset();
    } else {
        return qscriptvalue_cast<QPoint >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QPaintEngine::drawEllipse(const QRect&  r)
{
    QScriptValue _q_function = __qtscript_self.property("drawEllipse");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawEllipse") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawEllipse(r);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, r));
    }
}

void QtScriptShell_QPaintEngine::drawEllipse(const QRectF&  r)
{
    QScriptValue _q_function = __qtscript_self.property("drawEllipse");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawEllipse") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawEllipse(r);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, r));
    }
}

void QtScriptShell_QPaintEngine::drawImage(const QRectF&  r, const QImage&  pm, const QRectF&  sr, Qt::ImageConversionFlags  flags)
{
    QScriptValue _q_function = __qtscript_self.property("drawImage");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawImage") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawImage(r, pm, sr, flags);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, r)
            << qScriptValueFromValue(_q_engine, pm)
            << qScriptValueFromValue(_q_engine, sr)
            << qScriptValueFromValue(_q_engine, flags));
    }
}

void QtScriptShell_QPaintEngine::drawLines(const QLine*  lines, int  lineCount)
{
    QScriptValue _q_function = __qtscript_self.property("drawLines");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawLines") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawLines(lines, lineCount);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QLine *>(lines))
            << qScriptValueFromValue(_q_engine, lineCount));
    }
}

void QtScriptShell_QPaintEngine::drawLines(const QLineF*  lines, int  lineCount)
{
    QScriptValue _q_function = __qtscript_self.property("drawLines");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawLines") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawLines(lines, lineCount);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QLineF *>(lines))
            << qScriptValueFromValue(_q_engine, lineCount));
    }
}

void QtScriptShell_QPaintEngine::drawPath(const QPainterPath&  path)
{
    QScriptValue _q_function = __qtscript_self.property("drawPath");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawPath") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawPath(path);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, path));
    }
}

void QtScriptShell_QPaintEngine::drawPixmap(const QRectF&  r, const QPixmap&  pm, const QRectF&  sr)
{
    QScriptValue _q_function = __qtscript_self.property("drawPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawPixmap") & QScriptValue::QObjectMember)) {
        qFatal("QPaintEngine::drawPixmap() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, r)
            << qScriptValueFromValue(_q_engine, pm)
            << qScriptValueFromValue(_q_engine, sr));
    }
}

void QtScriptShell_QPaintEngine::drawPoints(const QPoint*  points, int  pointCount)
{
    QScriptValue _q_function = __qtscript_self.property("drawPoints");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawPoints") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawPoints(points, pointCount);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QPoint *>(points))
            << qScriptValueFromValue(_q_engine, pointCount));
    }
}

void QtScriptShell_QPaintEngine::drawPoints(const QPointF*  points, int  pointCount)
{
    QScriptValue _q_function = __qtscript_self.property("drawPoints");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawPoints") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawPoints(points, pointCount);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QPointF *>(points))
            << qScriptValueFromValue(_q_engine, pointCount));
    }
}

void QtScriptShell_QPaintEngine::drawPolygon(const QPoint*  points, int  pointCount, QPaintEngine::PolygonDrawMode  mode)
{
    QScriptValue _q_function = __qtscript_self.property("drawPolygon");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawPolygon") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawPolygon(points, pointCount, mode);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QPoint *>(points))
            << qScriptValueFromValue(_q_engine, pointCount)
            << qScriptValueFromValue(_q_engine, mode));
    }
}

void QtScriptShell_QPaintEngine::drawPolygon(const QPointF*  points, int  pointCount, QPaintEngine::PolygonDrawMode  mode)
{
    QScriptValue _q_function = __qtscript_self.property("drawPolygon");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawPolygon") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawPolygon(points, pointCount, mode);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QPointF *>(points))
            << qScriptValueFromValue(_q_engine, pointCount)
            << qScriptValueFromValue(_q_engine, mode));
    }
}

void QtScriptShell_QPaintEngine::drawRects(const QRect*  rects, int  rectCount)
{
    QScriptValue _q_function = __qtscript_self.property("drawRects");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawRects") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawRects(rects, rectCount);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QRect *>(rects))
            << qScriptValueFromValue(_q_engine, rectCount));
    }
}

void QtScriptShell_QPaintEngine::drawRects(const QRectF*  rects, int  rectCount)
{
    QScriptValue _q_function = __qtscript_self.property("drawRects");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawRects") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawRects(rects, rectCount);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<QRectF *>(rects))
            << qScriptValueFromValue(_q_engine, rectCount));
    }
}

void QtScriptShell_QPaintEngine::drawTextItem(const QPointF&  p, const QTextItem&  textItem)
{
    QScriptValue _q_function = __qtscript_self.property("drawTextItem");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawTextItem") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawTextItem(p, textItem);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, p)
            << qScriptValueFromValue(_q_engine, textItem));
    }
}

void QtScriptShell_QPaintEngine::drawTiledPixmap(const QRectF&  r, const QPixmap&  pixmap, const QPointF&  s)
{
    QScriptValue _q_function = __qtscript_self.property("drawTiledPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawTiledPixmap") & QScriptValue::QObjectMember)) {
        QPaintEngine::drawTiledPixmap(r, pixmap, s);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, r)
            << qScriptValueFromValue(_q_engine, pixmap)
            << qScriptValueFromValue(_q_engine, s));
    }
}

bool  QtScriptShell_QPaintEngine::end()
{
    QScriptValue _q_function = __qtscript_self.property("end");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("end") & QScriptValue::QObjectMember)) {
        qFatal("QPaintEngine::end() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

QPaintEngine::Type  QtScriptShell_QPaintEngine::type() const
{
    QScriptValue _q_function = __qtscript_self.property("type");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("type") & QScriptValue::QObjectMember)) {
        qFatal("QPaintEngine::type() is abstract!");
    } else {
        return qscriptvalue_cast<QPaintEngine::Type >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QPaintEngine::updateState(const QPaintEngineState&  state)
{
    QScriptValue _q_function = __qtscript_self.property("updateState");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateState") & QScriptValue::QObjectMember)) {
        qFatal("QPaintEngine::updateState() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, state));
    }
}

