#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qundostack.h>
#include <QVariant>
#include <qundostack.h>

#include "qtscriptshell_QUndoCommand.h"

static const char * const qtscript_QUndoCommand_function_names[] = {
    "QUndoCommand"
    // static
    // prototype
    , "actionText"
    , "child"
    , "childCount"
    , "id"
    , "mergeWith"
    , "redo"
    , "setText"
    , "text"
    , "undo"
    , "toString"
};

static const char * const qtscript_QUndoCommand_function_signatures[] = {
    "QUndoCommand parent\nString text, QUndoCommand parent"
    // static
    // prototype
    , ""
    , "int index"
    , ""
    , ""
    , "QUndoCommand other"
    , ""
    , "String text"
    , ""
    , ""
""
};

static const int qtscript_QUndoCommand_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
    , 1
    , 0
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QUndoCommand_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QUndoCommand::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QUndoCommand*)
Q_DECLARE_METATYPE(QtScriptShell_QUndoCommand*)
Q_DECLARE_METATYPE(const QUndoCommand*)

//
// QUndoCommand
//

static QScriptValue qtscript_QUndoCommand_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QUndoCommand* _q_self = qscriptvalue_cast<QUndoCommand*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QUndoCommand.%0(): this object is not a QUndoCommand")
            .arg(qtscript_QUndoCommand_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->actionText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        const QUndoCommand* _q_result = const_cast<const QUndoCommand*>(_q_self->child(_q_arg0));
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->childCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->id();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        const QUndoCommand* _q_arg0 = qscriptvalue_cast<const QUndoCommand*>(context->argument(0));
        bool _q_result = _q_self->mergeWith(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->redo();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        _q_self->undo();
        return context->engine()->undefinedValue();
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("QUndoCommand");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUndoCommand_throw_ambiguity_error_helper(context,
        qtscript_QUndoCommand_function_names[_id+1],
        qtscript_QUndoCommand_function_signatures[_id+1]);
}

static QScriptValue qtscript_QUndoCommand_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QUndoCommand(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QUndoCommand* _q_cpp_result = new QtScriptShell_QUndoCommand();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QUndoCommand*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QUndoCommand*>(context->argument(0))) {
            QUndoCommand* _q_arg0 = qscriptvalue_cast<QUndoCommand*>(context->argument(0));
            QtScriptShell_QUndoCommand* _q_cpp_result = new QtScriptShell_QUndoCommand(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QUndoCommand*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QUndoCommand* _q_cpp_result = new QtScriptShell_QUndoCommand(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QUndoCommand*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QUndoCommand* _q_arg1 = qscriptvalue_cast<QUndoCommand*>(context->argument(1));
        QtScriptShell_QUndoCommand* _q_cpp_result = new QtScriptShell_QUndoCommand(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QUndoCommand*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUndoCommand_throw_ambiguity_error_helper(context,
        qtscript_QUndoCommand_function_names[_id],
        qtscript_QUndoCommand_function_signatures[_id]);
}

QScriptValue qtscript_create_QUndoCommand_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QUndoCommand*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QUndoCommand*)0));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUndoCommand_prototype_call, qtscript_QUndoCommand_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QUndoCommand_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QUndoCommand*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QUndoCommand_static_call, proto, qtscript_QUndoCommand_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
