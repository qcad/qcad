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

#include "qtscriptshell_QStyleOptionTabBarBaseV2.h"

static const char * const qtscript_QStyleOptionTabBarBaseV2_function_names[] = {
    "QStyleOptionTabBarBaseV2"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionTabBarBaseV2_function_signatures[] = {
    "\nQStyleOptionTabBarBase other\nQStyleOptionTabBarBaseV2 other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionTabBarBaseV2_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionTabBarBaseV2_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionTabBarBaseV2::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionTabBarBaseV2)
Q_DECLARE_METATYPE(QStyleOptionTabBarBaseV2*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionTabBarBaseV2)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionTabBarBaseV2*)
Q_DECLARE_METATYPE(QStyleOptionTabBarBaseV2::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionTabBarBase)
Q_DECLARE_METATYPE(QStyleOptionTabBarBase*)

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
// QStyleOptionTabBarBaseV2::StyleOptionVersion
//

static const QStyleOptionTabBarBaseV2::StyleOptionVersion qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_values[] = {
    QStyleOptionTabBarBaseV2::Version
};

static const char * const qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_toStringHelper(QStyleOptionTabBarBaseV2::StyleOptionVersion value)
{
    if ((value >= QStyleOptionTabBarBaseV2::Version) && (value <= QStyleOptionTabBarBaseV2::Version))
        return qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionTabBarBaseV2::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionTabBarBaseV2::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionTabBarBaseV2"));
    return clazz.property(qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionTabBarBaseV2::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionTabBarBaseV2::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionTabBarBaseV2_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionTabBarBaseV2::Version) && (arg <= QStyleOptionTabBarBaseV2::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionTabBarBaseV2::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTabBarBaseV2::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionTabBarBaseV2::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionTabBarBaseV2::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionTabBarBaseV2::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionTabBarBaseV2_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionTabBarBaseV2_StyleOptionVersion,
        qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_valueOf, qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionTabBarBaseV2::StyleOptionVersion>(engine, qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionTabBarBaseV2_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionTabBarBaseV2
//

static QScriptValue qtscript_QStyleOptionTabBarBaseV2_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionTabBarBaseV2* _q_self = qscriptvalue_cast<QStyleOptionTabBarBaseV2*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionTabBarBaseV2.%0(): this object is not a QStyleOptionTabBarBaseV2")
            .arg(qtscript_QStyleOptionTabBarBaseV2_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionTabBarBaseV2");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionTabBarBaseV2_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionTabBarBaseV2_function_names[_id+1],
        qtscript_QStyleOptionTabBarBaseV2_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionTabBarBaseV2_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionTabBarBaseV2(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionTabBarBaseV2 _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionTabBarBaseV2)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QStyleOptionTabBarBase>() == context->argument(0).toVariant().userType())) {
            QStyleOptionTabBarBase _q_arg0 = qscriptvalue_cast<QStyleOptionTabBarBase>(context->argument(0));
            QtScriptShell_QStyleOptionTabBarBaseV2 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionTabBarBaseV2)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QStyleOptionTabBarBaseV2>() == context->argument(0).toVariant().userType())) {
            QStyleOptionTabBarBaseV2 _q_arg0 = qscriptvalue_cast<QStyleOptionTabBarBaseV2>(context->argument(0));
            QtScriptShell_QStyleOptionTabBarBaseV2 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionTabBarBaseV2)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionTabBarBaseV2_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionTabBarBaseV2_function_names[_id],
        qtscript_QStyleOptionTabBarBaseV2_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionTabBarBaseV2_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionTabBarBaseV2*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionTabBarBaseV2*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOptionTabBarBase*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionTabBarBaseV2>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionTabBarBaseV2*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionTabBarBaseV2_static_call, proto, qtscript_QStyleOptionTabBarBaseV2_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionTabBarBaseV2_StyleOptionVersion_class(engine, ctor));
    return ctor;
}
