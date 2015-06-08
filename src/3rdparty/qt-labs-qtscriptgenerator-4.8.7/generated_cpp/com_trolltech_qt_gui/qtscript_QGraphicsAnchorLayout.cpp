#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicsanchorlayout.h>
#include <QVariant>
#include <qcoreevent.h>
#include <qgraphicsanchorlayout.h>
#include <qgraphicsitem.h>
#include <qgraphicslayoutitem.h>
#include <qrect.h>
#include <qsize.h>
#include <qsizepolicy.h>

#include "qtscriptshell_QGraphicsAnchorLayout.h"

static const char * const qtscript_QGraphicsAnchorLayout_function_names[] = {
    "QGraphicsAnchorLayout"
    // static
    // prototype
    , "addAnchor"
    , "addAnchors"
    , "addCornerAnchors"
    , "anchor"
    , "horizontalSpacing"
    , "setHorizontalSpacing"
    , "setSpacing"
    , "setVerticalSpacing"
    , "verticalSpacing"
    , "toString"
};

static const char * const qtscript_QGraphicsAnchorLayout_function_signatures[] = {
    "QGraphicsLayoutItem parent"
    // static
    // prototype
    , "QGraphicsLayoutItem firstItem, AnchorPoint firstEdge, QGraphicsLayoutItem secondItem, AnchorPoint secondEdge"
    , "QGraphicsLayoutItem firstItem, QGraphicsLayoutItem secondItem, Orientations orientations"
    , "QGraphicsLayoutItem firstItem, Corner firstCorner, QGraphicsLayoutItem secondItem, Corner secondCorner"
    , "QGraphicsLayoutItem firstItem, AnchorPoint firstEdge, QGraphicsLayoutItem secondItem, AnchorPoint secondEdge"
    , ""
    , "qreal spacing"
    , "qreal spacing"
    , "qreal spacing"
    , ""
""
};

static const int qtscript_QGraphicsAnchorLayout_function_lengths[] = {
    1
    // static
    // prototype
    , 4
    , 3
    , 4
    , 4
    , 0
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsAnchorLayout_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsAnchorLayout::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsAnchorLayout*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsAnchorLayout*)
Q_DECLARE_METATYPE(QGraphicsLayoutItem*)
Q_DECLARE_METATYPE(Qt::AnchorPoint)
Q_DECLARE_METATYPE(QGraphicsAnchor*)
Q_DECLARE_METATYPE(QFlags<Qt::Orientation>)
Q_DECLARE_METATYPE(Qt::Corner)
Q_DECLARE_METATYPE(QGraphicsLayout*)

//
// QGraphicsAnchorLayout
//

static QScriptValue qtscript_QGraphicsAnchorLayout_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 9;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsAnchorLayout* _q_self = qscriptvalue_cast<QGraphicsAnchorLayout*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsAnchorLayout.%0(): this object is not a QGraphicsAnchorLayout")
            .arg(qtscript_QGraphicsAnchorLayout_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 4) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        Qt::AnchorPoint _q_arg1 = qscriptvalue_cast<Qt::AnchorPoint>(context->argument(1));
        QGraphicsLayoutItem* _q_arg2 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(2));
        Qt::AnchorPoint _q_arg3 = qscriptvalue_cast<Qt::AnchorPoint>(context->argument(3));
        QGraphicsAnchor* _q_result = _q_self->addAnchor(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        QGraphicsLayoutItem* _q_arg1 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(1));
        _q_self->addAnchors(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        QGraphicsLayoutItem* _q_arg1 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(1));
        QFlags<Qt::Orientation> _q_arg2 = qscriptvalue_cast<QFlags<Qt::Orientation> >(context->argument(2));
        _q_self->addAnchors(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 4) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        Qt::Corner _q_arg1 = qscriptvalue_cast<Qt::Corner>(context->argument(1));
        QGraphicsLayoutItem* _q_arg2 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(2));
        Qt::Corner _q_arg3 = qscriptvalue_cast<Qt::Corner>(context->argument(3));
        _q_self->addCornerAnchors(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 4) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        Qt::AnchorPoint _q_arg1 = qscriptvalue_cast<Qt::AnchorPoint>(context->argument(1));
        QGraphicsLayoutItem* _q_arg2 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(2));
        Qt::AnchorPoint _q_arg3 = qscriptvalue_cast<Qt::AnchorPoint>(context->argument(3));
        QGraphicsAnchor* _q_result = _q_self->anchor(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->horizontalSpacing();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setHorizontalSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setVerticalSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->verticalSpacing();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("QGraphicsAnchorLayout");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsAnchorLayout_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsAnchorLayout_function_names[_id+1],
        qtscript_QGraphicsAnchorLayout_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsAnchorLayout_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsAnchorLayout(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsAnchorLayout* _q_cpp_result = new QtScriptShell_QGraphicsAnchorLayout();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsAnchorLayout*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        QtScriptShell_QGraphicsAnchorLayout* _q_cpp_result = new QtScriptShell_QGraphicsAnchorLayout(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsAnchorLayout*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsAnchorLayout_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsAnchorLayout_function_names[_id],
        qtscript_QGraphicsAnchorLayout_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsAnchorLayout_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsAnchorLayout*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsAnchorLayout*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsLayout*>()));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsAnchorLayout_prototype_call, qtscript_QGraphicsAnchorLayout_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsAnchorLayout_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsAnchorLayout*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsAnchorLayout_static_call, proto, qtscript_QGraphicsAnchorLayout_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
