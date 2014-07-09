#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qlayoutitem.h>
#include <QVariant>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qrect.h>
#include <qsize.h>
#include <qwidget.h>

#include "qtscriptshell_QSpacerItem.h"

static const char * const qtscript_QSpacerItem_function_names[] = {
    "QSpacerItem"
    // static
    // prototype
    , "changeSize"
    , "toString"
};

static const char * const qtscript_QSpacerItem_function_signatures[] = {
    "int w, int h, Policy hData, Policy vData"
    // static
    // prototype
    , "int w, int h, Policy hData, Policy vData"
""
};

static const int qtscript_QSpacerItem_function_lengths[] = {
    4
    // static
    // prototype
    , 4
    , 0
};

static QScriptValue qtscript_QSpacerItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSpacerItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSpacerItem*)
Q_DECLARE_METATYPE(QtScriptShell_QSpacerItem*)
Q_DECLARE_METATYPE(QSizePolicy::Policy)
Q_DECLARE_METATYPE(QLayoutItem*)

//
// QSpacerItem
//

static QScriptValue qtscript_QSpacerItem_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSpacerItem* _q_self = qscriptvalue_cast<QSpacerItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSpacerItem.%0(): this object is not a QSpacerItem")
            .arg(qtscript_QSpacerItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->changeSize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QSizePolicy::Policy _q_arg2 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(2));
        _q_self->changeSize(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QSizePolicy::Policy _q_arg2 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(2));
        QSizePolicy::Policy _q_arg3 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(3));
        _q_self->changeSize(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QSpacerItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSpacerItem_throw_ambiguity_error_helper(context,
        qtscript_QSpacerItem_function_names[_id+1],
        qtscript_QSpacerItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSpacerItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSpacerItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QtScriptShell_QSpacerItem* _q_cpp_result = new QtScriptShell_QSpacerItem(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QSpacerItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QSizePolicy::Policy _q_arg2 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(2));
        QtScriptShell_QSpacerItem* _q_cpp_result = new QtScriptShell_QSpacerItem(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QSpacerItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QSizePolicy::Policy _q_arg2 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(2));
        QSizePolicy::Policy _q_arg3 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(3));
        QtScriptShell_QSpacerItem* _q_cpp_result = new QtScriptShell_QSpacerItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QSpacerItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSpacerItem_throw_ambiguity_error_helper(context,
        qtscript_QSpacerItem_function_names[_id],
        qtscript_QSpacerItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QSpacerItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSpacerItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSpacerItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QLayoutItem*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSpacerItem_prototype_call, qtscript_QSpacerItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSpacerItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSpacerItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSpacerItem_static_call, proto, qtscript_QSpacerItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
