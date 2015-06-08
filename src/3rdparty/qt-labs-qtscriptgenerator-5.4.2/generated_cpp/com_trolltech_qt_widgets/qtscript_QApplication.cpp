#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

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
#include <qlist.h>
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
    , "colorSpec"
    , "desktop"
    , "focusWidget"
    , "font"
    , "isEffectEnabled"
    , "palette"
    , "setActiveWindow"
    , "setColorSpec"
    , "setEffectEnabled"
    , "setFont"
    , "setPalette"
    , "setStyle"
    , "style"
    , "topLevelAt"
    , "topLevelWidgets"
    , "widgetAt"
    // prototype
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
    , ""
    , ""
    , ""
    , "QWidget arg__1"
    , "UIEffect arg__1"
    , "QWidget arg__1"
    , "QWidget act"
    , "int arg__1"
    , "UIEffect arg__1, bool enable"
    , "QFont arg__1, char className"
    , "QPalette arg__1, char className"
    , "QStyle arg__1\nString arg__1"
    , ""
    , "QPoint p\nint x, int y"
    , ""
    , "QPoint p\nint x, int y"
    // prototype
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
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 2
    , 1
    , 0
    , 2
    , 0
    , 2
    // prototype
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
Q_DECLARE_METATYPE(QApplication::ColorSpec)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QList<QWidget* >)
Q_DECLARE_METATYPE(QDesktopWidget*)
Q_DECLARE_METATYPE(const QWidget*)
Q_DECLARE_METATYPE(Qt::UIEffect)
Q_DECLARE_METATYPE(QStyle*)
Q_DECLARE_METATYPE(QGuiApplication*)

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
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QApplication* _q_self = qscriptvalue_cast<QApplication*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QApplication.%0(): this object is not a QApplication")
            .arg(qtscript_QApplication_function_names[_id+23]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QApplication");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QApplication_throw_ambiguity_error_helper(context,
        qtscript_QApplication_function_names[_id+23],
        qtscript_QApplication_function_signatures[_id+23]);
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
        QList<QWidget* > _q_result = QApplication::allWidgets();
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
    if (context->argumentCount() == 0) {
        int _q_result = QApplication::colorSpec();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QDesktopWidget* _q_result = QApplication::desktop();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = QApplication::focusWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QFont _q_result = QApplication::font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        const QWidget* _q_arg0 = qscriptvalue_cast<const QWidget*>(context->argument(0));
        QFont _q_result = QApplication::font(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        Qt::UIEffect _q_arg0 = qscriptvalue_cast<Qt::UIEffect>(context->argument(0));
        bool _q_result = QApplication::isEffectEnabled(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        const QWidget* _q_arg0 = qscriptvalue_cast<const QWidget*>(context->argument(0));
        QPalette _q_result = QApplication::palette(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QApplication::setActiveWindow(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QApplication::setColorSpec(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
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

    case 16:
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

    case 17:
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

    case 18:
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

    case 19:
    if (context->argumentCount() == 0) {
        QStyle* _q_result = QApplication::style();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
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

    case 21:
    if (context->argumentCount() == 0) {
        QList<QWidget* > _q_result = QApplication::topLevelWidgets();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 22:
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
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGuiApplication*>()));

    qScriptRegisterMetaType<QApplication*>(engine, qtscript_QApplication_toScriptValue, 
        qtscript_QApplication_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QApplication_static_call, proto, qtscript_QApplication_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 22; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QApplication_static_call,
            qtscript_QApplication_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QApplication_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("ColorSpec"),
        qtscript_create_QApplication_ColorSpec_class(engine, ctor));
    return ctor;
}
