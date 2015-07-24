#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qpainter.h>
#include <QPainterPath>
#include <QPixmap>
#include <QVariant>
#include <QWidget>
#include <qbrush.h>
#include <qcolor.h>
#include <qfont.h>
#include <qimage.h>
#include <qline.h>
#include <qmatrix.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpen.h>
#include <qpicture.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qtransform.h>
#include <qvector.h>

static const char * const qtscript_QPainter_function_names[] = {
    "QPainter"
    // static
    , "redirected"
    , "restoreRedirected"
    , "setRedirected"
    // prototype
    , "background"
    , "backgroundMode"
    , "begin"
    , "beginNativePainting"
    , "boundingRect"
    , "brush"
    , "brushOrigin"
    , "clipBoundingRect"
    , "clipPath"
    , "clipRegion"
    , "combinedMatrix"
    , "combinedTransform"
    , "compositionMode"
    , "device"
    , "deviceMatrix"
    , "deviceTransform"
    , "drawArc"
    , "drawChord"
    , "drawConvexPolygon"
    , "drawEllipse"
    , "drawImage"
    , "drawLine"
    , "drawLines"
    , "drawLinesF"
    , "drawLinesFromPoints"
    , "drawLinesFromPointsF"
    , "drawPath"
    , "drawPicture"
    , "drawPie"
    , "drawPixmap"
    , "drawPoint"
    , "drawPoints"
    , "drawPolygon"
    , "drawPolyline"
    , "drawRect"
    , "drawRects"
    , "drawRectsF"
    , "drawRoundRect"
    , "drawRoundedRect"
    , "drawText"
    , "drawTextItem"
    , "drawTiledPixmap"
    , "end"
    , "endNativePainting"
    , "eraseRect"
    , "fillPath"
    , "fillRect"
    , "font"
    , "hasClipping"
    , "initFrom"
    , "isActive"
    , "layoutDirection"
    , "opacity"
    , "paintEngine"
    , "pen"
    , "renderHints"
    , "resetMatrix"
    , "resetTransform"
    , "restore"
    , "rotate"
    , "save"
    , "scale"
    , "setBackground"
    , "setBackgroundMode"
    , "setBrush"
    , "setBrushOrigin"
    , "setClipPath"
    , "setClipRect"
    , "setClipRegion"
    , "setClipping"
    , "setCompositionMode"
    , "setFont"
    , "setLayoutDirection"
    , "setOpacity"
    , "setPen"
    , "setRenderHint"
    , "setRenderHints"
    , "setTransform"
    , "setViewTransformEnabled"
    , "setViewport"
    , "setWindow"
    , "setWorldMatrix"
    , "setWorldMatrixEnabled"
    , "setWorldTransform"
    , "shear"
    , "strokePath"
    , "testRenderHint"
    , "transform"
    , "translate"
    , "viewTransformEnabled"
    , "viewport"
    , "window"
    , "worldMatrix"
    , "worldMatrixEnabled"
    , "worldTransform"
    , "toString"
};

