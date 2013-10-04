#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicsitem.h>
#include <QGesture>
#include <QVariant>
#include <qbytearray.h>
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
#include <qobject.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qtransform.h>
#include <qwidget.h>

#include "qtscriptshell_QGraphicsObject.h"

static const char * const qtscript_QGraphicsObject_function_names[] = {
    "QGraphicsObject"
    // static
    // prototype
    , "grabGesture"
    , "ungrabGesture"
    , "toString"
};

static const char * const qtscript_QGraphicsObject_function_signatures[] = {
    "QGraphicsItem parent"
    // static
    // prototype
    , "GestureType type, GestureFlags flags"
    , "GestureType type"
""
};

static const int qtscript_QGraphicsObject_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QGraphicsObject_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsObject::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsObject*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsObject*)
Q_DECLARE_METATYPE(QFlags<Qt::GestureFlag>)

//
// QGraphicsObject
//

static QScriptValue qtscript_QGraphicsObject_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGraphicsObject* _q_self = qscriptvalue_cast<QGraphicsObject*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsObject.%0(): this object is not a QGraphicsObject")
            .arg(qtscript_QGraphicsObject_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        Qt::GestureType _q_arg0 = qscriptvalue_cast<Qt::GestureType>(context->argument(0));
        _q_self->grabGesture(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        Qt::GestureType _q_arg0 = qscriptvalue_cast<Qt::GestureType>(context->argument(0));
        QFlags<Qt::GestureFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::GestureFlag> >(context->argument(1));
        _q_self->grabGesture(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        Qt::GestureType _q_arg0 = qscriptvalue_cast<Qt::GestureType>(context->argument(0));
        _q_self->ungrabGesture(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2: {
    QString result;
    QDebug d(&result);
    d << _q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsObject_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsObject_function_names[_id+1],
        qtscript_QGraphicsObject_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsObject_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsObject(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsObject* _q_cpp_result = new QtScriptShell_QGraphicsObject();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsObject*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QtScriptShell_QGraphicsObject* _q_cpp_result = new QtScriptShell_QGraphicsObject(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsObject*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsObject_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsObject_function_names[_id],
        qtscript_QGraphicsObject_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsObject_toScriptValue(QScriptEngine *engine, QGraphicsObject* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsObject_fromScriptValue(const QScriptValue &value, QGraphicsObject* &out)
{
    out = qobject_cast<QGraphicsObject*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsObject_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsObject*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsObject*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    proto.setProperty(QString::fromLatin1("__QGraphicsItem__"),
        engine->defaultPrototype(qMetaTypeId<QGraphicsItem*>()),
        QScriptValue::SkipInEnumeration);
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsObject_prototype_call, qtscript_QGraphicsObject_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsObject_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGraphicsObject*>(engine, qtscript_QGraphicsObject_toScriptValue, 
        qtscript_QGraphicsObject_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsObject_static_call, proto, qtscript_QGraphicsObject_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
