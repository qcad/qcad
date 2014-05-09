#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qlcdnumber.h>
#include <QVariant>
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
#include <qlcdnumber.h>
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

#include "qtscriptshell_QLCDNumber.h"

static const char * const qtscript_QLCDNumber_function_names[] = {
    "QLCDNumber"
    // static
    // prototype
    , "checkOverflow"
    , "toString"
};

static const char * const qtscript_QLCDNumber_function_signatures[] = {
    "QWidget parent\nuint numDigits, QWidget parent"
    // static
    // prototype
    , "double num\nint num"
""
};

static const int qtscript_QLCDNumber_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 0
};

static QScriptValue qtscript_QLCDNumber_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QLCDNumber::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QLCDNumber_metaObject()
{
    return &QLCDNumber::staticMetaObject;
}

Q_DECLARE_METATYPE(QLCDNumber*)
Q_DECLARE_METATYPE(QtScriptShell_QLCDNumber*)
Q_DECLARE_METATYPE(QLCDNumber::SegmentStyle)
Q_DECLARE_METATYPE(QLCDNumber::Mode)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QFrame*)

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
// QLCDNumber::SegmentStyle
//

static const QLCDNumber::SegmentStyle qtscript_QLCDNumber_SegmentStyle_values[] = {
    QLCDNumber::Outline
    , QLCDNumber::Filled
    , QLCDNumber::Flat
};

static const char * const qtscript_QLCDNumber_SegmentStyle_keys[] = {
    "Outline"
    , "Filled"
    , "Flat"
};

static QString qtscript_QLCDNumber_SegmentStyle_toStringHelper(QLCDNumber::SegmentStyle value)
{
    const QMetaObject *meta = qtscript_QLCDNumber_metaObject();
    int idx = meta->indexOfEnumerator("SegmentStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QLCDNumber_SegmentStyle_toScriptValue(QScriptEngine *engine, const QLCDNumber::SegmentStyle &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLCDNumber"));
    return clazz.property(qtscript_QLCDNumber_SegmentStyle_toStringHelper(value));
}

static void qtscript_QLCDNumber_SegmentStyle_fromScriptValue(const QScriptValue &value, QLCDNumber::SegmentStyle &out)
{
    out = qvariant_cast<QLCDNumber::SegmentStyle>(value.toVariant());
}

