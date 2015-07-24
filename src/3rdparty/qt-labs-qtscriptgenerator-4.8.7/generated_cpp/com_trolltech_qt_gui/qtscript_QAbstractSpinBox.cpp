#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractspinbox.h>
#include <QVariant>
#include <qabstractspinbox.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qinputcontext.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QAbstractSpinBox.h"

static const char * const qtscript_QAbstractSpinBox_function_names[] = {
    "QAbstractSpinBox"
    // static
    // prototype
    , "fixup"
    , "interpretText"
    , "minimumSizeHint"
    , "sizeHint"
    , "stepBy"
    , "validate"
    , "toString"
};

static const char * const qtscript_QAbstractSpinBox_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "String input"
    , ""
    , ""
    , ""
    , "int steps"
    , "String input, int pos"
""
};

static const int qtscript_QAbstractSpinBox_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
    , 0
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QAbstractSpinBox_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractSpinBox::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QAbstractSpinBox_metaObject()
{
    return &QAbstractSpinBox::staticMetaObject;
}

Q_DECLARE_METATYPE(QAbstractSpinBox*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractSpinBox*)
Q_DECLARE_METATYPE(QAbstractSpinBox::StepEnabledFlag)
Q_DECLARE_METATYPE(QFlags<QAbstractSpinBox::StepEnabledFlag>)
Q_DECLARE_METATYPE(QAbstractSpinBox::CorrectionMode)
Q_DECLARE_METATYPE(QAbstractSpinBox::ButtonSymbols)
Q_DECLARE_METATYPE(QValidator::State)

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
// QAbstractSpinBox::StepEnabledFlag
//

static const QAbstractSpinBox::StepEnabledFlag qtscript_QAbstractSpinBox_StepEnabledFlag_values[] = {
    QAbstractSpinBox::StepNone
    , QAbstractSpinBox::StepUpEnabled
    , QAbstractSpinBox::StepDownEnabled
};

static const char * const qtscript_QAbstractSpinBox_StepEnabledFlag_keys[] = {
    "StepNone"
    , "StepUpEnabled"
    , "StepDownEnabled"
};

static QString qtscript_QAbstractSpinBox_StepEnabledFlag_toStringHelper(QAbstractSpinBox::StepEnabledFlag value)
{
    if ((value >= QAbstractSpinBox::StepNone) && (value <= QAbstractSpinBox::StepDownEnabled))
        return qtscript_QAbstractSpinBox_StepEnabledFlag_keys[static_cast<int>(value)-static_cast<int>(QAbstractSpinBox::StepNone)];
    return QString();
}

static QScriptValue qtscript_QAbstractSpinBox_StepEnabledFlag_toScriptValue(QScriptEngine *engine, const QAbstractSpinBox::StepEnabledFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSpinBox"));
    return clazz.property(qtscript_QAbstractSpinBox_StepEnabledFlag_toStringHelper(value));
}

static void qtscript_QAbstractSpinBox_StepEnabledFlag_fromScriptValue(const QScriptValue &value, QAbstractSpinBox::StepEnabledFlag &out)
{
    out = qvariant_cast<QAbstractSpinBox::StepEnabledFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSpinBox_StepEnabledFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractSpinBox::StepNone) && (arg <= QAbstractSpinBox::StepDownEnabled))
        return qScriptValueFromValue(engine,  static_cast<QAbstractSpinBox::StepEnabledFlag>(arg));
    return context->throwError(QString::fromLatin1("StepEnabledFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSpinBox_StepEnabledFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSpinBox::StepEnabledFlag value = qscriptvalue_cast<QAbstractSpinBox::StepEnabledFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSpinBox_StepEnabledFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSpinBox::StepEnabledFlag value = qscriptvalue_cast<QAbstractSpinBox::StepEnabledFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSpinBox_StepEnabledFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSpinBox_StepEnabledFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSpinBox_StepEnabledFlag,
        qtscript_QAbstractSpinBox_StepEnabledFlag_valueOf, qtscript_QAbstractSpinBox_StepEnabledFlag_toString);
    qScriptRegisterMetaType<QAbstractSpinBox::StepEnabledFlag>(engine, qtscript_QAbstractSpinBox_StepEnabledFlag_toScriptValue,
        qtscript_QAbstractSpinBox_StepEnabledFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSpinBox_StepEnabledFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSpinBox_StepEnabledFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSpinBox::StepEnabled
//

static QScriptValue qtscript_QAbstractSpinBox_StepEnabled_toScriptValue(QScriptEngine *engine, const QAbstractSpinBox::StepEnabled &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QAbstractSpinBox_StepEnabled_fromScriptValue(const QScriptValue &value, QAbstractSpinBox::StepEnabled &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QAbstractSpinBox::StepEnabled>())
        out = qvariant_cast<QAbstractSpinBox::StepEnabled>(var);
    else if (var.userType() == qMetaTypeId<QAbstractSpinBox::StepEnabledFlag>())
        out = qvariant_cast<QAbstractSpinBox::StepEnabledFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QAbstractSpinBox_StepEnabled(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSpinBox::StepEnabled result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QAbstractSpinBox::StepEnabled>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QAbstractSpinBox::StepEnabledFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("StepEnabled(): argument %0 is not of type StepEnabledFlag").arg(i));
            }
            result |= qvariant_cast<QAbstractSpinBox::StepEnabledFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QAbstractSpinBox_StepEnabled_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSpinBox::StepEnabled value = qscriptvalue_cast<QAbstractSpinBox::StepEnabled>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSpinBox_StepEnabled_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSpinBox::StepEnabled value = qscriptvalue_cast<QAbstractSpinBox::StepEnabled>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QAbstractSpinBox_StepEnabledFlag_values[i]) == qtscript_QAbstractSpinBox_StepEnabledFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QAbstractSpinBox_StepEnabledFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QAbstractSpinBox_StepEnabled_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QAbstractSpinBox::StepEnabled>() == otherObj.value<QAbstractSpinBox::StepEnabled>())));
}

