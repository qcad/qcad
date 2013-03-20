#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtextformat.h>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qfont.h>
#include <qpen.h>
#include <qstringlist.h>
#include <qtextformat.h>
#include <qvector.h>

#include "qtscriptshell_QTextImageFormat.h"

static const char * const qtscript_QTextImageFormat_function_names[] = {
    "QTextImageFormat"
    // static
    // prototype
    , "height"
    , "name"
    , "setHeight"
    , "setName"
    , "setWidth"
    , "width"
    , "toString"
};

static const char * const qtscript_QTextImageFormat_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , "qreal height"
    , "String name"
    , "qreal width"
    , ""
""
};

static const int qtscript_QTextImageFormat_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QTextImageFormat_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextImageFormat::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextImageFormat)
Q_DECLARE_METATYPE(QTextImageFormat*)
Q_DECLARE_METATYPE(QtScriptShell_QTextImageFormat)
Q_DECLARE_METATYPE(QtScriptShell_QTextImageFormat*)
Q_DECLARE_METATYPE(QTextCharFormat*)

//
// QTextImageFormat
//

static QScriptValue qtscript_QTextImageFormat_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTextImageFormat* _q_self = qscriptvalue_cast<QTextImageFormat*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextImageFormat.%0(): this object is not a QTextImageFormat")
            .arg(qtscript_QTextImageFormat_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->height();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setHeight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->width();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QTextImageFormat");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextImageFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextImageFormat_function_names[_id+1],
        qtscript_QTextImageFormat_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextImageFormat_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextImageFormat(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTextImageFormat _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTextImageFormat)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextImageFormat_throw_ambiguity_error_helper(context,
        qtscript_QTextImageFormat_function_names[_id],
        qtscript_QTextImageFormat_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextImageFormat_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextImageFormat*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextImageFormat*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTextCharFormat*>()));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextImageFormat_prototype_call, qtscript_QTextImageFormat_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextImageFormat_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextImageFormat>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextImageFormat*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextImageFormat_static_call, proto, qtscript_QTextImageFormat_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
