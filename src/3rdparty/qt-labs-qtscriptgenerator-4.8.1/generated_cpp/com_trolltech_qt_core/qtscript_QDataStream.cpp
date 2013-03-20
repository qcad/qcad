#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qdatastream.h>
#include <QVariant>
#include <qbytearray.h>
#include <qdatastream.h>
#include <qiodevice.h>

#include "qtscriptshell_QDataStream.h"

static const char * const qtscript_QDataStream_function_names[] = {
    "QDataStream"
    // static
    // prototype
    , "atEnd"
    , "device"
    , "floatingPointPrecision"
    , "readBoolean"
    , "readByte"
    , "readDouble"
    , "readFloat"
    , "readInt"
    , "readLongLong"
    , "readShort"
    , "readUInt"
    , "readULongLong"
    , "readUShort"
    , "resetStatus"
    , "setDevice"
    , "setFloatingPointPrecision"
    , "setStatus"
    , "setVersion"
    , "skipRawData"
    , "status"
    , "unsetDevice"
    , "version"
    , "writeBoolean"
    , "writeByte"
    , "writeDouble"
    , "writeFloat"
    , "writeInt"
    , "writeLongLong"
    , "writeShort"
    , "toString"
};

static const char * const qtscript_QDataStream_function_signatures[] = {
    "\nQByteArray arg__1, OpenMode flags\nQIODevice arg__1\nQByteArray arg__1"
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
    , ""
    , "QIODevice arg__1"
    , "FloatingPointPrecision precision"
    , "Status status"
    , "int arg__1"
    , "int len"
    , ""
    , ""
    , ""
    , "bool i"
    , "unsigned char i"
    , "double f"
    , "float f"
    , "int i"
    , "qint64 i"
    , "short i"
""
};

static const int qtscript_QDataStream_function_lengths[] = {
    2
    // static
    // prototype
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
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
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
    , 0
};

static QScriptValue qtscript_QDataStream_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDataStream::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(QtScriptShell_QDataStream*)
Q_DECLARE_METATYPE(QDataStream::FloatingPointPrecision)
Q_DECLARE_METATYPE(QDataStream::Version)
Q_DECLARE_METATYPE(QDataStream::Status)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QByteArray*)
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

//
// QDataStream::FloatingPointPrecision
//

static const QDataStream::FloatingPointPrecision qtscript_QDataStream_FloatingPointPrecision_values[] = {
    QDataStream::SinglePrecision
    , QDataStream::DoublePrecision
};

static const char * const qtscript_QDataStream_FloatingPointPrecision_keys[] = {
    "SinglePrecision"
    , "DoublePrecision"
};

static QString qtscript_QDataStream_FloatingPointPrecision_toStringHelper(QDataStream::FloatingPointPrecision value)
{
    if ((value >= QDataStream::SinglePrecision) && (value <= QDataStream::DoublePrecision))
        return qtscript_QDataStream_FloatingPointPrecision_keys[static_cast<int>(value)-static_cast<int>(QDataStream::SinglePrecision)];
    return QString();
}

static QScriptValue qtscript_QDataStream_FloatingPointPrecision_toScriptValue(QScriptEngine *engine, const QDataStream::FloatingPointPrecision &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDataStream"));
    return clazz.property(qtscript_QDataStream_FloatingPointPrecision_toStringHelper(value));
}

static void qtscript_QDataStream_FloatingPointPrecision_fromScriptValue(const QScriptValue &value, QDataStream::FloatingPointPrecision &out)
{
    out = qvariant_cast<QDataStream::FloatingPointPrecision>(value.toVariant());
}

