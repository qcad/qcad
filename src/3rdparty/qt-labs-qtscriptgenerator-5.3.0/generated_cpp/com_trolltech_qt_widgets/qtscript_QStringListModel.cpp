#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qstringlistmodel.h>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qstringlist.h>
#include <qstringlistmodel.h>
#include <qvector.h>

#include "qtscriptshell_QStringListModel.h"

static const char * const qtscript_QStringListModel_function_names[] = {
    "QStringListModel"
    // static
    // prototype
    , "setStringList"
    , "stringList"
    , "toString"
};

static const char * const qtscript_QStringListModel_function_signatures[] = {
    "QObject parent\nList strings, QObject parent"
    // static
    // prototype
    , "List strings"
    , ""
""
};

static const int qtscript_QStringListModel_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QStringListModel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStringListModel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStringListModel*)
Q_DECLARE_METATYPE(QtScriptShell_QStringListModel*)
Q_DECLARE_METATYPE(QAbstractListModel*)

//
// QStringListModel
//

static QScriptValue qtscript_QStringListModel_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStringListModel* _q_self = qscriptvalue_cast<QStringListModel*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStringListModel.%0(): this object is not a QStringListModel")
            .arg(qtscript_QStringListModel_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setStringList(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->stringList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QStringListModel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStringListModel_throw_ambiguity_error_helper(context,
        qtscript_QStringListModel_function_names[_id+1],
        qtscript_QStringListModel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStringListModel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStringListModel(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStringListModel* _q_cpp_result = new QtScriptShell_QStringListModel();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStringListModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QStringListModel* _q_cpp_result = new QtScriptShell_QStringListModel(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStringListModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isArray()) {
            QStringList _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            QtScriptShell_QStringListModel* _q_cpp_result = new QtScriptShell_QStringListModel(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStringListModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QStringListModel* _q_cpp_result = new QtScriptShell_QStringListModel(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStringListModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStringListModel_throw_ambiguity_error_helper(context,
        qtscript_QStringListModel_function_names[_id],
        qtscript_QStringListModel_function_signatures[_id]);
}

static QScriptValue qtscript_QStringListModel_toScriptValue(QScriptEngine *engine, QStringListModel* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QStringListModel_fromScriptValue(const QScriptValue &value, QStringListModel* &out)
{
    out = qobject_cast<QStringListModel*>(value.toQObject());
}

QScriptValue qtscript_create_QStringListModel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStringListModel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStringListModel*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractListModel*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStringListModel_prototype_call, qtscript_QStringListModel_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStringListModel_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QStringListModel*>(engine, qtscript_QStringListModel_toScriptValue, 
        qtscript_QStringListModel_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStringListModel_static_call, proto, qtscript_QStringListModel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
