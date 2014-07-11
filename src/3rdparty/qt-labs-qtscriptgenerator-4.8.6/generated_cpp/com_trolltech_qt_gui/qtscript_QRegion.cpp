#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qregion.h>
#include <QVariant>
#include <qbitmap.h>
#include <qdatastream.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qvector.h>

static const char * const qtscript_QRegion_function_names[] = {
    "QRegion"
    // static
    // prototype
    , "boundingRect"
    , "contains"
    , "intersect"
    , "intersected"
    , "intersects"
    , "isEmpty"
    , "numRects"
    , "operator_add"
    , "operator_and"
    , "equals"
    , "readFrom"
    , "rectCount"
    , "rects"
    , "setRects"
    , "subtracted"
    , "swap"
    , "translate"
    , "translated"
    , "unite"
    , "united"
    , "writeTo"
    , "xored"
    , "toString"
};

static const char * const qtscript_QRegion_function_signatures[] = {
    "\nQBitmap bitmap\nQPolygon pa, FillRule fillRule\nQRect r, RegionType t\nQRegion region\nint x, int y, int w, int h, RegionType t"
    // static
    // prototype
    , ""
    , "QPoint p\nQRect r"
    , "QRect r"
    , "QRect r\nQRegion r"
    , "QRect r\nQRegion r"
    , ""
    , ""
    , "QRect r"
    , "QRect r"
    , "QRegion r"
    , "QDataStream arg__1"
    , ""
    , ""
    , "QRect rect, int num"
    , "QRegion r"
    , "QRegion other"
    , "QPoint p\nint dx, int dy"
    , "QPoint p\nint dx, int dy"
    , "QRect r"
    , "QRect r\nQRegion r"
    , "QDataStream arg__1"
    , "QRegion r"
""
};

static const int qtscript_QRegion_function_lengths[] = {
    5
    // static
    // prototype
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 2
    , 1
    , 1
    , 2
    , 2
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QRegion_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QRegion::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QRegion*)
Q_DECLARE_METATYPE(QRegion::RegionType)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(QVector<QRect>)
Q_DECLARE_METATYPE(QRect*)
Q_DECLARE_METATYPE(Qt::FillRule)

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
// QRegion::RegionType
//

static const QRegion::RegionType qtscript_QRegion_RegionType_values[] = {
    QRegion::Rectangle
    , QRegion::Ellipse
};

static const char * const qtscript_QRegion_RegionType_keys[] = {
    "Rectangle"
    , "Ellipse"
};

static QString qtscript_QRegion_RegionType_toStringHelper(QRegion::RegionType value)
{
    if ((value >= QRegion::Rectangle) && (value <= QRegion::Ellipse))
        return qtscript_QRegion_RegionType_keys[static_cast<int>(value)-static_cast<int>(QRegion::Rectangle)];
    return QString();
}

static QScriptValue qtscript_QRegion_RegionType_toScriptValue(QScriptEngine *engine, const QRegion::RegionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QRegion"));
    return clazz.property(qtscript_QRegion_RegionType_toStringHelper(value));
}

static void qtscript_QRegion_RegionType_fromScriptValue(const QScriptValue &value, QRegion::RegionType &out)
{
    out = qvariant_cast<QRegion::RegionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QRegion_RegionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QRegion::Rectangle) && (arg <= QRegion::Ellipse))
        return qScriptValueFromValue(engine,  static_cast<QRegion::RegionType>(arg));
    return context->throwError(QString::fromLatin1("RegionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QRegion_RegionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QRegion::RegionType value = qscriptvalue_cast<QRegion::RegionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QRegion_RegionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QRegion::RegionType value = qscriptvalue_cast<QRegion::RegionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QRegion_RegionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QRegion_RegionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QRegion_RegionType,
        qtscript_QRegion_RegionType_valueOf, qtscript_QRegion_RegionType_toString);
    qScriptRegisterMetaType<QRegion::RegionType>(engine, qtscript_QRegion_RegionType_toScriptValue,
        qtscript_QRegion_RegionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QRegion_RegionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QRegion_RegionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QRegion
//

static QScriptValue qtscript_QRegion_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 22;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QRegion* _q_self = qscriptvalue_cast<QRegion*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QRegion.%0(): this object is not a QRegion")
            .arg(qtscript_QRegion_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->boundingRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            bool _q_result = _q_self->contains(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            bool _q_result = _q_self->contains(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        QRegion _q_result = _q_self->intersect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QRegion _q_result = _q_self->intersected(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRegion>() == context->argument(0).toVariant().userType())) {
            QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
            QRegion _q_result = _q_self->intersected(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            bool _q_result = _q_self->intersects(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRegion>() == context->argument(0).toVariant().userType())) {
            QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
            bool _q_result = _q_self->intersects(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->numRects();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        QRegion _q_result = _q_self->operator+(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        QRegion _q_result = _q_self->operator&(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->rectCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QVector<QRect> _q_result = _q_self->rects();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        QRect* _q_arg0 = qscriptvalue_cast<QRect*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setRects(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
        QRegion _q_result = _q_self->subtracted(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->translate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->translate(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QRegion _q_result = _q_self->translated(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QRegion _q_result = _q_self->translated(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        QRegion _q_result = _q_self->unite(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QRegion _q_result = _q_self->united(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRegion>() == context->argument(0).toVariant().userType())) {
            QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
            QRegion _q_result = _q_self->united(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
        QRegion _q_result = _q_self->xored(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRegion_throw_ambiguity_error_helper(context,
        qtscript_QRegion_function_names[_id+1],
        qtscript_QRegion_function_signatures[_id+1]);
}

static QScriptValue qtscript_QRegion_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QRegion(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QRegion _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QBitmap>() == context->argument(0).toVariant().userType())) {
            QBitmap _q_arg0 = qscriptvalue_cast<QBitmap>(context->argument(0));
            QRegion _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QPolygon>() == context->argument(0).toVariant().userType())) {
            QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
            QRegion _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QRegion _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QRegion>() == context->argument(0).toVariant().userType())) {
            QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
            QRegion _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPolygon>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::FillRule>() == context->argument(1).toVariant().userType())) {
            QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
            Qt::FillRule _q_arg1 = qscriptvalue_cast<Qt::FillRule>(context->argument(1));
            QRegion _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QRegion::RegionType>() == context->argument(1).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QRegion::RegionType _q_arg1 = qscriptvalue_cast<QRegion::RegionType>(context->argument(1));
            QRegion _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QRegion _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 5) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QRegion::RegionType _q_arg4 = qscriptvalue_cast<QRegion::RegionType>(context->argument(4));
        QRegion _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRegion_throw_ambiguity_error_helper(context,
        qtscript_QRegion_function_names[_id],
        qtscript_QRegion_function_signatures[_id]);
}

QScriptValue qtscript_create_QRegion_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QRegion*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QRegion*)0));
    for (int i = 0; i < 23; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QRegion_prototype_call, qtscript_QRegion_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QRegion_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QRegion>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QRegion*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QRegion_static_call, proto, qtscript_QRegion_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("RegionType"),
        qtscript_create_QRegion_RegionType_class(engine, ctor));
    return ctor;
}
