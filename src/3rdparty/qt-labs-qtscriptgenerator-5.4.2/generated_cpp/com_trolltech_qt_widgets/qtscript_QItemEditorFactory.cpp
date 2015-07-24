#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qitemeditorfactory.h>
#include <QVariant>
#include <qbytearray.h>
#include <qitemeditorfactory.h>
#include <qwidget.h>

#include "qtscriptshell_QItemEditorFactory.h"

static const char * const qtscript_QItemEditorFactory_function_names[] = {
    "QItemEditorFactory"
    // static
    , "defaultFactory"
    , "setDefaultFactory"
    // prototype
    , "createEditor"
    , "registerEditor"
    , "valuePropertyName"
    , "toString"
};

static const char * const qtscript_QItemEditorFactory_function_signatures[] = {
    ""
    // static
    , ""
    , "QItemEditorFactory factory"
    // prototype
    , "int userType, QWidget parent"
    , "int userType, QItemEditorCreatorBase creator"
    , "int userType"
""
};

static const int qtscript_QItemEditorFactory_function_lengths[] = {
    0
    // static
    , 0
    , 1
    // prototype
    , 2
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QItemEditorFactory_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QItemEditorFactory::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QItemEditorFactory*)
Q_DECLARE_METATYPE(QtScriptShell_QItemEditorFactory*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QItemEditorCreatorBase*)
Q_DECLARE_METATYPE(const QItemEditorFactory*)

//
// QItemEditorFactory
//

static QScriptValue qtscript_QItemEditorFactory_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QItemEditorFactory* _q_self = qscriptvalue_cast<QItemEditorFactory*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QItemEditorFactory.%0(): this object is not a QItemEditorFactory")
            .arg(qtscript_QItemEditorFactory_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QWidget* _q_result = _q_self->createEditor(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QItemEditorCreatorBase* _q_arg1 = qscriptvalue_cast<QItemEditorCreatorBase*>(context->argument(1));
        _q_self->registerEditor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QByteArray _q_result = _q_self->valuePropertyName(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QItemEditorFactory");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QItemEditorFactory_throw_ambiguity_error_helper(context,
        qtscript_QItemEditorFactory_function_names[_id+3],
        qtscript_QItemEditorFactory_function_signatures[_id+3]);
}

static QScriptValue qtscript_QItemEditorFactory_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QItemEditorFactory(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QItemEditorFactory* _q_cpp_result = new QtScriptShell_QItemEditorFactory();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QItemEditorFactory*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        const QItemEditorFactory* _q_result = const_cast<const QItemEditorFactory*>(QItemEditorFactory::defaultFactory());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QItemEditorFactory* _q_arg0 = qscriptvalue_cast<QItemEditorFactory*>(context->argument(0));
        QItemEditorFactory::setDefaultFactory(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QItemEditorFactory_throw_ambiguity_error_helper(context,
        qtscript_QItemEditorFactory_function_names[_id],
        qtscript_QItemEditorFactory_function_signatures[_id]);
}

QScriptValue qtscript_create_QItemEditorFactory_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QItemEditorFactory*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QItemEditorFactory*)0));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QItemEditorFactory_prototype_call, qtscript_QItemEditorFactory_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QItemEditorFactory_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QItemEditorFactory*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QItemEditorFactory_static_call, proto, qtscript_QItemEditorFactory_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QItemEditorFactory_static_call,
            qtscript_QItemEditorFactory_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QItemEditorFactory_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
