#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qstyleoption.h>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QStyleOptionFrameV2.h"

static const char * const qtscript_QStyleOptionFrameV2_function_names[] = {
    "QStyleOptionFrameV2"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionFrameV2_function_signatures[] = {
    "\nQStyleOptionFrame other\nQStyleOptionFrameV2 other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionFrameV2_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionFrameV2_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionFrameV2::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionFrameV2)
Q_DECLARE_METATYPE(QStyleOptionFrameV2*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionFrameV2)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionFrameV2*)
Q_DECLARE_METATYPE(QStyleOptionFrameV2::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionFrameV2::FrameFeature)
Q_DECLARE_METATYPE(QFlags<QStyleOptionFrameV2::FrameFeature>)
Q_DECLARE_METATYPE(QStyleOptionFrame)
Q_DECLARE_METATYPE(QStyleOptionFrame*)

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
// QStyleOptionFrameV2::StyleOptionVersion
//

static const QStyleOptionFrameV2::StyleOptionVersion qtscript_QStyleOptionFrameV2_StyleOptionVersion_values[] = {
    QStyleOptionFrameV2::Version
};

static const char * const qtscript_QStyleOptionFrameV2_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionFrameV2_StyleOptionVersion_toStringHelper(QStyleOptionFrameV2::StyleOptionVersion value)
{
    if ((value >= QStyleOptionFrameV2::Version) && (value <= QStyleOptionFrameV2::Version))
        return qtscript_QStyleOptionFrameV2_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionFrameV2::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionFrameV2_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionFrameV2::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionFrameV2"));
    return clazz.property(qtscript_QStyleOptionFrameV2_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionFrameV2_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionFrameV2::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionFrameV2::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionFrameV2_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionFrameV2::Version) && (arg <= QStyleOptionFrameV2::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionFrameV2::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionFrameV2_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFrameV2::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionFrameV2::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionFrameV2_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFrameV2::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionFrameV2::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionFrameV2_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionFrameV2_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionFrameV2_StyleOptionVersion,
        qtscript_QStyleOptionFrameV2_StyleOptionVersion_valueOf, qtscript_QStyleOptionFrameV2_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionFrameV2::StyleOptionVersion>(engine, qtscript_QStyleOptionFrameV2_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionFrameV2_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionFrameV2_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionFrameV2_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionFrameV2::FrameFeature
//

static const QStyleOptionFrameV2::FrameFeature qtscript_QStyleOptionFrameV2_FrameFeature_values[] = {
    QStyleOptionFrameV2::None
    , QStyleOptionFrameV2::Flat
};

static const char * const qtscript_QStyleOptionFrameV2_FrameFeature_keys[] = {
    "None"
    , "Flat"
};

static QString qtscript_QStyleOptionFrameV2_FrameFeature_toStringHelper(QStyleOptionFrameV2::FrameFeature value)
{
    if ((value >= QStyleOptionFrameV2::None) && (value <= QStyleOptionFrameV2::Flat))
        return qtscript_QStyleOptionFrameV2_FrameFeature_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionFrameV2::None)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionFrameV2_FrameFeature_toScriptValue(QScriptEngine *engine, const QStyleOptionFrameV2::FrameFeature &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionFrameV2"));
    return clazz.property(qtscript_QStyleOptionFrameV2_FrameFeature_toStringHelper(value));
}

static void qtscript_QStyleOptionFrameV2_FrameFeature_fromScriptValue(const QScriptValue &value, QStyleOptionFrameV2::FrameFeature &out)
{
    out = qvariant_cast<QStyleOptionFrameV2::FrameFeature>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionFrameV2_FrameFeature(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionFrameV2::None) && (arg <= QStyleOptionFrameV2::Flat))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionFrameV2::FrameFeature>(arg));
    return context->throwError(QString::fromLatin1("FrameFeature(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionFrameV2_FrameFeature_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFrameV2::FrameFeature value = qscriptvalue_cast<QStyleOptionFrameV2::FrameFeature>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionFrameV2_FrameFeature_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFrameV2::FrameFeature value = qscriptvalue_cast<QStyleOptionFrameV2::FrameFeature>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionFrameV2_FrameFeature_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionFrameV2_FrameFeature_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionFrameV2_FrameFeature,
        qtscript_QStyleOptionFrameV2_FrameFeature_valueOf, qtscript_QStyleOptionFrameV2_FrameFeature_toString);
    qScriptRegisterMetaType<QStyleOptionFrameV2::FrameFeature>(engine, qtscript_QStyleOptionFrameV2_FrameFeature_toScriptValue,
        qtscript_QStyleOptionFrameV2_FrameFeature_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionFrameV2_FrameFeature_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionFrameV2_FrameFeature_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionFrameV2::FrameFeatures
//

static QScriptValue qtscript_QStyleOptionFrameV2_FrameFeatures_toScriptValue(QScriptEngine *engine, const QStyleOptionFrameV2::FrameFeatures &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QStyleOptionFrameV2_FrameFeatures_fromScriptValue(const QScriptValue &value, QStyleOptionFrameV2::FrameFeatures &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QStyleOptionFrameV2::FrameFeatures>())
        out = qvariant_cast<QStyleOptionFrameV2::FrameFeatures>(var);
    else if (var.userType() == qMetaTypeId<QStyleOptionFrameV2::FrameFeature>())
        out = qvariant_cast<QStyleOptionFrameV2::FrameFeature>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QStyleOptionFrameV2_FrameFeatures(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFrameV2::FrameFeatures result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QStyleOptionFrameV2::FrameFeatures>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QStyleOptionFrameV2::FrameFeature>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("FrameFeatures(): argument %0 is not of type FrameFeature").arg(i));
            }
            result |= qvariant_cast<QStyleOptionFrameV2::FrameFeature>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QStyleOptionFrameV2_FrameFeatures_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFrameV2::FrameFeatures value = qscriptvalue_cast<QStyleOptionFrameV2::FrameFeatures>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionFrameV2_FrameFeatures_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionFrameV2::FrameFeatures value = qscriptvalue_cast<QStyleOptionFrameV2::FrameFeatures>(context->thisObject());
    QString result;
    for (int i = 0; i < 2; ++i) {
        if ((value & qtscript_QStyleOptionFrameV2_FrameFeature_values[i]) == qtscript_QStyleOptionFrameV2_FrameFeature_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QStyleOptionFrameV2_FrameFeature_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QStyleOptionFrameV2_FrameFeatures_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QStyleOptionFrameV2::FrameFeatures>() == otherObj.value<QStyleOptionFrameV2::FrameFeatures>())));
}

static QScriptValue qtscript_create_QStyleOptionFrameV2_FrameFeatures_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QStyleOptionFrameV2_FrameFeatures, qtscript_QStyleOptionFrameV2_FrameFeatures_valueOf,
        qtscript_QStyleOptionFrameV2_FrameFeatures_toString, qtscript_QStyleOptionFrameV2_FrameFeatures_equals);
    qScriptRegisterMetaType<QStyleOptionFrameV2::FrameFeatures>(engine, qtscript_QStyleOptionFrameV2_FrameFeatures_toScriptValue,
        qtscript_QStyleOptionFrameV2_FrameFeatures_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QStyleOptionFrameV2
//

static QScriptValue qtscript_QStyleOptionFrameV2_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionFrameV2* _q_self = qscriptvalue_cast<QStyleOptionFrameV2*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionFrameV2.%0(): this object is not a QStyleOptionFrameV2")
            .arg(qtscript_QStyleOptionFrameV2_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionFrameV2");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionFrameV2_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionFrameV2_function_names[_id+1],
        qtscript_QStyleOptionFrameV2_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionFrameV2_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionFrameV2(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionFrameV2 _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionFrameV2)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QStyleOptionFrame>() == context->argument(0).toVariant().userType())) {
            QStyleOptionFrame _q_arg0 = qscriptvalue_cast<QStyleOptionFrame>(context->argument(0));
            QtScriptShell_QStyleOptionFrameV2 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionFrameV2)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QStyleOptionFrameV2>() == context->argument(0).toVariant().userType())) {
            QStyleOptionFrameV2 _q_arg0 = qscriptvalue_cast<QStyleOptionFrameV2>(context->argument(0));
            QtScriptShell_QStyleOptionFrameV2 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionFrameV2)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionFrameV2_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionFrameV2_function_names[_id],
        qtscript_QStyleOptionFrameV2_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionFrameV2_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionFrameV2*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionFrameV2*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOptionFrame*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionFrameV2>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionFrameV2*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionFrameV2_static_call, proto, qtscript_QStyleOptionFrameV2_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionFrameV2_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FrameFeature"),
        qtscript_create_QStyleOptionFrameV2_FrameFeature_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FrameFeatures"),
        qtscript_create_QStyleOptionFrameV2_FrameFeatures_class(engine));
    return ctor;
}
