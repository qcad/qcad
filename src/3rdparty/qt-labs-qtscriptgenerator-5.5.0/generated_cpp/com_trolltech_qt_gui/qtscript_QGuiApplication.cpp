#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qguiapplication.h>
#include <QVariant>
#include <qbytearray.h>
#include <qclipboard.h>
#include <qcoreapplication.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qfont.h>
#include <qguiapplication.h>
#include <qicon.h>
#include <qlist.h>
#include <qobject.h>
#include <qpalette.h>
#include <qsessionmanager.h>
#include <qstringlist.h>
#include <qtranslator.h>

#include "qtscriptshell_QGuiApplication.h"

static const char * const qtscript_QGuiApplication_function_names[] = {
    "QGuiApplication"
    // static
    , "changeOverrideCursor"
    , "clipboard"
    , "desktopSettingsAware"
    , "focusObject"
    , "font"
    , "isLeftToRight"
    , "isRightToLeft"
    , "keyboardModifiers"
    , "mouseButtons"
    , "overrideCursor"
    , "palette"
    , "queryKeyboardModifiers"
    , "restoreOverrideCursor"
    , "setDesktopSettingsAware"
    , "setFont"
    , "setOverrideCursor"
    , "setPalette"
    , "sync"
    // prototype
    , "devicePixelRatio"
    , "isSavingSession"
    , "isSessionRestored"
    , "sessionId"
    , "sessionKey"
    , "toString"
};

static const char * const qtscript_QGuiApplication_function_signatures[] = {
    "int argc, char argv, int arg__3"
    // static
    , "QCursor arg__1"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "bool on"
    , "QFont arg__1"
    , "QCursor arg__1"
    , "QPalette pal"
    , ""
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QGuiApplication_function_lengths[] = {
    3
    // static
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QGuiApplication_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGuiApplication::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGuiApplication*)
Q_DECLARE_METATYPE(QtScriptShell_QGuiApplication*)
Q_DECLARE_METATYPE(QClipboard*)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(QCursor*)
Q_DECLARE_METATYPE(char**)
Q_DECLARE_METATYPE(QCoreApplication*)

//
// QGuiApplication
//

static QScriptValue qtscript_QGuiApplication_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGuiApplication* _q_self = qscriptvalue_cast<QGuiApplication*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGuiApplication.%0(): this object is not a QGuiApplication")
            .arg(qtscript_QGuiApplication_function_names[_id+19]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->devicePixelRatio();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSavingSession();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSessionRestored();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->sessionId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->sessionKey();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QGuiApplication");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGuiApplication_throw_ambiguity_error_helper(context,
        qtscript_QGuiApplication_function_names[_id+19],
        qtscript_QGuiApplication_function_signatures[_id+19]);
}

static QScriptValue qtscript_QGuiApplication_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGuiApplication(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        char** _q_arg1 = qscriptvalue_cast<char**>(context->argument(1));
        QtScriptShell_QGuiApplication* _q_cpp_result = new QtScriptShell_QGuiApplication(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGuiApplication*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        char** _q_arg1 = qscriptvalue_cast<char**>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QtScriptShell_QGuiApplication* _q_cpp_result = new QtScriptShell_QGuiApplication(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGuiApplication*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QCursor _q_arg0 = qscriptvalue_cast<QCursor>(context->argument(0));
        QGuiApplication::changeOverrideCursor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QClipboard* _q_result = QGuiApplication::clipboard();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = QGuiApplication::desktopSettingsAware();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QObject* _q_result = QGuiApplication::focusObject();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QFont _q_result = QGuiApplication::font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = QGuiApplication::isLeftToRight();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = QGuiApplication::isRightToLeft();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QFlags<Qt::KeyboardModifier> _q_result = QGuiApplication::keyboardModifiers();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QFlags<Qt::MouseButton> _q_result = QGuiApplication::mouseButtons();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QCursor* _q_result = QGuiApplication::overrideCursor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QPalette _q_result = QGuiApplication::palette();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QFlags<Qt::KeyboardModifier> _q_result = QGuiApplication::queryKeyboardModifiers();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QGuiApplication::restoreOverrideCursor();
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QGuiApplication::setDesktopSettingsAware(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        QGuiApplication::setFont(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QCursor _q_arg0 = qscriptvalue_cast<QCursor>(context->argument(0));
        QGuiApplication::setOverrideCursor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QPalette _q_arg0 = qscriptvalue_cast<QPalette>(context->argument(0));
        QGuiApplication::setPalette(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QGuiApplication::sync();
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGuiApplication_throw_ambiguity_error_helper(context,
        qtscript_QGuiApplication_function_names[_id],
        qtscript_QGuiApplication_function_signatures[_id]);
}

static QScriptValue qtscript_QGuiApplication_toScriptValue(QScriptEngine *engine, QGuiApplication* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGuiApplication_fromScriptValue(const QScriptValue &value, QGuiApplication* &out)
{
    out = qobject_cast<QGuiApplication*>(value.toQObject());
}

QScriptValue qtscript_create_QGuiApplication_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGuiApplication*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGuiApplication*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QCoreApplication*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGuiApplication_prototype_call, qtscript_QGuiApplication_function_lengths[i+19]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGuiApplication_function_names[i+19]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGuiApplication*>(engine, qtscript_QGuiApplication_toScriptValue, 
        qtscript_QGuiApplication_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGuiApplication_static_call, proto, qtscript_QGuiApplication_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 18; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGuiApplication_static_call,
            qtscript_QGuiApplication_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QGuiApplication_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
