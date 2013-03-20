#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qcolordialog.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcolordialog.h>
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
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QColorDialog.h"

static const char * const qtscript_QColorDialog_function_names[] = {
    "QColorDialog"
    // static
    , "customColor"
    , "customCount"
    , "getColor"
    , "setCustomColor"
    , "setStandardColor"
    // prototype
    , "open"
    , "selectedColor"
    , "setCurrentColor"
    , "setOption"
    , "testOption"
    , "toString"
};

static const char * const qtscript_QColorDialog_function_signatures[] = {
    "QWidget parent\nQColor initial, QWidget parent"
    // static
    , "int index"
    , ""
    , "QColor initial, QWidget parent\nQColor initial, QWidget parent, String title, ColorDialogOptions options"
    , "int index, unsigned int color"
    , "int index, unsigned int color"
    // prototype
    , "QObject receiver, char member"
    , ""
    , "QColor color"
    , "ColorDialogOption option, bool on"
    , "ColorDialogOption option"
""
};

static const int qtscript_QColorDialog_function_lengths[] = {
    2
    // static
    , 1
    , 0
    , 4
    , 2
    , 2
    // prototype
    , 2
    , 0
    , 1
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QColorDialog_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QColorDialog::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QColorDialog_metaObject()
{
    return &QColorDialog::staticMetaObject;
}

Q_DECLARE_METATYPE(QColorDialog*)
Q_DECLARE_METATYPE(QtScriptShell_QColorDialog*)
Q_DECLARE_METATYPE(QColorDialog::ColorDialogOption)
Q_DECLARE_METATYPE(QFlags<QColorDialog::ColorDialogOption>)
Q_DECLARE_METATYPE(char*)
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
// QColorDialog::ColorDialogOption
//

static const QColorDialog::ColorDialogOption qtscript_QColorDialog_ColorDialogOption_values[] = {
    QColorDialog::ShowAlphaChannel
    , QColorDialog::NoButtons
    , QColorDialog::DontUseNativeDialog
};

static const char * const qtscript_QColorDialog_ColorDialogOption_keys[] = {
    "ShowAlphaChannel"
    , "NoButtons"
    , "DontUseNativeDialog"
};

static QString qtscript_QColorDialog_ColorDialogOption_toStringHelper(QColorDialog::ColorDialogOption value)
{
    const QMetaObject *meta = qtscript_QColorDialog_metaObject();
    int idx = meta->indexOfEnumerator("ColorDialogOption");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QColorDialog_ColorDialogOption_toScriptValue(QScriptEngine *engine, const QColorDialog::ColorDialogOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QColorDialog"));
    return clazz.property(qtscript_QColorDialog_ColorDialogOption_toStringHelper(value));
}

static void qtscript_QColorDialog_ColorDialogOption_fromScriptValue(const QScriptValue &value, QColorDialog::ColorDialogOption &out)
{
    out = qvariant_cast<QColorDialog::ColorDialogOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QColorDialog_ColorDialogOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QColorDialog_metaObject();
    int idx = meta->indexOfEnumerator("ColorDialogOption");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QColorDialog::ColorDialogOption>(arg));
    return context->throwError(QString::fromLatin1("ColorDialogOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QColorDialog_ColorDialogOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QColorDialog::ColorDialogOption value = qscriptvalue_cast<QColorDialog::ColorDialogOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QColorDialog_ColorDialogOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QColorDialog::ColorDialogOption value = qscriptvalue_cast<QColorDialog::ColorDialogOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QColorDialog_ColorDialogOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QColorDialog_ColorDialogOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QColorDialog_ColorDialogOption,
        qtscript_QColorDialog_ColorDialogOption_valueOf, qtscript_QColorDialog_ColorDialogOption_toString);
    qScriptRegisterMetaType<QColorDialog::ColorDialogOption>(engine, qtscript_QColorDialog_ColorDialogOption_toScriptValue,
        qtscript_QColorDialog_ColorDialogOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QColorDialog_ColorDialogOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QColorDialog_ColorDialogOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QColorDialog::ColorDialogOptions
//

static QScriptValue qtscript_QColorDialog_ColorDialogOptions_toScriptValue(QScriptEngine *engine, const QColorDialog::ColorDialogOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QColorDialog_ColorDialogOptions_fromScriptValue(const QScriptValue &value, QColorDialog::ColorDialogOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QColorDialog::ColorDialogOptions>())
        out = qvariant_cast<QColorDialog::ColorDialogOptions>(var);
    else if (var.userType() == qMetaTypeId<QColorDialog::ColorDialogOption>())
        out = qvariant_cast<QColorDialog::ColorDialogOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QColorDialog_ColorDialogOptions(QScriptContext *context, QScriptEngine *engine)
{
    QColorDialog::ColorDialogOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QColorDialog::ColorDialogOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QColorDialog::ColorDialogOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ColorDialogOptions(): argument %0 is not of type ColorDialogOption").arg(i));
            }
            result |= qvariant_cast<QColorDialog::ColorDialogOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QColorDialog_ColorDialogOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QColorDialog::ColorDialogOptions value = qscriptvalue_cast<QColorDialog::ColorDialogOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QColorDialog_ColorDialogOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QColorDialog::ColorDialogOptions value = qscriptvalue_cast<QColorDialog::ColorDialogOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QColorDialog_ColorDialogOption_values[i]) == qtscript_QColorDialog_ColorDialogOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QColorDialog_ColorDialogOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QColorDialog_ColorDialogOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QColorDialog::ColorDialogOptions>() == otherObj.value<QColorDialog::ColorDialogOptions>())));
}

