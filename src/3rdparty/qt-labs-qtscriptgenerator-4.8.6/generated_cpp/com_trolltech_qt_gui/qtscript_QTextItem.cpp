#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpaintengine.h>
#include <QVariant>
#include <qfont.h>

#include "qtscriptshell_QTextItem.h"

static const char * const qtscript_QTextItem_function_names[] = {
    "QTextItem"
    // static
    // prototype
    , "ascent"
    , "descent"
    , "font"
    , "renderFlags"
    , "text"
    , "width"
    , "toString"
};

static const char * const qtscript_QTextItem_function_signatures[] = {
    ""
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

static const int qtscript_QTextItem_function_lengths[] = {
    0
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

static QScriptValue qtscript_QTextItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextItem*)
Q_DECLARE_METATYPE(QtScriptShell_QTextItem*)
Q_DECLARE_METATYPE(QTextItem::RenderFlag)
Q_DECLARE_METATYPE(QFlags<QTextItem::RenderFlag>)

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
// QTextItem::RenderFlag
//

static const QTextItem::RenderFlag qtscript_QTextItem_RenderFlag_values[] = {
    QTextItem::Dummy
    , QTextItem::RightToLeft
    , QTextItem::Overline
    , QTextItem::Underline
    , QTextItem::StrikeOut
};

static const char * const qtscript_QTextItem_RenderFlag_keys[] = {
    "Dummy"
    , "RightToLeft"
    , "Overline"
    , "Underline"
    , "StrikeOut"
};

static QString qtscript_QTextItem_RenderFlag_toStringHelper(QTextItem::RenderFlag value)
{
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QTextItem_RenderFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QTextItem_RenderFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QTextItem_RenderFlag_toScriptValue(QScriptEngine *engine, const QTextItem::RenderFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextItem"));
    return clazz.property(qtscript_QTextItem_RenderFlag_toStringHelper(value));
}

static void qtscript_QTextItem_RenderFlag_fromScriptValue(const QScriptValue &value, QTextItem::RenderFlag &out)
{
    out = qvariant_cast<QTextItem::RenderFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextItem_RenderFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QTextItem_RenderFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QTextItem::RenderFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("RenderFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextItem_RenderFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextItem::RenderFlag value = qscriptvalue_cast<QTextItem::RenderFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextItem_RenderFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextItem::RenderFlag value = qscriptvalue_cast<QTextItem::RenderFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextItem_RenderFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextItem_RenderFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextItem_RenderFlag,
        qtscript_QTextItem_RenderFlag_valueOf, qtscript_QTextItem_RenderFlag_toString);
    qScriptRegisterMetaType<QTextItem::RenderFlag>(engine, qtscript_QTextItem_RenderFlag_toScriptValue,
        qtscript_QTextItem_RenderFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextItem_RenderFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextItem_RenderFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextItem::RenderFlags
//

static QScriptValue qtscript_QTextItem_RenderFlags_toScriptValue(QScriptEngine *engine, const QTextItem::RenderFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QTextItem_RenderFlags_fromScriptValue(const QScriptValue &value, QTextItem::RenderFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QTextItem::RenderFlags>())
        out = qvariant_cast<QTextItem::RenderFlags>(var);
    else if (var.userType() == qMetaTypeId<QTextItem::RenderFlag>())
        out = qvariant_cast<QTextItem::RenderFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QTextItem_RenderFlags(QScriptContext *context, QScriptEngine *engine)
{
    QTextItem::RenderFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QTextItem::RenderFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QTextItem::RenderFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("RenderFlags(): argument %0 is not of type RenderFlag").arg(i));
            }
            result |= qvariant_cast<QTextItem::RenderFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QTextItem_RenderFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextItem::RenderFlags value = qscriptvalue_cast<QTextItem::RenderFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextItem_RenderFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextItem::RenderFlags value = qscriptvalue_cast<QTextItem::RenderFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 5; ++i) {
        if ((value & qtscript_QTextItem_RenderFlag_values[i]) == qtscript_QTextItem_RenderFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QTextItem_RenderFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QTextItem_RenderFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QTextItem::RenderFlags>() == otherObj.value<QTextItem::RenderFlags>())));
}

static QScriptValue qtscript_create_QTextItem_RenderFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QTextItem_RenderFlags, qtscript_QTextItem_RenderFlags_valueOf,
        qtscript_QTextItem_RenderFlags_toString, qtscript_QTextItem_RenderFlags_equals);
    qScriptRegisterMetaType<QTextItem::RenderFlags>(engine, qtscript_QTextItem_RenderFlags_toScriptValue,
        qtscript_QTextItem_RenderFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QTextItem
//

static QScriptValue qtscript_QTextItem_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTextItem* _q_self = qscriptvalue_cast<QTextItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextItem.%0(): this object is not a QTextItem")
            .arg(qtscript_QTextItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->ascent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->descent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QFont _q_result = _q_self->font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QFlags<QTextItem::RenderFlag> _q_result = _q_self->renderFlags();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->width();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QTextItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextItem_throw_ambiguity_error_helper(context,
        qtscript_QTextItem_function_names[_id+1],
        qtscript_QTextItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTextItem* _q_cpp_result = new QtScriptShell_QTextItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTextItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextItem_throw_ambiguity_error_helper(context,
        qtscript_QTextItem_function_names[_id],
        qtscript_QTextItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextItem*)0));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextItem_prototype_call, qtscript_QTextItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextItem_static_call, proto, qtscript_QTextItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("RenderFlag"),
        qtscript_create_QTextItem_RenderFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("RenderFlags"),
        qtscript_create_QTextItem_RenderFlags_class(engine));
    return ctor;
}
