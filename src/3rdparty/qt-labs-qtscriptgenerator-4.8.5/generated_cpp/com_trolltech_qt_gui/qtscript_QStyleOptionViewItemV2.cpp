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

#include "qtscriptshell_QStyleOptionViewItemV2.h"

static const char * const qtscript_QStyleOptionViewItemV2_function_names[] = {
    "QStyleOptionViewItemV2"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QStyleOptionViewItemV2_function_signatures[] = {
    "\nQStyleOptionViewItem other\nQStyleOptionViewItemV2 other"
    // static
    // prototype
""
};

static const int qtscript_QStyleOptionViewItemV2_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QStyleOptionViewItemV2_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOptionViewItemV2::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOptionViewItemV2)
Q_DECLARE_METATYPE(QStyleOptionViewItemV2*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionViewItemV2)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOptionViewItemV2*)
Q_DECLARE_METATYPE(QStyleOptionViewItemV2::StyleOptionVersion)
Q_DECLARE_METATYPE(QStyleOptionViewItemV2::ViewItemFeature)
Q_DECLARE_METATYPE(QFlags<QStyleOptionViewItemV2::ViewItemFeature>)
Q_DECLARE_METATYPE(QStyleOptionViewItem)
Q_DECLARE_METATYPE(QStyleOptionViewItem*)

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
// QStyleOptionViewItemV2::StyleOptionVersion
//

static const QStyleOptionViewItemV2::StyleOptionVersion qtscript_QStyleOptionViewItemV2_StyleOptionVersion_values[] = {
    QStyleOptionViewItemV2::Version
};

