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

#include "qtscriptshell_QVBoxLayout.h"

static const char * const qtscript_QVBoxLayout_function_names[] = {
    "QVBoxLayout"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QVBoxLayout_function_signatures[] = {
    "\nQWidget parent"
    // static
    // prototype
""
};

static const int qtscript_QVBoxLayout_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QVBoxLayout_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QVBoxLayout::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QVBoxLayout*)
Q_DECLARE_METATYPE(QtScriptShell_QVBoxLayout*)
Q_DECLARE_METATYPE(QBoxLayout*)

//
// QVBoxLayout
//

static QScriptValue qtscript_QVBoxLayout_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QVBoxLayout* _q_self = qscriptvalue_cast<QVBoxLayout*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QVBoxLayout.%0(): this object is not a QVBoxLayout")
            .arg(qtscript_QVBoxLayout_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QVBoxLayout");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QVBoxLayout_throw_ambiguity_error_helper(context,
        qtscript_QVBoxLayout_function_names[_id+1],
        qtscript_QVBoxLayout_function_signatures[_id+1]);
}

static QScriptValue qtscript_QVBoxLayout_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QVBoxLayout(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QVBoxLayout* _q_cpp_result = new QtScriptShell_QVBoxLayout();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QVBoxLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QVBoxLayout* _q_cpp_result = new QtScriptShell_QVBoxLayout(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QVBoxLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QVBoxLayout_throw_ambiguity_error_helper(context,
        qtscript_QVBoxLayout_function_names[_id],
        qtscript_QVBoxLayout_function_signatures[_id]);
}

static QScriptValue qtscript_QVBoxLayout_toScriptValue(QScriptEngine *engine, QVBoxLayout* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QVBoxLayout_fromScriptValue(const QScriptValue &value, QVBoxLayout* &out)
{
    out = qobject_cast<QVBoxLayout*>(value.toQObject());
}

QScriptValue qtscript_create_QVBoxLayout_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QVBoxLayout*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QVBoxLayout*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QBoxLayout*>()));

    qScriptRegisterMetaType<QVBoxLayout*>(engine, qtscript_QVBoxLayout_toScriptValue, 
        qtscript_QVBoxLayout_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QVBoxLayout_static_call, proto, qtscript_QVBoxLayout_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
