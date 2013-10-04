#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qbitarray.h>
#include <QVariant>
#include <qbitarray.h>
#include <qdatastream.h>

static const char * const qtscript_QBitArray_function_names[] = {
    "QBitArray"
    // static
    // prototype
    , "at"
    , "clear"
    , "clearBit"
    , "count"
    , "fill"
    , "isEmpty"
    , "isNull"
    , "operator_and_assign"
    , "operator_assign"
    , "equals"
    , "operator_negate"
    , "operator_or_assign"
    , "operator_xor_assign"
    , "readFrom"
    , "resize"
    , "setBit"
    , "size"
    , "swap"
    , "testBit"
    , "toggleBit"
    , "truncate"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QBitArray_function_signatures[] = {
    "\nQBitArray other\nint size, bool val"
    // static
    // prototype
    , "int i"
    , ""
    , "int i"
    , "\nbool on"
    , "bool val, int first, int last\nbool val, int size"
    , ""
    , ""
    , "QBitArray arg__1"
    , "QBitArray other"
    , "QBitArray a"
    , ""
    , "QBitArray arg__1"
    , "QBitArray arg__1"
    , "QDataStream arg__1"
    , "int size"
    , "int i\nint i, bool val"
    , ""
    , "QBitArray other"
    , "int i"
    , "int i"
    , "int pos"
    , "QDataStream arg__1"
""
};

static const int qtscript_QBitArray_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 0
    , 1
    , 1
    , 3
    , 0
    , 0
    , 1
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 2
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QBitArray_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QBitArray::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QBitArray*)
Q_DECLARE_METATYPE(QDataStream*)

//
// QBitArray
//

static QScriptValue qtscript_QBitArray_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QBitArray* _q_self = qscriptvalue_cast<QBitArray*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QBitArray.%0(): this object is not a QBitArray")
            .arg(qtscript_QBitArray_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {

        // TEMPLATE - core.convert_int_arg_and_check_range - START
          int _q_arg0 = context->argument(0).toInt32();
          if ((_q_arg0 < 0) || (_q_self->size() < _q_arg0)) {
              return context->throwError(QScriptContext::RangeError,
                                         QString::fromLatin1("QBitArray::at(): index out of range"));
          }
    // TEMPLATE - core.convert_int_arg_and_check_range - END
                bool _q_result = _q_self->at(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {

        // TEMPLATE - core.convert_int_arg_and_check_range - START
          int _q_arg0 = context->argument(0).toInt32();
          if ((_q_arg0 < 0) || (_q_self->size() < _q_arg0)) {
              return context->throwError(QScriptContext::RangeError,
                                         QString::fromLatin1("QBitArray::clearBit(): index out of range"));
          }
    // TEMPLATE - core.convert_int_arg_and_check_range - END
                _q_self->clearBit(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        int _q_result = _q_self->count(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        bool _q_result = _q_self->fill(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        bool _q_arg0 = context->argument(0).toBoolean();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->fill(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        bool _q_arg0 = context->argument(0).toBoolean();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->fill(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
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
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QBitArray _q_arg0 = qscriptvalue_cast<QBitArray>(context->argument(0));
        _q_self->operator&=(_q_arg0);
        return context->thisObject();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QBitArray _q_arg0 = qscriptvalue_cast<QBitArray>(context->argument(0));
        _q_self->operator=(_q_arg0);
        return context->thisObject();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QBitArray _q_arg0 = qscriptvalue_cast<QBitArray>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QBitArray _q_result = _q_self->operator~();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QBitArray _q_arg0 = qscriptvalue_cast<QBitArray>(context->argument(0));
        _q_self->operator|=(_q_arg0);
        return context->thisObject();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QBitArray _q_arg0 = qscriptvalue_cast<QBitArray>(context->argument(0));
        _q_self->operator^=(_q_arg0);
        return context->thisObject();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->resize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {

        // TEMPLATE - core.convert_int_arg_and_check_range - START
          int _q_arg0 = context->argument(0).toInt32();
          if ((_q_arg0 < 0) || (_q_self->size() < _q_arg0)) {
              return context->throwError(QScriptContext::RangeError,
                                         QString::fromLatin1("QBitArray::setBit(): index out of range"));
          }
    // TEMPLATE - core.convert_int_arg_and_check_range - END
                _q_self->setBit(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {

        // TEMPLATE - core.convert_int_arg_and_check_range - START
          int _q_arg0 = context->argument(0).toInt32();
          if ((_q_arg0 < 0) || (_q_self->size() < _q_arg0)) {
              return context->throwError(QScriptContext::RangeError,
                                         QString::fromLatin1("QBitArray::setBit(): index out of range"));
          }
    // TEMPLATE - core.convert_int_arg_and_check_range - END
                bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setBit(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->size();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QBitArray _q_arg0 = qscriptvalue_cast<QBitArray>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {

        // TEMPLATE - core.convert_int_arg_and_check_range - START
          int _q_arg0 = context->argument(0).toInt32();
          if ((_q_arg0 < 0) || (_q_self->size() < _q_arg0)) {
              return context->throwError(QScriptContext::RangeError,
                                         QString::fromLatin1("QBitArray::testBit(): index out of range"));
          }
    // TEMPLATE - core.convert_int_arg_and_check_range - END
                bool _q_result = _q_self->testBit(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {

        // TEMPLATE - core.convert_int_arg_and_check_range - START
          int _q_arg0 = context->argument(0).toInt32();
          if ((_q_arg0 < 0) || (_q_self->size() < _q_arg0)) {
              return context->throwError(QScriptContext::RangeError,
                                         QString::fromLatin1("QBitArray::toggleBit(): index out of range"));
          }
    // TEMPLATE - core.convert_int_arg_and_check_range - END
                bool _q_result = _q_self->toggleBit(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->truncate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 22: {
    QString result = QString::fromLatin1("QBitArray");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QBitArray_throw_ambiguity_error_helper(context,
        qtscript_QBitArray_function_names[_id+1],
        qtscript_QBitArray_function_signatures[_id+1]);
}

static QScriptValue qtscript_QBitArray_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QBitArray(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QBitArray _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QBitArray>() == context->argument(0).toVariant().userType())) {
            QBitArray _q_arg0 = qscriptvalue_cast<QBitArray>(context->argument(0));
            QBitArray _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QBitArray _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        QBitArray _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QBitArray_throw_ambiguity_error_helper(context,
        qtscript_QBitArray_function_names[_id],
        qtscript_QBitArray_function_signatures[_id]);
}

QScriptValue qtscript_create_QBitArray_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QBitArray*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QBitArray*)0));
    for (int i = 0; i < 23; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QBitArray_prototype_call, qtscript_QBitArray_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QBitArray_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QBitArray>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QBitArray*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QBitArray_static_call, proto, qtscript_QBitArray_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
