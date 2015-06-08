#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qaccessible.h>
#include <QVariant>
#include <qaccessible.h>
#include <qlist.h>
#include <qobject.h>
#include <qrect.h>

#include "qtscriptshell_QAccessibleInterface.h"

static const char * const qtscript_QAccessibleInterface_function_names[] = {
    "QAccessibleInterface"
    // static
    // prototype
    , "actionText"
    , "childAt"
    , "childCount"
    , "doAction"
    , "indexOfChild"
    , "invokeMethod"
    , "isValid"
    , "navigate"
    , "object"
    , "rect"
    , "relationTo"
    , "role"
    , "setText"
    , "state"
    , "supportedMethods"
    , "text"
    , "userActionCount"
    , "toString"
};

static const char * const qtscript_QAccessibleInterface_function_signatures[] = {
    ""
    // static
    // prototype
    , "int action, Text t, int child"
    , "int x, int y"
    , ""
    , "int action, int child, List params"
    , "QAccessibleInterface arg__1"
    , "Method method, int child, List params"
    , ""
    , "RelationFlag relation, int index, QAccessibleInterface iface"
    , ""
    , "int child"
    , "int child, QAccessibleInterface other, int otherChild"
    , "int child"
    , "Text t, int child, String text"
    , "int child"
    , ""
    , "Text t, int child"
    , "int child"
""
};

static const int qtscript_QAccessibleInterface_function_lengths[] = {
    0
    // static
    // prototype
    , 3
    , 2
    , 0
    , 3
    , 1
    , 3
    , 0
    , 3
    , 0
    , 1
    , 3
    , 1
    , 3
    , 1
    , 0
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QAccessibleInterface_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAccessibleInterface::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAccessibleInterface*)
Q_DECLARE_METATYPE(QtScriptShell_QAccessibleInterface*)
Q_DECLARE_METATYPE(QAccessible::Text)
Q_DECLARE_METATYPE(QAccessible::Method)
Q_DECLARE_METATYPE(QAccessible::RelationFlag)
Q_DECLARE_METATYPE(QAccessibleInterface**)
Q_DECLARE_METATYPE(QFlags<QAccessible::RelationFlag>)
Q_DECLARE_METATYPE(QAccessible::Role)
Q_DECLARE_METATYPE(QFlags<QAccessible::StateFlag>)
Q_DECLARE_METATYPE(QAccessible*)

//
// QAccessibleInterface
//

static QScriptValue qtscript_QAccessibleInterface_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 17;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAccessibleInterface* _q_self = qscriptvalue_cast<QAccessibleInterface*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAccessibleInterface.%0(): this object is not a QAccessibleInterface")
            .arg(qtscript_QAccessibleInterface_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QAccessible::Text _q_arg1 = qscriptvalue_cast<QAccessible::Text>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QString _q_result = _q_self->actionText(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->childAt(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->childCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QList<QVariant> _q_arg2;
        qScriptValueToSequence(context->argument(2), _q_arg2);
        bool _q_result = _q_self->doAction(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QAccessibleInterface* _q_arg0 = qscriptvalue_cast<QAccessibleInterface*>(context->argument(0));
        int _q_result = _q_self->indexOfChild(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 3) {
        QAccessible::Method _q_arg0 = qscriptvalue_cast<QAccessible::Method>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QList<QVariant> _q_arg2;
        qScriptValueToSequence(context->argument(2), _q_arg2);
        QVariant _q_result = _q_self->invokeMethod(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 3) {
        QAccessible::RelationFlag _q_arg0 = qscriptvalue_cast<QAccessible::RelationFlag>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QAccessibleInterface** _q_arg2 = qscriptvalue_cast<QAccessibleInterface**>(context->argument(2));
        int _q_result = _q_self->navigate(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QObject* _q_result = _q_self->object();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QRect _q_result = _q_self->rect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QAccessibleInterface* _q_arg1 = qscriptvalue_cast<QAccessibleInterface*>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QFlags<QAccessible::RelationFlag> _q_result = _q_self->relationTo(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QAccessible::Role _q_result = _q_self->role(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 3) {
        QAccessible::Text _q_arg0 = qscriptvalue_cast<QAccessible::Text>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QString _q_arg2 = context->argument(2).toString();
        _q_self->setText(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QFlags<QAccessible::StateFlag> _q_result = _q_self->state(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QSet<QAccessible::Method> _q_result = _q_self->supportedMethods();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        QAccessible::Text _q_arg0 = qscriptvalue_cast<QAccessible::Text>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QString _q_result = _q_self->text(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->userActionCount(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17: {
    QString result = QString::fromLatin1("QAccessibleInterface");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleInterface_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleInterface_function_names[_id+1],
        qtscript_QAccessibleInterface_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAccessibleInterface_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAccessibleInterface(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAccessibleInterface* _q_cpp_result = new QtScriptShell_QAccessibleInterface();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QAccessibleInterface*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessibleInterface_throw_ambiguity_error_helper(context,
        qtscript_QAccessibleInterface_function_names[_id],
        qtscript_QAccessibleInterface_function_signatures[_id]);
}

QScriptValue qtscript_create_QAccessibleInterface_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAccessibleInterface*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAccessibleInterface*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAccessible*>()));
    for (int i = 0; i < 18; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAccessibleInterface_prototype_call, qtscript_QAccessibleInterface_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAccessibleInterface_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QAccessibleInterface*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAccessibleInterface_static_call, proto, qtscript_QAccessibleInterface_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
