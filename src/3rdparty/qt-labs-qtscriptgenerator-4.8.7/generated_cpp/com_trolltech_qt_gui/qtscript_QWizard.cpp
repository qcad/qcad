#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qwizard.h>
#include <QVariant>
#include <qabstractbutton.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qinputcontext.h>
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
#include <qwidget.h>
#include <qwizard.h>

#include "qtscriptshell_QWizard.h"

static const char * const qtscript_QWizard_function_names[] = {
    "QWizard"
    // static
    // prototype
    , "addPage"
    , "button"
    , "buttonText"
    , "currentPage"
    , "field"
    , "hasVisitedPage"
    , "nextId"
    , "page"
    , "pageIds"
    , "pixmap"
    , "removePage"
    , "setButton"
    , "setButtonLayout"
    , "setButtonText"
    , "setField"
    , "setOption"
    , "setPage"
    , "setPixmap"
    , "setSideWidget"
    , "sideWidget"
    , "testOption"
    , "validateCurrentPage"
    , "visitedPages"
    , "toString"
};

static const char * const qtscript_QWizard_function_signatures[] = {
    "QWidget parent, WindowFlags flags"
    // static
    // prototype
    , "QWizardPage page"
    , "WizardButton which"
    , "WizardButton which"
    , ""
    , "String name"
    , "int id"
    , ""
    , "int id"
    , ""
    , "WizardPixmap which"
    , "int id"
    , "WizardButton which, QAbstractButton button"
    , "List layout"
    , "WizardButton which, String text"
    , "String name, Object value"
    , "WizardOption option, bool on"
    , "int id, QWizardPage page"
    , "WizardPixmap which, QPixmap pixmap"
    , "QWidget widget"
    , ""
    , "WizardOption option"
    , ""
    , ""
""
};

static const int qtscript_QWizard_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 1
    , 1
    , 0
    , 1
    , 1
    , 0
    , 1
    , 0
    , 1
    , 1
    , 2
    , 1
    , 2
    , 2
    , 2
    , 2
    , 2
    , 1
    , 0
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QWizard_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWizard::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QWizard_metaObject()
{
    return &QWizard::staticMetaObject;
}

Q_DECLARE_METATYPE(QWizard*)
Q_DECLARE_METATYPE(QtScriptShell_QWizard*)
Q_DECLARE_METATYPE(QWizard::WizardButton)
Q_DECLARE_METATYPE(QWizard::WizardStyle)
Q_DECLARE_METATYPE(QWizard::WizardPixmap)
Q_DECLARE_METATYPE(QWizard::WizardOption)
Q_DECLARE_METATYPE(QFlags<QWizard::WizardOption>)
Q_DECLARE_METATYPE(QWizardPage*)
Q_DECLARE_METATYPE(QAbstractButton*)
Q_DECLARE_METATYPE(QList<int>)
Q_DECLARE_METATYPE(QList<QWizard::WizardButton>)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)
Q_DECLARE_METATYPE(QDialog*)

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
// QWizard::WizardButton
//

static const QWizard::WizardButton qtscript_QWizard_WizardButton_values[] = {
    QWizard::NoButton
    , QWizard::BackButton
    , QWizard::NextButton
    , QWizard::CommitButton
    , QWizard::FinishButton
    , QWizard::CancelButton
    , QWizard::HelpButton
    , QWizard::CustomButton1
    , QWizard::CustomButton2
    , QWizard::CustomButton3
    , QWizard::Stretch
};

static const char * const qtscript_QWizard_WizardButton_keys[] = {
    "NoButton"
    , "BackButton"
    , "NextButton"
    , "CommitButton"
    , "FinishButton"
    , "CancelButton"
    , "HelpButton"
    , "CustomButton1"
    , "CustomButton2"
    , "CustomButton3"
    , "Stretch"
};

