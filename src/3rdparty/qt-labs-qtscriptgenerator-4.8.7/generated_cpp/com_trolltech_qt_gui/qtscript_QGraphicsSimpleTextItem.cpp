#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicsitem.h>
#include <QVariant>
#include <qbrush.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
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

#include "qtscriptshell_QGraphicsSimpleTextItem.h"

static const char * const qtscript_QGraphicsSimpleTextItem_function_names[] = {
    "QGraphicsSimpleTextItem"
    // static
    // prototype
    , "font"
    , "setFont"
    , "setText"
    , "text"
    , "toString"
};

static const char * const qtscript_QGraphicsSimpleTextItem_function_signatures[] = {
    "QGraphicsItem parent, QGraphicsScene scene\nString text, QGraphicsItem parent, QGraphicsScene scene"
    // static
    // prototype
    , ""
    , "QFont font"
    , "String text"
    , ""
""
};

static const int qtscript_QGraphicsSimpleTextItem_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsSimpleTextItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsSimpleTextItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsSimpleTextItem*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsSimpleTextItem*)
Q_DECLARE_METATYPE(QAbstractGraphicsShapeItem*)

//
// QGraphicsSimpleTextItem
//

static QScriptValue qtscript_QGraphicsSimpleTextItem_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGraphicsSimpleTextItem* _q_self = qscriptvalue_cast<QGraphicsSimpleTextItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsSimpleTextItem.%0(): this object is not a QGraphicsSimpleTextItem")
            .arg(qtscript_QGraphicsSimpleTextItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QFont _q_result = _q_self->font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        _q_self->setFont(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QGraphicsSimpleTextItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSimpleTextItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSimpleTextItem_function_names[_id+1],
        qtscript_QGraphicsSimpleTextItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsSimpleTextItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsSimpleTextItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsSimpleTextItem* _q_cpp_result = new QtScriptShell_QGraphicsSimpleTextItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsSimpleTextItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QtScriptShell_QGraphicsSimpleTextItem* _q_cpp_result = new QtScriptShell_QGraphicsSimpleTextItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsSimpleTextItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QGraphicsSimpleTextItem* _q_cpp_result = new QtScriptShell_QGraphicsSimpleTextItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsSimpleTextItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))
            && qscriptvalue_cast<QGraphicsScene*>(context->argument(1))) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QGraphicsScene* _q_arg1 = qscriptvalue_cast<QGraphicsScene*>(context->argument(1));
            QtScriptShell_QGraphicsSimpleTextItem* _q_cpp_result = new QtScriptShell_QGraphicsSimpleTextItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsSimpleTextItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && qscriptvalue_cast<QGraphicsItem*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            QGraphicsItem* _q_arg1 = qscriptvalue_cast<QGraphicsItem*>(context->argument(1));
            QtScriptShell_QGraphicsSimpleTextItem* _q_cpp_result = new QtScriptShell_QGraphicsSimpleTextItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsSimpleTextItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QGraphicsItem* _q_arg1 = qscriptvalue_cast<QGraphicsItem*>(context->argument(1));
        QGraphicsScene* _q_arg2 = qscriptvalue_cast<QGraphicsScene*>(context->argument(2));
        QtScriptShell_QGraphicsSimpleTextItem* _q_cpp_result = new QtScriptShell_QGraphicsSimpleTextItem(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsSimpleTextItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSimpleTextItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSimpleTextItem_function_names[_id],
        qtscript_QGraphicsSimpleTextItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsSimpleTextItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSimpleTextItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsSimpleTextItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractGraphicsShapeItem*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsSimpleTextItem_prototype_call, qtscript_QGraphicsSimpleTextItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsSimpleTextItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSimpleTextItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsSimpleTextItem_static_call, proto, qtscript_QGraphicsSimpleTextItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
