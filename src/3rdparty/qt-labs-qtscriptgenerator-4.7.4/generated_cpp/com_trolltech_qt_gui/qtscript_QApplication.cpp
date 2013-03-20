#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qapplication.h>
#include <QBasicTimer>
#include <QFont>
#include <QFontMetrics>
#include <QIcon>
#include <QLocale>
#include <QPalette>
#include <QVariant>
#include <qapplication.h>
#include <qbytearray.h>
#include <qclipboard.h>
#include <qcoreapplication.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdesktopwidget.h>
#include <qfont.h>
#include <qicon.h>
#include <qinputcontext.h>
#include <qlist.h>
#include <qlocale.h>
#include <qobject.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qsessionmanager.h>
#include <qsize.h>
#include <qstringlist.h>
#include <qstyle.h>
#include <qtranslator.h>
#include <qwidget.h>

#include "qtscriptshell_QApplication.h"

static const char * const qtscript_QApplication_function_names[] = {
    "QApplication"
    // static
    , "activeModalWidget"
    , "activePopupWidget"
    , "activeWindow"
    , "alert"
    , "allWidgets"
    , "beep"
    , "changeOverrideCursor"
    , "clipboard"
    , "colorSpec"
    , "desktop"
    , "desktopSettingsAware"
    , "focusWidget"
    , "font"
    , "isEffectEnabled"
    , "isLeftToRight"
    , "isRightToLeft"
    , "keyboardInputDirection"
    , "keyboardInputLocale"
    , "keyboardModifiers"
    , "mouseButtons"
    , "overrideCursor_private"
    , "palette"
    , "restoreOverrideCursor"
    , "setActiveWindow"
    , "setColorSpec"
    , "setDesktopSettingsAware"
    , "setEffectEnabled"
    , "setFont"
    , "setGraphicsSystem"
    , "setOverrideCursor"
    , "setPalette"
    , "setStyle"
    , "style"
    , "syncX"
    , "topLevelAt"
    , "topLevelWidgets"
    , "type"
    , "widgetAt"
    // prototype
    , "inputContext"
    , "isSessionRestored"
    , "sessionId"
    , "sessionKey"
    , "setInputContext"
    , "toString"
};

static const char * const qtscript_QApplication_function_signatures[] = {
    ""
    // static
    , ""
    , ""
    , ""
    , "QWidget widget, int duration"
    , ""
    , ""
    , "QCursor arg__1"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "\nQWidget arg__1"
    , "UIEffect arg__1"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "\nQWidget arg__1"
    , ""
    , "QWidget act"
    , "int arg__1"
    , "bool arg__1"
    , "UIEffect arg__1, bool enable"
    , "QFont arg__1, char className"
    , "String arg__1"
    , "QCursor arg__1"
    , "QPalette arg__1, char className"
    , "QStyle arg__1\nString arg__1"
    , ""
    , ""
    , "QPoint p\nint x, int y"
    , ""
    , ""
    , "QPoint p\nint x, int y"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "QInputContext arg__1"
""
};

static const int qtscript_QApplication_function_lengths[] = {
    0
    // static
    , 0
    , 0
    , 0
    , 2
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
    , 0
    , 1
    , 0
    , 1
    , 1
    , 1
    , 2
    , 2
    , 1
    , 1
    , 2
    , 1
    , 0
    , 0
    , 2
    , 0
    , 0
    , 2
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QApplication_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QApplication::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QApplication*)
Q_DECLARE_METATYPE(QtScriptShell_QApplication*)
Q_DECLARE_METATYPE(QApplication::Type)
Q_DECLARE_METATYPE(QApplication::ColorSpec)
Q_DECLARE_METATYPE(QInputContext*)
Q_DECLARE_METATYPE(QList<QWidget*>)
Q_DECLARE_METATYPE(QClipboard*)
Q_DECLARE_METATYPE(QDesktopWidget*)
Q_DECLARE_METATYPE(Qt::UIEffect)
Q_DECLARE_METATYPE(Qt::LayoutDirection)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(QCursor*)
Q_DECLARE_METATYPE(QStyle*)
Q_DECLARE_METATYPE(QCoreApplication*)

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
// QApplication::Type
//

static const QApplication::Type qtscript_QApplication_Type_values[] = {
    QApplication::Tty
    , QApplication::GuiClient
    , QApplication::GuiServer
};

static const char * const qtscript_QApplication_Type_keys[] = {
    "Tty"
    , "GuiClient"
    , "GuiServer"
};

