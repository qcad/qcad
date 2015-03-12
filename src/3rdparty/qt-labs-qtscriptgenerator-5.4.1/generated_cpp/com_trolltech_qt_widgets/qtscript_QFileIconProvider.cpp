#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qfileiconprovider.h>
#include <QVariant>
#include <qfileiconprovider.h>
#include <qfileinfo.h>
#include <qicon.h>

#include "qtscriptshell_QFileIconProvider.h"

static const char * const qtscript_QFileIconProvider_function_names[] = {
    "QFileIconProvider"
    // static
    // prototype
    , "icon"
    , "type"
    , "toString"
};

static const char * const qtscript_QFileIconProvider_function_signatures[] = {
    ""
    // static
    // prototype
    , "IconType type\nQFileInfo info"
    , "QFileInfo info"
""
};

static const int qtscript_QFileIconProvider_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QFileIconProvider_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFileIconProvider::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFileIconProvider*)
Q_DECLARE_METATYPE(QtScriptShell_QFileIconProvider*)
Q_DECLARE_METATYPE(QFileIconProvider::IconType)

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
// QFileIconProvider::IconType
//

static const QFileIconProvider::IconType qtscript_QFileIconProvider_IconType_values[] = {
    QFileIconProvider::Computer
    , QFileIconProvider::Desktop
    , QFileIconProvider::Trashcan
    , QFileIconProvider::Network
    , QFileIconProvider::Drive
    , QFileIconProvider::Folder
    , QFileIconProvider::File
};

static const char * const qtscript_QFileIconProvider_IconType_keys[] = {
    "Computer"
    , "Desktop"
    , "Trashcan"
    , "Network"
    , "Drive"
    , "Folder"
    , "File"
};

static QString qtscript_QFileIconProvider_IconType_toStringHelper(QFileIconProvider::IconType value)
{
    if ((value >= QFileIconProvider::Computer) && (value <= QFileIconProvider::File))
        return qtscript_QFileIconProvider_IconType_keys[static_cast<int>(value)-static_cast<int>(QFileIconProvider::Computer)];
    return QString();
}

static QScriptValue qtscript_QFileIconProvider_IconType_toScriptValue(QScriptEngine *engine, const QFileIconProvider::IconType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFileIconProvider"));
    return clazz.property(qtscript_QFileIconProvider_IconType_toStringHelper(value));
}

static void qtscript_QFileIconProvider_IconType_fromScriptValue(const QScriptValue &value, QFileIconProvider::IconType &out)
{
    out = qvariant_cast<QFileIconProvider::IconType>(value.toVariant());
}

static QScriptValue qtscript_construct_QFileIconProvider_IconType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFileIconProvider::Computer) && (arg <= QFileIconProvider::File))
        return qScriptValueFromValue(engine,  static_cast<QFileIconProvider::IconType>(arg));
    return context->throwError(QString::fromLatin1("IconType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFileIconProvider_IconType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFileIconProvider::IconType value = qscriptvalue_cast<QFileIconProvider::IconType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFileIconProvider_IconType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFileIconProvider::IconType value = qscriptvalue_cast<QFileIconProvider::IconType>(context->thisObject());
    return QScriptValue(engine, qtscript_QFileIconProvider_IconType_toStringHelper(value));
}

static QScriptValue qtscript_create_QFileIconProvider_IconType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFileIconProvider_IconType,
        qtscript_QFileIconProvider_IconType_valueOf, qtscript_QFileIconProvider_IconType_toString);
    qScriptRegisterMetaType<QFileIconProvider::IconType>(engine, qtscript_QFileIconProvider_IconType_toScriptValue,
        qtscript_QFileIconProvider_IconType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFileIconProvider_IconType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFileIconProvider_IconType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFileIconProvider
//

static QScriptValue qtscript_QFileIconProvider_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QFileIconProvider* _q_self = qscriptvalue_cast<QFileIconProvider*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFileIconProvider.%0(): this object is not a QFileIconProvider")
            .arg(qtscript_QFileIconProvider_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QFileIconProvider::IconType>() == context->argument(0).toVariant().userType())) {
            QFileIconProvider::IconType _q_arg0 = qscriptvalue_cast<QFileIconProvider::IconType>(context->argument(0));
            QIcon _q_result = _q_self->icon(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QFileInfo>() == context->argument(0).toVariant().userType())) {
            QFileInfo _q_arg0 = qscriptvalue_cast<QFileInfo>(context->argument(0));
            QIcon _q_result = _q_self->icon(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QFileInfo _q_arg0 = qscriptvalue_cast<QFileInfo>(context->argument(0));
        QString _q_result = _q_self->type(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QFileIconProvider");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFileIconProvider_throw_ambiguity_error_helper(context,
        qtscript_QFileIconProvider_function_names[_id+1],
        qtscript_QFileIconProvider_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFileIconProvider_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFileIconProvider(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QFileIconProvider* _q_cpp_result = new QtScriptShell_QFileIconProvider();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QFileIconProvider*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFileIconProvider_throw_ambiguity_error_helper(context,
        qtscript_QFileIconProvider_function_names[_id],
        qtscript_QFileIconProvider_function_signatures[_id]);
}

QScriptValue qtscript_create_QFileIconProvider_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFileIconProvider*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFileIconProvider*)0));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFileIconProvider_prototype_call, qtscript_QFileIconProvider_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFileIconProvider_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QFileIconProvider*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFileIconProvider_static_call, proto, qtscript_QFileIconProvider_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("IconType"),
        qtscript_create_QFileIconProvider_IconType_class(engine, ctor));
    return ctor;
}
