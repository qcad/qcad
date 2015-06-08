#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsettings.h>
#include <QStringList>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qsettings.h>
#include <qstringlist.h>
#include <qtextcodec.h>

#include "qtscriptshell_QSettings.h"

static const char * const qtscript_QSettings_function_names[] = {
    "QSettings"
    // static
    , "defaultFormat"
    , "setDefaultFormat"
    , "setPath"
    // prototype
    , "allKeys"
    , "applicationName"
    , "beginGroup"
    , "beginReadArray"
    , "beginWriteArray"
    , "childGroups"
    , "childKeys"
    , "clear"
    , "contains"
    , "endArray"
    , "endGroup"
    , "fallbacksEnabled"
    , "fileName"
    , "format"
    , "group"
    , "iniCodec"
    , "isWritable"
    , "organizationName"
    , "remove"
    , "scope"
    , "setArrayIndex"
    , "setFallbacksEnabled"
    , "setIniCodec"
    , "setValue"
    , "status"
    , "sync"
    , "value"
    , "toString"
};

static const char * const qtscript_QSettings_function_signatures[] = {
    "QObject parent\nFormat format, Scope scope, String organization, String application, QObject parent\nScope scope, String organization, String application, QObject parent\nString fileName, Format format, QObject parent\nString organization, String application, QObject parent"
    // static
    , ""
    , "Format format"
    , "Format format, Scope scope, String path"
    // prototype
    , ""
    , ""
    , "String prefix"
    , "String prefix"
    , "String prefix, int size"
    , ""
    , ""
    , ""
    , "String key"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String key"
    , ""
    , "int i"
    , "bool b"
    , "QTextCodec codec\nchar codecName"
    , "String key, Object value"
    , ""
    , ""
    , "String key, Object defaultValue"
""
};

static const int qtscript_QSettings_function_lengths[] = {
    5
    // static
    , 0
    , 1
    , 3
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 2
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 1
    , 1
    , 2
    , 0
    , 0
    , 2
    , 0
};

static QScriptValue qtscript_QSettings_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSettings::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSettings*)
Q_DECLARE_METATYPE(QtScriptShell_QSettings*)
Q_DECLARE_METATYPE(QSettings::Scope)
Q_DECLARE_METATYPE(QSettings::Format)
Q_DECLARE_METATYPE(QSettings::Status)
Q_DECLARE_METATYPE(QTextCodec*)
Q_DECLARE_METATYPE(const char*)

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
// QSettings::Scope
//

static const QSettings::Scope qtscript_QSettings_Scope_values[] = {
    QSettings::UserScope
    , QSettings::SystemScope
};

static const char * const qtscript_QSettings_Scope_keys[] = {
    "UserScope"
    , "SystemScope"
};

static QString qtscript_QSettings_Scope_toStringHelper(QSettings::Scope value)
{
    if ((value >= QSettings::UserScope) && (value <= QSettings::SystemScope))
        return qtscript_QSettings_Scope_keys[static_cast<int>(value)-static_cast<int>(QSettings::UserScope)];
    return QString();
}

static QScriptValue qtscript_QSettings_Scope_toScriptValue(QScriptEngine *engine, const QSettings::Scope &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSettings"));
    return clazz.property(qtscript_QSettings_Scope_toStringHelper(value));
}

static void qtscript_QSettings_Scope_fromScriptValue(const QScriptValue &value, QSettings::Scope &out)
{
    out = qvariant_cast<QSettings::Scope>(value.toVariant());
}

