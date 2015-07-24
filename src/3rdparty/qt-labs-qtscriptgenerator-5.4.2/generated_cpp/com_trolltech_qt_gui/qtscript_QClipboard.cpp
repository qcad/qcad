#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qclipboard.h>
#include <QImage>
#include <QPixmap>
#include <QVariant>
#include <qbytearray.h>
#include <qclipboard.h>
#include <qcoreevent.h>
#include <qimage.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qpixmap.h>

static const char * const qtscript_QClipboard_function_names[] = {
    "QClipboard"
    // static
    // prototype
    , "clear"
    , "image"
    , "mimeData"
    , "ownsClipboard"
    , "ownsFindBuffer"
    , "ownsSelection"
    , "pixmap"
    , "setImage"
    , "setMimeData"
    , "setPixmap"
    , "setText"
    , "supportsFindBuffer"
    , "supportsSelection"
    , "text"
    , "toString"
};

static const char * const qtscript_QClipboard_function_signatures[] = {
    ""
    // static
    // prototype
    , "Mode mode"
    , "Mode mode"
    , "Mode mode"
    , ""
    , ""
    , ""
    , "Mode mode"
    , "QImage arg__1, Mode mode"
    , "QMimeData data, Mode mode"
    , "QPixmap arg__1, Mode mode"
    , "String arg__1, Mode mode"
    , ""
    , ""
    , "Mode mode\nString subtype, Mode mode"
""
};

static const int qtscript_QClipboard_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 1
    , 2
    , 2
    , 2
    , 2
    , 0
    , 0
    , 2
    , 0
};

static QScriptValue qtscript_QClipboard_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QClipboard::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QClipboard*)
Q_DECLARE_METATYPE(QClipboard::Mode)
Q_DECLARE_METATYPE(const QMimeData*)
Q_DECLARE_METATYPE(QMimeData*)

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
// QClipboard::Mode
//

static const QClipboard::Mode qtscript_QClipboard_Mode_values[] = {
    QClipboard::Clipboard
    , QClipboard::Selection
    , QClipboard::FindBuffer
};

static const char * const qtscript_QClipboard_Mode_keys[] = {
    "Clipboard"
    , "Selection"
    , "FindBuffer"
};

static QString qtscript_QClipboard_Mode_toStringHelper(QClipboard::Mode value)
{
    if ((value >= QClipboard::Clipboard) && (value <= QClipboard::FindBuffer))
        return qtscript_QClipboard_Mode_keys[static_cast<int>(value)-static_cast<int>(QClipboard::Clipboard)];
    return QString();
}

static QScriptValue qtscript_QClipboard_Mode_toScriptValue(QScriptEngine *engine, const QClipboard::Mode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QClipboard"));
    return clazz.property(qtscript_QClipboard_Mode_toStringHelper(value));
}

static void qtscript_QClipboard_Mode_fromScriptValue(const QScriptValue &value, QClipboard::Mode &out)
{
    out = qvariant_cast<QClipboard::Mode>(value.toVariant());
}

static QScriptValue qtscript_construct_QClipboard_Mode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QClipboard::Clipboard) && (arg <= QClipboard::FindBuffer))
        return qScriptValueFromValue(engine,  static_cast<QClipboard::Mode>(arg));
    return context->throwError(QString::fromLatin1("Mode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QClipboard_Mode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QClipboard::Mode value = qscriptvalue_cast<QClipboard::Mode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QClipboard_Mode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QClipboard::Mode value = qscriptvalue_cast<QClipboard::Mode>(context->thisObject());
    return QScriptValue(engine, qtscript_QClipboard_Mode_toStringHelper(value));
}

static QScriptValue qtscript_create_QClipboard_Mode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QClipboard_Mode,
        qtscript_QClipboard_Mode_valueOf, qtscript_QClipboard_Mode_toString);
    qScriptRegisterMetaType<QClipboard::Mode>(engine, qtscript_QClipboard_Mode_toScriptValue,
        qtscript_QClipboard_Mode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QClipboard_Mode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QClipboard_Mode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QClipboard
//

static QScriptValue qtscript_QClipboard_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 14;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QClipboard* _q_self = qscriptvalue_cast<QClipboard*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QClipboard.%0(): this object is not a QClipboard")
            .arg(qtscript_QClipboard_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QClipboard::Mode _q_arg0 = qscriptvalue_cast<QClipboard::Mode>(context->argument(0));
        _q_self->clear(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->image();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QClipboard::Mode _q_arg0 = qscriptvalue_cast<QClipboard::Mode>(context->argument(0));
        QImage _q_result = _q_self->image(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        const QMimeData* _q_result = const_cast<const QMimeData*>(_q_self->mimeData());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QClipboard::Mode _q_arg0 = qscriptvalue_cast<QClipboard::Mode>(context->argument(0));
        const QMimeData* _q_result = const_cast<const QMimeData*>(_q_self->mimeData(_q_arg0));
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->ownsClipboard();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->ownsFindBuffer();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->ownsSelection();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QPixmap _q_result = _q_self->pixmap();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QClipboard::Mode _q_arg0 = qscriptvalue_cast<QClipboard::Mode>(context->argument(0));
        QPixmap _q_result = _q_self->pixmap(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        _q_self->setImage(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        QClipboard::Mode _q_arg1 = qscriptvalue_cast<QClipboard::Mode>(context->argument(1));
        _q_self->setImage(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QMimeData* _q_arg0 = qscriptvalue_cast<QMimeData*>(context->argument(0));
        _q_self->setMimeData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QMimeData* _q_arg0 = qscriptvalue_cast<QMimeData*>(context->argument(0));
        QClipboard::Mode _q_arg1 = qscriptvalue_cast<QClipboard::Mode>(context->argument(1));
        _q_self->setMimeData(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        _q_self->setPixmap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        QClipboard::Mode _q_arg1 = qscriptvalue_cast<QClipboard::Mode>(context->argument(1));
        _q_self->setPixmap(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QClipboard::Mode _q_arg1 = qscriptvalue_cast<QClipboard::Mode>(context->argument(1));
        _q_self->setText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->supportsFindBuffer();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->supportsSelection();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QClipboard::Mode _q_arg0 = qscriptvalue_cast<QClipboard::Mode>(context->argument(0));
        QString _q_result = _q_self->text(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QClipboard::Mode _q_arg1 = qscriptvalue_cast<QClipboard::Mode>(context->argument(1));
        QString _q_result = _q_self->text(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14: {
    QString result = QString::fromLatin1("QClipboard");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QClipboard_throw_ambiguity_error_helper(context,
        qtscript_QClipboard_function_names[_id+1],
        qtscript_QClipboard_function_signatures[_id+1]);
}

static QScriptValue qtscript_QClipboard_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QClipboard cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QClipboard_throw_ambiguity_error_helper(context,
        qtscript_QClipboard_function_names[_id],
        qtscript_QClipboard_function_signatures[_id]);
}

static QScriptValue qtscript_QClipboard_toScriptValue(QScriptEngine *engine, QClipboard* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QClipboard_fromScriptValue(const QScriptValue &value, QClipboard* &out)
{
    out = qobject_cast<QClipboard*>(value.toQObject());
}

QScriptValue qtscript_create_QClipboard_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QClipboard*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QClipboard*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QClipboard_prototype_call, qtscript_QClipboard_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QClipboard_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QClipboard*>(engine, qtscript_QClipboard_toScriptValue, 
        qtscript_QClipboard_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QClipboard_static_call, proto, qtscript_QClipboard_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Mode"),
        qtscript_create_QClipboard_Mode_class(engine, ctor));
    return ctor;
}
