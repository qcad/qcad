#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qbrush.h>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qpair.h>
#include <qvector.h>

static const char * const qtscript_QGradient_function_names[] = {
    "QGradient"
    // static
    // prototype
    , "coordinateMode"
    , "equals"
    , "setColorAt"
    , "setCoordinateMode"
    , "setSpread"
    , "setStops"
    , "spread"
    , "stops"
    , "type"
    , "toString"
};

static const char * const qtscript_QGradient_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , "QGradient gradient"
    , "qreal pos, QColor color"
    , "CoordinateMode mode"
    , "Spread spread"
    , "List stops"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QGradient_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 1
    , 2
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QGradient_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGradient::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QGradient_metaObject()
{
    return &QGradient::staticMetaObject;
}

Q_DECLARE_METATYPE(QGradient)
Q_DECLARE_METATYPE(QGradient*)
Q_DECLARE_METATYPE(QGradient::Type)
Q_DECLARE_METATYPE(QGradient::Spread)
Q_DECLARE_METATYPE(QGradient::CoordinateMode)
template <> \
struct QMetaTypeId< QPair<qreal,QColor > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QPair<qreal,QColor > >("QPair<qreal,QColor >")); \
        return metatype_id.load(); \
    } \
};
template <> \
struct QMetaTypeId< QVector<QPair<qreal,QColor > > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QVector<QPair<qreal,QColor > > >("QVector<QPair<qreal,QColor > >")); \
        return metatype_id.load(); \
    } \
};

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
// QGradient::Type
//

static const QGradient::Type qtscript_QGradient_Type_values[] = {
    QGradient::LinearGradient
    , QGradient::RadialGradient
    , QGradient::ConicalGradient
    , QGradient::NoGradient
};

static const char * const qtscript_QGradient_Type_keys[] = {
    "LinearGradient"
    , "RadialGradient"
    , "ConicalGradient"
    , "NoGradient"
};

