#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qwidgetaction.h>
#include <QVariant>
#include <qactiongroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qfont.h>
#include <qgraphicswidget.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlist.h>
#include <qmenu.h>
#include <qobject.h>
#include <qwidget.h>
#include <qwidgetaction.h>

#include "qtscriptshell_QWidgetAction.h"

static const char * const qtscript_QWidgetAction_function_names[] = {
    "QWidgetAction"
    // static
    // prototype
    , "defaultWidget"
    , "releaseWidget"
    , "requestWidget"
    , "setDefaultWidget"
    , "toString"
};

static const char * const qtscript_QWidgetAction_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , "QWidget widget"
    , "QWidget parent"
    , "QWidget w"
""
};

static const int qtscript_QWidgetAction_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QWidgetAction_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWidgetAction::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWidgetAction*)
Q_DECLARE_METATYPE(QtScriptShell_QWidgetAction*)
Q_DECLARE_METATYPE(QAction*)

//
// QWidgetAction
//

static QScriptValue qtscript_QWidgetAction_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QWidgetAction* _q_self = qscriptvalue_cast<QWidgetAction*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWidgetAction.%0(): this object is not a QWidgetAction")
            .arg(qtscript_QWidgetAction_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->defaultWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->releaseWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QWidget* _q_result = _q_self->requestWidget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setDefaultWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QWidgetAction");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWidgetAction_throw_ambiguity_error_helper(context,
        qtscript_QWidgetAction_function_names[_id+1],
        qtscript_QWidgetAction_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWidgetAction_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWidgetAction(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QWidgetAction* _q_cpp_result = new QtScriptShell_QWidgetAction(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWidgetAction*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWidgetAction_throw_ambiguity_error_helper(context,
        qtscript_QWidgetAction_function_names[_id],
        qtscript_QWidgetAction_function_signatures[_id]);
}

static QScriptValue qtscript_QWidgetAction_toScriptValue(QScriptEngine *engine, QWidgetAction* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QWidgetAction_fromScriptValue(const QScriptValue &value, QWidgetAction* &out)
{
    out = qobject_cast<QWidgetAction*>(value.toQObject());
}

QScriptValue qtscript_create_QWidgetAction_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWidgetAction*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWidgetAction*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAction*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWidgetAction_prototype_call, qtscript_QWidgetAction_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWidgetAction_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QWidgetAction*>(engine, qtscript_QWidgetAction_toScriptValue, 
        qtscript_QWidgetAction_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWidgetAction_static_call, proto, qtscript_QWidgetAction_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
