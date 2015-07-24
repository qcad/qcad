#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgraphicsitem.h>
#include <QVariant>
#include <qbrush.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qgraphicseffect.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qgraphicstransform.h>
#include <qgraphicswidget.h>
#include <qlist.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpen.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qtransform.h>
#include <qwidget.h>

#include "qtscriptshell_QGraphicsRectItem.h"

static const char * const qtscript_QGraphicsRectItem_function_names[] = {
    "QGraphicsRectItem"
    // static
    // prototype
    , "rect"
    , "setRect"
    , "toString"
};

static const char * const qtscript_QGraphicsRectItem_function_signatures[] = {
    "QGraphicsItem parent\nQRectF rect, QGraphicsItem parent\nqreal x, qreal y, qreal w, qreal h, QGraphicsItem parent"
    // static
    // prototype
    , ""
    , "QRectF rect\nqreal x, qreal y, qreal w, qreal h"
""
};

static const int qtscript_QGraphicsRectItem_function_lengths[] = {
    5
    // static
    // prototype
    , 0
    , 4
    , 0
};

static QScriptValue qtscript_QGraphicsRectItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsRectItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsRectItem*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsRectItem*)
Q_DECLARE_METATYPE(QAbstractGraphicsShapeItem*)

//
// QGraphicsRectItem
//

static QScriptValue qtscript_QGraphicsRectItem_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsRectItem* _q_self = qscriptvalue_cast<QGraphicsRectItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsRectItem.%0(): this object is not a QGraphicsRectItem")
            .arg(qtscript_QGraphicsRectItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->rect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        _q_self->setRect(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->setRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QGraphicsRectItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsRectItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsRectItem_function_names[_id+1],
        qtscript_QGraphicsRectItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsRectItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsRectItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsRectItem* _q_cpp_result = new QtScriptShell_QGraphicsRectItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsRectItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QtScriptShell_QGraphicsRectItem* _q_cpp_result = new QtScriptShell_QGraphicsRectItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsRectItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QtScriptShell_QGraphicsRectItem* _q_cpp_result = new QtScriptShell_QGraphicsRectItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsRectItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QGraphicsItem* _q_arg1 = qscriptvalue_cast<QGraphicsItem*>(context->argument(1));
        QtScriptShell_QGraphicsRectItem* _q_cpp_result = new QtScriptShell_QGraphicsRectItem(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsRectItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QtScriptShell_QGraphicsRectItem* _q_cpp_result = new QtScriptShell_QGraphicsRectItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsRectItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QGraphicsItem* _q_arg4 = qscriptvalue_cast<QGraphicsItem*>(context->argument(4));
        QtScriptShell_QGraphicsRectItem* _q_cpp_result = new QtScriptShell_QGraphicsRectItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsRectItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsRectItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsRectItem_function_names[_id],
        qtscript_QGraphicsRectItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsRectItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsRectItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsRectItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractGraphicsShapeItem*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsRectItem_prototype_call, qtscript_QGraphicsRectItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsRectItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsRectItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsRectItem_static_call, proto, qtscript_QGraphicsRectItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
