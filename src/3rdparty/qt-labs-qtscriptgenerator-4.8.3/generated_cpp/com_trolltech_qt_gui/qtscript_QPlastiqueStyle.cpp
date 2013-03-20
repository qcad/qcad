#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qplastiquestyle.h>
#include <QVariant>
#include <qapplication.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qicon.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qplastiquestyle.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QPlastiqueStyle.h"

static const char * const qtscript_QPlastiqueStyle_function_names[] = {
    "QPlastiqueStyle"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QPlastiqueStyle_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_QPlastiqueStyle_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QPlastiqueStyle_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPlastiqueStyle::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPlastiqueStyle*)
Q_DECLARE_METATYPE(QtScriptShell_QPlastiqueStyle*)
Q_DECLARE_METATYPE(QWindowsStyle*)

//
// QPlastiqueStyle
//

static QScriptValue qtscript_QPlastiqueStyle_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QPlastiqueStyle* _q_self = qscriptvalue_cast<QPlastiqueStyle*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPlastiqueStyle.%0(): this object is not a QPlastiqueStyle")
            .arg(qtscript_QPlastiqueStyle_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QPlastiqueStyle");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPlastiqueStyle_throw_ambiguity_error_helper(context,
        qtscript_QPlastiqueStyle_function_names[_id+1],
        qtscript_QPlastiqueStyle_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPlastiqueStyle_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPlastiqueStyle(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPlastiqueStyle* _q_cpp_result = new QtScriptShell_QPlastiqueStyle();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPlastiqueStyle*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPlastiqueStyle_throw_ambiguity_error_helper(context,
        qtscript_QPlastiqueStyle_function_names[_id],
        qtscript_QPlastiqueStyle_function_signatures[_id]);
}

static QScriptValue qtscript_QPlastiqueStyle_toScriptValue(QScriptEngine *engine, QPlastiqueStyle* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QPlastiqueStyle_fromScriptValue(const QScriptValue &value, QPlastiqueStyle* &out)
{
    out = qobject_cast<QPlastiqueStyle*>(value.toQObject());
}

QScriptValue qtscript_create_QPlastiqueStyle_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPlastiqueStyle*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPlastiqueStyle*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWindowsStyle*>()));

    qScriptRegisterMetaType<QPlastiqueStyle*>(engine, qtscript_QPlastiqueStyle_toScriptValue, 
        qtscript_QPlastiqueStyle_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPlastiqueStyle_static_call, proto, qtscript_QPlastiqueStyle_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
