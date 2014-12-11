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

#include "qtscriptshell_QAbstractGraphicsShapeItem.h"

static const char * const qtscript_QAbstractGraphicsShapeItem_function_names[] = {
    "QAbstractGraphicsShapeItem"
    // static
    // prototype
    , "brush"
    , "pen"
    , "setBrush"
    , "setPen"
    , "toString"
};

static const char * const qtscript_QAbstractGraphicsShapeItem_function_signatures[] = {
    "QGraphicsItem parent"
    // static
    // prototype
    , ""
    , ""
    , "QBrush brush"
    , "QPen pen"
""
};

static const int qtscript_QAbstractGraphicsShapeItem_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QAbstractGraphicsShapeItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractGraphicsShapeItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractGraphicsShapeItem*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractGraphicsShapeItem*)

//
// QAbstractGraphicsShapeItem
//

static QScriptValue qtscript_QAbstractGraphicsShapeItem_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QAbstractGraphicsShapeItem* _q_self = qscriptvalue_cast<QAbstractGraphicsShapeItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractGraphicsShapeItem.%0(): this object is not a QAbstractGraphicsShapeItem")
            .arg(qtscript_QAbstractGraphicsShapeItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->brush();
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
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        _q_self->setBrush(_q_arg0);
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
    QString result = QString::fromLatin1("QAbstractGraphicsShapeItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractGraphicsShapeItem_throw_ambiguity_error_helper(context,
        qtscript_QAbstractGraphicsShapeItem_function_names[_id+1],
        qtscript_QAbstractGraphicsShapeItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractGraphicsShapeItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractGraphicsShapeItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractGraphicsShapeItem* _q_cpp_result = new QtScriptShell_QAbstractGraphicsShapeItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QAbstractGraphicsShapeItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QtScriptShell_QAbstractGraphicsShapeItem* _q_cpp_result = new QtScriptShell_QAbstractGraphicsShapeItem(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QAbstractGraphicsShapeItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractGraphicsShapeItem_throw_ambiguity_error_helper(context,
        qtscript_QAbstractGraphicsShapeItem_function_names[_id],
        qtscript_QAbstractGraphicsShapeItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QAbstractGraphicsShapeItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractGraphicsShapeItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractGraphicsShapeItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsItem*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractGraphicsShapeItem_prototype_call, qtscript_QAbstractGraphicsShapeItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractGraphicsShapeItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QAbstractGraphicsShapeItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractGraphicsShapeItem_static_call, proto, qtscript_QAbstractGraphicsShapeItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
