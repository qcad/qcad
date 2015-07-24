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

#include "qtscriptshell_QStyleOptionViewItemV4.h"

static const char * const qtscript_QStyleOptionViewItemV4_function_names[] = {
    "QStyleOptionViewItemV4"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionViewItemV4_function_signatures[] = {
    "\nQStyleOptionViewItem other\nQStyleOptionViewItemV4 other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionViewItemV4_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionViewItemV4_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionViewItemV4::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionViewItemV4)
Q_DECLARE_METATYPE(QStyleOptionViewItemV4*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionViewItemV4)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionViewItemV4*)
Q_DECLARE_METATYPE(QStyleOptionViewItemV4::ViewItemPosition)
Q_DECLARE_METATYPE(QStyleOptionViewItemV4::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionViewItem)
Q_DECLARE_METATYPE(QStyleOptionViewItemV3*)

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
// QStyleOptionViewItemV4::ViewItemPosition
//

static const QStyleOptionViewItemV4::ViewItemPosition qtscript_QStyleOptionViewItemV4_ViewItemPosition_values[] = {
    QStyleOptionViewItemV4::Invalid
    , QStyleOptionViewItemV4::Beginning
    , QStyleOptionViewItemV4::Middle
    , QStyleOptionViewItemV4::End
    , QStyleOptionViewItemV4::OnlyOne
};

static const char * const qtscript_QStyleOptionViewItemV4_ViewItemPosition_keys[] = {
    "Invalid"
    , "Beginning"
    , "Middle"
    , "End"
    , "OnlyOne"
};

static QString qtscript_QStyleOptionViewItemV4_ViewItemPosition_toStringHelper(QStyleOptionViewItemV4::ViewItemPosition value)
{
    if ((value >= QStyleOptionViewItemV4::Invalid) && (value <= QStyleOptionViewItemV4::OnlyOne))
        return qtscript_QStyleOptionViewItemV4_ViewItemPosition_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionViewItemV4::Invalid)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionViewItemV4_ViewItemPosition_toScriptValue(QScriptEngine *engine, const QStyleOptionViewItemV4::ViewItemPosition &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionViewItemV4"));
    return clazz.property(qtscript_QStyleOptionViewItemV4_ViewItemPosition_toStringHelper(value));
}

static void qtscript_QStyleOptionViewItemV4_ViewItemPosition_fromScriptValue(const QScriptValue &value, QStyleOptionViewItemV4::ViewItemPosition &out)
{
    out = qvariant_cast<QStyleOptionViewItemV4::ViewItemPosition>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionViewItemV4_ViewItemPosition(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionViewItemV4::Invalid) && (arg <= QStyleOptionViewItemV4::OnlyOne))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionViewItemV4::ViewItemPosition>(arg));
    return context->throwError(QString::fromLatin1("ViewItemPosition(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionViewItemV4_ViewItemPosition_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItemV4::ViewItemPosition value = qscriptvalue_cast<QStyleOptionViewItemV4::ViewItemPosition>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionViewItemV4_ViewItemPosition_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItemV4::ViewItemPosition value = qscriptvalue_cast<QStyleOptionViewItemV4::ViewItemPosition>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionViewItemV4_ViewItemPosition_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionViewItemV4_ViewItemPosition_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionViewItemV4_ViewItemPosition,
        qtscript_QStyleOptionViewItemV4_ViewItemPosition_valueOf, qtscript_QStyleOptionViewItemV4_ViewItemPosition_toString);
    qScriptRegisterMetaType<QStyleOptionViewItemV4::ViewItemPosition>(engine, qtscript_QStyleOptionViewItemV4_ViewItemPosition_toScriptValue,
        qtscript_QStyleOptionViewItemV4_ViewItemPosition_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionViewItemV4_ViewItemPosition_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionViewItemV4_ViewItemPosition_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionViewItemV4::StyleOptionVersion
//

static const QStyleOptionViewItemV4::StyleOptionVersion qtscript_QStyleOptionViewItemV4_StyleOptionVersion_values[] = {
    QStyleOptionViewItemV4::Version
};

static const char * const qtscript_QStyleOptionViewItemV4_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionViewItemV4_StyleOptionVersion_toStringHelper(QStyleOptionViewItemV4::StyleOptionVersion value)
{
    if ((value >= QStyleOptionViewItemV4::Version) && (value <= QStyleOptionViewItemV4::Version))
        return qtscript_QStyleOptionViewItemV4_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionViewItemV4::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionViewItemV4_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionViewItemV4::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionViewItemV4"));
    return clazz.property(qtscript_QStyleOptionViewItemV4_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionViewItemV4_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionViewItemV4::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionViewItemV4::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionViewItemV4_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionViewItemV4::Version) && (arg <= QStyleOptionViewItemV4::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionViewItemV4::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionViewItemV4_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItemV4::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionViewItemV4::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionViewItemV4_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItemV4::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionViewItemV4::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionViewItemV4_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionViewItemV4_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionViewItemV4_StyleOptionVersion,
        qtscript_QStyleOptionViewItemV4_StyleOptionVersion_valueOf, qtscript_QStyleOptionViewItemV4_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionViewItemV4::StyleOptionVersion>(engine, qtscript_QStyleOptionViewItemV4_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionViewItemV4_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionViewItemV4_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionViewItemV4_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionViewItemV4
//

static QScriptValue qtscript_QStyleOptionViewItemV4_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionViewItemV4* _q_self = qscriptvalue_cast<QStyleOptionViewItemV4*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionViewItemV4.%0(): this object is not a QStyleOptionViewItemV4")
            .arg(qtscript_QStyleOptionViewItemV4_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionViewItemV4");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionViewItemV4_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionViewItemV4_function_names[_id+1],
        qtscript_QStyleOptionViewItemV4_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionViewItemV4_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionViewItemV4(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionViewItemV4 _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionViewItemV4)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QStyleOptionViewItem>() == context->argument(0).toVariant().userType())) {
            QStyleOptionViewItem _q_arg0 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(0));
            QtScriptShell_QStyleOptionViewItemV4 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionViewItemV4)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QStyleOptionViewItemV4>() == context->argument(0).toVariant().userType())) {
            QStyleOptionViewItemV4 _q_arg0 = qscriptvalue_cast<QStyleOptionViewItemV4>(context->argument(0));
            QtScriptShell_QStyleOptionViewItemV4 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionViewItemV4)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionViewItemV4_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionViewItemV4_function_names[_id],
        qtscript_QStyleOptionViewItemV4_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionViewItemV4_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionViewItemV4*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionViewItemV4*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOptionViewItemV3*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionViewItemV4>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionViewItemV4*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionViewItemV4_static_call, proto, qtscript_QStyleOptionViewItemV4_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ViewItemPosition"),
        qtscript_create_QStyleOptionViewItemV4_ViewItemPosition_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionViewItemV4_StyleOptionVersion_class(engine, ctor));
    return ctor;
}
