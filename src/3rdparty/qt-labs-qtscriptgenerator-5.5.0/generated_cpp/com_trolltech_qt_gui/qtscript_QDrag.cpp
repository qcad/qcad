#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdrag.h>
#include <QPixmap>
#include <QPoint>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdrag.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qpixmap.h>
#include <qpoint.h>

#include "qtscriptshell_QDrag.h"

static const char * const qtscript_QDrag_function_names[] = {
    "QDrag"
    // static
    // prototype
    , "defaultAction"
    , "dragCursor"
    , "exec"
    , "hotSpot"
    , "mimeData"
    , "pixmap"
    , "setDragCursor"
    , "setHotSpot"
    , "setMimeData"
    , "setPixmap"
    , "source"
    , "supportedActions"
    , "target"
    , "toString"
};

static const char * const qtscript_QDrag_function_signatures[] = {
    "QObject dragSource"
    // static
    // prototype
    , ""
    , "DropAction action"
    , "DropActions supportedActions\nDropActions supportedActions, DropAction defaultAction"
    , ""
    , ""
    , ""
    , "QPixmap cursor, DropAction action"
    , "QPoint hotspot"
    , "QMimeData data"
    , "QPixmap arg__1"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QDrag_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 2
    , 0
    , 0
    , 0
    , 2
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QDrag_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDrag::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDrag*)
Q_DECLARE_METATYPE(QtScriptShell_QDrag*)
Q_DECLARE_METATYPE(Qt::DropAction)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)
Q_DECLARE_METATYPE(QMimeData*)

//
// QDrag
//

static QScriptValue qtscript_QDrag_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 13;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDrag* _q_self = qscriptvalue_cast<QDrag*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDrag.%0(): this object is not a QDrag")
            .arg(qtscript_QDrag_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        Qt::DropAction _q_result = _q_self->defaultAction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        Qt::DropAction _q_arg0 = qscriptvalue_cast<Qt::DropAction>(context->argument(0));
        QPixmap _q_result = _q_self->dragCursor(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        Qt::DropAction _q_result = _q_self->exec();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QFlags<Qt::DropAction> _q_arg0 = qscriptvalue_cast<QFlags<Qt::DropAction> >(context->argument(0));
        Qt::DropAction _q_result = _q_self->exec(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QFlags<Qt::DropAction> _q_arg0 = qscriptvalue_cast<QFlags<Qt::DropAction> >(context->argument(0));
        Qt::DropAction _q_arg1 = qscriptvalue_cast<Qt::DropAction>(context->argument(1));
        Qt::DropAction _q_result = _q_self->exec(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->hotSpot();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QMimeData* _q_result = _q_self->mimeData();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QPixmap _q_result = _q_self->pixmap();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        Qt::DropAction _q_arg1 = qscriptvalue_cast<Qt::DropAction>(context->argument(1));
        _q_self->setDragCursor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->setHotSpot(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QMimeData* _q_arg0 = qscriptvalue_cast<QMimeData*>(context->argument(0));
        _q_self->setMimeData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        _q_self->setPixmap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QObject* _q_result = _q_self->source();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QFlags<Qt::DropAction> _q_result = _q_self->supportedActions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QObject* _q_result = _q_self->target();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13: {
    QString result = QString::fromLatin1("QDrag");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDrag_throw_ambiguity_error_helper(context,
        qtscript_QDrag_function_names[_id+1],
        qtscript_QDrag_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDrag_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDrag(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QDrag* _q_cpp_result = new QtScriptShell_QDrag(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDrag*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDrag_throw_ambiguity_error_helper(context,
        qtscript_QDrag_function_names[_id],
        qtscript_QDrag_function_signatures[_id]);
}

static QScriptValue qtscript_QDrag_toScriptValue(QScriptEngine *engine, QDrag* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QDrag_fromScriptValue(const QScriptValue &value, QDrag* &out)
{
    out = qobject_cast<QDrag*>(value.toQObject());
}

QScriptValue qtscript_create_QDrag_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDrag*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDrag*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 14; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDrag_prototype_call, qtscript_QDrag_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDrag_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QDrag*>(engine, qtscript_QDrag_toScriptValue, 
        qtscript_QDrag_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDrag_static_call, proto, qtscript_QDrag_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
