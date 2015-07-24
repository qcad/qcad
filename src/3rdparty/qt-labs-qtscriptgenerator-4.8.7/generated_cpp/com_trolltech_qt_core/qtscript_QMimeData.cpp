#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qmimedata.h>
#include <QStringList>
#include <QUrl>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qstringlist.h>
#include <qurl.h>

#include "qtscriptshell_QMimeData.h"

static const char * const qtscript_QMimeData_function_names[] = {
    "QMimeData"
    // static
    // prototype
    , "clear"
    , "colorData"
    , "data"
    , "formats"
    , "hasColor"
    , "hasFormat"
    , "hasHtml"
    , "hasImage"
    , "hasText"
    , "hasUrls"
    , "html"
    , "imageData"
    , "removeFormat"
    , "setColorData"
    , "setData"
    , "setHtml"
    , "setImageData"
    , "setText"
    , "setUrls"
    , "text"
    , "urls"
    , "toString"
};

static const char * const qtscript_QMimeData_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , "String mimetype"
    , ""
    , ""
    , "String mimetype"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String mimetype"
    , "Object color"
    , "String mimetype, QByteArray data"
    , "String html"
    , "Object image"
    , "String text"
    , "List urls"
    , ""
    , ""
""
};

static const int qtscript_QMimeData_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QMimeData_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMimeData::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMimeData*)
Q_DECLARE_METATYPE(QtScriptShell_QMimeData*)
Q_DECLARE_METATYPE(QList<QUrl>)

//
// QMimeData
//

static QScriptValue qtscript_QMimeData_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 21;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QMimeData* _q_self = qscriptvalue_cast<QMimeData*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMimeData.%0(): this object is not a QMimeData")
            .arg(qtscript_QMimeData_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->colorData();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QByteArray _q_result = _q_self->data(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->formats();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasColor();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->hasFormat(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasHtml();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasImage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasUrls();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->html();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->imageData();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->removeFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        _q_self->setColorData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
        _q_self->setData(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setHtml(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        _q_self->setImageData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QList<QUrl> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setUrls(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QList<QUrl> _q_result = _q_self->urls();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 21: {
    QString result = QString::fromLatin1("QMimeData");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMimeData_throw_ambiguity_error_helper(context,
        qtscript_QMimeData_function_names[_id+1],
        qtscript_QMimeData_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMimeData_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMimeData(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QMimeData* _q_cpp_result = new QtScriptShell_QMimeData();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMimeData*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMimeData_throw_ambiguity_error_helper(context,
        qtscript_QMimeData_function_names[_id],
        qtscript_QMimeData_function_signatures[_id]);
}

static QScriptValue qtscript_QMimeData_toScriptValue(QScriptEngine *engine, QMimeData* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QMimeData_fromScriptValue(const QScriptValue &value, QMimeData* &out)
{
    out = qobject_cast<QMimeData*>(value.toQObject());
}

QScriptValue qtscript_create_QMimeData_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMimeData*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMimeData*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 22; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMimeData_prototype_call, qtscript_QMimeData_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMimeData_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QMimeData*>(engine, qtscript_QMimeData_toScriptValue, 
        qtscript_QMimeData_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMimeData_static_call, proto, qtscript_QMimeData_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
