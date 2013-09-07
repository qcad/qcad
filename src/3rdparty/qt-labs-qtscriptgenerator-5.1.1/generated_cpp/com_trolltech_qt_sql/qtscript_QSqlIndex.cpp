#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsqlindex.h>
#include <QVariant>
#include <qsqlfield.h>
#include <qsqlindex.h>
#include <qsqlrecord.h>

static const char * const qtscript_QSqlIndex_function_names[] = {
    "QSqlIndex"
    // static
    // prototype
    , "append"
    , "cursorName"
    , "isDescending"
    , "name"
    , "setCursorName"
    , "setDescending"
    , "setName"
    , "toString"
};

static const char * const qtscript_QSqlIndex_function_signatures[] = {
    "QSqlIndex other\nString cursorName, String name"
    // static
    // prototype
    , "QSqlField field, bool desc"
    , ""
    , "int i"
    , ""
    , "String cursorName"
    , "int i, bool desc"
    , "String name"
""
};

static const int qtscript_QSqlIndex_function_lengths[] = {
    2
    // static
    // prototype
    , 2
    , 0
    , 1
    , 0
    , 1
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QSqlIndex_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSqlIndex::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSqlIndex)
Q_DECLARE_METATYPE(QSqlIndex*)
Q_DECLARE_METATYPE(QSqlField)
Q_DECLARE_METATYPE(QSqlRecord*)

//
// QSqlIndex
//

static QScriptValue qtscript_QSqlIndex_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 7;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSqlIndex* _q_self = qscriptvalue_cast<QSqlIndex*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSqlIndex.%0(): this object is not a QSqlIndex")
            .arg(qtscript_QSqlIndex_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QSqlField _q_arg0 = qscriptvalue_cast<QSqlField>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->append(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->cursorName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isDescending(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setCursorName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setDescending(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7: {
    QString result = QString::fromLatin1("QSqlIndex");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlIndex_throw_ambiguity_error_helper(context,
        qtscript_QSqlIndex_function_names[_id+1],
        qtscript_QSqlIndex_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSqlIndex_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSqlIndex(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSqlIndex _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QSqlIndex>() == context->argument(0).toVariant().userType())) {
            QSqlIndex _q_arg0 = qscriptvalue_cast<QSqlIndex>(context->argument(0));
            QSqlIndex _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QSqlIndex _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QSqlIndex _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSqlIndex_throw_ambiguity_error_helper(context,
        qtscript_QSqlIndex_function_names[_id],
        qtscript_QSqlIndex_function_signatures[_id]);
}

QScriptValue qtscript_create_QSqlIndex_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSqlIndex*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSqlIndex*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QSqlRecord*>()));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSqlIndex_prototype_call, qtscript_QSqlIndex_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSqlIndex_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSqlIndex>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSqlIndex*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSqlIndex_static_call, proto, qtscript_QSqlIndex_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
