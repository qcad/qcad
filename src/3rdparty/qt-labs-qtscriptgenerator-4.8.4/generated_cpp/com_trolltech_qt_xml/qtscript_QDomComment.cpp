#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qdom.h>
#include <QVariant>
#include <qdom.h>
#include <qtextstream.h>

static const char * const qtscript_QDomComment_function_names[] = {
    "QDomComment"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QDomComment_function_signatures[] = {
    "\nQDomComment x"
    // static
    // prototype
""
};

static const int qtscript_QDomComment_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QDomComment_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDomComment::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDomComment)
Q_DECLARE_METATYPE(QDomComment*)
Q_DECLARE_METATYPE(QDomCharacterData*)

//
// QDomComment
//

static QScriptValue qtscript_QDomComment_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QDomComment* _q_self = qscriptvalue_cast<QDomComment*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDomComment.%0(): this object is not a QDomComment")
            .arg(qtscript_QDomComment_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QDomComment");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomComment_throw_ambiguity_error_helper(context,
        qtscript_QDomComment_function_names[_id+1],
        qtscript_QDomComment_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDomComment_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDomComment(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QDomComment _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QDomComment _q_arg0 = qscriptvalue_cast<QDomComment>(context->argument(0));
        QDomComment _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDomComment_throw_ambiguity_error_helper(context,
        qtscript_QDomComment_function_names[_id],
        qtscript_QDomComment_function_signatures[_id]);
}

QScriptValue qtscript_create_QDomComment_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDomComment*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDomComment*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDomCharacterData*>()));

    engine->setDefaultPrototype(qMetaTypeId<QDomComment>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QDomComment*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDomComment_static_call, proto, qtscript_QDomComment_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