static const char * const qtscript_QPainter_function_signatures[] = {
    ""
    // static
    , "QPaintDevice device, QPoint offset"
    , "QPaintDevice device"
    , "QPaintDevice device, QPaintDevice replacement, QPoint offset"
    // prototype
    , ""
    , ""
    , "QPaintDevice arg__1"
    , ""
    , "QRect rect, int flags, String text\nQRectF rect, String text, QTextOption o\nQRectF rect, int flags, String text\nint x, int y, int w, int h, int flags, String text"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QRect arg__1, int a, int alen\nQRectF rect, int a, int alen\nint x, int y, int w, int h, int a, int alen"
    , "QRect arg__1, int a, int alen\nQRectF rect, int a, int alen\nint x, int y, int w, int h, int a, int alen"
    , "QPolygon polygon\nQPolygonF polygon"
    , "QPoint center, int rx, int ry\nQPointF center, qreal rx, qreal ry\nQRect r\nQRectF r\nint x, int y, int w, int h"
    , "QPoint p, QImage image\nQPoint p, QImage image, QRect sr, ImageConversionFlags flags\nQPointF p, QImage image\nQPointF p, QImage image, QRectF sr, ImageConversionFlags flags\nQRect r, QImage image\nQRect targetRect, QImage image, QRect sourceRect, ImageConversionFlags flags\nQRectF r, QImage image\nQRectF targetRect, QImage image, QRectF sourceRect, ImageConversionFlags flags\nint x, int y, QImage image, int sx, int sy, int sw, int sh, ImageConversionFlags flags"
    , "QLine line\nQLineF line\nQPoint p1, QPoint p2\nQPointF p1, QPointF p2\nint x1, int y1, int x2, int y2"
    , "List lines"
    , "List lines"
    , "List pointPairs"
    , "List pointPairs"
    , "QPainterPath path"
    , "QPoint p, QPicture picture\nQPointF p, QPicture picture\nint x, int y, QPicture picture"
    , "QRect arg__1, int a, int alen\nQRectF rect, int a, int alen\nint x, int y, int w, int h, int a, int alen"
    , "QPoint p, QPixmap pm\nQPoint p, QPixmap pm, QRect sr\nQPointF p, QPixmap pm\nQPointF p, QPixmap pm, QRectF sr\nQRect r, QPixmap pm\nQRect targetRect, QPixmap pixmap, QRect sourceRect\nQRectF targetRect, QPixmap pixmap, QRectF sourceRect\nint x, int y, QPixmap pm\nint x, int y, QPixmap pm, int sx, int sy, int sw, int sh\nint x, int y, int w, int h, QPixmap pm\nint x, int y, int w, int h, QPixmap pm, int sx, int sy, int sw, int sh"
    , "QPoint p\nQPointF pt\nint x, int y"
    , "QPolygon points\nQPolygonF points"
    , "QPolygon polygon, FillRule fillRule\nQPolygonF polygon, FillRule fillRule"
    , "QPolygon polygon\nQPolygonF polyline"
    , "QRect rect\nQRectF rect\nint x1, int y1, int w, int h"
    , "List rectangles"
    , "List rectangles"
    , "QRect r, int xround, int yround\nQRectF r, int xround, int yround\nint x, int y, int w, int h, int arg__5, int arg__6"
    , "QRect rect, qreal xRadius, qreal yRadius, SizeMode mode\nQRectF rect, qreal xRadius, qreal yRadius, SizeMode mode\nint x, int y, int w, int h, qreal xRadius, qreal yRadius, SizeMode mode"
    , "QPoint p, String s\nQPointF p, String s\nQRect r, int flags, String text, QRect br\nQRectF r, String text, QTextOption o\nQRectF r, int flags, String text, QRectF br\nint x, int y, String s\nint x, int y, int w, int h, int flags, String text, QRect br"
    , "QPoint p, QTextItem ti\nQPointF p, QTextItem ti\nint x, int y, QTextItem ti"
    , "QRect arg__1, QPixmap arg__2, QPoint arg__3\nQRectF rect, QPixmap pm, QPointF offset\nint x, int y, int w, int h, QPixmap arg__5, int sx, int sy"
    , ""
    , ""
    , "QRect arg__1\nQRectF arg__1\nint x, int y, int w, int h"
    , "QPainterPath path, QBrush brush"
    , "QRect arg__1, QBrush arg__2\nQRect arg__1, QColor color\nQRect r, BrushStyle style\nQRect r, GlobalColor c\nQRectF arg__1, QBrush arg__2\nQRectF arg__1, QColor color\nQRectF r, BrushStyle style\nQRectF r, GlobalColor c\nint x, int y, int w, int h, BrushStyle style\nint x, int y, int w, int h, GlobalColor c\nint x, int y, int w, int h, QBrush arg__5\nint x, int y, int w, int h, QColor color"
    , ""
    , ""
    , "QPaintDevice device"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "qreal a"
    , ""
    , "qreal sx, qreal sy"
    , "QBrush bg"
    , "BGMode mode"
    , "BrushStyle style\nQBrush brush"
    , "QPoint arg__1\nQPointF arg__1\nint x, int y"
    , "QPainterPath path, ClipOperation op"
    , "QRect arg__1, ClipOperation op\nQRectF arg__1, ClipOperation op\nint x, int y, int w, int h, ClipOperation op"
    , "QRegion arg__1, ClipOperation op"
    , "bool enable"
    , "CompositionMode mode"
    , "QFont f"
    , "LayoutDirection direction"
    , "qreal opacity"
    , "PenStyle style\nQColor color\nQPen pen"
    , "RenderHint hint, bool on"
    , "RenderHints hints, bool on"
    , "QTransform transform, bool combine"
    , "bool enable"
    , "QRect viewport\nint x, int y, int w, int h"
    , "QRect window\nint x, int y, int w, int h"
    , "QMatrix matrix, bool combine"
    , "bool enabled"
    , "QTransform matrix, bool combine"
    , "qreal sh, qreal sv"
    , "QPainterPath path, QPen pen"
    , "RenderHint hint"
    , ""
    , "QPoint offset\nQPointF offset\nqreal dx, qreal dy"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QPainter_function_lengths[] = {
    0
    // static
    , 2
    , 1
    , 3
    // prototype
    , 0
    , 0
    , 1
    , 0
    , 6
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 6
    , 6
    , 1
    , 4
    , 8
    , 4
    , 1
    , 1
    , 1
    , 1
    , 1
    , 3
    , 6
    , 9
    , 2
    , 1
    , 2
    , 1
    , 4
    , 1
    , 1
    , 6
    , 7
    , 7
    , 3
    , 7
    , 0
    , 0
    , 4
    , 2
    , 5
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 2
    , 1
    , 1
    , 1
    , 2
    , 2
    , 5
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 2
    , 1
    , 4
    , 4
    , 2
    , 1
    , 2
    , 2
    , 2
    , 1
    , 0
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QPainter_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPainter::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QPainter::RenderHint)
Q_DECLARE_METATYPE(QFlags<QPainter::RenderHint>)
Q_DECLARE_METATYPE(QPainter::CompositionMode)
Q_DECLARE_METATYPE(QPainter::PixmapFragmentHint)
Q_DECLARE_METATYPE(Qt::BGMode)
Q_DECLARE_METATYPE(QPaintDevice*)
Q_DECLARE_METATYPE(QTextOption)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QFlags<Qt::ImageConversionFlag>)
Q_DECLARE_METATYPE(QVector<QLine >)
Q_DECLARE_METATYPE(QVector<QLineF >)
Q_DECLARE_METATYPE(QVector<QPoint >)
Q_DECLARE_METATYPE(QVector<QPointF >)
Q_DECLARE_METATYPE(QPicture)
Q_DECLARE_METATYPE(Qt::FillRule)
Q_DECLARE_METATYPE(QVector<QRect >)
Q_DECLARE_METATYPE(QVector<QRectF >)
Q_DECLARE_METATYPE(Qt::SizeMode)
Q_DECLARE_METATYPE(QRect*)
Q_DECLARE_METATYPE(QRectF*)
Q_DECLARE_METATYPE(QTextItem)
Q_DECLARE_METATYPE(Qt::BrushStyle)
Q_DECLARE_METATYPE(Qt::GlobalColor)
Q_DECLARE_METATYPE(const QPaintDevice*)
Q_DECLARE_METATYPE(Qt::LayoutDirection)
Q_DECLARE_METATYPE(QPaintEngine*)
Q_DECLARE_METATYPE(Qt::ClipOperation)
Q_DECLARE_METATYPE(Qt::PenStyle)
Q_DECLARE_METATYPE(QPoint*)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QPainter::RenderHint
//

static const QPainter::RenderHint qtscript_QPainter_RenderHint_values[] = {
    QPainter::Antialiasing
    , QPainter::TextAntialiasing
    , QPainter::SmoothPixmapTransform
    , QPainter::HighQualityAntialiasing
    , QPainter::NonCosmeticDefaultPen
    , QPainter::Qt4CompatiblePainting
};