static QScriptValue qtscript_create_QAbstractSpinBox_StepEnabled_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QAbstractSpinBox_StepEnabled, qtscript_QAbstractSpinBox_StepEnabled_valueOf,
        qtscript_QAbstractSpinBox_StepEnabled_toString, qtscript_QAbstractSpinBox_StepEnabled_equals);
    qScriptRegisterMetaType<QAbstractSpinBox::StepEnabled>(engine, qtscript_QAbstractSpinBox_StepEnabled_toScriptValue,
        qtscript_QAbstractSpinBox_StepEnabled_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QAbstractSpinBox::CorrectionMode
//

static const QAbstractSpinBox::CorrectionMode qtscript_QAbstractSpinBox_CorrectionMode_values[] = {
    QAbstractSpinBox::CorrectToPreviousValue
    , QAbstractSpinBox::CorrectToNearestValue
};

static const char * const qtscript_QAbstractSpinBox_CorrectionMode_keys[] = {
    "CorrectToPreviousValue"
    , "CorrectToNearestValue"
};

static QString qtscript_QAbstractSpinBox_CorrectionMode_toStringHelper(QAbstractSpinBox::CorrectionMode value)
{
    const QMetaObject *meta = qtscript_QAbstractSpinBox_metaObject();
    int idx = meta->indexOfEnumerator("CorrectionMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractSpinBox_CorrectionMode_toScriptValue(QScriptEngine *engine, const QAbstractSpinBox::CorrectionMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSpinBox"));
    return clazz.property(qtscript_QAbstractSpinBox_CorrectionMode_toStringHelper(value));
}

