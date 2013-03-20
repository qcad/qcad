#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <medianode.h>
#include <QVariant>
#include <path.h>
#include <qlist.h>

#include "qtscriptshell_MediaNode.h"

static const char * const qtscript_MediaNode_function_names[] = {
    "MediaNode"
    // static
    // prototype
    , "inputPaths"
    , "isValid"
    , "outputPaths"
    , "toString"
};

static const char * const qtscript_MediaNode_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
""
};

static const int qtscript_MediaNode_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_MediaNode_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("MediaNode::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::MediaNode*)
Q_DECLARE_METATYPE(QtScriptShell_MediaNode*)
Q_DECLARE_METATYPE(Phonon::Path)
Q_DECLARE_METATYPE(QList<Phonon::Path>)

//
// MediaNode
//

static QScriptValue qtscript_MediaNode_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Phonon::MediaNode* _q_self = qscriptvalue_cast<Phonon::MediaNode*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("MediaNode.%0(): this object is not a MediaNode")
            .arg(qtscript_MediaNode_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<Phonon::Path> _q_result = _q_self->inputPaths();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QList<Phonon::Path> _q_result = _q_self->outputPaths();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("MediaNode");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_MediaNode_throw_ambiguity_error_helper(context,
        qtscript_MediaNode_function_names[_id+1],
        qtscript_MediaNode_function_signatures[_id+1]);
}

static QScriptValue qtscript_MediaNode_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("MediaNode cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_MediaNode_throw_ambiguity_error_helper(context,
        qtscript_MediaNode_function_names[_id],
        qtscript_MediaNode_function_signatures[_id]);
}

QScriptValue qtscript_create_MediaNode_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::MediaNode*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::MediaNode*)0));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_MediaNode_prototype_call, qtscript_MediaNode_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_MediaNode_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::MediaNode*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_MediaNode_static_call, proto, qtscript_MediaNode_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
