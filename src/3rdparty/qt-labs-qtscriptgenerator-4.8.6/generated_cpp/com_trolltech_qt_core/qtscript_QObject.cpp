#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qobject.h>
#include <QVarLengthArray>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QObject.h"

static const char * const qtscript_QObject_function_names[] = {
    "QObject"
    // static
    // prototype
    , "blockSignals"
    , "children"
    , "dumpObjectInfo"
    , "dumpObjectTree"
    , "dynamicPropertyNames"
    , "event"
    , "eventFilter"
    , "inherits"
    , "installEventFilter"
    , "isWidgetType"
    , "killTimer"
    , "moveToThread"
    , "parent"
    , "property"
    , "removeEventFilter"
    , "setParent"
    , "setProperty"
    , "signalsBlocked"
    , "startTimer"
    , "thread"
    , "toString"
};

static const char * const qtscript_QObject_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "bool b"
    , ""
    , ""
    , ""
    , ""
    , "QEvent arg__1"
    , "QObject arg__1, QEvent arg__2"
    , "char classname"
    , "QObject arg__1"
    , ""
    , "int id"
    , "Thread thread"
    , ""
    , "char name"
    , "QObject arg__1"
    , "QObject arg__1"
    , "char name, Object value"
    , ""
    , "int interval"
    , ""
""
};

static const int qtscript_QObject_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 2
    , 1
    , 1
    , 0
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 2
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QObject_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QObject::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QtScriptShell_QObject*)
Q_DECLARE_METATYPE(QList<QObject*>)
Q_DECLARE_METATYPE(QList<QByteArray>)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QThread*)

//
// QObject
//

static QScriptValue qtscript_QObject_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QObject* _q_self = qscriptvalue_cast<QObject*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QObject.%0(): this object is not a QObject")
            .arg(qtscript_QObject_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        bool _q_result = _q_self->blockSignals(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<QObject*> _q_result = _q_self->children();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->dumpObjectInfo();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->dumpObjectTree();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QList<QByteArray> _q_result = _q_self->dynamicPropertyNames();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QEvent* _q_arg0 = qscriptvalue_cast<QEvent*>(context->argument(0));
        bool _q_result = _q_self->event(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QEvent* _q_arg1 = qscriptvalue_cast<QEvent*>(context->argument(1));
        bool _q_result = _q_self->eventFilter(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg0 = context->argument(0).toString().toLatin1();
          const char * _q_arg0 = tmp__q_arg0.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                bool _q_result = _q_self->inherits(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        _q_self->installEventFilter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isWidgetType();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->killTimer(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QThread* _q_arg0 = qscriptvalue_cast<QThread*>(context->argument(0));
        _q_self->moveToThread(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QObject* _q_result = _q_self->parent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg0 = context->argument(0).toString().toLatin1();
          const char * _q_arg0 = tmp__q_arg0.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QVariant _q_result = _q_self->property(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        _q_self->removeEventFilter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        _q_self->setParent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg0 = context->argument(0).toString().toLatin1();
          const char * _q_arg0 = tmp__q_arg0.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QVariant _q_arg1 = context->argument(1).toVariant();
        bool _q_result = _q_self->setProperty(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->signalsBlocked();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->startTimer(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QThread* _q_result = _q_self->thread();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20: {
    QString result;
    QDebug d(&result);
    d << _q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QObject_throw_ambiguity_error_helper(context,
        qtscript_QObject_function_names[_id+1],
        qtscript_QObject_function_signatures[_id+1]);
}

static QScriptValue qtscript_QObject_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QObject(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QObject* _q_cpp_result = new QtScriptShell_QObject();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QObject*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QObject* _q_cpp_result = new QtScriptShell_QObject(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QObject*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QObject_throw_ambiguity_error_helper(context,
        qtscript_QObject_function_names[_id],
        qtscript_QObject_function_signatures[_id]);
}

static QScriptValue qtscript_QObject_toScriptValue(QScriptEngine *engine, QObject* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QObject_fromScriptValue(const QScriptValue &value, QObject* &out)
{
    out = qobject_cast<QObject*>(value.toQObject());
}

QScriptValue qtscript_create_QObject_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QObject*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QObject*)0));
    for (int i = 0; i < 21; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QObject_prototype_call, qtscript_QObject_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QObject_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QObject*>(engine, qtscript_QObject_toScriptValue, 
        qtscript_QObject_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QObject_static_call, proto, qtscript_QObject_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
