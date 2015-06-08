#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdialogbuttonbox.h>
#include <QVariant>
#include <qabstractbutton.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdialogbuttonbox.h>
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
#include <qpushbutton.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QDialogButtonBox.h"

static const char * const qtscript_QDialogButtonBox_function_names[] = {
    "QDialogButtonBox"
    // static
    // prototype
    , "addButton"
    , "button"
    , "buttonRole"
    , "buttons"
    , "clear"
    , "removeButton"
    , "standardButton"
    , "toString"
};

static const char * const qtscript_QDialogButtonBox_function_signatures[] = {
    "StandardButtons buttons, QWidget parent\nStandardButtons buttons, Orientation orientation, QWidget parent\nQWidget parent\nOrientation orientation, QWidget parent"
    // static
    // prototype
    , "QAbstractButton button, ButtonRole role\nStandardButton button\nString text, ButtonRole role"
    , "StandardButton which"
    , "QAbstractButton button"
    , ""
    , ""
    , "QAbstractButton button"
    , "QAbstractButton button"
""
};

static const int qtscript_QDialogButtonBox_function_lengths[] = {
    3
    // static
    // prototype
    , 2
    , 1
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QDialogButtonBox_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDialogButtonBox::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDialogButtonBox*)
Q_DECLARE_METATYPE(QtScriptShell_QDialogButtonBox*)
Q_DECLARE_METATYPE(QDialogButtonBox::StandardButton)
Q_DECLARE_METATYPE(QFlags<QDialogButtonBox::StandardButton>)
Q_DECLARE_METATYPE(QDialogButtonBox::ButtonLayout)
Q_DECLARE_METATYPE(QDialogButtonBox::ButtonRole)
Q_DECLARE_METATYPE(QAbstractButton*)
Q_DECLARE_METATYPE(QPushButton*)
Q_DECLARE_METATYPE(QList<QAbstractButton* >)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(Qt::Orientation)

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
// QDialogButtonBox::StandardButton
//

static const QDialogButtonBox::StandardButton qtscript_QDialogButtonBox_StandardButton_values[] = {
    QDialogButtonBox::NoButton
    , QDialogButtonBox::Ok
    , QDialogButtonBox::Save
    , QDialogButtonBox::SaveAll
    , QDialogButtonBox::Open
    , QDialogButtonBox::Yes
    , QDialogButtonBox::YesToAll
    , QDialogButtonBox::No
    , QDialogButtonBox::NoToAll
    , QDialogButtonBox::Abort
    , QDialogButtonBox::Retry
    , QDialogButtonBox::Ignore
    , QDialogButtonBox::Close
    , QDialogButtonBox::Cancel
    , QDialogButtonBox::Discard
    , QDialogButtonBox::Help
    , QDialogButtonBox::Apply
    , QDialogButtonBox::Reset
    , QDialogButtonBox::RestoreDefaults
};