static QString qtscript_QApplication_Type_toStringHelper(QApplication::Type value)
{
    if ((value >= QApplication::Tty) && (value <= QApplication::GuiServer))
        return qtscript_QApplication_Type_keys[static_cast<int>(value)-static_cast<int>(QApplication::Tty)];
    return QString();
}

static QScriptValue qtscript_QApplication_Type_toScriptValue(QScriptEngine *engine, const QApplication::Type &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QApplication"));
    return clazz.property(qtscript_QApplication_Type_toStringHelper(value));
}

static void qtscript_QApplication_Type_fromScriptValue(const QScriptValue &value, QApplication::Type &out)
{
    out = qvariant_cast<QApplication::Type>(value.toVariant());
}

static QScriptValue qtscript_construct_QApplication_Type(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QApplication::Tty) && (arg <= QApplication::GuiServer))
        return qScriptValueFromValue(engine,  static_cast<QApplication::Type>(arg));
    return context->throwError(QString::fromLatin1("Type(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QApplication_Type_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QApplication::Type value = qscriptvalue_cast<QApplication::Type>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QApplication_Type_toString(QScriptContext *context, QScriptEngine *engine)
{
    QApplication::Type value = qscriptvalue_cast<QApplication::Type>(context->thisObject());
    return QScriptValue(engine, qtscript_QApplication_Type_toStringHelper(value));
}

static QScriptValue qtscript_create_QApplication_Type_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QApplication_Type,
        qtscript_QApplication_Type_valueOf, qtscript_QApplication_Type_toString);
    qScriptRegisterMetaType<QApplication::Type>(engine, qtscript_QApplication_Type_toScriptValue,
        qtscript_QApplication_Type_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QApplication_Type_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QApplication_Type_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QApplication::ColorSpec
//

static const QApplication::ColorSpec qtscript_QApplication_ColorSpec_values[] = {
    QApplication::NormalColor
    , QApplication::CustomColor
    , QApplication::ManyColor
};

static const char * const qtscript_QApplication_ColorSpec_keys[] = {
    "NormalColor"
    , "CustomColor"
    , "ManyColor"
};

static QString qtscript_QApplication_ColorSpec_toStringHelper(QApplication::ColorSpec value)
{
    if ((value >= QApplication::NormalColor) && (value <= QApplication::ManyColor))
        return qtscript_QApplication_ColorSpec_keys[static_cast<int>(value)-static_cast<int>(QApplication::NormalColor)];
    return QString();
}

static QScriptValue qtscript_QApplication_ColorSpec_toScriptValue(QScriptEngine *engine, const QApplication::ColorSpec &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QApplication"));
    return clazz.property(qtscript_QApplication_ColorSpec_toStringHelper(value));
}

static void qtscript_QApplication_ColorSpec_fromScriptValue(const QScriptValue &value, QApplication::ColorSpec &out)
{
    out = qvariant_cast<QApplication::ColorSpec>(value.toVariant());
}

static QScriptValue qtscript_construct_QApplication_ColorSpec(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QApplication::NormalColor) && (arg <= QApplication::ManyColor))
        return qScriptValueFromValue(engine,  static_cast<QApplication::ColorSpec>(arg));
    return context->throwError(QString::fromLatin1("ColorSpec(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QApplication_ColorSpec_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QApplication::ColorSpec value = qscriptvalue_cast<QApplication::ColorSpec>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QApplication_ColorSpec_toString(QScriptContext *context, QScriptEngine *engine)
{
    QApplication::ColorSpec value = qscriptvalue_cast<QApplication::ColorSpec>(context->thisObject());
    return QScriptValue(engine, qtscript_QApplication_ColorSpec_toStringHelper(value));
}

static QScriptValue qtscript_create_QApplication_ColorSpec_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QApplication_ColorSpec,
        qtscript_QApplication_ColorSpec_valueOf, qtscript_QApplication_ColorSpec_toString);
    qScriptRegisterMetaType<QApplication::ColorSpec>(engine, qtscript_QApplication_ColorSpec_toScriptValue,
        qtscript_QApplication_ColorSpec_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QApplication_ColorSpec_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QApplication_ColorSpec_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QApplication
//

static QScriptValue qtscript_QApplication_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QApplication* _q_self = qscriptvalue_cast<QApplication*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QApplication.%0(): this object is not a QApplication")
            .arg(qtscript_QApplication_function_names[_id+39]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QInputContext* _q_result = _q_self->inputContext();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSessionRestored();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->sessionId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->sessionKey();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QInputContext* _q_arg0 = qscriptvalue_cast<QInputContext*>(context->argument(0));
        _q_self->setInputContext(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QApplication");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QApplication_throw_ambiguity_error_helper(context,
        qtscript_QApplication_function_names[_id+39],
        qtscript_QApplication_function_signatures[_id+39]);
}

static QScriptValue qtscript_QApplication_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QApplication cannot be constructed"));
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = QApplication::activeModalWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = QApplication::activePopupWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = QApplication::activeWindow();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QApplication::alert(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QApplication::alert(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QList<QWidget*> _q_result = QApplication::allWidgets();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QApplication::beep();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QCursor _q_arg0 = qscriptvalue_cast<QCursor>(context->argument(0));
        QApplication::changeOverrideCursor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QClipboard* _q_result = QApplication::clipboard();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = QApplication::colorSpec();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QDesktopWidget* _q_result = QApplication::desktop();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = QApplication::desktopSettingsAware();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = QApplication::focusWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QFont _q_result = QApplication::font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFont _q_result = QApplication::font(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        Qt::UIEffect _q_arg0 = qscriptvalue_cast<Qt::UIEffect>(context->argument(0));
        bool _q_result = QApplication::isEffectEnabled(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = QApplication::isLeftToRight();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        bool _q_result = QApplication::isRightToLeft();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        Qt::LayoutDirection _q_result = QApplication::keyboardInputDirection();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QLocale _q_result = QApplication::keyboardInputLocale();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QFlags<Qt::KeyboardModifier> _q_result = QApplication::keyboardModifiers();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QFlags<Qt::MouseButton> _q_result = QApplication::mouseButtons();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        QCursor* _q_result = QApplication::overrideCursor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        QPalette _q_result = QApplication::palette();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QPalette _q_result = QApplication::palette(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        QApplication::restoreOverrideCursor();
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QApplication::setActiveWindow(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QApplication::setColorSpec(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        QApplication::setDesktopSettingsAware(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        Qt::UIEffect _q_arg0 = qscriptvalue_cast<Qt::UIEffect>(context->argument(0));
        QApplication::setEffectEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        Qt::UIEffect _q_arg0 = qscriptvalue_cast<Qt::UIEffect>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        QApplication::setEffectEnabled(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 2) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QApplication::setFont(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QApplication::setGraphicsSystem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QCursor _q_arg0 = qscriptvalue_cast<QCursor>(context->argument(0));
        QApplication::setOverrideCursor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 2) {
        QPalette _q_arg0 = qscriptvalue_cast<QPalette>(context->argument(0));

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                QApplication::setPalette(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QStyle*>(context->argument(0))) {
            QStyle* _q_arg0 = qscriptvalue_cast<QStyle*>(context->argument(0));
            QApplication::setStyle(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QStyle* _q_result = QApplication::setStyle(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        QStyle* _q_result = QApplication::style();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 0) {
        QApplication::syncX();
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QWidget* _q_result = QApplication::topLevelAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QWidget* _q_result = QApplication::topLevelAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        QList<QWidget*> _q_result = QApplication::topLevelWidgets();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 0) {
        QApplication::Type _q_result = QApplication::type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QWidget* _q_result = QApplication::widgetAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QWidget* _q_result = QApplication::widgetAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QApplication_throw_ambiguity_error_helper(context,
        qtscript_QApplication_function_names[_id],
        qtscript_QApplication_function_signatures[_id]);
}

static QScriptValue qtscript_QApplication_toScriptValue(QScriptEngine *engine, QApplication* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QApplication_fromScriptValue(const QScriptValue &value, QApplication* &out)
{
    out = qobject_cast<QApplication*>(value.toQObject());
}

QScriptValue qtscript_create_QApplication_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QApplication*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QApplication*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QCoreApplication*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QApplication_prototype_call, qtscript_QApplication_function_lengths[i+39]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QApplication_function_names[i+39]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QApplication*>(engine, qtscript_QApplication_toScriptValue, 
        qtscript_QApplication_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QApplication_static_call, proto, qtscript_QApplication_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 38; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QApplication_static_call,
            qtscript_QApplication_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QApplication_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Type"),
        qtscript_create_QApplication_Type_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ColorSpec"),
        qtscript_create_QApplication_ColorSpec_class(engine, ctor));
    return ctor;
}
