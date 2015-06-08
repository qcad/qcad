#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qmessagebox.h>
#include <QPixmap>
#include <QVariant>
#include <qabstractbutton.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcheckbox.h>
#include <qcoreevent.h>
#include <qcursor.h>
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
#include <qmessagebox.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qpushbutton.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QMessageBox.h"

static const char * const qtscript_QMessageBox_function_names[] = {
    "QMessageBox"
    // static
    , "about"
    , "aboutQt"
    , "critical"
    , "information"
    , "question"
    , "warning"
    // prototype
    , "addButton"
    , "button"
    , "buttonRole"
    , "buttons"
    , "checkBox"
    , "clickedButton"
    , "defaultButton"
    , "escapeButton"
    , "open"
    , "removeButton"
    , "setCheckBox"
    , "setDefaultButton"
    , "setEscapeButton"
    , "standardButton"
    , "toString"
};

static const char * const qtscript_QMessageBox_function_signatures[] = {
    "Icon icon, String title, String text, StandardButtons buttons, QWidget parent, WindowFlags flags\nQWidget parent"
    // static
    , "QWidget parent, String title, String text"
    , "QWidget parent, String title"
    , "QWidget parent, String title, String text, StandardButtons buttons, StandardButton defaultButton\nQWidget parent, String title, String text, StandardButton button0, StandardButton button1"
    , "QWidget parent, String title, String text, StandardButtons buttons, StandardButton defaultButton\nQWidget parent, String title, String text, StandardButton button0, StandardButton button1"
    , "QWidget parent, String title, String text, StandardButtons buttons, StandardButton defaultButton\nQWidget parent, String title, String text, StandardButton button0, StandardButton button1"
    , "QWidget parent, String title, String text, StandardButtons buttons, StandardButton defaultButton\nQWidget parent, String title, String text, StandardButton button0, StandardButton button1"
    // prototype
    , "QAbstractButton button, ButtonRole role\nStandardButton button\nString text, ButtonRole role"
    , "StandardButton which"
    , "QAbstractButton button"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QObject receiver, char member"
    , "QAbstractButton button"
    , "QCheckBox cb"
    , "StandardButton button\nQPushButton button"
    , "QAbstractButton button\nStandardButton button"
    , "QAbstractButton button"
""
};