static const char * const qtscript_QDialogButtonBox_StandardButton_keys[] = {
    "NoButton"
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

static QString qtscript_QDialogButtonBox_StandardButton_toStringHelper(QDialogButtonBox::StandardButton value)
{
    for (int i = 0; i < 19; ++i) {
        if (qtscript_QDialogButtonBox_StandardButton_values[i] == value)
            return QString::fromLatin1(qtscript_QDialogButtonBox_StandardButton_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QDialogButtonBox_StandardButton_toScriptValue(QScriptEngine *engine, const QDialogButtonBox::StandardButton &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDialogButtonBox"));
    return clazz.property(qtscript_QDialogButtonBox_StandardButton_toStringHelper(value));
}

static void qtscript_QDialogButtonBox_StandardButton_fromScriptValue(const QScriptValue &value, QDialogButtonBox::StandardButton &out)
{
    out = qvariant_cast<QDialogButtonBox::StandardButton>(value.toVariant());
}

static QScriptValue qtscript_construct_QDialogButtonBox_StandardButton(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 19; ++i) {
        if (qtscript_QDialogButtonBox_StandardButton_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QDialogButtonBox::StandardButton>(arg));
    }
    return context->throwError(QString::fromLatin1("StandardButton(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDialogButtonBox_StandardButton_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDialogButtonBox::StandardButton value = qscriptvalue_cast<QDialogButtonBox::StandardButton>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDialogButtonBox_StandardButton_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDialogButtonBox::StandardButton value = qscriptvalue_cast<QDialogButtonBox::StandardButton>(context->thisObject());
    return QScriptValue(engine, qtscript_QDialogButtonBox_StandardButton_toStringHelper(value));
}

static QScriptValue qtscript_create_QDialogButtonBox_StandardButton_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDialogButtonBox_StandardButton,
        qtscript_QDialogButtonBox_StandardButton_valueOf, qtscript_QDialogButtonBox_StandardButton_toString);
    qScriptRegisterMetaType<QDialogButtonBox::StandardButton>(engine, qtscript_QDialogButtonBox_StandardButton_toScriptValue,
        qtscript_QDialogButtonBox_StandardButton_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 19; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDialogButtonBox_StandardButton_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDialogButtonBox_StandardButton_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDialogButtonBox::StandardButtons
//

static QScriptValue qtscript_QDialogButtonBox_StandardButtons_toScriptValue(QScriptEngine *engine, const QDialogButtonBox::StandardButtons &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QDialogButtonBox_StandardButtons_fromScriptValue(const QScriptValue &value, QDialogButtonBox::StandardButtons &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QDialogButtonBox::StandardButtons>())
        out = qvariant_cast<QDialogButtonBox::StandardButtons>(var);
    else if (var.userType() == qMetaTypeId<QDialogButtonBox::StandardButton>())
        out = qvariant_cast<QDialogButtonBox::StandardButton>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QDialogButtonBox_StandardButtons(QScriptContext *context, QScriptEngine *engine)
{
    QDialogButtonBox::StandardButtons result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QDialogButtonBox::StandardButtons>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QDialogButtonBox::StandardButton>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("StandardButtons(): argument %0 is not of type StandardButton").arg(i));
            }
            result |= qvariant_cast<QDialogButtonBox::StandardButton>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QDialogButtonBox_StandardButtons_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDialogButtonBox::StandardButtons value = qscriptvalue_cast<QDialogButtonBox::StandardButtons>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDialogButtonBox_StandardButtons_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDialogButtonBox::StandardButtons value = qscriptvalue_cast<QDialogButtonBox::StandardButtons>(context->thisObject());
    QString result;
    for (int i = 0; i < 19; ++i) {
        if ((value & qtscript_QDialogButtonBox_StandardButton_values[i]) == qtscript_QDialogButtonBox_StandardButton_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QDialogButtonBox_StandardButton_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QDialogButtonBox_StandardButtons_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QDialogButtonBox::StandardButtons>() == otherObj.value<QDialogButtonBox::StandardButtons>())));
}

static QScriptValue qtscript_create_QDialogButtonBox_StandardButtons_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QDialogButtonBox_StandardButtons, qtscript_QDialogButtonBox_StandardButtons_valueOf,
        qtscript_QDialogButtonBox_StandardButtons_toString, qtscript_QDialogButtonBox_StandardButtons_equals);
    qScriptRegisterMetaType<QDialogButtonBox::StandardButtons>(engine, qtscript_QDialogButtonBox_StandardButtons_toScriptValue,
        qtscript_QDialogButtonBox_StandardButtons_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QDialogButtonBox::ButtonLayout
//

static const QDialogButtonBox::ButtonLayout qtscript_QDialogButtonBox_ButtonLayout_values[] = {
    QDialogButtonBox::WinLayout
    , QDialogButtonBox::MacLayout
    , QDialogButtonBox::KdeLayout
    , QDialogButtonBox::GnomeLayout
};

static const char * const qtscript_QDialogButtonBox_ButtonLayout_keys[] = {
    "WinLayout"
    , "MacLayout"
    , "KdeLayout"
    , "GnomeLayout"
};

static QString qtscript_QDialogButtonBox_ButtonLayout_toStringHelper(QDialogButtonBox::ButtonLayout value)
{
    if ((value >= QDialogButtonBox::WinLayout) && (value <= QDialogButtonBox::GnomeLayout))
        return qtscript_QDialogButtonBox_ButtonLayout_keys[static_cast<int>(value)-static_cast<int>(QDialogButtonBox::WinLayout)];
    return QString();
}

static QScriptValue qtscript_QDialogButtonBox_ButtonLayout_toScriptValue(QScriptEngine *engine, const QDialogButtonBox::ButtonLayout &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDialogButtonBox"));
    return clazz.property(qtscript_QDialogButtonBox_ButtonLayout_toStringHelper(value));
}

static void qtscript_QDialogButtonBox_ButtonLayout_fromScriptValue(const QScriptValue &value, QDialogButtonBox::ButtonLayout &out)
{
    out = qvariant_cast<QDialogButtonBox::ButtonLayout>(value.toVariant());
}

static QScriptValue qtscript_construct_QDialogButtonBox_ButtonLayout(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QDialogButtonBox::WinLayout) && (arg <= QDialogButtonBox::GnomeLayout))
        return qScriptValueFromValue(engine,  static_cast<QDialogButtonBox::ButtonLayout>(arg));
    return context->throwError(QString::fromLatin1("ButtonLayout(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDialogButtonBox_ButtonLayout_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDialogButtonBox::ButtonLayout value = qscriptvalue_cast<QDialogButtonBox::ButtonLayout>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDialogButtonBox_ButtonLayout_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDialogButtonBox::ButtonLayout value = qscriptvalue_cast<QDialogButtonBox::ButtonLayout>(context->thisObject());
    return QScriptValue(engine, qtscript_QDialogButtonBox_ButtonLayout_toStringHelper(value));
}

static QScriptValue qtscript_create_QDialogButtonBox_ButtonLayout_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDialogButtonBox_ButtonLayout,
        qtscript_QDialogButtonBox_ButtonLayout_valueOf, qtscript_QDialogButtonBox_ButtonLayout_toString);
    qScriptRegisterMetaType<QDialogButtonBox::ButtonLayout>(engine, qtscript_QDialogButtonBox_ButtonLayout_toScriptValue,
        qtscript_QDialogButtonBox_ButtonLayout_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDialogButtonBox_ButtonLayout_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDialogButtonBox_ButtonLayout_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDialogButtonBox::ButtonRole
//

static const QDialogButtonBox::ButtonRole qtscript_QDialogButtonBox_ButtonRole_values[] = {
    QDialogButtonBox::InvalidRole
    , QDialogButtonBox::AcceptRole
    , QDialogButtonBox::RejectRole
    , QDialogButtonBox::DestructiveRole
    , QDialogButtonBox::ActionRole
    , QDialogButtonBox::HelpRole
    , QDialogButtonBox::YesRole
    , QDialogButtonBox::NoRole
    , QDialogButtonBox::ResetRole
    , QDialogButtonBox::ApplyRole
    , QDialogButtonBox::NRoles
};

static const char * const qtscript_QDialogButtonBox_ButtonRole_keys[] = {
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

static QString qtscript_QDialogButtonBox_ButtonRole_toStringHelper(QDialogButtonBox::ButtonRole value)
{
    if ((value >= QDialogButtonBox::InvalidRole) && (value <= QDialogButtonBox::NRoles))
        return qtscript_QDialogButtonBox_ButtonRole_keys[static_cast<int>(value)-static_cast<int>(QDialogButtonBox::InvalidRole)];
    return QString();
}

static QScriptValue qtscript_QDialogButtonBox_ButtonRole_toScriptValue(QScriptEngine *engine, const QDialogButtonBox::ButtonRole &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDialogButtonBox"));
    return clazz.property(qtscript_QDialogButtonBox_ButtonRole_toStringHelper(value));
}

static void qtscript_QDialogButtonBox_ButtonRole_fromScriptValue(const QScriptValue &value, QDialogButtonBox::ButtonRole &out)
{
    out = qvariant_cast<QDialogButtonBox::ButtonRole>(value.toVariant());
}

static QScriptValue qtscript_construct_QDialogButtonBox_ButtonRole(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QDialogButtonBox::InvalidRole) && (arg <= QDialogButtonBox::NRoles))
        return qScriptValueFromValue(engine,  static_cast<QDialogButtonBox::ButtonRole>(arg));
    return context->throwError(QString::fromLatin1("ButtonRole(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDialogButtonBox_ButtonRole_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDialogButtonBox::ButtonRole value = qscriptvalue_cast<QDialogButtonBox::ButtonRole>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDialogButtonBox_ButtonRole_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDialogButtonBox::ButtonRole value = qscriptvalue_cast<QDialogButtonBox::ButtonRole>(context->thisObject());
    return QScriptValue(engine, qtscript_QDialogButtonBox_ButtonRole_toStringHelper(value));
}

static QScriptValue qtscript_create_QDialogButtonBox_ButtonRole_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDialogButtonBox_ButtonRole,
        qtscript_QDialogButtonBox_ButtonRole_valueOf, qtscript_QDialogButtonBox_ButtonRole_toString);
    qScriptRegisterMetaType<QDialogButtonBox::ButtonRole>(engine, qtscript_QDialogButtonBox_ButtonRole_toScriptValue,
        qtscript_QDialogButtonBox_ButtonRole_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDialogButtonBox_ButtonRole_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDialogButtonBox_ButtonRole_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDialogButtonBox
//

static QScriptValue qtscript_QDialogButtonBox_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 7;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDialogButtonBox* _q_self = qscriptvalue_cast<QDialogButtonBox*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDialogButtonBox.%0(): this object is not a QDialogButtonBox")
            .arg(qtscript_QDialogButtonBox_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QDialogButtonBox::StandardButton _q_arg0 = qscriptvalue_cast<QDialogButtonBox::StandardButton>(context->argument(0));
        QPushButton* _q_result = _q_self->addButton(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QAbstractButton*>(context->argument(0))
            && (qMetaTypeId<QDialogButtonBox::ButtonRole>() == context->argument(1).toVariant().userType())) {
            QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
            QDialogButtonBox::ButtonRole _q_arg1 = qscriptvalue_cast<QDialogButtonBox::ButtonRole>(context->argument(1));
            _q_self->addButton(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QDialogButtonBox::ButtonRole>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QDialogButtonBox::ButtonRole _q_arg1 = qscriptvalue_cast<QDialogButtonBox::ButtonRole>(context->argument(1));
            QPushButton* _q_result = _q_self->addButton(_q_arg0, _q_arg1);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QDialogButtonBox::StandardButton _q_arg0 = qscriptvalue_cast<QDialogButtonBox::StandardButton>(context->argument(0));
        QPushButton* _q_result = _q_self->button(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
        QDialogButtonBox::ButtonRole _q_result = _q_self->buttonRole(_q_arg0);
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
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
        _q_self->removeButton(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QAbstractButton* _q_arg0 = qscriptvalue_cast<QAbstractButton*>(context->argument(0));
        QDialogButtonBox::StandardButton _q_result = _q_self->standardButton(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7: {
    QString result = QString::fromLatin1("QDialogButtonBox");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDialogButtonBox_throw_ambiguity_error_helper(context,
        qtscript_QDialogButtonBox_function_names[_id+1],
        qtscript_QDialogButtonBox_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDialogButtonBox_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDialogButtonBox(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QDialogButtonBox* _q_cpp_result = new QtScriptShell_QDialogButtonBox();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDialogButtonBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QFlags<QDialogButtonBox::StandardButton> >() == context->argument(0).toVariant().userType())) {
            QFlags<QDialogButtonBox::StandardButton> _q_arg0 = qscriptvalue_cast<QFlags<QDialogButtonBox::StandardButton> >(context->argument(0));
            QtScriptShell_QDialogButtonBox* _q_cpp_result = new QtScriptShell_QDialogButtonBox(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDialogButtonBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QDialogButtonBox* _q_cpp_result = new QtScriptShell_QDialogButtonBox(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDialogButtonBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<Qt::Orientation>() == context->argument(0).toVariant().userType())) {
            Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
            QtScriptShell_QDialogButtonBox* _q_cpp_result = new QtScriptShell_QDialogButtonBox(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDialogButtonBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QFlags<QDialogButtonBox::StandardButton> >() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QFlags<QDialogButtonBox::StandardButton> _q_arg0 = qscriptvalue_cast<QFlags<QDialogButtonBox::StandardButton> >(context->argument(0));
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QtScriptShell_QDialogButtonBox* _q_cpp_result = new QtScriptShell_QDialogButtonBox(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDialogButtonBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QFlags<QDialogButtonBox::StandardButton> >() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::Orientation>() == context->argument(1).toVariant().userType())) {
            QFlags<QDialogButtonBox::StandardButton> _q_arg0 = qscriptvalue_cast<QFlags<QDialogButtonBox::StandardButton> >(context->argument(0));
            Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
            QtScriptShell_QDialogButtonBox* _q_cpp_result = new QtScriptShell_QDialogButtonBox(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDialogButtonBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<Qt::Orientation>() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QtScriptShell_QDialogButtonBox* _q_cpp_result = new QtScriptShell_QDialogButtonBox(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDialogButtonBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QFlags<QDialogButtonBox::StandardButton> _q_arg0 = qscriptvalue_cast<QFlags<QDialogButtonBox::StandardButton> >(context->argument(0));
        Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        QtScriptShell_QDialogButtonBox* _q_cpp_result = new QtScriptShell_QDialogButtonBox(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDialogButtonBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDialogButtonBox_throw_ambiguity_error_helper(context,
        qtscript_QDialogButtonBox_function_names[_id],
        qtscript_QDialogButtonBox_function_signatures[_id]);
}

static QScriptValue qtscript_QDialogButtonBox_toScriptValue(QScriptEngine *engine, QDialogButtonBox* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QDialogButtonBox_fromScriptValue(const QScriptValue &value, QDialogButtonBox* &out)
{
    out = qobject_cast<QDialogButtonBox*>(value.toQObject());
}

QScriptValue qtscript_create_QDialogButtonBox_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDialogButtonBox*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDialogButtonBox*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDialogButtonBox_prototype_call, qtscript_QDialogButtonBox_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDialogButtonBox_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QDialogButtonBox*>(engine, qtscript_QDialogButtonBox_toScriptValue, 
        qtscript_QDialogButtonBox_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDialogButtonBox_static_call, proto, qtscript_QDialogButtonBox_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StandardButton"),
        qtscript_create_QDialogButtonBox_StandardButton_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StandardButtons"),
        qtscript_create_QDialogButtonBox_StandardButtons_class(engine));
    ctor.setProperty(QString::fromLatin1("ButtonLayout"),
        qtscript_create_QDialogButtonBox_ButtonLayout_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ButtonRole"),
        qtscript_create_QDialogButtonBox_ButtonRole_class(engine, ctor));
    return ctor;
}
