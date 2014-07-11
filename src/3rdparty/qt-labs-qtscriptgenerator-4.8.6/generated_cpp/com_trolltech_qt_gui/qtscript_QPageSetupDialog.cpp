#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpagesetupdialog.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdialog.h>
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
#include <qprinter.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QPageSetupDialog.h"

static const char * const qtscript_QPageSetupDialog_function_names[] = {
    "QPageSetupDialog"
    // static
    // prototype
    , "addEnabledOption"
    , "enabledOptions"
    , "isOptionEnabled"
    , "open"
    , "setEnabledOptions"
    , "setOption"
    , "testOption"
    , "toString"
};

static const char * const qtscript_QPageSetupDialog_function_signatures[] = {
    "QPrinter printer, QWidget parent\nQWidget parent"
    // static
    // prototype
    , "PageSetupDialogOption option"
    , ""
    , "PageSetupDialogOption option"
    , "QObject receiver, char member"
    , "PageSetupDialogOptions options"
    , "PageSetupDialogOption option, bool on"
    , "PageSetupDialogOption option"
""
};

static const int qtscript_QPageSetupDialog_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 0
    , 1
    , 2
    , 1
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QPageSetupDialog_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPageSetupDialog::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QPageSetupDialog_metaObject()
{
    return &QPageSetupDialog::staticMetaObject;
}

Q_DECLARE_METATYPE(QPageSetupDialog*)
Q_DECLARE_METATYPE(QtScriptShell_QPageSetupDialog*)
Q_DECLARE_METATYPE(QPageSetupDialog::PageSetupDialogOption)
Q_DECLARE_METATYPE(QFlags<QPageSetupDialog::PageSetupDialogOption>)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QPrinter*)
Q_DECLARE_METATYPE(QAbstractPageSetupDialog*)

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
// QPageSetupDialog::PageSetupDialogOption
//

static const QPageSetupDialog::PageSetupDialogOption qtscript_QPageSetupDialog_PageSetupDialogOption_values[] = {
    QPageSetupDialog::OwnsPrinter
    , QPageSetupDialog::None
    , QPageSetupDialog::DontUseSheet
};

static const char * const qtscript_QPageSetupDialog_PageSetupDialogOption_keys[] = {
    "OwnsPrinter"
    , "None"
    , "DontUseSheet"
};

static QString qtscript_QPageSetupDialog_PageSetupDialogOption_toStringHelper(QPageSetupDialog::PageSetupDialogOption value)
{
    const QMetaObject *meta = qtscript_QPageSetupDialog_metaObject();
    int idx = meta->indexOfEnumerator("PageSetupDialogOption");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QPageSetupDialog_PageSetupDialogOption_toScriptValue(QScriptEngine *engine, const QPageSetupDialog::PageSetupDialogOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPageSetupDialog"));
    return clazz.property(qtscript_QPageSetupDialog_PageSetupDialogOption_toStringHelper(value));
}

static void qtscript_QPageSetupDialog_PageSetupDialogOption_fromScriptValue(const QScriptValue &value, QPageSetupDialog::PageSetupDialogOption &out)
{
    out = qvariant_cast<QPageSetupDialog::PageSetupDialogOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QPageSetupDialog_PageSetupDialogOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QPageSetupDialog_metaObject();
    int idx = meta->indexOfEnumerator("PageSetupDialogOption");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QPageSetupDialog::PageSetupDialogOption>(arg));
    return context->throwError(QString::fromLatin1("PageSetupDialogOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPageSetupDialog_PageSetupDialogOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPageSetupDialog::PageSetupDialogOption value = qscriptvalue_cast<QPageSetupDialog::PageSetupDialogOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPageSetupDialog_PageSetupDialogOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPageSetupDialog::PageSetupDialogOption value = qscriptvalue_cast<QPageSetupDialog::PageSetupDialogOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QPageSetupDialog_PageSetupDialogOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QPageSetupDialog_PageSetupDialogOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPageSetupDialog_PageSetupDialogOption,
        qtscript_QPageSetupDialog_PageSetupDialogOption_valueOf, qtscript_QPageSetupDialog_PageSetupDialogOption_toString);
    qScriptRegisterMetaType<QPageSetupDialog::PageSetupDialogOption>(engine, qtscript_QPageSetupDialog_PageSetupDialogOption_toScriptValue,
        qtscript_QPageSetupDialog_PageSetupDialogOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPageSetupDialog_PageSetupDialogOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPageSetupDialog_PageSetupDialogOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPageSetupDialog::PageSetupDialogOptions
//

static QScriptValue qtscript_QPageSetupDialog_PageSetupDialogOptions_toScriptValue(QScriptEngine *engine, const QPageSetupDialog::PageSetupDialogOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QPageSetupDialog_PageSetupDialogOptions_fromScriptValue(const QScriptValue &value, QPageSetupDialog::PageSetupDialogOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QPageSetupDialog::PageSetupDialogOptions>())
        out = qvariant_cast<QPageSetupDialog::PageSetupDialogOptions>(var);
    else if (var.userType() == qMetaTypeId<QPageSetupDialog::PageSetupDialogOption>())
        out = qvariant_cast<QPageSetupDialog::PageSetupDialogOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QPageSetupDialog_PageSetupDialogOptions(QScriptContext *context, QScriptEngine *engine)
{
    QPageSetupDialog::PageSetupDialogOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QPageSetupDialog::PageSetupDialogOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QPageSetupDialog::PageSetupDialogOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("PageSetupDialogOptions(): argument %0 is not of type PageSetupDialogOption").arg(i));
            }
            result |= qvariant_cast<QPageSetupDialog::PageSetupDialogOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QPageSetupDialog_PageSetupDialogOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPageSetupDialog::PageSetupDialogOptions value = qscriptvalue_cast<QPageSetupDialog::PageSetupDialogOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPageSetupDialog_PageSetupDialogOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPageSetupDialog::PageSetupDialogOptions value = qscriptvalue_cast<QPageSetupDialog::PageSetupDialogOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QPageSetupDialog_PageSetupDialogOption_values[i]) == qtscript_QPageSetupDialog_PageSetupDialogOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QPageSetupDialog_PageSetupDialogOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QPageSetupDialog_PageSetupDialogOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QPageSetupDialog::PageSetupDialogOptions>() == otherObj.value<QPageSetupDialog::PageSetupDialogOptions>())));
}

