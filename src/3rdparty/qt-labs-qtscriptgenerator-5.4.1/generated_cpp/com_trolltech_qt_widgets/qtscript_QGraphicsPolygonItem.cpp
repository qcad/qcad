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

#include "qtscriptshell_QGraphicsPolygonItem.h"

static const char * const qtscript_QGraphicsPolygonItem_function_names[] = {
    "QGraphicsPolygonItem"
    // static
    // prototype
    , "fillRule"
    , "polygon"
    , "setFillRule"
    , "setPolygon"
    , "toString"
};

static const char * const qtscript_QGraphicsPolygonItem_function_signatures[] = {
    "QGraphicsItem parent\nQPolygonF polygon, QGraphicsItem parent"
    // static
    // prototype
    , ""
    , ""
    , "FillRule rule"
    , "QPolygonF polygon"
""
};

static const int qtscript_QGraphicsPolygonItem_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QGraphicsPolygonItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsPolygonItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsPolygonItem*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsPolygonItem*)
Q_DECLARE_METATYPE(Qt::FillRule)
Q_DECLARE_METATYPE(QAbstractGraphicsShapeItem*)

//
// QGraphicsPolygonItem
//

static QScriptValue qtscript_QGraphicsPolygonItem_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGraphicsPolygonItem* _q_self = qscriptvalue_cast<QGraphicsPolygonItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsPolygonItem.%0(): this object is not a QGraphicsPolygonItem")
            .arg(qtscript_QGraphicsPolygonItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        Qt::FillRule _q_result = _q_self->fillRule();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPolygonF _q_result = _q_self->polygon();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        Qt::FillRule _q_arg0 = qscriptvalue_cast<Qt::FillRule>(context->argument(0));
        _q_self->setFillRule(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
        _q_self->setPolygon(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QGraphicsPolygonItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsPolygonItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsPolygonItem_function_names[_id+1],
        qtscript_QGraphicsPolygonItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsPolygonItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsPolygonItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsPolygonItem* _q_cpp_result = new QtScriptShell_QGraphicsPolygonItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPolygonItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QtScriptShell_QGraphicsPolygonItem* _q_cpp_result = new QtScriptShell_QGraphicsPolygonItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPolygonItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            QtScriptShell_QGraphicsPolygonItem* _q_cpp_result = new QtScriptShell_QGraphicsPolygonItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPolygonItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
        QGraphicsItem* _q_arg1 = qscriptvalue_cast<QGraphicsItem*>(context->argument(1));
        QtScriptShell_QGraphicsPolygonItem* _q_cpp_result = new QtScriptShell_QGraphicsPolygonItem(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPolygonItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsPolygonItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsPolygonItem_function_names[_id],
        qtscript_QGraphicsPolygonItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsPolygonItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsPolygonItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsPolygonItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractGraphicsShapeItem*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsPolygonItem_prototype_call, qtscript_QGraphicsPolygonItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsPolygonItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsPolygonItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsPolygonItem_static_call, proto, qtscript_QGraphicsPolygonItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
