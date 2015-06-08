#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtranslator.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qlocale.h>
#include <qobject.h>
#include <qtranslator.h>

#include "qtscriptshell_QTranslator.h"

static const char * const qtscript_QTranslator_function_names[] = {
    "QTranslator"
    // static
    // prototype
    , "isEmpty"
    , "load"
    , "toString"
};

static const char * const qtscript_QTranslator_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , "QLocale locale, String filename, String prefix, String directory, String suffix\nString filename, String directory, String search_delimiters, String suffix\nuchar data, int len, String directory"
""
};

static const int qtscript_QTranslator_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 5
    , 0
};

static QScriptValue qtscript_QTranslator_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTranslator::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTranslator*)
Q_DECLARE_METATYPE(QtScriptShell_QTranslator*)
Q_DECLARE_METATYPE(const uchar*)

//
// QTranslator
//

static QScriptValue qtscript_QTranslator_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTranslator* _q_self = qscriptvalue_cast<QTranslator*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTranslator.%0(): this object is not a QTranslator")
            .arg(qtscript_QTranslator_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->load(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QLocale>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QLocale _q_arg0 = qscriptvalue_cast<QLocale>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            bool _q_result = _q_self->load(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            bool _q_result = _q_self->load(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<const uchar*>(context->argument(0))
            && context->argument(1).isNumber()) {
            const uchar* _q_arg0 = qscriptvalue_cast<const uchar*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            bool _q_result = _q_self->load(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QLocale>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()
            && context->argument(2).isString()) {
            QLocale _q_arg0 = qscriptvalue_cast<QLocale>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            bool _q_result = _q_self->load(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()
            && context->argument(2).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            bool _q_result = _q_self->load(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<const uchar*>(context->argument(0))
            && context->argument(1).isNumber()
            && context->argument(2).isString()) {
            const uchar* _q_arg0 = qscriptvalue_cast<const uchar*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QString _q_arg2 = context->argument(2).toString();
            bool _q_result = _q_self->load(_q_arg0, _q_arg1, _q_arg2);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 4) {
        if ((qMetaTypeId<QLocale>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()
            && context->argument(2).isString()
            && context->argument(3).isString()) {
            QLocale _q_arg0 = qscriptvalue_cast<QLocale>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QString _q_arg3 = context->argument(3).toString();
            bool _q_result = _q_self->load(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()
            && context->argument(2).isString()
            && context->argument(3).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QString _q_arg3 = context->argument(3).toString();
            bool _q_result = _q_self->load(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 5) {
        QLocale _q_arg0 = qscriptvalue_cast<QLocale>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QString _q_arg4 = context->argument(4).toString();
        bool _q_result = _q_self->load(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QTranslator");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTranslator_throw_ambiguity_error_helper(context,
        qtscript_QTranslator_function_names[_id+1],
        qtscript_QTranslator_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTranslator_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTranslator(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTranslator* _q_cpp_result = new QtScriptShell_QTranslator();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTranslator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QTranslator* _q_cpp_result = new QtScriptShell_QTranslator(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTranslator*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTranslator_throw_ambiguity_error_helper(context,
        qtscript_QTranslator_function_names[_id],
        qtscript_QTranslator_function_signatures[_id]);
}

static QScriptValue qtscript_QTranslator_toScriptValue(QScriptEngine *engine, QTranslator* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTranslator_fromScriptValue(const QScriptValue &value, QTranslator* &out)
{
    out = qobject_cast<QTranslator*>(value.toQObject());
}

QScriptValue qtscript_create_QTranslator_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTranslator*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTranslator*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTranslator_prototype_call, qtscript_QTranslator_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTranslator_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTranslator*>(engine, qtscript_QTranslator_toScriptValue, 
        qtscript_QTranslator_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTranslator_static_call, proto, qtscript_QTranslator_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
