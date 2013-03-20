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
#include <qlist.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qtransform.h>
#include <qwidget.h>

#include "qtscriptshell_QGraphicsPixmapItem.h"

static const char * const qtscript_QGraphicsPixmapItem_function_names[] = {
    "QGraphicsPixmapItem"
    // static
    // prototype
    , "offset"
    , "pixmap"
    , "setOffset"
    , "setPixmap"
    , "setShapeMode"
    , "setTransformationMode"
    , "shapeMode"
    , "transformationMode"
    , "toString"
};

static const char * const qtscript_QGraphicsPixmapItem_function_signatures[] = {
    "QGraphicsItem parent, QGraphicsScene scene\nQPixmap pixmap, QGraphicsItem parent, QGraphicsScene scene"
    // static
    // prototype
    , ""
    , ""
    , "QPointF offset\nqreal x, qreal y"
    , "QPixmap pixmap"
    , "ShapeMode mode"
    , "TransformationMode mode"
    , ""
    , ""
""
};

static const int qtscript_QGraphicsPixmapItem_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 0
    , 2
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsPixmapItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsPixmapItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsPixmapItem*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsPixmapItem*)
Q_DECLARE_METATYPE(QGraphicsPixmapItem::ShapeMode)
Q_DECLARE_METATYPE(Qt::TransformationMode)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QGraphicsPixmapItem::ShapeMode
//

static const QGraphicsPixmapItem::ShapeMode qtscript_QGraphicsPixmapItem_ShapeMode_values[] = {
    QGraphicsPixmapItem::MaskShape
    , QGraphicsPixmapItem::BoundingRectShape
    , QGraphicsPixmapItem::HeuristicMaskShape
};

static const char * const qtscript_QGraphicsPixmapItem_ShapeMode_keys[] = {
    "MaskShape"
    , "BoundingRectShape"
    , "HeuristicMaskShape"
};

static QString qtscript_QGraphicsPixmapItem_ShapeMode_toStringHelper(QGraphicsPixmapItem::ShapeMode value)
{
    if ((value >= QGraphicsPixmapItem::MaskShape) && (value <= QGraphicsPixmapItem::HeuristicMaskShape))
        return qtscript_QGraphicsPixmapItem_ShapeMode_keys[static_cast<int>(value)-static_cast<int>(QGraphicsPixmapItem::MaskShape)];
    return QString();
}

static QScriptValue qtscript_QGraphicsPixmapItem_ShapeMode_toScriptValue(QScriptEngine *engine, const QGraphicsPixmapItem::ShapeMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsPixmapItem"));
    return clazz.property(qtscript_QGraphicsPixmapItem_ShapeMode_toStringHelper(value));
}

static void qtscript_QGraphicsPixmapItem_ShapeMode_fromScriptValue(const QScriptValue &value, QGraphicsPixmapItem::ShapeMode &out)
{
    out = qvariant_cast<QGraphicsPixmapItem::ShapeMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsPixmapItem_ShapeMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QGraphicsPixmapItem::MaskShape) && (arg <= QGraphicsPixmapItem::HeuristicMaskShape))
        return qScriptValueFromValue(engine,  static_cast<QGraphicsPixmapItem::ShapeMode>(arg));
    return context->throwError(QString::fromLatin1("ShapeMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsPixmapItem_ShapeMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsPixmapItem::ShapeMode value = qscriptvalue_cast<QGraphicsPixmapItem::ShapeMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsPixmapItem_ShapeMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsPixmapItem::ShapeMode value = qscriptvalue_cast<QGraphicsPixmapItem::ShapeMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsPixmapItem_ShapeMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsPixmapItem_ShapeMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsPixmapItem_ShapeMode,
        qtscript_QGraphicsPixmapItem_ShapeMode_valueOf, qtscript_QGraphicsPixmapItem_ShapeMode_toString);
    qScriptRegisterMetaType<QGraphicsPixmapItem::ShapeMode>(engine, qtscript_QGraphicsPixmapItem_ShapeMode_toScriptValue,
        qtscript_QGraphicsPixmapItem_ShapeMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsPixmapItem_ShapeMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsPixmapItem_ShapeMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsPixmapItem
//

static QScriptValue qtscript_QGraphicsPixmapItem_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGraphicsPixmapItem* _q_self = qscriptvalue_cast<QGraphicsPixmapItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsPixmapItem.%0(): this object is not a QGraphicsPixmapItem")
            .arg(qtscript_QGraphicsPixmapItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->offset();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPixmap _q_result = _q_self->pixmap();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setOffset(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setOffset(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        _q_self->setPixmap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QGraphicsPixmapItem::ShapeMode _q_arg0 = qscriptvalue_cast<QGraphicsPixmapItem::ShapeMode>(context->argument(0));
        _q_self->setShapeMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        Qt::TransformationMode _q_arg0 = qscriptvalue_cast<Qt::TransformationMode>(context->argument(0));
        _q_self->setTransformationMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QGraphicsPixmapItem::ShapeMode _q_result = _q_self->shapeMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        Qt::TransformationMode _q_result = _q_self->transformationMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QGraphicsPixmapItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsPixmapItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsPixmapItem_function_names[_id+1],
        qtscript_QGraphicsPixmapItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsPixmapItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsPixmapItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsPixmapItem* _q_cpp_result = new QtScriptShell_QGraphicsPixmapItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPixmapItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QtScriptShell_QGraphicsPixmapItem* _q_cpp_result = new QtScriptShell_QGraphicsPixmapItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPixmapItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QPixmap>() == context->argument(0).toVariant().userType())) {
            QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
            QtScriptShell_QGraphicsPixmapItem* _q_cpp_result = new QtScriptShell_QGraphicsPixmapItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPixmapItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))
            && qscriptvalue_cast<QGraphicsScene*>(context->argument(1))) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QGraphicsScene* _q_arg1 = qscriptvalue_cast<QGraphicsScene*>(context->argument(1));
            QtScriptShell_QGraphicsPixmapItem* _q_cpp_result = new QtScriptShell_QGraphicsPixmapItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPixmapItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QPixmap>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QGraphicsItem*>(context->argument(1))) {
            QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
            QGraphicsItem* _q_arg1 = qscriptvalue_cast<QGraphicsItem*>(context->argument(1));
            QtScriptShell_QGraphicsPixmapItem* _q_cpp_result = new QtScriptShell_QGraphicsPixmapItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPixmapItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        QGraphicsItem* _q_arg1 = qscriptvalue_cast<QGraphicsItem*>(context->argument(1));
        QGraphicsScene* _q_arg2 = qscriptvalue_cast<QGraphicsScene*>(context->argument(2));
        QtScriptShell_QGraphicsPixmapItem* _q_cpp_result = new QtScriptShell_QGraphicsPixmapItem(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsPixmapItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsPixmapItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsPixmapItem_function_names[_id],
        qtscript_QGraphicsPixmapItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsPixmapItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsPixmapItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsPixmapItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsItem*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsPixmapItem_prototype_call, qtscript_QGraphicsPixmapItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsPixmapItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsPixmapItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsPixmapItem_static_call, proto, qtscript_QGraphicsPixmapItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ShapeMode"),
        qtscript_create_QGraphicsPixmapItem_ShapeMode_class(engine, ctor));
    return ctor;
}
