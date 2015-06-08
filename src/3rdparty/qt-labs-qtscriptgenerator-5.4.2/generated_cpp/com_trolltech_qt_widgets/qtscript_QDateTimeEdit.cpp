#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdatetimeedit.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcalendarwidget.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdatetime.h>
#include <qdatetimeedit.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlineedit.h>
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
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QDateTimeEdit.h"

static const char * const qtscript_QDateTimeEdit_function_names[] = {
    "QDateTimeEdit"
    // static
    // prototype
    , "calendarWidget"
    , "clearMaximumDate"
    , "clearMaximumDateTime"
    , "clearMaximumTime"
    , "clearMinimumDate"
    , "clearMinimumDateTime"
    , "clearMinimumTime"
    , "sectionAt"
    , "sectionText"
    , "setCalendarWidget"
    , "setDateRange"
    , "setDateTimeRange"
    , "setSelectedSection"
    , "setTimeRange"
    , "toString"
};

static const char * const qtscript_QDateTimeEdit_function_signatures[] = {
    "QWidget parent\nQDate d, QWidget parent\nQDateTime dt, QWidget parent\nQTime t, QWidget parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int index"
    , "Section section"
    , "QCalendarWidget calendarWidget"
    , "QDate min, QDate max"
    , "QDateTime min, QDateTime max"
    , "Section section"
    , "QTime min, QTime max"
""
};