static QScriptValue qtscript_create_QPageSetupDialog_PageSetupDialogOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QPageSetupDialog_PageSetupDialogOptions, qtscript_QPageSetupDialog_PageSetupDialogOptions_valueOf,
        qtscript_QPageSetupDialog_PageSetupDialogOptions_toString, qtscript_QPageSetupDialog_PageSetupDialogOptions_equals);
    qScriptRegisterMetaType<QPageSetupDialog::PageSetupDialogOptions>(engine, qtscript_QPageSetupDialog_PageSetupDialogOptions_toScriptValue,
        qtscript_QPageSetupDialog_PageSetupDialogOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QPageSetupDialog
//

static QScriptValue qtscript_QPageSetupDialog_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QPageSetupDialog* _q_self = qscriptvalue_cast<QPageSetupDialog*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPageSetupDialog.%0(): this object is not a QPageSetupDialog")
            .arg(qtscript_QPageSetupDialog_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QPageSetupDialog::PageSetupDialogOption _q_arg0 = qscriptvalue_cast<QPageSetupDialog::PageSetupDialogOption>(context->argument(0));
        _q_self->addEnabledOption(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QFlags<QPageSetupDialog::PageSetupDialogOption> _q_result = _q_self->enabledOptions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QPageSetupDialog::PageSetupDialogOption _q_arg0 = qscriptvalue_cast<QPageSetupDialog::PageSetupDialogOption>(context->argument(0));
        bool _q_result = _q_self->isOptionEnabled(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        char* _q_arg1 = qscriptvalue_cast<char*>(context->argument(1));
        _q_self->open(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QFlags<QPageSetupDialog::PageSetupDialogOption> _q_arg0 = qscriptvalue_cast<QFlags<QPageSetupDialog::PageSetupDialogOption> >(context->argument(0));
        _q_self->setEnabledOptions(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QPageSetupDialog::PageSetupDialogOption _q_arg0 = qscriptvalue_cast<QPageSetupDialog::PageSetupDialogOption>(context->argument(0));
        _q_self->setOption(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QPageSetupDialog::PageSetupDialogOption _q_arg0 = qscriptvalue_cast<QPageSetupDialog::PageSetupDialogOption>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QPageSetupDialog::PageSetupDialogOption _q_arg0 = qscriptvalue_cast<QPageSetupDialog::PageSetupDialogOption>(context->argument(0));
        bool _q_result = _q_self->testOption(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7: {
    QString result = QString::fromLatin1("QPageSetupDialog");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPageSetupDialog_throw_ambiguity_error_helper(context,
        qtscript_QPageSetupDialog_function_names[_id+1],
        qtscript_QPageSetupDialog_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPageSetupDialog_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPageSetupDialog(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPageSetupDialog* _q_cpp_result = new QtScriptShell_QPageSetupDialog();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPageSetupDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QPrinter*>(context->argument(0))) {
            QPrinter* _q_arg0 = qscriptvalue_cast<QPrinter*>(context->argument(0));
            QtScriptShell_QPageSetupDialog* _q_cpp_result = new QtScriptShell_QPageSetupDialog(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPageSetupDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QPageSetupDialog* _q_cpp_result = new QtScriptShell_QPageSetupDialog(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPageSetupDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QPrinter* _q_arg0 = qscriptvalue_cast<QPrinter*>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QPageSetupDialog* _q_cpp_result = new QtScriptShell_QPageSetupDialog(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPageSetupDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPageSetupDialog_throw_ambiguity_error_helper(context,
        qtscript_QPageSetupDialog_function_names[_id],
        qtscript_QPageSetupDialog_function_signatures[_id]);
}

static QScriptValue qtscript_QPageSetupDialog_toScriptValue(QScriptEngine *engine, QPageSetupDialog* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QPageSetupDialog_fromScriptValue(const QScriptValue &value, QPageSetupDialog* &out)
{
    out = qobject_cast<QPageSetupDialog*>(value.toQObject());
}

QScriptValue qtscript_create_QPageSetupDialog_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPageSetupDialog*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPageSetupDialog*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractPageSetupDialog*>()));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPageSetupDialog_prototype_call, qtscript_QPageSetupDialog_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPageSetupDialog_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QPageSetupDialog*>(engine, qtscript_QPageSetupDialog_toScriptValue, 
        qtscript_QPageSetupDialog_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPageSetupDialog_static_call, proto, qtscript_QPageSetupDialog_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("PageSetupDialogOption"),
        qtscript_create_QPageSetupDialog_PageSetupDialogOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PageSetupDialogOptions"),
        qtscript_create_QPageSetupDialog_PageSetupDialogOptions_class(engine));
    return ctor;
}
