#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qcalendarwidget.h>
#include <QTextCharFormat>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcalendarwidget.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdatetime.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qtextformat.h>
#include <qwidget.h>

#include "qtscriptshell_QCalendarWidget.h"

static const char * const qtscript_QCalendarWidget_function_names[] = {
    "QCalendarWidget"
    // static
    // prototype
    , "dateTextFormat"
    , "headerTextFormat"
    , "monthShown"
    , "setDateTextFormat"
    , "setHeaderTextFormat"
    , "setWeekdayTextFormat"
    , "weekdayTextFormat"
    , "yearShown"
    , "toString"
};

static const char * const qtscript_QCalendarWidget_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "\nQDate date"
    , ""
    , ""
    , "QDate date, QTextCharFormat format"
    , "QTextCharFormat format"
    , "DayOfWeek dayOfWeek, QTextCharFormat format"
    , "DayOfWeek dayOfWeek"
    , ""
""
};

static const int qtscript_QCalendarWidget_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
    , 2
    , 1
    , 2
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QCalendarWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QCalendarWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QCalendarWidget_metaObject()
{
    return &QCalendarWidget::staticMetaObject;
}

Q_DECLARE_METATYPE(QCalendarWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QCalendarWidget*)
Q_DECLARE_METATYPE(QCalendarWidget::VerticalHeaderFormat)
Q_DECLARE_METATYPE(QCalendarWidget::SelectionMode)
Q_DECLARE_METATYPE(QCalendarWidget::HorizontalHeaderFormat)
Q_DECLARE_METATYPE(QTextCharFormat)
template <> \
struct QMetaTypeId< QMap<QDate,QTextCharFormat > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QMap<QDate,QTextCharFormat > >("QMap<QDate,QTextCharFormat >")); \
        return metatype_id.load(); \
    } \
};
Q_DECLARE_METATYPE(Qt::DayOfWeek)
Q_DECLARE_METATYPE(QWidget*)

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
// QCalendarWidget::VerticalHeaderFormat
//

static const QCalendarWidget::VerticalHeaderFormat qtscript_QCalendarWidget_VerticalHeaderFormat_values[] = {
    QCalendarWidget::NoVerticalHeader
    , QCalendarWidget::ISOWeekNumbers
};

static const char * const qtscript_QCalendarWidget_VerticalHeaderFormat_keys[] = {
    "NoVerticalHeader"
    , "ISOWeekNumbers"
};

