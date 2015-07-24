#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qboxlayout.h>
#include <QVariant>
#include <qboxlayout.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qlist.h>
#include <qmargins.h>
#include <qobject.h>
#include <qrect.h>
#include <qsize.h>
#include <qwidget.h>

#include "qtscriptshell_QHBoxLayout.h"

static const char * const qtscript_QHBoxLayout_function_names[] = {
    "QHBoxLayout"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QHBoxLayout_function_signatures[] = {
    "\nQWidget parent"
    // static
    // prototype
""
};

static const int qtscript_QHBoxLayout_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QHBoxLayout_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QHBoxLayout::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QHBoxLayout*)
Q_DECLARE_METATYPE(QtScriptShell_QHBoxLayout*)
Q_DECLARE_METATYPE(QBoxLayout*)

//
// QHBoxLayout
//

static QScriptValue qtscript_QHBoxLayout_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QHBoxLayout* _q_self = qscriptvalue_cast<QHBoxLayout*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QHBoxLayout.%0(): this object is not a QHBoxLayout")
            .arg(qtscript_QHBoxLayout_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QHBoxLayout");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHBoxLayout_throw_ambiguity_error_helper(context,
        qtscript_QHBoxLayout_function_names[_id+1],
        qtscript_QHBoxLayout_function_signatures[_id+1]);
}

static QScriptValue qtscript_QHBoxLayout_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QHBoxLayout(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QHBoxLayout* _q_cpp_result = new QtScriptShell_QHBoxLayout();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHBoxLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QHBoxLayout* _q_cpp_result = new QtScriptShell_QHBoxLayout(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHBoxLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHBoxLayout_throw_ambiguity_error_helper(context,
        qtscript_QHBoxLayout_function_names[_id],
        qtscript_QHBoxLayout_function_signatures[_id]);
}

static QScriptValue qtscript_QHBoxLayout_toScriptValue(QScriptEngine *engine, QHBoxLayout* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QHBoxLayout_fromScriptValue(const QScriptValue &value, QHBoxLayout* &out)
{
    out = qobject_cast<QHBoxLayout*>(value.toQObject());
}

QScriptValue qtscript_create_QHBoxLayout_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QHBoxLayout*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QHBoxLayout*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QBoxLayout*>()));

    qScriptRegisterMetaType<QHBoxLayout*>(engine, qtscript_QHBoxLayout_toScriptValue, 
        qtscript_QHBoxLayout_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QHBoxLayout_static_call, proto, qtscript_QHBoxLayout_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