static QScriptValue qtscript_construct_QLCDNumber_SegmentStyle(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QLCDNumber_metaObject();
    int idx = meta->indexOfEnumerator("SegmentStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QLCDNumber::SegmentStyle>(arg));
    return context->throwError(QString::fromLatin1("SegmentStyle(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLCDNumber_SegmentStyle_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLCDNumber::SegmentStyle value = qscriptvalue_cast<QLCDNumber::SegmentStyle>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLCDNumber_SegmentStyle_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLCDNumber::SegmentStyle value = qscriptvalue_cast<QLCDNumber::SegmentStyle>(context->thisObject());
    return QScriptValue(engine, qtscript_QLCDNumber_SegmentStyle_toStringHelper(value));
}

static QScriptValue qtscript_create_QLCDNumber_SegmentStyle_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLCDNumber_SegmentStyle,
        qtscript_QLCDNumber_SegmentStyle_valueOf, qtscript_QLCDNumber_SegmentStyle_toString);
    qScriptRegisterMetaType<QLCDNumber::SegmentStyle>(engine, qtscript_QLCDNumber_SegmentStyle_toScriptValue,
        qtscript_QLCDNumber_SegmentStyle_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLCDNumber_SegmentStyle_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLCDNumber_SegmentStyle_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLCDNumber::Mode
//

static const QLCDNumber::Mode qtscript_QLCDNumber_Mode_values[] = {
    QLCDNumber::Hex
    , QLCDNumber::Dec
    , QLCDNumber::Oct
    , QLCDNumber::Bin
};

static const char * const qtscript_QLCDNumber_Mode_keys[] = {
    "Hex"
    , "Dec"
    , "Oct"
    , "Bin"
};

static QString qtscript_QLCDNumber_Mode_toStringHelper(QLCDNumber::Mode value)
{
    const QMetaObject *meta = qtscript_QLCDNumber_metaObject();
    int idx = meta->indexOfEnumerator("Mode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QLCDNumber_Mode_toScriptValue(QScriptEngine *engine, const QLCDNumber::Mode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLCDNumber"));
    return clazz.property(qtscript_QLCDNumber_Mode_toStringHelper(value));
}

static void qtscript_QLCDNumber_Mode_fromScriptValue(const QScriptValue &value, QLCDNumber::Mode &out)
{
    out = qvariant_cast<QLCDNumber::Mode>(value.toVariant());
}

static QScriptValue qtscript_construct_QLCDNumber_Mode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QLCDNumber_metaObject();
    int idx = meta->indexOfEnumerator("Mode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QLCDNumber::Mode>(arg));
    return context->throwError(QString::fromLatin1("Mode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLCDNumber_Mode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLCDNumber::Mode value = qscriptvalue_cast<QLCDNumber::Mode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLCDNumber_Mode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLCDNumber::Mode value = qscriptvalue_cast<QLCDNumber::Mode>(context->thisObject());
    return QScriptValue(engine, qtscript_QLCDNumber_Mode_toStringHelper(value));
}

static QScriptValue qtscript_create_QLCDNumber_Mode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLCDNumber_Mode,
        qtscript_QLCDNumber_Mode_valueOf, qtscript_QLCDNumber_Mode_toString);
    qScriptRegisterMetaType<QLCDNumber::Mode>(engine, qtscript_QLCDNumber_Mode_toScriptValue,
        qtscript_QLCDNumber_Mode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLCDNumber_Mode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLCDNumber_Mode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLCDNumber
//

static QScriptValue qtscript_QLCDNumber_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QLCDNumber* _q_self = qscriptvalue_cast<QLCDNumber*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QLCDNumber.%0(): this object is not a QLCDNumber")
            .arg(qtscript_QLCDNumber_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isNumber()) {
            double _q_arg0 = context->argument(0).toNumber();
            bool _q_result = _q_self->checkOverflow(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            bool _q_result = _q_self->checkOverflow(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QLCDNumber");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLCDNumber_throw_ambiguity_error_helper(context,
        qtscript_QLCDNumber_function_names[_id+1],
        qtscript_QLCDNumber_function_signatures[_id+1]);
}

static QScriptValue qtscript_QLCDNumber_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QLCDNumber(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QLCDNumber* _q_cpp_result = new QtScriptShell_QLCDNumber();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLCDNumber*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QLCDNumber* _q_cpp_result = new QtScriptShell_QLCDNumber(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLCDNumber*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            uint _q_arg0 = context->argument(0).toUInt32();
            QtScriptShell_QLCDNumber* _q_cpp_result = new QtScriptShell_QLCDNumber(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLCDNumber*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        uint _q_arg0 = context->argument(0).toUInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QLCDNumber* _q_cpp_result = new QtScriptShell_QLCDNumber(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLCDNumber*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLCDNumber_throw_ambiguity_error_helper(context,
        qtscript_QLCDNumber_function_names[_id],
        qtscript_QLCDNumber_function_signatures[_id]);
}

static QScriptValue qtscript_QLCDNumber_toScriptValue(QScriptEngine *engine, QLCDNumber* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QLCDNumber_fromScriptValue(const QScriptValue &value, QLCDNumber* &out)
{
    out = qobject_cast<QLCDNumber*>(value.toQObject());
}

QScriptValue qtscript_create_QLCDNumber_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QLCDNumber*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QLCDNumber*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QFrame*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLCDNumber_prototype_call, qtscript_QLCDNumber_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QLCDNumber_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QLCDNumber*>(engine, qtscript_QLCDNumber_toScriptValue, 
        qtscript_QLCDNumber_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QLCDNumber_static_call, proto, qtscript_QLCDNumber_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("SegmentStyle"),
        qtscript_create_QLCDNumber_SegmentStyle_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Mode"),
        qtscript_create_QLCDNumber_Mode_class(engine, ctor));
    return ctor;
}
