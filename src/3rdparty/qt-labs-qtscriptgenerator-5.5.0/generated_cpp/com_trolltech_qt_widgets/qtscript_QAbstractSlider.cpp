#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qabstractslider.h>
#include <QVariant>
#include <qabstractslider.h>
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
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QAbstractSlider.h"

static const char * const qtscript_QAbstractSlider_function_names[] = {
    "QAbstractSlider"
    // static
    // prototype
    , "triggerAction"
    , "toString"
};

static const char * const qtscript_QAbstractSlider_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "SliderAction action"
""
};

static const int qtscript_QAbstractSlider_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
};

static QScriptValue qtscript_QAbstractSlider_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractSlider::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractSlider*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractSlider*)
Q_DECLARE_METATYPE(QAbstractSlider::SliderAction)
Q_DECLARE_METATYPE(QWidget*)

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
// QAbstractSlider::SliderAction
//

static const QAbstractSlider::SliderAction qtscript_QAbstractSlider_SliderAction_values[] = {
    QAbstractSlider::SliderNoAction
    , QAbstractSlider::SliderSingleStepAdd
    , QAbstractSlider::SliderSingleStepSub
    , QAbstractSlider::SliderPageStepAdd
    , QAbstractSlider::SliderPageStepSub
    , QAbstractSlider::SliderToMinimum
    , QAbstractSlider::SliderToMaximum
    , QAbstractSlider::SliderMove
};

static const char * const qtscript_QAbstractSlider_SliderAction_keys[] = {
    "SliderNoAction"
    , "SliderSingleStepAdd"
    , "SliderSingleStepSub"
    , "SliderPageStepAdd"
    , "SliderPageStepSub"
    , "SliderToMinimum"
    , "SliderToMaximum"
    , "SliderMove"
};

static QString qtscript_QAbstractSlider_SliderAction_toStringHelper(QAbstractSlider::SliderAction value)
{
    if ((value >= QAbstractSlider::SliderNoAction) && (value <= QAbstractSlider::SliderMove))
        return qtscript_QAbstractSlider_SliderAction_keys[static_cast<int>(value)-static_cast<int>(QAbstractSlider::SliderNoAction)];
    return QString();
}

static QScriptValue qtscript_QAbstractSlider_SliderAction_toScriptValue(QScriptEngine *engine, const QAbstractSlider::SliderAction &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSlider"));
    return clazz.property(qtscript_QAbstractSlider_SliderAction_toStringHelper(value));
}

static void qtscript_QAbstractSlider_SliderAction_fromScriptValue(const QScriptValue &value, QAbstractSlider::SliderAction &out)
{
    out = qvariant_cast<QAbstractSlider::SliderAction>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSlider_SliderAction(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractSlider::SliderNoAction) && (arg <= QAbstractSlider::SliderMove))
        return qScriptValueFromValue(engine,  static_cast<QAbstractSlider::SliderAction>(arg));
    return context->throwError(QString::fromLatin1("SliderAction(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSlider_SliderAction_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSlider::SliderAction value = qscriptvalue_cast<QAbstractSlider::SliderAction>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSlider_SliderAction_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSlider::SliderAction value = qscriptvalue_cast<QAbstractSlider::SliderAction>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSlider_SliderAction_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSlider_SliderAction_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSlider_SliderAction,
        qtscript_QAbstractSlider_SliderAction_valueOf, qtscript_QAbstractSlider_SliderAction_toString);
    qScriptRegisterMetaType<QAbstractSlider::SliderAction>(engine, qtscript_QAbstractSlider_SliderAction_toScriptValue,
        qtscript_QAbstractSlider_SliderAction_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSlider_SliderAction_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSlider_SliderAction_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSlider
//

static QScriptValue qtscript_QAbstractSlider_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QAbstractSlider* _q_self = qscriptvalue_cast<QAbstractSlider*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractSlider.%0(): this object is not a QAbstractSlider")
            .arg(qtscript_QAbstractSlider_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QAbstractSlider::SliderAction _q_arg0 = qscriptvalue_cast<QAbstractSlider::SliderAction>(context->argument(0));
        _q_self->triggerAction(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QAbstractSlider");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractSlider_throw_ambiguity_error_helper(context,
        qtscript_QAbstractSlider_function_names[_id+1],
        qtscript_QAbstractSlider_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractSlider_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractSlider(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractSlider* _q_cpp_result = new QtScriptShell_QAbstractSlider();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractSlider*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QAbstractSlider* _q_cpp_result = new QtScriptShell_QAbstractSlider(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractSlider*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractSlider_throw_ambiguity_error_helper(context,
        qtscript_QAbstractSlider_function_names[_id],
        qtscript_QAbstractSlider_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractSlider_toScriptValue(QScriptEngine *engine, QAbstractSlider* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractSlider_fromScriptValue(const QScriptValue &value, QAbstractSlider* &out)
{
    out = qobject_cast<QAbstractSlider*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractSlider_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractSlider*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractSlider*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractSlider_prototype_call, qtscript_QAbstractSlider_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractSlider_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractSlider*>(engine, qtscript_QAbstractSlider_toScriptValue, 
        qtscript_QAbstractSlider_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractSlider_static_call, proto, qtscript_QAbstractSlider_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("SliderAction"),
        qtscript_create_QAbstractSlider_SliderAction_class(engine, ctor));
    return ctor;
}
