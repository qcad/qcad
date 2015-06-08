#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

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
    , "QObject receiver, QEvent event\nQObject receiver, QEvent event, int priority"
    , "ProcessEventsFlags flags\nProcessEventsFlags flags, int maxtime"
    , "String arg__1"
    , "QObject receiver\nQObject receiver, int eventType"
    , "QTranslator messageFile"
    , "QObject receiver, QEvent event"
    , "\nQObject receiver, int event_type"
    , "ApplicationAttribute attribute, bool on"
    , "List arg__1"
    , ""
    , "ApplicationAttribute attribute"
    , "char context, char key, char disambiguation, Encoding encoding\nchar context, char key, char disambiguation, Encoding encoding, int n"
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
    , 3
    , 2
    , 1
    , 2
    , 1
    , 2
    , 2
    , 2
    , 1
    , 0
    , 1
    , 5
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
Q_DECLARE_METATYPE(QCoreApplication::Encoding)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QTranslator*)
Q_DECLARE_METATYPE(QFlags<QEventLoop::ProcessEventsFlag>)
Q_DECLARE_METATYPE(Qt::ApplicationAttribute)
Q_DECLARE_METATYPE(char**)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QCoreApplication::Encoding
//

static const QCoreApplication::Encoding qtscript_QCoreApplication_Encoding_values[] = {
    QCoreApplication::CodecForTr
    , QCoreApplication::UnicodeUTF8
};

static const char * const qtscript_QCoreApplication_Encoding_keys[] = {
    "CodecForTr"
    , "UnicodeUTF8"
};

static QString qtscript_QCoreApplication_Encoding_toStringHelper(QCoreApplication::Encoding value)
{
    if ((value >= QCoreApplication::CodecForTr) && (value <= QCoreApplication::UnicodeUTF8))
        return qtscript_QCoreApplication_Encoding_keys[static_cast<int>(value)-static_cast<int>(QCoreApplication::CodecForTr)];
    return QString();
}

static QScriptValue qtscript_QCoreApplication_Encoding_toScriptValue(QScriptEngine *engine, const QCoreApplication::Encoding &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QCoreApplication"));
    return clazz.property(qtscript_QCoreApplication_Encoding_toStringHelper(value));
}

static void qtscript_QCoreApplication_Encoding_fromScriptValue(const QScriptValue &value, QCoreApplication::Encoding &out)
{
    out = qvariant_cast<QCoreApplication::Encoding>(value.toVariant());
}

static QScriptValue qtscript_construct_QCoreApplication_Encoding(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QCoreApplication::CodecForTr) && (arg <= QCoreApplication::UnicodeUTF8))
        return qScriptValueFromValue(engine,  static_cast<QCoreApplication::Encoding>(arg));
    return context->throwError(QString::fromLatin1("Encoding(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QCoreApplication_Encoding_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QCoreApplication::Encoding value = qscriptvalue_cast<QCoreApplication::Encoding>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QCoreApplication_Encoding_toString(QScriptContext *context, QScriptEngine *engine)
{
    QCoreApplication::Encoding value = qscriptvalue_cast<QCoreApplication::Encoding>(context->thisObject());
    return QScriptValue(engine, qtscript_QCoreApplication_Encoding_toStringHelper(value));
}

static QScriptValue qtscript_create_QCoreApplication_Encoding_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QCoreApplication_Encoding,
        qtscript_QCoreApplication_Encoding_valueOf, qtscript_QCoreApplication_Encoding_toString);
    qScriptRegisterMetaType<QCoreApplication::Encoding>(engine, qtscript_QCoreApplication_Encoding_toScriptValue,
        qtscript_QCoreApplication_Encoding_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QCoreApplication_Encoding_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QCoreApplication_Encoding_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

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
            .arg(qtscript_QCoreApplication_function_names[_id+25]));
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
        qtscript_QCoreApplication_function_names[_id+25],
        qtscript_QCoreApplication_function_signatures[_id+25]);
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
        QCoreApplication::installTranslator(_q_arg0);
        return context->engine()->undefinedValue();
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
        QStringList _q_result = QCoreApplication::libraryPaths();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 13:
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

    case 14:
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

    case 15:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QCoreApplication::removeLibraryPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
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

    case 17:
    if (context->argumentCount() == 1) {
        QTranslator* _q_arg0 = qscriptvalue_cast<QTranslator*>(context->argument(0));
        QCoreApplication::removeTranslator(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QEvent* _q_arg1 = qscriptvalue_cast<QEvent*>(context->argument(1));
        bool _q_result = QCoreApplication::sendEvent(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QCoreApplication::sendPostedEvents();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        int _q_arg1 = context->argument(1).toInt32();
        QCoreApplication::sendPostedEvents(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
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

    case 21:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QCoreApplication::setLibraryPaths(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        bool _q_result = QCoreApplication::startingUp();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        Qt::ApplicationAttribute _q_arg0 = qscriptvalue_cast<Qt::ApplicationAttribute>(context->argument(0));
        bool _q_result = QCoreApplication::testAttribute(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 2) {

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg0 = context->argument(0).toString().toLatin1();
          const char * _q_arg0 = tmp__q_arg0.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
        
          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QString _q_result = QCoreApplication::translate(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg0 = context->argument(0).toString().toLatin1();
          const char * _q_arg0 = tmp__q_arg0.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
        
          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
        
          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg2 = context->argument(2).toString().toLatin1();
          const char * _q_arg2 = tmp__q_arg2.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QString _q_result = QCoreApplication::translate(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg0 = context->argument(0).toString().toLatin1();
          const char * _q_arg0 = tmp__q_arg0.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
        
          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
        
          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg2 = context->argument(2).toString().toLatin1();
          const char * _q_arg2 = tmp__q_arg2.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QCoreApplication::Encoding _q_arg3 = qscriptvalue_cast<QCoreApplication::Encoding>(context->argument(3));
        QString _q_result = QCoreApplication::translate(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg0 = context->argument(0).toString().toLatin1();
          const char * _q_arg0 = tmp__q_arg0.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
        
          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
        
          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg2 = context->argument(2).toString().toLatin1();
          const char * _q_arg2 = tmp__q_arg2.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QCoreApplication::Encoding _q_arg3 = qscriptvalue_cast<QCoreApplication::Encoding>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        QString _q_result = QCoreApplication::translate(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
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
        QScriptValue fun = engine->newFunction(qtscript_QCoreApplication_prototype_call, qtscript_QCoreApplication_function_lengths[i+25]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QCoreApplication_function_names[i+25]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QCoreApplication*>(engine, qtscript_QCoreApplication_toScriptValue, 
        qtscript_QCoreApplication_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QCoreApplication_static_call, proto, qtscript_QCoreApplication_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 24; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QCoreApplication_static_call,
            qtscript_QCoreApplication_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QCoreApplication_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Encoding"),
        qtscript_create_QCoreApplication_Encoding_class(engine, ctor));
    return ctor;
}
