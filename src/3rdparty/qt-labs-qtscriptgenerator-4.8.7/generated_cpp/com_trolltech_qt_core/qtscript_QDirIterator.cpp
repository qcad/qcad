#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qdiriterator.h>
#include <QVariant>
#include <qdir.h>
#include <qdiriterator.h>
#include <qfileinfo.h>
#include <qstringlist.h>

#include "qtscriptshell_QDirIterator.h"

static const char * const qtscript_QDirIterator_function_names[] = {
    "QDirIterator"
    // static
    // prototype
    , "fileInfo"
    , "fileName"
    , "filePath"
    , "hasNext"
    , "next"
    , "path"
    , "toString"
};

static const char * const qtscript_QDirIterator_function_signatures[] = {
    "QDir dir, IteratorFlags flags\nString path, Filters filter, IteratorFlags flags\nString path, IteratorFlags flags\nString path, List nameFilters, Filters filters, IteratorFlags flags"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QDirIterator_function_lengths[] = {
    4
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QDirIterator_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDirIterator::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDirIterator*)
Q_DECLARE_METATYPE(QtScriptShell_QDirIterator*)
Q_DECLARE_METATYPE(QDirIterator::IteratorFlag)
Q_DECLARE_METATYPE(QFlags<QDirIterator::IteratorFlag>)
Q_DECLARE_METATYPE(QFileInfo)
Q_DECLARE_METATYPE(QDir)
Q_DECLARE_METATYPE(QFlags<QDir::Filter>)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QDirIterator::IteratorFlag
//

static const QDirIterator::IteratorFlag qtscript_QDirIterator_IteratorFlag_values[] = {
    QDirIterator::NoIteratorFlags
    , QDirIterator::FollowSymlinks
    , QDirIterator::Subdirectories
};

static const char * const qtscript_QDirIterator_IteratorFlag_keys[] = {
    "NoIteratorFlags"
    , "FollowSymlinks"
    , "Subdirectories"
};

static QString qtscript_QDirIterator_IteratorFlag_toStringHelper(QDirIterator::IteratorFlag value)
{
    if ((value >= QDirIterator::NoIteratorFlags) && (value <= QDirIterator::Subdirectories))
        return qtscript_QDirIterator_IteratorFlag_keys[static_cast<int>(value)-static_cast<int>(QDirIterator::NoIteratorFlags)];
    return QString();
}

static QScriptValue qtscript_QDirIterator_IteratorFlag_toScriptValue(QScriptEngine *engine, const QDirIterator::IteratorFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDirIterator"));
    return clazz.property(qtscript_QDirIterator_IteratorFlag_toStringHelper(value));
}

static void qtscript_QDirIterator_IteratorFlag_fromScriptValue(const QScriptValue &value, QDirIterator::IteratorFlag &out)
{
    out = qvariant_cast<QDirIterator::IteratorFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QDirIterator_IteratorFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QDirIterator::NoIteratorFlags) && (arg <= QDirIterator::Subdirectories))
        return qScriptValueFromValue(engine,  static_cast<QDirIterator::IteratorFlag>(arg));
    return context->throwError(QString::fromLatin1("IteratorFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDirIterator_IteratorFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDirIterator::IteratorFlag value = qscriptvalue_cast<QDirIterator::IteratorFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDirIterator_IteratorFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDirIterator::IteratorFlag value = qscriptvalue_cast<QDirIterator::IteratorFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QDirIterator_IteratorFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QDirIterator_IteratorFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDirIterator_IteratorFlag,
        qtscript_QDirIterator_IteratorFlag_valueOf, qtscript_QDirIterator_IteratorFlag_toString);
    qScriptRegisterMetaType<QDirIterator::IteratorFlag>(engine, qtscript_QDirIterator_IteratorFlag_toScriptValue,
        qtscript_QDirIterator_IteratorFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDirIterator_IteratorFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDirIterator_IteratorFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDirIterator::IteratorFlags
//

static QScriptValue qtscript_QDirIterator_IteratorFlags_toScriptValue(QScriptEngine *engine, const QDirIterator::IteratorFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QDirIterator_IteratorFlags_fromScriptValue(const QScriptValue &value, QDirIterator::IteratorFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QDirIterator::IteratorFlags>())
        out = qvariant_cast<QDirIterator::IteratorFlags>(var);
    else if (var.userType() == qMetaTypeId<QDirIterator::IteratorFlag>())
        out = qvariant_cast<QDirIterator::IteratorFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QDirIterator_IteratorFlags(QScriptContext *context, QScriptEngine *engine)
{
    QDirIterator::IteratorFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QDirIterator::IteratorFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QDirIterator::IteratorFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("IteratorFlags(): argument %0 is not of type IteratorFlag").arg(i));
            }
            result |= qvariant_cast<QDirIterator::IteratorFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QDirIterator_IteratorFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDirIterator::IteratorFlags value = qscriptvalue_cast<QDirIterator::IteratorFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDirIterator_IteratorFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDirIterator::IteratorFlags value = qscriptvalue_cast<QDirIterator::IteratorFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QDirIterator_IteratorFlag_values[i]) == qtscript_QDirIterator_IteratorFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QDirIterator_IteratorFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QDirIterator_IteratorFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QDirIterator::IteratorFlags>() == otherObj.value<QDirIterator::IteratorFlags>())));
}

