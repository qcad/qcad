#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qerrormessage.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qerrormessage.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QErrorMessage.h"

static const char * const qtscript_QErrorMessage_function_names[] = {
    "QErrorMessage"
    // static
    , "qtHandler"
    // prototype
    , "toString"
};

static const char * const qtscript_QErrorMessage_function_signatures[] = {
    "QWidget parent"
    // static
    , ""
    // prototype
""
};

static const int qtscript_QErrorMessage_function_lengths[] = {
    1
    // static
    , 0
    // prototype
    , 0
};

static QScriptValue qtscript_QErrorMessage_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QErrorMessage::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QErrorMessage*)
Q_DECLARE_METATYPE(QtScriptShell_QErrorMessage*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QDialog*)

//
// QErrorMessage
//

static QScriptValue qtscript_QErrorMessage_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QErrorMessage* _q_self = qscriptvalue_cast<QErrorMessage*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QErrorMessage.%0(): this object is not a QErrorMessage")
            .arg(qtscript_QErrorMessage_function_names[_id+2]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QErrorMessage");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QErrorMessage_throw_ambiguity_error_helper(context,
        qtscript_QErrorMessage_function_names[_id+2],
        qtscript_QErrorMessage_function_signatures[_id+2]);
}

static QScriptValue qtscript_QErrorMessage_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QErrorMessage(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QErrorMessage* _q_cpp_result = new QtScriptShell_QErrorMessage();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QErrorMessage*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QErrorMessage* _q_cpp_result = new QtScriptShell_QErrorMessage(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QErrorMessage*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QErrorMessage* _q_result = QErrorMessage::qtHandler();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QErrorMessage_throw_ambiguity_error_helper(context,
        qtscript_QErrorMessage_function_names[_id],
        qtscript_QErrorMessage_function_signatures[_id]);
}

static QScriptValue qtscript_QErrorMessage_toScriptValue(QScriptEngine *engine, QErrorMessage* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QErrorMessage_fromScriptValue(const QScriptValue &value, QErrorMessage* &out)
{
    out = qobject_cast<QErrorMessage*>(value.toQObject());
}

QScriptValue qtscript_create_QErrorMessage_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QErrorMessage*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QErrorMessage*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDialog*>()));

    qScriptRegisterMetaType<QErrorMessage*>(engine, qtscript_QErrorMessage_toScriptValue, 
        qtscript_QErrorMessage_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QErrorMessage_static_call, proto, qtscript_QErrorMessage_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QErrorMessage_static_call,
            qtscript_QErrorMessage_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QErrorMessage_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
