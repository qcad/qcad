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

#include "qtscriptshell_QStyleOptionComboBox.h"

static const char * const qtscript_QStyleOptionComboBox_function_names[] = {
    "QStyleOptionComboBox"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionComboBox_function_signatures[] = {
    "\nQStyleOptionComboBox other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionComboBox_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionComboBox_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionComboBox::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionComboBox)
Q_DECLARE_METATYPE(QStyleOptionComboBox*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionComboBox)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionComboBox*)
Q_DECLARE_METATYPE(QStyleOptionComboBox::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionComboBox::StyleOptionType)
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
// QStyleOptionComboBox::StyleOptionVersion
//

static const QStyleOptionComboBox::StyleOptionVersion qtscript_QStyleOptionComboBox_StyleOptionVersion_values[] = {
    QStyleOptionComboBox::Version
};

static const char * const qtscript_QStyleOptionComboBox_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionComboBox_StyleOptionVersion_toStringHelper(QStyleOptionComboBox::StyleOptionVersion value)
{
    if ((value >= QStyleOptionComboBox::Version) && (value <= QStyleOptionComboBox::Version))
        return qtscript_QStyleOptionComboBox_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionComboBox::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionComboBox_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionComboBox::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionComboBox"));
    return clazz.property(qtscript_QStyleOptionComboBox_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionComboBox_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionComboBox::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionComboBox::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionComboBox_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionComboBox::Version) && (arg <= QStyleOptionComboBox::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionComboBox::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionComboBox_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionComboBox::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionComboBox::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionComboBox_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionComboBox::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionComboBox::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionComboBox_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionComboBox_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionComboBox_StyleOptionVersion,
        qtscript_QStyleOptionComboBox_StyleOptionVersion_valueOf, qtscript_QStyleOptionComboBox_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionComboBox::StyleOptionVersion>(engine, qtscript_QStyleOptionComboBox_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionComboBox_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionComboBox_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionComboBox_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionComboBox::StyleOptionType
//

static const QStyleOptionComboBox::StyleOptionType qtscript_QStyleOptionComboBox_StyleOptionType_values[] = {
    QStyleOptionComboBox::Type
};

static const char * const qtscript_QStyleOptionComboBox_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOptionComboBox_StyleOptionType_toStringHelper(QStyleOptionComboBox::StyleOptionType value)
{
    if ((value >= QStyleOptionComboBox::Type) && (value <= QStyleOptionComboBox::Type))
        return qtscript_QStyleOptionComboBox_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionComboBox::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionComboBox_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOptionComboBox::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionComboBox"));
    return clazz.property(qtscript_QStyleOptionComboBox_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOptionComboBox_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOptionComboBox::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOptionComboBox::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionComboBox_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionComboBox::Type) && (arg <= QStyleOptionComboBox::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionComboBox::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionComboBox_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionComboBox::StyleOptionType value = qscriptvalue_cast<QStyleOptionComboBox::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionComboBox_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionComboBox::StyleOptionType value = qscriptvalue_cast<QStyleOptionComboBox::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionComboBox_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionComboBox_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionComboBox_StyleOptionType,
        qtscript_QStyleOptionComboBox_StyleOptionType_valueOf, qtscript_QStyleOptionComboBox_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOptionComboBox::StyleOptionType>(engine, qtscript_QStyleOptionComboBox_StyleOptionType_toScriptValue,
        qtscript_QStyleOptionComboBox_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionComboBox_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionComboBox_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionComboBox
//

static QScriptValue qtscript_QStyleOptionComboBox_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionComboBox* _q_self = qscriptvalue_cast<QStyleOptionComboBox*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionComboBox.%0(): this object is not a QStyleOptionComboBox")
            .arg(qtscript_QStyleOptionComboBox_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionComboBox");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionComboBox_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionComboBox_function_names[_id+1],
        qtscript_QStyleOptionComboBox_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionComboBox_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionComboBox(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionComboBox _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionComboBox)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QStyleOptionComboBox _q_arg0 = qscriptvalue_cast<QStyleOptionComboBox>(context->argument(0));
        QtScriptShell_QStyleOptionComboBox _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionComboBox)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionComboBox_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionComboBox_function_names[_id],
        qtscript_QStyleOptionComboBox_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionComboBox_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionComboBox*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionComboBox*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOptionComplex*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionComboBox>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionComboBox*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionComboBox_static_call, proto, qtscript_QStyleOptionComboBox_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionComboBox_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOptionComboBox_StyleOptionType_class(engine, ctor));
    return ctor;
}