static void qtscript_QAbstractSpinBox_CorrectionMode_fromScriptValue(const QScriptValue &value, QAbstractSpinBox::CorrectionMode &out)
{
    out = qvariant_cast<QAbstractSpinBox::CorrectionMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSpinBox_CorrectionMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractSpinBox_metaObject();
    int idx = meta->indexOfEnumerator("CorrectionMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractSpinBox::CorrectionMode>(arg));
    return context->throwError(QString::fromLatin1("CorrectionMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSpinBox_CorrectionMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSpinBox::CorrectionMode value = qscriptvalue_cast<QAbstractSpinBox::CorrectionMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSpinBox_CorrectionMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSpinBox::CorrectionMode value = qscriptvalue_cast<QAbstractSpinBox::CorrectionMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSpinBox_CorrectionMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSpinBox_CorrectionMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSpinBox_CorrectionMode,
        qtscript_QAbstractSpinBox_CorrectionMode_valueOf, qtscript_QAbstractSpinBox_CorrectionMode_toString);
    qScriptRegisterMetaType<QAbstractSpinBox::CorrectionMode>(engine, qtscript_QAbstractSpinBox_CorrectionMode_toScriptValue,
        qtscript_QAbstractSpinBox_CorrectionMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSpinBox_CorrectionMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSpinBox_CorrectionMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSpinBox::ButtonSymbols
//

static const QAbstractSpinBox::ButtonSymbols qtscript_QAbstractSpinBox_ButtonSymbols_values[] = {
    QAbstractSpinBox::UpDownArrows
    , QAbstractSpinBox::PlusMinus
    , QAbstractSpinBox::NoButtons
};

static const char * const qtscript_QAbstractSpinBox_ButtonSymbols_keys[] = {
    "UpDownArrows"
    , "PlusMinus"
    , "NoButtons"
};

static QString qtscript_QAbstractSpinBox_ButtonSymbols_toStringHelper(QAbstractSpinBox::ButtonSymbols value)
{
    const QMetaObject *meta = qtscript_QAbstractSpinBox_metaObject();
    int idx = meta->indexOfEnumerator("ButtonSymbols");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractSpinBox_ButtonSymbols_toScriptValue(QScriptEngine *engine, const QAbstractSpinBox::ButtonSymbols &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSpinBox"));
    return clazz.property(qtscript_QAbstractSpinBox_ButtonSymbols_toStringHelper(value));
}

static void qtscript_QAbstractSpinBox_ButtonSymbols_fromScriptValue(const QScriptValue &value, QAbstractSpinBox::ButtonSymbols &out)
{
    out = qvariant_cast<QAbstractSpinBox::ButtonSymbols>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSpinBox_ButtonSymbols(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractSpinBox_metaObject();
    int idx = meta->indexOfEnumerator("ButtonSymbols");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractSpinBox::ButtonSymbols>(arg));
    return context->throwError(QString::fromLatin1("ButtonSymbols(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSpinBox_ButtonSymbols_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSpinBox::ButtonSymbols value = qscriptvalue_cast<QAbstractSpinBox::ButtonSymbols>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSpinBox_ButtonSymbols_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSpinBox::ButtonSymbols value = qscriptvalue_cast<QAbstractSpinBox::ButtonSymbols>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSpinBox_ButtonSymbols_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSpinBox_ButtonSymbols_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSpinBox_ButtonSymbols,
        qtscript_QAbstractSpinBox_ButtonSymbols_valueOf, qtscript_QAbstractSpinBox_ButtonSymbols_toString);
    qScriptRegisterMetaType<QAbstractSpinBox::ButtonSymbols>(engine, qtscript_QAbstractSpinBox_ButtonSymbols_toScriptValue,
        qtscript_QAbstractSpinBox_ButtonSymbols_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSpinBox_ButtonSymbols_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSpinBox_ButtonSymbols_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSpinBox
//

static QScriptValue qtscript_QAbstractSpinBox_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 6;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractSpinBox* _q_self = qscriptvalue_cast<QAbstractSpinBox*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractSpinBox.%0(): this object is not a QAbstractSpinBox")
            .arg(qtscript_QAbstractSpinBox_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->fixup(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->interpretText();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->stepBy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_arg1 = context->argument(1).toInt32();
        QValidator::State _q_result = _q_self->validate(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QAbstractSpinBox");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractSpinBox_throw_ambiguity_error_helper(context,
        qtscript_QAbstractSpinBox_function_names[_id+1],
        qtscript_QAbstractSpinBox_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractSpinBox_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractSpinBox(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractSpinBox* _q_cpp_result = new QtScriptShell_QAbstractSpinBox();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractSpinBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QAbstractSpinBox* _q_cpp_result = new QtScriptShell_QAbstractSpinBox(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractSpinBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractSpinBox_throw_ambiguity_error_helper(context,
        qtscript_QAbstractSpinBox_function_names[_id],
        qtscript_QAbstractSpinBox_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractSpinBox_toScriptValue(QScriptEngine *engine, QAbstractSpinBox* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractSpinBox_fromScriptValue(const QScriptValue &value, QAbstractSpinBox* &out)
{
    out = qobject_cast<QAbstractSpinBox*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractSpinBox_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractSpinBox*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractSpinBox*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractSpinBox_prototype_call, qtscript_QAbstractSpinBox_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractSpinBox_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractSpinBox*>(engine, qtscript_QAbstractSpinBox_toScriptValue, 
        qtscript_QAbstractSpinBox_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractSpinBox_static_call, proto, qtscript_QAbstractSpinBox_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StepEnabledFlag"),
        qtscript_create_QAbstractSpinBox_StepEnabledFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StepEnabled"),
        qtscript_create_QAbstractSpinBox_StepEnabled_class(engine));
    ctor.setProperty(QString::fromLatin1("CorrectionMode"),
        qtscript_create_QAbstractSpinBox_CorrectionMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ButtonSymbols"),
        qtscript_create_QAbstractSpinBox_ButtonSymbols_class(engine, ctor));
    return ctor;
}
