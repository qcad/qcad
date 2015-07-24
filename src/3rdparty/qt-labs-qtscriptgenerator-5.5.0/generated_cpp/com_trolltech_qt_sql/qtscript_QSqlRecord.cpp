#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsqlrecord.h>
#include <QSqlField>
#include <QVariant>
#include <qsqlfield.h>
#include <qsqlrecord.h>

static const char * const qtscript_QSqlRecord_function_names[] = {
    "QSqlRecord"
    // static
    // prototype
    , "append"
    , "clear"
    , "clearValues"
    , "contains"
    , "count"
    , "field"
    , "fieldName"
    , "indexOf"
    , "insert"
    , "isEmpty"
    , "isGenerated"
    , "isNull"
    , "keyValues"
    , "equals"
    , "remove"
    , "replace"
    , "setGenerated"
    , "setNull"
    , "setValue"
    , "value"
    , "toString"
};

static const char * const qtscript_QSqlRecord_function_signatures[] = {
    "\nQSqlRecord other"
    // static
    // prototype
    , "QSqlField field"
    , ""
    , ""
    , "String name"
    , ""
    , "String name\nint i"
    , "int i"
    , "String name"
    , "int pos, QSqlField field"
    , ""
    , "String name\nint i"
    , "String name\nint i"
    , "QSqlRecord keyFields"
    , "QSqlRecord other"
    , "int pos"
    , "int pos, QSqlField field"
    , "String name, bool generated\nint i, bool generated"
    , "String name\nint i"
    , "String name, Object val\nint i, Object val"
    , "String name\nint i"
""
};

static const int qtscript_QSqlRecord_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
    , 1
    , 0
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
    , 2
    , 2
    , 1
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QSqlRecord_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlRecord::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlRecord)
Q_DECLARE_METATYPE(QSqlRecord*)
Q_DECLARE_METATYPE(QSqlField)

//
// QSqlRecord
//

static QScriptValue qtscript_QSqlRecord_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 20;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSqlRecord* _q_self = qscriptvalue_cast<QSqlRecord*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlRecord.%0(): this object is not a QSqlRecord")
            .arg(qtscript_QSqlRecord_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QSqlField _q_arg0 = qscriptvalue_cast<QSqlField>(context->argument(0));
        _q_self->append(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->clearValues();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->contains(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QSqlField _q_result = _q_self->field(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QSqlField _q_result = _q_self->field(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->fieldName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->indexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QSqlField _q_arg1 = qscriptvalue_cast<QSqlField>(context->argument(1));
        _q_self->insert(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->isGenerated(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            bool _q_result = _q_self->isGenerated(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->isNull(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            bool _q_result = _q_self->isNull(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QSqlRecord _q_arg0 = qscriptvalue_cast<QSqlRecord>(context->argument(0));
        QSqlRecord _q_result = _q_self->keyValues(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QSqlRecord _q_arg0 = qscriptvalue_cast<QSqlRecord>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->remove(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QSqlField _q_arg1 = qscriptvalue_cast<QSqlField>(context->argument(1));
        _q_self->replace(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && context->argument(1).isBoolean()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_arg1 = context->argument(1).toBoolean();
            _q_self->setGenerated(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isBoolean()) {
            int _q_arg0 = context->argument(0).toInt32();
            bool _q_arg1 = context->argument(1).toBoolean();
            _q_self->setGenerated(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->setNull(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            _q_self->setNull(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 18:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && true) {
            QString _q_arg0 = context->argument(0).toString();
            QVariant _q_arg1 = context->argument(1).toVariant();
            _q_self->setValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && true) {
            int _q_arg0 = context->argument(0).toInt32();
            QVariant _q_arg1 = context->argument(1).toVariant();
            _q_self->setValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QVariant _q_result = _q_self->value(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QVariant _q_result = _q_self->value(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 20: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlRecord_throw_ambiguity_error_helper(context,
        qtscript_QSqlRecord_function_names[_id+1],
        qtscript_QSqlRecord_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSqlRecord_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSqlRecord(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSqlRecord _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QSqlRecord _q_arg0 = qscriptvalue_cast<QSqlRecord>(context->argument(0));
        QSqlRecord _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlRecord_throw_ambiguity_error_helper(context,
        qtscript_QSqlRecord_function_names[_id],
        qtscript_QSqlRecord_function_signatures[_id]);
}

QScriptValue qtscript_create_QSqlRecord_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlRecord*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlRecord*)0));
    for (int i = 0; i < 21; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlRecord_prototype_call, qtscript_QSqlRecord_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlRecord_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSqlRecord>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSqlRecord*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlRecord_static_call, proto, qtscript_QSqlRecord_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
