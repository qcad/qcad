#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qaccessiblewidget.h>
#include <QVariant>
#include <qaccessible.h>
#include <qaccessiblewidget.h>
#include <qlist.h>
#include <qobject.h>
#include <qrect.h>
#include <qwidget.h>

#include "qtscriptshell_QAccessibleWidgetEx.h"

static const char * const qtscript_QAccessibleWidgetEx_function_names[] = {
    "QAccessibleWidgetEx"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QAccessibleWidgetEx_function_signatures[] = {
    "QWidget o, Role r, String name"
    // static
    // prototype
""
};

static const int qtscript_QAccessibleWidgetEx_function_lengths[] = {
    3
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QAccessibleWidgetEx_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAccessibleWidgetEx::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAccessibleWidgetEx*)
Q_DECLARE_METATYPE(QtScriptShell_QAccessibleWidgetEx*)
Q_DECLARE_METATYPE(QAccessible::Role)
Q_DECLARE_METATYPE(QAccessibleObjectEx*)

//
// QAccessibleWidgetEx
//

static QScriptValue qtscript_QAccessibleWidgetEx_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAccessibleWidgetEx* _q_self = qscriptvalue_cast<QAccessibleWidgetEx*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAccessibleWidgetEx.%0(): this object is not a QAccessibleWidgetEx")
            .arg(qtscript_QAccessibleWidgetEx_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QAccessibleWidgetEx");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleWidgetEx_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleWidgetEx_function_names[_id+1],
        qtscript_QAccessibleWidgetEx_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAccessibleWidgetEx_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAccessibleWidgetEx(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QAccessibleWidgetEx* _q_cpp_result = new QtScriptShell_QAccessibleWidgetEx(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QAccessibleWidgetEx*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QAccessible::Role _q_arg1 = qscriptvalue_cast<QAccessible::Role>(context->argument(1));
        QtScriptShell_QAccessibleWidgetEx* _q_cpp_result = new QtScriptShell_QAccessibleWidgetEx(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QAccessibleWidgetEx*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QAccessible::Role _q_arg1 = qscriptvalue_cast<QAccessible::Role>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        QtScriptShell_QAccessibleWidgetEx* _q_cpp_result = new QtScriptShell_QAccessibleWidgetEx(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QAccessibleWidgetEx*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleWidgetEx_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleWidgetEx_function_names[_id],
        qtscript_QAccessibleWidgetEx_function_signatures[_id]);
}

QScriptValue qtscript_create_QAccessibleWidgetEx_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAccessibleWidgetEx*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAccessibleWidgetEx*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAccessibleObjectEx*>()));

    engine->setDefaultPrototype(qMetaTypeId<QAccessibleWidgetEx*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAccessibleWidgetEx_static_call, proto, qtscript_QAccessibleWidgetEx_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
