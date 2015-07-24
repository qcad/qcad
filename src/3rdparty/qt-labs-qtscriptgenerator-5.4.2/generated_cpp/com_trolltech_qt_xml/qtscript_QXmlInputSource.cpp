#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qxml.h>
#include <QVariant>
#include <qbytearray.h>
#include <qiodevice.h>

#include "qtscriptshell_QXmlInputSource.h"

static const char * const qtscript_QXmlInputSource_function_names[] = {
    "QXmlInputSource"
    // static
    // prototype
    , "data"
    , "fetchData"
    , "next"
    , "reset"
    , "setData"
    , "toString"
};

static const char * const qtscript_QXmlInputSource_function_signatures[] = {
    "\nQIODevice dev"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "QByteArray dat\nString dat"
""
};

static const int qtscript_QXmlInputSource_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QXmlInputSource_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QXmlInputSource::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QXmlInputSource*)
Q_DECLARE_METATYPE(QtScriptShell_QXmlInputSource*)
Q_DECLARE_METATYPE(QIODevice*)

//
// QXmlInputSource
//

static QScriptValue qtscript_QXmlInputSource_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QXmlInputSource* _q_self = qscriptvalue_cast<QXmlInputSource*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QXmlInputSource.%0(): this object is not a QXmlInputSource")
            .arg(qtscript_QXmlInputSource_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->data();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->fetchData();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QChar _q_result = _q_self->next();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->reset();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            _q_self->setData(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->setData(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QXmlInputSource");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlInputSource_throw_ambiguity_error_helper(context,
        qtscript_QXmlInputSource_function_names[_id+1],
        qtscript_QXmlInputSource_function_signatures[_id+1]);
}

static QScriptValue qtscript_QXmlInputSource_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QXmlInputSource(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QXmlInputSource* _q_cpp_result = new QtScriptShell_QXmlInputSource();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlInputSource*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        QtScriptShell_QXmlInputSource* _q_cpp_result = new QtScriptShell_QXmlInputSource(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QXmlInputSource*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QXmlInputSource_throw_ambiguity_error_helper(context,
        qtscript_QXmlInputSource_function_names[_id],
        qtscript_QXmlInputSource_function_signatures[_id]);
}

QScriptValue qtscript_create_QXmlInputSource_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QXmlInputSource*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QXmlInputSource*)0));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QXmlInputSource_prototype_call, qtscript_QXmlInputSource_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QXmlInputSource_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QXmlInputSource*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QXmlInputSource_static_call, proto, qtscript_QXmlInputSource_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
