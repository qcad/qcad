#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsystemtrayicon.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qicon.h>
#include <qlist.h>
#include <qmenu.h>
#include <qobject.h>
#include <qrect.h>
#include <qsystemtrayicon.h>

#include "qtscriptshell_QSystemTrayIcon.h"

static const char * const qtscript_QSystemTrayIcon_function_names[] = {
    "QSystemTrayIcon"
    // static
    , "isSystemTrayAvailable"
    , "supportsMessages"
    // prototype
    , "contextMenu"
    , "geometry"
    , "setContextMenu"
    , "showMessage"
    , "toString"
};

static const char * const qtscript_QSystemTrayIcon_function_signatures[] = {
    "QObject parent\nQIcon icon, QObject parent"
    // static
    , ""
    , ""
    // prototype
    , ""
    , ""
    , "QMenu menu"
    , "String title, String msg, MessageIcon icon, int msecs"
""
};

static const int qtscript_QSystemTrayIcon_function_lengths[] = {
    2
    // static
    , 0
    , 0
    // prototype
    , 0
    , 0
    , 1
    , 4
    , 0
};

static QScriptValue qtscript_QSystemTrayIcon_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSystemTrayIcon::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSystemTrayIcon*)
Q_DECLARE_METATYPE(QtScriptShell_QSystemTrayIcon*)
Q_DECLARE_METATYPE(QSystemTrayIcon::MessageIcon)
Q_DECLARE_METATYPE(QSystemTrayIcon::ActivationReason)
Q_DECLARE_METATYPE(QMenu*)

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
// QSystemTrayIcon::MessageIcon
//

static const QSystemTrayIcon::MessageIcon qtscript_QSystemTrayIcon_MessageIcon_values[] = {
    QSystemTrayIcon::NoIcon
    , QSystemTrayIcon::Information
    , QSystemTrayIcon::Warning
    , QSystemTrayIcon::Critical
};

static const char * const qtscript_QSystemTrayIcon_MessageIcon_keys[] = {
    "NoIcon"
    , "Information"
    , "Warning"
    , "Critical"
};

static QString qtscript_QSystemTrayIcon_MessageIcon_toStringHelper(QSystemTrayIcon::MessageIcon value)
{
    if ((value >= QSystemTrayIcon::NoIcon) && (value <= QSystemTrayIcon::Critical))
        return qtscript_QSystemTrayIcon_MessageIcon_keys[static_cast<int>(value)-static_cast<int>(QSystemTrayIcon::NoIcon)];
    return QString();
}

static QScriptValue qtscript_QSystemTrayIcon_MessageIcon_toScriptValue(QScriptEngine *engine, const QSystemTrayIcon::MessageIcon &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSystemTrayIcon"));
    return clazz.property(qtscript_QSystemTrayIcon_MessageIcon_toStringHelper(value));
}

static void qtscript_QSystemTrayIcon_MessageIcon_fromScriptValue(const QScriptValue &value, QSystemTrayIcon::MessageIcon &out)
{
    out = qvariant_cast<QSystemTrayIcon::MessageIcon>(value.toVariant());
}

