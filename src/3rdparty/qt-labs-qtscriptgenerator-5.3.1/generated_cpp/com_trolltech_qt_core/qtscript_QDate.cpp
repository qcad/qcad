#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdatetime.h>
#include <QVariant>
#include <qdatetime.h>

static const char * const qtscript_QDate_function_names[] = {
    "QDate"
    // static
    , "currentDate"
    , "fromJulianDay"
    , "fromString"
    , "isLeapYear"
    , "isValid"
    , "longDayName"
    , "longMonthName"
    , "shortDayName"
    , "shortMonthName"
    // prototype
    , "addDays"
    , "addMonths"
    , "addYears"
    , "day"
    , "dayOfWeek"
    , "dayOfYear"
    , "daysInMonth"
    , "daysInYear"
    , "daysTo"
    , "getDate"
    , "isNull"
    , "isValid"
    , "month"
    , "equals"
    , "operator_less"
    , "setDate"
    , "toJulianDay"
    , "toString"
    , "weekNumber"
    , "year"
};

static const char * const qtscript_QDate_function_signatures[] = {
    "\nint y, int m, int d"
    // static
    , ""
    , "qint64 jd"
    , "String s, DateFormat f\nString s, String format"
    , "int year"
    , "int y, int m, int d"
    , "int weekday, MonthNameType type"
    , "int month, MonthNameType type"
    , "int weekday, MonthNameType type"
    , "int month, MonthNameType type"
    // prototype
    , "qint64 days"
    , "int months"
    , "int years"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QDate arg__1"
    , "int year, int month, int day"
    , ""
    , ""
    , ""
    , "QDate other"
    , "QDate other"
    , "int year, int month, int day"
    , ""
    , "DateFormat f\nString format"
    , "int yearNum"
    , ""
};

static const int qtscript_QDate_function_lengths[] = {
    3
    // static
    , 0
    , 1
    , 2
    , 1
    , 3
    , 2
    , 2
    , 2
    , 2
    // prototype
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 3
    , 0
    , 0
    , 0
    , 1
    , 1
    , 3
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QDate_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDate::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDate*)
Q_DECLARE_METATYPE(QDate::MonthNameType)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(Qt::DateFormat)

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
// QDate::MonthNameType
//

static const QDate::MonthNameType qtscript_QDate_MonthNameType_values[] = {
    QDate::DateFormat
    , QDate::StandaloneFormat
};

static const char * const qtscript_QDate_MonthNameType_keys[] = {
    "DateFormat"
    , "StandaloneFormat"
};

static QString qtscript_QDate_MonthNameType_toStringHelper(QDate::MonthNameType value)
{
    if ((value >= QDate::DateFormat) && (value <= QDate::StandaloneFormat))
        return qtscript_QDate_MonthNameType_keys[static_cast<int>(value)-static_cast<int>(QDate::DateFormat)];
    return QString();
}

static QScriptValue qtscript_QDate_MonthNameType_toScriptValue(QScriptEngine *engine, const QDate::MonthNameType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDate"));
    return clazz.property(qtscript_QDate_MonthNameType_toStringHelper(value));
}

static void qtscript_QDate_MonthNameType_fromScriptValue(const QScriptValue &value, QDate::MonthNameType &out)
{
    out = qvariant_cast<QDate::MonthNameType>(value.toVariant());
}

