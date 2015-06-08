#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtextdocumentwriter.h>
#include <QVariant>
#include <qbytearray.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qtextcodec.h>
#include <qtextdocument.h>
#include <qtextdocumentfragment.h>
#include <qtextdocumentwriter.h>

static const char * const qtscript_QTextDocumentWriter_function_names[] = {
    "QTextDocumentWriter"
    // static
    , "supportedDocumentFormats"
    // prototype
    , "codec"
    , "device"
    , "fileName"
    , "format"
    , "setCodec"
    , "setDevice"
    , "setFileName"
    , "setFormat"
    , "write"
    , "toString"
};

static const char * const qtscript_QTextDocumentWriter_function_signatures[] = {
    "\nQIODevice device, QByteArray format\nString fileName, QByteArray format"
    // static
    , ""
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "QTextCodec codec"
    , "QIODevice device"
    , "String fileName"
    , "QByteArray format"
    , "QTextDocument document\nQTextDocumentFragment fragment"
""
};

static const int qtscript_QTextDocumentWriter_function_lengths[] = {
    2
    // static
    , 0
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QTextDocumentWriter_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextDocumentWriter::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextDocumentWriter*)
Q_DECLARE_METATYPE(QTextCodec*)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(const QTextDocument*)
Q_DECLARE_METATYPE(QTextDocumentFragment)
Q_DECLARE_METATYPE(QList<QByteArray >)

//
// QTextDocumentWriter
//

static QScriptValue qtscript_QTextDocumentWriter_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTextDocumentWriter* _q_self = qscriptvalue_cast<QTextDocumentWriter*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextDocumentWriter.%0(): this object is not a QTextDocumentWriter")
            .arg(qtscript_QTextDocumentWriter_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QTextCodec* _q_result = _q_self->codec();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QIODevice* _q_result = _q_self->device();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QTextCodec* _q_arg0 = qscriptvalue_cast<QTextCodec*>(context->argument(0));
        _q_self->setCodec(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        _q_self->setDevice(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFileName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<const QTextDocument*>(context->argument(0))) {
            const QTextDocument* _q_arg0 = qscriptvalue_cast<const QTextDocument*>(context->argument(0));
            bool _q_result = _q_self->write(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTextDocumentFragment>() == context->argument(0).toVariant().userType())) {
            QTextDocumentFragment _q_arg0 = qscriptvalue_cast<QTextDocumentFragment>(context->argument(0));
            bool _q_result = _q_self->write(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("QTextDocumentWriter");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextDocumentWriter_throw_ambiguity_error_helper(context,
        qtscript_QTextDocumentWriter_function_names[_id+2],
        qtscript_QTextDocumentWriter_function_signatures[_id+2]);
}

static QScriptValue qtscript_QTextDocumentWriter_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextDocumentWriter(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTextDocumentWriter* _q_cpp_result = new QTextDocumentWriter();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QTextDocumentWriter* _q_cpp_result = new QTextDocumentWriter(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QTextDocumentWriter* _q_cpp_result = new QTextDocumentWriter(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            QTextDocumentWriter* _q_cpp_result = new QTextDocumentWriter(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<QByteArray > _q_result = QTextDocumentWriter::supportedDocumentFormats();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextDocumentWriter_throw_ambiguity_error_helper(context,
        qtscript_QTextDocumentWriter_function_names[_id],
        qtscript_QTextDocumentWriter_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextDocumentWriter_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextDocumentWriter*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextDocumentWriter*)0));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextDocumentWriter_prototype_call, qtscript_QTextDocumentWriter_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextDocumentWriter_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextDocumentWriter*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextDocumentWriter_static_call, proto, qtscript_QTextDocumentWriter_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextDocumentWriter_static_call,
            qtscript_QTextDocumentWriter_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QTextDocumentWriter_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