static const char * const qtscript_QStyleOptionViewItemV2_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOptionViewItemV2_StyleOptionVersion_toStringHelper(QStyleOptionViewItemV2::StyleOptionVersion value)
{
    if ((value >= QStyleOptionViewItemV2::Version) && (value <= QStyleOptionViewItemV2::Version))
        return qtscript_QStyleOptionViewItemV2_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOptionViewItemV2::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOptionViewItemV2_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOptionViewItemV2::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionViewItemV2"));
    return clazz.property(qtscript_QStyleOptionViewItemV2_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOptionViewItemV2_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOptionViewItemV2::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOptionViewItemV2::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionViewItemV2_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOptionViewItemV2::Version) && (arg <= QStyleOptionViewItemV2::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOptionViewItemV2::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionViewItemV2_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItemV2::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionViewItemV2::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionViewItemV2_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItemV2::StyleOptionVersion value = qscriptvalue_cast<QStyleOptionViewItemV2::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionViewItemV2_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionViewItemV2_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionViewItemV2_StyleOptionVersion,
        qtscript_QStyleOptionViewItemV2_StyleOptionVersion_valueOf, qtscript_QStyleOptionViewItemV2_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOptionViewItemV2::StyleOptionVersion>(engine, qtscript_QStyleOptionViewItemV2_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOptionViewItemV2_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionViewItemV2_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionViewItemV2_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionViewItemV2::ViewItemFeature
//

static const QStyleOptionViewItemV2::ViewItemFeature qtscript_QStyleOptionViewItemV2_ViewItemFeature_values[] = {
    QStyleOptionViewItemV2::None
    , QStyleOptionViewItemV2::WrapText
    , QStyleOptionViewItemV2::Alternate
    , QStyleOptionViewItemV2::HasCheckIndicator
    , QStyleOptionViewItemV2::HasDisplay
    , QStyleOptionViewItemV2::HasDecoration
};

static const char * const qtscript_QStyleOptionViewItemV2_ViewItemFeature_keys[] = {
    "None"
    , "WrapText"
    , "Alternate"
    , "HasCheckIndicator"
    , "HasDisplay"
    , "HasDecoration"
};

static QString qtscript_QStyleOptionViewItemV2_ViewItemFeature_toStringHelper(QStyleOptionViewItemV2::ViewItemFeature value)
{
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QStyleOptionViewItemV2_ViewItemFeature_values[i] == value)
            return QString::fromLatin1(qtscript_QStyleOptionViewItemV2_ViewItemFeature_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyleOptionViewItemV2_ViewItemFeature_toScriptValue(QScriptEngine *engine, const QStyleOptionViewItemV2::ViewItemFeature &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOptionViewItemV2"));
    return clazz.property(qtscript_QStyleOptionViewItemV2_ViewItemFeature_toStringHelper(value));
}

static void qtscript_QStyleOptionViewItemV2_ViewItemFeature_fromScriptValue(const QScriptValue &value, QStyleOptionViewItemV2::ViewItemFeature &out)
{
    out = qvariant_cast<QStyleOptionViewItemV2::ViewItemFeature>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOptionViewItemV2_ViewItemFeature(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QStyleOptionViewItemV2_ViewItemFeature_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyleOptionViewItemV2::ViewItemFeature>(arg));
    }
    return context->throwError(QString::fromLatin1("ViewItemFeature(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOptionViewItemV2_ViewItemFeature_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItemV2::ViewItemFeature value = qscriptvalue_cast<QStyleOptionViewItemV2::ViewItemFeature>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionViewItemV2_ViewItemFeature_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItemV2::ViewItemFeature value = qscriptvalue_cast<QStyleOptionViewItemV2::ViewItemFeature>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOptionViewItemV2_ViewItemFeature_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOptionViewItemV2_ViewItemFeature_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOptionViewItemV2_ViewItemFeature,
        qtscript_QStyleOptionViewItemV2_ViewItemFeature_valueOf, qtscript_QStyleOptionViewItemV2_ViewItemFeature_toString);
    qScriptRegisterMetaType<QStyleOptionViewItemV2::ViewItemFeature>(engine, qtscript_QStyleOptionViewItemV2_ViewItemFeature_toScriptValue,
        qtscript_QStyleOptionViewItemV2_ViewItemFeature_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOptionViewItemV2_ViewItemFeature_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOptionViewItemV2_ViewItemFeature_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOptionViewItemV2::ViewItemFeatures
//

static QScriptValue qtscript_QStyleOptionViewItemV2_ViewItemFeatures_toScriptValue(QScriptEngine *engine, const QStyleOptionViewItemV2::ViewItemFeatures &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QStyleOptionViewItemV2_ViewItemFeatures_fromScriptValue(const QScriptValue &value, QStyleOptionViewItemV2::ViewItemFeatures &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QStyleOptionViewItemV2::ViewItemFeatures>())
        out = qvariant_cast<QStyleOptionViewItemV2::ViewItemFeatures>(var);
    else if (var.userType() == qMetaTypeId<QStyleOptionViewItemV2::ViewItemFeature>())
        out = qvariant_cast<QStyleOptionViewItemV2::ViewItemFeature>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QStyleOptionViewItemV2_ViewItemFeatures(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItemV2::ViewItemFeatures result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QStyleOptionViewItemV2::ViewItemFeatures>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QStyleOptionViewItemV2::ViewItemFeature>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ViewItemFeatures(): argument %0 is not of type ViewItemFeature").arg(i));
            }
            result |= qvariant_cast<QStyleOptionViewItemV2::ViewItemFeature>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QStyleOptionViewItemV2_ViewItemFeatures_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItemV2::ViewItemFeatures value = qscriptvalue_cast<QStyleOptionViewItemV2::ViewItemFeatures>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOptionViewItemV2_ViewItemFeatures_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOptionViewItemV2::ViewItemFeatures value = qscriptvalue_cast<QStyleOptionViewItemV2::ViewItemFeatures>(context->thisObject());
    QString result;
    for (int i = 0; i < 6; ++i) {
        if ((value & qtscript_QStyleOptionViewItemV2_ViewItemFeature_values[i]) == qtscript_QStyleOptionViewItemV2_ViewItemFeature_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QStyleOptionViewItemV2_ViewItemFeature_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QStyleOptionViewItemV2_ViewItemFeatures_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QStyleOptionViewItemV2::ViewItemFeatures>() == otherObj.value<QStyleOptionViewItemV2::ViewItemFeatures>())));
}

static QScriptValue qtscript_create_QStyleOptionViewItemV2_ViewItemFeatures_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QStyleOptionViewItemV2_ViewItemFeatures, qtscript_QStyleOptionViewItemV2_ViewItemFeatures_valueOf,
        qtscript_QStyleOptionViewItemV2_ViewItemFeatures_toString, qtscript_QStyleOptionViewItemV2_ViewItemFeatures_equals);
    qScriptRegisterMetaType<QStyleOptionViewItemV2::ViewItemFeatures>(engine, qtscript_QStyleOptionViewItemV2_ViewItemFeatures_toScriptValue,
        qtscript_QStyleOptionViewItemV2_ViewItemFeatures_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QStyleOptionViewItemV2
//

static QScriptValue qtscript_QStyleOptionViewItemV2_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStyleOptionViewItemV2* _q_self = qscriptvalue_cast<QStyleOptionViewItemV2*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOptionViewItemV2.%0(): this object is not a QStyleOptionViewItemV2")
            .arg(qtscript_QStyleOptionViewItemV2_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QStyleOptionViewItemV2");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionViewItemV2_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionViewItemV2_function_names[_id+1],
        qtscript_QStyleOptionViewItemV2_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOptionViewItemV2_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOptionViewItemV2(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOptionViewItemV2 _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionViewItemV2)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QStyleOptionViewItem>() == context->argument(0).toVariant().userType())) {
            QStyleOptionViewItem _q_arg0 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(0));
            QtScriptShell_QStyleOptionViewItemV2 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionViewItemV2)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QStyleOptionViewItemV2>() == context->argument(0).toVariant().userType())) {
            QStyleOptionViewItemV2 _q_arg0 = qscriptvalue_cast<QStyleOptionViewItemV2>(context->argument(0));
            QtScriptShell_QStyleOptionViewItemV2 _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOptionViewItemV2)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOptionViewItemV2_throw_ambiguity_error_helper(context,
        qtscript_QStyleOptionViewItemV2_function_names[_id],
        qtscript_QStyleOptionViewItemV2_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOptionViewItemV2_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionViewItemV2*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOptionViewItemV2*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QStyleOptionViewItem*>()));

    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionViewItemV2>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOptionViewItemV2*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOptionViewItemV2_static_call, proto, qtscript_QStyleOptionViewItemV2_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOptionViewItemV2_StyleOptionVersion_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ViewItemFeature"),
        qtscript_create_QStyleOptionViewItemV2_ViewItemFeature_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ViewItemFeatures"),
        qtscript_create_QStyleOptionViewItemV2_ViewItemFeatures_class(engine));
    return ctor;
}