static const int qtscript_QDateTimeEdit_function_lengths[] = {
    2
    // static
    // prototype
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
    , 2
    , 2
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QDateTimeEdit_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDateTimeEdit::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QDateTimeEdit_metaObject()
{
    return &QDateTimeEdit::staticMetaObject;
}

Q_DECLARE_METATYPE(QDateTimeEdit*)
Q_DECLARE_METATYPE(QtScriptShell_QDateTimeEdit*)
Q_DECLARE_METATYPE(QDateTimeEdit::Section)
Q_DECLARE_METATYPE(QFlags<QDateTimeEdit::Section>)
Q_DECLARE_METATYPE(QCalendarWidget*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QAbstractSpinBox*)

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
// QDateTimeEdit::Section
//

static const QDateTimeEdit::Section qtscript_QDateTimeEdit_Section_values[] = {
    QDateTimeEdit::NoSection
    , QDateTimeEdit::AmPmSection
    , QDateTimeEdit::MSecSection
    , QDateTimeEdit::SecondSection
    , QDateTimeEdit::MinuteSection
    , QDateTimeEdit::HourSection
    , QDateTimeEdit::TimeSections_Mask
    , QDateTimeEdit::DaySection
    , QDateTimeEdit::MonthSection
    , QDateTimeEdit::YearSection
    , QDateTimeEdit::DateSections_Mask
};

static const char * const qtscript_QDateTimeEdit_Section_keys[] = {
    "NoSection"
    , "AmPmSection"
    , "MSecSection"
    , "SecondSection"
    , "MinuteSection"
    , "HourSection"
    , "TimeSections_Mask"
    , "DaySection"
    , "MonthSection"
    , "YearSection"
    , "DateSections_Mask"
};

static QString qtscript_QDateTimeEdit_Section_toStringHelper(QDateTimeEdit::Section value)
{
    const QMetaObject *meta = qtscript_QDateTimeEdit_metaObject();
    int idx = meta->indexOfEnumerator("Section");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QDateTimeEdit_Section_toScriptValue(QScriptEngine *engine, const QDateTimeEdit::Section &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDateTimeEdit"));
    return clazz.property(qtscript_QDateTimeEdit_Section_toStringHelper(value));
}

static void qtscript_QDateTimeEdit_Section_fromScriptValue(const QScriptValue &value, QDateTimeEdit::Section &out)
{
    out = qvariant_cast<QDateTimeEdit::Section>(value.toVariant());
}

static QScriptValue qtscript_construct_QDateTimeEdit_Section(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QDateTimeEdit_metaObject();
    int idx = meta->indexOfEnumerator("Section");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QDateTimeEdit::Section>(arg));
    return context->throwError(QString::fromLatin1("Section(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDateTimeEdit_Section_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDateTimeEdit::Section value = qscriptvalue_cast<QDateTimeEdit::Section>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDateTimeEdit_Section_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDateTimeEdit::Section value = qscriptvalue_cast<QDateTimeEdit::Section>(context->thisObject());
    return QScriptValue(engine, qtscript_QDateTimeEdit_Section_toStringHelper(value));
}

static QScriptValue qtscript_create_QDateTimeEdit_Section_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDateTimeEdit_Section,
        qtscript_QDateTimeEdit_Section_valueOf, qtscript_QDateTimeEdit_Section_toString);
    qScriptRegisterMetaType<QDateTimeEdit::Section>(engine, qtscript_QDateTimeEdit_Section_toScriptValue,
        qtscript_QDateTimeEdit_Section_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDateTimeEdit_Section_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDateTimeEdit_Section_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDateTimeEdit::Sections
//

static QScriptValue qtscript_QDateTimeEdit_Sections_toScriptValue(QScriptEngine *engine, const QDateTimeEdit::Sections &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QDateTimeEdit_Sections_fromScriptValue(const QScriptValue &value, QDateTimeEdit::Sections &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QDateTimeEdit::Sections>())
        out = qvariant_cast<QDateTimeEdit::Sections>(var);
    else if (var.userType() == qMetaTypeId<QDateTimeEdit::Section>())
        out = qvariant_cast<QDateTimeEdit::Section>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QDateTimeEdit_Sections(QScriptContext *context, QScriptEngine *engine)
{
    QDateTimeEdit::Sections result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QDateTimeEdit::Sections>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QDateTimeEdit::Section>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("Sections(): argument %0 is not of type Section").arg(i));
            }
            result |= qvariant_cast<QDateTimeEdit::Section>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QDateTimeEdit_Sections_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDateTimeEdit::Sections value = qscriptvalue_cast<QDateTimeEdit::Sections>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDateTimeEdit_Sections_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDateTimeEdit::Sections value = qscriptvalue_cast<QDateTimeEdit::Sections>(context->thisObject());
    QString result;
    for (int i = 0; i < 11; ++i) {
        if ((value & qtscript_QDateTimeEdit_Section_values[i]) == qtscript_QDateTimeEdit_Section_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QDateTimeEdit_Section_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QDateTimeEdit_Sections_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QDateTimeEdit::Sections>() == otherObj.value<QDateTimeEdit::Sections>())));
}

static QScriptValue qtscript_create_QDateTimeEdit_Sections_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QDateTimeEdit_Sections, qtscript_QDateTimeEdit_Sections_valueOf,
        qtscript_QDateTimeEdit_Sections_toString, qtscript_QDateTimeEdit_Sections_equals);
    qScriptRegisterMetaType<QDateTimeEdit::Sections>(engine, qtscript_QDateTimeEdit_Sections_toScriptValue,
        qtscript_QDateTimeEdit_Sections_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QDateTimeEdit
//

static QScriptValue qtscript_QDateTimeEdit_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 14;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDateTimeEdit* _q_self = qscriptvalue_cast<QDateTimeEdit*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDateTimeEdit.%0(): this object is not a QDateTimeEdit")
            .arg(qtscript_QDateTimeEdit_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QCalendarWidget* _q_result = _q_self->calendarWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->clearMaximumDate();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->clearMaximumDateTime();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->clearMaximumTime();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        _q_self->clearMinimumDate();
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->clearMinimumDateTime();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->clearMinimumTime();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QDateTimeEdit::Section _q_result = _q_self->sectionAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QDateTimeEdit::Section _q_arg0 = qscriptvalue_cast<QDateTimeEdit::Section>(context->argument(0));
        QString _q_result = _q_self->sectionText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QCalendarWidget* _q_arg0 = qscriptvalue_cast<QCalendarWidget*>(context->argument(0));
        _q_self->setCalendarWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        QDate _q_arg0 = qscriptvalue_cast<QDate>(context->argument(0));
        QDate _q_arg1 = qscriptvalue_cast<QDate>(context->argument(1));
        _q_self->setDateRange(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        QDateTime _q_arg0 = context->argument(0).toDateTime();
        QDateTime _q_arg1 = context->argument(1).toDateTime();
        _q_self->setDateTimeRange(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QDateTimeEdit::Section _q_arg0 = qscriptvalue_cast<QDateTimeEdit::Section>(context->argument(0));
        _q_self->setSelectedSection(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        QTime _q_arg0 = qscriptvalue_cast<QTime>(context->argument(0));
        QTime _q_arg1 = qscriptvalue_cast<QTime>(context->argument(1));
        _q_self->setTimeRange(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 14: {
    QString result = QString::fromLatin1("QDateTimeEdit");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDateTimeEdit_throw_ambiguity_error_helper(context,
        qtscript_QDateTimeEdit_function_names[_id+1],
        qtscript_QDateTimeEdit_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDateTimeEdit_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDateTimeEdit(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QDateTimeEdit* _q_cpp_result = new QtScriptShell_QDateTimeEdit();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDateTimeEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QDateTimeEdit* _q_cpp_result = new QtScriptShell_QDateTimeEdit(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDateTimeEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QDate>() == context->argument(0).toVariant().userType())) {
            QDate _q_arg0 = qscriptvalue_cast<QDate>(context->argument(0));
            QtScriptShell_QDateTimeEdit* _q_cpp_result = new QtScriptShell_QDateTimeEdit(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDateTimeEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QDateTime>() == context->argument(0).toVariant().userType())) {
            QDateTime _q_arg0 = context->argument(0).toDateTime();
            QtScriptShell_QDateTimeEdit* _q_cpp_result = new QtScriptShell_QDateTimeEdit(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDateTimeEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QTime>() == context->argument(0).toVariant().userType())) {
            QTime _q_arg0 = qscriptvalue_cast<QTime>(context->argument(0));
            QtScriptShell_QDateTimeEdit* _q_cpp_result = new QtScriptShell_QDateTimeEdit(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDateTimeEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QDate>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QDate _q_arg0 = qscriptvalue_cast<QDate>(context->argument(0));
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QtScriptShell_QDateTimeEdit* _q_cpp_result = new QtScriptShell_QDateTimeEdit(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDateTimeEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QDateTime>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QDateTime _q_arg0 = context->argument(0).toDateTime();
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QtScriptShell_QDateTimeEdit* _q_cpp_result = new QtScriptShell_QDateTimeEdit(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDateTimeEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QTime>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QTime _q_arg0 = qscriptvalue_cast<QTime>(context->argument(0));
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QtScriptShell_QDateTimeEdit* _q_cpp_result = new QtScriptShell_QDateTimeEdit(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDateTimeEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDateTimeEdit_throw_ambiguity_error_helper(context,
        qtscript_QDateTimeEdit_function_names[_id],
        qtscript_QDateTimeEdit_function_signatures[_id]);
}

static QScriptValue qtscript_QDateTimeEdit_toScriptValue(QScriptEngine *engine, QDateTimeEdit* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QDateTimeEdit_fromScriptValue(const QScriptValue &value, QDateTimeEdit* &out)
{
    out = qobject_cast<QDateTimeEdit*>(value.toQObject());
}

QScriptValue qtscript_create_QDateTimeEdit_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDateTimeEdit*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDateTimeEdit*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractSpinBox*>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDateTimeEdit_prototype_call, qtscript_QDateTimeEdit_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDateTimeEdit_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QDateTimeEdit*>(engine, qtscript_QDateTimeEdit_toScriptValue, 
        qtscript_QDateTimeEdit_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDateTimeEdit_static_call, proto, qtscript_QDateTimeEdit_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Section"),
        qtscript_create_QDateTimeEdit_Section_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Sections"),
        qtscript_create_QDateTimeEdit_Sections_class(engine));
    return ctor;
}
