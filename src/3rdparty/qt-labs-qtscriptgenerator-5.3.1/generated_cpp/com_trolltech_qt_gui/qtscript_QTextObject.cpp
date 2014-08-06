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

#include "qtscriptshell_QTextObject.h"

static const char * const qtscript_QTextObject_function_names[] = {
    "QTextObject"
    // static
    // prototype
    , "document"
    , "format"
    , "formatIndex"
    , "objectIndex"
    , "toString"
};

static const char * const qtscript_QTextObject_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QTextObject_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTextObject_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextObject::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextObject*)
Q_DECLARE_METATYPE(QtScriptShell_QTextObject*)
Q_DECLARE_METATYPE(QTextDocument*)

//
// QTextObject
//

static QScriptValue qtscript_QTextObject_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTextObject* _q_self = qscriptvalue_cast<QTextObject*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextObject.%0(): this object is not a QTextObject")
            .arg(qtscript_QTextObject_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QTextDocument* _q_result = _q_self->document();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QTextFormat _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->formatIndex();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->objectIndex();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QTextObject");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextObject_throw_ambiguity_error_helper(context,
        qtscript_QTextObject_function_names[_id+1],
        qtscript_QTextObject_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextObject_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QTextObject cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextObject_throw_ambiguity_error_helper(context,
        qtscript_QTextObject_function_names[_id],
        qtscript_QTextObject_function_signatures[_id]);
}

static QScriptValue qtscript_QTextObject_toScriptValue(QScriptEngine *engine, QTextObject* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTextObject_fromScriptValue(const QScriptValue &value, QTextObject* &out)
{
    out = qobject_cast<QTextObject*>(value.toQObject());
}

QScriptValue qtscript_create_QTextObject_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextObject*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextObject*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextObject_prototype_call, qtscript_QTextObject_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextObject_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTextObject*>(engine, qtscript_QTextObject_toScriptValue, 
        qtscript_QTextObject_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextObject_static_call, proto, qtscript_QTextObject_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
