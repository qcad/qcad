#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qundogroup.h>
#include <QVariant>
#include <qaction.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qundogroup.h>
#include <qundostack.h>

#include "qtscriptshell_QUndoGroup.h"

static const char * const qtscript_QUndoGroup_function_names[] = {
    "QUndoGroup"
    // static
    // prototype
    , "activeStack"
    , "addStack"
    , "canRedo"
    , "canUndo"
    , "createRedoAction"
    , "createUndoAction"
    , "isClean"
    , "redoText"
    , "removeStack"
    , "stacks"
    , "undoText"
    , "toString"
};

static const char * const qtscript_QUndoGroup_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , "QUndoStack stack"
    , ""
    , ""
    , "QObject parent, String prefix"
    , "QObject parent, String prefix"
    , ""
    , ""
    , "QUndoStack stack"
    , ""
    , ""
""
};

static const int qtscript_QUndoGroup_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
    , 2
    , 2
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QUndoGroup_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QUndoGroup::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QUndoGroup*)
Q_DECLARE_METATYPE(QtScriptShell_QUndoGroup*)
Q_DECLARE_METATYPE(QUndoStack*)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QList<QUndoStack*>)

//
// QUndoGroup
//

static QScriptValue qtscript_QUndoGroup_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 11;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QUndoGroup* _q_self = qscriptvalue_cast<QUndoGroup*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QUndoGroup.%0(): this object is not a QUndoGroup")
            .arg(qtscript_QUndoGroup_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QUndoStack* _q_result = _q_self->activeStack();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QUndoStack* _q_arg0 = qscriptvalue_cast<QUndoStack*>(context->argument(0));
        _q_self->addStack(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->canRedo();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->canUndo();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
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

    case 5:
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

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isClean();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->redoText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QUndoStack* _q_arg0 = qscriptvalue_cast<QUndoStack*>(context->argument(0));
        _q_self->removeStack(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QList<QUndoStack*> _q_result = _q_self->stacks();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->undoText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11: {
    QString result = QString::fromLatin1("QUndoGroup");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUndoGroup_throw_ambiguity_error_helper(context,
        qtscript_QUndoGroup_function_names[_id+1],
        qtscript_QUndoGroup_function_signatures[_id+1]);
}

static QScriptValue qtscript_QUndoGroup_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QUndoGroup(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QUndoGroup* _q_cpp_result = new QtScriptShell_QUndoGroup();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QUndoGroup*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QUndoGroup* _q_cpp_result = new QtScriptShell_QUndoGroup(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QUndoGroup*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUndoGroup_throw_ambiguity_error_helper(context,
        qtscript_QUndoGroup_function_names[_id],
        qtscript_QUndoGroup_function_signatures[_id]);
}

static QScriptValue qtscript_QUndoGroup_toScriptValue(QScriptEngine *engine, QUndoGroup* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QUndoGroup_fromScriptValue(const QScriptValue &value, QUndoGroup* &out)
{
    out = qobject_cast<QUndoGroup*>(value.toQObject());
}

QScriptValue qtscript_create_QUndoGroup_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QUndoGroup*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QUndoGroup*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 12; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUndoGroup_prototype_call, qtscript_QUndoGroup_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QUndoGroup_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QUndoGroup*>(engine, qtscript_QUndoGroup_toScriptValue, 
        qtscript_QUndoGroup_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QUndoGroup_static_call, proto, qtscript_QUndoGroup_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
