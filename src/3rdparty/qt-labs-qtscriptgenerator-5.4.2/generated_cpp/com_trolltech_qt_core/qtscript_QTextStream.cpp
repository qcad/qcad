#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtextstream.h>
#include <QVariant>
#include <qbytearray.h>
#include <qiodevice.h>
#include <qlocale.h>
#include <qtextcodec.h>
#include <qtextstream.h>

#include "qtscriptshell_QTextStream.h"

static const char * const qtscript_QTextStream_function_names[] = {
    "QTextStream"
    // static
    // prototype
    , "atEnd"
    , "autoDetectUnicode"
    , "codec"
    , "device"
    , "fieldAlignment"
    , "fieldWidth"
    , "flush"
    , "generateByteOrderMark"
    , "integerBase"
    , "locale"
    , "numberFlags"
    , "padChar"
    , "pos"
    , "read"
    , "readAll"
    , "readByte"
    , "readDouble"
    , "readFloat"
    , "readInt"
    , "readLine"
    , "readLongLong"
    , "readShort"
    , "readUInt"
    , "readUShort"
    , "realNumberNotation"
    , "realNumberPrecision"
    , "reset"
    , "resetStatus"
    , "seek"
    , "setAutoDetectUnicode"
    , "setCodec"
    , "setDevice"
    , "setFieldAlignment"
    , "setFieldWidth"
    , "setGenerateByteOrderMark"
    , "setIntegerBase"
    , "setLocale"
    , "setNumberFlags"
    , "setPadChar"
    , "setRealNumberNotation"
    , "setRealNumberPrecision"
    , "setStatus"
    , "skipWhiteSpace"
    , "status"
    , "writeByte"
    , "writeByteArray"
    , "writeDouble"
    , "writeFloat"
    , "writeInt"
    , "writeShort"
    , "writeString"
    , "toString"
};

static const char * const qtscript_QTextStream_function_signatures[] = {
    "\nQIODevice device\nQByteArray array, OpenMode openMode"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "qint64 maxlen"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "qint64 maxlen"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "qint64 pos"
    , "bool enabled"
    , "QTextCodec codec\nchar codecName"
    , "QIODevice device"
    , "FieldAlignment alignment"
    , "int width"
    , "bool generate"
    , "int base"
    , "QLocale locale"
    , "NumberFlags flags"
    , "char ch"
    , "RealNumberNotation notation"
    , "int precision"
    , "Status status"
    , ""
    , ""
    , "char ch"
    , "QByteArray array"
    , "double f"
    , "float f"
    , "signed int i"
    , "signed short i"
    , "String s"
""
};

static const int qtscript_QTextStream_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
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
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QTextStream_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextStream::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextStream*)
Q_DECLARE_METATYPE(QtScriptShell_QTextStream*)
Q_DECLARE_METATYPE(QTextStream::FieldAlignment)
Q_DECLARE_METATYPE(QTextStream::RealNumberNotation)
Q_DECLARE_METATYPE(QTextStream::NumberFlag)
Q_DECLARE_METATYPE(QFlags<QTextStream::NumberFlag>)
Q_DECLARE_METATYPE(QTextStream::Status)
Q_DECLARE_METATYPE(QTextCodec*)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(signed int)
Q_DECLARE_METATYPE(signed short)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QTextStream::FieldAlignment
//

static const QTextStream::FieldAlignment qtscript_QTextStream_FieldAlignment_values[] = {
    QTextStream::AlignLeft
    , QTextStream::AlignRight
    , QTextStream::AlignCenter
    , QTextStream::AlignAccountingStyle
};

static const char * const qtscript_QTextStream_FieldAlignment_keys[] = {
    "AlignLeft"
    , "AlignRight"
    , "AlignCenter"
    , "AlignAccountingStyle"
};

static QString qtscript_QTextStream_FieldAlignment_toStringHelper(QTextStream::FieldAlignment value)
{
    if ((value >= QTextStream::AlignLeft) && (value <= QTextStream::AlignAccountingStyle))
        return qtscript_QTextStream_FieldAlignment_keys[static_cast<int>(value)-static_cast<int>(QTextStream::AlignLeft)];
    return QString();
}

static QScriptValue qtscript_QTextStream_FieldAlignment_toScriptValue(QScriptEngine *engine, const QTextStream::FieldAlignment &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextStream"));
    return clazz.property(qtscript_QTextStream_FieldAlignment_toStringHelper(value));
}