static QString qtscript_QWizard_WizardButton_toStringHelper(QWizard::WizardButton value)
{
    if ((value >= QWizard::NoButton) && (value <= QWizard::Stretch))
        return qtscript_QWizard_WizardButton_keys[static_cast<int>(value)-static_cast<int>(QWizard::NoButton)];
    return QString();
}

static QScriptValue qtscript_QWizard_WizardButton_toScriptValue(QScriptEngine *engine, const QWizard::WizardButton &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWizard"));
    return clazz.property(qtscript_QWizard_WizardButton_toStringHelper(value));
}

static void qtscript_QWizard_WizardButton_fromScriptValue(const QScriptValue &value, QWizard::WizardButton &out)
{
    out = qvariant_cast<QWizard::WizardButton>(value.toVariant());
}

static QScriptValue qtscript_construct_QWizard_WizardButton(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QWizard::NoButton) && (arg <= QWizard::Stretch))
        return qScriptValueFromValue(engine,  static_cast<QWizard::WizardButton>(arg));
    return context->throwError(QString::fromLatin1("WizardButton(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWizard_WizardButton_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWizard::WizardButton value = qscriptvalue_cast<QWizard::WizardButton>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWizard_WizardButton_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWizard::WizardButton value = qscriptvalue_cast<QWizard::WizardButton>(context->thisObject());
    return QScriptValue(engine, qtscript_QWizard_WizardButton_toStringHelper(value));
}

static QScriptValue qtscript_create_QWizard_WizardButton_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWizard_WizardButton,
        qtscript_QWizard_WizardButton_valueOf, qtscript_QWizard_WizardButton_toString);
    qScriptRegisterMetaType<QWizard::WizardButton>(engine, qtscript_QWizard_WizardButton_toScriptValue,
        qtscript_QWizard_WizardButton_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWizard_WizardButton_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWizard_WizardButton_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWizard::WizardStyle
//

static const QWizard::WizardStyle qtscript_QWizard_WizardStyle_values[] = {
    QWizard::ClassicStyle
    , QWizard::ModernStyle
    , QWizard::MacStyle
    , QWizard::AeroStyle
    , QWizard::NStyles
};

static const char * const qtscript_QWizard_WizardStyle_keys[] = {
    "ClassicStyle"
    , "ModernStyle"
    , "MacStyle"
    , "AeroStyle"
    , "NStyles"
};

static QString qtscript_QWizard_WizardStyle_toStringHelper(QWizard::WizardStyle value)
{
    const QMetaObject *meta = qtscript_QWizard_metaObject();
    int idx = meta->indexOfEnumerator("WizardStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QWizard_WizardStyle_toScriptValue(QScriptEngine *engine, const QWizard::WizardStyle &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWizard"));
    return clazz.property(qtscript_QWizard_WizardStyle_toStringHelper(value));
}

static void qtscript_QWizard_WizardStyle_fromScriptValue(const QScriptValue &value, QWizard::WizardStyle &out)
{
    out = qvariant_cast<QWizard::WizardStyle>(value.toVariant());
}

