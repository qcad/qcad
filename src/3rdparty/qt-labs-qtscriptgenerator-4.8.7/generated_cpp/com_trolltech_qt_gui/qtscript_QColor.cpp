#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qcolor.h>
#include <QVariant>
#include <qcolor.h>
#include <qdatastream.h>
#include <qstringlist.h>

static const char * const qtscript_QColor_function_names[] = {
    "QColor"
    // static
    , "colorNames"
    , "fromCmyk"
    , "fromCmykF"
    , "fromHsl"
    , "fromHslF"
    , "fromHsv"
    , "fromHsvF"
    , "fromRgb"
    , "fromRgbF"
    , "fromRgba"
    , "isValidColor"
    // prototype
    , "alpha"
    , "alphaF"
    , "black"
    , "blackF"
    , "blue"
    , "blueF"
    , "convertTo"
    , "cyan"
    , "cyanF"
    , "darker"
    , "getHsl"
    , "getHslF"
    , "green"
    , "greenF"
    , "hslHue"
    , "hslHueF"
    , "hslSaturation"
    , "hslSaturationF"
    , "hsvHue"
    , "hsvHueF"
    , "hsvSaturation"
    , "hsvSaturationF"
    , "hue"
    , "hueF"
    , "isValid"
    , "lighter"
    , "lightness"
    , "lightnessF"
    , "magenta"
    , "magentaF"
    , "name"
    , "equals"
    , "readFrom"
    , "red"
    , "redF"
    , "rgb"
    , "rgba"
    , "saturation"
    , "saturationF"
    , "setAlpha"
    , "setAlphaF"
    , "setBlue"
    , "setBlueF"
    , "setCmyk"
    , "setCmykF"
    , "setGreen"
    , "setGreenF"
    , "setHsl"
    , "setHslF"
    , "setHsv"
    , "setHsvF"
    , "setNamedColor"
    , "setRed"
    , "setRedF"
    , "setRgb"
    , "setRgbF"
    , "setRgba"
    , "spec"
    , "toCmyk"
    , "toHsl"
    , "toHsv"
    , "toRgb"
    , "value"
    , "valueF"
    , "writeTo"
    , "yellow"
    , "yellowF"
    , "toString"
};

static const char * const qtscript_QColor_function_signatures[] = {
    "\nGlobalColor color\nQColor color\nString name\nint r, int g, int b, int a\nunsigned int rgb"
    // static
    , ""
    , "int c, int m, int y, int k, int a"
    , "qreal c, qreal m, qreal y, qreal k, qreal a"
    , "int h, int s, int l, int a"
    , "qreal h, qreal s, qreal l, qreal a"
    , "int h, int s, int v, int a"
    , "qreal h, qreal s, qreal v, qreal a"
    , "int r, int g, int b, int a\nunsigned int rgb"
    , "qreal r, qreal g, qreal b, qreal a"
    , "unsigned int rgba"
    , "String name"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "Spec colorSpec"
    , ""
    , ""
    , "int f"
    , "int h, int s, int l, int a"
    , "qreal h, qreal s, qreal l, qreal a"
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
    , "int f"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QColor c"
    , "QDataStream arg__1"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int alpha"
    , "qreal alpha"
    , "int blue"
    , "qreal blue"
    , "int c, int m, int y, int k, int a"
    , "qreal c, qreal m, qreal y, qreal k, qreal a"
    , "int green"
    , "qreal green"
    , "int h, int s, int l, int a"
    , "qreal h, qreal s, qreal l, qreal a"
    , "int h, int s, int v, int a"
    , "qreal h, qreal s, qreal v, qreal a"
    , "String name"
    , "int red"
    , "qreal red"
    , "int r, int g, int b, int a\nunsigned int rgb"
    , "qreal r, qreal g, qreal b, qreal a"
    , "unsigned int rgba"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QDataStream arg__1"
    , ""
    , ""
""
};

