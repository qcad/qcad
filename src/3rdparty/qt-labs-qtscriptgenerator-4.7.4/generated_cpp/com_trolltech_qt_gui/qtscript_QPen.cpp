#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpen.h>
#include <QBrush>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qdatastream.h>
#include <qpen.h>
#include <qvector.h>

static const char * const qtscript_QPen_function_names[] = {
    "QPen"
    // static
    // prototype
    , "brush"
    , "capStyle"
    , "color"
    , "dashOffset"
    , "dashPattern"
    , "isCosmetic"
    , "isSolid"
    , "joinStyle"
    , "miterLimit"
    , "equals"
    , "readFrom"
    , "setBrush"
    , "setCapStyle"
    , "setColor"
    , "setCosmetic"
    , "setDashOffset"
    , "setDashPattern"
    , "setJoinStyle"
    , "setMiterLimit"
    , "setStyle"
    , "setWidth"
    , "setWidthF"
    , "style"
    , "width"
    , "widthF"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QPen_function_signatures[] = {
    "\nPenStyle arg__1\nQBrush brush, qreal width, PenStyle s, PenCapStyle c, PenJoinStyle j\nQColor color\nQPen pen"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QPen p"
    , "QDataStream arg__1"
    , "QBrush brush"
    , "PenCapStyle pcs"
    , "QColor color"
    , "bool cosmetic"
    , "qreal doffset"
    , "List pattern"
    , "PenJoinStyle pcs"
    , "qreal limit"
    , "PenStyle arg__1"
    , "int width"
    , "qreal width"
    , ""
    , ""
    , ""
    , "QDataStream arg__1"
""
};

static const int qtscript_QPen_function_lengths[] = {
    5
    // static
    // prototype
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
    , 1
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QPen_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPen::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPen*)
Q_DECLARE_METATYPE(Qt::PenCapStyle)
Q_DECLARE_METATYPE(QVector<qreal>)
Q_DECLARE_METATYPE(Qt::PenJoinStyle)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(Qt::PenStyle)

//
// QPen
//

static QScriptValue qtscript_QPen_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 26;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPen* _q_self = qscriptvalue_cast<QPen*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPen.%0(): this object is not a QPen")
            .arg(qtscript_QPen_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->brush();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        Qt::PenCapStyle _q_result = _q_self->capStyle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->color();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->dashOffset();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QVector<qreal> _q_result = _q_self->dashPattern();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isCosmetic();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSolid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        Qt::PenJoinStyle _q_result = _q_self->joinStyle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->miterLimit();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QPen _q_arg0 = qscriptvalue_cast<QPen>(context->argument(0));
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
    if (context->argumentCount() == 1) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        _q_self->setBrush(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        Qt::PenCapStyle _q_arg0 = qscriptvalue_cast<Qt::PenCapStyle>(context->argument(0));
        _q_self->setCapStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        _q_self->setColor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setCosmetic(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setDashOffset(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QVector<qreal> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setDashPattern(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        Qt::PenJoinStyle _q_arg0 = qscriptvalue_cast<Qt::PenJoinStyle>(context->argument(0));
        _q_self->setJoinStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setMiterLimit(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        Qt::PenStyle _q_arg0 = qscriptvalue_cast<Qt::PenStyle>(context->argument(0));
        _q_self->setStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setWidthF(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        Qt::PenStyle _q_result = _q_self->style();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->width();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->widthF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 26: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPen_throw_ambiguity_error_helper(context,
        qtscript_QPen_function_names[_id+1],
        qtscript_QPen_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPen_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPen(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QPen _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::PenStyle>() == context->argument(0).toVariant().userType())) {
            Qt::PenStyle _q_arg0 = qscriptvalue_cast<Qt::PenStyle>(context->argument(0));
            QPen _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QColor>() == context->argument(0).toVariant().userType())) {
            QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
            QPen _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QPen>() == context->argument(0).toVariant().userType())) {
            QPen _q_arg0 = qscriptvalue_cast<QPen>(context->argument(0));
            QPen _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QPen _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        Qt::PenStyle _q_arg2 = qscriptvalue_cast<Qt::PenStyle>(context->argument(2));
        QPen _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 4) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        Qt::PenStyle _q_arg2 = qscriptvalue_cast<Qt::PenStyle>(context->argument(2));
        Qt::PenCapStyle _q_arg3 = qscriptvalue_cast<Qt::PenCapStyle>(context->argument(3));
        QPen _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 5) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        Qt::PenStyle _q_arg2 = qscriptvalue_cast<Qt::PenStyle>(context->argument(2));
        Qt::PenCapStyle _q_arg3 = qscriptvalue_cast<Qt::PenCapStyle>(context->argument(3));
        Qt::PenJoinStyle _q_arg4 = qscriptvalue_cast<Qt::PenJoinStyle>(context->argument(4));
        QPen _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPen_throw_ambiguity_error_helper(context,
        qtscript_QPen_function_names[_id],
        qtscript_QPen_function_signatures[_id]);
}

QScriptValue qtscript_create_QPen_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPen*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPen*)0));
    for (int i = 0; i < 27; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPen_prototype_call, qtscript_QPen_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPen_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPen>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QPen*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPen_static_call, proto, qtscript_QPen_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