static QScriptValue qtscript_create_QDirIterator_IteratorFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QDirIterator_IteratorFlags, qtscript_QDirIterator_IteratorFlags_valueOf,
        qtscript_QDirIterator_IteratorFlags_toString, qtscript_QDirIterator_IteratorFlags_equals);
    qScriptRegisterMetaType<QDirIterator::IteratorFlags>(engine, qtscript_QDirIterator_IteratorFlags_toScriptValue,
        qtscript_QDirIterator_IteratorFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QDirIterator
//

static QScriptValue qtscript_QDirIterator_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 6;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDirIterator* _q_self = qscriptvalue_cast<QDirIterator*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDirIterator.%0(): this object is not a QDirIterator")
            .arg(qtscript_QDirIterator_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QFileInfo _q_result = _q_self->fileInfo();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->filePath();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasNext();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->next();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->path();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QDirIterator");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDirIterator_throw_ambiguity_error_helper(context,
        qtscript_QDirIterator_function_names[_id+1],
        qtscript_QDirIterator_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDirIterator_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDirIterator(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QDir>() == context->argument(0).toVariant().userType())) {
            QDir _q_arg0 = qscriptvalue_cast<QDir>(context->argument(0));
            QtScriptShell_QDirIterator* _q_cpp_result = new QtScriptShell_QDirIterator(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDirIterator*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QDirIterator* _q_cpp_result = new QtScriptShell_QDirIterator(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDirIterator*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QDir>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QFlags<QDirIterator::IteratorFlag> >() == context->argument(1).toVariant().userType())) {
            QDir _q_arg0 = qscriptvalue_cast<QDir>(context->argument(0));
            QFlags<QDirIterator::IteratorFlag> _q_arg1 = qscriptvalue_cast<QFlags<QDirIterator::IteratorFlag> >(context->argument(1));
            QtScriptShell_QDirIterator* _q_cpp_result = new QtScriptShell_QDirIterator(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDirIterator*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QFlags<QDir::Filter> >() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QFlags<QDir::Filter> _q_arg1 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(1));
            QtScriptShell_QDirIterator* _q_cpp_result = new QtScriptShell_QDirIterator(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDirIterator*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QFlags<QDirIterator::IteratorFlag> >() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QFlags<QDirIterator::IteratorFlag> _q_arg1 = qscriptvalue_cast<QFlags<QDirIterator::IteratorFlag> >(context->argument(1));
            QtScriptShell_QDirIterator* _q_cpp_result = new QtScriptShell_QDirIterator(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDirIterator*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isArray()) {
            QString _q_arg0 = context->argument(0).toString();
            QStringList _q_arg1;
            qScriptValueToSequence(context->argument(1), _q_arg1);
            QtScriptShell_QDirIterator* _q_cpp_result = new QtScriptShell_QDirIterator(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDirIterator*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        if (context->argument(0).isString()
            && (qMetaTypeId<QFlags<QDir::Filter> >() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QFlags<QDirIterator::IteratorFlag> >() == context->argument(2).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QFlags<QDir::Filter> _q_arg1 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(1));
            QFlags<QDirIterator::IteratorFlag> _q_arg2 = qscriptvalue_cast<QFlags<QDirIterator::IteratorFlag> >(context->argument(2));
            QtScriptShell_QDirIterator* _q_cpp_result = new QtScriptShell_QDirIterator(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDirIterator*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isArray()
            && (qMetaTypeId<QFlags<QDir::Filter> >() == context->argument(2).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QStringList _q_arg1;
            qScriptValueToSequence(context->argument(1), _q_arg1);
            QFlags<QDir::Filter> _q_arg2 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(2));
            QtScriptShell_QDirIterator* _q_cpp_result = new QtScriptShell_QDirIterator(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDirIterator*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        QFlags<QDir::Filter> _q_arg2 = qscriptvalue_cast<QFlags<QDir::Filter> >(context->argument(2));
        QFlags<QDirIterator::IteratorFlag> _q_arg3 = qscriptvalue_cast<QFlags<QDirIterator::IteratorFlag> >(context->argument(3));
        QtScriptShell_QDirIterator* _q_cpp_result = new QtScriptShell_QDirIterator(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QDirIterator*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDirIterator_throw_ambiguity_error_helper(context,
        qtscript_QDirIterator_function_names[_id],
        qtscript_QDirIterator_function_signatures[_id]);
}

QScriptValue qtscript_create_QDirIterator_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDirIterator*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDirIterator*)0));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDirIterator_prototype_call, qtscript_QDirIterator_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDirIterator_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDirIterator*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDirIterator_static_call, proto, qtscript_QDirIterator_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("IteratorFlag"),
        qtscript_create_QDirIterator_IteratorFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("IteratorFlags"),
        qtscript_create_QDirIterator_IteratorFlags_class(engine));
    return ctor;
}
