#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qhttp.h>
#include <QVariant>
#include <qlist.h>
#include <qpair.h>
#include <qstringlist.h>

#include "qtscriptshell_QHttpHeader.h"

static const char * const qtscript_QHttpHeader_function_names[] = {
    "QHttpHeader"
    // static
    // prototype
    , "addValue"
    , "allValues"
    , "contentLength"
    , "contentType"
    , "hasContentLength"
    , "hasContentType"
    , "hasKey"
    , "isValid"
    , "keys"
    , "majorVersion"
    , "minorVersion"
    , "removeAllValues"
    , "removeValue"
    , "setContentLength"
    , "setContentType"
    , "setValue"
    , "setValues"
    , "toString"
    , "value"
    , "values"
};

static const char * const qtscript_QHttpHeader_function_signatures[] = {
    "\nString str"
    // static
    // prototype
    , "String key, String value"
    , "String key"
    , ""
    , ""
    , ""
    , ""
    , "String key"
    , ""
    , ""
    , ""
    , ""
    , "String key"
    , "String key"
    , "int len"
    , "String type"
    , "String key, String value"
    , "List values"
    , ""
    , "String key"
    , ""
};

static const int qtscript_QHttpHeader_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QHttpHeader_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QHttpHeader::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QHttpHeader*)
Q_DECLARE_METATYPE(QtScriptShell_QHttpHeader*)
template <> \
struct QMetaTypeId< QPair<QString,QString> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QPair<QString,QString> >("QPair<QString,QString>"); \
        return metatype_id; \
    } \
};
template <> \
struct QMetaTypeId< QList<QPair<QString,QString> > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QList<QPair<QString,QString> > >("QList<QPair<QString,QString> >"); \
        return metatype_id; \
    } \
};

//
// QHttpHeader
//

static QScriptValue qtscript_QHttpHeader_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QHttpHeader* _q_self = qscriptvalue_cast<QHttpHeader*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QHttpHeader.%0(): this object is not a QHttpHeader")
            .arg(qtscript_QHttpHeader_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->addValue(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_result = _q_self->allValues(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        uint _q_result = _q_self->contentLength();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->contentType();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasContentLength();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasContentType();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->hasKey(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->keys();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->majorVersion();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->minorVersion();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->removeAllValues(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->removeValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setContentLength(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setContentType(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setValue(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QList<QPair<QString,QString> > _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setValues(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toString();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_result = _q_self->value(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QList<QPair<QString,QString> > _q_result = _q_self->values();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHttpHeader_throw_ambiguity_error_helper(context,
        qtscript_QHttpHeader_function_names[_id+1],
        qtscript_QHttpHeader_function_signatures[_id+1]);
}

static QScriptValue qtscript_QHttpHeader_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QHttpHeader(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QHttpHeader* _q_cpp_result = new QtScriptShell_QHttpHeader();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QHttpHeader*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QtScriptShell_QHttpHeader* _q_cpp_result = new QtScriptShell_QHttpHeader(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QHttpHeader*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHttpHeader_throw_ambiguity_error_helper(context,
        qtscript_QHttpHeader_function_names[_id],
        qtscript_QHttpHeader_function_signatures[_id]);
}

QScriptValue qtscript_create_QHttpHeader_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QHttpHeader*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QHttpHeader*)0));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QHttpHeader_prototype_call, qtscript_QHttpHeader_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QHttpHeader_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QHttpHeader*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QHttpHeader_static_call, proto, qtscript_QHttpHeader_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