static const int qtscript_QColor_function_lengths[] = {
    4
    // static
    , 0
    , 5
    , 5
    , 4
    , 4
    , 4
    , 4
    , 4
    , 4
    , 1
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 4
    , 4
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
    , 0
    , 0
    , 1
    , 1
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
    , 5
    , 5
    , 1
    , 1
    , 4
    , 4
    , 4
    , 4
    , 1
    , 1
    , 1
    , 4
    , 4
    , 1
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

static QScriptValue qtscript_QColor_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QColor::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QColor*)
Q_DECLARE_METATYPE(QColor::Spec)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(qreal*)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(Qt::GlobalColor)

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
// QColor::Spec
//

static const QColor::Spec qtscript_QColor_Spec_values[] = {
    QColor::Invalid
    , QColor::Rgb
    , QColor::Hsv
    , QColor::Cmyk
    , QColor::Hsl
};

static const char * const qtscript_QColor_Spec_keys[] = {
    "Invalid"
    , "Rgb"
    , "Hsv"
    , "Cmyk"
    , "Hsl"
};

static QString qtscript_QColor_Spec_toStringHelper(QColor::Spec value)
{
    if ((value >= QColor::Invalid) && (value <= QColor::Hsl))
        return qtscript_QColor_Spec_keys[static_cast<int>(value)-static_cast<int>(QColor::Invalid)];
    return QString();
}

static QScriptValue qtscript_QColor_Spec_toScriptValue(QScriptEngine *engine, const QColor::Spec &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QColor"));
    return clazz.property(qtscript_QColor_Spec_toStringHelper(value));
}

static void qtscript_QColor_Spec_fromScriptValue(const QScriptValue &value, QColor::Spec &out)
{
    out = qvariant_cast<QColor::Spec>(value.toVariant());
}

