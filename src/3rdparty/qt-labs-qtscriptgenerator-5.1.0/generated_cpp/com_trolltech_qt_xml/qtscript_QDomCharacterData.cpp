#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdom.h>
#include <QVariant>
#include <qdom.h>
#include <qtextstream.h>

static const char * const qtscript_QDomCharacterData_function_names[] = {
    "QDomCharacterData"
    // static
    // prototype
    , "appendData"
    , "data"
    , "deleteData"
    , "insertData"
    , "length"
    , "replaceData"
    , "setData"
    , "substringData"
    , "toString"
};

static const char * const qtscript_QDomCharacterData_function_signatures[] = {
    "\nQDomCharacterData x"
    // static
    // prototype
    , "String arg"
    , ""
    , "unsigned long offset, unsigned long count"
    , "unsigned long offset, String arg"
    , ""
    , "unsigned long offset, unsigned long count, String arg"
    , "String arg__1"
    , "unsigned long offset, unsigned long count"
""
};

static const int qtscript_QDomCharacterData_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 2
    , 2
    , 0
    , 3
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QDomCharacterData_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDomCharacterData::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDomCharacterData)
Q_DECLARE_METATYPE(QDomCharacterData*)
Q_DECLARE_METATYPE(QDomNode*)

//
// QDomCharacterData
//

static QScriptValue qtscript_QDomCharacterData_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 8;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDomCharacterData* _q_self = qscriptvalue_cast<QDomCharacterData*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDomCharacterData.%0(): this object is not a QDomCharacterData")
            .arg(qtscript_QDomCharacterData_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->appendData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->data();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        ulong _q_arg0 = qscriptvalue_cast<ulong>(context->argument(0));
        ulong _q_arg1 = qscriptvalue_cast<ulong>(context->argument(1));
        _q_self->deleteData(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        ulong _q_arg0 = qscriptvalue_cast<ulong>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        _q_self->insertData(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->length();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 3) {
        ulong _q_arg0 = qscriptvalue_cast<ulong>(context->argument(0));
        ulong _q_arg1 = qscriptvalue_cast<ulong>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        _q_self->replaceData(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        ulong _q_arg0 = qscriptvalue_cast<ulong>(context->argument(0));
        ulong _q_arg1 = qscriptvalue_cast<ulong>(context->argument(1));
        QString _q_result = _q_self->substringData(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QDomCharacterData");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomCharacterData_throw_ambiguity_error_helper(context,
        qtscript_QDomCharacterData_function_names[_id+1],
        qtscript_QDomCharacterData_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDomCharacterData_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDomCharacterData(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QDomCharacterData _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QDomCharacterData _q_arg0 = qscriptvalue_cast<QDomCharacterData>(context->argument(0));
        QDomCharacterData _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomCharacterData_throw_ambiguity_error_helper(context,
        qtscript_QDomCharacterData_function_names[_id],
        qtscript_QDomCharacterData_function_signatures[_id]);
}

QScriptValue qtscript_create_QDomCharacterData_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDomCharacterData*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDomCharacterData*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDomNode*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDomCharacterData_prototype_call, qtscript_QDomCharacterData_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDomCharacterData_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDomCharacterData>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QDomCharacterData*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDomCharacterData_static_call, proto, qtscript_QDomCharacterData_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
