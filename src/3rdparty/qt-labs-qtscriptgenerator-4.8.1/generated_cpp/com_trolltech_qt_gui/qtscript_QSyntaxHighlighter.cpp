#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsyntaxhighlighter.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qfont.h>
#include <qlist.h>
#include <qobject.h>
#include <qsyntaxhighlighter.h>
#include <qtextdocument.h>
#include <qtextedit.h>
#include <qtextformat.h>
#include <qtextobject.h>

#include "qtscriptshell_QSyntaxHighlighter.h"

static const char * const qtscript_QSyntaxHighlighter_function_names[] = {
    "QSyntaxHighlighter"
    // static
    // prototype
    , "document"
    , "setDocument"
    , "toString"
};

static const char * const qtscript_QSyntaxHighlighter_function_signatures[] = {
    "QObject parent\nQTextDocument parent\nQTextEdit parent"
    // static
    // prototype
    , ""
    , "QTextDocument doc"
""
};

static const int qtscript_QSyntaxHighlighter_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QSyntaxHighlighter_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSyntaxHighlighter::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSyntaxHighlighter*)
Q_DECLARE_METATYPE(QtScriptShell_QSyntaxHighlighter*)
Q_DECLARE_METATYPE(QTextDocument*)
Q_DECLARE_METATYPE(QTextEdit*)

//
// QSyntaxHighlighter
//

static QScriptValue qtscript_QSyntaxHighlighter_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSyntaxHighlighter* _q_self = qscriptvalue_cast<QSyntaxHighlighter*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSyntaxHighlighter.%0(): this object is not a QSyntaxHighlighter")
            .arg(qtscript_QSyntaxHighlighter_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QTextDocument* _q_result = _q_self->document();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QTextDocument* _q_arg0 = qscriptvalue_cast<QTextDocument*>(context->argument(0));
        _q_self->setDocument(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QSyntaxHighlighter");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSyntaxHighlighter_throw_ambiguity_error_helper(context,
        qtscript_QSyntaxHighlighter_function_names[_id+1],
        qtscript_QSyntaxHighlighter_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSyntaxHighlighter_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSyntaxHighlighter(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QSyntaxHighlighter* _q_cpp_result = new QtScriptShell_QSyntaxHighlighter(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSyntaxHighlighter*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QTextDocument*>(context->argument(0))) {
            QTextDocument* _q_arg0 = qscriptvalue_cast<QTextDocument*>(context->argument(0));
            QtScriptShell_QSyntaxHighlighter* _q_cpp_result = new QtScriptShell_QSyntaxHighlighter(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSyntaxHighlighter*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QTextEdit*>(context->argument(0))) {
            QTextEdit* _q_arg0 = qscriptvalue_cast<QTextEdit*>(context->argument(0));
            QtScriptShell_QSyntaxHighlighter* _q_cpp_result = new QtScriptShell_QSyntaxHighlighter(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSyntaxHighlighter*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSyntaxHighlighter_throw_ambiguity_error_helper(context,
        qtscript_QSyntaxHighlighter_function_names[_id],
        qtscript_QSyntaxHighlighter_function_signatures[_id]);
}

static QScriptValue qtscript_QSyntaxHighlighter_toScriptValue(QScriptEngine *engine, QSyntaxHighlighter* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSyntaxHighlighter_fromScriptValue(const QScriptValue &value, QSyntaxHighlighter* &out)
{
    out = qobject_cast<QSyntaxHighlighter*>(value.toQObject());
}

QScriptValue qtscript_create_QSyntaxHighlighter_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSyntaxHighlighter*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSyntaxHighlighter*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSyntaxHighlighter_prototype_call, qtscript_QSyntaxHighlighter_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSyntaxHighlighter_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSyntaxHighlighter*>(engine, qtscript_QSyntaxHighlighter_toScriptValue, 
        qtscript_QSyntaxHighlighter_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSyntaxHighlighter_static_call, proto, qtscript_QSyntaxHighlighter_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
