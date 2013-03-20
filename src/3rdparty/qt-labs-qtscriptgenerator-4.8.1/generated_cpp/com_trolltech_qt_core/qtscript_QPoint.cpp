#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpoint.h>
#include <QVariant>
#include <qdatastream.h>
#include <qpoint.h>

static const char * const qtscript_QPoint_function_names[] = {
    "QPoint"
    // static
    // prototype
    , "isNull"
    , "manhattanLength"
    , "operator_add_assign"
    , "operator_divide_assign"
    , "equals"
    , "operator_multiply_assign"
    , "operator_subtract_assign"
    , "readFrom"
    , "setX"
    , "setY"
    , "writeTo"
    , "x"
    , "y"
    , "toString"
};

static const char * const qtscript_QPoint_function_signatures[] = {
    "\nint xpos, int ypos"
    // static
    // prototype
    , ""
    , ""
    , "QPoint p"
    , "qreal c"
    , "QPoint p2"
    , "double c\nfloat c\nint c"
    , "QPoint p"
    , "QDataStream arg__1"
    , "int x"
    , "int y"
    , "QDataStream arg__1"
    , ""
    , ""
""
};

static const int qtscript_QPoint_function_lengths[] = {
    2
    // static
    // prototype
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
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QPoint_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPoint::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPoint*)
Q_DECLARE_METATYPE(QDataStream*)

//
// QPoint
//

static QScriptValue qtscript_QPoint_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 13;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPoint* _q_self = qscriptvalue_cast<QPoint*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPoint.%0(): this object is not a QPoint")
            .arg(qtscript_QPoint_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->manhattanLength();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QPoint _q_result = _q_self->operator+=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QPoint _q_result = _q_self->operator/=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        bool _q_result = operator==(*_q_self, _q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isNumber()) {
            double _q_arg0 = context->argument(0).toNumber();
            QPoint _q_result = _q_self->operator*=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
            QPoint _q_result = _q_self->operator*=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QPoint _q_result = _q_self->operator*=(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QPoint _q_result = _q_self->operator-=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setX(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setY(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->x();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->y();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPoint_throw_ambiguity_error_helper(context,
        qtscript_QPoint_function_names[_id+1],
        qtscript_QPoint_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPoint_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPoint(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QPoint _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QPoint _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPoint_throw_ambiguity_error_helper(context,
        qtscript_QPoint_function_names[_id],
        qtscript_QPoint_function_signatures[_id]);
}

QScriptValue qtscript_create_QPoint_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPoint*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPoint*)0));
    for (int i = 0; i < 14; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPoint_prototype_call, qtscript_QPoint_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPoint_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPoint>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QPoint*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPoint_static_call, proto, qtscript_QPoint_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