static QScriptValue qtscript_construct_QSettings_Scope(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSettings::UserScope) && (arg <= QSettings::SystemScope))
        return qScriptValueFromValue(engine,  static_cast<QSettings::Scope>(arg));
    return context->throwError(QString::fromLatin1("Scope(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSettings_Scope_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSettings::Scope value = qscriptvalue_cast<QSettings::Scope>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSettings_Scope_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSettings::Scope value = qscriptvalue_cast<QSettings::Scope>(context->thisObject());
    return QScriptValue(engine, qtscript_QSettings_Scope_toStringHelper(value));
}

static QScriptValue qtscript_create_QSettings_Scope_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSettings_Scope,
        qtscript_QSettings_Scope_valueOf, qtscript_QSettings_Scope_toString);
    qScriptRegisterMetaType<QSettings::Scope>(engine, qtscript_QSettings_Scope_toScriptValue,
        qtscript_QSettings_Scope_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSettings_Scope_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSettings_Scope_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSettings::Format
//

static const QSettings::Format qtscript_QSettings_Format_values[] = {
    QSettings::NativeFormat
    , QSettings::IniFormat
    , QSettings::InvalidFormat
    , QSettings::CustomFormat1
    , QSettings::CustomFormat2
    , QSettings::CustomFormat3
    , QSettings::CustomFormat4
    , QSettings::CustomFormat5
    , QSettings::CustomFormat6
    , QSettings::CustomFormat7
    , QSettings::CustomFormat8
    , QSettings::CustomFormat9
    , QSettings::CustomFormat10
    , QSettings::CustomFormat11
    , QSettings::CustomFormat12
    , QSettings::CustomFormat13
    , QSettings::CustomFormat14
    , QSettings::CustomFormat15
    , QSettings::CustomFormat16
};

static const char * const qtscript_QSettings_Format_keys[] = {
    "NativeFormat"
    , "IniFormat"
    , "InvalidFormat"
    , "CustomFormat1"
    , "CustomFormat2"
    , "CustomFormat3"
    , "CustomFormat4"
    , "CustomFormat5"
    , "CustomFormat6"
    , "CustomFormat7"
    , "CustomFormat8"
    , "CustomFormat9"
    , "CustomFormat10"
    , "CustomFormat11"
    , "CustomFormat12"
    , "CustomFormat13"
    , "CustomFormat14"
    , "CustomFormat15"
    , "CustomFormat16"
};

static QString qtscript_QSettings_Format_toStringHelper(QSettings::Format value)
{
    for (int i = 0; i < 19; ++i) {
        if (qtscript_QSettings_Format_values[i] == value)
            return QString::fromLatin1(qtscript_QSettings_Format_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QSettings_Format_toScriptValue(QScriptEngine *engine, const QSettings::Format &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSettings"));
    return clazz.property(qtscript_QSettings_Format_toStringHelper(value));
}

static void qtscript_QSettings_Format_fromScriptValue(const QScriptValue &value, QSettings::Format &out)
{
    out = qvariant_cast<QSettings::Format>(value.toVariant());
}

static QScriptValue qtscript_construct_QSettings_Format(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 19; ++i) {
        if (qtscript_QSettings_Format_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QSettings::Format>(arg));
    }
    return context->throwError(QString::fromLatin1("Format(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSettings_Format_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSettings::Format value = qscriptvalue_cast<QSettings::Format>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSettings_Format_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSettings::Format value = qscriptvalue_cast<QSettings::Format>(context->thisObject());
    return QScriptValue(engine, qtscript_QSettings_Format_toStringHelper(value));
}

static QScriptValue qtscript_create_QSettings_Format_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSettings_Format,
        qtscript_QSettings_Format_valueOf, qtscript_QSettings_Format_toString);
    qScriptRegisterMetaType<QSettings::Format>(engine, qtscript_QSettings_Format_toScriptValue,
        qtscript_QSettings_Format_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 19; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSettings_Format_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSettings_Format_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSettings::Status
//

static const QSettings::Status qtscript_QSettings_Status_values[] = {
    QSettings::NoError
    , QSettings::AccessError
    , QSettings::FormatError
};

static const char * const qtscript_QSettings_Status_keys[] = {
    "NoError"
    , "AccessError"
    , "FormatError"
};

static QString qtscript_QSettings_Status_toStringHelper(QSettings::Status value)
{
    if ((value >= QSettings::NoError) && (value <= QSettings::FormatError))
        return qtscript_QSettings_Status_keys[static_cast<int>(value)-static_cast<int>(QSettings::NoError)];
    return QString();
}

static QScriptValue qtscript_QSettings_Status_toScriptValue(QScriptEngine *engine, const QSettings::Status &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSettings"));
    return clazz.property(qtscript_QSettings_Status_toStringHelper(value));
}

static void qtscript_QSettings_Status_fromScriptValue(const QScriptValue &value, QSettings::Status &out)
{
    out = qvariant_cast<QSettings::Status>(value.toVariant());
}

static QScriptValue qtscript_construct_QSettings_Status(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSettings::NoError) && (arg <= QSettings::FormatError))
        return qScriptValueFromValue(engine,  static_cast<QSettings::Status>(arg));
    return context->throwError(QString::fromLatin1("Status(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSettings_Status_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSettings::Status value = qscriptvalue_cast<QSettings::Status>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSettings_Status_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSettings::Status value = qscriptvalue_cast<QSettings::Status>(context->thisObject());
    return QScriptValue(engine, qtscript_QSettings_Status_toStringHelper(value));
}

static QScriptValue qtscript_create_QSettings_Status_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSettings_Status,
        qtscript_QSettings_Status_valueOf, qtscript_QSettings_Status_toString);
    qScriptRegisterMetaType<QSettings::Status>(engine, qtscript_QSettings_Status_toScriptValue,
        qtscript_QSettings_Status_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSettings_Status_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSettings_Status_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSettings
//

static QScriptValue qtscript_QSettings_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 27;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSettings* _q_self = qscriptvalue_cast<QSettings*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSettings.%0(): this object is not a QSettings")
            .arg(qtscript_QSettings_function_names[_id+4]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->allKeys();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->applicationName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->beginGroup(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->beginReadArray(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->beginWriteArray(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->beginWriteArray(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->childGroups();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->childKeys();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->contains(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        _q_self->endArray();
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        _q_self->endGroup();
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fallbacksEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QSettings::Format _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->group();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QTextCodec* _q_result = _q_self->iniCodec();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isWritable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->organizationName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->remove(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QSettings::Scope _q_result = _q_self->scope();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setArrayIndex(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFallbacksEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QTextCodec*>(context->argument(0))) {
            QTextCodec* _q_arg0 = qscriptvalue_cast<QTextCodec*>(context->argument(0));
            _q_self->setIniCodec(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            _q_self->setIniCodec(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 23:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setValue(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QSettings::Status _q_result = _q_self->status();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        _q_self->sync();
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QVariant _q_result = _q_self->value(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QVariant _q_arg1 = context->argument(1).toVariant();
        QVariant _q_result = _q_self->value(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27: {
    QString result = QString::fromLatin1("QSettings");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSettings_throw_ambiguity_error_helper(context,
        qtscript_QSettings_function_names[_id+4],
        qtscript_QSettings_function_signatures[_id+4]);
}

static QScriptValue qtscript_QSettings_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSettings(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QSettings::Scope>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QSettings::Scope _q_arg0 = qscriptvalue_cast<QSettings::Scope>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QSettings::Format>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QSettings::Format _q_arg1 = qscriptvalue_cast<QSettings::Format>(context->argument(1));
            QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QSettings::Format>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QSettings::Scope>() == context->argument(1).toVariant().userType())
            && context->argument(2).isString()) {
            QSettings::Format _q_arg0 = qscriptvalue_cast<QSettings::Format>(context->argument(0));
            QSettings::Scope _q_arg1 = qscriptvalue_cast<QSettings::Scope>(context->argument(1));
            QString _q_arg2 = context->argument(2).toString();
            QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QSettings::Scope>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()
            && context->argument(2).isString()) {
            QSettings::Scope _q_arg0 = qscriptvalue_cast<QSettings::Scope>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QSettings::Format>() == context->argument(1).toVariant().userType())
            && context->argument(2).isQObject()) {
            QString _q_arg0 = context->argument(0).toString();
            QSettings::Format _q_arg1 = qscriptvalue_cast<QSettings::Format>(context->argument(1));
            QObject* _q_arg2 = context->argument(2).toQObject();
            QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isString()
            && context->argument(2).isQObject()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QObject* _q_arg2 = context->argument(2).toQObject();
            QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 4) {
        if ((qMetaTypeId<QSettings::Format>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QSettings::Scope>() == context->argument(1).toVariant().userType())
            && context->argument(2).isString()
            && context->argument(3).isString()) {
            QSettings::Format _q_arg0 = qscriptvalue_cast<QSettings::Format>(context->argument(0));
            QSettings::Scope _q_arg1 = qscriptvalue_cast<QSettings::Scope>(context->argument(1));
            QString _q_arg2 = context->argument(2).toString();
            QString _q_arg3 = context->argument(3).toString();
            QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QSettings::Scope>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()
            && context->argument(2).isString()
            && context->argument(3).isQObject()) {
            QSettings::Scope _q_arg0 = qscriptvalue_cast<QSettings::Scope>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QObject* _q_arg3 = context->argument(3).toQObject();
            QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 5) {
        QSettings::Format _q_arg0 = qscriptvalue_cast<QSettings::Format>(context->argument(0));
        QSettings::Scope _q_arg1 = qscriptvalue_cast<QSettings::Scope>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        QString _q_arg3 = context->argument(3).toString();
        QObject* _q_arg4 = context->argument(4).toQObject();
        QtScriptShell_QSettings* _q_cpp_result = new QtScriptShell_QSettings(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSettings*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QSettings::Format _q_result = QSettings::defaultFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QSettings::Format _q_arg0 = qscriptvalue_cast<QSettings::Format>(context->argument(0));
        QSettings::setDefaultFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 3) {
        QSettings::Format _q_arg0 = qscriptvalue_cast<QSettings::Format>(context->argument(0));
        QSettings::Scope _q_arg1 = qscriptvalue_cast<QSettings::Scope>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        QSettings::setPath(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSettings_throw_ambiguity_error_helper(context,
        qtscript_QSettings_function_names[_id],
        qtscript_QSettings_function_signatures[_id]);
}

static QScriptValue qtscript_QSettings_toScriptValue(QScriptEngine *engine, QSettings* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSettings_fromScriptValue(const QScriptValue &value, QSettings* &out)
{
    out = qobject_cast<QSettings*>(value.toQObject());
}

QScriptValue qtscript_create_QSettings_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSettings*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSettings*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 28; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSettings_prototype_call, qtscript_QSettings_function_lengths[i+4]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSettings_function_names[i+4]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSettings*>(engine, qtscript_QSettings_toScriptValue, 
        qtscript_QSettings_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSettings_static_call, proto, qtscript_QSettings_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSettings_static_call,
            qtscript_QSettings_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QSettings_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Scope"),
        qtscript_create_QSettings_Scope_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Format"),
        qtscript_create_QSettings_Format_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Status"),
        qtscript_create_QSettings_Status_class(engine, ctor));
    return ctor;
}