static QScriptValue qtscript_construct_QSystemTrayIcon_MessageIcon(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSystemTrayIcon::NoIcon) && (arg <= QSystemTrayIcon::Critical))
        return qScriptValueFromValue(engine,  static_cast<QSystemTrayIcon::MessageIcon>(arg));
    return context->throwError(QString::fromLatin1("MessageIcon(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSystemTrayIcon_MessageIcon_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSystemTrayIcon::MessageIcon value = qscriptvalue_cast<QSystemTrayIcon::MessageIcon>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSystemTrayIcon_MessageIcon_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSystemTrayIcon::MessageIcon value = qscriptvalue_cast<QSystemTrayIcon::MessageIcon>(context->thisObject());
    return QScriptValue(engine, qtscript_QSystemTrayIcon_MessageIcon_toStringHelper(value));
}

static QScriptValue qtscript_create_QSystemTrayIcon_MessageIcon_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSystemTrayIcon_MessageIcon,
        qtscript_QSystemTrayIcon_MessageIcon_valueOf, qtscript_QSystemTrayIcon_MessageIcon_toString);
    qScriptRegisterMetaType<QSystemTrayIcon::MessageIcon>(engine, qtscript_QSystemTrayIcon_MessageIcon_toScriptValue,
        qtscript_QSystemTrayIcon_MessageIcon_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSystemTrayIcon_MessageIcon_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSystemTrayIcon_MessageIcon_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSystemTrayIcon::ActivationReason
//

static const QSystemTrayIcon::ActivationReason qtscript_QSystemTrayIcon_ActivationReason_values[] = {
    QSystemTrayIcon::Unknown
    , QSystemTrayIcon::Context
    , QSystemTrayIcon::DoubleClick
    , QSystemTrayIcon::Trigger
    , QSystemTrayIcon::MiddleClick
};

static const char * const qtscript_QSystemTrayIcon_ActivationReason_keys[] = {
    "Unknown"
    , "Context"
    , "DoubleClick"
    , "Trigger"
    , "MiddleClick"
};

static QString qtscript_QSystemTrayIcon_ActivationReason_toStringHelper(QSystemTrayIcon::ActivationReason value)
{
    if ((value >= QSystemTrayIcon::Unknown) && (value <= QSystemTrayIcon::MiddleClick))
        return qtscript_QSystemTrayIcon_ActivationReason_keys[static_cast<int>(value)-static_cast<int>(QSystemTrayIcon::Unknown)];
    return QString();
}

static QScriptValue qtscript_QSystemTrayIcon_ActivationReason_toScriptValue(QScriptEngine *engine, const QSystemTrayIcon::ActivationReason &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSystemTrayIcon"));
    return clazz.property(qtscript_QSystemTrayIcon_ActivationReason_toStringHelper(value));
}

static void qtscript_QSystemTrayIcon_ActivationReason_fromScriptValue(const QScriptValue &value, QSystemTrayIcon::ActivationReason &out)
{
    out = qvariant_cast<QSystemTrayIcon::ActivationReason>(value.toVariant());
}

static QScriptValue qtscript_construct_QSystemTrayIcon_ActivationReason(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSystemTrayIcon::Unknown) && (arg <= QSystemTrayIcon::MiddleClick))
        return qScriptValueFromValue(engine,  static_cast<QSystemTrayIcon::ActivationReason>(arg));
    return context->throwError(QString::fromLatin1("ActivationReason(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSystemTrayIcon_ActivationReason_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSystemTrayIcon::ActivationReason value = qscriptvalue_cast<QSystemTrayIcon::ActivationReason>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSystemTrayIcon_ActivationReason_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSystemTrayIcon::ActivationReason value = qscriptvalue_cast<QSystemTrayIcon::ActivationReason>(context->thisObject());
    return QScriptValue(engine, qtscript_QSystemTrayIcon_ActivationReason_toStringHelper(value));
}

static QScriptValue qtscript_create_QSystemTrayIcon_ActivationReason_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSystemTrayIcon_ActivationReason,
        qtscript_QSystemTrayIcon_ActivationReason_valueOf, qtscript_QSystemTrayIcon_ActivationReason_toString);
    qScriptRegisterMetaType<QSystemTrayIcon::ActivationReason>(engine, qtscript_QSystemTrayIcon_ActivationReason_toScriptValue,
        qtscript_QSystemTrayIcon_ActivationReason_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSystemTrayIcon_ActivationReason_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSystemTrayIcon_ActivationReason_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSystemTrayIcon
//

static QScriptValue qtscript_QSystemTrayIcon_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSystemTrayIcon* _q_self = qscriptvalue_cast<QSystemTrayIcon*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSystemTrayIcon.%0(): this object is not a QSystemTrayIcon")
            .arg(qtscript_QSystemTrayIcon_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QMenu* _q_result = _q_self->contextMenu();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->geometry();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QMenu* _q_arg0 = qscriptvalue_cast<QMenu*>(context->argument(0));
        _q_self->setContextMenu(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->showMessage(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QSystemTrayIcon::MessageIcon _q_arg2 = qscriptvalue_cast<QSystemTrayIcon::MessageIcon>(context->argument(2));
        _q_self->showMessage(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QSystemTrayIcon::MessageIcon _q_arg2 = qscriptvalue_cast<QSystemTrayIcon::MessageIcon>(context->argument(2));
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->showMessage(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QSystemTrayIcon");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSystemTrayIcon_throw_ambiguity_error_helper(context,
        qtscript_QSystemTrayIcon_function_names[_id+3],
        qtscript_QSystemTrayIcon_function_signatures[_id+3]);
}

static QScriptValue qtscript_QSystemTrayIcon_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSystemTrayIcon(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSystemTrayIcon* _q_cpp_result = new QtScriptShell_QSystemTrayIcon();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSystemTrayIcon*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QSystemTrayIcon* _q_cpp_result = new QtScriptShell_QSystemTrayIcon(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSystemTrayIcon*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QIcon>() == context->argument(0).toVariant().userType())) {
            QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
            QtScriptShell_QSystemTrayIcon* _q_cpp_result = new QtScriptShell_QSystemTrayIcon(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSystemTrayIcon*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QSystemTrayIcon* _q_cpp_result = new QtScriptShell_QSystemTrayIcon(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSystemTrayIcon*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = QSystemTrayIcon::isSystemTrayAvailable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = QSystemTrayIcon::supportsMessages();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSystemTrayIcon_throw_ambiguity_error_helper(context,
        qtscript_QSystemTrayIcon_function_names[_id],
        qtscript_QSystemTrayIcon_function_signatures[_id]);
}

static QScriptValue qtscript_QSystemTrayIcon_toScriptValue(QScriptEngine *engine, QSystemTrayIcon* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSystemTrayIcon_fromScriptValue(const QScriptValue &value, QSystemTrayIcon* &out)
{
    out = qobject_cast<QSystemTrayIcon*>(value.toQObject());
}

QScriptValue qtscript_create_QSystemTrayIcon_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSystemTrayIcon*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSystemTrayIcon*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSystemTrayIcon_prototype_call, qtscript_QSystemTrayIcon_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSystemTrayIcon_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSystemTrayIcon*>(engine, qtscript_QSystemTrayIcon_toScriptValue, 
        qtscript_QSystemTrayIcon_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSystemTrayIcon_static_call, proto, qtscript_QSystemTrayIcon_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSystemTrayIcon_static_call,
            qtscript_QSystemTrayIcon_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QSystemTrayIcon_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("MessageIcon"),
        qtscript_create_QSystemTrayIcon_MessageIcon_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ActivationReason"),
        qtscript_create_QSystemTrayIcon_ActivationReason_class(engine, ctor));
    return ctor;
}
