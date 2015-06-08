#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qcoreapplication.h>
#include <QStringList>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreapplication.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>
#include <qtranslator.h>

#include "qtscriptshell_QCoreApplication.h"

static const char * const qtscript_QCoreApplication_function_names[] = {
    "QCoreApplication"
    // static
    , "addLibraryPath"
    , "applicationDirPath"
    , "applicationFilePath"
    , "applicationPid"
    , "closingDown"
    , "exec"
    , "exit"
    , "flush"
    , "hasPendingEvents"
    , "installTranslator"
    , "instance"
    , "isSetuidAllowed"
    , "libraryPaths"
    , "postEvent"
    , "processEvents"
    , "removeLibraryPath"
    , "removePostedEvents"
    , "removeTranslator"
    , "sendEvent"
    , "sendPostedEvents"
    , "setAttribute"
    , "setLibraryPaths"
    , "setSetuidAllowed"
    , "startingUp"
    , "testAttribute"
    , "translate"
    // prototype
    , "notify"
    , "toString"
};

static const char * const qtscript_QCoreApplication_function_signatures[] = {
    "int argc, char argv, int arg__3"
    // static
    , "String arg__1"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int retcode"
    , ""
    , ""
    , "QTranslator messageFile"
    , ""
    , ""
    , ""
    , "QObject receiver, QEvent event, int priority"
    , "ProcessEventsFlags flags\nProcessEventsFlags flags, int maxtime"
    , "String arg__1"
    , "QObject receiver, int eventType"
    , "QTranslator messageFile"
    , "QObject receiver, QEvent event"
    , "QObject receiver, int event_type"
    , "ApplicationAttribute attribute, bool on"
    , "List arg__1"
    , "bool allow"
    , ""
    , "ApplicationAttribute attribute"
    , "char context, char key, char disambiguation, int n"
    // prototype
    , "QObject arg__1, QEvent arg__2"
""
};

static const int qtscript_QCoreApplication_function_lengths[] = {
    3
    // static
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 3
    , 2
    , 1
    , 2
    , 1
    , 2
    , 2
    , 2
    , 1
    , 1
    , 0
    , 1
    , 4
    // prototype
    , 2
    , 0
};

static QScriptValue qtscript_QCoreApplication_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QCoreApplication::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QCoreApplication*)
Q_DECLARE_METATYPE(QtScriptShell_QCoreApplication*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QTranslator*)
Q_DECLARE_METATYPE(QFlags<QEventLoop::ProcessEventsFlag>)
Q_DECLARE_METATYPE(Qt::ApplicationAttribute)
Q_DECLARE_METATYPE(const char*)
Q_DECLARE_METATYPE(char**)

//
// QCoreApplication
//

static QScriptValue qtscript_QCoreApplication_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QCoreApplication* _q_self = qscriptvalue_cast<QCoreApplication*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QCoreApplication.%0(): this object is not a QCoreApplication")
            .arg(qtscript_QCoreApplication_function_names[_id+27]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QEvent* _q_arg1 = qscriptvalue_cast<QEvent*>(context->argument(1));
        bool _q_result = _q_self->notify(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QCoreApplication");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QCoreApplication_throw_ambiguity_error_helper(context,
        qtscript_QCoreApplication_function_names[_id+27],
        qtscript_QCoreApplication_function_signatures[_id+27]);
}

