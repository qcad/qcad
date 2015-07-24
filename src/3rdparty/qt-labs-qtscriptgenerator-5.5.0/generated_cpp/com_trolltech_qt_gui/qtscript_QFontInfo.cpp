#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qfontinfo.h>
#include <QVariant>
#include <qfont.h>
#include <qfontinfo.h>

static const char * const qtscript_QFontInfo_function_names[] = {
    "QFontInfo"
    // static
    // prototype
    , "bold"
    , "exactMatch"
    , "family"
    , "fixedPitch"
    , "italic"
    , "overline"
    , "pixelSize"
    , "pointSize"
    , "pointSizeF"
    , "rawMode"
    , "strikeOut"
    , "style"
    , "styleHint"
    , "styleName"
    , "swap"
    , "underline"
    , "weight"
    , "toString"
};

static const char * const qtscript_QFontInfo_function_signatures[] = {
    "QFont arg__1\nQFontInfo arg__1"
    // static
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
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QFontInfo other"
    , ""
    , ""
""
};

static const int qtscript_QFontInfo_function_lengths[] = {
    1
    // static
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
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QFontInfo_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFontInfo::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFontInfo*)
Q_DECLARE_METATYPE(QFont::Style)
Q_DECLARE_METATYPE(QFont::StyleHint)

//
// QFontInfo
//

static QScriptValue qtscript_QFontInfo_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 17;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QFontInfo* _q_self = qscriptvalue_cast<QFontInfo*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFontInfo.%0(): this object is not a QFontInfo")
            .arg(qtscript_QFontInfo_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->bold();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->exactMatch();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->family();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fixedPitch();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->italic();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->overline();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->pixelSize();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->pointSize();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->pointSizeF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->rawMode();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->strikeOut();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QFont::Style _q_result = _q_self->style();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QFont::StyleHint _q_result = _q_self->styleHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->styleName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
//        QFontInfo _q_arg0 = qscriptvalue_cast<QFontInfo>(context->argument(0));
//        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->underline();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->weight();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17: {
    QString result = QString::fromLatin1("QFontInfo");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFontInfo_throw_ambiguity_error_helper(context,
        qtscript_QFontInfo_function_names[_id+1],
        qtscript_QFontInfo_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFontInfo_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFontInfo(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QFont>() == context->argument(0).toVariant().userType())) {
            QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
            QFontInfo* _q_cpp_result = new QFontInfo(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (qscriptvalue_cast<QFontInfo*>(context->argument(0))) {

        QFontInfo & _q_arg0 = *qscriptvalue_cast<QFontInfo*>(context->argument(0));
                    QFontInfo* _q_cpp_result = new QFontInfo(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFontInfo_throw_ambiguity_error_helper(context,
        qtscript_QFontInfo_function_names[_id],
        qtscript_QFontInfo_function_signatures[_id]);
}

QScriptValue qtscript_create_QFontInfo_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFontInfo*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFontInfo*)0));
    for (int i = 0; i < 18; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFontInfo_prototype_call, qtscript_QFontInfo_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFontInfo_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QFontInfo*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFontInfo_static_call, proto, qtscript_QFontInfo_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