static QScriptValue qtscript_create_QColorDialog_ColorDialogOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QColorDialog_ColorDialogOptions, qtscript_QColorDialog_ColorDialogOptions_valueOf,
        qtscript_QColorDialog_ColorDialogOptions_toString, qtscript_QColorDialog_ColorDialogOptions_equals);
    qScriptRegisterMetaType<QColorDialog::ColorDialogOptions>(engine, qtscript_QColorDialog_ColorDialogOptions_toScriptValue,
        qtscript_QColorDialog_ColorDialogOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QColorDialog
//

static QScriptValue qtscript_QColorDialog_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QColorDialog* _q_self = qscriptvalue_cast<QColorDialog*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QColorDialog.%0(): this object is not a QColorDialog")
            .arg(qtscript_QColorDialog_function_names[_id+6]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        char* _q_arg1 = qscriptvalue_cast<char*>(context->argument(1));
        _q_self->open(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->selectedColor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        _q_self->setCurrentColor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QColorDialog::ColorDialogOption _q_arg0 = qscriptvalue_cast<QColorDialog::ColorDialogOption>(context->argument(0));
        _q_self->setOption(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QColorDialog::ColorDialogOption _q_arg0 = qscriptvalue_cast<QColorDialog::ColorDialogOption>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QColorDialog::ColorDialogOption _q_arg0 = qscriptvalue_cast<QColorDialog::ColorDialogOption>(context->argument(0));
        bool _q_result = _q_self->testOption(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QColorDialog");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QColorDialog_throw_ambiguity_error_helper(context,
        qtscript_QColorDialog_function_names[_id+6],
        qtscript_QColorDialog_function_signatures[_id+6]);
}

static QScriptValue qtscript_QColorDialog_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QColorDialog(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QColorDialog* _q_cpp_result = new QtScriptShell_QColorDialog();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QColorDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QColorDialog* _q_cpp_result = new QtScriptShell_QColorDialog(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QColorDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QColor>() == context->argument(0).toVariant().userType())) {
            QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
            QtScriptShell_QColorDialog* _q_cpp_result = new QtScriptShell_QColorDialog(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QColorDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QColorDialog* _q_cpp_result = new QtScriptShell_QColorDialog(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QColorDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        uint _q_result = QColorDialog::customColor(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = QColorDialog::customCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QColor _q_result = QColorDialog::getColor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        QColor _q_result = QColorDialog::getColor(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QColor _q_result = QColorDialog::getColor(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        QColor _q_result = QColorDialog::getColor(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        QFlags<QColorDialog::ColorDialogOption> _q_arg3 = qscriptvalue_cast<QFlags<QColorDialog::ColorDialogOption> >(context->argument(3));
        QColor _q_result = QColorDialog::getColor(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        uint _q_arg1 = context->argument(1).toUInt32();
        QColorDialog::setCustomColor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        uint _q_arg1 = context->argument(1).toUInt32();
        QColorDialog::setStandardColor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QColorDialog_throw_ambiguity_error_helper(context,
        qtscript_QColorDialog_function_names[_id],
        qtscript_QColorDialog_function_signatures[_id]);
}

static QScriptValue qtscript_QColorDialog_toScriptValue(QScriptEngine *engine, QColorDialog* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QColorDialog_fromScriptValue(const QScriptValue &value, QColorDialog* &out)
{
    out = qobject_cast<QColorDialog*>(value.toQObject());
}

QScriptValue qtscript_create_QColorDialog_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QColorDialog*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QColorDialog*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDialog*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QColorDialog_prototype_call, qtscript_QColorDialog_function_lengths[i+6]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QColorDialog_function_names[i+6]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QColorDialog*>(engine, qtscript_QColorDialog_toScriptValue, 
        qtscript_QColorDialog_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QColorDialog_static_call, proto, qtscript_QColorDialog_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QColorDialog_static_call,
            qtscript_QColorDialog_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QColorDialog_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("ColorDialogOption"),
        qtscript_create_QColorDialog_ColorDialogOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ColorDialogOptions"),
        qtscript_create_QColorDialog_ColorDialogOptions_class(engine));
    return ctor;
}
