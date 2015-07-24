#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtextobject.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qtextdocument.h>
#include <qtextformat.h>
#include <qtextobject.h>

#include "qtscriptshell_QTextBlockGroup.h"

static const char * const qtscript_QTextBlockGroup_function_names[] = {
    "QTextBlockGroup"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QTextBlockGroup_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_QTextBlockGroup_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QTextBlockGroup_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextBlockGroup::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextBlockGroup*)
Q_DECLARE_METATYPE(QtScriptShell_QTextBlockGroup*)
Q_DECLARE_METATYPE(QTextObject*)

//
// QTextBlockGroup
//

static QScriptValue qtscript_QTextBlockGroup_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTextBlockGroup* _q_self = qscriptvalue_cast<QTextBlockGroup*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextBlockGroup.%0(): this object is not a QTextBlockGroup")
            .arg(qtscript_QTextBlockGroup_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QTextBlockGroup");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextBlockGroup_throw_ambiguity_error_helper(context,
        qtscript_QTextBlockGroup_function_names[_id+1],
        qtscript_QTextBlockGroup_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextBlockGroup_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QTextBlockGroup cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextBlockGroup_throw_ambiguity_error_helper(context,
        qtscript_QTextBlockGroup_function_names[_id],
        qtscript_QTextBlockGroup_function_signatures[_id]);
}

static QScriptValue qtscript_QTextBlockGroup_toScriptValue(QScriptEngine *engine, QTextBlockGroup* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTextBlockGroup_fromScriptValue(const QScriptValue &value, QTextBlockGroup* &out)
{
    out = qobject_cast<QTextBlockGroup*>(value.toQObject());
}

QScriptValue qtscript_create_QTextBlockGroup_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextBlockGroup*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextBlockGroup*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTextObject*>()));

    qScriptRegisterMetaType<QTextBlockGroup*>(engine, qtscript_QTextBlockGroup_toScriptValue, 
        qtscript_QTextBlockGroup_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextBlockGroup_static_call, proto, qtscript_QTextBlockGroup_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
