#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qhttp.h>
#include <QVariant>
#include <qhttp.h>
#include <qlist.h>
#include <qpair.h>
#include <qstringlist.h>

#include "qtscriptshell_QHttpRequestHeader.h"

static const char * const qtscript_QHttpRequestHeader_function_names[] = {
    "QHttpRequestHeader"
    // static
    // prototype
    , "method"
    , "path"
    , "setRequest"
};

static const char * const qtscript_QHttpRequestHeader_function_signatures[] = {
    "\nQHttpRequestHeader header\nString method, String path, int majorVer, int minorVer\nString str"
    // static
    // prototype
    , ""
    , ""
    , "String method, String path, int majorVer, int minorVer"
};

static const int qtscript_QHttpRequestHeader_function_lengths[] = {
    4
    // static
    // prototype
    , 0
    , 0
    , 4
};

static QScriptValue qtscript_QHttpRequestHeader_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QHttpRequestHeader::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QHttpRequestHeader)
Q_DECLARE_METATYPE(QHttpRequestHeader*)
Q_DECLARE_METATYPE(QtScriptShell_QHttpRequestHeader)
Q_DECLARE_METATYPE(QtScriptShell_QHttpRequestHeader*)
Q_DECLARE_METATYPE(QHttpHeader*)

//
// QHttpRequestHeader
//

static QScriptValue qtscript_QHttpRequestHeader_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QHttpRequestHeader* _q_self = qscriptvalue_cast<QHttpRequestHeader*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QHttpRequestHeader.%0(): this object is not a QHttpRequestHeader")
            .arg(qtscript_QHttpRequestHeader_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->method();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->path();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setRequest(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->setRequest(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setRequest(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHttpRequestHeader_throw_ambiguity_error_helper(context,
        qtscript_QHttpRequestHeader_function_names[_id+1],
        qtscript_QHttpRequestHeader_function_signatures[_id+1]);
}

static QScriptValue qtscript_QHttpRequestHeader_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QHttpRequestHeader(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QHttpRequestHeader _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QHttpRequestHeader)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QHttpRequestHeader>() == context->argument(0).toVariant().userType())) {
            QHttpRequestHeader _q_arg0 = qscriptvalue_cast<QHttpRequestHeader>(context->argument(0));
            QtScriptShell_QHttpRequestHeader _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QHttpRequestHeader)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QHttpRequestHeader _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QHttpRequestHeader)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QtScriptShell_QHttpRequestHeader _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QHttpRequestHeader)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        int _q_arg2 = context->argument(2).toInt32();
        QtScriptShell_QHttpRequestHeader _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QHttpRequestHeader)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QtScriptShell_QHttpRequestHeader _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QHttpRequestHeader)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHttpRequestHeader_throw_ambiguity_error_helper(context,
        qtscript_QHttpRequestHeader_function_names[_id],
        qtscript_QHttpRequestHeader_function_signatures[_id]);
}

QScriptValue qtscript_create_QHttpRequestHeader_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QHttpRequestHeader*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QHttpRequestHeader*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QHttpHeader*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QHttpRequestHeader_prototype_call, qtscript_QHttpRequestHeader_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QHttpRequestHeader_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QHttpRequestHeader>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QHttpRequestHeader*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QHttpRequestHeader_static_call, proto, qtscript_QHttpRequestHeader_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