static void qtscript_QTextStream_FieldAlignment_fromScriptValue(const QScriptValue &value, QTextStream::FieldAlignment &out)
{
    out = qvariant_cast<QTextStream::FieldAlignment>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextStream_FieldAlignment(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextStream::AlignLeft) && (arg <= QTextStream::AlignAccountingStyle))
        return qScriptValueFromValue(engine,  static_cast<QTextStream::FieldAlignment>(arg));
    return context->throwError(QString::fromLatin1("FieldAlignment(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextStream_FieldAlignment_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextStream::FieldAlignment value = qscriptvalue_cast<QTextStream::FieldAlignment>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextStream_FieldAlignment_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextStream::FieldAlignment value = qscriptvalue_cast<QTextStream::FieldAlignment>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextStream_FieldAlignment_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextStream_FieldAlignment_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextStream_FieldAlignment,
        qtscript_QTextStream_FieldAlignment_valueOf, qtscript_QTextStream_FieldAlignment_toString);
    qScriptRegisterMetaType<QTextStream::FieldAlignment>(engine, qtscript_QTextStream_FieldAlignment_toScriptValue,
        qtscript_QTextStream_FieldAlignment_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextStream_FieldAlignment_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextStream_FieldAlignment_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextStream::RealNumberNotation
//

static const QTextStream::RealNumberNotation qtscript_QTextStream_RealNumberNotation_values[] = {
    QTextStream::SmartNotation
    , QTextStream::FixedNotation
    , QTextStream::ScientificNotation
};

static const char * const qtscript_QTextStream_RealNumberNotation_keys[] = {
    "SmartNotation"
    , "FixedNotation"
    , "ScientificNotation"
};

static QString qtscript_QTextStream_RealNumberNotation_toStringHelper(QTextStream::RealNumberNotation value)
{
    if ((value >= QTextStream::SmartNotation) && (value <= QTextStream::ScientificNotation))
        return qtscript_QTextStream_RealNumberNotation_keys[static_cast<int>(value)-static_cast<int>(QTextStream::SmartNotation)];
    return QString();
}

static QScriptValue qtscript_QTextStream_RealNumberNotation_toScriptValue(QScriptEngine *engine, const QTextStream::RealNumberNotation &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextStream"));
    return clazz.property(qtscript_QTextStream_RealNumberNotation_toStringHelper(value));
}

static void qtscript_QTextStream_RealNumberNotation_fromScriptValue(const QScriptValue &value, QTextStream::RealNumberNotation &out)
{
    out = qvariant_cast<QTextStream::RealNumberNotation>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextStream_RealNumberNotation(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextStream::SmartNotation) && (arg <= QTextStream::ScientificNotation))
        return qScriptValueFromValue(engine,  static_cast<QTextStream::RealNumberNotation>(arg));
    return context->throwError(QString::fromLatin1("RealNumberNotation(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextStream_RealNumberNotation_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextStream::RealNumberNotation value = qscriptvalue_cast<QTextStream::RealNumberNotation>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextStream_RealNumberNotation_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextStream::RealNumberNotation value = qscriptvalue_cast<QTextStream::RealNumberNotation>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextStream_RealNumberNotation_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextStream_RealNumberNotation_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextStream_RealNumberNotation,
        qtscript_QTextStream_RealNumberNotation_valueOf, qtscript_QTextStream_RealNumberNotation_toString);
    qScriptRegisterMetaType<QTextStream::RealNumberNotation>(engine, qtscript_QTextStream_RealNumberNotation_toScriptValue,
        qtscript_QTextStream_RealNumberNotation_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextStream_RealNumberNotation_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextStream_RealNumberNotation_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextStream::NumberFlag
//

static const QTextStream::NumberFlag qtscript_QTextStream_NumberFlag_values[] = {
    QTextStream::ShowBase
    , QTextStream::ForcePoint
    , QTextStream::ForceSign
    , QTextStream::UppercaseBase
    , QTextStream::UppercaseDigits
};

static const char * const qtscript_QTextStream_NumberFlag_keys[] = {
    "ShowBase"
    , "ForcePoint"
    , "ForceSign"
    , "UppercaseBase"
    , "UppercaseDigits"
};

static QString qtscript_QTextStream_NumberFlag_toStringHelper(QTextStream::NumberFlag value)
{
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QTextStream_NumberFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QTextStream_NumberFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QTextStream_NumberFlag_toScriptValue(QScriptEngine *engine, const QTextStream::NumberFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextStream"));
    return clazz.property(qtscript_QTextStream_NumberFlag_toStringHelper(value));
}

static void qtscript_QTextStream_NumberFlag_fromScriptValue(const QScriptValue &value, QTextStream::NumberFlag &out)
{
    out = qvariant_cast<QTextStream::NumberFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextStream_NumberFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QTextStream_NumberFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QTextStream::NumberFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("NumberFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextStream_NumberFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextStream::NumberFlag value = qscriptvalue_cast<QTextStream::NumberFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextStream_NumberFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextStream::NumberFlag value = qscriptvalue_cast<QTextStream::NumberFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextStream_NumberFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextStream_NumberFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextStream_NumberFlag,
        qtscript_QTextStream_NumberFlag_valueOf, qtscript_QTextStream_NumberFlag_toString);
    qScriptRegisterMetaType<QTextStream::NumberFlag>(engine, qtscript_QTextStream_NumberFlag_toScriptValue,
        qtscript_QTextStream_NumberFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextStream_NumberFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextStream_NumberFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextStream::NumberFlags
//

static QScriptValue qtscript_QTextStream_NumberFlags_toScriptValue(QScriptEngine *engine, const QTextStream::NumberFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QTextStream_NumberFlags_fromScriptValue(const QScriptValue &value, QTextStream::NumberFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QTextStream::NumberFlags>())
        out = qvariant_cast<QTextStream::NumberFlags>(var);
    else if (var.userType() == qMetaTypeId<QTextStream::NumberFlag>())
        out = qvariant_cast<QTextStream::NumberFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QTextStream_NumberFlags(QScriptContext *context, QScriptEngine *engine)
{
    QTextStream::NumberFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QTextStream::NumberFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QTextStream::NumberFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("NumberFlags(): argument %0 is not of type NumberFlag").arg(i));
            }
            result |= qvariant_cast<QTextStream::NumberFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QTextStream_NumberFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextStream::NumberFlags value = qscriptvalue_cast<QTextStream::NumberFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextStream_NumberFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextStream::NumberFlags value = qscriptvalue_cast<QTextStream::NumberFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 5; ++i) {
        if ((value & qtscript_QTextStream_NumberFlag_values[i]) == qtscript_QTextStream_NumberFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QTextStream_NumberFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QTextStream_NumberFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QTextStream::NumberFlags>() == otherObj.value<QTextStream::NumberFlags>())));
}

static QScriptValue qtscript_create_QTextStream_NumberFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QTextStream_NumberFlags, qtscript_QTextStream_NumberFlags_valueOf,
        qtscript_QTextStream_NumberFlags_toString, qtscript_QTextStream_NumberFlags_equals);
    qScriptRegisterMetaType<QTextStream::NumberFlags>(engine, qtscript_QTextStream_NumberFlags_toScriptValue,
        qtscript_QTextStream_NumberFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QTextStream::Status
//

static const QTextStream::Status qtscript_QTextStream_Status_values[] = {
    QTextStream::Ok
    , QTextStream::ReadPastEnd
    , QTextStream::ReadCorruptData
    , QTextStream::WriteFailed
};

static const char * const qtscript_QTextStream_Status_keys[] = {
    "Ok"
    , "ReadPastEnd"
    , "ReadCorruptData"
    , "WriteFailed"
};

static QString qtscript_QTextStream_Status_toStringHelper(QTextStream::Status value)
{
    if ((value >= QTextStream::Ok) && (value <= QTextStream::WriteFailed))
        return qtscript_QTextStream_Status_keys[static_cast<int>(value)-static_cast<int>(QTextStream::Ok)];
    return QString();
}

static QScriptValue qtscript_QTextStream_Status_toScriptValue(QScriptEngine *engine, const QTextStream::Status &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextStream"));
    return clazz.property(qtscript_QTextStream_Status_toStringHelper(value));
}

static void qtscript_QTextStream_Status_fromScriptValue(const QScriptValue &value, QTextStream::Status &out)
{
    out = qvariant_cast<QTextStream::Status>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextStream_Status(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextStream::Ok) && (arg <= QTextStream::WriteFailed))
        return qScriptValueFromValue(engine,  static_cast<QTextStream::Status>(arg));
    return context->throwError(QString::fromLatin1("Status(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextStream_Status_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextStream::Status value = qscriptvalue_cast<QTextStream::Status>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextStream_Status_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextStream::Status value = qscriptvalue_cast<QTextStream::Status>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextStream_Status_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextStream_Status_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextStream_Status,
        qtscript_QTextStream_Status_valueOf, qtscript_QTextStream_Status_toString);
    qScriptRegisterMetaType<QTextStream::Status>(engine, qtscript_QTextStream_Status_toScriptValue,
        qtscript_QTextStream_Status_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextStream_Status_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextStream_Status_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextStream
//

static QScriptValue qtscript_QTextStream_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 51;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextStream* _q_self = qscriptvalue_cast<QTextStream*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextStream.%0(): this object is not a QTextStream")
            .arg(qtscript_QTextStream_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->atEnd();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->autoDetectUnicode();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QTextCodec* _q_result = _q_self->codec();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QIODevice* _q_result = _q_self->device();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QTextStream::FieldAlignment _q_result = _q_self->fieldAlignment();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->fieldWidth();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->flush();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->generateByteOrderMark();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->integerBase();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QLocale _q_result = _q_self->locale();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QFlags<QTextStream::NumberFlag> _q_result = _q_self->numberFlags();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QChar _q_result = _q_self->padChar();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        QString _q_result = _q_self->read(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->readAll();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {

            char __result;
            char & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            int _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {

            double __result;
            double & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            double _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {

            float __result;
            float & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            float _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {

            int __result;
            int & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            int _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->readLine();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        QString _q_result = _q_self->readLine(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {

            qlonglong __result;
            qlonglong & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            qlonglong _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {

            short __result;
            short & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            short _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {

            unsigned int __result;
            unsigned int & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            unsigned int _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {

            unsigned short __result;
            unsigned short & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            unsigned short _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QTextStream::RealNumberNotation _q_result = _q_self->realNumberNotation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->realNumberPrecision();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        _q_self->reset();
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        _q_self->resetStatus();
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        bool _q_result = _q_self->seek(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAutoDetectUnicode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QTextCodec*>(context->argument(0))) {
            QTextCodec* _q_arg0 = qscriptvalue_cast<QTextCodec*>(context->argument(0));
            _q_self->setCodec(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {

            // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg0 = context->argument(0).toString().toLatin1();
          const char * _q_arg0 = tmp__q_arg0.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                      _q_self->setCodec(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        _q_self->setDevice(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        QTextStream::FieldAlignment _q_arg0 = qscriptvalue_cast<QTextStream::FieldAlignment>(context->argument(0));
        _q_self->setFieldAlignment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setFieldWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setGenerateByteOrderMark(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setIntegerBase(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        QLocale _q_arg0 = qscriptvalue_cast<QLocale>(context->argument(0));
        _q_self->setLocale(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        QFlags<QTextStream::NumberFlag> _q_arg0 = qscriptvalue_cast<QFlags<QTextStream::NumberFlag> >(context->argument(0));
        _q_self->setNumberFlags(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QChar _q_arg0 = qscriptvalue_cast<QChar>(context->argument(0));
        _q_self->setPadChar(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        QTextStream::RealNumberNotation _q_arg0 = qscriptvalue_cast<QTextStream::RealNumberNotation>(context->argument(0));
        _q_self->setRealNumberNotation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setRealNumberPrecision(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        QTextStream::Status _q_arg0 = qscriptvalue_cast<QTextStream::Status>(context->argument(0));
        _q_self->setStatus(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 0) {
        _q_self->skipWhiteSpace();
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 0) {
        QTextStream::Status _q_result = _q_self->status();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        char _q_arg0 = qscriptvalue_cast<char>(context->argument(0));
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 46:
    if (context->argumentCount() == 1) {
        double _q_arg0 = context->argument(0).toNumber();
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 47:
    if (context->argumentCount() == 1) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 48:
    if (context->argumentCount() == 1) {
        signed int _q_arg0 = qscriptvalue_cast<signed int>(context->argument(0));
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 49:
    if (context->argumentCount() == 1) {
        signed short _q_arg0 = qscriptvalue_cast<signed short>(context->argument(0));
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 50:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 51: {
    QString result = QString::fromLatin1("QTextStream");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextStream_throw_ambiguity_error_helper(context,
        qtscript_QTextStream_function_names[_id+1],
        qtscript_QTextStream_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextStream_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextStream(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTextStream* _q_cpp_result = new QtScriptShell_QTextStream();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTextStream*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QtScriptShell_QTextStream* _q_cpp_result = new QtScriptShell_QTextStream(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTextStream*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QtScriptShell_QTextStream* _q_cpp_result = new QtScriptShell_QTextStream(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTextStream*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QFlags<QIODevice::OpenModeFlag> _q_arg1 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(1));
        QtScriptShell_QTextStream* _q_cpp_result = new QtScriptShell_QTextStream(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTextStream*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextStream_throw_ambiguity_error_helper(context,
        qtscript_QTextStream_function_names[_id],
        qtscript_QTextStream_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextStream_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextStream*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextStream*)0));
    for (int i = 0; i < 52; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextStream_prototype_call, qtscript_QTextStream_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextStream_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextStream*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextStream_static_call, proto, qtscript_QTextStream_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("FieldAlignment"),
        qtscript_create_QTextStream_FieldAlignment_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("RealNumberNotation"),
        qtscript_create_QTextStream_RealNumberNotation_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("NumberFlag"),
        qtscript_create_QTextStream_NumberFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("NumberFlags"),
        qtscript_create_QTextStream_NumberFlags_class(engine));
    ctor.setProperty(QString::fromLatin1("Status"),
        qtscript_create_QTextStream_Status_class(engine, ctor));
    return ctor;
}
