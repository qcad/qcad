#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qdesktopservices.h>
#include <QVariant>
#include <qobject.h>
#include <qurl.h>

#include "qtscriptshell_QDesktopServices.h"

static const char * const qtscript_QDesktopServices_function_names[] = {
    "QDesktopServices"
    // static
    , "displayName"
    , "openUrl"
    , "setUrlHandler"
    , "storageLocation"
    , "unsetUrlHandler"
    // prototype
    , "toString"
};

static const char * const qtscript_QDesktopServices_function_signatures[] = {
    ""
    // static
    , "StandardLocation type"
    , "QUrl url"
    , "String scheme, QObject receiver, char method"
    , "StandardLocation type"
    , "String scheme"
    // prototype
""
};

static const int qtscript_QDesktopServices_function_lengths[] = {
    0
    // static
    , 1
    , 1
    , 3
    , 1
    , 1
    // prototype
    , 0
};

static QScriptValue qtscript_QDesktopServices_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDesktopServices::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDesktopServices*)
Q_DECLARE_METATYPE(QtScriptShell_QDesktopServices*)
Q_DECLARE_METATYPE(QDesktopServices::StandardLocation)
Q_DECLARE_METATYPE(char*)

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
// QDesktopServices::StandardLocation
//

static const QDesktopServices::StandardLocation qtscript_QDesktopServices_StandardLocation_values[] = {
    QDesktopServices::DesktopLocation
    , QDesktopServices::DocumentsLocation
    , QDesktopServices::FontsLocation
    , QDesktopServices::ApplicationsLocation
    , QDesktopServices::MusicLocation
    , QDesktopServices::MoviesLocation
    , QDesktopServices::PicturesLocation
    , QDesktopServices::TempLocation
    , QDesktopServices::HomeLocation
    , QDesktopServices::DataLocation
    , QDesktopServices::CacheLocation
};

static const char * const qtscript_QDesktopServices_StandardLocation_keys[] = {
    "DesktopLocation"
    , "DocumentsLocation"
    , "FontsLocation"
    , "ApplicationsLocation"
    , "MusicLocation"
    , "MoviesLocation"
    , "PicturesLocation"
    , "TempLocation"
    , "HomeLocation"
    , "DataLocation"
    , "CacheLocation"
};

static QString qtscript_QDesktopServices_StandardLocation_toStringHelper(QDesktopServices::StandardLocation value)
{
    if ((value >= QDesktopServices::DesktopLocation) && (value <= QDesktopServices::CacheLocation))
        return qtscript_QDesktopServices_StandardLocation_keys[static_cast<int>(value)-static_cast<int>(QDesktopServices::DesktopLocation)];
    return QString();
}

static QScriptValue qtscript_QDesktopServices_StandardLocation_toScriptValue(QScriptEngine *engine, const QDesktopServices::StandardLocation &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDesktopServices"));
    return clazz.property(qtscript_QDesktopServices_StandardLocation_toStringHelper(value));
}

static void qtscript_QDesktopServices_StandardLocation_fromScriptValue(const QScriptValue &value, QDesktopServices::StandardLocation &out)
{
    out = qvariant_cast<QDesktopServices::StandardLocation>(value.toVariant());
}

static QScriptValue qtscript_construct_QDesktopServices_StandardLocation(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QDesktopServices::DesktopLocation) && (arg <= QDesktopServices::CacheLocation))
        return qScriptValueFromValue(engine,  static_cast<QDesktopServices::StandardLocation>(arg));
    return context->throwError(QString::fromLatin1("StandardLocation(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDesktopServices_StandardLocation_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDesktopServices::StandardLocation value = qscriptvalue_cast<QDesktopServices::StandardLocation>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDesktopServices_StandardLocation_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDesktopServices::StandardLocation value = qscriptvalue_cast<QDesktopServices::StandardLocation>(context->thisObject());
    return QScriptValue(engine, qtscript_QDesktopServices_StandardLocation_toStringHelper(value));
}

static QScriptValue qtscript_create_QDesktopServices_StandardLocation_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDesktopServices_StandardLocation,
        qtscript_QDesktopServices_StandardLocation_valueOf, qtscript_QDesktopServices_StandardLocation_toString);
    qScriptRegisterMetaType<QDesktopServices::StandardLocation>(engine, qtscript_QDesktopServices_StandardLocation_toScriptValue,
        qtscript_QDesktopServices_StandardLocation_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDesktopServices_StandardLocation_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDesktopServices_StandardLocation_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDesktopServices
//

static QScriptValue qtscript_QDesktopServices_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QDesktopServices* _q_self = qscriptvalue_cast<QDesktopServices*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDesktopServices.%0(): this object is not a QDesktopServices")
            .arg(qtscript_QDesktopServices_function_names[_id+6]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QDesktopServices");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDesktopServices_throw_ambiguity_error_helper(context,
        qtscript_QDesktopServices_function_names[_id+6],
        qtscript_QDesktopServices_function_signatures[_id+6]);
}

static QScriptValue qtscript_QDesktopServices_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDesktopServices(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QDesktopServices* _q_cpp_result = new QtScriptShell_QDesktopServices();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDesktopServices*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QDesktopServices::StandardLocation _q_arg0 = qscriptvalue_cast<QDesktopServices::StandardLocation>(context->argument(0));
        QString _q_result = QDesktopServices::displayName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        bool _q_result = QDesktopServices::openUrl(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_arg1 = context->argument(1).toQObject();
        char* _q_arg2 = qscriptvalue_cast<char*>(context->argument(2));
        QDesktopServices::setUrlHandler(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QDesktopServices::StandardLocation _q_arg0 = qscriptvalue_cast<QDesktopServices::StandardLocation>(context->argument(0));
        QString _q_result = QDesktopServices::storageLocation(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDesktopServices::unsetUrlHandler(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDesktopServices_throw_ambiguity_error_helper(context,
        qtscript_QDesktopServices_function_names[_id],
        qtscript_QDesktopServices_function_signatures[_id]);
}

QScriptValue qtscript_create_QDesktopServices_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDesktopServices*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDesktopServices*)0));

    engine->setDefaultPrototype(qMetaTypeId<QDesktopServices*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDesktopServices_static_call, proto, qtscript_QDesktopServices_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDesktopServices_static_call,
            qtscript_QDesktopServices_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QDesktopServices_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("StandardLocation"),
        qtscript_create_QDesktopServices_StandardLocation_class(engine, ctor));
    return ctor;
}
