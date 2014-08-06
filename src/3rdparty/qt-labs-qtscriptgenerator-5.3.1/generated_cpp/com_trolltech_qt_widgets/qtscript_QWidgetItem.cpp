#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qlayoutitem.h>
#include <QVariant>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qrect.h>
#include <qsize.h>
#include <qwidget.h>

#include "qtscriptshell_QWidgetItem.h"

static const char * const qtscript_QWidgetItem_function_names[] = {
    "QWidgetItem"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QWidgetItem_function_signatures[] = {
    "QWidget w"
    // static
    // prototype
""
};

static const int qtscript_QWidgetItem_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QWidgetItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWidgetItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWidgetItem*)
Q_DECLARE_METATYPE(QtScriptShell_QWidgetItem*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QLayoutItem*)

//
// QWidgetItem
//

static QScriptValue qtscript_QWidgetItem_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QWidgetItem* _q_self = qscriptvalue_cast<QWidgetItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWidgetItem.%0(): this object is not a QWidgetItem")
            .arg(qtscript_QWidgetItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QWidgetItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWidgetItem_throw_ambiguity_error_helper(context,
        qtscript_QWidgetItem_function_names[_id+1],
        qtscript_QWidgetItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWidgetItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWidgetItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QWidgetItem* _q_cpp_result = new QtScriptShell_QWidgetItem(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QWidgetItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWidgetItem_throw_ambiguity_error_helper(context,
        qtscript_QWidgetItem_function_names[_id],
        qtscript_QWidgetItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QWidgetItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWidgetItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWidgetItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QLayoutItem*>()));

    engine->setDefaultPrototype(qMetaTypeId<QWidgetItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWidgetItem_static_call, proto, qtscript_QWidgetItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
