#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qinputcontext.h>
#include <QTextFormat>
#include <QVariant>
#include <qaction.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qfont.h>
#include <qinputcontext.h>
#include <qlist.h>
#include <qobject.h>
#include <qtextformat.h>
#include <qwidget.h>

#include "qtscriptshell_QInputContext.h"

static const char * const qtscript_QInputContext_function_names[] = {
    "QInputContext"
    // static
    // prototype
    , "actions"
    , "filterEvent"
    , "focusWidget"
    , "font"
    , "identifierName"
    , "isComposing"
    , "language"
    , "mouseHandler"
    , "reset"
    , "sendEvent"
    , "standardFormat"
    , "update"
    , "widgetDestroyed"
    , "toString"
};

static const char * const qtscript_QInputContext_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , "QEvent event"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int x, QMouseEvent event"
    , ""
    , "QInputMethodEvent event"
    , "StandardFormat s"
    , ""
    , "QWidget w"
""
};

static const int qtscript_QInputContext_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 1
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QInputContext_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QInputContext::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QInputContext*)
Q_DECLARE_METATYPE(QtScriptShell_QInputContext*)
Q_DECLARE_METATYPE(QInputContext::StandardFormat)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QList<QAction*>)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QMouseEvent*)
Q_DECLARE_METATYPE(QInputMethodEvent)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QInputContext::StandardFormat
//

static const QInputContext::StandardFormat qtscript_QInputContext_StandardFormat_values[] = {
    QInputContext::PreeditFormat
    , QInputContext::SelectionFormat
};

static const char * const qtscript_QInputContext_StandardFormat_keys[] = {
    "PreeditFormat"
    , "SelectionFormat"
};

static QString qtscript_QInputContext_StandardFormat_toStringHelper(QInputContext::StandardFormat value)
{
    if ((value >= QInputContext::PreeditFormat) && (value <= QInputContext::SelectionFormat))
        return qtscript_QInputContext_StandardFormat_keys[static_cast<int>(value)-static_cast<int>(QInputContext::PreeditFormat)];
    return QString();
}

static QScriptValue qtscript_QInputContext_StandardFormat_toScriptValue(QScriptEngine *engine, const QInputContext::StandardFormat &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QInputContext"));
    return clazz.property(qtscript_QInputContext_StandardFormat_toStringHelper(value));
}

static void qtscript_QInputContext_StandardFormat_fromScriptValue(const QScriptValue &value, QInputContext::StandardFormat &out)
{
    out = qvariant_cast<QInputContext::StandardFormat>(value.toVariant());
}

static QScriptValue qtscript_construct_QInputContext_StandardFormat(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QInputContext::PreeditFormat) && (arg <= QInputContext::SelectionFormat))
        return qScriptValueFromValue(engine,  static_cast<QInputContext::StandardFormat>(arg));
    return context->throwError(QString::fromLatin1("StandardFormat(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QInputContext_StandardFormat_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QInputContext::StandardFormat value = qscriptvalue_cast<QInputContext::StandardFormat>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QInputContext_StandardFormat_toString(QScriptContext *context, QScriptEngine *engine)
{
    QInputContext::StandardFormat value = qscriptvalue_cast<QInputContext::StandardFormat>(context->thisObject());
    return QScriptValue(engine, qtscript_QInputContext_StandardFormat_toStringHelper(value));
}

static QScriptValue qtscript_create_QInputContext_StandardFormat_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QInputContext_StandardFormat,
        qtscript_QInputContext_StandardFormat_valueOf, qtscript_QInputContext_StandardFormat_toString);
    qScriptRegisterMetaType<QInputContext::StandardFormat>(engine, qtscript_QInputContext_StandardFormat_toScriptValue,
        qtscript_QInputContext_StandardFormat_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QInputContext_StandardFormat_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QInputContext_StandardFormat_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QInputContext
//

static QScriptValue qtscript_QInputContext_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 13;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QInputContext* _q_self = qscriptvalue_cast<QInputContext*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QInputContext.%0(): this object is not a QInputContext")
            .arg(qtscript_QInputContext_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<QAction*> _q_result = _q_self->actions();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QEvent* _q_arg0 = qscriptvalue_cast<QEvent*>(context->argument(0));
        bool _q_result = _q_self->filterEvent(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->focusWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QFont _q_result = _q_self->font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->identifierName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isComposing();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->language();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QMouseEvent* _q_arg1 = qscriptvalue_cast<QMouseEvent*>(context->argument(1));
        _q_self->mouseHandler(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        _q_self->reset();
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QInputMethodEvent _q_arg0 = qscriptvalue_cast<QInputMethodEvent>(context->argument(0));
        _q_self->sendEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QInputContext::StandardFormat _q_arg0 = qscriptvalue_cast<QInputContext::StandardFormat>(context->argument(0));
        QTextFormat _q_result = _q_self->standardFormat(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        _q_self->update();
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->widgetDestroyed(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13: {
    QString result = QString::fromLatin1("QInputContext");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QInputContext_throw_ambiguity_error_helper(context,
        qtscript_QInputContext_function_names[_id+1],
        qtscript_QInputContext_function_signatures[_id+1]);
}

static QScriptValue qtscript_QInputContext_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QInputContext(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QInputContext* _q_cpp_result = new QtScriptShell_QInputContext();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QInputContext*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QInputContext* _q_cpp_result = new QtScriptShell_QInputContext(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QInputContext*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QInputContext_throw_ambiguity_error_helper(context,
        qtscript_QInputContext_function_names[_id],
        qtscript_QInputContext_function_signatures[_id]);
}

static QScriptValue qtscript_QInputContext_toScriptValue(QScriptEngine *engine, QInputContext* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QInputContext_fromScriptValue(const QScriptValue &value, QInputContext* &out)
{
    out = qobject_cast<QInputContext*>(value.toQObject());
}

QScriptValue qtscript_create_QInputContext_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QInputContext*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QInputContext*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 14; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QInputContext_prototype_call, qtscript_QInputContext_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QInputContext_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QInputContext*>(engine, qtscript_QInputContext_toScriptValue, 
        qtscript_QInputContext_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QInputContext_static_call, proto, qtscript_QInputContext_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StandardFormat"),
        qtscript_create_QInputContext_StandardFormat_class(engine, ctor));
    return ctor;
}