static QScriptValue qtscript_construct_QColor_Spec(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QColor::Invalid) && (arg <= QColor::Hsl))
        return qScriptValueFromValue(engine,  static_cast<QColor::Spec>(arg));
    return context->throwError(QString::fromLatin1("Spec(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QColor_Spec_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QColor::Spec value = qscriptvalue_cast<QColor::Spec>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QColor_Spec_toString(QScriptContext *context, QScriptEngine *engine)
{
    QColor::Spec value = qscriptvalue_cast<QColor::Spec>(context->thisObject());
    return QScriptValue(engine, qtscript_QColor_Spec_toStringHelper(value));
}

static QScriptValue qtscript_create_QColor_Spec_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QColor_Spec,
        qtscript_QColor_Spec_valueOf, qtscript_QColor_Spec_toString);
    qScriptRegisterMetaType<QColor::Spec>(engine, qtscript_QColor_Spec_toScriptValue,
        qtscript_QColor_Spec_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QColor_Spec_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QColor_Spec_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QColor
//

static QScriptValue qtscript_QColor_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 67;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QColor* _q_self = qscriptvalue_cast<QColor*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QColor.%0(): this object is not a QColor")
            .arg(qtscript_QColor_function_names[_id+12]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->alpha();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->alphaF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->black();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->blackF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->blue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->blueF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QColor::Spec _q_arg0 = qscriptvalue_cast<QColor::Spec>(context->argument(0));
        QColor _q_result = _q_self->convertTo(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->cyan();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->cyanF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->darker();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QColor _q_result = _q_self->darker(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 3) {
        int* _q_arg0 = qscriptvalue_cast<int*>(context->argument(0));
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
        _q_self->getHsl(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int* _q_arg0 = qscriptvalue_cast<int*>(context->argument(0));
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
        int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
        _q_self->getHsl(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 3) {
        qreal* _q_arg0 = qscriptvalue_cast<qreal*>(context->argument(0));
        qreal* _q_arg1 = qscriptvalue_cast<qreal*>(context->argument(1));
        qreal* _q_arg2 = qscriptvalue_cast<qreal*>(context->argument(2));
        _q_self->getHslF(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal* _q_arg0 = qscriptvalue_cast<qreal*>(context->argument(0));
        qreal* _q_arg1 = qscriptvalue_cast<qreal*>(context->argument(1));
        qreal* _q_arg2 = qscriptvalue_cast<qreal*>(context->argument(2));
        qreal* _q_arg3 = qscriptvalue_cast<qreal*>(context->argument(3));
        _q_self->getHslF(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->green();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->greenF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->hslHue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->hslHueF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->hslSaturation();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->hslSaturationF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->hsvHue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->hsvHueF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->hsvSaturation();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->hsvSaturationF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->hue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->hueF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->lighter();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QColor _q_result = _q_self->lighter(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->lightness();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->lightnessF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->magenta();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->magentaF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->red();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->redF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 0) {
        uint _q_result = _q_self->rgb();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        uint _q_result = _q_self->rgba();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->saturation();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 38:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->saturationF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setAlpha(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setAlphaF(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setBlue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setBlueF(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setCmyk(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        _q_self->setCmyk(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    break;

    case 44:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->setCmykF(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        _q_self->setCmykF(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setGreen(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 46:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setGreenF(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 47:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->setHsl(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setHsl(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 48:
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->setHslF(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->setHslF(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 49:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->setHsv(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setHsv(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 50:
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->setHsvF(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->setHsvF(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 51:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setNamedColor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 52:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setRed(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 53:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setRedF(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 54:
    if (context->argumentCount() == 1) {
        uint _q_arg0 = context->argument(0).toUInt32();
        _q_self->setRgb(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->setRgb(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setRgb(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 55:
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->setRgbF(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->setRgbF(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 56:
    if (context->argumentCount() == 1) {
        uint _q_arg0 = context->argument(0).toUInt32();
        _q_self->setRgba(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 57:
    if (context->argumentCount() == 0) {
        QColor::Spec _q_result = _q_self->spec();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 58:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->toCmyk();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 59:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->toHsl();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 60:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->toHsv();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 61:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->toRgb();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 62:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->value();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 63:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->valueF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 64:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 65:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->yellow();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 66:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->yellowF();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 67: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QColor_throw_ambiguity_error_helper(context,
        qtscript_QColor_function_names[_id+12],
        qtscript_QColor_function_signatures[_id+12]);
}

static QScriptValue qtscript_QColor_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QColor(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QColor _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::GlobalColor>() == context->argument(0).toVariant().userType())) {
            Qt::GlobalColor _q_arg0 = qscriptvalue_cast<Qt::GlobalColor>(context->argument(0));
            QColor _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QColor>() == context->argument(0).toVariant().userType())) {
            QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
            QColor _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QColor _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            uint _q_arg0 = context->argument(0).toUInt32();
            QColor _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QColor _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QColor _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QStringList _q_result = QColor::colorNames();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QColor _q_result = QColor::fromCmyk(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        QColor _q_result = QColor::fromCmyk(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QColor _q_result = QColor::fromCmykF(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        qreal _q_arg4 = qscriptvalue_cast<qreal>(context->argument(4));
        QColor _q_result = QColor::fromCmykF(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QColor _q_result = QColor::fromHsl(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QColor _q_result = QColor::fromHsl(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        QColor _q_result = QColor::fromHslF(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QColor _q_result = QColor::fromHslF(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QColor _q_result = QColor::fromHsv(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QColor _q_result = QColor::fromHsv(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        QColor _q_result = QColor::fromHsvF(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QColor _q_result = QColor::fromHsvF(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        uint _q_arg0 = context->argument(0).toUInt32();
        QColor _q_result = QColor::fromRgb(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QColor _q_result = QColor::fromRgb(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QColor _q_result = QColor::fromRgb(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        QColor _q_result = QColor::fromRgbF(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QColor _q_result = QColor::fromRgbF(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        uint _q_arg0 = context->argument(0).toUInt32();
        QColor _q_result = QColor::fromRgba(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QColor::isValidColor(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QColor_throw_ambiguity_error_helper(context,
        qtscript_QColor_function_names[_id],
        qtscript_QColor_function_signatures[_id]);
}

QScriptValue qtscript_create_QColor_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QColor*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QColor*)0));
    for (int i = 0; i < 68; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QColor_prototype_call, qtscript_QColor_function_lengths[i+12]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QColor_function_names[i+12]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QColor>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QColor*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QColor_static_call, proto, qtscript_QColor_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QColor_static_call,
            qtscript_QColor_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QColor_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Spec"),
        qtscript_create_QColor_Spec_class(engine, ctor));
    return ctor;
}
