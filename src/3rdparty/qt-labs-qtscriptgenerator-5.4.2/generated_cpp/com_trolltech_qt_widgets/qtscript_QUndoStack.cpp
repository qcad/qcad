#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qundostack.h>
#include <QVariant>
#include <qaction.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qundostack.h>

#include "qtscriptshell_QUndoStack.h"

static const char * const qtscript_QUndoStack_function_names[] = {
    "QUndoStack"
    // static
    // prototype
    , "beginMacro"
    , "canRedo"
    , "canUndo"
    , "cleanIndex"
    , "clear"
    , "command"
    , "count"
    , "createRedoAction"
    , "createUndoAction"
    , "endMacro"
    , "index"
    , "isClean"
    , "push"
    , "redoText"
    , "text"
    , "undoText"
    , "toString"
};

static const char * const qtscript_QUndoStack_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "String text"
    , ""
    , ""
    , ""
    , ""
    , "int index"
    , ""
    , "QObject parent, String prefix"
    , "QObject parent, String prefix"
    , ""
    , ""
    , ""
    , "QUndoCommand cmd"
    , ""
    , "int idx"
    , ""
""
};

static const int qtscript_QUndoStack_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 2
    , 2
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QUndoStack_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QUndoStack::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QUndoStack*)
Q_DECLARE_METATYPE(QtScriptShell_QUndoStack*)
Q_DECLARE_METATYPE(const QUndoCommand*)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QUndoCommand*)

//
// QUndoStack
//

static QScriptValue qtscript_QUndoStack_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 16;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QUndoStack* _q_self = qscriptvalue_cast<QUndoStack*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QUndoStack.%0(): this object is not a QUndoStack")
            .arg(qtscript_QUndoStack_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->beginMacro(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->canRedo();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->canUndo();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->cleanIndex();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        const QUndoCommand* _q_result = const_cast<const QUndoCommand*>(_q_self->command(_q_arg0));
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QAction* _q_result = _q_self->createRedoAction(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QString _q_arg1 = context->argument(1).toString();
        QAction* _q_result = _q_self->createRedoAction(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QAction* _q_result = _q_self->createUndoAction(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QString _q_arg1 = context->argument(1).toString();
        QAction* _q_result = _q_self->createUndoAction(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        _q_self->endMacro();
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->index();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isClean();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QUndoCommand* _q_arg0 = qscriptvalue_cast<QUndoCommand*>(context->argument(0));
        _q_self->push(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->redoText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->text(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->undoText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16: {
    QString result = QString::fromLatin1("QUndoStack");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUndoStack_throw_ambiguity_error_helper(context,
        qtscript_QUndoStack_function_names[_id+1],
        qtscript_QUndoStack_function_signatures[_id+1]);
}

static QScriptValue qtscript_QUndoStack_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QUndoStack(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QUndoStack* _q_cpp_result = new QtScriptShell_QUndoStack();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QUndoStack*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QUndoStack* _q_cpp_result = new QtScriptShell_QUndoStack(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QUndoStack*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUndoStack_throw_ambiguity_error_helper(context,
        qtscript_QUndoStack_function_names[_id],
        qtscript_QUndoStack_function_signatures[_id]);
}

static QScriptValue qtscript_QUndoStack_toScriptValue(QScriptEngine *engine, QUndoStack* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QUndoStack_fromScriptValue(const QScriptValue &value, QUndoStack* &out)
{
    out = qobject_cast<QUndoStack*>(value.toQObject());
}

QScriptValue qtscript_create_QUndoStack_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QUndoStack*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QUndoStack*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 17; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUndoStack_prototype_call, qtscript_QUndoStack_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QUndoStack_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QUndoStack*>(engine, qtscript_QUndoStack_toScriptValue, 
        qtscript_QUndoStack_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QUndoStack_static_call, proto, qtscript_QUndoStack_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
