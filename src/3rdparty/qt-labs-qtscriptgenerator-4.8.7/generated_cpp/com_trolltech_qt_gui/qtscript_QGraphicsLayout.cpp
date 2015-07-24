#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicslayout.h>
#include <QVariant>
#include <qcoreevent.h>
#include <qgraphicsitem.h>
#include <qgraphicslayout.h>
#include <qgraphicslayoutitem.h>
#include <qrect.h>
#include <qsize.h>
#include <qsizepolicy.h>

#include "qtscriptshell_QGraphicsLayout.h"

static const char * const qtscript_QGraphicsLayout_function_names[] = {
    "QGraphicsLayout"
    // static
    , "instantInvalidatePropagation"
    , "setInstantInvalidatePropagation"
    // prototype
    , "activate"
    , "count"
    , "invalidate"
    , "isActivated"
    , "itemAt"
    , "removeAt"
    , "setContentsMargins"
    , "widgetEvent"
    , "toString"
};

static const char * const qtscript_QGraphicsLayout_function_signatures[] = {
    "QGraphicsLayoutItem parent"
    // static
    , ""
    , "bool enable"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "int i"
    , "int index"
    , "qreal left, qreal top, qreal right, qreal bottom"
    , "QEvent e"
""
};

static const int qtscript_QGraphicsLayout_function_lengths[] = {
    1
    // static
    , 0
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 4
    , 1
    , 0
};

static QScriptValue qtscript_QGraphicsLayout_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsLayout::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsLayout*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsLayout*)
Q_DECLARE_METATYPE(QGraphicsLayoutItem*)
Q_DECLARE_METATYPE(QEvent*)

//
// QGraphicsLayout
//

static QScriptValue qtscript_QGraphicsLayout_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGraphicsLayout* _q_self = qscriptvalue_cast<QGraphicsLayout*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsLayout.%0(): this object is not a QGraphicsLayout")
            .arg(qtscript_QGraphicsLayout_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->activate();
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
    if (context->argumentCount() == 0) {
        _q_self->invalidate();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isActivated();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QGraphicsLayoutItem* _q_result = _q_self->itemAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->removeAt(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->setContentsMargins(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QEvent* _q_arg0 = qscriptvalue_cast<QEvent*>(context->argument(0));
        _q_self->widgetEvent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QGraphicsLayout");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsLayout_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsLayout_function_names[_id+3],
        qtscript_QGraphicsLayout_function_signatures[_id+3]);
}

static QScriptValue qtscript_QGraphicsLayout_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsLayout(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsLayout* _q_cpp_result = new QtScriptShell_QGraphicsLayout();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLayout*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        QtScriptShell_QGraphicsLayout* _q_cpp_result = new QtScriptShell_QGraphicsLayout(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLayout*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = QGraphicsLayout::instantInvalidatePropagation();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QGraphicsLayout::setInstantInvalidatePropagation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsLayout_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsLayout_function_names[_id],
        qtscript_QGraphicsLayout_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsLayout_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsLayout*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsLayout*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsLayoutItem*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsLayout_prototype_call, qtscript_QGraphicsLayout_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsLayout_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsLayout*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsLayout_static_call, proto, qtscript_QGraphicsLayout_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsLayout_static_call,
            qtscript_QGraphicsLayout_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QGraphicsLayout_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
