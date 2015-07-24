#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgraphicseffect.h>
#include <QVariant>
#include <qbrush.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qgraphicseffect.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>

#include "qtscriptshell_QGraphicsOpacityEffect.h"

static const char * const qtscript_QGraphicsOpacityEffect_function_names[] = {
    "QGraphicsOpacityEffect"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QGraphicsOpacityEffect_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
""
};

static const int qtscript_QGraphicsOpacityEffect_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QGraphicsOpacityEffect_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsOpacityEffect::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsOpacityEffect*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsOpacityEffect*)
Q_DECLARE_METATYPE(QGraphicsEffect*)

//
// QGraphicsOpacityEffect
//

static QScriptValue qtscript_QGraphicsOpacityEffect_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGraphicsOpacityEffect* _q_self = qscriptvalue_cast<QGraphicsOpacityEffect*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsOpacityEffect.%0(): this object is not a QGraphicsOpacityEffect")
            .arg(qtscript_QGraphicsOpacityEffect_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QGraphicsOpacityEffect");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsOpacityEffect_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsOpacityEffect_function_names[_id+1],
        qtscript_QGraphicsOpacityEffect_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsOpacityEffect_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsOpacityEffect(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsOpacityEffect* _q_cpp_result = new QtScriptShell_QGraphicsOpacityEffect();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsOpacityEffect*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QGraphicsOpacityEffect* _q_cpp_result = new QtScriptShell_QGraphicsOpacityEffect(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsOpacityEffect*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsOpacityEffect_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsOpacityEffect_function_names[_id],
        qtscript_QGraphicsOpacityEffect_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsOpacityEffect_toScriptValue(QScriptEngine *engine, QGraphicsOpacityEffect* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsOpacityEffect_fromScriptValue(const QScriptValue &value, QGraphicsOpacityEffect* &out)
{
    out = qobject_cast<QGraphicsOpacityEffect*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsOpacityEffect_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsOpacityEffect*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsOpacityEffect*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsEffect*>()));

    qScriptRegisterMetaType<QGraphicsOpacityEffect*>(engine, qtscript_QGraphicsOpacityEffect_toScriptValue, 
        qtscript_QGraphicsOpacityEffect_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsOpacityEffect_static_call, proto, qtscript_QGraphicsOpacityEffect_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