static const int qtscript_QMessageBox_function_lengths[] = {
    6
    // static
    , 3
    , 2
    , 5
    , 5
    , 5
    , 5
    // prototype
    , 2
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QMessageBox_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMessageBox::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QMessageBox_metaObject()
{
    return &QMessageBox::staticMetaObject;
}

Q_DECLARE_METATYPE(QMessageBox*)
Q_DECLARE_METATYPE(QtScriptShell_QMessageBox*)
Q_DECLARE_METATYPE(QMessageBox::StandardButton)
Q_DECLARE_METATYPE(QFlags<QMessageBox::StandardButton>)
Q_DECLARE_METATYPE(QMessageBox::Icon)
Q_DECLARE_METATYPE(QMessageBox::ButtonRole)
Q_DECLARE_METATYPE(QAbstractButton*)
Q_DECLARE_METATYPE(QPushButton*)
Q_DECLARE_METATYPE(QList<QAbstractButton* >)
Q_DECLARE_METATYPE(QCheckBox*)
Q_DECLARE_METATYPE(const char*)
Q_DECLARE_METATYPE(QWidget*)
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
// QMessageBox::StandardButton
//

static const QMessageBox::StandardButton qtscript_QMessageBox_StandardButton_values[] = {
    QMessageBox::NoButton
    , QMessageBox::Default
    , QMessageBox::Escape
    , QMessageBox::FlagMask
    , QMessageBox::ButtonMask
    , QMessageBox::Ok
    , QMessageBox::Save
    , QMessageBox::SaveAll
    , QMessageBox::Open
    , QMessageBox::Yes
    , QMessageBox::YesToAll
    , QMessageBox::No
    , QMessageBox::NoToAll
    , QMessageBox::Abort
    , QMessageBox::Retry
    , QMessageBox::Ignore
    , QMessageBox::Close
    , QMessageBox::Cancel
    , QMessageBox::Discard
    , QMessageBox::Help
    , QMessageBox::Apply
    , QMessageBox::Reset
    , QMessageBox::RestoreDefaults
};

static const char * const qtscript_QMessageBox_StandardButton_keys[] = {
    "NoButton"
    , "Default"
    , "Escape"
    , "FlagMask"
    , "ButtonMask"
    , "Ok"
    , "Save"
    , "SaveAll"
    , "Open"
    , "Yes"
    , "YesToAll"
    , "No"
    , "NoToAll"
    , "Abort"
    , "Retry"
    , "Ignore"
    , "Close"
    , "Cancel"
    , "Discard"
    , "Help"
    , "Apply"
    , "Reset"
    , "RestoreDefaults"
};

static QString qtscript_QMessageBox_StandardButton_toStringHelper(QMessageBox::StandardButton value)
{
    for (int i = 0; i < 23; ++i) {
        if (qtscript_QMessageBox_StandardButton_values[i] == value)
            return QString::fromLatin1(qtscript_QMessageBox_StandardButton_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QMessageBox_StandardButton_toScriptValue(QScriptEngine *engine, const QMessageBox::StandardButton &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QMessageBox"));
    return clazz.property(qtscript_QMessageBox_StandardButton_toStringHelper(value));
}

static void qtscript_QMessageBox_StandardButton_fromScriptValue(const QScriptValue &value, QMessageBox::StandardButton &out)
{
    out = qvariant_cast<QMessageBox::StandardButton>(value.toVariant());
}

static QScriptValue qtscript_construct_QMessageBox_StandardButton(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 23; ++i) {
        if (qtscript_QMessageBox_StandardButton_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QMessageBox::StandardButton>(arg));
    }
    return context->throwError(QString::fromLatin1("StandardButton(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QMessageBox_StandardButton_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMessageBox::StandardButton value = qscriptvalue_cast<QMessageBox::StandardButton>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMessageBox_StandardButton_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMessageBox::StandardButton value = qscriptvalue_cast<QMessageBox::StandardButton>(context->thisObject());
    return QScriptValue(engine, qtscript_QMessageBox_StandardButton_toStringHelper(value));
}

static QScriptValue qtscript_create_QMessageBox_StandardButton_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QMessageBox_StandardButton,
        qtscript_QMessageBox_StandardButton_valueOf, qtscript_QMessageBox_StandardButton_toString);
    qScriptRegisterMetaType<QMessageBox::StandardButton>(engine, qtscript_QMessageBox_StandardButton_toScriptValue,
        qtscript_QMessageBox_StandardButton_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 23; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QMessageBox_StandardButton_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QMessageBox_StandardButton_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QMessageBox::StandardButtons
//

static QScriptValue qtscript_QMessageBox_StandardButtons_toScriptValue(QScriptEngine *engine, const QMessageBox::StandardButtons &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QMessageBox_StandardButtons_fromScriptValue(const QScriptValue &value, QMessageBox::StandardButtons &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QMessageBox::StandardButtons>())
        out = qvariant_cast<QMessageBox::StandardButtons>(var);
    else if (var.userType() == qMetaTypeId<QMessageBox::StandardButton>())
        out = qvariant_cast<QMessageBox::StandardButton>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QMessageBox_StandardButtons(QScriptContext *context, QScriptEngine *engine)
{
    QMessageBox::StandardButtons result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QMessageBox::StandardButtons>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QMessageBox::StandardButton>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("StandardButtons(): argument %0 is not of type StandardButton").arg(i));
            }
            result |= qvariant_cast<QMessageBox::StandardButton>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QMessageBox_StandardButtons_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMessageBox::StandardButtons value = qscriptvalue_cast<QMessageBox::StandardButtons>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMessageBox_StandardButtons_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMessageBox::StandardButtons value = qscriptvalue_cast<QMessageBox::StandardButtons>(context->thisObject());
    QString result;
    for (int i = 0; i < 23; ++i) {
        if ((value & qtscript_QMessageBox_StandardButton_values[i]) == qtscript_QMessageBox_StandardButton_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QMessageBox_StandardButton_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QMessageBox_StandardButtons_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QMessageBox::StandardButtons>() == otherObj.value<QMessageBox::StandardButtons>())));
}

static QScriptValue qtscript_create_QMessageBox_StandardButtons_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QMessageBox_StandardButtons, qtscript_QMessageBox_StandardButtons_valueOf,
        qtscript_QMessageBox_StandardButtons_toString, qtscript_QMessageBox_StandardButtons_equals);
    qScriptRegisterMetaType<QMessageBox::StandardButtons>(engine, qtscript_QMessageBox_StandardButtons_toScriptValue,
        qtscript_QMessageBox_StandardButtons_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QMessageBox::Icon
//

static const QMessageBox::Icon qtscript_QMessageBox_Icon_values[] = {
    QMessageBox::NoIcon
    , QMessageBox::Information
    , QMessageBox::Warning
    , QMessageBox::Critical
    , QMessageBox::Question
};

static const char * const qtscript_QMessageBox_Icon_keys[] = {
    "NoIcon"
    , "Information"
    , "Warning"
    , "Critical"
    , "Question"
};

static QString qtscript_QMessageBox_Icon_toStringHelper(QMessageBox::Icon value)
{
    const QMetaObject *meta = qtscript_QMessageBox_metaObject();
    int idx = meta->indexOfEnumerator("Icon");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QMessageBox_Icon_toScriptValue(QScriptEngine *engine, const QMessageBox::Icon &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QMessageBox"));
    return clazz.property(qtscript_QMessageBox_Icon_toStringHelper(value));
}

static void qtscript_QMessageBox_Icon_fromScriptValue(const QScriptValue &value, QMessageBox::Icon &out)
{
    out = qvariant_cast<QMessageBox::Icon>(value.toVariant());
}

static QScriptValue qtscript_construct_QMessageBox_Icon(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QMessageBox_metaObject();
    int idx = meta->indexOfEnumerator("Icon");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QMessageBox::Icon>(arg));
    return context->throwError(QString::fromLatin1("Icon(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QMessageBox_Icon_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMessageBox::Icon value = qscriptvalue_cast<QMessageBox::Icon>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMessageBox_Icon_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMessageBox::Icon value = qscriptvalue_cast<QMessageBox::Icon>(context->thisObject());
    return QScriptValue(engine, qtscript_QMessageBox_Icon_toStringHelper(value));
}

static QScriptValue qtscript_create_QMessageBox_Icon_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QMessageBox_Icon,
        qtscript_QMessageBox_Icon_valueOf, qtscript_QMessageBox_Icon_toString);
    qScriptRegisterMetaType<QMessageBox::Icon>(engine, qtscript_QMessageBox_Icon_toScriptValue,
        qtscript_QMessageBox_Icon_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QMessageBox_Icon_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QMessageBox_Icon_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QMessageBox::ButtonRole
//

static const QMessageBox::ButtonRole qtscript_QMessageBox_ButtonRole_values[] = {
    QMessageBox::InvalidRole
    , QMessageBox::AcceptRole
    , QMessageBox::RejectRole
    , QMessageBox::DestructiveRole
    , QMessageBox::ActionRole
    , QMessageBox::HelpRole
    , QMessageBox::YesRole
    , QMessageBox::NoRole
    , QMessageBox::ResetRole
    , QMessageBox::ApplyRole
    , QMessageBox::NRoles
};

static const char * const qtscript_QMessageBox_ButtonRole_keys[] = {
    "InvalidRole"
    , "AcceptRole"
    , "RejectRole"
    , "DestructiveRole"
    , "ActionRole"
    , "HelpRole"
    , "YesRole"
    , "NoRole"
    , "ResetRole"
    , "ApplyRole"
    , "NRoles"
};

static QString qtscript_QMessageBox_ButtonRole_toStringHelper(QMessageBox::ButtonRole value)
{
    if ((value >= QMessageBox::InvalidRole) && (value <= QMessageBox::NRoles))
        return qtscript_QMessageBox_ButtonRole_keys[static_cast<int>(value)-static_cast<int>(QMessageBox::InvalidRole)];
    return QString();
}

static QScriptValue qtscript_QMessageBox_ButtonRole_toScriptValue(QScriptEngine *engine, const QMessageBox::ButtonRole &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QMessageBox"));
    return clazz.property(qtscript_QMessageBox_ButtonRole_toStringHelper(value));
}

static void qtscript_QMessageBox_ButtonRole_fromScriptValue(const QScriptValue &value, QMessageBox::ButtonRole &out)
{
    out = qvariant_cast<QMessageBox::ButtonRole>(value.toVariant());
}

static QScriptValue qtscript_construct_QMessageBox_ButtonRole(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QMessageBox::InvalidRole) && (arg <= QMessageBox::NRoles))
        return qScriptValueFromValue(engine,  static_cast<QMessageBox::ButtonRole>(arg));
    return context->throwError(QString::fromLatin1("ButtonRole(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QMessageBox_ButtonRole_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMessageBox::ButtonRole value = qscriptvalue_cast<QMessageBox::ButtonRole>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMessageBox_ButtonRole_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMessageBox::ButtonRole value = qscriptvalue_cast<QMessageBox::ButtonRole>(context->thisObject());
    return QScriptValue(engine, qtscript_QMessageBox_ButtonRole_toStringHelper(value));
}

static QScriptValue qtscript_create_QMessageBox_ButtonRole_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QMessageBox_ButtonRole,
        qtscript_QMessageBox_ButtonRole_valueOf, qtscript_QMessageBox_ButtonRole_toString);
    qScriptRegisterMetaType<QMessageBox::ButtonRole>(engine, qtscript_QMessageBox_ButtonRole_toScriptValue,
        qtscript_QMessageBox_ButtonRole_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QMessageBox_ButtonRole_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QMessageBox_ButtonRole_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QMessageBox
//

static QScriptValue qtscript_QMessageBox_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QMessageBox* _q_self = qscriptvalue_cast<QMessageBox*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMessageBox.%0(): this object is not a QMessageBox")
            .arg(qtscript_QMessageBox_function_names[_id+7]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QMessageBox::StandardButton _q_arg0 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(0));
        QPushButton* _q_result = _q_self->addButton(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QAbstractButton*>(context->argument(0))
            && (qMetaTypeId<QMessageBox::ButtonRole>() == context->argument(1).toVariant().userType())) {
            QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
            QMessageBox::ButtonRole _q_arg1 = qscriptvalue_cast<QMessageBox::ButtonRole>(context->argument(1));
            _q_self->addButton(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QMessageBox::ButtonRole>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QMessageBox::ButtonRole _q_arg1 = qscriptvalue_cast<QMessageBox::ButtonRole>(context->argument(1));
            QPushButton* _q_result = _q_self->addButton(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QMessageBox::StandardButton _q_arg0 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(0));
        QAbstractButton* _q_result = _q_self->button(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
        QMessageBox::ButtonRole _q_result = _q_self->buttonRole(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QList<QAbstractButton* > _q_result = _q_self->buttons();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QCheckBox* _q_result = _q_self->checkBox();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QAbstractButton* _q_result = _q_self->clickedButton();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QPushButton* _q_result = _q_self->defaultButton();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QAbstractButton* _q_result = _q_self->escapeButton();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        const char* _q_arg1 = qscriptvalue_cast<const char*>(context->argument(1));
        _q_self->open(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
        _q_self->removeButton(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QCheckBox* _q_arg0 = qscriptvalue_cast<QCheckBox*>(context->argument(0));
        _q_self->setCheckBox(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QMessageBox::StandardButton>() == context->argument(0).toVariant().userType())) {
            QMessageBox::StandardButton _q_arg0 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(0));
            _q_self->setDefaultButton(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QPushButton*>(context->argument(0))) {
            QPushButton* _q_arg0 = qscriptvalue_cast<QPushButton*>(context->argument(0));
            _q_self->setDefaultButton(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QAbstractButton*>(context->argument(0))) {
            QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
            _q_self->setEscapeButton(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QMessageBox::StandardButton>() == context->argument(0).toVariant().userType())) {
            QMessageBox::StandardButton _q_arg0 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(0));
            _q_self->setEscapeButton(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
        QMessageBox::StandardButton _q_result = _q_self->standardButton(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14: {
    QString result = QString::fromLatin1("QMessageBox");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMessageBox_throw_ambiguity_error_helper(context,
        qtscript_QMessageBox_function_names[_id+7],
        qtscript_QMessageBox_function_signatures[_id+7]);
}

static QScriptValue qtscript_QMessageBox_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMessageBox(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QMessageBox* _q_cpp_result = new QtScriptShell_QMessageBox();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMessageBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QMessageBox* _q_cpp_result = new QtScriptShell_QMessageBox(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMessageBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QMessageBox::Icon _q_arg0 = qscriptvalue_cast<QMessageBox::Icon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QtScriptShell_QMessageBox* _q_cpp_result = new QtScriptShell_QMessageBox(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMessageBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 4) {
        QMessageBox::Icon _q_arg0 = qscriptvalue_cast<QMessageBox::Icon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QFlags<QMessageBox::StandardButton> _q_arg3 = qscriptvalue_cast<QFlags<QMessageBox::StandardButton> >(context->argument(3));
        QtScriptShell_QMessageBox* _q_cpp_result = new QtScriptShell_QMessageBox(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMessageBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 5) {
        QMessageBox::Icon _q_arg0 = qscriptvalue_cast<QMessageBox::Icon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QFlags<QMessageBox::StandardButton> _q_arg3 = qscriptvalue_cast<QFlags<QMessageBox::StandardButton> >(context->argument(3));
        QWidget* _q_arg4 = qscriptvalue_cast<QWidget*>(context->argument(4));
        QtScriptShell_QMessageBox* _q_cpp_result = new QtScriptShell_QMessageBox(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMessageBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 6) {
        QMessageBox::Icon _q_arg0 = qscriptvalue_cast<QMessageBox::Icon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QFlags<QMessageBox::StandardButton> _q_arg3 = qscriptvalue_cast<QFlags<QMessageBox::StandardButton> >(context->argument(3));
        QWidget* _q_arg4 = qscriptvalue_cast<QWidget*>(context->argument(4));
        QFlags<Qt::WindowType> _q_arg5 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(5));
        QtScriptShell_QMessageBox* _q_cpp_result = new QtScriptShell_QMessageBox(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMessageBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QMessageBox::about(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QMessageBox::aboutQt(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QMessageBox::aboutQt(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QMessageBox::StandardButton _q_result = QMessageBox::critical(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QFlags<QMessageBox::StandardButton> _q_arg3 = qscriptvalue_cast<QFlags<QMessageBox::StandardButton> >(context->argument(3));
        QMessageBox::StandardButton _q_result = QMessageBox::critical(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isString()
            && context->argument(2).isString()
            && (qMetaTypeId<QFlags<QMessageBox::StandardButton> >() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(4).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QFlags<QMessageBox::StandardButton> _q_arg3 = qscriptvalue_cast<QFlags<QMessageBox::StandardButton> >(context->argument(3));
            QMessageBox::StandardButton _q_arg4 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(4));
            QMessageBox::StandardButton _q_result = QMessageBox::critical(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isString()
            && context->argument(2).isString()
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(4).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QMessageBox::StandardButton _q_arg3 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(3));
            QMessageBox::StandardButton _q_arg4 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(4));
            int _q_result = QMessageBox::critical(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 4:
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QMessageBox::StandardButton _q_result = QMessageBox::information(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isString()
            && context->argument(2).isString()
            && (qMetaTypeId<QFlags<QMessageBox::StandardButton> >() == context->argument(3).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QFlags<QMessageBox::StandardButton> _q_arg3 = qscriptvalue_cast<QFlags<QMessageBox::StandardButton> >(context->argument(3));
            QMessageBox::StandardButton _q_result = QMessageBox::information(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isString()
            && context->argument(2).isString()
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(3).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QMessageBox::StandardButton _q_arg3 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(3));
            QMessageBox::StandardButton _q_result = QMessageBox::information(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 5) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isString()
            && context->argument(2).isString()
            && (qMetaTypeId<QFlags<QMessageBox::StandardButton> >() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(4).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QFlags<QMessageBox::StandardButton> _q_arg3 = qscriptvalue_cast<QFlags<QMessageBox::StandardButton> >(context->argument(3));
            QMessageBox::StandardButton _q_arg4 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(4));
            QMessageBox::StandardButton _q_result = QMessageBox::information(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isString()
            && context->argument(2).isString()
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(4).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QMessageBox::StandardButton _q_arg3 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(3));
            QMessageBox::StandardButton _q_arg4 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(4));
            QMessageBox::StandardButton _q_result = QMessageBox::information(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 5:
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QMessageBox::StandardButton _q_result = QMessageBox::question(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QFlags<QMessageBox::StandardButton> _q_arg3 = qscriptvalue_cast<QFlags<QMessageBox::StandardButton> >(context->argument(3));
        QMessageBox::StandardButton _q_result = QMessageBox::question(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isString()
            && context->argument(2).isString()
            && (qMetaTypeId<QFlags<QMessageBox::StandardButton> >() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(4).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QFlags<QMessageBox::StandardButton> _q_arg3 = qscriptvalue_cast<QFlags<QMessageBox::StandardButton> >(context->argument(3));
            QMessageBox::StandardButton _q_arg4 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(4));
            QMessageBox::StandardButton _q_result = QMessageBox::question(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isString()
            && context->argument(2).isString()
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(4).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QMessageBox::StandardButton _q_arg3 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(3));
            QMessageBox::StandardButton _q_arg4 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(4));
            int _q_result = QMessageBox::question(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 6:
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QMessageBox::StandardButton _q_result = QMessageBox::warning(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QFlags<QMessageBox::StandardButton> _q_arg3 = qscriptvalue_cast<QFlags<QMessageBox::StandardButton> >(context->argument(3));
        QMessageBox::StandardButton _q_result = QMessageBox::warning(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isString()
            && context->argument(2).isString()
            && (qMetaTypeId<QFlags<QMessageBox::StandardButton> >() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(4).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QFlags<QMessageBox::StandardButton> _q_arg3 = qscriptvalue_cast<QFlags<QMessageBox::StandardButton> >(context->argument(3));
            QMessageBox::StandardButton _q_arg4 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(4));
            QMessageBox::StandardButton _q_result = QMessageBox::warning(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isString()
            && context->argument(2).isString()
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(3).toVariant().userType())
            && (qMetaTypeId<QMessageBox::StandardButton>() == context->argument(4).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QString _q_arg2 = context->argument(2).toString();
            QMessageBox::StandardButton _q_arg3 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(3));
            QMessageBox::StandardButton _q_arg4 = qscriptvalue_cast<QMessageBox::StandardButton>(context->argument(4));
            int _q_result = QMessageBox::warning(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMessageBox_throw_ambiguity_error_helper(context,
        qtscript_QMessageBox_function_names[_id],
        qtscript_QMessageBox_function_signatures[_id]);
}

static QScriptValue qtscript_QMessageBox_toScriptValue(QScriptEngine *engine, QMessageBox* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QMessageBox_fromScriptValue(const QScriptValue &value, QMessageBox* &out)
{
    out = qobject_cast<QMessageBox*>(value.toQObject());
}

QScriptValue qtscript_create_QMessageBox_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMessageBox*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMessageBox*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDialog*>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMessageBox_prototype_call, qtscript_QMessageBox_function_lengths[i+7]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMessageBox_function_names[i+7]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QMessageBox*>(engine, qtscript_QMessageBox_toScriptValue, 
        qtscript_QMessageBox_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMessageBox_static_call, proto, qtscript_QMessageBox_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMessageBox_static_call,
            qtscript_QMessageBox_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QMessageBox_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("StandardButton"),
        qtscript_create_QMessageBox_StandardButton_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StandardButtons"),
        qtscript_create_QMessageBox_StandardButtons_class(engine));
    ctor.setProperty(QString::fromLatin1("Icon"),
        qtscript_create_QMessageBox_Icon_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ButtonRole"),
        qtscript_create_QMessageBox_ButtonRole_class(engine, ctor));
    return ctor;
}
