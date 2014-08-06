#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qactiongroup.h>
#include <QVariant>
#include <qaction.h>
#include <qactiongroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qicon.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QActionGroup.h"

static const char * const qtscript_QActionGroup_function_names[] = {
    "QActionGroup"
    // static
    // prototype
    , "actions"
    , "addAction"
    , "checkedAction"
    , "removeAction"
    , "toString"
};

static const char * const qtscript_QActionGroup_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , "QAction a\nQIcon icon, String text\nString text"
    , ""
    , "QAction a"
""
};

static const int qtscript_QActionGroup_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 2
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QActionGroup_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QActionGroup::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QActionGroup*)
Q_DECLARE_METATYPE(QtScriptShell_QActionGroup*)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QList<QAction* >)

//
// QActionGroup
//

static QScriptValue qtscript_QActionGroup_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QActionGroup* _q_self = qscriptvalue_cast<QActionGroup*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QActionGroup.%0(): this object is not a QActionGroup")
            .arg(qtscript_QActionGroup_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<QAction* > _q_result = _q_self->actions();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QAction*>(context->argument(0))) {
            QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
            QAction* _q_result = _q_self->addAction(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QAction* _q_result = _q_self->addAction(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QAction* _q_result = _q_self->addAction(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->checkedAction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        _q_self->removeAction(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QActionGroup");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QActionGroup_throw_ambiguity_error_helper(context,
        qtscript_QActionGroup_function_names[_id+1],
        qtscript_QActionGroup_function_signatures[_id+1]);
}

static QScriptValue qtscript_QActionGroup_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QActionGroup(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QActionGroup* _q_cpp_result = new QtScriptShell_QActionGroup(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QActionGroup*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QActionGroup_throw_ambiguity_error_helper(context,
        qtscript_QActionGroup_function_names[_id],
        qtscript_QActionGroup_function_signatures[_id]);
}

static QScriptValue qtscript_QActionGroup_toScriptValue(QScriptEngine *engine, QActionGroup* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QActionGroup_fromScriptValue(const QScriptValue &value, QActionGroup* &out)
{
    out = qobject_cast<QActionGroup*>(value.toQObject());
}

QScriptValue qtscript_create_QActionGroup_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QActionGroup*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QActionGroup*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QActionGroup_prototype_call, qtscript_QActionGroup_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QActionGroup_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QActionGroup*>(engine, qtscript_QActionGroup_toScriptValue, 
        qtscript_QActionGroup_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QActionGroup_static_call, proto, qtscript_QActionGroup_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
