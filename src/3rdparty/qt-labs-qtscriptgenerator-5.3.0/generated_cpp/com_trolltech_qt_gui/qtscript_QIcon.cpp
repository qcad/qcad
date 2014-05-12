#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qicon.h>
#include <QVariant>
#include <qicon.h>
#include <qlist.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qrect.h>
#include <qsize.h>
#include <qstringlist.h>

static const char * const qtscript_QIcon_function_names[] = {
    "QIcon"
    // static
    , "fromTheme"
    , "hasThemeIcon"
    , "setThemeName"
    , "setThemeSearchPaths"
    , "themeName"
    , "themeSearchPaths"
    // prototype
    , "actualSize"
    , "addFile"
    , "addPixmap"
    , "availableSizes"
    , "cacheKey"
    , "isNull"
    , "name"
    , "paint"
    , "pixmap"
    , "swap"
    , "toString"
};

static const char * const qtscript_QIcon_function_signatures[] = {
    "\nQIcon other\nQPixmap pixmap\nString fileName"
    // static
    , "String name, QIcon fallback"
    , "String name"
    , "String path"
    , "List searchpath"
    , ""
    , ""
    // prototype
    , "QSize size, Mode mode, State state"
    , "String fileName, QSize size, Mode mode, State state"
    , "QPixmap pixmap, Mode mode, State state"
    , "Mode mode, State state"
    , ""
    , ""
    , ""
    , "QPainter painter, QRect rect, Alignment alignment, Mode mode, State state\nQPainter painter, int x, int y, int w, int h, Alignment alignment, Mode mode, State state"
    , "QSize size, Mode mode, State state\nint extent, Mode mode, State state\nint w, int h, Mode mode, State state"
    , "QIcon other"
""
};

static const int qtscript_QIcon_function_lengths[] = {
    1
    // static
    , 2
    , 1
    , 1
    , 1
    , 0
    , 0
    // prototype
    , 3
    , 4
    , 3
    , 2
    , 0
    , 0
    , 0
    , 8
    , 4
    , 1
    , 0
};

static QScriptValue qtscript_QIcon_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QIcon::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QIcon*)
Q_DECLARE_METATYPE(QIcon::State)
Q_DECLARE_METATYPE(QIcon::Mode)
Q_DECLARE_METATYPE(QList<QSize >)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QFlags<Qt::AlignmentFlag>)

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
// QIcon::State
//

static const QIcon::State qtscript_QIcon_State_values[] = {
    QIcon::On
    , QIcon::Off
};

static const char * const qtscript_QIcon_State_keys[] = {
    "On"
    , "Off"
};

static QString qtscript_QIcon_State_toStringHelper(QIcon::State value)
{
    if ((value >= QIcon::On) && (value <= QIcon::Off))
        return qtscript_QIcon_State_keys[static_cast<int>(value)-static_cast<int>(QIcon::On)];
    return QString();
}

static QScriptValue qtscript_QIcon_State_toScriptValue(QScriptEngine *engine, const QIcon::State &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QIcon"));
    return clazz.property(qtscript_QIcon_State_toStringHelper(value));
}

static void qtscript_QIcon_State_fromScriptValue(const QScriptValue &value, QIcon::State &out)
{
    out = qvariant_cast<QIcon::State>(value.toVariant());
}

