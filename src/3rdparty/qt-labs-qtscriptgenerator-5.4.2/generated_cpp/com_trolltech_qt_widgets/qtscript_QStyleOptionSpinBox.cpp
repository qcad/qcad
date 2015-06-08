#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qstyleoption.h>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QStyleOptionSpinBox.h"

static const char * const qtscript_QStyleOptionSpinBox_function_names[] = {
    "QStyleOptionSpinBox"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionSpinBox_function_signatures[] = {
    "\nQStyleOptionSpinBox other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionSpinBox_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionSpinBox_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionSpinBox::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionSpinBox)
Q_DECLARE_METATYPE(QStyleOptionSpinBox*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionSpinBox)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionSpinBox*)
Q_DECLARE_METATYPE(QStyleOptionSpinBox::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOptionSpinBox::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionComplex*)

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
// QStyleOptionSpinBox::StyleOptionType
//

static const QStyleOptionSpinBox::StyleOptionType qtscript_QStyleOptionSpinBox_StyleOptionType_values[] = {
    QStyleOptionSpinBox::Type
};

static const char * const qtscript_QStyleOptionSpinBox_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionSpinBox_StyleOptionType_toStringHelper(QStyleOptionSpinBox::StyleOptionType value)
{
    if ((value >= QStyleOptionSpinBox::Type) && (value <= QStyleOptionSpinBox::Type))
        return qtscript_QStyleOptionSpinBox_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionSpinBox::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionSpinBox_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionSpinBox::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionSpinBox"));
    return clazz.property(qtscript_QStyleOptionSpinBox_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionSpinBox_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionSpinBox::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionSpinBox::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionSpinBox_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionSpinBox::Type) && (arg <= QStyleOptionSpinBox::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionSpinBox::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionSpinBox_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionSpinBox::StyleOptionType value = qscriptvalue_cast<QStyleOptionSpinBox::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionSpinBox_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionSpinBox::StyleOptionType value = qscriptvalue_cast<QStyleOptionSpinBox::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionSpinBox_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionSpinBox_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionSpinBox_StyleOptionType,
        qtscript_QStyleOptionSpinBox_StyleOptionType_valueOf, qtscript_QStyleOptionSpinBox_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionSpinBox::StyleOptionType>(engine, qtscript_QStyleOptionSpinBox_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionSpinBox_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionSpinBox_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionSpinBox_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionSpinBox::StyleOptionVersion
//

static const QStyleOptionSpinBox::StyleOptionVersion qtscript_QStyleOptionSpinBox_StyleOptionVersion_values[] = {
    QStyleOptionSpinBox::Version
};

static const char * const qtscript_QStyleOptionSpinBox_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionSpinBox_StyleOptionVersion_toStringHelper(QStyleOptionSpinBox::StyleOptionVersion value)
{
    if ((value >= QStyleOptionSpinBox::Version) && (value <= QStyleOptionSpinBox::Version))
        return qtscript_QStyleOptionSpinBox_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionSpinBox::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionSpinBox_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionSpinBox::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionSpinBox"));
    return clazz.property(qtscript_QStyleOptionSpinBox_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionSpinBox_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionSpinBox::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionSpinBox::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionSpinBox_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionSpinBox::Version) && (arg <= QStyleOptionSpinBox::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionSpinBox::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionSpinBox_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionSpinBox::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionSpinBox::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionSpinBox_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionSpinBox::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionSpinBox::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionSpinBox_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionSpinBox_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionSpinBox_StyleOptionVersion,
        qtscript_QStyleOptionSpinBox_StyleOptionVersion_valueOf, qtscript_QStyleOptionSpinBox_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionSpinBox::StyleOptionVersion>(engine, qtscript_QStyleOptionSpinBox_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionSpinBox_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionSpinBox_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionSpinBox_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionSpinBox
//

static QScriptValue qtscript_QStyleOptionSpinBox_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionSpinBox* _q_self = qscriptvalue_cast<QStyleOptionSpinBox*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionSpinBox.%0(): this object is not a QStyleOptionSpinBox")
            .arg(qtscript_QStyleOptionSpinBox_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionSpinBox");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionSpinBox_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionSpinBox_function_names[_id+1],
        qtscript_QStyleOptionSpinBox_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionSpinBox_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionSpinBox(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionSpinBox _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionSpinBox)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionSpinBox _q_arg0 = qscriptvalue_cast<QStyleOptionSpinBox>(context->argument(0));
        QtScriptShell_QStyleOptionSpinBox _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionSpinBox)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionSpinBox_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionSpinBox_function_names[_id],
        qtscript_QStyleOptionSpinBox_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionSpinBox_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionSpinBox*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionSpinBox*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOptionComplex*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionSpinBox>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionSpinBox*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionSpinBox_static_call, proto, qtscript_QStyleOptionSpinBox_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionSpinBox_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionSpinBox_StyleOptionVersion_class(engine, ctor));
    return ctor;
}
