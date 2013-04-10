#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qshortcut.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qkeysequence.h>
#include <qlist.h>
#include <qobject.h>
#include <qwidget.h>

#include "qtscriptshell_QShortcut.h"

static const char * const qtscript_QShortcut_function_names[] = {
    "QShortcut"
    // static
    // prototype
    , "id"
    , "parentWidget"
    , "toString"
};

static const char * const qtscript_QShortcut_function_signatures[] = {
    "QWidget parent\nQKeySequence key, QWidget parent, char member, char ambiguousMember, ShortcutContext context"
    // static
    // prototype
    , ""
    , ""
""
};

static const int qtscript_QShortcut_function_lengths[] = {
    5
    // static
    // prototype
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QShortcut_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QShortcut::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QShortcut*)
Q_DECLARE_METATYPE(QtScriptShell_QShortcut*)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(Qt::ShortcutContext)

//
// QShortcut
//

static QScriptValue qtscript_QShortcut_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QShortcut* _q_self = qscriptvalue_cast<QShortcut*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QShortcut.%0(): this object is not a QShortcut")
            .arg(qtscript_QShortcut_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->id();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->parentWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QShortcut");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QShortcut_throw_ambiguity_error_helper(context,
        qtscript_QShortcut_function_names[_id+1],
        qtscript_QShortcut_function_signatures[_id+1]);
}

static QScriptValue qtscript_QShortcut_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QShortcut(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QShortcut* _q_cpp_result = new QtScriptShell_QShortcut(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QShortcut*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 5) {
        QKeySequence _q_arg0 = qscriptvalue_cast<QKeySequence>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        char* _q_arg2 = qscriptvalue_cast<char*>(context->argument(2));
        char* _q_arg3 = qscriptvalue_cast<char*>(context->argument(3));
        Qt::ShortcutContext _q_arg4 = qscriptvalue_cast<Qt::ShortcutContext>(context->argument(4));
        QtScriptShell_QShortcut* _q_cpp_result = new QtScriptShell_QShortcut(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QShortcut*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QShortcut_throw_ambiguity_error_helper(context,
        qtscript_QShortcut_function_names[_id],
        qtscript_QShortcut_function_signatures[_id]);
}

static QScriptValue qtscript_QShortcut_toScriptValue(QScriptEngine *engine, QShortcut* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QShortcut_fromScriptValue(const QScriptValue &value, QShortcut* &out)
{
    out = qobject_cast<QShortcut*>(value.toQObject());
}

QScriptValue qtscript_create_QShortcut_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QShortcut*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QShortcut*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QShortcut_prototype_call, qtscript_QShortcut_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QShortcut_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QShortcut*>(engine, qtscript_QShortcut_toScriptValue, 
        qtscript_QShortcut_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QShortcut_static_call, proto, qtscript_QShortcut_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