static QScriptValue qtscript_construct_QDate_MonthNameType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QDate::DateFormat) && (arg <= QDate::StandaloneFormat))
        return qScriptValueFromValue(engine,  static_cast<QDate::MonthNameType>(arg));
    return context->throwError(QString::fromLatin1("MonthNameType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDate_MonthNameType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDate::MonthNameType value = qscriptvalue_cast<QDate::MonthNameType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDate_MonthNameType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDate::MonthNameType value = qscriptvalue_cast<QDate::MonthNameType>(context->thisObject());
    return QScriptValue(engine, qtscript_QDate_MonthNameType_toStringHelper(value));
}

static QScriptValue qtscript_create_QDate_MonthNameType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDate_MonthNameType,
        qtscript_QDate_MonthNameType_valueOf, qtscript_QDate_MonthNameType_toString);
    qScriptRegisterMetaType<QDate::MonthNameType>(engine, qtscript_QDate_MonthNameType_toScriptValue,
        qtscript_QDate_MonthNameType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDate_MonthNameType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDate_MonthNameType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDate
//

static QScriptValue qtscript_QDate_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QDate* _q_self = qscriptvalue_cast<QDate*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDate.%0(): this object is not a QDate")
            .arg(qtscript_QDate_function_names[_id+10]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        QDate _q_result = _q_self->addDays(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QDate _q_result = _q_self->addMonths(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QDate _q_result = _q_self->addYears(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->day();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->dayOfWeek();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->dayOfYear();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->daysInMonth();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->daysInYear();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QDate _q_arg0 = qscriptvalue_cast<QDate>(context->argument(0));
        qint64 _q_result = _q_self->daysTo(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 3) {
        int* _q_arg0 = qscriptvalue_cast<int*>(context->argument(0));
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
        _q_self->getDate(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->month();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QDate _q_arg0 = qscriptvalue_cast<QDate>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QDate _q_arg0 = qscriptvalue_cast<QDate>(context->argument(0));
        bool _q_result = _q_self->operator<(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        bool _q_result = _q_self->setDate(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->toJulianDay();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toString();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::DateFormat>() == context->argument(0).toVariant().userType())) {
            Qt::DateFormat _q_arg0 = qscriptvalue_cast<Qt::DateFormat>(context->argument(0));
            QString _q_result = _q_self->toString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_result = _q_self->toString(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->weekNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int* _q_arg0 = qscriptvalue_cast<int*>(context->argument(0));
        int _q_result = _q_self->weekNumber(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->year();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDate_throw_ambiguity_error_helper(context,
        qtscript_QDate_function_names[_id+10],
        qtscript_QDate_function_signatures[_id+10]);
}

static QScriptValue qtscript_QDate_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDate(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QDate _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QDate _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QDate _q_result = QDate::currentDate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        QDate _q_result = QDate::fromJulianDay(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QDate _q_result = QDate::fromString(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && (qMetaTypeId<Qt::DateFormat>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            Qt::DateFormat _q_arg1 = qscriptvalue_cast<Qt::DateFormat>(context->argument(1));
            QDate _q_result = QDate::fromString(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QDate _q_result = QDate::fromString(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = QDate::isLeapYear(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        bool _q_result = QDate::isValid(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = QDate::longDayName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QDate::MonthNameType _q_arg1 = qscriptvalue_cast<QDate::MonthNameType>(context->argument(1));
        QString _q_result = QDate::longDayName(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = QDate::longMonthName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QDate::MonthNameType _q_arg1 = qscriptvalue_cast<QDate::MonthNameType>(context->argument(1));
        QString _q_result = QDate::longMonthName(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = QDate::shortDayName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QDate::MonthNameType _q_arg1 = qscriptvalue_cast<QDate::MonthNameType>(context->argument(1));
        QString _q_result = QDate::shortDayName(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = QDate::shortMonthName(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QDate::MonthNameType _q_arg1 = qscriptvalue_cast<QDate::MonthNameType>(context->argument(1));
        QString _q_result = QDate::shortMonthName(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDate_throw_ambiguity_error_helper(context,
        qtscript_QDate_function_names[_id],
        qtscript_QDate_function_signatures[_id]);
}

QScriptValue qtscript_create_QDate_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDate*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDate*)0));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDate_prototype_call, qtscript_QDate_function_lengths[i+10]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDate_function_names[i+10]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDate>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QDate*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDate_static_call, proto, qtscript_QDate_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDate_static_call,
            qtscript_QDate_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QDate_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("MonthNameType"),
        qtscript_create_QDate_MonthNameType_class(engine, ctor));
    return ctor;
}
