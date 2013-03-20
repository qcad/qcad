#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qinputdialog.h>
#include <QVariant>
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
#include <qinputdialog.h>
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
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstringlist.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QInputDialog.h"

static const char * const qtscript_QInputDialog_function_names[] = {
    "QInputDialog"
    // static
    , "getDouble"
    , "getInt_private"
    , "getInteger"
    , "getItem"
    , "getText"
    // prototype
    , "cancelButtonText"
    , "comboBoxItems"
    , "doubleDecimals"
    , "doubleMaximum"
    , "doubleMinimum"
    , "doubleValue"
    , "inputMode"
    , "intMaximum"
    , "intMinimum"
    , "intStep"
    , "intValue"
    , "isComboBoxEditable"
    , "labelText"
    , "okButtonText"
    , "open"
    , "options"
    , "setCancelButtonText"
    , "setComboBoxEditable"
    , "setComboBoxItems"
    , "setDoubleDecimals"
    , "setDoubleMaximum"
    , "setDoubleMinimum"
    , "setDoubleRange"
    , "setDoubleValue"
    , "setInputMode"
    , "setIntMaximum"
    , "setIntMinimum"
    , "setIntRange"
    , "setIntStep"
    , "setIntValue"
    , "setLabelText"
    , "setOkButtonText"
    , "setOption"
    , "setOptions"
    , "setTextEchoMode"
    , "setTextValue"
    , "testOption"
    , "textEchoMode"
    , "textValue"
    , "toString"
};

static const char * const qtscript_QInputDialog_function_signatures[] = {
    "QWidget parent, WindowFlags flags"
    // static
    , "QWidget parent, String title, String label, double value, double minValue, double maxValue, int decimals, WindowFlags flags"
    , "QWidget parent, String title, String label, int value, int minValue, int maxValue, int step, bool ok, WindowFlags flags"
    , "QWidget parent, String title, String label, int value, int minValue, int maxValue, int step, WindowFlags flags"
    , "QWidget parent, String title, String label, List items, int current, bool editable, WindowFlags flags"
    , "QWidget parent, String title, String label, EchoMode echo, String text, WindowFlags flags"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QObject receiver, char member"
    , ""
    , "String text"
    , "bool editable"
    , "List items"
    , "int decimals"
    , "double max"
    , "double min"
    , "double min, double max"
    , "double value"
    , "InputMode mode"
    , "int max"
    , "int min"
    , "int min, int max"
    , "int step"
    , "int value"
    , "String text"
    , "String text"
    , "InputDialogOption option, bool on"
    , "InputDialogOptions options"
    , "EchoMode mode"
    , "String text"
    , "InputDialogOption option"
    , ""
    , ""
""
};

static const int qtscript_QInputDialog_function_lengths[] = {
    2
    // static
    , 9
    , 9
    , 9
    , 8
    , 7
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QInputDialog_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QInputDialog::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QInputDialog*)
Q_DECLARE_METATYPE(QtScriptShell_QInputDialog*)
Q_DECLARE_METATYPE(QInputDialog::InputMode)
Q_DECLARE_METATYPE(QInputDialog::InputDialogOption)
Q_DECLARE_METATYPE(QFlags<QInputDialog::InputDialogOption>)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QLineEdit::EchoMode)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)
Q_DECLARE_METATYPE(bool*)
Q_DECLARE_METATYPE(QDialog*)


    Q_DECLARE_METATYPE(QScriptValue)
    
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
// QInputDialog::InputMode
//

static const QInputDialog::InputMode qtscript_QInputDialog_InputMode_values[] = {
    QInputDialog::TextInput
    , QInputDialog::IntInput
    , QInputDialog::DoubleInput
};

static const char * const qtscript_QInputDialog_InputMode_keys[] = {
    "TextInput"
    , "IntInput"
    , "DoubleInput"
};

static QString qtscript_QInputDialog_InputMode_toStringHelper(QInputDialog::InputMode value)
{
    if ((value >= QInputDialog::TextInput) && (value <= QInputDialog::DoubleInput))
        return qtscript_QInputDialog_InputMode_keys[static_cast<int>(value)-static_cast<int>(QInputDialog::TextInput)];
    return QString();
}

