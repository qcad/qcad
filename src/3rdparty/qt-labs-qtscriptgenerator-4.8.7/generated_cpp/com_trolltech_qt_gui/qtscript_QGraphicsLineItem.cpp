#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicsitem.h>
#include <QVariant>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qgraphicseffect.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qgraphicstransform.h>
#include <qgraphicswidget.h>
#include <qline.h>
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

#include "qtscriptshell_QGraphicsLineItem.h"

static const char * const qtscript_QGraphicsLineItem_function_names[] = {
    "QGraphicsLineItem"
    // static
    // prototype
    , "line"
    , "pen"
    , "setLine"
    , "setPen"
    , "toString"
};

static const char * const qtscript_QGraphicsLineItem_function_signatures[] = {
    "QGraphicsItem parent, QGraphicsScene scene\nQLineF line, QGraphicsItem parent, QGraphicsScene scene\nqreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem parent, QGraphicsScene scene"
    // static
    // prototype
    , ""
    , ""
    , "QLineF line\nqreal x1, qreal y1, qreal x2, qreal y2"
    , "QPen pen"
""
};

static const int qtscript_QGraphicsLineItem_function_lengths[] = {
    6
    // static
    // prototype
    , 0
    , 0
    , 4
    , 1
    , 0
};

static QScriptValue qtscript_QGraphicsLineItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsLineItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsLineItem*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsLineItem*)

//
// QGraphicsLineItem
//

static QScriptValue qtscript_QGraphicsLineItem_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsLineItem* _q_self = qscriptvalue_cast<QGraphicsLineItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsLineItem.%0(): this object is not a QGraphicsLineItem")
            .arg(qtscript_QGraphicsLineItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QLineF _q_result = _q_self->line();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPen _q_result = _q_self->pen();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QLineF _q_arg0 = qscriptvalue_cast<QLineF>(context->argument(0));
        _q_self->setLine(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->setLine(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QPen _q_arg0 = qscriptvalue_cast<QPen>(context->argument(0));
        _q_self->setPen(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QGraphicsLineItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsLineItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsLineItem_function_names[_id+1],
        qtscript_QGraphicsLineItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsLineItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsLineItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsLineItem* _q_cpp_result = new QtScriptShell_QGraphicsLineItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLineItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QtScriptShell_QGraphicsLineItem* _q_cpp_result = new QtScriptShell_QGraphicsLineItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLineItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QLineF>() == context->argument(0).toVariant().userType())) {
            QLineF _q_arg0 = qscriptvalue_cast<QLineF>(context->argument(0));
            QtScriptShell_QGraphicsLineItem* _q_cpp_result = new QtScriptShell_QGraphicsLineItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLineItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))
            && qscriptvalue_cast<QGraphicsScene*>(context->argument(1))) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QGraphicsScene* _q_arg1 = qscriptvalue_cast<QGraphicsScene*>(context->argument(1));
            QtScriptShell_QGraphicsLineItem* _q_cpp_result = new QtScriptShell_QGraphicsLineItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLineItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QLineF>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QGraphicsItem*>(context->argument(1))) {
            QLineF _q_arg0 = qscriptvalue_cast<QLineF>(context->argument(0));
            QGraphicsItem* _q_arg1 = qscriptvalue_cast<QGraphicsItem*>(context->argument(1));
            QtScriptShell_QGraphicsLineItem* _q_cpp_result = new QtScriptShell_QGraphicsLineItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLineItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QLineF _q_arg0 = qscriptvalue_cast<QLineF>(context->argument(0));
        QGraphicsItem* _q_arg1 = qscriptvalue_cast<QGraphicsItem*>(context->argument(1));
        QGraphicsScene* _q_arg2 = qscriptvalue_cast<QGraphicsScene*>(context->argument(2));
        QtScriptShell_QGraphicsLineItem* _q_cpp_result = new QtScriptShell_QGraphicsLineItem(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLineItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QtScriptShell_QGraphicsLineItem* _q_cpp_result = new QtScriptShell_QGraphicsLineItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLineItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QGraphicsItem* _q_arg4 = qscriptvalue_cast<QGraphicsItem*>(context->argument(4));
        QtScriptShell_QGraphicsLineItem* _q_cpp_result = new QtScriptShell_QGraphicsLineItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLineItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QGraphicsItem* _q_arg4 = qscriptvalue_cast<QGraphicsItem*>(context->argument(4));
        QGraphicsScene* _q_arg5 = qscriptvalue_cast<QGraphicsScene*>(context->argument(5));
        QtScriptShell_QGraphicsLineItem* _q_cpp_result = new QtScriptShell_QGraphicsLineItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsLineItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsLineItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsLineItem_function_names[_id],
        qtscript_QGraphicsLineItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsLineItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsLineItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsLineItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsItem*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsLineItem_prototype_call, qtscript_QGraphicsLineItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsLineItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsLineItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsLineItem_static_call, proto, qtscript_QGraphicsLineItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