static QScriptValue qtscript_construct_QDataStream_FloatingPointPrecision(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QDataStream::SinglePrecision) && (arg <= QDataStream::DoublePrecision))
        return qScriptValueFromValue(engine,  static_cast<QDataStream::FloatingPointPrecision>(arg));
    return context->throwError(QString::fromLatin1("FloatingPointPrecision(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDataStream_FloatingPointPrecision_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDataStream::FloatingPointPrecision value = qscriptvalue_cast<QDataStream::FloatingPointPrecision>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDataStream_FloatingPointPrecision_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDataStream::FloatingPointPrecision value = qscriptvalue_cast<QDataStream::FloatingPointPrecision>(context->thisObject());
    return QScriptValue(engine, qtscript_QDataStream_FloatingPointPrecision_toStringHelper(value));
}

static QScriptValue qtscript_create_QDataStream_FloatingPointPrecision_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDataStream_FloatingPointPrecision,
        qtscript_QDataStream_FloatingPointPrecision_valueOf, qtscript_QDataStream_FloatingPointPrecision_toString);
    qScriptRegisterMetaType<QDataStream::FloatingPointPrecision>(engine, qtscript_QDataStream_FloatingPointPrecision_toScriptValue,
        qtscript_QDataStream_FloatingPointPrecision_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDataStream_FloatingPointPrecision_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDataStream_FloatingPointPrecision_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDataStream::Version
//

static const QDataStream::Version qtscript_QDataStream_Version_values[] = {
    QDataStream::Qt_1_0
    , QDataStream::Qt_2_0
    , QDataStream::Qt_2_1
    , QDataStream::Qt_3_0
    , QDataStream::Qt_3_1
    , QDataStream::Qt_3_3
    , QDataStream::Qt_4_0
    , QDataStream::Qt_4_2
    , QDataStream::Qt_4_3
    , QDataStream::Qt_4_4
    , QDataStream::Qt_4_5
    , QDataStream::Qt_4_6
};

static const char * const qtscript_QDataStream_Version_keys[] = {
    "Qt_1_0"
    , "Qt_2_0"
    , "Qt_2_1"
    , "Qt_3_0"
    , "Qt_3_1"
    , "Qt_3_3"
    , "Qt_4_0"
    , "Qt_4_2"
    , "Qt_4_3"
    , "Qt_4_4"
    , "Qt_4_5"
    , "Qt_4_6"
};

static QString qtscript_QDataStream_Version_toStringHelper(QDataStream::Version value)
{
    if ((value >= QDataStream::Qt_1_0) && (value <= QDataStream::Qt_4_6))
        return qtscript_QDataStream_Version_keys[static_cast<int>(value)-static_cast<int>(QDataStream::Qt_1_0)];
    return QString();
}

static QScriptValue qtscript_QDataStream_Version_toScriptValue(QScriptEngine *engine, const QDataStream::Version &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDataStream"));
    return clazz.property(qtscript_QDataStream_Version_toStringHelper(value));
}

static void qtscript_QDataStream_Version_fromScriptValue(const QScriptValue &value, QDataStream::Version &out)
{
    out = qvariant_cast<QDataStream::Version>(value.toVariant());
}

static QScriptValue qtscript_construct_QDataStream_Version(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QDataStream::Qt_1_0) && (arg <= QDataStream::Qt_4_6))
        return qScriptValueFromValue(engine,  static_cast<QDataStream::Version>(arg));
    return context->throwError(QString::fromLatin1("Version(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDataStream_Version_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDataStream::Version value = qscriptvalue_cast<QDataStream::Version>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDataStream_Version_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDataStream::Version value = qscriptvalue_cast<QDataStream::Version>(context->thisObject());
    return QScriptValue(engine, qtscript_QDataStream_Version_toStringHelper(value));
}

static QScriptValue qtscript_create_QDataStream_Version_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDataStream_Version,
        qtscript_QDataStream_Version_valueOf, qtscript_QDataStream_Version_toString);
    qScriptRegisterMetaType<QDataStream::Version>(engine, qtscript_QDataStream_Version_toScriptValue,
        qtscript_QDataStream_Version_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 12; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDataStream_Version_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDataStream_Version_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDataStream::Status
//

static const QDataStream::Status qtscript_QDataStream_Status_values[] = {
    QDataStream::Ok
    , QDataStream::ReadPastEnd
    , QDataStream::ReadCorruptData
    , QDataStream::WriteFailed
};

static const char * const qtscript_QDataStream_Status_keys[] = {
    "Ok"
    , "ReadPastEnd"
    , "ReadCorruptData"
    , "WriteFailed"
};

static QString qtscript_QDataStream_Status_toStringHelper(QDataStream::Status value)
{
    if ((value >= QDataStream::Ok) && (value <= QDataStream::WriteFailed))
        return qtscript_QDataStream_Status_keys[static_cast<int>(value)-static_cast<int>(QDataStream::Ok)];
    return QString();
}

static QScriptValue qtscript_QDataStream_Status_toScriptValue(QScriptEngine *engine, const QDataStream::Status &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDataStream"));
    return clazz.property(qtscript_QDataStream_Status_toStringHelper(value));
}

static void qtscript_QDataStream_Status_fromScriptValue(const QScriptValue &value, QDataStream::Status &out)
{
    out = qvariant_cast<QDataStream::Status>(value.toVariant());
}

static QScriptValue qtscript_construct_QDataStream_Status(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QDataStream::Ok) && (arg <= QDataStream::WriteFailed))
        return qScriptValueFromValue(engine,  static_cast<QDataStream::Status>(arg));
    return context->throwError(QString::fromLatin1("Status(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDataStream_Status_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDataStream::Status value = qscriptvalue_cast<QDataStream::Status>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDataStream_Status_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDataStream::Status value = qscriptvalue_cast<QDataStream::Status>(context->thisObject());
    return QScriptValue(engine, qtscript_QDataStream_Status_toStringHelper(value));
}

static QScriptValue qtscript_create_QDataStream_Status_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDataStream_Status,
        qtscript_QDataStream_Status_valueOf, qtscript_QDataStream_Status_toString);
    qScriptRegisterMetaType<QDataStream::Status>(engine, qtscript_QDataStream_Status_toScriptValue,
        qtscript_QDataStream_Status_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDataStream_Status_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDataStream_Status_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDataStream
//

static QScriptValue qtscript_QDataStream_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 29;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDataStream* _q_self = qscriptvalue_cast<QDataStream*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDataStream.%0(): this object is not a QDataStream")
            .arg(qtscript_QDataStream_function_names[_id+1]));
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
        QIODevice* _q_result = _q_self->device();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QDataStream::FloatingPointPrecision _q_result = _q_self->floatingPointPrecision();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {

            bool __result;
            bool & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            bool _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {

            unsigned char __result;
            unsigned char & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            int _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {

            double __result;
            double & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            double _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {

            float __result;
            float & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            float _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {

            int __result;
            int & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            int _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {

            qint64 __result;
            qint64 & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            qint64 _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {

            short __result;
            short & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            short _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {

            uint __result;
            uint & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            uint _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {

            unsigned long long __result;
            unsigned long long & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            unsigned long long _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {

            unsigned short __result;
            unsigned short & _q_arg0 = __result;
                    _q_self->operator>>(_q_arg0);
        
            unsigned short _q_convertedResult = __result;
            return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        _q_self->resetStatus();
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        _q_self->setDevice(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QDataStream::FloatingPointPrecision _q_arg0 = qscriptvalue_cast<QDataStream::FloatingPointPrecision>(context->argument(0));
        _q_self->setFloatingPointPrecision(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QDataStream::Status _q_arg0 = qscriptvalue_cast<QDataStream::Status>(context->argument(0));
        _q_self->setStatus(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setVersion(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->skipRawData(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QDataStream::Status _q_result = _q_self->status();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        _q_self->unsetDevice();
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->version();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        unsigned char _q_arg0 = qscriptvalue_cast<unsigned char>(context->argument(0));
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        double _q_arg0 = context->argument(0).toNumber();
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        short _q_arg0 = qscriptvalue_cast<short>(context->argument(0));
        _q_self->operator<<(_q_arg0);
        return context->thisObject();
    }
    break;

    case 29: {
    QString result = QString::fromLatin1("QDataStream");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDataStream_throw_ambiguity_error_helper(context,
        qtscript_QDataStream_function_names[_id+1],
        qtscript_QDataStream_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDataStream_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDataStream(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QDataStream* _q_cpp_result = new QtScriptShell_QDataStream();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDataStream*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QtScriptShell_QDataStream* _q_cpp_result = new QtScriptShell_QDataStream(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDataStream*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QtScriptShell_QDataStream* _q_cpp_result = new QtScriptShell_QDataStream(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDataStream*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QByteArray* _q_arg0 = qscriptvalue_cast<QByteArray*>(context->argument(0));
        QFlags<QIODevice::OpenModeFlag> _q_arg1 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(1));
        QtScriptShell_QDataStream* _q_cpp_result = new QtScriptShell_QDataStream(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDataStream*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDataStream_throw_ambiguity_error_helper(context,
        qtscript_QDataStream_function_names[_id],
        qtscript_QDataStream_function_signatures[_id]);
}

QScriptValue qtscript_create_QDataStream_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDataStream*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDataStream*)0));
    for (int i = 0; i < 30; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDataStream_prototype_call, qtscript_QDataStream_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDataStream_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDataStream*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDataStream_static_call, proto, qtscript_QDataStream_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("FloatingPointPrecision"),
        qtscript_create_QDataStream_FloatingPointPrecision_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Version"),
        qtscript_create_QDataStream_Version_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Status"),
        qtscript_create_QDataStream_Status_class(engine, ctor));
    return ctor;
}
