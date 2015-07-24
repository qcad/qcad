#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpicture.h>
#include <QVariant>
#include <qbytearray.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qpicture.h>

static const char * const qtscript_QPictureIO_function_names[] = {
    "QPictureIO"
    // static
    , "inputFormats"
    , "outputFormats"
    , "pictureFormat"
    // prototype
    , "description"
    , "fileName"
    , "format_private"
    , "gamma"
    , "ioDevice"
    , "parameters_private"
    , "picture"
    , "quality"
    , "read"
    , "setDescription"
    , "setFileName"
    , "setFormat"
    , "setGamma"
    , "setIODevice"
    , "setParameters"
    , "setPicture"
    , "setQuality"
    , "setStatus"
    , "status"
    , "write"
    , "toString"
};

static const char * const qtscript_QPictureIO_function_signatures[] = {
    "\nQIODevice ioDevice, char format\nString fileName, char format"
    // static
    , ""
    , ""
    , "QIODevice arg__1\nString fileName"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String arg__1"
    , "String arg__1"
    , "char arg__1"
    , "float arg__1"
    , "QIODevice arg__1"
    , "char arg__1"
    , "QPicture arg__1"
    , "int arg__1"
    , "int arg__1"
    , ""
    , ""
""
};

static const int qtscript_QPictureIO_function_lengths[] = {
    2
    // static
    , 0
    , 0
    , 1
    // prototype
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
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QPictureIO_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPictureIO::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPictureIO*)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QPicture)
Q_DECLARE_METATYPE(QList<QByteArray>)

//
// QPictureIO
//

static QScriptValue qtscript_QPictureIO_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 20;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPictureIO* _q_self = qscriptvalue_cast<QPictureIO*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPictureIO.%0(): this object is not a QPictureIO")
            .arg(qtscript_QPictureIO_function_names[_id+4]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->description();
        return QScriptValue(context->engine(), _q_result);
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
        char* _q_result = const_cast<char*>(_q_self->format());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        float _q_result = _q_self->gamma();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QIODevice* _q_result = _q_self->ioDevice();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        char* _q_result = const_cast<char*>(_q_self->parameters());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QPicture _q_result = _q_self->picture();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->quality();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->read();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setDescription(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setFileName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg0 = context->argument(0).toString().toLatin1();
          const char * _q_arg0 = tmp__q_arg0.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                _q_self->setFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        float _q_arg0 = qscriptvalue_cast<float>(context->argument(0));
        _q_self->setGamma(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        _q_self->setIODevice(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg0 = context->argument(0).toString().toLatin1();
          const char * _q_arg0 = tmp__q_arg0.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                _q_self->setParameters(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QPicture _q_arg0 = qscriptvalue_cast<QPicture>(context->argument(0));
        _q_self->setPicture(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setQuality(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setStatus(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->status();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->write();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20: {
    QString result = QString::fromLatin1("QPictureIO");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPictureIO_throw_ambiguity_error_helper(context,
        qtscript_QPictureIO_function_names[_id+4],
        qtscript_QPictureIO_function_signatures[_id+4]);
}

static QScriptValue qtscript_QPictureIO_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPictureIO(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QPictureIO* _q_cpp_result = new QPictureIO();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))
            && context->argument(1).isString()) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    QPictureIO* _q_cpp_result = new QPictureIO(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    QPictureIO* _q_cpp_result = new QPictureIO(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<QByteArray> _q_result = QPictureIO::inputFormats();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QList<QByteArray> _q_result = QPictureIO::outputFormats();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QIODevice*>(context->argument(0))) {
            QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
            QByteArray _q_result = QPictureIO::pictureFormat(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QByteArray _q_result = QPictureIO::pictureFormat(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPictureIO_throw_ambiguity_error_helper(context,
        qtscript_QPictureIO_function_names[_id],
        qtscript_QPictureIO_function_signatures[_id]);
}

QScriptValue qtscript_create_QPictureIO_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPictureIO*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPictureIO*)0));
    for (int i = 0; i < 21; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPictureIO_prototype_call, qtscript_QPictureIO_function_lengths[i+4]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPictureIO_function_names[i+4]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPictureIO*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPictureIO_static_call, proto, qtscript_QPictureIO_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPictureIO_static_call,
            qtscript_QPictureIO_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QPictureIO_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
