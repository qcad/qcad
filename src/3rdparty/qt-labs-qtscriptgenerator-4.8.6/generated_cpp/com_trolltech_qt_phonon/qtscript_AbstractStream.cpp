#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <streaminterface.h>
#include <QVariant>
#include <mediasource.h>
#include <qbytearray.h>

#include "qtscriptshell_AbstractStream.h"

static const char * const qtscript_AbstractStream_function_names[] = {
    "AbstractStream"
    // static
    // prototype
    , "connectToSource"
    , "endOfData"
    , "enoughData"
    , "needData"
    , "reset"
    , "seekStream"
    , "setStreamSeekable"
    , "setStreamSize"
    , "writeData"
    , "toString"
};

static const char * const qtscript_AbstractStream_function_signatures[] = {
    ""
    // static
    // prototype
    , "MediaSource mediaSource"
    , ""
    , ""
    , ""
    , ""
    , "qint64 seekTo"
    , "bool s"
    , "qint64 newSize"
    , "QByteArray data"
""
};

static const int qtscript_AbstractStream_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_AbstractStream_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("AbstractStream::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::StreamInterface*)
Q_DECLARE_METATYPE(QtScriptShell_AbstractStream*)
Q_DECLARE_METATYPE(Phonon::MediaSource)

//
// AbstractStream
//

static QScriptValue qtscript_AbstractStream_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 9;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Phonon::StreamInterface* _q_self = qscriptvalue_cast<Phonon::StreamInterface*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("AbstractStream.%0(): this object is not a AbstractStream")
            .arg(qtscript_AbstractStream_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        Phonon::MediaSource _q_arg0 = qscriptvalue_cast<Phonon::MediaSource>(context->argument(0));
        _q_self->connectToSource(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->endOfData();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->enoughData();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->needData();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        _q_self->reset();
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->seekStream(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setStreamSeekable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->setStreamSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->writeData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("AbstractStream");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractStream_throw_ambiguity_error_helper(context,
        qtscript_AbstractStream_function_names[_id+1],
        qtscript_AbstractStream_function_signatures[_id+1]);
}

static QScriptValue qtscript_AbstractStream_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("AbstractStream cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractStream_throw_ambiguity_error_helper(context,
        qtscript_AbstractStream_function_names[_id],
        qtscript_AbstractStream_function_signatures[_id]);
}

QScriptValue qtscript_create_AbstractStream_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::StreamInterface*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::StreamInterface*)0));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_AbstractStream_prototype_call, qtscript_AbstractStream_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_AbstractStream_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::StreamInterface*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_AbstractStream_static_call, proto, qtscript_AbstractStream_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