static QScriptValue qtscript_QInputDialog_InputMode_toScriptValue(QScriptEngine *engine, const QInputDialog::InputMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QInputDialog"));
    return clazz.property(qtscript_QInputDialog_InputMode_toStringHelper(value));
}

static void qtscript_QInputDialog_InputMode_fromScriptValue(const QScriptValue &value, QInputDialog::InputMode &out)
{
    out = qvariant_cast<QInputDialog::InputMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QInputDialog_InputMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QInputDialog::TextInput) && (arg <= QInputDialog::DoubleInput))
        return qScriptValueFromValue(engine,  static_cast<QInputDialog::InputMode>(arg));
    return context->throwError(QString::fromLatin1("InputMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QInputDialog_InputMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QInputDialog::InputMode value = qscriptvalue_cast<QInputDialog::InputMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QInputDialog_InputMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QInputDialog::InputMode value = qscriptvalue_cast<QInputDialog::InputMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QInputDialog_InputMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QInputDialog_InputMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QInputDialog_InputMode,
        qtscript_QInputDialog_InputMode_valueOf, qtscript_QInputDialog_InputMode_toString);
    qScriptRegisterMetaType<QInputDialog::InputMode>(engine, qtscript_QInputDialog_InputMode_toScriptValue,
        qtscript_QInputDialog_InputMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QInputDialog_InputMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QInputDialog_InputMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QInputDialog::InputDialogOption
//

static const QInputDialog::InputDialogOption qtscript_QInputDialog_InputDialogOption_values[] = {
    QInputDialog::NoButtons
    , QInputDialog::UseListViewForComboBoxItems
};

static const char * const qtscript_QInputDialog_InputDialogOption_keys[] = {
    "NoButtons"
    , "UseListViewForComboBoxItems"
};

static QString qtscript_QInputDialog_InputDialogOption_toStringHelper(QInputDialog::InputDialogOption value)
{
    if ((value >= QInputDialog::NoButtons) && (value <= QInputDialog::UseListViewForComboBoxItems))
        return qtscript_QInputDialog_InputDialogOption_keys[static_cast<int>(value)-static_cast<int>(QInputDialog::NoButtons)];
    return QString();
}

static QScriptValue qtscript_QInputDialog_InputDialogOption_toScriptValue(QScriptEngine *engine, const QInputDialog::InputDialogOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QInputDialog"));
    return clazz.property(qtscript_QInputDialog_InputDialogOption_toStringHelper(value));
}

static void qtscript_QInputDialog_InputDialogOption_fromScriptValue(const QScriptValue &value, QInputDialog::InputDialogOption &out)
{
    out = qvariant_cast<QInputDialog::InputDialogOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QInputDialog_InputDialogOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QInputDialog::NoButtons) && (arg <= QInputDialog::UseListViewForComboBoxItems))
        return qScriptValueFromValue(engine,  static_cast<QInputDialog::InputDialogOption>(arg));
    return context->throwError(QString::fromLatin1("InputDialogOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QInputDialog_InputDialogOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QInputDialog::InputDialogOption value = qscriptvalue_cast<QInputDialog::InputDialogOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QInputDialog_InputDialogOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QInputDialog::InputDialogOption value = qscriptvalue_cast<QInputDialog::InputDialogOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QInputDialog_InputDialogOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QInputDialog_InputDialogOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QInputDialog_InputDialogOption,
        qtscript_QInputDialog_InputDialogOption_valueOf, qtscript_QInputDialog_InputDialogOption_toString);
    qScriptRegisterMetaType<QInputDialog::InputDialogOption>(engine, qtscript_QInputDialog_InputDialogOption_toScriptValue,
        qtscript_QInputDialog_InputDialogOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QInputDialog_InputDialogOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QInputDialog_InputDialogOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QInputDialog::InputDialogOptions
//

static QScriptValue qtscript_QInputDialog_InputDialogOptions_toScriptValue(QScriptEngine *engine, const QInputDialog::InputDialogOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QInputDialog_InputDialogOptions_fromScriptValue(const QScriptValue &value, QInputDialog::InputDialogOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QInputDialog::InputDialogOptions>())
        out = qvariant_cast<QInputDialog::InputDialogOptions>(var);
    else if (var.userType() == qMetaTypeId<QInputDialog::InputDialogOption>())
        out = qvariant_cast<QInputDialog::InputDialogOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QInputDialog_InputDialogOptions(QScriptContext *context, QScriptEngine *engine)
{
    QInputDialog::InputDialogOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QInputDialog::InputDialogOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QInputDialog::InputDialogOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("InputDialogOptions(): argument %0 is not of type InputDialogOption").arg(i));
            }
            result |= qvariant_cast<QInputDialog::InputDialogOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QInputDialog_InputDialogOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QInputDialog::InputDialogOptions value = qscriptvalue_cast<QInputDialog::InputDialogOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QInputDialog_InputDialogOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QInputDialog::InputDialogOptions value = qscriptvalue_cast<QInputDialog::InputDialogOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 2; ++i) {
        if ((value & qtscript_QInputDialog_InputDialogOption_values[i]) == qtscript_QInputDialog_InputDialogOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QInputDialog_InputDialogOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QInputDialog_InputDialogOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QInputDialog::InputDialogOptions>() == otherObj.value<QInputDialog::InputDialogOptions>())));
}