static const char * const qtscript_QPainter_RenderHint_keys[] = {
    "Antialiasing"
    , "TextAntialiasing"
    , "SmoothPixmapTransform"
    , "HighQualityAntialiasing"
    , "NonCosmeticDefaultPen"
    , "Qt4CompatiblePainting"
};

static QString qtscript_QPainter_RenderHint_toStringHelper(QPainter::RenderHint value)
{
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QPainter_RenderHint_values[i] == value)
            return QString::fromLatin1(qtscript_QPainter_RenderHint_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QPainter_RenderHint_toScriptValue(QScriptEngine *engine, const QPainter::RenderHint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPainter"));
    return clazz.property(qtscript_QPainter_RenderHint_toStringHelper(value));
}

static void qtscript_QPainter_RenderHint_fromScriptValue(const QScriptValue &value, QPainter::RenderHint &out)
{
    out = qvariant_cast<QPainter::RenderHint>(value.toVariant());
}

static QScriptValue qtscript_construct_QPainter_RenderHint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QPainter_RenderHint_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QPainter::RenderHint>(arg));
    }
    return context->throwError(QString::fromLatin1("RenderHint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPainter_RenderHint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPainter::RenderHint value = qscriptvalue_cast<QPainter::RenderHint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPainter_RenderHint_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPainter::RenderHint value = qscriptvalue_cast<QPainter::RenderHint>(context->thisObject());
    return QScriptValue(engine, qtscript_QPainter_RenderHint_toStringHelper(value));
}

static QScriptValue qtscript_create_QPainter_RenderHint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPainter_RenderHint,
        qtscript_QPainter_RenderHint_valueOf, qtscript_QPainter_RenderHint_toString);
    qScriptRegisterMetaType<QPainter::RenderHint>(engine, qtscript_QPainter_RenderHint_toScriptValue,
        qtscript_QPainter_RenderHint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPainter_RenderHint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPainter_RenderHint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPainter::RenderHints
//

static QScriptValue qtscript_QPainter_RenderHints_toScriptValue(QScriptEngine *engine, const QPainter::RenderHints &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QPainter_RenderHints_fromScriptValue(const QScriptValue &value, QPainter::RenderHints &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QPainter::RenderHints>())
        out = qvariant_cast<QPainter::RenderHints>(var);
    else if (var.userType() == qMetaTypeId<QPainter::RenderHint>())
        out = qvariant_cast<QPainter::RenderHint>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QPainter_RenderHints(QScriptContext *context, QScriptEngine *engine)
{
    QPainter::RenderHints result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QPainter::RenderHints>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QPainter::RenderHint>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("RenderHints(): argument %0 is not of type RenderHint").arg(i));
            }
            result |= qvariant_cast<QPainter::RenderHint>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QPainter_RenderHints_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPainter::RenderHints value = qscriptvalue_cast<QPainter::RenderHints>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPainter_RenderHints_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPainter::RenderHints value = qscriptvalue_cast<QPainter::RenderHints>(context->thisObject());
    QString result;
    for (int i = 0; i < 6; ++i) {
        if ((value & qtscript_QPainter_RenderHint_values[i]) == qtscript_QPainter_RenderHint_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QPainter_RenderHint_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QPainter_RenderHints_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QPainter::RenderHints>() == otherObj.value<QPainter::RenderHints>())));
}

