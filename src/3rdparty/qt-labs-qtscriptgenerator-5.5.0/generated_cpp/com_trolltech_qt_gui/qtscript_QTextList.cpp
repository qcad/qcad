#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtextlist.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qtextdocument.h>
#include <qtextformat.h>
#include <qtextlist.h>
#include <qtextobject.h>

#include "qtscriptshell_QTextList.h"

static const char * const qtscript_QTextList_function_names[] = {
    "QTextList"
    // static
    // prototype
    , "add"
    , "count"
    , "item"
    , "itemNumber"
    , "itemText"
    , "remove"
    , "removeItem"
    , "setFormat"
    , "textListFormat"
    , "toString"
};

static const char * const qtscript_QTextList_function_signatures[] = {
    "QTextDocument doc"
    // static
    // prototype
    , "QTextBlock block"
    , ""
    , "int i"
    , "QTextBlock arg__1"
    , "QTextBlock arg__1"
    , "QTextBlock arg__1"
    , "int i"
    , "QTextListFormat format"
    , ""
""
};

static const int qtscript_QTextList_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QTextList_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextList::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextList*)
Q_DECLARE_METATYPE(QtScriptShell_QTextList*)
Q_DECLARE_METATYPE(QTextBlock)
Q_DECLARE_METATYPE(QTextListFormat)
Q_DECLARE_METATYPE(QTextDocument*)
Q_DECLARE_METATYPE(QTextBlockGroup*)

//
// QTextList
//

static QScriptValue qtscript_QTextList_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTextList* _q_self = qscriptvalue_cast<QTextList*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextList.%0(): this object is not a QTextList")
            .arg(qtscript_QTextList_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QTextBlock _q_arg0 = qscriptvalue_cast<QTextBlock>(context->argument(0));
        _q_self->add(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTextBlock _q_result = _q_self->item(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QTextBlock _q_arg0 = qscriptvalue_cast<QTextBlock>(context->argument(0));
        int _q_result = _q_self->itemNumber(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QTextBlock _q_arg0 = qscriptvalue_cast<QTextBlock>(context->argument(0));
        QString _q_result = _q_self->itemText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QTextBlock _q_arg0 = qscriptvalue_cast<QTextBlock>(context->argument(0));
        _q_self->remove(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->removeItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QTextListFormat _q_arg0 = qscriptvalue_cast<QTextListFormat>(context->argument(0));
        _q_self->setFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QTextListFormat _q_result = _q_self->format();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("QTextList");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextList_throw_ambiguity_error_helper(context,
        qtscript_QTextList_function_names[_id+1],
        qtscript_QTextList_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextList_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextList(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QTextDocument* _q_arg0 = qscriptvalue_cast<QTextDocument*>(context->argument(0));
        QtScriptShell_QTextList* _q_cpp_result = new QtScriptShell_QTextList(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTextList*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextList_throw_ambiguity_error_helper(context,
        qtscript_QTextList_function_names[_id],
        qtscript_QTextList_function_signatures[_id]);
}

static QScriptValue qtscript_QTextList_toScriptValue(QScriptEngine *engine, QTextList* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTextList_fromScriptValue(const QScriptValue &value, QTextList* &out)
{
    out = qobject_cast<QTextList*>(value.toQObject());
}

QScriptValue qtscript_create_QTextList_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextList*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextList*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTextBlockGroup*>()));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextList_prototype_call, qtscript_QTextList_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextList_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTextList*>(engine, qtscript_QTextList_toScriptValue, 
        qtscript_QTextList_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextList_static_call, proto, qtscript_QTextList_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
