#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgesture.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qpoint.h>

#include "qtscriptshell_QSwipeGesture.h"

static const char * const qtscript_QSwipeGesture_function_names[] = {
    "QSwipeGesture"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QSwipeGesture_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
""
};

static const int qtscript_QSwipeGesture_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QSwipeGesture_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSwipeGesture::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QSwipeGesture_metaObject()
{
    return &QSwipeGesture::staticMetaObject;
}

Q_DECLARE_METATYPE(QSwipeGesture*)
Q_DECLARE_METATYPE(QtScriptShell_QSwipeGesture*)
Q_DECLARE_METATYPE(QSwipeGesture::SwipeDirection)
Q_DECLARE_METATYPE(QGesture*)

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
// QSwipeGesture::SwipeDirection
//

static const QSwipeGesture::SwipeDirection qtscript_QSwipeGesture_SwipeDirection_values[] = {
    QSwipeGesture::NoDirection
    , QSwipeGesture::Left
    , QSwipeGesture::Right
    , QSwipeGesture::Up
    , QSwipeGesture::Down
};

static const char * const qtscript_QSwipeGesture_SwipeDirection_keys[] = {
    "NoDirection"
    , "Left"
    , "Right"
    , "Up"
    , "Down"
};

static QString qtscript_QSwipeGesture_SwipeDirection_toStringHelper(QSwipeGesture::SwipeDirection value)
{
    const QMetaObject *meta = qtscript_QSwipeGesture_metaObject();
    int idx = meta->indexOfEnumerator("SwipeDirection");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QSwipeGesture_SwipeDirection_toScriptValue(QScriptEngine *engine, const QSwipeGesture::SwipeDirection &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSwipeGesture"));
    return clazz.property(qtscript_QSwipeGesture_SwipeDirection_toStringHelper(value));
}

static void qtscript_QSwipeGesture_SwipeDirection_fromScriptValue(const QScriptValue &value, QSwipeGesture::SwipeDirection &out)
{
    out = qvariant_cast<QSwipeGesture::SwipeDirection>(value.toVariant());
}

static QScriptValue qtscript_construct_QSwipeGesture_SwipeDirection(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QSwipeGesture_metaObject();
    int idx = meta->indexOfEnumerator("SwipeDirection");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QSwipeGesture::SwipeDirection>(arg));
    return context->throwError(QString::fromLatin1("SwipeDirection(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSwipeGesture_SwipeDirection_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSwipeGesture::SwipeDirection value = qscriptvalue_cast<QSwipeGesture::SwipeDirection>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSwipeGesture_SwipeDirection_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSwipeGesture::SwipeDirection value = qscriptvalue_cast<QSwipeGesture::SwipeDirection>(context->thisObject());
    return QScriptValue(engine, qtscript_QSwipeGesture_SwipeDirection_toStringHelper(value));
}

static QScriptValue qtscript_create_QSwipeGesture_SwipeDirection_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSwipeGesture_SwipeDirection,
        qtscript_QSwipeGesture_SwipeDirection_valueOf, qtscript_QSwipeGesture_SwipeDirection_toString);
    qScriptRegisterMetaType<QSwipeGesture::SwipeDirection>(engine, qtscript_QSwipeGesture_SwipeDirection_toScriptValue,
        qtscript_QSwipeGesture_SwipeDirection_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSwipeGesture_SwipeDirection_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSwipeGesture_SwipeDirection_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSwipeGesture
//

static QScriptValue qtscript_QSwipeGesture_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSwipeGesture* _q_self = qscriptvalue_cast<QSwipeGesture*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSwipeGesture.%0(): this object is not a QSwipeGesture")
            .arg(qtscript_QSwipeGesture_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QSwipeGesture");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSwipeGesture_throw_ambiguity_error_helper(context,
        qtscript_QSwipeGesture_function_names[_id+1],
        qtscript_QSwipeGesture_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSwipeGesture_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSwipeGesture(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSwipeGesture* _q_cpp_result = new QtScriptShell_QSwipeGesture();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSwipeGesture*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QSwipeGesture* _q_cpp_result = new QtScriptShell_QSwipeGesture(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSwipeGesture*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSwipeGesture_throw_ambiguity_error_helper(context,
        qtscript_QSwipeGesture_function_names[_id],
        qtscript_QSwipeGesture_function_signatures[_id]);
}

static QScriptValue qtscript_QSwipeGesture_toScriptValue(QScriptEngine *engine, QSwipeGesture* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSwipeGesture_fromScriptValue(const QScriptValue &value, QSwipeGesture* &out)
{
    out = qobject_cast<QSwipeGesture*>(value.toQObject());
}

QScriptValue qtscript_create_QSwipeGesture_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSwipeGesture*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSwipeGesture*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGesture*>()));

    qScriptRegisterMetaType<QSwipeGesture*>(engine, qtscript_QSwipeGesture_toScriptValue, 
        qtscript_QSwipeGesture_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSwipeGesture_static_call, proto, qtscript_QSwipeGesture_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("SwipeDirection"),
        qtscript_create_QSwipeGesture_SwipeDirection_class(engine, ctor));
    return ctor;
}