static QScriptValue qtscript_QCoreApplication_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QCoreApplication(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        char** _q_arg1 = qscriptvalue_cast<char**>(context->argument(1));
        QtScriptShell_QCoreApplication* _q_cpp_result = new QtScriptShell_QCoreApplication(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCoreApplication*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        char** _q_arg1 = qscriptvalue_cast<char**>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QtScriptShell_QCoreApplication* _q_cpp_result = new QtScriptShell_QCoreApplication(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCoreApplication*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QCoreApplication::addLibraryPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = QCoreApplication::applicationDirPath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = QCoreApplication::applicationFilePath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        qint64 _q_result = QCoreApplication::applicationPid();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = QCoreApplication::closingDown();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = QCoreApplication::exec();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QCoreApplication::exit();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QCoreApplication::exit(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QCoreApplication::flush();
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = QCoreApplication::hasPendingEvents();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QTranslator* _q_arg0 = qscriptvalue_cast<QTranslator*>(context->argument(0));
        bool _q_result = QCoreApplication::installTranslator(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QCoreApplication* _q_result = QCoreApplication::instance();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = QCoreApplication::isSetuidAllowed();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QStringList _q_result = QCoreApplication::libraryPaths();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QEvent* _q_arg1 = qscriptvalue_cast<QEvent*>(context->argument(1));
        QCoreApplication::postEvent(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QEvent* _q_arg1 = qscriptvalue_cast<QEvent*>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QCoreApplication::postEvent(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QCoreApplication::processEvents();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QFlags<QEventLoop::ProcessEventsFlag> _q_arg0 = qscriptvalue_cast<QFlags<QEventLoop::ProcessEventsFlag> >(context->argument(0));
        QCoreApplication::processEvents(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QFlags<QEventLoop::ProcessEventsFlag> _q_arg0 = qscriptvalue_cast<QFlags<QEventLoop::ProcessEventsFlag> >(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QCoreApplication::processEvents(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QCoreApplication::removeLibraryPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QCoreApplication::removePostedEvents(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        int _q_arg1 = context->argument(1).toInt32();
        QCoreApplication::removePostedEvents(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QTranslator* _q_arg0 = qscriptvalue_cast<QTranslator*>(context->argument(0));
        bool _q_result = QCoreApplication::removeTranslator(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QEvent* _q_arg1 = qscriptvalue_cast<QEvent*>(context->argument(1));
        bool _q_result = QCoreApplication::sendEvent(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QCoreApplication::sendPostedEvents();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QCoreApplication::sendPostedEvents(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        int _q_arg1 = context->argument(1).toInt32();
        QCoreApplication::sendPostedEvents(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        Qt::ApplicationAttribute _q_arg0 = qscriptvalue_cast<Qt::ApplicationAttribute>(context->argument(0));
        QCoreApplication::setAttribute(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        Qt::ApplicationAttribute _q_arg0 = qscriptvalue_cast<Qt::ApplicationAttribute>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        QCoreApplication::setAttribute(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QCoreApplication::setLibraryPaths(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QCoreApplication::setSetuidAllowed(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        bool _q_result = QCoreApplication::startingUp();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        Qt::ApplicationAttribute _q_arg0 = qscriptvalue_cast<Qt::ApplicationAttribute>(context->argument(0));
        bool _q_result = QCoreApplication::testAttribute(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 2) {
        const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
        const char* _q_arg1 = qscriptvalue_cast<const char*>(context->argument(1));
        QString _q_result = QCoreApplication::translate(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
        const char* _q_arg1 = qscriptvalue_cast<const char*>(context->argument(1));
        const char* _q_arg2 = qscriptvalue_cast<const char*>(context->argument(2));
        QString _q_result = QCoreApplication::translate(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
        const char* _q_arg1 = qscriptvalue_cast<const char*>(context->argument(1));
        const char* _q_arg2 = qscriptvalue_cast<const char*>(context->argument(2));
        int _q_arg3 = context->argument(3).toInt32();
        QString _q_result = QCoreApplication::translate(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QCoreApplication_throw_ambiguity_error_helper(context,
        qtscript_QCoreApplication_function_names[_id],
        qtscript_QCoreApplication_function_signatures[_id]);
}

static QScriptValue qtscript_QCoreApplication_toScriptValue(QScriptEngine *engine, QCoreApplication* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QCoreApplication_fromScriptValue(const QScriptValue &value, QCoreApplication* &out)
{
    out = qobject_cast<QCoreApplication*>(value.toQObject());
}

QScriptValue qtscript_create_QCoreApplication_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QCoreApplication*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QCoreApplication*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QCoreApplication_prototype_call, qtscript_QCoreApplication_function_lengths[i+27]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QCoreApplication_function_names[i+27]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QCoreApplication*>(engine, qtscript_QCoreApplication_toScriptValue, 
        qtscript_QCoreApplication_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QCoreApplication_static_call, proto, qtscript_QCoreApplication_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 26; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QCoreApplication_static_call,
            qtscript_QCoreApplication_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QCoreApplication_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
