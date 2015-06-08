#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qmotifstyle.h>
#include <QVariant>
#include <qapplication.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qicon.h>
#include <qlist.h>
#include <qmotifstyle.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QMotifStyle.h"

static const char * const qtscript_QMotifStyle_function_names[] = {
    "QMotifStyle"
    // static
    // prototype
    , "setUseHighlightColors"
    , "useHighlightColors"
    , "toString"
};

static const char * const qtscript_QMotifStyle_function_signatures[] = {
    "bool useHighlightCols"
    // static
    // prototype
    , "bool arg__1"
    , ""
""
};

static const int qtscript_QMotifStyle_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QMotifStyle_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMotifStyle::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMotifStyle*)
Q_DECLARE_METATYPE(QtScriptShell_QMotifStyle*)
Q_DECLARE_METATYPE(QCommonStyle*)

//
// QMotifStyle
//

static QScriptValue qtscript_QMotifStyle_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QMotifStyle* _q_self = qscriptvalue_cast<QMotifStyle*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMotifStyle.%0(): this object is not a QMotifStyle")
            .arg(qtscript_QMotifStyle_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setUseHighlightColors(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->useHighlightColors();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QMotifStyle");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMotifStyle_throw_ambiguity_error_helper(context,
        qtscript_QMotifStyle_function_names[_id+1],
        qtscript_QMotifStyle_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMotifStyle_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMotifStyle(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QMotifStyle* _q_cpp_result = new QtScriptShell_QMotifStyle();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMotifStyle*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QtScriptShell_QMotifStyle* _q_cpp_result = new QtScriptShell_QMotifStyle(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMotifStyle*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMotifStyle_throw_ambiguity_error_helper(context,
        qtscript_QMotifStyle_function_names[_id],
        qtscript_QMotifStyle_function_signatures[_id]);
}

static QScriptValue qtscript_QMotifStyle_toScriptValue(QScriptEngine *engine, QMotifStyle* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QMotifStyle_fromScriptValue(const QScriptValue &value, QMotifStyle* &out)
{
    out = qobject_cast<QMotifStyle*>(value.toQObject());
}

QScriptValue qtscript_create_QMotifStyle_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMotifStyle*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMotifStyle*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QCommonStyle*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMotifStyle_prototype_call, qtscript_QMotifStyle_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMotifStyle_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QMotifStyle*>(engine, qtscript_QMotifStyle_toScriptValue, 
        qtscript_QMotifStyle_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMotifStyle_static_call, proto, qtscript_QMotifStyle_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
