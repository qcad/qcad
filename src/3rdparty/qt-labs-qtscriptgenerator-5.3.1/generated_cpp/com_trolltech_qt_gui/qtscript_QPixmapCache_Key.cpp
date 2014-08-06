#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qpixmapcache.h>
#include <QVariant>
#include <qpixmapcache.h>

static const char * const qtscript_QPixmapCache_Key_function_names[] = {
    "QPixmapCache_Key"
    // static
    // prototype
    , "operator_assign"
    , "equals"
    , "toString"
};

static const char * const qtscript_QPixmapCache_Key_function_signatures[] = {
    "\nQPixmapCache_Key other"
    // static
    // prototype
    , "QPixmapCache_Key other"
    , "QPixmapCache_Key key"
""
};

static const int qtscript_QPixmapCache_Key_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QPixmapCache_Key_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPixmapCache_Key::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPixmapCache::Key)
Q_DECLARE_METATYPE(QPixmapCache::Key*)

//
// QPixmapCache_Key
//

static QScriptValue qtscript_QPixmapCache_Key_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPixmapCache::Key* _q_self = qscriptvalue_cast<QPixmapCache::Key*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPixmapCache_Key.%0(): this object is not a QPixmapCache_Key")
            .arg(qtscript_QPixmapCache_Key_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QPixmapCache::Key _q_arg0 = qscriptvalue_cast<QPixmapCache::Key>(context->argument(0));
        QPixmapCache::Key& _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QPixmapCache::Key _q_arg0 = qscriptvalue_cast<QPixmapCache::Key>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QPixmapCache_Key");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPixmapCache_Key_throw_ambiguity_error_helper(context,
        qtscript_QPixmapCache_Key_function_names[_id+1],
        qtscript_QPixmapCache_Key_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPixmapCache_Key_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPixmapCache_Key(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QPixmapCache::Key _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QPixmapCache::Key _q_arg0 = qscriptvalue_cast<QPixmapCache::Key>(context->argument(0));
        QPixmapCache::Key _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPixmapCache_Key_throw_ambiguity_error_helper(context,
        qtscript_QPixmapCache_Key_function_names[_id],
        qtscript_QPixmapCache_Key_function_signatures[_id]);
}

QScriptValue qtscript_create_QPixmapCache_Key_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPixmapCache::Key*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPixmapCache::Key*)0));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPixmapCache_Key_prototype_call, qtscript_QPixmapCache_Key_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPixmapCache_Key_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPixmapCache::Key>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QPixmapCache::Key*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPixmapCache_Key_static_call, proto, qtscript_QPixmapCache_Key_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