static QScriptValue qtscript_create_QInputDialog_InputDialogOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QInputDialog_InputDialogOptions, qtscript_QInputDialog_InputDialogOptions_valueOf,
        qtscript_QInputDialog_InputDialogOptions_toString, qtscript_QInputDialog_InputDialogOptions_equals);
    qScriptRegisterMetaType<QInputDialog::InputDialogOptions>(engine, qtscript_QInputDialog_InputDialogOptions_toScriptValue,
        qtscript_QInputDialog_InputDialogOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QInputDialog
//

static QScriptValue qtscript_QInputDialog_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 39;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QInputDialog* _q_self = qscriptvalue_cast<QInputDialog*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QInputDialog.%0(): this object is not a QInputDialog")
            .arg(qtscript_QInputDialog_function_names[_id+6]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->cancelButtonText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->comboBoxItems();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->doubleDecimals();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        double _q_result = _q_self->doubleMaximum();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        double _q_result = _q_self->doubleMinimum();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        double _q_result = _q_self->doubleValue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QInputDialog::InputMode _q_result = _q_self->inputMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->intMaximum();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->intMinimum();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->intStep();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->intValue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isComboBoxEditable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->labelText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->okButtonText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        char* _q_arg1 = qscriptvalue_cast<char*>(context->argument(1));
        _q_self->open(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QFlags<QInputDialog::InputDialogOption> _q_result = _q_self->options();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setCancelButtonText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setComboBoxEditable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setComboBoxItems(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setDoubleDecimals(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        double _q_arg0 = context->argument(0).toNumber();
        _q_self->setDoubleMaximum(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        double _q_arg0 = context->argument(0).toNumber();
        _q_self->setDoubleMinimum(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 2) {
        double _q_arg0 = context->argument(0).toNumber();
        double _q_arg1 = context->argument(1).toNumber();
        _q_self->setDoubleRange(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        double _q_arg0 = context->argument(0).toNumber();
        _q_self->setDoubleValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QInputDialog::InputMode _q_arg0 = qscriptvalue_cast<QInputDialog::InputMode>(context->argument(0));
        _q_self->setInputMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setIntMaximum(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setIntMinimum(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setIntRange(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setIntStep(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setIntValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setLabelText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setOkButtonText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        QInputDialog::InputDialogOption _q_arg0 = qscriptvalue_cast<QInputDialog::InputDialogOption>(context->argument(0));
        _q_self->setOption(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QInputDialog::InputDialogOption _q_arg0 = qscriptvalue_cast<QInputDialog::InputDialogOption>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QFlags<QInputDialog::InputDialogOption> _q_arg0 = qscriptvalue_cast<QFlags<QInputDialog::InputDialogOption> >(context->argument(0));
        _q_self->setOptions(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        QLineEdit::EchoMode _q_arg0 = qscriptvalue_cast<QLineEdit::EchoMode>(context->argument(0));
        _q_self->setTextEchoMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setTextValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        QInputDialog::InputDialogOption _q_arg0 = qscriptvalue_cast<QInputDialog::InputDialogOption>(context->argument(0));
        bool _q_result = _q_self->testOption(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 0) {
        QLineEdit::EchoMode _q_result = _q_self->textEchoMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 38:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->textValue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 39: {
    QString result = QString::fromLatin1("QInputDialog");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QInputDialog_throw_ambiguity_error_helper(context,
        qtscript_QInputDialog_function_names[_id+6],
        qtscript_QInputDialog_function_signatures[_id+6]);
}

static QScriptValue qtscript_QInputDialog_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QInputDialog(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QInputDialog* _q_cpp_result = new QtScriptShell_QInputDialog();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QInputDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QInputDialog* _q_cpp_result = new QtScriptShell_QInputDialog(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QInputDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QtScriptShell_QInputDialog* _q_cpp_result = new QtScriptShell_QInputDialog(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QInputDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 8) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        double _q_arg3 = context->argument(3).toNumber();
        double _q_arg4 = context->argument(4).toNumber();
        double _q_arg5 = context->argument(5).toNumber();
        int _q_arg6 = context->argument(6).toInt32();

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg7 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  QFlags<Qt::WindowType> _q_arg8 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(7));
        double _q_result = QInputDialog::getDouble(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8);
        
          // TEMPLATE - core.convert_to_null_or_primitive - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = QScriptValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_primitive - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 2:
    if (context->argumentCount() == 9) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        int _q_arg6 = context->argument(6).toInt32();
        bool* _q_arg7 = qscriptvalue_cast<bool*>(context->argument(7));
        QFlags<Qt::WindowType> _q_arg8 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(8));
        int _q_result = QInputDialog::getInt(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 8) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        int _q_arg6 = context->argument(6).toInt32();

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg7 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  QFlags<Qt::WindowType> _q_arg8 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(7));
        int _q_result = QInputDialog::getInteger(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8);
        
          // TEMPLATE - core.convert_to_null_or_primitive - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = QScriptValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_primitive - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 4:
    if (context->argumentCount() == 7) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QStringList _q_arg3;
        qScriptValueToSequence(context->argument(3), _q_arg3);
        int _q_arg4 = context->argument(4).toInt32();
        bool _q_arg5 = context->argument(5).toBoolean();

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg6 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  QFlags<Qt::WindowType> _q_arg7 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(6));
        QString _q_result = QInputDialog::getItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7);
        
          // TEMPLATE - core.convert_to_null_or_primitive - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = QScriptValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_primitive - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    case 5:
    if (context->argumentCount() == 6) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QString _q_arg2 = context->argument(2).toString();
        QLineEdit::EchoMode _q_arg3 = qscriptvalue_cast<QLineEdit::EchoMode>(context->argument(3));
        QString _q_arg4 = context->argument(4).toString();

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg5 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  QFlags<Qt::WindowType> _q_arg6 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(5));
        QString _q_result = QInputDialog::getText(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        
          // TEMPLATE - core.convert_to_null_or_primitive - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = QScriptValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_primitive - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QInputDialog_throw_ambiguity_error_helper(context,
        qtscript_QInputDialog_function_names[_id],
        qtscript_QInputDialog_function_signatures[_id]);
}

static QScriptValue qtscript_QInputDialog_toScriptValue(QScriptEngine *engine, QInputDialog* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QInputDialog_fromScriptValue(const QScriptValue &value, QInputDialog* &out)
{
    out = qobject_cast<QInputDialog*>(value.toQObject());
}

QScriptValue qtscript_create_QInputDialog_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QInputDialog*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QInputDialog*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDialog*>()));
    for (int i = 0; i < 40; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QInputDialog_prototype_call, qtscript_QInputDialog_function_lengths[i+6]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QInputDialog_function_names[i+6]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QInputDialog*>(engine, qtscript_QInputDialog_toScriptValue, 
        qtscript_QInputDialog_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QInputDialog_static_call, proto, qtscript_QInputDialog_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QInputDialog_static_call,
            qtscript_QInputDialog_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QInputDialog_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("InputMode"),
        qtscript_create_QInputDialog_InputMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("InputDialogOption"),
        qtscript_create_QInputDialog_InputDialogOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("InputDialogOptions"),
        qtscript_create_QInputDialog_InputDialogOptions_class(engine));
    return ctor;
}