static QString qtscript_QCalendarWidget_VerticalHeaderFormat_toStringHelper(QCalendarWidget::VerticalHeaderFormat value)
{
    const QMetaObject *meta = qtscript_QCalendarWidget_metaObject();
    int idx = meta->indexOfEnumerator("VerticalHeaderFormat");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QCalendarWidget_VerticalHeaderFormat_toScriptValue(QScriptEngine *engine, const QCalendarWidget::VerticalHeaderFormat &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QCalendarWidget"));
    return clazz.property(qtscript_QCalendarWidget_VerticalHeaderFormat_toStringHelper(value));
}

static void qtscript_QCalendarWidget_VerticalHeaderFormat_fromScriptValue(const QScriptValue &value, QCalendarWidget::VerticalHeaderFormat &out)
{
    out = qvariant_cast<QCalendarWidget::VerticalHeaderFormat>(value.toVariant());
}

static QScriptValue qtscript_construct_QCalendarWidget_VerticalHeaderFormat(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QCalendarWidget_metaObject();
    int idx = meta->indexOfEnumerator("VerticalHeaderFormat");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QCalendarWidget::VerticalHeaderFormat>(arg));
    return context->throwError(QString::fromLatin1("VerticalHeaderFormat(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QCalendarWidget_VerticalHeaderFormat_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QCalendarWidget::VerticalHeaderFormat value = qscriptvalue_cast<QCalendarWidget::VerticalHeaderFormat>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QCalendarWidget_VerticalHeaderFormat_toString(QScriptContext *context, QScriptEngine *engine)
{
    QCalendarWidget::VerticalHeaderFormat value = qscriptvalue_cast<QCalendarWidget::VerticalHeaderFormat>(context->thisObject());
    return QScriptValue(engine, qtscript_QCalendarWidget_VerticalHeaderFormat_toStringHelper(value));
}

static QScriptValue qtscript_create_QCalendarWidget_VerticalHeaderFormat_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QCalendarWidget_VerticalHeaderFormat,
        qtscript_QCalendarWidget_VerticalHeaderFormat_valueOf, qtscript_QCalendarWidget_VerticalHeaderFormat_toString);
    qScriptRegisterMetaType<QCalendarWidget::VerticalHeaderFormat>(engine, qtscript_QCalendarWidget_VerticalHeaderFormat_toScriptValue,
        qtscript_QCalendarWidget_VerticalHeaderFormat_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QCalendarWidget_VerticalHeaderFormat_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QCalendarWidget_VerticalHeaderFormat_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QCalendarWidget::SelectionMode
//

static const QCalendarWidget::SelectionMode qtscript_QCalendarWidget_SelectionMode_values[] = {
    QCalendarWidget::NoSelection
    , QCalendarWidget::SingleSelection
};

static const char * const qtscript_QCalendarWidget_SelectionMode_keys[] = {
    "NoSelection"
    , "SingleSelection"
};

static QString qtscript_QCalendarWidget_SelectionMode_toStringHelper(QCalendarWidget::SelectionMode value)
{
    const QMetaObject *meta = qtscript_QCalendarWidget_metaObject();
    int idx = meta->indexOfEnumerator("SelectionMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QCalendarWidget_SelectionMode_toScriptValue(QScriptEngine *engine, const QCalendarWidget::SelectionMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QCalendarWidget"));
    return clazz.property(qtscript_QCalendarWidget_SelectionMode_toStringHelper(value));
}

static void qtscript_QCalendarWidget_SelectionMode_fromScriptValue(const QScriptValue &value, QCalendarWidget::SelectionMode &out)
{
    out = qvariant_cast<QCalendarWidget::SelectionMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QCalendarWidget_SelectionMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QCalendarWidget_metaObject();
    int idx = meta->indexOfEnumerator("SelectionMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QCalendarWidget::SelectionMode>(arg));
    return context->throwError(QString::fromLatin1("SelectionMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QCalendarWidget_SelectionMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QCalendarWidget::SelectionMode value = qscriptvalue_cast<QCalendarWidget::SelectionMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QCalendarWidget_SelectionMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QCalendarWidget::SelectionMode value = qscriptvalue_cast<QCalendarWidget::SelectionMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QCalendarWidget_SelectionMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QCalendarWidget_SelectionMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QCalendarWidget_SelectionMode,
        qtscript_QCalendarWidget_SelectionMode_valueOf, qtscript_QCalendarWidget_SelectionMode_toString);
    qScriptRegisterMetaType<QCalendarWidget::SelectionMode>(engine, qtscript_QCalendarWidget_SelectionMode_toScriptValue,
        qtscript_QCalendarWidget_SelectionMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QCalendarWidget_SelectionMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QCalendarWidget_SelectionMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QCalendarWidget::HorizontalHeaderFormat
//

static const QCalendarWidget::HorizontalHeaderFormat qtscript_QCalendarWidget_HorizontalHeaderFormat_values[] = {
    QCalendarWidget::NoHorizontalHeader
    , QCalendarWidget::SingleLetterDayNames
    , QCalendarWidget::ShortDayNames
    , QCalendarWidget::LongDayNames
};

static const char * const qtscript_QCalendarWidget_HorizontalHeaderFormat_keys[] = {
    "NoHorizontalHeader"
    , "SingleLetterDayNames"
    , "ShortDayNames"
    , "LongDayNames"
};

static QString qtscript_QCalendarWidget_HorizontalHeaderFormat_toStringHelper(QCalendarWidget::HorizontalHeaderFormat value)
{
    const QMetaObject *meta = qtscript_QCalendarWidget_metaObject();
    int idx = meta->indexOfEnumerator("HorizontalHeaderFormat");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QCalendarWidget_HorizontalHeaderFormat_toScriptValue(QScriptEngine *engine, const QCalendarWidget::HorizontalHeaderFormat &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QCalendarWidget"));
    return clazz.property(qtscript_QCalendarWidget_HorizontalHeaderFormat_toStringHelper(value));
}

static void qtscript_QCalendarWidget_HorizontalHeaderFormat_fromScriptValue(const QScriptValue &value, QCalendarWidget::HorizontalHeaderFormat &out)
{
    out = qvariant_cast<QCalendarWidget::HorizontalHeaderFormat>(value.toVariant());
}

static QScriptValue qtscript_construct_QCalendarWidget_HorizontalHeaderFormat(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QCalendarWidget_metaObject();
    int idx = meta->indexOfEnumerator("HorizontalHeaderFormat");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QCalendarWidget::HorizontalHeaderFormat>(arg));
    return context->throwError(QString::fromLatin1("HorizontalHeaderFormat(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QCalendarWidget_HorizontalHeaderFormat_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QCalendarWidget::HorizontalHeaderFormat value = qscriptvalue_cast<QCalendarWidget::HorizontalHeaderFormat>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QCalendarWidget_HorizontalHeaderFormat_toString(QScriptContext *context, QScriptEngine *engine)
{
    QCalendarWidget::HorizontalHeaderFormat value = qscriptvalue_cast<QCalendarWidget::HorizontalHeaderFormat>(context->thisObject());
    return QScriptValue(engine, qtscript_QCalendarWidget_HorizontalHeaderFormat_toStringHelper(value));
}

static QScriptValue qtscript_create_QCalendarWidget_HorizontalHeaderFormat_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QCalendarWidget_HorizontalHeaderFormat,
        qtscript_QCalendarWidget_HorizontalHeaderFormat_valueOf, qtscript_QCalendarWidget_HorizontalHeaderFormat_toString);
    qScriptRegisterMetaType<QCalendarWidget::HorizontalHeaderFormat>(engine, qtscript_QCalendarWidget_HorizontalHeaderFormat_toScriptValue,
        qtscript_QCalendarWidget_HorizontalHeaderFormat_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QCalendarWidget_HorizontalHeaderFormat_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QCalendarWidget_HorizontalHeaderFormat_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QCalendarWidget
//

static QScriptValue qtscript_QCalendarWidget_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 8;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QCalendarWidget* _q_self = qscriptvalue_cast<QCalendarWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QCalendarWidget.%0(): this object is not a QCalendarWidget")
            .arg(qtscript_QCalendarWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QMap<QDate,QTextCharFormat > _q_result = _q_self->dateTextFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QDate _q_arg0 = qscriptvalue_cast<QDate>(context->argument(0));
        QTextCharFormat _q_result = _q_self->dateTextFormat(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QTextCharFormat _q_result = _q_self->headerTextFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->monthShown();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        QDate _q_arg0 = qscriptvalue_cast<QDate>(context->argument(0));
        QTextCharFormat _q_arg1 = qscriptvalue_cast<QTextCharFormat>(context->argument(1));
        _q_self->setDateTextFormat(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QTextCharFormat _q_arg0 = qscriptvalue_cast<QTextCharFormat>(context->argument(0));
        _q_self->setHeaderTextFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        Qt::DayOfWeek _q_arg0 = qscriptvalue_cast<Qt::DayOfWeek>(context->argument(0));
        QTextCharFormat _q_arg1 = qscriptvalue_cast<QTextCharFormat>(context->argument(1));
        _q_self->setWeekdayTextFormat(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        Qt::DayOfWeek _q_arg0 = qscriptvalue_cast<Qt::DayOfWeek>(context->argument(0));
        QTextCharFormat _q_result = _q_self->weekdayTextFormat(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->yearShown();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QCalendarWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QCalendarWidget_throw_ambiguity_error_helper(context,
        qtscript_QCalendarWidget_function_names[_id+1],
        qtscript_QCalendarWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_QCalendarWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QCalendarWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QCalendarWidget* _q_cpp_result = new QtScriptShell_QCalendarWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCalendarWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QCalendarWidget* _q_cpp_result = new QtScriptShell_QCalendarWidget(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCalendarWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QCalendarWidget_throw_ambiguity_error_helper(context,
        qtscript_QCalendarWidget_function_names[_id],
        qtscript_QCalendarWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QCalendarWidget_toScriptValue(QScriptEngine *engine, QCalendarWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QCalendarWidget_fromScriptValue(const QScriptValue &value, QCalendarWidget* &out)
{
    out = qobject_cast<QCalendarWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QCalendarWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QCalendarWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QCalendarWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QCalendarWidget_prototype_call, qtscript_QCalendarWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QCalendarWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QCalendarWidget*>(engine, qtscript_QCalendarWidget_toScriptValue, 
        qtscript_QCalendarWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QCalendarWidget_static_call, proto, qtscript_QCalendarWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("VerticalHeaderFormat"),
        qtscript_create_QCalendarWidget_VerticalHeaderFormat_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SelectionMode"),
        qtscript_create_QCalendarWidget_SelectionMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("HorizontalHeaderFormat"),
        qtscript_create_QCalendarWidget_HorizontalHeaderFormat_class(engine, ctor));
    return ctor;
}
