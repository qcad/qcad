#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpaintengine.h>
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

#include "qtscriptshell_QPaintEngine.h"

static const char * const qtscript_QPaintEngine_function_names[] = {
    "QPaintEngine"
    // static
    // prototype
    , "begin"
    , "clearDirty"
    , "coordinateOffset"
    , "drawEllipse"
    , "drawImage"
    , "drawLines"
    , "drawPath"
    , "drawPixmap"
    , "drawPoints"
    , "drawPolygon"
    , "drawRects"
    , "drawTextItem"
    , "drawTiledPixmap"
    , "end"
    , "hasFeature"
    , "isActive"
    , "isExtended"
    , "paintDevice"
    , "painter"
    , "setActive"
    , "setDirty"
    , "setSystemClip"
    , "setSystemRect"
    , "syncState"
    , "systemClip"
    , "systemRect"
    , "testDirty"
    , "type"
    , "updateState"
    , "toString"
};

static const char * const qtscript_QPaintEngine_function_signatures[] = {
    "PaintEngineFeatures features"
    // static
    // prototype
    , "QPaintDevice pdev"
    , "DirtyFlags df"
    , ""
    , "QRect r\nQRectF r"
    , "QRectF r, QImage pm, QRectF sr, ImageConversionFlags flags"
    , "QLine lines, int lineCount\nQLineF lines, int lineCount"
    , "QPainterPath path"
    , "QRectF r, QPixmap pm, QRectF sr"
    , "QPoint points, int pointCount\nQPointF points, int pointCount"
    , "QPoint points, int pointCount, PolygonDrawMode mode\nQPointF points, int pointCount, PolygonDrawMode mode"
    , "QRect rects, int rectCount\nQRectF rects, int rectCount"
    , "QPointF p, QTextItem textItem"
    , "QRectF r, QPixmap pixmap, QPointF s"
    , ""
    , "PaintEngineFeatures feature"
    , ""
    , ""
    , ""
    , ""
    , "bool newState"
    , "DirtyFlags df"
    , "QRegion baseClip"
    , "QRect rect"
    , ""
    , ""
    , ""
    , "DirtyFlags df"
    , ""
    , "QPaintEngineState state"
""
};

static const int qtscript_QPaintEngine_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 0
    , 1
    , 4
    , 2
    , 1
    , 3
    , 2
    , 3
    , 2
    , 2
    , 3
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QPaintEngine_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPaintEngine::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPaintEngine*)
Q_DECLARE_METATYPE(QtScriptShell_QPaintEngine*)
Q_DECLARE_METATYPE(QPaintEngine::PolygonDrawMode)
Q_DECLARE_METATYPE(QPaintEngine::Type)
Q_DECLARE_METATYPE(QPaintEngine::PaintEngineFeature)
Q_DECLARE_METATYPE(QFlags<QPaintEngine::PaintEngineFeature>)
Q_DECLARE_METATYPE(QPaintEngine::DirtyFlag)
Q_DECLARE_METATYPE(QFlags<QPaintEngine::DirtyFlag>)
Q_DECLARE_METATYPE(QPaintDevice*)
Q_DECLARE_METATYPE(QFlags<Qt::ImageConversionFlag>)
Q_DECLARE_METATYPE(QLine*)
Q_DECLARE_METATYPE(QLineF*)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QPoint*)
Q_DECLARE_METATYPE(QPointF*)
Q_DECLARE_METATYPE(QRect*)
Q_DECLARE_METATYPE(QRectF*)
Q_DECLARE_METATYPE(QTextItem)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QPaintEngineState)

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
// QPaintEngine::PolygonDrawMode
//

static const QPaintEngine::PolygonDrawMode qtscript_QPaintEngine_PolygonDrawMode_values[] = {
    QPaintEngine::OddEvenMode
    , QPaintEngine::WindingMode
    , QPaintEngine::ConvexMode
    , QPaintEngine::PolylineMode
};

