#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicsanchorlayout.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

static const char * const qtscript_QGraphicsAnchor_function_names[] = {
    "QGraphicsAnchor"
    // static
    // prototype
    , "unsetSpacing"
    , "toString"
};

static const char * const qtscript_QGraphicsAnchor_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
""
};

static const int qtscript_QGraphicsAnchor_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsAnchor_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsAnchor::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsAnchor*)

//
// QGraphicsAnchor
//

static QScriptValue qtscript_QGraphicsAnchor_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGraphicsAnchor* _q_self = qscriptvalue_cast<QGraphicsAnchor*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsAnchor.%0(): this object is not a QGraphicsAnchor")
            .arg(qtscript_QGraphicsAnchor_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->unsetSpacing();
        return context->engine()->undefinedValue();
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QGraphicsAnchor");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsAnchor_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsAnchor_function_names[_id+1],
        qtscript_QGraphicsAnchor_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsAnchor_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QGraphicsAnchor cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsAnchor_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsAnchor_function_names[_id],
        qtscript_QGraphicsAnchor_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsAnchor_toScriptValue(QScriptEngine *engine, QGraphicsAnchor* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsAnchor_fromScriptValue(const QScriptValue &value, QGraphicsAnchor* &out)
{
    out = qobject_cast<QGraphicsAnchor*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsAnchor_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsAnchor*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsAnchor*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsAnchor_prototype_call, qtscript_QGraphicsAnchor_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsAnchor_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGraphicsAnchor*>(engine, qtscript_QGraphicsAnchor_toScriptValue, 
        qtscript_QGraphicsAnchor_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsAnchor_static_call, proto, qtscript_QGraphicsAnchor_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
