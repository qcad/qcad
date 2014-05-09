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

#include "qtscriptshell_QGraphicsPathItem.h"

static const char * const qtscript_QGraphicsPathItem_function_names[] = {
    "QGraphicsPathItem"
    // static
    // prototype
    , "path"
    , "setPath"
    , "toString"
};

static const char * const qtscript_QGraphicsPathItem_function_signatures[] = {
    "QGraphicsItem parent\nQPainterPath path, QGraphicsItem parent"
    // static
    // prototype
    , ""
    , "QPainterPath path"
""
};

static const int qtscript_QGraphicsPathItem_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QGraphicsPathItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsPathItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsPathItem*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsPathItem*)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QAbstractGraphicsShapeItem*)

//
// QGraphicsPathItem
//

static QScriptValue qtscript_QGraphicsPathItem_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGraphicsPathItem* _q_self = qscriptvalue_cast<QGraphicsPathItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsPathItem.%0(): this object is not a QGraphicsPathItem")
            .arg(qtscript_QGraphicsPathItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QPainterPath _q_result = _q_self->path();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        _q_self->setPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QGraphicsPathItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsPathItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsPathItem_function_names[_id+1],
        qtscript_QGraphicsPathItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsPathItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsPathItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsPathItem* _q_cpp_result = new QtScriptShell_QGraphicsPathItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPathItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QtScriptShell_QGraphicsPathItem* _q_cpp_result = new QtScriptShell_QGraphicsPathItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPathItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            QtScriptShell_QGraphicsPathItem* _q_cpp_result = new QtScriptShell_QGraphicsPathItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPathItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
        QGraphicsItem* _q_arg1 = qscriptvalue_cast<QGraphicsItem*>(context->argument(1));
        QtScriptShell_QGraphicsPathItem* _q_cpp_result = new QtScriptShell_QGraphicsPathItem(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPathItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsPathItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsPathItem_function_names[_id],
        qtscript_QGraphicsPathItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsPathItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsPathItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsPathItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractGraphicsShapeItem*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsPathItem_prototype_call, qtscript_QGraphicsPathItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsPathItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsPathItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsPathItem_static_call, proto, qtscript_QGraphicsPathItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