static const char * const qtscript_QPaintEngine_PolygonDrawMode_keys[] = {
    "OddEvenMode"
    , "WindingMode"
    , "ConvexMode"
    , "PolylineMode"
};

static QString qtscript_QPaintEngine_PolygonDrawMode_toStringHelper(QPaintEngine::PolygonDrawMode value)
{
    if ((value >= QPaintEngine::OddEvenMode) && (value <= QPaintEngine::PolylineMode))
        return qtscript_QPaintEngine_PolygonDrawMode_keys[static_cast<int>(value)-static_cast<int>(QPaintEngine::OddEvenMode)];
    return QString();
}

static QScriptValue qtscript_QPaintEngine_PolygonDrawMode_toScriptValue(QScriptEngine *engine, const QPaintEngine::PolygonDrawMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPaintEngine"));
    return clazz.property(qtscript_QPaintEngine_PolygonDrawMode_toStringHelper(value));
}

static void qtscript_QPaintEngine_PolygonDrawMode_fromScriptValue(const QScriptValue &value, QPaintEngine::PolygonDrawMode &out)
{
    out = qvariant_cast<QPaintEngine::PolygonDrawMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QPaintEngine_PolygonDrawMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPaintEngine::OddEvenMode) && (arg <= QPaintEngine::PolylineMode))
        return qScriptValueFromValue(engine,  static_cast<QPaintEngine::PolygonDrawMode>(arg));
    return context->throwError(QString::fromLatin1("PolygonDrawMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPaintEngine_PolygonDrawMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::PolygonDrawMode value = qscriptvalue_cast<QPaintEngine::PolygonDrawMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPaintEngine_PolygonDrawMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::PolygonDrawMode value = qscriptvalue_cast<QPaintEngine::PolygonDrawMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QPaintEngine_PolygonDrawMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QPaintEngine_PolygonDrawMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPaintEngine_PolygonDrawMode,
        qtscript_QPaintEngine_PolygonDrawMode_valueOf, qtscript_QPaintEngine_PolygonDrawMode_toString);
    qScriptRegisterMetaType<QPaintEngine::PolygonDrawMode>(engine, qtscript_QPaintEngine_PolygonDrawMode_toScriptValue,
        qtscript_QPaintEngine_PolygonDrawMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPaintEngine_PolygonDrawMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPaintEngine_PolygonDrawMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPaintEngine::Type
//

static const QPaintEngine::Type qtscript_QPaintEngine_Type_values[] = {
    QPaintEngine::X11
    , QPaintEngine::Windows
    , QPaintEngine::QuickDraw
    , QPaintEngine::CoreGraphics
    , QPaintEngine::MacPrinter
    , QPaintEngine::QWindowSystem
    , QPaintEngine::PostScript
    , QPaintEngine::OpenGL
    , QPaintEngine::Picture
    , QPaintEngine::SVG
    , QPaintEngine::Raster
    , QPaintEngine::Direct3D
    , QPaintEngine::Pdf
    , QPaintEngine::OpenVG
    , QPaintEngine::OpenGL2
    , QPaintEngine::PaintBuffer
    , QPaintEngine::Blitter
    , QPaintEngine::User
    , QPaintEngine::MaxUser
};

static const char * const qtscript_QPaintEngine_Type_keys[] = {
    "X11"
    , "Windows"
    , "QuickDraw"
    , "CoreGraphics"
    , "MacPrinter"
    , "QWindowSystem"
    , "PostScript"
    , "OpenGL"
    , "Picture"
    , "SVG"
    , "Raster"
    , "Direct3D"
    , "Pdf"
    , "OpenVG"
    , "OpenGL2"
    , "PaintBuffer"
    , "Blitter"
    , "User"
    , "MaxUser"
};

static QString qtscript_QPaintEngine_Type_toStringHelper(QPaintEngine::Type value)
{
    for (int i = 0; i < 19; ++i) {
        if (qtscript_QPaintEngine_Type_values[i] == value)
            return QString::fromLatin1(qtscript_QPaintEngine_Type_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QPaintEngine_Type_toScriptValue(QScriptEngine *engine, const QPaintEngine::Type &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPaintEngine"));
    return clazz.property(qtscript_QPaintEngine_Type_toStringHelper(value));
}

static void qtscript_QPaintEngine_Type_fromScriptValue(const QScriptValue &value, QPaintEngine::Type &out)
{
    out = qvariant_cast<QPaintEngine::Type>(value.toVariant());
}

static QScriptValue qtscript_construct_QPaintEngine_Type(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 19; ++i) {
        if (qtscript_QPaintEngine_Type_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QPaintEngine::Type>(arg));
    }
    return context->throwError(QString::fromLatin1("Type(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPaintEngine_Type_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::Type value = qscriptvalue_cast<QPaintEngine::Type>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPaintEngine_Type_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::Type value = qscriptvalue_cast<QPaintEngine::Type>(context->thisObject());
    return QScriptValue(engine, qtscript_QPaintEngine_Type_toStringHelper(value));
}

static QScriptValue qtscript_create_QPaintEngine_Type_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPaintEngine_Type,
        qtscript_QPaintEngine_Type_valueOf, qtscript_QPaintEngine_Type_toString);
    qScriptRegisterMetaType<QPaintEngine::Type>(engine, qtscript_QPaintEngine_Type_toScriptValue,
        qtscript_QPaintEngine_Type_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 19; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPaintEngine_Type_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPaintEngine_Type_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPaintEngine::PaintEngineFeature
//

static const QPaintEngine::PaintEngineFeature qtscript_QPaintEngine_PaintEngineFeature_values[] = {
    QPaintEngine::AllFeatures
    , QPaintEngine::PrimitiveTransform
    , QPaintEngine::PatternTransform
    , QPaintEngine::PixmapTransform
    , QPaintEngine::PatternBrush
    , QPaintEngine::LinearGradientFill
    , QPaintEngine::RadialGradientFill
    , QPaintEngine::ConicalGradientFill
    , QPaintEngine::AlphaBlend
    , QPaintEngine::PorterDuff
    , QPaintEngine::PainterPaths
    , QPaintEngine::Antialiasing
    , QPaintEngine::BrushStroke
    , QPaintEngine::ConstantOpacity
    , QPaintEngine::MaskedBrush
    , QPaintEngine::PerspectiveTransform
    , QPaintEngine::BlendModes
    , QPaintEngine::ObjectBoundingModeGradients
    , QPaintEngine::RasterOpModes
    , QPaintEngine::PaintOutsidePaintEvent
};

static const char * const qtscript_QPaintEngine_PaintEngineFeature_keys[] = {
    "AllFeatures"
    , "PrimitiveTransform"
    , "PatternTransform"
    , "PixmapTransform"
    , "PatternBrush"
    , "LinearGradientFill"
    , "RadialGradientFill"
    , "ConicalGradientFill"
    , "AlphaBlend"
    , "PorterDuff"
    , "PainterPaths"
    , "Antialiasing"
    , "BrushStroke"
    , "ConstantOpacity"
    , "MaskedBrush"
    , "PerspectiveTransform"
    , "BlendModes"
    , "ObjectBoundingModeGradients"
    , "RasterOpModes"
    , "PaintOutsidePaintEvent"
};

static QString qtscript_QPaintEngine_PaintEngineFeature_toStringHelper(QPaintEngine::PaintEngineFeature value)
{
    for (int i = 0; i < 20; ++i) {
        if (qtscript_QPaintEngine_PaintEngineFeature_values[i] == value)
            return QString::fromLatin1(qtscript_QPaintEngine_PaintEngineFeature_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QPaintEngine_PaintEngineFeature_toScriptValue(QScriptEngine *engine, const QPaintEngine::PaintEngineFeature &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPaintEngine"));
    return clazz.property(qtscript_QPaintEngine_PaintEngineFeature_toStringHelper(value));
}

static void qtscript_QPaintEngine_PaintEngineFeature_fromScriptValue(const QScriptValue &value, QPaintEngine::PaintEngineFeature &out)
{
    out = qvariant_cast<QPaintEngine::PaintEngineFeature>(value.toVariant());
}

static QScriptValue qtscript_construct_QPaintEngine_PaintEngineFeature(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 20; ++i) {
        if (qtscript_QPaintEngine_PaintEngineFeature_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QPaintEngine::PaintEngineFeature>(arg));
    }
    return context->throwError(QString::fromLatin1("PaintEngineFeature(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPaintEngine_PaintEngineFeature_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::PaintEngineFeature value = qscriptvalue_cast<QPaintEngine::PaintEngineFeature>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPaintEngine_PaintEngineFeature_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::PaintEngineFeature value = qscriptvalue_cast<QPaintEngine::PaintEngineFeature>(context->thisObject());
    return QScriptValue(engine, qtscript_QPaintEngine_PaintEngineFeature_toStringHelper(value));
}

static QScriptValue qtscript_create_QPaintEngine_PaintEngineFeature_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPaintEngine_PaintEngineFeature,
        qtscript_QPaintEngine_PaintEngineFeature_valueOf, qtscript_QPaintEngine_PaintEngineFeature_toString);
    qScriptRegisterMetaType<QPaintEngine::PaintEngineFeature>(engine, qtscript_QPaintEngine_PaintEngineFeature_toScriptValue,
        qtscript_QPaintEngine_PaintEngineFeature_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 20; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPaintEngine_PaintEngineFeature_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPaintEngine_PaintEngineFeature_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPaintEngine::PaintEngineFeatures
//

static QScriptValue qtscript_QPaintEngine_PaintEngineFeatures_toScriptValue(QScriptEngine *engine, const QPaintEngine::PaintEngineFeatures &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QPaintEngine_PaintEngineFeatures_fromScriptValue(const QScriptValue &value, QPaintEngine::PaintEngineFeatures &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QPaintEngine::PaintEngineFeatures>())
        out = qvariant_cast<QPaintEngine::PaintEngineFeatures>(var);
    else if (var.userType() == qMetaTypeId<QPaintEngine::PaintEngineFeature>())
        out = qvariant_cast<QPaintEngine::PaintEngineFeature>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QPaintEngine_PaintEngineFeatures(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::PaintEngineFeatures result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QPaintEngine::PaintEngineFeatures>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QPaintEngine::PaintEngineFeature>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("PaintEngineFeatures(): argument %0 is not of type PaintEngineFeature").arg(i));
            }
            result |= qvariant_cast<QPaintEngine::PaintEngineFeature>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QPaintEngine_PaintEngineFeatures_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::PaintEngineFeatures value = qscriptvalue_cast<QPaintEngine::PaintEngineFeatures>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPaintEngine_PaintEngineFeatures_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::PaintEngineFeatures value = qscriptvalue_cast<QPaintEngine::PaintEngineFeatures>(context->thisObject());
    QString result;
    for (int i = 0; i < 20; ++i) {
        if ((value & qtscript_QPaintEngine_PaintEngineFeature_values[i]) == qtscript_QPaintEngine_PaintEngineFeature_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QPaintEngine_PaintEngineFeature_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QPaintEngine_PaintEngineFeatures_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QPaintEngine::PaintEngineFeatures>() == otherObj.value<QPaintEngine::PaintEngineFeatures>())));
}

static QScriptValue qtscript_create_QPaintEngine_PaintEngineFeatures_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QPaintEngine_PaintEngineFeatures, qtscript_QPaintEngine_PaintEngineFeatures_valueOf,
        qtscript_QPaintEngine_PaintEngineFeatures_toString, qtscript_QPaintEngine_PaintEngineFeatures_equals);
    qScriptRegisterMetaType<QPaintEngine::PaintEngineFeatures>(engine, qtscript_QPaintEngine_PaintEngineFeatures_toScriptValue,
        qtscript_QPaintEngine_PaintEngineFeatures_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QPaintEngine::DirtyFlag
//

static const QPaintEngine::DirtyFlag qtscript_QPaintEngine_DirtyFlag_values[] = {
    QPaintEngine::DirtyPen
    , QPaintEngine::DirtyBrush
    , QPaintEngine::DirtyBrushOrigin
    , QPaintEngine::DirtyFont
    , QPaintEngine::DirtyBackground
    , QPaintEngine::DirtyBackgroundMode
    , QPaintEngine::DirtyTransform
    , QPaintEngine::DirtyClipRegion
    , QPaintEngine::DirtyClipPath
    , QPaintEngine::DirtyHints
    , QPaintEngine::DirtyCompositionMode
    , QPaintEngine::DirtyClipEnabled
    , QPaintEngine::DirtyOpacity
    , QPaintEngine::AllDirty
};

static const char * const qtscript_QPaintEngine_DirtyFlag_keys[] = {
    "DirtyPen"
    , "DirtyBrush"
    , "DirtyBrushOrigin"
    , "DirtyFont"
    , "DirtyBackground"
    , "DirtyBackgroundMode"
    , "DirtyTransform"
    , "DirtyClipRegion"
    , "DirtyClipPath"
    , "DirtyHints"
    , "DirtyCompositionMode"
    , "DirtyClipEnabled"
    , "DirtyOpacity"
    , "AllDirty"
};

static QString qtscript_QPaintEngine_DirtyFlag_toStringHelper(QPaintEngine::DirtyFlag value)
{
    for (int i = 0; i < 14; ++i) {
        if (qtscript_QPaintEngine_DirtyFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QPaintEngine_DirtyFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QPaintEngine_DirtyFlag_toScriptValue(QScriptEngine *engine, const QPaintEngine::DirtyFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPaintEngine"));
    return clazz.property(qtscript_QPaintEngine_DirtyFlag_toStringHelper(value));
}

static void qtscript_QPaintEngine_DirtyFlag_fromScriptValue(const QScriptValue &value, QPaintEngine::DirtyFlag &out)
{
    out = qvariant_cast<QPaintEngine::DirtyFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QPaintEngine_DirtyFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 14; ++i) {
        if (qtscript_QPaintEngine_DirtyFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QPaintEngine::DirtyFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("DirtyFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPaintEngine_DirtyFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::DirtyFlag value = qscriptvalue_cast<QPaintEngine::DirtyFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPaintEngine_DirtyFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::DirtyFlag value = qscriptvalue_cast<QPaintEngine::DirtyFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QPaintEngine_DirtyFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QPaintEngine_DirtyFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPaintEngine_DirtyFlag,
        qtscript_QPaintEngine_DirtyFlag_valueOf, qtscript_QPaintEngine_DirtyFlag_toString);
    qScriptRegisterMetaType<QPaintEngine::DirtyFlag>(engine, qtscript_QPaintEngine_DirtyFlag_toScriptValue,
        qtscript_QPaintEngine_DirtyFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 14; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPaintEngine_DirtyFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPaintEngine_DirtyFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPaintEngine::DirtyFlags
//

static QScriptValue qtscript_QPaintEngine_DirtyFlags_toScriptValue(QScriptEngine *engine, const QPaintEngine::DirtyFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QPaintEngine_DirtyFlags_fromScriptValue(const QScriptValue &value, QPaintEngine::DirtyFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QPaintEngine::DirtyFlags>())
        out = qvariant_cast<QPaintEngine::DirtyFlags>(var);
    else if (var.userType() == qMetaTypeId<QPaintEngine::DirtyFlag>())
        out = qvariant_cast<QPaintEngine::DirtyFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QPaintEngine_DirtyFlags(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::DirtyFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QPaintEngine::DirtyFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QPaintEngine::DirtyFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("DirtyFlags(): argument %0 is not of type DirtyFlag").arg(i));
            }
            result |= qvariant_cast<QPaintEngine::DirtyFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QPaintEngine_DirtyFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::DirtyFlags value = qscriptvalue_cast<QPaintEngine::DirtyFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPaintEngine_DirtyFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPaintEngine::DirtyFlags value = qscriptvalue_cast<QPaintEngine::DirtyFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 14; ++i) {
        if ((value & qtscript_QPaintEngine_DirtyFlag_values[i]) == qtscript_QPaintEngine_DirtyFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QPaintEngine_DirtyFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QPaintEngine_DirtyFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QPaintEngine::DirtyFlags>() == otherObj.value<QPaintEngine::DirtyFlags>())));
}

static QScriptValue qtscript_create_QPaintEngine_DirtyFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QPaintEngine_DirtyFlags, qtscript_QPaintEngine_DirtyFlags_valueOf,
        qtscript_QPaintEngine_DirtyFlags_toString, qtscript_QPaintEngine_DirtyFlags_equals);
    qScriptRegisterMetaType<QPaintEngine::DirtyFlags>(engine, qtscript_QPaintEngine_DirtyFlags_toScriptValue,
        qtscript_QPaintEngine_DirtyFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QPaintEngine
//

static QScriptValue qtscript_QPaintEngine_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 29;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPaintEngine* _q_self = qscriptvalue_cast<QPaintEngine*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPaintEngine.%0(): this object is not a QPaintEngine")
            .arg(qtscript_QPaintEngine_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QPaintDevice* _q_arg0 = qscriptvalue_cast<QPaintDevice*>(context->argument(0));
        bool _q_result = _q_self->begin(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QFlags<QPaintEngine::DirtyFlag> _q_arg0 = qscriptvalue_cast<QFlags<QPaintEngine::DirtyFlag> >(context->argument(0));
        _q_self->clearDirty(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->coordinateOffset();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
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
    break;

    case 4:
    if (context->argumentCount() == 3) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
        QRectF _q_arg2 = qscriptvalue_cast<QRectF>(context->argument(2));
        _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QImage _q_arg1 = qscriptvalue_cast<QImage>(context->argument(1));
        QRectF _q_arg2 = qscriptvalue_cast<QRectF>(context->argument(2));
        QFlags<Qt::ImageConversionFlag> _q_arg3 = qscriptvalue_cast<QFlags<Qt::ImageConversionFlag> >(context->argument(3));
        _q_self->drawImage(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QLine*>(context->argument(0))
            && context->argument(1).isNumber()) {
            QLine* _q_arg0 = qscriptvalue_cast<QLine*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->drawLines(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QLineF*>(context->argument(0))
            && context->argument(1).isNumber()) {
            QLineF* _q_arg0 = qscriptvalue_cast<QLineF*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->drawLines(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        _q_self->drawPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 3) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
        QRectF _q_arg2 = qscriptvalue_cast<QRectF>(context->argument(2));
        _q_self->drawPixmap(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QPoint*>(context->argument(0))
            && context->argument(1).isNumber()) {
            QPoint* _q_arg0 = qscriptvalue_cast<QPoint*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->drawPoints(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QPointF*>(context->argument(0))
            && context->argument(1).isNumber()) {
            QPointF* _q_arg0 = qscriptvalue_cast<QPointF*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->drawPoints(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 9:
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<QPoint*>(context->argument(0))
            && context->argument(1).isNumber()
            && (qMetaTypeId<QPaintEngine::PolygonDrawMode>() == context->argument(2).toVariant().userType())) {
            QPoint* _q_arg0 = qscriptvalue_cast<QPoint*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QPaintEngine::PolygonDrawMode _q_arg2 = qscriptvalue_cast<QPaintEngine::PolygonDrawMode>(context->argument(2));
            _q_self->drawPolygon(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QPointF*>(context->argument(0))
            && context->argument(1).isNumber()
            && (qMetaTypeId<QPaintEngine::PolygonDrawMode>() == context->argument(2).toVariant().userType())) {
            QPointF* _q_arg0 = qscriptvalue_cast<QPointF*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QPaintEngine::PolygonDrawMode _q_arg2 = qscriptvalue_cast<QPaintEngine::PolygonDrawMode>(context->argument(2));
            _q_self->drawPolygon(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QRect*>(context->argument(0))
            && context->argument(1).isNumber()) {
            QRect* _q_arg0 = qscriptvalue_cast<QRect*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->drawRects(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QRectF*>(context->argument(0))
            && context->argument(1).isNumber()) {
            QRectF* _q_arg0 = qscriptvalue_cast<QRectF*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->drawRects(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QTextItem _q_arg1 = qscriptvalue_cast<QTextItem>(context->argument(1));
        _q_self->drawTextItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 3) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
        QPointF _q_arg2 = qscriptvalue_cast<QPointF>(context->argument(2));
        _q_self->drawTiledPixmap(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->end();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QFlags<QPaintEngine::PaintEngineFeature> _q_arg0 = qscriptvalue_cast<QFlags<QPaintEngine::PaintEngineFeature> >(context->argument(0));
        bool _q_result = _q_self->hasFeature(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isActive();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isExtended();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QPaintDevice* _q_result = _q_self->paintDevice();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QPainter* _q_result = _q_self->painter();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setActive(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QFlags<QPaintEngine::DirtyFlag> _q_arg0 = qscriptvalue_cast<QFlags<QPaintEngine::DirtyFlag> >(context->argument(0));
        _q_self->setDirty(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
        _q_self->setSystemClip(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        _q_self->setSystemRect(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        _q_self->syncState();
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QRegion _q_result = _q_self->systemClip();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->systemRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QFlags<QPaintEngine::DirtyFlag> _q_arg0 = qscriptvalue_cast<QFlags<QPaintEngine::DirtyFlag> >(context->argument(0));
        bool _q_result = _q_self->testDirty(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QPaintEngine::Type _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        QPaintEngineState _q_arg0 = qscriptvalue_cast<QPaintEngineState>(context->argument(0));
        _q_self->updateState(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29: {
    QString result = QString::fromLatin1("QPaintEngine");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPaintEngine_throw_ambiguity_error_helper(context,
        qtscript_QPaintEngine_function_names[_id+1],
        qtscript_QPaintEngine_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPaintEngine_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPaintEngine(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPaintEngine* _q_cpp_result = new QtScriptShell_QPaintEngine();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPaintEngine*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QFlags<QPaintEngine::PaintEngineFeature> _q_arg0 = qscriptvalue_cast<QFlags<QPaintEngine::PaintEngineFeature> >(context->argument(0));
        QtScriptShell_QPaintEngine* _q_cpp_result = new QtScriptShell_QPaintEngine(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPaintEngine*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPaintEngine_throw_ambiguity_error_helper(context,
        qtscript_QPaintEngine_function_names[_id],
        qtscript_QPaintEngine_function_signatures[_id]);
}

QScriptValue qtscript_create_QPaintEngine_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPaintEngine*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPaintEngine*)0));
    for (int i = 0; i < 30; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPaintEngine_prototype_call, qtscript_QPaintEngine_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPaintEngine_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPaintEngine*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPaintEngine_static_call, proto, qtscript_QPaintEngine_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("PolygonDrawMode"),
        qtscript_create_QPaintEngine_PolygonDrawMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Type"),
        qtscript_create_QPaintEngine_Type_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PaintEngineFeature"),
        qtscript_create_QPaintEngine_PaintEngineFeature_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PaintEngineFeatures"),
        qtscript_create_QPaintEngine_PaintEngineFeatures_class(engine));
    ctor.setProperty(QString::fromLatin1("DirtyFlag"),
        qtscript_create_QPaintEngine_DirtyFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("DirtyFlags"),
        qtscript_create_QPaintEngine_DirtyFlags_class(engine));
    return ctor;
}