static QScriptValue qtscript_construct_QIcon_State(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QIcon::On) && (arg <= QIcon::Off))
        return qScriptValueFromValue(engine,  static_cast<QIcon::State>(arg));
    return context->throwError(QString::fromLatin1("State(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QIcon_State_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QIcon::State value = qscriptvalue_cast<QIcon::State>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QIcon_State_toString(QScriptContext *context, QScriptEngine *engine)
{
    QIcon::State value = qscriptvalue_cast<QIcon::State>(context->thisObject());
    return QScriptValue(engine, qtscript_QIcon_State_toStringHelper(value));
}

static QScriptValue qtscript_create_QIcon_State_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QIcon_State,
        qtscript_QIcon_State_valueOf, qtscript_QIcon_State_toString);
    qScriptRegisterMetaType<QIcon::State>(engine, qtscript_QIcon_State_toScriptValue,
        qtscript_QIcon_State_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QIcon_State_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QIcon_State_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QIcon::Mode
//

static const QIcon::Mode qtscript_QIcon_Mode_values[] = {
    QIcon::Normal
    , QIcon::Disabled
    , QIcon::Active
    , QIcon::Selected
};

static const char * const qtscript_QIcon_Mode_keys[] = {
    "Normal"
    , "Disabled"
    , "Active"
    , "Selected"
};

static QString qtscript_QIcon_Mode_toStringHelper(QIcon::Mode value)
{
    if ((value >= QIcon::Normal) && (value <= QIcon::Selected))
        return qtscript_QIcon_Mode_keys[static_cast<int>(value)-static_cast<int>(QIcon::Normal)];
    return QString();
}

static QScriptValue qtscript_QIcon_Mode_toScriptValue(QScriptEngine *engine, const QIcon::Mode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QIcon"));
    return clazz.property(qtscript_QIcon_Mode_toStringHelper(value));
}

static void qtscript_QIcon_Mode_fromScriptValue(const QScriptValue &value, QIcon::Mode &out)
{
    out = qvariant_cast<QIcon::Mode>(value.toVariant());
}

static QScriptValue qtscript_construct_QIcon_Mode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QIcon::Normal) && (arg <= QIcon::Selected))
        return qScriptValueFromValue(engine,  static_cast<QIcon::Mode>(arg));
    return context->throwError(QString::fromLatin1("Mode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QIcon_Mode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QIcon::Mode value = qscriptvalue_cast<QIcon::Mode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QIcon_Mode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QIcon::Mode value = qscriptvalue_cast<QIcon::Mode>(context->thisObject());
    return QScriptValue(engine, qtscript_QIcon_Mode_toStringHelper(value));
}

static QScriptValue qtscript_create_QIcon_Mode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QIcon_Mode,
        qtscript_QIcon_Mode_valueOf, qtscript_QIcon_Mode_toString);
    qScriptRegisterMetaType<QIcon::Mode>(engine, qtscript_QIcon_Mode_toScriptValue,
        qtscript_QIcon_Mode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QIcon_Mode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QIcon_Mode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QIcon
//

static QScriptValue qtscript_QIcon_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 10;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QIcon* _q_self = qscriptvalue_cast<QIcon*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QIcon.%0(): this object is not a QIcon")
            .arg(qtscript_QIcon_function_names[_id+7]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        QSize _q_result = _q_self->actualSize(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        QIcon::Mode _q_arg1 = qscriptvalue_cast<QIcon::Mode>(context->argument(1));
        QSize _q_result = _q_self->actualSize(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        QIcon::Mode _q_arg1 = qscriptvalue_cast<QIcon::Mode>(context->argument(1));
        QIcon::State _q_arg2 = qscriptvalue_cast<QIcon::State>(context->argument(2));
        QSize _q_result = _q_self->actualSize(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->addFile(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QSize _q_arg1 = qscriptvalue_cast<QSize>(context->argument(1));
        _q_self->addFile(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QSize _q_arg1 = qscriptvalue_cast<QSize>(context->argument(1));
        QIcon::Mode _q_arg2 = qscriptvalue_cast<QIcon::Mode>(context->argument(2));
        _q_self->addFile(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QSize _q_arg1 = qscriptvalue_cast<QSize>(context->argument(1));
        QIcon::Mode _q_arg2 = qscriptvalue_cast<QIcon::Mode>(context->argument(2));
        QIcon::State _q_arg3 = qscriptvalue_cast<QIcon::State>(context->argument(3));
        _q_self->addFile(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        _q_self->addPixmap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        QIcon::Mode _q_arg1 = qscriptvalue_cast<QIcon::Mode>(context->argument(1));
        _q_self->addPixmap(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        QIcon::Mode _q_arg1 = qscriptvalue_cast<QIcon::Mode>(context->argument(1));
        QIcon::State _q_arg2 = qscriptvalue_cast<QIcon::State>(context->argument(2));
        _q_self->addPixmap(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QList<QSize > _q_result = _q_self->availableSizes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QIcon::Mode _q_arg0 = qscriptvalue_cast<QIcon::Mode>(context->argument(0));
        QList<QSize > _q_result = _q_self->availableSizes(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QIcon::Mode _q_arg0 = qscriptvalue_cast<QIcon::Mode>(context->argument(0));
        QIcon::State _q_arg1 = qscriptvalue_cast<QIcon::State>(context->argument(1));
        QList<QSize > _q_result = _q_self->availableSizes(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->cacheKey();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->name();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
        _q_self->paint(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
        QFlags<Qt::AlignmentFlag> _q_arg2 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(2));
        _q_self->paint(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
        QFlags<Qt::AlignmentFlag> _q_arg2 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(2));
        QIcon::Mode _q_arg3 = qscriptvalue_cast<QIcon::Mode>(context->argument(3));
        _q_self->paint(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        if (qscriptvalue_cast<QPainter*>(context->argument(0))
            && (qMetaTypeId<QRect>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QFlags<Qt::AlignmentFlag> >() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QIcon::Mode>() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<QIcon::State>() == context->argument(4).toVariant().userType())) {
            QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
            QRect _q_arg1 = qscriptvalue_cast<QRect>(context->argument(1));
            QFlags<Qt::AlignmentFlag> _q_arg2 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(2));
            QIcon::Mode _q_arg3 = qscriptvalue_cast<QIcon::Mode>(context->argument(3));
            QIcon::State _q_arg4 = qscriptvalue_cast<QIcon::State>(context->argument(4));
            _q_self->paint(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QPainter*>(context->argument(0))
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()
            && context->argument(4).isNumber()) {
            QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            int _q_arg4 = context->argument(4).toInt32();
            _q_self->paint(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 6) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg5 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(5));
        _q_self->paint(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 7) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg5 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(5));
        QIcon::Mode _q_arg6 = qscriptvalue_cast<QIcon::Mode>(context->argument(6));
        _q_self->paint(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 8) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg5 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(5));
        QIcon::Mode _q_arg6 = qscriptvalue_cast<QIcon::Mode>(context->argument(6));
        QIcon::State _q_arg7 = qscriptvalue_cast<QIcon::State>(context->argument(7));
        _q_self->paint(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QSize>() == context->argument(0).toVariant().userType())) {
            QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
            QPixmap _q_result = _q_self->pixmap(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QPixmap _q_result = _q_self->pixmap(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QSize>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QIcon::Mode>() == context->argument(1).toVariant().userType())) {
            QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
            QIcon::Mode _q_arg1 = qscriptvalue_cast<QIcon::Mode>(context->argument(1));
            QPixmap _q_result = _q_self->pixmap(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QIcon::Mode>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QIcon::Mode _q_arg1 = qscriptvalue_cast<QIcon::Mode>(context->argument(1));
            QPixmap _q_result = _q_self->pixmap(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QPixmap _q_result = _q_self->pixmap(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QSize>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QIcon::Mode>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QIcon::State>() == context->argument(2).toVariant().userType())) {
            QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
            QIcon::Mode _q_arg1 = qscriptvalue_cast<QIcon::Mode>(context->argument(1));
            QIcon::State _q_arg2 = qscriptvalue_cast<QIcon::State>(context->argument(2));
            QPixmap _q_result = _q_self->pixmap(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QIcon::Mode>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QIcon::State>() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QIcon::Mode _q_arg1 = qscriptvalue_cast<QIcon::Mode>(context->argument(1));
            QIcon::State _q_arg2 = qscriptvalue_cast<QIcon::State>(context->argument(2));
            QPixmap _q_result = _q_self->pixmap(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && (qMetaTypeId<QIcon::Mode>() == context->argument(2).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QIcon::Mode _q_arg2 = qscriptvalue_cast<QIcon::Mode>(context->argument(2));
            QPixmap _q_result = _q_self->pixmap(_q_arg0, _q_arg1, _q_arg2);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QIcon::Mode _q_arg2 = qscriptvalue_cast<QIcon::Mode>(context->argument(2));
        QIcon::State _q_arg3 = qscriptvalue_cast<QIcon::State>(context->argument(3));
        QPixmap _q_result = _q_self->pixmap(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        _q_self->swap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QIcon_throw_ambiguity_error_helper(context,
        qtscript_QIcon_function_names[_id+7],
        qtscript_QIcon_function_signatures[_id+7]);
}

static QScriptValue qtscript_QIcon_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QIcon(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QIcon _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QIcon>() == context->argument(0).toVariant().userType())) {
            QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
            QIcon _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QPixmap>() == context->argument(0).toVariant().userType())) {
            QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
            QIcon _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QIcon _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QIcon _q_result = QIcon::fromTheme(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QIcon _q_arg1 = qscriptvalue_cast<QIcon>(context->argument(1));
        QIcon _q_result = QIcon::fromTheme(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = QIcon::hasThemeIcon(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QIcon::setThemeName(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QIcon::setThemeSearchPaths(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QString _q_result = QIcon::themeName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QStringList _q_result = QIcon::themeSearchPaths();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QIcon_throw_ambiguity_error_helper(context,
        qtscript_QIcon_function_names[_id],
        qtscript_QIcon_function_signatures[_id]);
}

QScriptValue qtscript_create_QIcon_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QIcon*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QIcon*)0));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QIcon_prototype_call, qtscript_QIcon_function_lengths[i+7]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QIcon_function_names[i+7]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QIcon>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QIcon*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QIcon_static_call, proto, qtscript_QIcon_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QIcon_static_call,
            qtscript_QIcon_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QIcon_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("State"),
        qtscript_create_QIcon_State_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Mode"),
        qtscript_create_QIcon_Mode_class(engine, ctor));
    return ctor;
}
