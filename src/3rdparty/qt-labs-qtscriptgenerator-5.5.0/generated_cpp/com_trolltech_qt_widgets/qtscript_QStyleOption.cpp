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

#include "qtscriptshell_QStyleOption.h"

static const char * const qtscript_QStyleOption_function_names[] = {
    "QStyleOption"
    // static
    // prototype
    , "initFrom"
    , "toString"
};

static const char * const qtscript_QStyleOption_function_signatures[] = {
    "QStyleOption other\nint version, int type"
    // static
    // prototype
    , "QWidget w"
""
};

static const int qtscript_QStyleOption_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 0
};

static QScriptValue qtscript_QStyleOption_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyleOption::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyleOption)
Q_DECLARE_METATYPE(QStyleOption*)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOption)
Q_DECLARE_METATYPE(QtScriptShell_QStyleOption*)
Q_DECLARE_METATYPE(QStyleOption::OptionType)
Q_DECLARE_METATYPE(QStyleOption::StyleOptionType)
Q_DECLARE_METATYPE(QStyleOption::StyleOptionVersion)
Q_DECLARE_METATYPE(const QWidget*)

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
// QStyleOption::OptionType
//

static const QStyleOption::OptionType qtscript_QStyleOption_OptionType_values[] = {
    QStyleOption::SO_Default
    , QStyleOption::SO_FocusRect
    , QStyleOption::SO_Button
    , QStyleOption::SO_Tab
    , QStyleOption::SO_MenuItem
    , QStyleOption::SO_Frame
    , QStyleOption::SO_ProgressBar
    , QStyleOption::SO_ToolBox
    , QStyleOption::SO_Header
    , QStyleOption::SO_DockWidget
    , QStyleOption::SO_ViewItem
    , QStyleOption::SO_TabWidgetFrame
    , QStyleOption::SO_TabBarBase
    , QStyleOption::SO_RubberBand
    , QStyleOption::SO_ToolBar
    , QStyleOption::SO_GraphicsItem
    , QStyleOption::SO_CustomBase
    , QStyleOption::SO_Complex
    , QStyleOption::SO_Slider
    , QStyleOption::SO_SpinBox
    , QStyleOption::SO_ToolButton
    , QStyleOption::SO_ComboBox
    , QStyleOption::SO_TitleBar
    , QStyleOption::SO_GroupBox
    , QStyleOption::SO_SizeGrip
    , QStyleOption::SO_ComplexCustomBase
};

static const char * const qtscript_QStyleOption_OptionType_keys[] = {
    "SO_Default"
    , "SO_FocusRect"
    , "SO_Button"
    , "SO_Tab"
    , "SO_MenuItem"
    , "SO_Frame"
    , "SO_ProgressBar"
    , "SO_ToolBox"
    , "SO_Header"
    , "SO_DockWidget"
    , "SO_ViewItem"
    , "SO_TabWidgetFrame"
    , "SO_TabBarBase"
    , "SO_RubberBand"
    , "SO_ToolBar"
    , "SO_GraphicsItem"
    , "SO_CustomBase"
    , "SO_Complex"
    , "SO_Slider"
    , "SO_SpinBox"
    , "SO_ToolButton"
    , "SO_ComboBox"
    , "SO_TitleBar"
    , "SO_GroupBox"
    , "SO_SizeGrip"
    , "SO_ComplexCustomBase"
};

