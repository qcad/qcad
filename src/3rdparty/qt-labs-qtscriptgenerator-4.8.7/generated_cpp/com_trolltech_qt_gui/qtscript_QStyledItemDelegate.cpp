#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qstyleditemdelegate.h>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qitemeditorfactory.h>
#include <qlist.h>
#include <qlocale.h>
#include <qobject.h>
#include <qpainter.h>
#include <qsize.h>
#include <qstyleditemdelegate.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QStyledItemDelegate.h"

static const char * const qtscript_QStyledItemDelegate_function_names[] = {
    "QStyledItemDelegate"
    // static
    // prototype
    , "displayText"
    , "itemEditorFactory"
    , "setItemEditorFactory"
    , "toString"
};

static const char * const qtscript_QStyledItemDelegate_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "Object value, QLocale locale"
    , ""
    , "QItemEditorFactory factory"
""
};

static const int qtscript_QStyledItemDelegate_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QStyledItemDelegate_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStyledItemDelegate::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStyledItemDelegate*)
Q_DECLARE_METATYPE(QtScriptShell_QStyledItemDelegate*)
Q_DECLARE_METATYPE(QItemEditorFactory*)
Q_DECLARE_METATYPE(QAbstractItemDelegate*)

//
// QStyledItemDelegate
//

static QScriptValue qtscript_QStyledItemDelegate_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QStyledItemDelegate* _q_self = qscriptvalue_cast<QStyledItemDelegate*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStyledItemDelegate.%0(): this object is not a QStyledItemDelegate")
            .arg(qtscript_QStyledItemDelegate_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        QLocale _q_arg1 = qscriptvalue_cast<QLocale>(context->argument(1));
        QString _q_result = _q_self->displayText(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QItemEditorFactory* _q_result = _q_self->itemEditorFactory();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QItemEditorFactory* _q_arg0 = qscriptvalue_cast<QItemEditorFactory*>(context->argument(0));
        _q_self->setItemEditorFactory(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QStyledItemDelegate");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyledItemDelegate_throw_ambiguity_error_helper(context,
        qtscript_QStyledItemDelegate_function_names[_id+1],
        qtscript_QStyledItemDelegate_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStyledItemDelegate_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStyledItemDelegate(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStyledItemDelegate* _q_cpp_result = new QtScriptShell_QStyledItemDelegate();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStyledItemDelegate*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QStyledItemDelegate* _q_cpp_result = new QtScriptShell_QStyledItemDelegate(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStyledItemDelegate*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStyledItemDelegate_throw_ambiguity_error_helper(context,
        qtscript_QStyledItemDelegate_function_names[_id],
        qtscript_QStyledItemDelegate_function_signatures[_id]);
}

static QScriptValue qtscript_QStyledItemDelegate_toScriptValue(QScriptEngine *engine, QStyledItemDelegate* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QStyledItemDelegate_fromScriptValue(const QScriptValue &value, QStyledItemDelegate* &out)
{
    out = qobject_cast<QStyledItemDelegate*>(value.toQObject());
}

QScriptValue qtscript_create_QStyledItemDelegate_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStyledItemDelegate*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStyledItemDelegate*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractItemDelegate*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStyledItemDelegate_prototype_call, qtscript_QStyledItemDelegate_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStyledItemDelegate_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QStyledItemDelegate*>(engine, qtscript_QStyledItemDelegate_toScriptValue, 
        qtscript_QStyledItemDelegate_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStyledItemDelegate_static_call, proto, qtscript_QStyledItemDelegate_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
