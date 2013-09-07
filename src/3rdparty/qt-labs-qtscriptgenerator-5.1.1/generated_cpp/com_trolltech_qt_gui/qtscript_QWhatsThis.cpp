#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qwhatsthis.h>
#include <QVariant>
#include <qaction.h>
#include <qobject.h>
#include <qpoint.h>
#include <qwidget.h>

static const char * const qtscript_QWhatsThis_function_names[] = {
    "QWhatsThis"
    // static
    , "createAction"
    , "enterWhatsThisMode"
    , "hideText"
    , "inWhatsThisMode"
    , "leaveWhatsThisMode"
    , "showText"
    // prototype
    , "toString"
};

static const char * const qtscript_QWhatsThis_function_signatures[] = {
    ""
    // static
    , "QObject parent"
    , ""
    , ""
    , ""
    , ""
    , "QPoint pos, String text, QWidget w"
    // prototype
""
};

static const int qtscript_QWhatsThis_function_lengths[] = {
    0
    // static
    , 1
    , 0
    , 0
    , 0
    , 0
    , 3
    // prototype
    , 0
};

static QScriptValue qtscript_QWhatsThis_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWhatsThis::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWhatsThis*)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QWidget*)

//
// QWhatsThis
//

static QScriptValue qtscript_QWhatsThis_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QWhatsThis* _q_self = qscriptvalue_cast<QWhatsThis*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWhatsThis.%0(): this object is not a QWhatsThis")
            .arg(qtscript_QWhatsThis_function_names[_id+7]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QWhatsThis");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWhatsThis_throw_ambiguity_error_helper(context,
        qtscript_QWhatsThis_function_names[_id+7],
        qtscript_QWhatsThis_function_signatures[_id+7]);
}

static QScriptValue qtscript_QWhatsThis_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QWhatsThis cannot be constructed"));
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QAction* _q_result = QWhatsThis::createAction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QAction* _q_result = QWhatsThis::createAction(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QWhatsThis::enterWhatsThisMode();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QWhatsThis::hideText();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = QWhatsThis::inWhatsThisMode();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QWhatsThis::leaveWhatsThisMode();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QWhatsThis::showText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        QWhatsThis::showText(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWhatsThis_throw_ambiguity_error_helper(context,
        qtscript_QWhatsThis_function_names[_id],
        qtscript_QWhatsThis_function_signatures[_id]);
}

QScriptValue qtscript_create_QWhatsThis_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWhatsThis*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWhatsThis*)0));

    engine->setDefaultPrototype(qMetaTypeId<QWhatsThis*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWhatsThis_static_call, proto, qtscript_QWhatsThis_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWhatsThis_static_call,
            qtscript_QWhatsThis_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QWhatsThis_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
