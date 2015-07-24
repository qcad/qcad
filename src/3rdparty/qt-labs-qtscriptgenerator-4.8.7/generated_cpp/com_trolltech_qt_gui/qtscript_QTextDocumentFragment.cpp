#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtextdocumentfragment.h>
#include <QVariant>
#include <qbytearray.h>
#include <qtextcursor.h>
#include <qtextdocument.h>
#include <qtextdocumentfragment.h>

static const char * const qtscript_QTextDocumentFragment_function_names[] = {
    "QTextDocumentFragment"
    // static
    , "fromHtml"
    , "fromPlainText"
    // prototype
    , "isEmpty"
    , "toHtml"
    , "toPlainText"
    , "toString"
};

static const char * const qtscript_QTextDocumentFragment_function_signatures[] = {
    "\nQTextCursor range\nQTextDocument document\nQTextDocumentFragment rhs"
    // static
    , "String html\nString html, QTextDocument resourceProvider"
    , "String plainText"
    // prototype
    , ""
    , "\nQByteArray encoding"
    , ""
""
};

static const int qtscript_QTextDocumentFragment_function_lengths[] = {
    1
    // static
    , 2
    , 1
    // prototype
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QTextDocumentFragment_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextDocumentFragment::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextDocumentFragment)
Q_DECLARE_METATYPE(QTextDocumentFragment*)
Q_DECLARE_METATYPE(QTextDocument*)
Q_DECLARE_METATYPE(QTextCursor)

//
// QTextDocumentFragment
//

static QScriptValue qtscript_QTextDocumentFragment_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTextDocumentFragment* _q_self = qscriptvalue_cast<QTextDocumentFragment*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextDocumentFragment.%0(): this object is not a QTextDocumentFragment")
            .arg(qtscript_QTextDocumentFragment_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toHtml();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QString _q_result = _q_self->toHtml(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toPlainText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QTextDocumentFragment");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextDocumentFragment_throw_ambiguity_error_helper(context,
        qtscript_QTextDocumentFragment_function_names[_id+3],
        qtscript_QTextDocumentFragment_function_signatures[_id+3]);
}

static QScriptValue qtscript_QTextDocumentFragment_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextDocumentFragment(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTextDocumentFragment _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QTextCursor>() == context->argument(0).toVariant().userType())) {
            QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
            QTextDocumentFragment _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (qscriptvalue_cast<QTextDocument*>(context->argument(0))) {
            QTextDocument* _q_arg0 = qscriptvalue_cast<QTextDocument*>(context->argument(0));
            QTextDocumentFragment _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QTextDocumentFragment>() == context->argument(0).toVariant().userType())) {
            QTextDocumentFragment _q_arg0 = qscriptvalue_cast<QTextDocumentFragment>(context->argument(0));
            QTextDocumentFragment _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QTextDocumentFragment _q_result = QTextDocumentFragment::fromHtml(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QTextDocument* _q_arg1 = qscriptvalue_cast<QTextDocument*>(context->argument(1));
        QTextDocumentFragment _q_result = QTextDocumentFragment::fromHtml(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QTextDocumentFragment _q_result = QTextDocumentFragment::fromPlainText(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextDocumentFragment_throw_ambiguity_error_helper(context,
        qtscript_QTextDocumentFragment_function_names[_id],
        qtscript_QTextDocumentFragment_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextDocumentFragment_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextDocumentFragment*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextDocumentFragment*)0));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextDocumentFragment_prototype_call, qtscript_QTextDocumentFragment_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextDocumentFragment_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextDocumentFragment>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextDocumentFragment*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextDocumentFragment_static_call, proto, qtscript_QTextDocumentFragment_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextDocumentFragment_static_call,
            qtscript_QTextDocumentFragment_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QTextDocumentFragment_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