static QScriptValue qtscript_create_QPainter_RenderHints_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QPainter_RenderHints, qtscript_QPainter_RenderHints_valueOf,
        qtscript_QPainter_RenderHints_toString, qtscript_QPainter_RenderHints_equals);
    qScriptRegisterMetaType<QPainter::RenderHints>(engine, qtscript_QPainter_RenderHints_toScriptValue,
        qtscript_QPainter_RenderHints_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QPainter::CompositionMode
//

static const QPainter::CompositionMode qtscript_QPainter_CompositionMode_values[] = {
    QPainter::CompositionMode_SourceOver
    , QPainter::CompositionMode_DestinationOver
    , QPainter::CompositionMode_Clear
    , QPainter::CompositionMode_Source
    , QPainter::CompositionMode_Destination
    , QPainter::CompositionMode_SourceIn
    , QPainter::CompositionMode_DestinationIn
    , QPainter::CompositionMode_SourceOut
    , QPainter::CompositionMode_DestinationOut
    , QPainter::CompositionMode_SourceAtop
    , QPainter::CompositionMode_DestinationAtop
    , QPainter::CompositionMode_Xor
    , QPainter::CompositionMode_Plus
    , QPainter::CompositionMode_Multiply
    , QPainter::CompositionMode_Screen
    , QPainter::CompositionMode_Overlay
    , QPainter::CompositionMode_Darken
    , QPainter::CompositionMode_Lighten
    , QPainter::CompositionMode_ColorDodge
    , QPainter::CompositionMode_ColorBurn
    , QPainter::CompositionMode_HardLight
    , QPainter::CompositionMode_SoftLight
    , QPainter::CompositionMode_Difference
    , QPainter::CompositionMode_Exclusion
    , QPainter::RasterOp_SourceOrDestination
    , QPainter::RasterOp_SourceAndDestination
    , QPainter::RasterOp_SourceXorDestination
    , QPainter::RasterOp_NotSourceAndNotDestination
    , QPainter::RasterOp_NotSourceOrNotDestination
    , QPainter::RasterOp_NotSourceXorDestination
    , QPainter::RasterOp_NotSource
    , QPainter::RasterOp_NotSourceAndDestination
    , QPainter::RasterOp_SourceAndNotDestination
    , QPainter::RasterOp_NotSourceOrDestination
    , QPainter::RasterOp_SourceOrNotDestination
    , QPainter::RasterOp_ClearDestination
    , QPainter::RasterOp_SetDestination
    , QPainter::RasterOp_NotDestination
};

static const char * const qtscript_QPainter_CompositionMode_keys[] = {
    "CompositionMode_SourceOver"
    , "CompositionMode_DestinationOver"
    , "CompositionMode_Clear"
    , "CompositionMode_Source"
    , "CompositionMode_Destination"
    , "CompositionMode_SourceIn"
    , "CompositionMode_DestinationIn"
    , "CompositionMode_SourceOut"
    , "CompositionMode_DestinationOut"
    , "CompositionMode_SourceAtop"
    , "CompositionMode_DestinationAtop"
    , "CompositionMode_Xor"
    , "CompositionMode_Plus"
    , "CompositionMode_Multiply"
    , "CompositionMode_Screen"
    , "CompositionMode_Overlay"
    , "CompositionMode_Darken"
    , "CompositionMode_Lighten"
    , "CompositionMode_ColorDodge"
    , "CompositionMode_ColorBurn"
    , "CompositionMode_HardLight"
    , "CompositionMode_SoftLight"
    , "CompositionMode_Difference"
    , "CompositionMode_Exclusion"
    , "RasterOp_SourceOrDestination"
    , "RasterOp_SourceAndDestination"
    , "RasterOp_SourceXorDestination"
    , "RasterOp_NotSourceAndNotDestination"
    , "RasterOp_NotSourceOrNotDestination"
    , "RasterOp_NotSourceXorDestination"
    , "RasterOp_NotSource"
    , "RasterOp_NotSourceAndDestination"
    , "RasterOp_SourceAndNotDestination"
    , "RasterOp_NotSourceOrDestination"
    , "RasterOp_SourceOrNotDestination"
    , "RasterOp_ClearDestination"
    , "RasterOp_SetDestination"
    , "RasterOp_NotDestination"
};

static QString qtscript_QPainter_CompositionMode_toStringHelper(QPainter::CompositionMode value)
{
    if ((value >= QPainter::CompositionMode_SourceOver) && (value <= QPainter::RasterOp_NotDestination))
        return qtscript_QPainter_CompositionMode_keys[static_cast<int>(value)-static_cast<int>(QPainter::CompositionMode_SourceOver)];
    return QString();
}

static QScriptValue qtscript_QPainter_CompositionMode_toScriptValue(QScriptEngine *engine, const QPainter::CompositionMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPainter"));
    return clazz.property(qtscript_QPainter_CompositionMode_toStringHelper(value));
}

static void qtscript_QPainter_CompositionMode_fromScriptValue(const QScriptValue &value, QPainter::CompositionMode &out)
{
    out = qvariant_cast<QPainter::CompositionMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QPainter_CompositionMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPainter::CompositionMode_SourceOver) && (arg <= QPainter::RasterOp_NotDestination))
        return qScriptValueFromValue(engine,  static_cast<QPainter::CompositionMode>(arg));
    return context->throwError(QString::fromLatin1("CompositionMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPainter_CompositionMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPainter::CompositionMode value = qscriptvalue_cast<QPainter::CompositionMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPainter_CompositionMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPainter::CompositionMode value = qscriptvalue_cast<QPainter::CompositionMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QPainter_CompositionMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QPainter_CompositionMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPainter_CompositionMode,
        qtscript_QPainter_CompositionMode_valueOf, qtscript_QPainter_CompositionMode_toString);
    qScriptRegisterMetaType<QPainter::CompositionMode>(engine, qtscript_QPainter_CompositionMode_toScriptValue,
        qtscript_QPainter_CompositionMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 38; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPainter_CompositionMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPainter_CompositionMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPainter::PixmapFragmentHint
//

static const QPainter::PixmapFragmentHint qtscript_QPainter_PixmapFragmentHint_values[] = {
    QPainter::OpaqueHint
};

static const char * const qtscript_QPainter_PixmapFragmentHint_keys[] = {
    "OpaqueHint"
};

static QString qtscript_QPainter_PixmapFragmentHint_toStringHelper(QPainter::PixmapFragmentHint value)
{
    if ((value >= QPainter::OpaqueHint) && (value <= QPainter::OpaqueHint))
        return qtscript_QPainter_PixmapFragmentHint_keys[static_cast<int>(value)-static_cast<int>(QPainter::OpaqueHint)];
    return QString();
}

static QScriptValue qtscript_QPainter_PixmapFragmentHint_toScriptValue(QScriptEngine *engine, const QPainter::PixmapFragmentHint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPainter"));
    return clazz.property(qtscript_QPainter_PixmapFragmentHint_toStringHelper(value));
}

static void qtscript_QPainter_PixmapFragmentHint_fromScriptValue(const QScriptValue &value, QPainter::PixmapFragmentHint &out)
{
    out = qvariant_cast<QPainter::PixmapFragmentHint>(value.toVariant());
}

static QScriptValue qtscript_construct_QPainter_PixmapFragmentHint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPainter::OpaqueHint) && (arg <= QPainter::OpaqueHint))
        return qScriptValueFromValue(engine,  static_cast<QPainter::PixmapFragmentHint>(arg));
    return context->throwError(QString::fromLatin1("PixmapFragmentHint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPainter_PixmapFragmentHint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPainter::PixmapFragmentHint value = qscriptvalue_cast<QPainter::PixmapFragmentHint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPainter_PixmapFragmentHint_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPainter::PixmapFragmentHint value = qscriptvalue_cast<QPainter::PixmapFragmentHint>(context->thisObject());
    return QScriptValue(engine, qtscript_QPainter_PixmapFragmentHint_toStringHelper(value));
}

static QScriptValue qtscript_create_QPainter_PixmapFragmentHint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPainter_PixmapFragmentHint,
        qtscript_QPainter_PixmapFragmentHint_valueOf, qtscript_QPainter_PixmapFragmentHint_toString);
    qScriptRegisterMetaType<QPainter::PixmapFragmentHint>(engine, qtscript_QPainter_PixmapFragmentHint_toScriptValue,
        qtscript_QPainter_PixmapFragmentHint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPainter_PixmapFragmentHint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPainter_PixmapFragmentHint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPainter
//

static QScriptValue qtscript_QPainter_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 95;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPainter* _q_self = qscriptvalue_cast<QPainter*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPainter.%0(): this object is not a QPainter")
            .arg(qtscript_QPainter_function_names[_id+4]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        const QBrush& _q_result = _q_self->background();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        Qt::BGMode _q_result = _q_self->backgroundMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {

        // TEMPLATE - core.convert_pointer_arg_and_check_null - START
          QPaintDevice* _q_arg0 = qscriptvalue_cast<QPaintDevice*>(context->argument(0));
          if (!_q_arg0) {
              return context->throwError(QScriptContext::TypeError,
                                         QString::fromLatin1("QPainter::begin(): failed to convert argument to QPaintDevice*"));
          }
    // TEMPLATE - core.convert_pointer_arg_and_check_null - END
                bool _q_result = _q_self->begin(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->beginNativePainting();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QRectF _q_result = _q_self->boundingRect(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isString()) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QString _q_arg2 = context->argument(2).toString();
            QRect _q_result = _q_self->boundingRect(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()
            && (qMetaTypeId<QTextOption>() == context->argument(2).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QTextOption _q_arg2 = qscriptvalue_cast<QTextOption>(context->argument(2));
            QRectF _q_result = _q_self->boundingRect(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isString()) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QString _q_arg2 = context->argument(2).toString();
            QRectF _q_result = _q_self->boundingRect(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 6) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        QString _q_arg5 = context->argument(5).toString();
        QRect _q_result = _q_self->boundingRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        const QBrush& _q_result = _q_self->brush();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->brushOrigin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->clipBoundingRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QPainterPath _q_result = _q_self->clipPath();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QRegion _q_result = _q_self->clipRegion();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QMatrix _q_result = _q_self->combinedMatrix();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QTransform _q_result = _q_self->combinedTransform();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QPainter::CompositionMode _q_result = _q_self->compositionMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QPaintDevice* _q_result = _q_self->device();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        const QMatrix& _q_result = _q_self->deviceMatrix();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        const QTransform& _q_result = _q_self->deviceTransform();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->drawArc(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->drawArc(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 6) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        _q_self->drawArc(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->drawChord(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->drawChord(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 6) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        _q_self->drawChord(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPolygon>() == context->argument(0).toVariant().userType())) {
            QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
            _q_self->drawConvexPolygon(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            _q_self->drawConvexPolygon(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            _q_self->drawEllipse(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            _q_self->drawEllipse(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->drawEllipse(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(2).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
            qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
            _q_self->drawEllipse(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->drawEllipse(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage>() == context->argument(1).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
            _q_self->drawImage(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage>() == context->argument(1).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
            _q_self->drawImage(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage>() == context->argument(1).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
            _q_self->drawImage(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage>() == context->argument(1).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
            _q_self->drawImage(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRect>() == context->argument(2).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
            QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
            _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRectF>() == context->argument(2).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
            QRectF _q_arg2 = qscriptvalue_cast<QRectF>(context->argument(2));
            _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRect>() == context->argument(2).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
            QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
            _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRectF>() == context->argument(2).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
            QRectF _q_arg2 = qscriptvalue_cast<QRectF>(context->argument(2));
            _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && (qMetaTypeId<QImage>() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QImage _q_arg2 = qscriptvalue_cast<QImage>(context->argument(2));
            _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRect>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QFlags<Qt::ImageConversionFlag> >() == context->argument(3).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
            QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
            QFlags<Qt::ImageConversionFlag> _q_arg3 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(3));
            _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRectF>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QFlags<Qt::ImageConversionFlag> >() == context->argument(3).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
            QRectF _q_arg2 = qscriptvalue_cast<QRectF>(context->argument(2));
            QFlags<Qt::ImageConversionFlag> _q_arg3 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(3));
            _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRect>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QFlags<Qt::ImageConversionFlag> >() == context->argument(3).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
            QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
            QFlags<Qt::ImageConversionFlag> _q_arg3 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(3));
            _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QImage>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRectF>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QFlags<Qt::ImageConversionFlag> >() == context->argument(3).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
            QRectF _q_arg2 = qscriptvalue_cast<QRectF>(context->argument(2));
            QFlags<Qt::ImageConversionFlag> _q_arg3 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(3));
            _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && (qMetaTypeId<QImage>() == context->argument(2).toVariant().userType())
            && context->argument(3).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QImage _q_arg2 = qscriptvalue_cast<QImage>(context->argument(2));
            int _q_arg3 = context->argument(3).toInt32();
            _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 5) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QImage _q_arg2 = qscriptvalue_cast<QImage>(context->argument(2));
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QImage _q_arg2 = qscriptvalue_cast<QImage>(context->argument(2));
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 7) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QImage _q_arg2 = qscriptvalue_cast<QImage>(context->argument(2));
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        int _q_arg6 = context->argument(6).toInt32();
        _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 8) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QImage _q_arg2 = qscriptvalue_cast<QImage>(context->argument(2));
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        int _q_arg6 = context->argument(6).toInt32();
        QFlags<Qt::ImageConversionFlag> _q_arg7 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(7));
        _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QLine>() == context->argument(0).toVariant().userType())) {
            QLine _q_arg0 = qscriptvalue_cast<QLine>(context->argument(0));
            _q_self->drawLine(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QLineF>() == context->argument(0).toVariant().userType())) {
            QLineF _q_arg0 = qscriptvalue_cast<QLineF>(context->argument(0));
            _q_self->drawLine(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPoint>() == context->argument(1).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
            _q_self->drawLine(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPointF>() == context->argument(1).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
            _q_self->drawLine(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->drawLine(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QVector<QLine> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->drawLines(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QVector<QLineF> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->drawLines(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QVector<QPoint> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->drawLines(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QVector<QPointF> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->drawLines(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        _q_self->drawPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPicture>() == context->argument(1).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QPicture _q_arg1 = qscriptvalue_cast<QPicture>(context->argument(1));
            _q_self->drawPicture(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPicture>() == context->argument(1).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPicture _q_arg1 = qscriptvalue_cast<QPicture>(context->argument(1));
            _q_self->drawPicture(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QPicture _q_arg2 = qscriptvalue_cast<QPicture>(context->argument(2));
        _q_self->drawPicture(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->drawPie(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->drawPie(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 6) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        _q_self->drawPie(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            _q_self->drawPixmap(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            _q_self->drawPixmap(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            _q_self->drawPixmap(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRect>() == context->argument(2).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
            _q_self->drawPixmap(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRectF>() == context->argument(2).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            QRectF _q_arg2 = qscriptvalue_cast<QRectF>(context->argument(2));
            _q_self->drawPixmap(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRect>() == context->argument(2).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
            _q_self->drawPixmap(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRectF>() == context->argument(2).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            QRectF _q_arg2 = qscriptvalue_cast<QRectF>(context->argument(2));
            _q_self->drawPixmap(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && (qMetaTypeId<QPixmap>() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QPixmap _q_arg2 = qscriptvalue_cast<QPixmap>(context->argument(2));
            _q_self->drawPixmap(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 5) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QPixmap _q_arg4 = qscriptvalue_cast<QPixmap>(context->argument(4));
        _q_self->drawPixmap(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 7) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QPixmap _q_arg2 = qscriptvalue_cast<QPixmap>(context->argument(2));
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        int _q_arg6 = context->argument(6).toInt32();
        _q_self->drawPixmap(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 9) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QPixmap _q_arg4 = qscriptvalue_cast<QPixmap>(context->argument(4));
        int _q_arg5 = context->argument(5).toInt32();
        int _q_arg6 = context->argument(6).toInt32();
        int _q_arg7 = context->argument(7).toInt32();
        int _q_arg8 = context->argument(8).toInt32();
        _q_self->drawPixmap(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            _q_self->drawPoint(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            _q_self->drawPoint(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->drawPoint(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPolygon>() == context->argument(0).toVariant().userType())) {
            QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
            _q_self->drawPoints(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            _q_self->drawPoints(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPolygon>() == context->argument(0).toVariant().userType())) {
            QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
            _q_self->drawPolygon(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            _q_self->drawPolygon(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPolygon>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::FillRule>() == context->argument(1).toVariant().userType())) {
            QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
            Qt::FillRule _q_arg1 = qscriptvalue_cast<Qt::FillRule>(context->argument(1));
            _q_self->drawPolygon(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::FillRule>() == context->argument(1).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            Qt::FillRule _q_arg1 = qscriptvalue_cast<Qt::FillRule>(context->argument(1));
            _q_self->drawPolygon(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPolygon>() == context->argument(0).toVariant().userType())) {
            QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
            _q_self->drawPolyline(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            _q_self->drawPolyline(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            _q_self->drawRect(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            _q_self->drawRect(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->drawRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QVector<QRect> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->drawRects(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        QVector<QRectF> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->drawRects(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            _q_self->drawRoundRect(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            _q_self->drawRoundRect(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->drawRoundRect(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->drawRoundRect(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->drawRoundRect(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->drawRoundRect(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->drawRoundRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        _q_self->drawRoundRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        _q_self->drawRoundRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(2).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
            qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
            _q_self->drawRoundedRect(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(2).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
            qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
            _q_self->drawRoundedRect(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<Qt::SizeMode>() == context->argument(3).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
            qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
            Qt::SizeMode _q_arg3 = qscriptvalue_cast<Qt::SizeMode>(context->argument(3));
            _q_self->drawRoundedRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<qreal>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<Qt::SizeMode>() == context->argument(3).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
            qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
            Qt::SizeMode _q_arg3 = qscriptvalue_cast<Qt::SizeMode>(context->argument(3));
            _q_self->drawRoundedRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 6) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        _q_self->drawRoundedRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 7) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        Qt::SizeMode _q_arg6 = qscriptvalue_cast<Qt::SizeMode>(context->argument(6));
        _q_self->drawRoundedRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            _q_self->drawText(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            _q_self->drawText(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            _q_self->drawText(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()
            && (qMetaTypeId<QTextOption>() == context->argument(2).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QTextOption _q_arg2 = qscriptvalue_cast<QTextOption>(context->argument(2));
            _q_self->drawText(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isString()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QString _q_arg2 = context->argument(2).toString();
            _q_self->drawText(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isString()
            && qscriptvalue_cast<QRect*>(context->argument(3))) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QString _q_arg2 = context->argument(2).toString();
            QRect* _q_arg3 = qscriptvalue_cast<QRect*>(context->argument(3));
            _q_self->drawText(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isString()
            && qscriptvalue_cast<QRectF*>(context->argument(3))) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QString _q_arg2 = context->argument(2).toString();
            QRectF* _q_arg3 = qscriptvalue_cast<QRectF*>(context->argument(3));
            _q_self->drawText(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 7) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        QString _q_arg5 = context->argument(5).toString();
        QRect* _q_arg6 = qscriptvalue_cast<QRect*>(context->argument(6));
        _q_self->drawText(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QTextItem>() == context->argument(1).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QTextItem _q_arg1 = qscriptvalue_cast<QTextItem>(context->argument(1));
            _q_self->drawTextItem(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QTextItem>() == context->argument(1).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QTextItem _q_arg1 = qscriptvalue_cast<QTextItem>(context->argument(1));
            _q_self->drawTextItem(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QTextItem _q_arg2 = qscriptvalue_cast<QTextItem>(context->argument(2));
        _q_self->drawTextItem(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            _q_self->drawTiledPixmap(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            _q_self->drawTiledPixmap(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QPoint>() == context->argument(2).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            QPoint _q_arg2 = qscriptvalue_cast<QPoint>(context->argument(2));
            _q_self->drawTiledPixmap(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QPointF>() == context->argument(2).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            QPointF _q_arg2 = qscriptvalue_cast<QPointF>(context->argument(2));
            _q_self->drawTiledPixmap(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 5) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QPixmap _q_arg4 = qscriptvalue_cast<QPixmap>(context->argument(4));
        _q_self->drawTiledPixmap(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QPixmap _q_arg4 = qscriptvalue_cast<QPixmap>(context->argument(4));
        int _q_arg5 = context->argument(5).toInt32();
        _q_self->drawTiledPixmap(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 7) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QPixmap _q_arg4 = qscriptvalue_cast<QPixmap>(context->argument(4));
        int _q_arg5 = context->argument(5).toInt32();
        int _q_arg6 = context->argument(6).toInt32();
        _q_self->drawTiledPixmap(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->end();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 43:
    if (context->argumentCount() == 0) {
        _q_self->endNativePainting();
        return context->engine()->undefinedValue();
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            _q_self->eraseRect(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            _q_self->eraseRect(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->eraseRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 2) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QBrush _q_arg1 = qscriptvalue_cast<QBrush>(context->argument(1));
        _q_self->fillPath(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 46:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QBrush>() == context->argument(1).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QBrush _q_arg1 = qscriptvalue_cast<QBrush>(context->argument(1));
            _q_self->fillRect(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QColor>() == context->argument(1).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QColor _q_arg1 = qscriptvalue_cast<QColor>(context->argument(1));
            _q_self->fillRect(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::BrushStyle>() == context->argument(1).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            Qt::BrushStyle _q_arg1 = qscriptvalue_cast<Qt::BrushStyle>(context->argument(1));
            _q_self->fillRect(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::GlobalColor>() == context->argument(1).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            Qt::GlobalColor _q_arg1 = qscriptvalue_cast<Qt::GlobalColor>(context->argument(1));
            _q_self->fillRect(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QBrush>() == context->argument(1).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QBrush _q_arg1 = qscriptvalue_cast<QBrush>(context->argument(1));
            _q_self->fillRect(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QColor>() == context->argument(1).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QColor _q_arg1 = qscriptvalue_cast<QColor>(context->argument(1));
            _q_self->fillRect(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::BrushStyle>() == context->argument(1).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            Qt::BrushStyle _q_arg1 = qscriptvalue_cast<Qt::BrushStyle>(context->argument(1));
            _q_self->fillRect(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::GlobalColor>() == context->argument(1).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            Qt::GlobalColor _q_arg1 = qscriptvalue_cast<Qt::GlobalColor>(context->argument(1));
            _q_self->fillRect(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 5) {
        if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()
            && (qMetaTypeId<Qt::BrushStyle>() == context->argument(4).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            Qt::BrushStyle _q_arg4 = qscriptvalue_cast<Qt::BrushStyle>(context->argument(4));
            _q_self->fillRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()
            && (qMetaTypeId<Qt::GlobalColor>() == context->argument(4).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            Qt::GlobalColor _q_arg4 = qscriptvalue_cast<Qt::GlobalColor>(context->argument(4));
            _q_self->fillRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()
            && (qMetaTypeId<QBrush>() == context->argument(4).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            QBrush _q_arg4 = qscriptvalue_cast<QBrush>(context->argument(4));
            _q_self->fillRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()
            && (qMetaTypeId<QColor>() == context->argument(4).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            QColor _q_arg4 = qscriptvalue_cast<QColor>(context->argument(4));
            _q_self->fillRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {
        const QFont& _q_result = _q_self->font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasClipping();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 49:
    if (context->argumentCount() == 1) {
        const QPaintDevice* _q_arg0 = qscriptvalue_cast<const QPaintDevice*>(context->argument(0));
        _q_self->initFrom(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 50:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isActive();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 51:
    if (context->argumentCount() == 0) {
        Qt::LayoutDirection _q_result = _q_self->layoutDirection();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 52:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->opacity();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 53:
    if (context->argumentCount() == 0) {
        QPaintEngine* _q_result = _q_self->paintEngine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 54:
    if (context->argumentCount() == 0) {
        const QPen& _q_result = _q_self->pen();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 55:
    if (context->argumentCount() == 0) {
        QFlags<QPainter::RenderHint> _q_result = _q_self->renderHints();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 56:
    if (context->argumentCount() == 0) {
        _q_self->resetMatrix();
        return context->engine()->undefinedValue();
    }
    break;

    case 57:
    if (context->argumentCount() == 0) {
        _q_self->resetTransform();
        return context->engine()->undefinedValue();
    }
    break;

    case 58:
    if (context->argumentCount() == 0) {
        _q_self->restore();
        return context->engine()->undefinedValue();
    }
    break;

    case 59:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->rotate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 60:
    if (context->argumentCount() == 0) {
        _q_self->save();
        return context->engine()->undefinedValue();
    }
    break;

    case 61:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->scale(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 62:
    if (context->argumentCount() == 1) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        _q_self->setBackground(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 63:
    if (context->argumentCount() == 1) {
        Qt::BGMode _q_arg0 = qscriptvalue_cast<Qt::BGMode>(context->argument(0));
        _q_self->setBackgroundMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 64:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::BrushStyle>() == context->argument(0).toVariant().userType())) {
            Qt::BrushStyle _q_arg0 = qscriptvalue_cast<Qt::BrushStyle>(context->argument(0));
            _q_self->setBrush(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QBrush>() == context->argument(0).toVariant().userType())) {
            QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
            _q_self->setBrush(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 65:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            _q_self->setBrushOrigin(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            _q_self->setBrushOrigin(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setBrushOrigin(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 66:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        _q_self->setClipPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        Qt::ClipOperation _q_arg1 = qscriptvalue_cast<Qt::ClipOperation>(context->argument(1));
        _q_self->setClipPath(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 67:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            _q_self->setClipRect(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            _q_self->setClipRect(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ClipOperation>() == context->argument(1).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            Qt::ClipOperation _q_arg1 = qscriptvalue_cast<Qt::ClipOperation>(context->argument(1));
            _q_self->setClipRect(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ClipOperation>() == context->argument(1).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            Qt::ClipOperation _q_arg1 = qscriptvalue_cast<Qt::ClipOperation>(context->argument(1));
            _q_self->setClipRect(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setClipRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        Qt::ClipOperation _q_arg4 = qscriptvalue_cast<Qt::ClipOperation>(context->argument(4));
        _q_self->setClipRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    break;

    case 68:
    if (context->argumentCount() == 1) {
        QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
        _q_self->setClipRegion(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
        Qt::ClipOperation _q_arg1 = qscriptvalue_cast<Qt::ClipOperation>(context->argument(1));
        _q_self->setClipRegion(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 69:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setClipping(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 70:
    if (context->argumentCount() == 1) {
        QPainter::CompositionMode _q_arg0 = qscriptvalue_cast<QPainter::CompositionMode>(context->argument(0));
        _q_self->setCompositionMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 71:
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        _q_self->setFont(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 72:
    if (context->argumentCount() == 1) {
        Qt::LayoutDirection _q_arg0 = qscriptvalue_cast<Qt::LayoutDirection>(context->argument(0));
        _q_self->setLayoutDirection(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 73:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setOpacity(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 74:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::PenStyle>() == context->argument(0).toVariant().userType())) {
            Qt::PenStyle _q_arg0 = qscriptvalue_cast<Qt::PenStyle>(context->argument(0));
            _q_self->setPen(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QColor>() == context->argument(0).toVariant().userType())) {
            QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
            _q_self->setPen(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPen>() == context->argument(0).toVariant().userType())) {
            QPen _q_arg0 = qscriptvalue_cast<QPen>(context->argument(0));
            _q_self->setPen(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 75:
    if (context->argumentCount() == 1) {
        QPainter::RenderHint _q_arg0 = qscriptvalue_cast<QPainter::RenderHint>(context->argument(0));
        _q_self->setRenderHint(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QPainter::RenderHint _q_arg0 = qscriptvalue_cast<QPainter::RenderHint>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setRenderHint(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 76:
    if (context->argumentCount() == 1) {
        QFlags<QPainter::RenderHint> _q_arg0 = qscriptvalue_cast<QFlags<QPainter::RenderHint> >(context->argument(0));
        _q_self->setRenderHints(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QFlags<QPainter::RenderHint> _q_arg0 = qscriptvalue_cast<QFlags<QPainter::RenderHint> >(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setRenderHints(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 77:
    if (context->argumentCount() == 1) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        _q_self->setTransform(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setTransform(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 78:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setViewTransformEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 79:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        _q_self->setViewport(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setViewport(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 80:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        _q_self->setWindow(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setWindow(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 81:
    if (context->argumentCount() == 1) {
        QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
        _q_self->setWorldMatrix(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setWorldMatrix(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 82:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setWorldMatrixEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 83:
    if (context->argumentCount() == 1) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        _q_self->setWorldTransform(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setWorldTransform(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 84:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->shear(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 85:
    if (context->argumentCount() == 2) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPen _q_arg1 = qscriptvalue_cast<QPen>(context->argument(1));
        _q_self->strokePath(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 86:
    if (context->argumentCount() == 1) {
        QPainter::RenderHint _q_arg0 = qscriptvalue_cast<QPainter::RenderHint>(context->argument(0));
        bool _q_result = _q_self->testRenderHint(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 87:
    if (context->argumentCount() == 0) {
        const QTransform& _q_result = _q_self->transform();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 88:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            _q_self->translate(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            _q_self->translate(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->translate(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 89:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->viewTransformEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 90:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->viewport();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 91:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->window();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 92:
    if (context->argumentCount() == 0) {
        const QMatrix& _q_result = _q_self->worldMatrix();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 93:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->worldMatrixEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 94:
    if (context->argumentCount() == 0) {
        const QTransform& _q_result = _q_self->worldTransform();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 95: {
    QString result = QString::fromLatin1("QPainter");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPainter_throw_ambiguity_error_helper(context,
        qtscript_QPainter_function_names[_id+4],
        qtscript_QPainter_function_signatures[_id+4]);
}

static QScriptValue qtscript_QPainter_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPainter(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QPainter* _q_cpp_result = new QPainter();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        const QPaintDevice* _q_arg0 = qscriptvalue_cast<const QPaintDevice*>(context->argument(0));
        QPoint* _q_arg1 = qscriptvalue_cast<QPoint*>(context->argument(1));
        QPaintDevice* _q_result = QPainter::redirected(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        const QPaintDevice* _q_arg0 = qscriptvalue_cast<const QPaintDevice*>(context->argument(0));
        QPainter::restoreRedirected(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        const QPaintDevice* _q_arg0 = qscriptvalue_cast<const QPaintDevice*>(context->argument(0));
        QPaintDevice* _q_arg1 = qscriptvalue_cast<QPaintDevice*>(context->argument(1));
        QPainter::setRedirected(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        const QPaintDevice* _q_arg0 = qscriptvalue_cast<const QPaintDevice*>(context->argument(0));
        QPaintDevice* _q_arg1 = qscriptvalue_cast<QPaintDevice*>(context->argument(1));
        QPoint _q_arg2 = qscriptvalue_cast<QPoint>(context->argument(2));
        QPainter::setRedirected(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPainter_throw_ambiguity_error_helper(context,
        qtscript_QPainter_function_names[_id],
        qtscript_QPainter_function_signatures[_id]);
}

QScriptValue qtscript_create_QPainter_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPainter*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPainter*)0));
    for (int i = 0; i < 96; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPainter_prototype_call, qtscript_QPainter_function_lengths[i+4]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPainter_function_names[i+4]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPainter*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPainter_static_call, proto, qtscript_QPainter_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPainter_static_call,
            qtscript_QPainter_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QPainter_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("RenderHint"),
        qtscript_create_QPainter_RenderHint_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("RenderHints"),
        qtscript_create_QPainter_RenderHints_class(engine));
    ctor.setProperty(QString::fromLatin1("CompositionMode"),
        qtscript_create_QPainter_CompositionMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PixmapFragmentHint"),
        qtscript_create_QPainter_PixmapFragmentHint_class(engine, ctor));
    return ctor;
}