static QScriptValue qtscript_construct_QWizard_WizardStyle(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QWizard_metaObject();
    int idx = meta->indexOfEnumerator("WizardStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QWizard::WizardStyle>(arg));
    return context->throwError(QString::fromLatin1("WizardStyle(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWizard_WizardStyle_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWizard::WizardStyle value = qscriptvalue_cast<QWizard::WizardStyle>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWizard_WizardStyle_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWizard::WizardStyle value = qscriptvalue_cast<QWizard::WizardStyle>(context->thisObject());
    return QScriptValue(engine, qtscript_QWizard_WizardStyle_toStringHelper(value));
}

static QScriptValue qtscript_create_QWizard_WizardStyle_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWizard_WizardStyle,
        qtscript_QWizard_WizardStyle_valueOf, qtscript_QWizard_WizardStyle_toString);
    qScriptRegisterMetaType<QWizard::WizardStyle>(engine, qtscript_QWizard_WizardStyle_toScriptValue,
        qtscript_QWizard_WizardStyle_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWizard_WizardStyle_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWizard_WizardStyle_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWizard::WizardPixmap
//

static const QWizard::WizardPixmap qtscript_QWizard_WizardPixmap_values[] = {
    QWizard::WatermarkPixmap
    , QWizard::LogoPixmap
    , QWizard::BannerPixmap
    , QWizard::BackgroundPixmap
    , QWizard::NPixmaps
};

static const char * const qtscript_QWizard_WizardPixmap_keys[] = {
    "WatermarkPixmap"
    , "LogoPixmap"
    , "BannerPixmap"
    , "BackgroundPixmap"
    , "NPixmaps"
};

static QString qtscript_QWizard_WizardPixmap_toStringHelper(QWizard::WizardPixmap value)
{
    if ((value >= QWizard::WatermarkPixmap) && (value <= QWizard::NPixmaps))
        return qtscript_QWizard_WizardPixmap_keys[static_cast<int>(value)-static_cast<int>(QWizard::WatermarkPixmap)];
    return QString();
}

static QScriptValue qtscript_QWizard_WizardPixmap_toScriptValue(QScriptEngine *engine, const QWizard::WizardPixmap &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWizard"));
    return clazz.property(qtscript_QWizard_WizardPixmap_toStringHelper(value));
}

static void qtscript_QWizard_WizardPixmap_fromScriptValue(const QScriptValue &value, QWizard::WizardPixmap &out)
{
    out = qvariant_cast<QWizard::WizardPixmap>(value.toVariant());
}

static QScriptValue qtscript_construct_QWizard_WizardPixmap(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QWizard::WatermarkPixmap) && (arg <= QWizard::NPixmaps))
        return qScriptValueFromValue(engine,  static_cast<QWizard::WizardPixmap>(arg));
    return context->throwError(QString::fromLatin1("WizardPixmap(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWizard_WizardPixmap_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWizard::WizardPixmap value = qscriptvalue_cast<QWizard::WizardPixmap>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWizard_WizardPixmap_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWizard::WizardPixmap value = qscriptvalue_cast<QWizard::WizardPixmap>(context->thisObject());
    return QScriptValue(engine, qtscript_QWizard_WizardPixmap_toStringHelper(value));
}

static QScriptValue qtscript_create_QWizard_WizardPixmap_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWizard_WizardPixmap,
        qtscript_QWizard_WizardPixmap_valueOf, qtscript_QWizard_WizardPixmap_toString);
    qScriptRegisterMetaType<QWizard::WizardPixmap>(engine, qtscript_QWizard_WizardPixmap_toScriptValue,
        qtscript_QWizard_WizardPixmap_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWizard_WizardPixmap_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWizard_WizardPixmap_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWizard::WizardOption
//

static const QWizard::WizardOption qtscript_QWizard_WizardOption_values[] = {
    QWizard::IndependentPages
    , QWizard::IgnoreSubTitles
    , QWizard::ExtendedWatermarkPixmap
    , QWizard::NoDefaultButton
    , QWizard::NoBackButtonOnStartPage
    , QWizard::NoBackButtonOnLastPage
    , QWizard::DisabledBackButtonOnLastPage
    , QWizard::HaveNextButtonOnLastPage
    , QWizard::HaveFinishButtonOnEarlyPages
    , QWizard::NoCancelButton
    , QWizard::CancelButtonOnLeft
    , QWizard::HaveHelpButton
    , QWizard::HelpButtonOnRight
    , QWizard::HaveCustomButton1
    , QWizard::HaveCustomButton2
    , QWizard::HaveCustomButton3
};

static const char * const qtscript_QWizard_WizardOption_keys[] = {
    "IndependentPages"
    , "IgnoreSubTitles"
    , "ExtendedWatermarkPixmap"
    , "NoDefaultButton"
    , "NoBackButtonOnStartPage"
    , "NoBackButtonOnLastPage"
    , "DisabledBackButtonOnLastPage"
    , "HaveNextButtonOnLastPage"
    , "HaveFinishButtonOnEarlyPages"
    , "NoCancelButton"
    , "CancelButtonOnLeft"
    , "HaveHelpButton"
    , "HelpButtonOnRight"
    , "HaveCustomButton1"
    , "HaveCustomButton2"
    , "HaveCustomButton3"
};

static QString qtscript_QWizard_WizardOption_toStringHelper(QWizard::WizardOption value)
{
    const QMetaObject *meta = qtscript_QWizard_metaObject();
    int idx = meta->indexOfEnumerator("WizardOption");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QWizard_WizardOption_toScriptValue(QScriptEngine *engine, const QWizard::WizardOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWizard"));
    return clazz.property(qtscript_QWizard_WizardOption_toStringHelper(value));
}

static void qtscript_QWizard_WizardOption_fromScriptValue(const QScriptValue &value, QWizard::WizardOption &out)
{
    out = qvariant_cast<QWizard::WizardOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QWizard_WizardOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QWizard_metaObject();
    int idx = meta->indexOfEnumerator("WizardOption");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QWizard::WizardOption>(arg));
    return context->throwError(QString::fromLatin1("WizardOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWizard_WizardOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWizard::WizardOption value = qscriptvalue_cast<QWizard::WizardOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWizard_WizardOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWizard::WizardOption value = qscriptvalue_cast<QWizard::WizardOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QWizard_WizardOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QWizard_WizardOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWizard_WizardOption,
        qtscript_QWizard_WizardOption_valueOf, qtscript_QWizard_WizardOption_toString);
    qScriptRegisterMetaType<QWizard::WizardOption>(engine, qtscript_QWizard_WizardOption_toScriptValue,
        qtscript_QWizard_WizardOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 16; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWizard_WizardOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWizard_WizardOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWizard::WizardOptions
//

static QScriptValue qtscript_QWizard_WizardOptions_toScriptValue(QScriptEngine *engine, const QWizard::WizardOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QWizard_WizardOptions_fromScriptValue(const QScriptValue &value, QWizard::WizardOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QWizard::WizardOptions>())
        out = qvariant_cast<QWizard::WizardOptions>(var);
    else if (var.userType() == qMetaTypeId<QWizard::WizardOption>())
        out = qvariant_cast<QWizard::WizardOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QWizard_WizardOptions(QScriptContext *context, QScriptEngine *engine)
{
    QWizard::WizardOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QWizard::WizardOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QWizard::WizardOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("WizardOptions(): argument %0 is not of type WizardOption").arg(i));
            }
            result |= qvariant_cast<QWizard::WizardOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QWizard_WizardOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWizard::WizardOptions value = qscriptvalue_cast<QWizard::WizardOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWizard_WizardOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWizard::WizardOptions value = qscriptvalue_cast<QWizard::WizardOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 16; ++i) {
        if ((value & qtscript_QWizard_WizardOption_values[i]) == qtscript_QWizard_WizardOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QWizard_WizardOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QWizard_WizardOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QWizard::WizardOptions>() == otherObj.value<QWizard::WizardOptions>())));
}

static QScriptValue qtscript_create_QWizard_WizardOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QWizard_WizardOptions, qtscript_QWizard_WizardOptions_valueOf,
        qtscript_QWizard_WizardOptions_toString, qtscript_QWizard_WizardOptions_equals);
    qScriptRegisterMetaType<QWizard::WizardOptions>(engine, qtscript_QWizard_WizardOptions_toScriptValue,
        qtscript_QWizard_WizardOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QWizard
//

static QScriptValue qtscript_QWizard_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 23;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QWizard* _q_self = qscriptvalue_cast<QWizard*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWizard.%0(): this object is not a QWizard")
            .arg(qtscript_QWizard_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QWizardPage* _q_arg0 = qscriptvalue_cast<QWizardPage*>(context->argument(0));
        int _q_result = _q_self->addPage(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QWizard::WizardButton _q_arg0 = qscriptvalue_cast<QWizard::WizardButton>(context->argument(0));
        QAbstractButton* _q_result = _q_self->button(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QWizard::WizardButton _q_arg0 = qscriptvalue_cast<QWizard::WizardButton>(context->argument(0));
        QString _q_result = _q_self->buttonText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QWizardPage* _q_result = _q_self->currentPage();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QVariant _q_result = _q_self->field(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->hasVisitedPage(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->nextId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QWizardPage* _q_result = _q_self->page(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QList<int> _q_result = _q_self->pageIds();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QWizard::WizardPixmap _q_arg0 = qscriptvalue_cast<QWizard::WizardPixmap>(context->argument(0));
        QPixmap _q_result = _q_self->pixmap(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->removePage(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        QWizard::WizardButton _q_arg0 = qscriptvalue_cast<QWizard::WizardButton>(context->argument(0));
        QAbstractButton* _q_arg1 = qscriptvalue_cast<QAbstractButton*>(context->argument(1));
        _q_self->setButton(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QList<QWizard::WizardButton> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setButtonLayout(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        QWizard::WizardButton _q_arg0 = qscriptvalue_cast<QWizard::WizardButton>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setButtonText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setField(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QWizard::WizardOption _q_arg0 = qscriptvalue_cast<QWizard::WizardOption>(context->argument(0));
        _q_self->setOption(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QWizard::WizardOption _q_arg0 = qscriptvalue_cast<QWizard::WizardOption>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QWizardPage* _q_arg1 = qscriptvalue_cast<QWizardPage*>(context->argument(1));
        _q_self->setPage(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 2) {
        QWizard::WizardPixmap _q_arg0 = qscriptvalue_cast<QWizard::WizardPixmap>(context->argument(0));
        QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
        _q_self->setPixmap(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setSideWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->sideWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QWizard::WizardOption _q_arg0 = qscriptvalue_cast<QWizard::WizardOption>(context->argument(0));
        bool _q_result = _q_self->testOption(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->validateCurrentPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        QList<int> _q_result = _q_self->visitedPages();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 23: {
    QString result = QString::fromLatin1("QWizard");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWizard_throw_ambiguity_error_helper(context,
        qtscript_QWizard_function_names[_id+1],
        qtscript_QWizard_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWizard_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWizard(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QWizard* _q_cpp_result = new QtScriptShell_QWizard();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWizard*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QWizard* _q_cpp_result = new QtScriptShell_QWizard(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWizard*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QtScriptShell_QWizard* _q_cpp_result = new QtScriptShell_QWizard(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWizard*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWizard_throw_ambiguity_error_helper(context,
        qtscript_QWizard_function_names[_id],
        qtscript_QWizard_function_signatures[_id]);
}

static QScriptValue qtscript_QWizard_toScriptValue(QScriptEngine *engine, QWizard* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QWizard_fromScriptValue(const QScriptValue &value, QWizard* &out)
{
    out = qobject_cast<QWizard*>(value.toQObject());
}

QScriptValue qtscript_create_QWizard_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWizard*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWizard*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDialog*>()));
    for (int i = 0; i < 24; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWizard_prototype_call, qtscript_QWizard_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWizard_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QWizard*>(engine, qtscript_QWizard_toScriptValue, 
        qtscript_QWizard_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWizard_static_call, proto, qtscript_QWizard_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("WizardButton"),
        qtscript_create_QWizard_WizardButton_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WizardStyle"),
        qtscript_create_QWizard_WizardStyle_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WizardPixmap"),
        qtscript_create_QWizard_WizardPixmap_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WizardOption"),
        qtscript_create_QWizard_WizardOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WizardOptions"),
        qtscript_create_QWizard_WizardOptions_class(engine));
    return ctor;
}
