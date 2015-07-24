#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qabstractprintdialog.h>
#include <QVariant>
#include <qabstractprintdialog.h>
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
#include <qprinter.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QAbstractPrintDialog.h"

static const char * const qtscript_QAbstractPrintDialog_function_names[] = {
    "QAbstractPrintDialog"
    // static
    // prototype
    , "addEnabledOption"
    , "enabledOptions"
    , "fromPage"
    , "isOptionEnabled"
    , "maxPage"
    , "minPage"
    , "printRange"
    , "printer"
    , "setEnabledOptions"
    , "setFromTo"
    , "setMinMax"
    , "setOptionTabs"
    , "setPrintRange"
    , "toPage"
    , "toString"
};

static const char * const qtscript_QAbstractPrintDialog_function_signatures[] = {
    "QPrinter printer, QWidget parent"
    // static
    // prototype
    , "PrintDialogOption option"
    , ""
    , ""
    , "PrintDialogOption option"
    , ""
    , ""
    , ""
    , ""
    , "PrintDialogOptions options"
    , "int fromPage, int toPage"
    , "int min, int max"
    , "List tabs"
    , "PrintRange range"
    , ""
""
};

static const int qtscript_QAbstractPrintDialog_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 2
    , 2
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QAbstractPrintDialog_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractPrintDialog::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractPrintDialog*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractPrintDialog*)
Q_DECLARE_METATYPE(QAbstractPrintDialog::PrintDialogOption)
Q_DECLARE_METATYPE(QFlags<QAbstractPrintDialog::PrintDialogOption>)
Q_DECLARE_METATYPE(QAbstractPrintDialog::PrintRange)
Q_DECLARE_METATYPE(QPrinter*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QList<QWidget* >)
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
// QAbstractPrintDialog::PrintDialogOption
//

static const QAbstractPrintDialog::PrintDialogOption qtscript_QAbstractPrintDialog_PrintDialogOption_values[] = {
    QAbstractPrintDialog::None
    , QAbstractPrintDialog::PrintToFile
    , QAbstractPrintDialog::PrintSelection
    , QAbstractPrintDialog::PrintPageRange
    , QAbstractPrintDialog::PrintShowPageSize
    , QAbstractPrintDialog::PrintCollateCopies
    , QAbstractPrintDialog::DontUseSheet
    , QAbstractPrintDialog::PrintCurrentPage
};

static const char * const qtscript_QAbstractPrintDialog_PrintDialogOption_keys[] = {
    "None"
    , "PrintToFile"
    , "PrintSelection"
    , "PrintPageRange"
    , "PrintShowPageSize"
    , "PrintCollateCopies"
    , "DontUseSheet"
    , "PrintCurrentPage"
};