static QString qtscript_QStyleOption_OptionType_toStringHelper(QStyleOption::OptionType value)
{
    for (int i = 0; i < 26; ++i) {
        if (qtscript_QStyleOption_OptionType_values[i] == value)
            return QString::fromLatin1(qtscript_QStyleOption_OptionType_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStyleOption_OptionType_toScriptValue(QScriptEngine *engine, const QStyleOption::OptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOption"));
    return clazz.property(qtscript_QStyleOption_OptionType_toStringHelper(value));
}

static void qtscript_QStyleOption_OptionType_fromScriptValue(const QScriptValue &value, QStyleOption::OptionType &out)
{
    out = qvariant_cast<QStyleOption::OptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOption_OptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 26; ++i) {
        if (qtscript_QStyleOption_OptionType_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStyleOption::OptionType>(arg));
    }
    return context->throwError(QString::fromLatin1("OptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOption_OptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOption::OptionType value = qscriptvalue_cast<QStyleOption::OptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOption_OptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOption::OptionType value = qscriptvalue_cast<QStyleOption::OptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOption_OptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOption_OptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOption_OptionType,
        qtscript_QStyleOption_OptionType_valueOf, qtscript_QStyleOption_OptionType_toString);
    qScriptRegisterMetaType<QStyleOption::OptionType>(engine, qtscript_QStyleOption_OptionType_toScriptValue,
        qtscript_QStyleOption_OptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 26; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOption_OptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOption_OptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOption::StyleOptionType
//

static const QStyleOption::StyleOptionType qtscript_QStyleOption_StyleOptionType_values[] = {
    QStyleOption::Type
};

static const char * const qtscript_QStyleOption_StyleOptionType_keys[] = {
    "Type"
};

static QString qtscript_QStyleOption_StyleOptionType_toStringHelper(QStyleOption::StyleOptionType value)
{
    if ((value >= QStyleOption::Type) && (value <= QStyleOption::Type))
        return qtscript_QStyleOption_StyleOptionType_keys[static_cast<int>(value)-static_cast<int>(QStyleOption::Type)];
    return QString();
}

static QScriptValue qtscript_QStyleOption_StyleOptionType_toScriptValue(QScriptEngine *engine, const QStyleOption::StyleOptionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOption"));
    return clazz.property(qtscript_QStyleOption_StyleOptionType_toStringHelper(value));
}

static void qtscript_QStyleOption_StyleOptionType_fromScriptValue(const QScriptValue &value, QStyleOption::StyleOptionType &out)
{
    out = qvariant_cast<QStyleOption::StyleOptionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOption_StyleOptionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOption::Type) && (arg <= QStyleOption::Type))
        return qScriptValueFromValue(engine,  static_cast<QStyleOption::StyleOptionType>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOption_StyleOptionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOption::StyleOptionType value = qscriptvalue_cast<QStyleOption::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOption_StyleOptionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOption::StyleOptionType value = qscriptvalue_cast<QStyleOption::StyleOptionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOption_StyleOptionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOption_StyleOptionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOption_StyleOptionType,
        qtscript_QStyleOption_StyleOptionType_valueOf, qtscript_QStyleOption_StyleOptionType_toString);
    qScriptRegisterMetaType<QStyleOption::StyleOptionType>(engine, qtscript_QStyleOption_StyleOptionType_toScriptValue,
        qtscript_QStyleOption_StyleOptionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOption_StyleOptionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOption_StyleOptionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOption::StyleOptionVersion
//

static const QStyleOption::StyleOptionVersion qtscript_QStyleOption_StyleOptionVersion_values[] = {
    QStyleOption::Version
};

static const char * const qtscript_QStyleOption_StyleOptionVersion_keys[] = {
    "Version"
};

static QString qtscript_QStyleOption_StyleOptionVersion_toStringHelper(QStyleOption::StyleOptionVersion value)
{
    if ((value >= QStyleOption::Version) && (value <= QStyleOption::Version))
        return qtscript_QStyleOption_StyleOptionVersion_keys[static_cast<int>(value)-static_cast<int>(QStyleOption::Version)];
    return QString();
}

static QScriptValue qtscript_QStyleOption_StyleOptionVersion_toScriptValue(QScriptEngine *engine, const QStyleOption::StyleOptionVersion &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStyleOption"));
    return clazz.property(qtscript_QStyleOption_StyleOptionVersion_toStringHelper(value));
}

static void qtscript_QStyleOption_StyleOptionVersion_fromScriptValue(const QScriptValue &value, QStyleOption::StyleOptionVersion &out)
{
    out = qvariant_cast<QStyleOption::StyleOptionVersion>(value.toVariant());
}

static QScriptValue qtscript_construct_QStyleOption_StyleOptionVersion(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QStyleOption::Version) && (arg <= QStyleOption::Version))
        return qScriptValueFromValue(engine,  static_cast<QStyleOption::StyleOptionVersion>(arg));
    return context->throwError(QString::fromLatin1("StyleOptionVersion(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStyleOption_StyleOptionVersion_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOption::StyleOptionVersion value = qscriptvalue_cast<QStyleOption::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStyleOption_StyleOptionVersion_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStyleOption::StyleOptionVersion value = qscriptvalue_cast<QStyleOption::StyleOptionVersion>(context->thisObject());
    return QScriptValue(engine, qtscript_QStyleOption_StyleOptionVersion_toStringHelper(value));
}

static QScriptValue qtscript_create_QStyleOption_StyleOptionVersion_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStyleOption_StyleOptionVersion,
        qtscript_QStyleOption_StyleOptionVersion_valueOf, qtscript_QStyleOption_StyleOptionVersion_toString);
    qScriptRegisterMetaType<QStyleOption::StyleOptionVersion>(engine, qtscript_QStyleOption_StyleOptionVersion_toScriptValue,
        qtscript_QStyleOption_StyleOptionVersion_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStyleOption_StyleOptionVersion_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStyleOption_StyleOptionVersion_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStyleOption
//

static QScriptValue qtscript_QStyleOption_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QStyleOption* _q_self = qscriptvalue_cast<QStyleOption*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyleOption.%0(): this object is not a QStyleOption")
            .arg(qtscript_QStyleOption_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        const QWidget* _q_arg0 = qscriptvalue_cast<const QWidget*>(context->argument(0));
        _q_self->initFrom(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOption_throw_ambiguity_error_helper(context,
        qtscript_QStyleOption_function_names[_id+1],
        qtscript_QStyleOption_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyleOption_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyleOption(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyleOption _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOption)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QStyleOption>() == context->argument(0).toVariant().userType())) {
            QStyleOption _q_arg0 = qscriptvalue_cast<QStyleOption>(context->argument(0));
            QtScriptShell_QStyleOption _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOption)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QtScriptShell_QStyleOption _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOption)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QtScriptShell_QStyleOption _q_cpp_result(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStyleOption)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyleOption_throw_ambiguity_error_helper(context,
        qtscript_QStyleOption_function_names[_id],
        qtscript_QStyleOption_function_signatures[_id]);
}

QScriptValue qtscript_create_QStyleOption_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyleOption*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyleOption*)0));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStyleOption_prototype_call, qtscript_QStyleOption_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStyleOption_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QStyleOption>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QStyleOption*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyleOption_static_call, proto, qtscript_QStyleOption_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("OptionType"),
        qtscript_create_QStyleOption_OptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionType"),
        qtscript_create_QStyleOption_StyleOptionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StyleOptionVersion"),
        qtscript_create_QStyleOption_StyleOptionVersion_class(engine, ctor));
    return ctor;
}
