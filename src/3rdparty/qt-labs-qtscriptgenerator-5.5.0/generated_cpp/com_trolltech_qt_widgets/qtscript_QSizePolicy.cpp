#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsizepolicy.h>
#include <QVariant>
#include <qsizepolicy.h>

static const char * const qtscript_QSizePolicy_function_names[] = {
    "QSizePolicy"
    // static
    // prototype
    , "controlType"
    , "expandingDirections"
    , "hasHeightForWidth"
    , "hasWidthForHeight"
    , "horizontalPolicy"
    , "horizontalStretch"
    , "equals"
    , "retainSizeWhenHidden"
    , "setControlType"
    , "setHeightForWidth"
    , "setHorizontalPolicy"
    , "setHorizontalStretch"
    , "setRetainSizeWhenHidden"
    , "setVerticalPolicy"
    , "setVerticalStretch"
    , "setWidthForHeight"
    , "transpose"
    , "verticalPolicy"
    , "verticalStretch"
    , "toString"
};

static const char * const qtscript_QSizePolicy_function_signatures[] = {
    "\nPolicy horizontal, Policy vertical, ControlType type"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QSizePolicy s"
    , ""
    , "ControlType type"
    , "bool b"
    , "Policy d"
    , "int stretchFactor"
    , "bool retainSize"
    , "Policy d"
    , "int stretchFactor"
    , "bool b"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QSizePolicy_function_lengths[] = {
    3
    // static
    // prototype
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
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QSizePolicy_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSizePolicy::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QSizePolicy_metaObject()
{
    return &QSizePolicy::staticMetaObject;
}

Q_DECLARE_METATYPE(QSizePolicy*)
Q_DECLARE_METATYPE(QSizePolicy::PolicyFlag)
Q_DECLARE_METATYPE(QSizePolicy::Policy)
Q_DECLARE_METATYPE(QSizePolicy::ControlType)
Q_DECLARE_METATYPE(QFlags<QSizePolicy::ControlType>)
Q_DECLARE_METATYPE(QFlags<Qt::Orientation>)

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
// QSizePolicy::PolicyFlag
//

static const QSizePolicy::PolicyFlag qtscript_QSizePolicy_PolicyFlag_values[] = {
    QSizePolicy::GrowFlag
    , QSizePolicy::ExpandFlag
    , QSizePolicy::ShrinkFlag
    , QSizePolicy::IgnoreFlag
};

static const char * const qtscript_QSizePolicy_PolicyFlag_keys[] = {
    "GrowFlag"
    , "ExpandFlag"
    , "ShrinkFlag"
    , "IgnoreFlag"
};

static QString qtscript_QSizePolicy_PolicyFlag_toStringHelper(QSizePolicy::PolicyFlag value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QSizePolicy_PolicyFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QSizePolicy_PolicyFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QSizePolicy_PolicyFlag_toScriptValue(QScriptEngine *engine, const QSizePolicy::PolicyFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSizePolicy"));
    return clazz.property(qtscript_QSizePolicy_PolicyFlag_toStringHelper(value));
}

static void qtscript_QSizePolicy_PolicyFlag_fromScriptValue(const QScriptValue &value, QSizePolicy::PolicyFlag &out)
{
    out = qvariant_cast<QSizePolicy::PolicyFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QSizePolicy_PolicyFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QSizePolicy_PolicyFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QSizePolicy::PolicyFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("PolicyFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSizePolicy_PolicyFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSizePolicy::PolicyFlag value = qscriptvalue_cast<QSizePolicy::PolicyFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSizePolicy_PolicyFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSizePolicy::PolicyFlag value = qscriptvalue_cast<QSizePolicy::PolicyFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QSizePolicy_PolicyFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QSizePolicy_PolicyFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSizePolicy_PolicyFlag,
        qtscript_QSizePolicy_PolicyFlag_valueOf, qtscript_QSizePolicy_PolicyFlag_toString);
    qScriptRegisterMetaType<QSizePolicy::PolicyFlag>(engine, qtscript_QSizePolicy_PolicyFlag_toScriptValue,
        qtscript_QSizePolicy_PolicyFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSizePolicy_PolicyFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSizePolicy_PolicyFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSizePolicy::Policy
//

static const QSizePolicy::Policy qtscript_QSizePolicy_Policy_values[] = {
    QSizePolicy::Fixed
    , QSizePolicy::Minimum
    , QSizePolicy::MinimumExpanding
    , QSizePolicy::Maximum
    , QSizePolicy::Preferred
    , QSizePolicy::Expanding
    , QSizePolicy::Ignored
};

static const char * const qtscript_QSizePolicy_Policy_keys[] = {
    "Fixed"
    , "Minimum"
    , "MinimumExpanding"
    , "Maximum"
    , "Preferred"
    , "Expanding"
    , "Ignored"
};

static QString qtscript_QSizePolicy_Policy_toStringHelper(QSizePolicy::Policy value)
{
    const QMetaObject *meta = qtscript_QSizePolicy_metaObject();
    int idx = meta->indexOfEnumerator("Policy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QSizePolicy_Policy_toScriptValue(QScriptEngine *engine, const QSizePolicy::Policy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSizePolicy"));
    return clazz.property(qtscript_QSizePolicy_Policy_toStringHelper(value));
}

static void qtscript_QSizePolicy_Policy_fromScriptValue(const QScriptValue &value, QSizePolicy::Policy &out)
{
    out = qvariant_cast<QSizePolicy::Policy>(value.toVariant());
}

static QScriptValue qtscript_construct_QSizePolicy_Policy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QSizePolicy_metaObject();
    int idx = meta->indexOfEnumerator("Policy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QSizePolicy::Policy>(arg));
    return context->throwError(QString::fromLatin1("Policy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSizePolicy_Policy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSizePolicy::Policy value = qscriptvalue_cast<QSizePolicy::Policy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSizePolicy_Policy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSizePolicy::Policy value = qscriptvalue_cast<QSizePolicy::Policy>(context->thisObject());
    return QScriptValue(engine, qtscript_QSizePolicy_Policy_toStringHelper(value));
}

static QScriptValue qtscript_create_QSizePolicy_Policy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSizePolicy_Policy,
        qtscript_QSizePolicy_Policy_valueOf, qtscript_QSizePolicy_Policy_toString);
    qScriptRegisterMetaType<QSizePolicy::Policy>(engine, qtscript_QSizePolicy_Policy_toScriptValue,
        qtscript_QSizePolicy_Policy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSizePolicy_Policy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSizePolicy_Policy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSizePolicy::ControlType
//

static const QSizePolicy::ControlType qtscript_QSizePolicy_ControlType_values[] = {
    QSizePolicy::DefaultType
    , QSizePolicy::ButtonBox
    , QSizePolicy::CheckBox
    , QSizePolicy::ComboBox
    , QSizePolicy::Frame
    , QSizePolicy::GroupBox
    , QSizePolicy::Label
    , QSizePolicy::Line
    , QSizePolicy::LineEdit
    , QSizePolicy::PushButton
    , QSizePolicy::RadioButton
    , QSizePolicy::Slider
    , QSizePolicy::SpinBox
    , QSizePolicy::TabWidget
    , QSizePolicy::ToolButton
};

static const char * const qtscript_QSizePolicy_ControlType_keys[] = {
    "DefaultType"
    , "ButtonBox"
    , "CheckBox"
    , "ComboBox"
    , "Frame"
    , "GroupBox"
    , "Label"
    , "Line"
    , "LineEdit"
    , "PushButton"
    , "RadioButton"
    , "Slider"
    , "SpinBox"
    , "TabWidget"
    , "ToolButton"
};

static QString qtscript_QSizePolicy_ControlType_toStringHelper(QSizePolicy::ControlType value)
{
    for (int i = 0; i < 15; ++i) {
        if (qtscript_QSizePolicy_ControlType_values[i] == value)
            return QString::fromLatin1(qtscript_QSizePolicy_ControlType_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QSizePolicy_ControlType_toScriptValue(QScriptEngine *engine, const QSizePolicy::ControlType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSizePolicy"));
    return clazz.property(qtscript_QSizePolicy_ControlType_toStringHelper(value));
}

static void qtscript_QSizePolicy_ControlType_fromScriptValue(const QScriptValue &value, QSizePolicy::ControlType &out)
{
    out = qvariant_cast<QSizePolicy::ControlType>(value.toVariant());
}

static QScriptValue qtscript_construct_QSizePolicy_ControlType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 15; ++i) {
        if (qtscript_QSizePolicy_ControlType_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QSizePolicy::ControlType>(arg));
    }
    return context->throwError(QString::fromLatin1("ControlType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSizePolicy_ControlType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSizePolicy::ControlType value = qscriptvalue_cast<QSizePolicy::ControlType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSizePolicy_ControlType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSizePolicy::ControlType value = qscriptvalue_cast<QSizePolicy::ControlType>(context->thisObject());
    return QScriptValue(engine, qtscript_QSizePolicy_ControlType_toStringHelper(value));
}

static QScriptValue qtscript_create_QSizePolicy_ControlType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSizePolicy_ControlType,
        qtscript_QSizePolicy_ControlType_valueOf, qtscript_QSizePolicy_ControlType_toString);
    qScriptRegisterMetaType<QSizePolicy::ControlType>(engine, qtscript_QSizePolicy_ControlType_toScriptValue,
        qtscript_QSizePolicy_ControlType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 15; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSizePolicy_ControlType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSizePolicy_ControlType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSizePolicy::ControlTypes
//

static QScriptValue qtscript_QSizePolicy_ControlTypes_toScriptValue(QScriptEngine *engine, const QSizePolicy::ControlTypes &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QSizePolicy_ControlTypes_fromScriptValue(const QScriptValue &value, QSizePolicy::ControlTypes &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QSizePolicy::ControlTypes>())
        out = qvariant_cast<QSizePolicy::ControlTypes>(var);
    else if (var.userType() == qMetaTypeId<QSizePolicy::ControlType>())
        out = qvariant_cast<QSizePolicy::ControlType>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QSizePolicy_ControlTypes(QScriptContext *context, QScriptEngine *engine)
{
    QSizePolicy::ControlTypes result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QSizePolicy::ControlTypes>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QSizePolicy::ControlType>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ControlTypes(): argument %0 is not of type ControlType").arg(i));
            }
            result |= qvariant_cast<QSizePolicy::ControlType>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QSizePolicy_ControlTypes_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSizePolicy::ControlTypes value = qscriptvalue_cast<QSizePolicy::ControlTypes>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSizePolicy_ControlTypes_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSizePolicy::ControlTypes value = qscriptvalue_cast<QSizePolicy::ControlTypes>(context->thisObject());
    QString result;
    for (int i = 0; i < 15; ++i) {
        if ((value & qtscript_QSizePolicy_ControlType_values[i]) == qtscript_QSizePolicy_ControlType_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QSizePolicy_ControlType_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QSizePolicy_ControlTypes_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QSizePolicy::ControlTypes>() == otherObj.value<QSizePolicy::ControlTypes>())));
}

static QScriptValue qtscript_create_QSizePolicy_ControlTypes_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QSizePolicy_ControlTypes, qtscript_QSizePolicy_ControlTypes_valueOf,
        qtscript_QSizePolicy_ControlTypes_toString, qtscript_QSizePolicy_ControlTypes_equals);
    qScriptRegisterMetaType<QSizePolicy::ControlTypes>(engine, qtscript_QSizePolicy_ControlTypes_toScriptValue,
        qtscript_QSizePolicy_ControlTypes_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QSizePolicy
//

static QScriptValue qtscript_QSizePolicy_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 19;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSizePolicy* _q_self = qscriptvalue_cast<QSizePolicy*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSizePolicy.%0(): this object is not a QSizePolicy")
            .arg(qtscript_QSizePolicy_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QSizePolicy::ControlType _q_result = _q_self->controlType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QFlags<Qt::Orientation> _q_result = _q_self->expandingDirections();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasHeightForWidth();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasWidthForHeight();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QSizePolicy::Policy _q_result = _q_self->horizontalPolicy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->horizontalStretch();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QSizePolicy _q_arg0 = qscriptvalue_cast<QSizePolicy>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->retainSizeWhenHidden();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QSizePolicy::ControlType _q_arg0 = qscriptvalue_cast<QSizePolicy::ControlType>(context->argument(0));
        _q_self->setControlType(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setHeightForWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QSizePolicy::Policy _q_arg0 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(0));
        _q_self->setHorizontalPolicy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setHorizontalStretch(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setRetainSizeWhenHidden(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QSizePolicy::Policy _q_arg0 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(0));
        _q_self->setVerticalPolicy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setVerticalStretch(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setWidthForHeight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        _q_self->transpose();
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QSizePolicy::Policy _q_result = _q_self->verticalPolicy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->verticalStretch();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSizePolicy_throw_ambiguity_error_helper(context,
        qtscript_QSizePolicy_function_names[_id+1],
        qtscript_QSizePolicy_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSizePolicy_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSizePolicy(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QSizePolicy _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QSizePolicy::Policy _q_arg0 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(0));
        QSizePolicy::Policy _q_arg1 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(1));
        QSizePolicy _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QSizePolicy::Policy _q_arg0 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(0));
        QSizePolicy::Policy _q_arg1 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(1));
        QSizePolicy::ControlType _q_arg2 = qscriptvalue_cast<QSizePolicy::ControlType>(context->argument(2));
        QSizePolicy _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSizePolicy_throw_ambiguity_error_helper(context,
        qtscript_QSizePolicy_function_names[_id],
        qtscript_QSizePolicy_function_signatures[_id]);
}

QScriptValue qtscript_create_QSizePolicy_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSizePolicy*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSizePolicy*)0));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSizePolicy_prototype_call, qtscript_QSizePolicy_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSizePolicy_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSizePolicy>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QSizePolicy*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSizePolicy_static_call, proto, qtscript_QSizePolicy_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("PolicyFlag"),
        qtscript_create_QSizePolicy_PolicyFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Policy"),
        qtscript_create_QSizePolicy_Policy_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ControlType"),
        qtscript_create_QSizePolicy_ControlType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ControlTypes"),
        qtscript_create_QSizePolicy_ControlTypes_class(engine));
    return ctor;
}
