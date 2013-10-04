#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qvariantanimation.h>
#include <QVariant>
#include <qanimationgroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qeasingcurve.h>
#include <qlist.h>
#include <qobject.h>
#include <qpair.h>
#include <qvariantanimation.h>
#include <qvector.h>

#include "qtscriptshell_QVariantAnimation.h"

static const char * const qtscript_QVariantAnimation_function_names[] = {
    "QVariantAnimation"
    // static
    // prototype
    , "keyValueAt"
    , "keyValues"
    , "setKeyValueAt"
    , "setKeyValues"
    , "toString"
};

static const char * const qtscript_QVariantAnimation_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "qreal step"
    , ""
    , "qreal step, Object value"
    , "List values"
""
};

static const int qtscript_QVariantAnimation_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QVariantAnimation_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QVariantAnimation::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QVariantAnimation*)
Q_DECLARE_METATYPE(QtScriptShell_QVariantAnimation*)
template <> \
struct QMetaTypeId< QPair<qreal,QVariant> > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QPair<qreal,QVariant> >("QPair<qreal,QVariant>"); \
        return metatype_id; \
    } \
};
template <> \
struct QMetaTypeId< QVector<QPair<qreal,QVariant> > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id) \
            metatype_id = qRegisterMetaType< QVector<QPair<qreal,QVariant> > >("QVector<QPair<qreal,QVariant> >"); \
        return metatype_id; \
    } \
};
Q_DECLARE_METATYPE(QAbstractAnimation*)

//
// QVariantAnimation
//

static QScriptValue qtscript_QVariantAnimation_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QVariantAnimation* _q_self = qscriptvalue_cast<QVariantAnimation*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QVariantAnimation.%0(): this object is not a QVariantAnimation")
            .arg(qtscript_QVariantAnimation_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QVariant _q_result = _q_self->keyValueAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QVector<QPair<qreal,QVariant> > _q_result = _q_self->keyValues();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setKeyValueAt(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QVector<QPair<qreal,QVariant> > _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setKeyValues(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QVariantAnimation");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QVariantAnimation_throw_ambiguity_error_helper(context,
        qtscript_QVariantAnimation_function_names[_id+1],
        qtscript_QVariantAnimation_function_signatures[_id+1]);
}

static QScriptValue qtscript_QVariantAnimation_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QVariantAnimation(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QVariantAnimation* _q_cpp_result = new QtScriptShell_QVariantAnimation();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QVariantAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QVariantAnimation* _q_cpp_result = new QtScriptShell_QVariantAnimation(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QVariantAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QVariantAnimation_throw_ambiguity_error_helper(context,
        qtscript_QVariantAnimation_function_names[_id],
        qtscript_QVariantAnimation_function_signatures[_id]);
}

static QScriptValue qtscript_QVariantAnimation_toScriptValue(QScriptEngine *engine, QVariantAnimation* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QVariantAnimation_fromScriptValue(const QScriptValue &value, QVariantAnimation* &out)
{
    out = qobject_cast<QVariantAnimation*>(value.toQObject());
}

QScriptValue qtscript_create_QVariantAnimation_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QVariantAnimation*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QVariantAnimation*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractAnimation*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QVariantAnimation_prototype_call, qtscript_QVariantAnimation_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QVariantAnimation_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QVariantAnimation*>(engine, qtscript_QVariantAnimation_toScriptValue, 
        qtscript_QVariantAnimation_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QVariantAnimation_static_call, proto, qtscript_QVariantAnimation_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
