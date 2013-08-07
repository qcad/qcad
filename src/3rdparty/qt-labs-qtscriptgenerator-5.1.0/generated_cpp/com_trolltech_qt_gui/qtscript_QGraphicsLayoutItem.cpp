#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgraphicslayoutitem.h>
#include <QVariant>
#include <qgraphicsitem.h>
#include <qgraphicslayoutitem.h>
#include <qrect.h>
#include <qsize.h>
#include <qsizepolicy.h>

#include "qtscriptshell_QGraphicsLayoutItem.h"

static const char * const qtscript_QGraphicsLayoutItem_function_names[] = {
    "QGraphicsLayoutItem"
    // static
    // prototype
    , "contentsRect"
    , "effectiveSizeHint"
    , "geometry"
    , "getContentsMargins"
    , "graphicsItem"
    , "isLayout"
    , "maximumHeight"
    , "maximumSize"
    , "maximumWidth"
    , "minimumHeight"
    , "minimumSize"
    , "minimumWidth"
    , "ownedByLayout"
    , "parentLayoutItem"
    , "preferredHeight"
    , "preferredSize"
    , "preferredWidth"
    , "setGeometry"
    , "setMaximumHeight"
    , "setMaximumSize"
    , "setMaximumWidth"
    , "setMinimumHeight"
    , "setMinimumSize"
    , "setMinimumWidth"
    , "setParentLayoutItem"
    , "setPreferredHeight"
    , "setPreferredSize"
    , "setPreferredWidth"
    , "setSizePolicy"
    , "sizePolicy"
    , "updateGeometry"
    , "toString"
};

static const char * const qtscript_QGraphicsLayoutItem_function_signatures[] = {
    "QGraphicsLayoutItem parent, bool isLayout"
    // static
    // prototype
    , ""
    , "SizeHint which, QSizeF constraint"
    , ""
    , "qreal left, qreal top, qreal right, qreal bottom"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QRectF rect"
    , "qreal height"
    , "QSizeF size\nqreal w, qreal h"
    , "qreal width"
    , "qreal height"
    , "QSizeF size\nqreal w, qreal h"
    , "qreal width"
    , "QGraphicsLayoutItem parent"
    , "qreal height"
    , "QSizeF size\nqreal w, qreal h"
    , "qreal width"
    , "Policy hPolicy, Policy vPolicy, ControlType controlType\nQSizePolicy policy"
    , ""
    , ""
""
};

static const int qtscript_QGraphicsLayoutItem_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 2
    , 0
    , 4
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 2
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 2
    , 1
    , 3
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsLayoutItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsLayoutItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsLayoutItem*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsLayoutItem*)
Q_DECLARE_METATYPE(Qt::SizeHint)
Q_DECLARE_METATYPE(qreal*)
Q_DECLARE_METATYPE(QSizePolicy::Policy)
Q_DECLARE_METATYPE(QSizePolicy::ControlType)

//
// QGraphicsLayoutItem
//

static QScriptValue qtscript_QGraphicsLayoutItem_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 31;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsLayoutItem* _q_self = qscriptvalue_cast<QGraphicsLayoutItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsLayoutItem.%0(): this object is not a QGraphicsLayoutItem")
            .arg(qtscript_QGraphicsLayoutItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->contentsRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        Qt::SizeHint _q_arg0 = qscriptvalue_cast<Qt::SizeHint>(context->argument(0));
        QSizeF _q_result = _q_self->effectiveSizeHint(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        Qt::SizeHint _q_arg0 = qscriptvalue_cast<Qt::SizeHint>(context->argument(0));
        QSizeF _q_arg1 = qscriptvalue_cast<QSizeF>(context->argument(1));
        QSizeF _q_result = _q_self->effectiveSizeHint(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->geometry();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 4) {
        qreal* _q_arg0 = qscriptvalue_cast<qreal*>(context->argument(0));
        qreal* _q_arg1 = qscriptvalue_cast<qreal*>(context->argument(1));
        qreal* _q_arg2 = qscriptvalue_cast<qreal*>(context->argument(2));
        qreal* _q_arg3 = qscriptvalue_cast<qreal*>(context->argument(3));
        _q_self->getContentsMargins(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QGraphicsItem* _q_result = _q_self->graphicsItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isLayout();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->maximumHeight();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QSizeF _q_result = _q_self->maximumSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->maximumWidth();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->minimumHeight();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QSizeF _q_result = _q_self->minimumSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->minimumWidth();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->ownedByLayout();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QGraphicsLayoutItem* _q_result = _q_self->parentLayoutItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->preferredHeight();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QSizeF _q_result = _q_self->preferredSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->preferredWidth();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        _q_self->setGeometry(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setMaximumHeight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        _q_self->setMaximumSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setMaximumSize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setMaximumWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setMinimumHeight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        _q_self->setMinimumSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setMinimumSize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setMinimumWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        _q_self->setParentLayoutItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setPreferredHeight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        _q_self->setPreferredSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setPreferredSize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setPreferredWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        QSizePolicy _q_arg0 = qscriptvalue_cast<QSizePolicy>(context->argument(0));
        _q_self->setSizePolicy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QSizePolicy::Policy _q_arg0 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(0));
        QSizePolicy::Policy _q_arg1 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(1));
        _q_self->setSizePolicy(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QSizePolicy::Policy _q_arg0 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(0));
        QSizePolicy::Policy _q_arg1 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(1));
        QSizePolicy::ControlType _q_arg2 = qscriptvalue_cast<QSizePolicy::ControlType>(context->argument(2));
        _q_self->setSizePolicy(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        QSizePolicy _q_result = _q_self->sizePolicy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        _q_self->updateGeometry();
        return context->engine()->undefinedValue();
    }
    break;

    case 31: {
    QString result = QString::fromLatin1("QGraphicsLayoutItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsLayoutItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsLayoutItem_function_names[_id+1],
        qtscript_QGraphicsLayoutItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsLayoutItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsLayoutItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsLayoutItem* _q_cpp_result = new QtScriptShell_QGraphicsLayoutItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLayoutItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        QtScriptShell_QGraphicsLayoutItem* _q_cpp_result = new QtScriptShell_QGraphicsLayoutItem(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLayoutItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        QtScriptShell_QGraphicsLayoutItem* _q_cpp_result = new QtScriptShell_QGraphicsLayoutItem(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLayoutItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsLayoutItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsLayoutItem_function_names[_id],
        qtscript_QGraphicsLayoutItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsLayoutItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsLayoutItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsLayoutItem*)0));
    for (int i = 0; i < 32; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsLayoutItem_prototype_call, qtscript_QGraphicsLayoutItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsLayoutItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsLayoutItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsLayoutItem_static_call, proto, qtscript_QGraphicsLayoutItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
