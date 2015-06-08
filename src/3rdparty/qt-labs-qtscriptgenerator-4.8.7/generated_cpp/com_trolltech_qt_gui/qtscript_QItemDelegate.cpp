#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qitemdelegate.h>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qfont.h>
#include <qitemdelegate.h>
#include <qitemeditorfactory.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qrect.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QItemDelegate.h"

static const char * const qtscript_QItemDelegate_function_names[] = {
    "QItemDelegate"
    // static
    // prototype
    , "itemEditorFactory"
    , "setItemEditorFactory"
    , "toString"
};

static const char * const qtscript_QItemDelegate_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , "QItemEditorFactory factory"
""
};

static const int qtscript_QItemDelegate_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QItemDelegate_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QItemDelegate::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QItemDelegate*)
Q_DECLARE_METATYPE(QtScriptShell_QItemDelegate*)
Q_DECLARE_METATYPE(QItemEditorFactory*)
Q_DECLARE_METATYPE(QAbstractItemDelegate*)

//
// QItemDelegate
//

static QScriptValue qtscript_QItemDelegate_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QItemDelegate* _q_self = qscriptvalue_cast<QItemDelegate*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QItemDelegate.%0(): this object is not a QItemDelegate")
            .arg(qtscript_QItemDelegate_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QItemEditorFactory* _q_result = _q_self->itemEditorFactory();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QItemEditorFactory* _q_arg0 = qscriptvalue_cast<QItemEditorFactory*>(context->argument(0));
        _q_self->setItemEditorFactory(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QItemDelegate");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QItemDelegate_throw_ambiguity_error_helper(context,
        qtscript_QItemDelegate_function_names[_id+1],
        qtscript_QItemDelegate_function_signatures[_id+1]);
}

static QScriptValue qtscript_QItemDelegate_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QItemDelegate(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QItemDelegate* _q_cpp_result = new QtScriptShell_QItemDelegate();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QItemDelegate*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QItemDelegate* _q_cpp_result = new QtScriptShell_QItemDelegate(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QItemDelegate*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QItemDelegate_throw_ambiguity_error_helper(context,
        qtscript_QItemDelegate_function_names[_id],
        qtscript_QItemDelegate_function_signatures[_id]);
}

static QScriptValue qtscript_QItemDelegate_toScriptValue(QScriptEngine *engine, QItemDelegate* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QItemDelegate_fromScriptValue(const QScriptValue &value, QItemDelegate* &out)
{
    out = qobject_cast<QItemDelegate*>(value.toQObject());
}

QScriptValue qtscript_create_QItemDelegate_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QItemDelegate*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QItemDelegate*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractItemDelegate*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QItemDelegate_prototype_call, qtscript_QItemDelegate_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QItemDelegate_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QItemDelegate*>(engine, qtscript_QItemDelegate_toScriptValue, 
        qtscript_QItemDelegate_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QItemDelegate_static_call, proto, qtscript_QItemDelegate_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