static QString qtscript_QAbstractPrintDialog_PrintDialogOption_toStringHelper(QAbstractPrintDialog::PrintDialogOption value)
{
    for (int i = 0; i < 8; ++i) {
        if (qtscript_QAbstractPrintDialog_PrintDialogOption_values[i] == value)
            return QString::fromLatin1(qtscript_QAbstractPrintDialog_PrintDialogOption_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QAbstractPrintDialog_PrintDialogOption_toScriptValue(QScriptEngine *engine, const QAbstractPrintDialog::PrintDialogOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractPrintDialog"));
    return clazz.property(qtscript_QAbstractPrintDialog_PrintDialogOption_toStringHelper(value));
}

static void qtscript_QAbstractPrintDialog_PrintDialogOption_fromScriptValue(const QScriptValue &value, QAbstractPrintDialog::PrintDialogOption &out)
{
    out = qvariant_cast<QAbstractPrintDialog::PrintDialogOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractPrintDialog_PrintDialogOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 8; ++i) {
        if (qtscript_QAbstractPrintDialog_PrintDialogOption_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QAbstractPrintDialog::PrintDialogOption>(arg));
    }
    return context->throwError(QString::fromLatin1("PrintDialogOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractPrintDialog_PrintDialogOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractPrintDialog::PrintDialogOption value = qscriptvalue_cast<QAbstractPrintDialog::PrintDialogOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractPrintDialog_PrintDialogOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractPrintDialog::PrintDialogOption value = qscriptvalue_cast<QAbstractPrintDialog::PrintDialogOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractPrintDialog_PrintDialogOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractPrintDialog_PrintDialogOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractPrintDialog_PrintDialogOption,
        qtscript_QAbstractPrintDialog_PrintDialogOption_valueOf, qtscript_QAbstractPrintDialog_PrintDialogOption_toString);
    qScriptRegisterMetaType<QAbstractPrintDialog::PrintDialogOption>(engine, qtscript_QAbstractPrintDialog_PrintDialogOption_toScriptValue,
        qtscript_QAbstractPrintDialog_PrintDialogOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractPrintDialog_PrintDialogOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractPrintDialog_PrintDialogOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractPrintDialog::PrintDialogOptions
//

static QScriptValue qtscript_QAbstractPrintDialog_PrintDialogOptions_toScriptValue(QScriptEngine *engine, const QAbstractPrintDialog::PrintDialogOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QAbstractPrintDialog_PrintDialogOptions_fromScriptValue(const QScriptValue &value, QAbstractPrintDialog::PrintDialogOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QAbstractPrintDialog::PrintDialogOptions>())
        out = qvariant_cast<QAbstractPrintDialog::PrintDialogOptions>(var);
    else if (var.userType() == qMetaTypeId<QAbstractPrintDialog::PrintDialogOption>())
        out = qvariant_cast<QAbstractPrintDialog::PrintDialogOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QAbstractPrintDialog_PrintDialogOptions(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractPrintDialog::PrintDialogOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QAbstractPrintDialog::PrintDialogOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QAbstractPrintDialog::PrintDialogOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("PrintDialogOptions(): argument %0 is not of type PrintDialogOption").arg(i));
            }
            result |= qvariant_cast<QAbstractPrintDialog::PrintDialogOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QAbstractPrintDialog_PrintDialogOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractPrintDialog::PrintDialogOptions value = qscriptvalue_cast<QAbstractPrintDialog::PrintDialogOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractPrintDialog_PrintDialogOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractPrintDialog::PrintDialogOptions value = qscriptvalue_cast<QAbstractPrintDialog::PrintDialogOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 8; ++i) {
        if ((value & qtscript_QAbstractPrintDialog_PrintDialogOption_values[i]) == qtscript_QAbstractPrintDialog_PrintDialogOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QAbstractPrintDialog_PrintDialogOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QAbstractPrintDialog_PrintDialogOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QAbstractPrintDialog::PrintDialogOptions>() == otherObj.value<QAbstractPrintDialog::PrintDialogOptions>())));
}

static QScriptValue qtscript_create_QAbstractPrintDialog_PrintDialogOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QAbstractPrintDialog_PrintDialogOptions, qtscript_QAbstractPrintDialog_PrintDialogOptions_valueOf,
        qtscript_QAbstractPrintDialog_PrintDialogOptions_toString, qtscript_QAbstractPrintDialog_PrintDialogOptions_equals);
    qScriptRegisterMetaType<QAbstractPrintDialog::PrintDialogOptions>(engine, qtscript_QAbstractPrintDialog_PrintDialogOptions_toScriptValue,
        qtscript_QAbstractPrintDialog_PrintDialogOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QAbstractPrintDialog::PrintRange
//

static const QAbstractPrintDialog::PrintRange qtscript_QAbstractPrintDialog_PrintRange_values[] = {
    QAbstractPrintDialog::AllPages
    , QAbstractPrintDialog::Selection
    , QAbstractPrintDialog::PageRange
    , QAbstractPrintDialog::CurrentPage
};

static const char * const qtscript_QAbstractPrintDialog_PrintRange_keys[] = {
    "AllPages"
    , "Selection"
    , "PageRange"
    , "CurrentPage"
};

static QString qtscript_QAbstractPrintDialog_PrintRange_toStringHelper(QAbstractPrintDialog::PrintRange value)
{
    if ((value >= QAbstractPrintDialog::AllPages) && (value <= QAbstractPrintDialog::CurrentPage))
        return qtscript_QAbstractPrintDialog_PrintRange_keys[static_cast<int>(value)-static_cast<int>(QAbstractPrintDialog::AllPages)];
    return QString();
}

static QScriptValue qtscript_QAbstractPrintDialog_PrintRange_toScriptValue(QScriptEngine *engine, const QAbstractPrintDialog::PrintRange &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractPrintDialog"));
    return clazz.property(qtscript_QAbstractPrintDialog_PrintRange_toStringHelper(value));
}

static void qtscript_QAbstractPrintDialog_PrintRange_fromScriptValue(const QScriptValue &value, QAbstractPrintDialog::PrintRange &out)
{
    out = qvariant_cast<QAbstractPrintDialog::PrintRange>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractPrintDialog_PrintRange(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractPrintDialog::AllPages) && (arg <= QAbstractPrintDialog::CurrentPage))
        return qScriptValueFromValue(engine,  static_cast<QAbstractPrintDialog::PrintRange>(arg));
    return context->throwError(QString::fromLatin1("PrintRange(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractPrintDialog_PrintRange_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractPrintDialog::PrintRange value = qscriptvalue_cast<QAbstractPrintDialog::PrintRange>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractPrintDialog_PrintRange_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractPrintDialog::PrintRange value = qscriptvalue_cast<QAbstractPrintDialog::PrintRange>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractPrintDialog_PrintRange_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractPrintDialog_PrintRange_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractPrintDialog_PrintRange,
        qtscript_QAbstractPrintDialog_PrintRange_valueOf, qtscript_QAbstractPrintDialog_PrintRange_toString);
    qScriptRegisterMetaType<QAbstractPrintDialog::PrintRange>(engine, qtscript_QAbstractPrintDialog_PrintRange_toScriptValue,
        qtscript_QAbstractPrintDialog_PrintRange_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractPrintDialog_PrintRange_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractPrintDialog_PrintRange_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractPrintDialog
//

static QScriptValue qtscript_QAbstractPrintDialog_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QAbstractPrintDialog* _q_self = qscriptvalue_cast<QAbstractPrintDialog*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractPrintDialog.%0(): this object is not a QAbstractPrintDialog")
            .arg(qtscript_QAbstractPrintDialog_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QAbstractPrintDialog::PrintDialogOption _q_arg0 = qscriptvalue_cast<QAbstractPrintDialog::PrintDialogOption>(context->argument(0));
        _q_self->addEnabledOption(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QFlags<QAbstractPrintDialog::PrintDialogOption> _q_result = _q_self->enabledOptions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->fromPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QAbstractPrintDialog::PrintDialogOption _q_arg0 = qscriptvalue_cast<QAbstractPrintDialog::PrintDialogOption>(context->argument(0));
        bool _q_result = _q_self->isOptionEnabled(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->maxPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->minPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QAbstractPrintDialog::PrintRange _q_result = _q_self->printRange();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QPrinter* _q_result = _q_self->printer();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QFlags<QAbstractPrintDialog::PrintDialogOption> _q_arg0 = qscriptvalue_cast<QFlags<QAbstractPrintDialog::PrintDialogOption> >(context->argument(0));
        _q_self->setEnabledOptions(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setFromTo(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setMinMax(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QList<QWidget*> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setOptionTabs(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QAbstractPrintDialog::PrintRange _q_arg0 = qscriptvalue_cast<QAbstractPrintDialog::PrintRange>(context->argument(0));
        _q_self->setPrintRange(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->toPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14: {
    QString result = QString::fromLatin1("QAbstractPrintDialog");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractPrintDialog_throw_ambiguity_error_helper(context,
        qtscript_QAbstractPrintDialog_function_names[_id+1],
        qtscript_QAbstractPrintDialog_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractPrintDialog_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractPrintDialog(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QPrinter* _q_arg0 = qscriptvalue_cast<QPrinter*>(context->argument(0));
        QtScriptShell_QAbstractPrintDialog* _q_cpp_result = new QtScriptShell_QAbstractPrintDialog(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractPrintDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QPrinter* _q_arg0 = qscriptvalue_cast<QPrinter*>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QAbstractPrintDialog* _q_cpp_result = new QtScriptShell_QAbstractPrintDialog(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractPrintDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractPrintDialog_throw_ambiguity_error_helper(context,
        qtscript_QAbstractPrintDialog_function_names[_id],
        qtscript_QAbstractPrintDialog_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractPrintDialog_toScriptValue(QScriptEngine *engine, QAbstractPrintDialog* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractPrintDialog_fromScriptValue(const QScriptValue &value, QAbstractPrintDialog* &out)
{
    out = qobject_cast<QAbstractPrintDialog*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractPrintDialog_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractPrintDialog*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractPrintDialog*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDialog*>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractPrintDialog_prototype_call, qtscript_QAbstractPrintDialog_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractPrintDialog_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractPrintDialog*>(engine, qtscript_QAbstractPrintDialog_toScriptValue, 
        qtscript_QAbstractPrintDialog_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractPrintDialog_static_call, proto, qtscript_QAbstractPrintDialog_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("PrintDialogOption"),
        qtscript_create_QAbstractPrintDialog_PrintDialogOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PrintDialogOptions"),
        qtscript_create_QAbstractPrintDialog_PrintDialogOptions_class(engine));
    ctor.setProperty(QString::fromLatin1("PrintRange"),
        qtscript_create_QAbstractPrintDialog_PrintRange_class(engine, ctor));
    return ctor;
}
