#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qbuttongroup.h>
#include <QVariant>
#include <qabstractbutton.h>
#include <qbuttongroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QButtonGroup.h"

static const char * const qtscript_QButtonGroup_function_names[] = {
    "QButtonGroup"
    // static
    // prototype
    , "addButton"
    , "button"
    , "buttons"
    , "checkedButton"
    , "checkedId"
    , "id"
    , "removeButton"
    , "setId"
    , "toString"
};

static const char * const qtscript_QButtonGroup_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "QAbstractButton arg__1\nQAbstractButton arg__1, int id"
    , "int id"
    , ""
    , ""
    , ""
    , "QAbstractButton button"
    , "QAbstractButton arg__1"
    , "QAbstractButton button, int id"
""
};

static const int qtscript_QButtonGroup_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 1
    , 0
    , 0
    , 0
    , 1
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QButtonGroup_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QButtonGroup::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QButtonGroup*)
Q_DECLARE_METATYPE(QtScriptShell_QButtonGroup*)
Q_DECLARE_METATYPE(QAbstractButton*)
Q_DECLARE_METATYPE(QList<QAbstractButton*>)

//
// QButtonGroup
//

static QScriptValue qtscript_QButtonGroup_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 8;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QButtonGroup* _q_self = qscriptvalue_cast<QButtonGroup*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QButtonGroup.%0(): this object is not a QButtonGroup")
            .arg(qtscript_QButtonGroup_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
        _q_self->addButton(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->addButton(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QAbstractButton* _q_result = _q_self->button(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QList<QAbstractButton*> _q_result = _q_self->buttons();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QAbstractButton* _q_result = _q_self->checkedButton();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->checkedId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
        int _q_result = _q_self->id(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
        _q_self->removeButton(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setId(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QButtonGroup");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QButtonGroup_throw_ambiguity_error_helper(context,
        qtscript_QButtonGroup_function_names[_id+1],
        qtscript_QButtonGroup_function_signatures[_id+1]);
}

static QScriptValue qtscript_QButtonGroup_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QButtonGroup(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QButtonGroup* _q_cpp_result = new QtScriptShell_QButtonGroup();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QButtonGroup*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QButtonGroup* _q_cpp_result = new QtScriptShell_QButtonGroup(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QButtonGroup*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QButtonGroup_throw_ambiguity_error_helper(context,
        qtscript_QButtonGroup_function_names[_id],
        qtscript_QButtonGroup_function_signatures[_id]);
}

static QScriptValue qtscript_QButtonGroup_toScriptValue(QScriptEngine *engine, QButtonGroup* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QButtonGroup_fromScriptValue(const QScriptValue &value, QButtonGroup* &out)
{
    out = qobject_cast<QButtonGroup*>(value.toQObject());
}

QScriptValue qtscript_create_QButtonGroup_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QButtonGroup*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QButtonGroup*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QButtonGroup_prototype_call, qtscript_QButtonGroup_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QButtonGroup_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QButtonGroup*>(engine, qtscript_QButtonGroup_toScriptValue, 
        qtscript_QButtonGroup_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QButtonGroup_static_call, proto, qtscript_QButtonGroup_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
