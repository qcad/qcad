#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpainterpath.h>
#include <QPainterPath>
#include <QVariant>
#include <qdatastream.h>
#include <qfont.h>
#include <qlist.h>
#include <qmatrix.h>
#include <qpainterpath.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qtransform.h>

static const char * const qtscript_QPainterPath_function_names[] = {
    "QPainterPath"
    // static
    // prototype
    , "addEllipse"
    , "addPath"
    , "addPolygon"
    , "addRect"
    , "addRegion"
    , "addRoundRect"
    , "addRoundedRect"
    , "addText"
    , "angleAtPercent"
    , "arcMoveTo"
    , "arcTo"
    , "boundingRect"
    , "closeSubpath"
    , "connectPath"
    , "contains"
    , "controlPointRect"
    , "cubicTo"
    , "currentPosition"
    , "elementAt"
    , "elementCount"
    , "fillRule"
    , "intersected"
    , "intersects"
    , "isEmpty"
    , "length"
    , "lineTo"
    , "moveTo"
    , "operator_add"
    , "operator_add_assign"
    , "operator_and"
    , "operator_and_assign"
    , "equals"
    , "operator_or"
    , "operator_or_assign"
    , "operator_subtract"
    , "operator_subtract_assign"
    , "percentAtLength"
    , "pointAtPercent"
    , "quadTo"
    , "readFrom"
    , "setElementPositionAt"
    , "setFillRule"
    , "simplified"
    , "slopeAtPercent"
    , "subtracted"
    , "subtractedInverted"
    , "swap"
    , "toFillPolygon"
    , "toFillPolygons"
    , "toReversed"
    , "toSubpathPolygons"
    , "translate"
    , "translated"
    , "united"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QPainterPath_function_signatures[] = {
    "\nQPainterPath other\nQPointF startPoint"
    // static
    // prototype
    , "QPointF center, qreal rx, qreal ry\nQRectF rect\nqreal x, qreal y, qreal w, qreal h"
    , "QPainterPath path"
    , "QPolygonF polygon"
    , "QRectF rect\nqreal x, qreal y, qreal w, qreal h"
    , "QRegion region"
    , "QRectF rect, int roundness\nQRectF rect, int xRnd, int yRnd\nqreal x, qreal y, qreal w, qreal h, int roundness\nqreal x, qreal y, qreal w, qreal h, int xRnd, int yRnd"
    , "QRectF rect, qreal xRadius, qreal yRadius, SizeMode mode\nqreal x, qreal y, qreal w, qreal h, qreal xRadius, qreal yRadius, SizeMode mode"
    , "QPointF point, QFont f, String text\nqreal x, qreal y, QFont f, String text"
    , "qreal t"
    , "QRectF rect, qreal angle\nqreal x, qreal y, qreal w, qreal h, qreal angle"
    , "QRectF rect, qreal startAngle, qreal arcLength\nqreal x, qreal y, qreal w, qreal h, qreal startAngle, qreal arcLength"
    , ""
    , ""
    , "QPainterPath path"
    , "QPainterPath p\nQPointF pt\nQRectF rect"
    , ""
    , "QPointF ctrlPt1, QPointF ctrlPt2, QPointF endPt\nqreal ctrlPt1x, qreal ctrlPt1y, qreal ctrlPt2x, qreal ctrlPt2y, qreal endPtx, qreal endPty"
    , ""
    , "int i"
    , ""
    , ""
    , "QPainterPath r"
    , "QPainterPath p\nQRectF rect"
    , ""
    , ""
    , "QPointF p\nqreal x, qreal y"
    , "QPointF p\nqreal x, qreal y"
    , "QPainterPath other"
    , "QPainterPath other"
    , "QPainterPath other"
    , "QPainterPath other"
    , "QPainterPath other"
    , "QPainterPath other"
    , "QPainterPath other"
    , "QPainterPath other"
    , "QPainterPath other"
    , "qreal t"
    , "qreal t"
    , "QPointF ctrlPt, QPointF endPt\nqreal ctrlPtx, qreal ctrlPty, qreal endPtx, qreal endPty"
    , "QDataStream arg__1"
    , "int i, qreal x, qreal y"
    , "FillRule fillRule"
    , ""
    , "qreal t"
    , "QPainterPath r"
    , "QPainterPath r"
    , "QPainterPath other"
    , "QMatrix matrix\nQTransform matrix"
    , "QMatrix matrix\nQTransform matrix"
    , ""
    , "QMatrix matrix\nQTransform matrix"
    , "QPointF offset\nqreal dx, qreal dy"
    , "QPointF offset\nqreal dx, qreal dy"
    , "QPainterPath r"
    , "QDataStream arg__1"
""
};

static const int qtscript_QPainterPath_function_lengths[] = {
    1
    // static
    // prototype
    , 4
    , 1
    , 1
    , 4
    , 1
    , 6
    , 7
    , 4
    , 1
    , 5
    , 6
    , 0
    , 0
    , 1
    , 1
    , 0
    , 6
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 2
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 4
    , 1
    , 3
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 1
    , 2
    , 2
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QPainterPath_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPainterPath::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QPainterPath*)
Q_DECLARE_METATYPE(QPainterPath::ElementType)
Q_DECLARE_METATYPE(QPolygonF)
Q_DECLARE_METATYPE(Qt::SizeMode)
Q_DECLARE_METATYPE(QPainterPath::Element)
Q_DECLARE_METATYPE(Qt::FillRule)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(QList<QPolygonF>)

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

//
// QPainterPath::ElementType
//

static const QPainterPath::ElementType qtscript_QPainterPath_ElementType_values[] = {
    QPainterPath::MoveToElement
    , QPainterPath::LineToElement
    , QPainterPath::CurveToElement
    , QPainterPath::CurveToDataElement
};

static const char * const qtscript_QPainterPath_ElementType_keys[] = {
    "MoveToElement"
    , "LineToElement"
    , "CurveToElement"
    , "CurveToDataElement"
};

static QString qtscript_QPainterPath_ElementType_toStringHelper(QPainterPath::ElementType value)
{
    if ((value >= QPainterPath::MoveToElement) && (value <= QPainterPath::CurveToDataElement))
        return qtscript_QPainterPath_ElementType_keys[static_cast<int>(value)-static_cast<int>(QPainterPath::MoveToElement)];
    return QString();
}

static QScriptValue qtscript_QPainterPath_ElementType_toScriptValue(QScriptEngine *engine, const QPainterPath::ElementType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPainterPath"));
    return clazz.property(qtscript_QPainterPath_ElementType_toStringHelper(value));
}

static void qtscript_QPainterPath_ElementType_fromScriptValue(const QScriptValue &value, QPainterPath::ElementType &out)
{
    out = qvariant_cast<QPainterPath::ElementType>(value.toVariant());
}

static QScriptValue qtscript_construct_QPainterPath_ElementType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPainterPath::MoveToElement) && (arg <= QPainterPath::CurveToDataElement))
        return qScriptValueFromValue(engine,  static_cast<QPainterPath::ElementType>(arg));
    return context->throwError(QString::fromLatin1("ElementType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPainterPath_ElementType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPainterPath::ElementType value = qscriptvalue_cast<QPainterPath::ElementType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPainterPath_ElementType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPainterPath::ElementType value = qscriptvalue_cast<QPainterPath::ElementType>(context->thisObject());
    return QScriptValue(engine, qtscript_QPainterPath_ElementType_toStringHelper(value));
}

static QScriptValue qtscript_create_QPainterPath_ElementType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPainterPath_ElementType,
        qtscript_QPainterPath_ElementType_valueOf, qtscript_QPainterPath_ElementType_toString);
    qScriptRegisterMetaType<QPainterPath::ElementType>(engine, qtscript_QPainterPath_ElementType_toScriptValue,
        qtscript_QPainterPath_ElementType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPainterPath_ElementType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPainterPath_ElementType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPainterPath
//

static QScriptValue qtscript_QPainterPath_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 55;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPainterPath* _q_self = qscriptvalue_cast<QPainterPath*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPainterPath.%0(): this object is not a QPainterPath")
            .arg(qtscript_QPainterPath_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        _q_self->addEllipse(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->addEllipse(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->addEllipse(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        _q_self->addPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
        _q_self->addPolygon(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        _q_self->addRect(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->addRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
        _q_self->addRegion(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->addRoundRect(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->addRoundRect(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        _q_self->addRoundRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        _q_self->addRoundRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 3) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->addRoundedRect(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        Qt::SizeMode _q_arg3 = qscriptvalue_cast<Qt::SizeMode>(context->argument(3));
        _q_self->addRoundedRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        _q_self->addRoundedRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 7) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        Qt::SizeMode _q_arg6 = qscriptvalue_cast<Qt::SizeMode>(context->argument(6));
        _q_self->addRoundedRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 3) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QFont _q_arg1 = qscriptvalue_cast<QFont>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        _q_self->addText(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QFont _q_arg2 = qscriptvalue_cast<QFont>(context->argument(2));
        QString _q_arg3 = context->argument(3).toString();
        _q_self->addText(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_result = _q_self->angleAtPercent(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->arcMoveTo(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        _q_self->arcMoveTo(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 3) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->arcTo(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        _q_self->arcTo(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->boundingRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        _q_self->closeSubpath();
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        _q_self->connectPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            bool _q_result = _q_self->contains(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            bool _q_result = _q_self->contains(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            bool _q_result = _q_self->contains(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->controlPointRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 3) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        QPointF _q_arg2 = qscriptvalue_cast<QPointF>(context->argument(2));
        _q_self->cubicTo(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        qreal _q_arg5 = qscriptvalue_cast<qreal>(context->argument(5));
        _q_self->cubicTo(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->currentPosition();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QPainterPath::Element _q_result = _q_self->elementAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->elementCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        Qt::FillRule _q_result = _q_self->fillRule();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->intersected(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            bool _q_result = _q_self->intersects(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            bool _q_result = _q_self->intersects(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->length();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->lineTo(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->lineTo(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->moveTo(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->moveTo(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->operator+(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->operator+=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->operator&(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->operator&=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->operator|(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->operator|=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->operator-(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->operator-=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_result = _q_self->percentAtLength(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QPointF _q_result = _q_self->pointAtPercent(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 38:
    if (context->argumentCount() == 2) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        _q_self->quadTo(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->quadTo(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->setElementPositionAt(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        Qt::FillRule _q_arg0 = qscriptvalue_cast<Qt::FillRule>(context->argument(0));
        _q_self->setFillRule(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 0) {
        QPainterPath _q_result = _q_self->simplified();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_result = _q_self->slopeAtPercent(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->subtracted(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->subtractedInverted(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 46:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {
        QPolygonF _q_result = _q_self->toFillPolygon();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QMatrix>() == context->argument(0).toVariant().userType())) {
            QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
            QPolygonF _q_result = _q_self->toFillPolygon(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTransform>() == context->argument(0).toVariant().userType())) {
            QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
            QPolygonF _q_result = _q_self->toFillPolygon(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {
        QList<QPolygonF> _q_result = _q_self->toFillPolygons();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QMatrix>() == context->argument(0).toVariant().userType())) {
            QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
            QList<QPolygonF> _q_result = _q_self->toFillPolygons(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTransform>() == context->argument(0).toVariant().userType())) {
            QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
            QList<QPolygonF> _q_result = _q_self->toFillPolygons(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    break;

    case 49:
    if (context->argumentCount() == 0) {
        QPainterPath _q_result = _q_self->toReversed();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 50:
    if (context->argumentCount() == 0) {
        QList<QPolygonF> _q_result = _q_self->toSubpathPolygons();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QMatrix>() == context->argument(0).toVariant().userType())) {
            QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
            QList<QPolygonF> _q_result = _q_self->toSubpathPolygons(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTransform>() == context->argument(0).toVariant().userType())) {
            QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
            QList<QPolygonF> _q_result = _q_self->toSubpathPolygons(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    break;

    case 51:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->translate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->translate(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 52:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QPainterPath _q_result = _q_self->translated(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QPainterPath _q_result = _q_self->translated(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 53:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QPainterPath _q_result = _q_self->united(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 54:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 55: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPainterPath_throw_ambiguity_error_helper(context,
        qtscript_QPainterPath_function_names[_id+1],
        qtscript_QPainterPath_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPainterPath_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPainterPath(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QPainterPath _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            QPainterPath _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPainterPath _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPainterPath_throw_ambiguity_error_helper(context,
        qtscript_QPainterPath_function_names[_id],
        qtscript_QPainterPath_function_signatures[_id]);
}

QScriptValue qtscript_create_QPainterPath_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPainterPath*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPainterPath*)0));
    for (int i = 0; i < 56; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPainterPath_prototype_call, qtscript_QPainterPath_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPainterPath_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPainterPath>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QPainterPath*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPainterPath_static_call, proto, qtscript_QPainterPath_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ElementType"),
        qtscript_create_QPainterPath_ElementType_class(engine, ctor));
    return ctor;
}