static QString qtscript_QGradient_Type_toStringHelper(QGradient::Type value)
{
    const QMetaObject *meta = qtscript_QGradient_metaObject();
    int idx = meta->indexOfEnumerator("Type");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QGradient_Type_toScriptValue(QScriptEngine *engine, const QGradient::Type &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGradient"));
    return clazz.property(qtscript_QGradient_Type_toStringHelper(value));
}

static void qtscript_QGradient_Type_fromScriptValue(const QScriptValue &value, QGradient::Type &out)
{
    out = qvariant_cast<QGradient::Type>(value.toVariant());
}

static QScriptValue qtscript_construct_QGradient_Type(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QGradient_metaObject();
    int idx = meta->indexOfEnumerator("Type");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QGradient::Type>(arg));
    return context->throwError(QString::fromLatin1("Type(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGradient_Type_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGradient::Type value = qscriptvalue_cast<QGradient::Type>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGradient_Type_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGradient::Type value = qscriptvalue_cast<QGradient::Type>(context->thisObject());
    return QScriptValue(engine, qtscript_QGradient_Type_toStringHelper(value));
}

static QScriptValue qtscript_create_QGradient_Type_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGradient_Type,
        qtscript_QGradient_Type_valueOf, qtscript_QGradient_Type_toString);
    qScriptRegisterMetaType<QGradient::Type>(engine, qtscript_QGradient_Type_toScriptValue,
        qtscript_QGradient_Type_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGradient_Type_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGradient_Type_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGradient::Spread
//

static const QGradient::Spread qtscript_QGradient_Spread_values[] = {
    QGradient::PadSpread
    , QGradient::ReflectSpread
    , QGradient::RepeatSpread
};

static const char * const qtscript_QGradient_Spread_keys[] = {
    "PadSpread"
    , "ReflectSpread"
    , "RepeatSpread"
};

static QString qtscript_QGradient_Spread_toStringHelper(QGradient::Spread value)
{
    const QMetaObject *meta = qtscript_QGradient_metaObject();
    int idx = meta->indexOfEnumerator("Spread");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QGradient_Spread_toScriptValue(QScriptEngine *engine, const QGradient::Spread &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGradient"));
    return clazz.property(qtscript_QGradient_Spread_toStringHelper(value));
}

static void qtscript_QGradient_Spread_fromScriptValue(const QScriptValue &value, QGradient::Spread &out)
{
    out = qvariant_cast<QGradient::Spread>(value.toVariant());
}

static QScriptValue qtscript_construct_QGradient_Spread(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QGradient_metaObject();
    int idx = meta->indexOfEnumerator("Spread");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QGradient::Spread>(arg));
    return context->throwError(QString::fromLatin1("Spread(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGradient_Spread_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGradient::Spread value = qscriptvalue_cast<QGradient::Spread>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGradient_Spread_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGradient::Spread value = qscriptvalue_cast<QGradient::Spread>(context->thisObject());
    return QScriptValue(engine, qtscript_QGradient_Spread_toStringHelper(value));
}

static QScriptValue qtscript_create_QGradient_Spread_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGradient_Spread,
        qtscript_QGradient_Spread_valueOf, qtscript_QGradient_Spread_toString);
    qScriptRegisterMetaType<QGradient::Spread>(engine, qtscript_QGradient_Spread_toScriptValue,
        qtscript_QGradient_Spread_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGradient_Spread_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGradient_Spread_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGradient::CoordinateMode
//

static const QGradient::CoordinateMode qtscript_QGradient_CoordinateMode_values[] = {
    QGradient::LogicalMode
    , QGradient::StretchToDeviceMode
    , QGradient::ObjectBoundingMode
};

static const char * const qtscript_QGradient_CoordinateMode_keys[] = {
    "LogicalMode"
    , "StretchToDeviceMode"
    , "ObjectBoundingMode"
};

static QString qtscript_QGradient_CoordinateMode_toStringHelper(QGradient::CoordinateMode value)
{
    const QMetaObject *meta = qtscript_QGradient_metaObject();
    int idx = meta->indexOfEnumerator("CoordinateMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QGradient_CoordinateMode_toScriptValue(QScriptEngine *engine, const QGradient::CoordinateMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGradient"));
    return clazz.property(qtscript_QGradient_CoordinateMode_toStringHelper(value));
}

static void qtscript_QGradient_CoordinateMode_fromScriptValue(const QScriptValue &value, QGradient::CoordinateMode &out)
{
    out = qvariant_cast<QGradient::CoordinateMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QGradient_CoordinateMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QGradient_metaObject();
    int idx = meta->indexOfEnumerator("CoordinateMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QGradient::CoordinateMode>(arg));
    return context->throwError(QString::fromLatin1("CoordinateMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGradient_CoordinateMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGradient::CoordinateMode value = qscriptvalue_cast<QGradient::CoordinateMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGradient_CoordinateMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGradient::CoordinateMode value = qscriptvalue_cast<QGradient::CoordinateMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QGradient_CoordinateMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QGradient_CoordinateMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGradient_CoordinateMode,
        qtscript_QGradient_CoordinateMode_valueOf, qtscript_QGradient_CoordinateMode_toString);
    qScriptRegisterMetaType<QGradient::CoordinateMode>(engine, qtscript_QGradient_CoordinateMode_toScriptValue,
        qtscript_QGradient_CoordinateMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGradient_CoordinateMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGradient_CoordinateMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGradient
//

static QScriptValue qtscript_QGradient_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 9;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGradient* _q_self = qscriptvalue_cast<QGradient*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGradient.%0(): this object is not a QGradient")
            .arg(qtscript_QGradient_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QGradient::CoordinateMode _q_result = _q_self->coordinateMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QGradient _q_arg0 = qscriptvalue_cast<QGradient>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QColor _q_arg1 = qscriptvalue_cast<QColor>(context->argument(1));
        _q_self->setColorAt(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QGradient::CoordinateMode _q_arg0 = qscriptvalue_cast<QGradient::CoordinateMode>(context->argument(0));
        _q_self->setCoordinateMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QGradient::Spread _q_arg0 = qscriptvalue_cast<QGradient::Spread>(context->argument(0));
        _q_self->setSpread(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QVector<QPair<qreal,QColor> > _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setStops(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QGradient::Spread _q_result = _q_self->spread();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QVector<QPair<qreal,QColor > > _q_result = _q_self->stops();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QGradient::Type _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("QGradient");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGradient_throw_ambiguity_error_helper(context,
        qtscript_QGradient_function_names[_id+1],
        qtscript_QGradient_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGradient_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGradient(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QGradient _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGradient_throw_ambiguity_error_helper(context,
        qtscript_QGradient_function_names[_id],
        qtscript_QGradient_function_signatures[_id]);
}

QScriptValue qtscript_create_QGradient_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGradient*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGradient*)0));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGradient_prototype_call, qtscript_QGradient_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGradient_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGradient>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QGradient*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGradient_static_call, proto, qtscript_QGradient_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Type"),
        qtscript_create_QGradient_Type_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Spread"),
        qtscript_create_QGradient_Spread_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("CoordinateMode"),
        qtscript_create_QGradient_CoordinateMode_class(engine, ctor));
    return ctor;
}
