#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qprintdialog.h>
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

#include "qtscriptshell_QPrintDialog.h"

static const char * const qtscript_QPrintDialog_function_names[] = {
    "QPrintDialog"
    // static
    // prototype
    , "open"
    , "setOption"
    , "testOption"
    , "toString"
};

static const char * const qtscript_QPrintDialog_function_signatures[] = {
    "QPrinter printer, QWidget parent\nQWidget parent"
    // static
    // prototype
    , "QObject receiver, char member"
    , "PrintDialogOption option, bool on"
    , "PrintDialogOption option"
""
};

static const int qtscript_QPrintDialog_function_lengths[] = {
    2
    // static
    // prototype
    , 2
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QPrintDialog_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPrintDialog::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPrintDialog*)
Q_DECLARE_METATYPE(QtScriptShell_QPrintDialog*)
Q_DECLARE_METATYPE(const char*)
Q_DECLARE_METATYPE(QAbstractPrintDialog::PrintDialogOption)
Q_DECLARE_METATYPE(QPrinter*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QAbstractPrintDialog*)

//
// QPrintDialog
//

static QScriptValue qtscript_QPrintDialog_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPrintDialog* _q_self = qscriptvalue_cast<QPrintDialog*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPrintDialog.%0(): this object is not a QPrintDialog")
            .arg(qtscript_QPrintDialog_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        const char* _q_arg1 = qscriptvalue_cast<const char*>(context->argument(1));
        _q_self->open(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QAbstractPrintDialog::PrintDialogOption _q_arg0 = qscriptvalue_cast<QAbstractPrintDialog::PrintDialogOption>(context->argument(0));
        _q_self->setOption(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QAbstractPrintDialog::PrintDialogOption _q_arg0 = qscriptvalue_cast<QAbstractPrintDialog::PrintDialogOption>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QAbstractPrintDialog::PrintDialogOption _q_arg0 = qscriptvalue_cast<QAbstractPrintDialog::PrintDialogOption>(context->argument(0));
        bool _q_result = _q_self->testOption(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QPrintDialog");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPrintDialog_throw_ambiguity_error_helper(context,
        qtscript_QPrintDialog_function_names[_id+1],
        qtscript_QPrintDialog_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPrintDialog_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPrintDialog(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPrintDialog* _q_cpp_result = new QtScriptShell_QPrintDialog();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPrintDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QPrinter*>(context->argument(0))) {
            QPrinter* _q_arg0 = qscriptvalue_cast<QPrinter*>(context->argument(0));
            QtScriptShell_QPrintDialog* _q_cpp_result = new QtScriptShell_QPrintDialog(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPrintDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QPrintDialog* _q_cpp_result = new QtScriptShell_QPrintDialog(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPrintDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QPrinter* _q_arg0 = qscriptvalue_cast<QPrinter*>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QPrintDialog* _q_cpp_result = new QtScriptShell_QPrintDialog(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPrintDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPrintDialog_throw_ambiguity_error_helper(context,
        qtscript_QPrintDialog_function_names[_id],
        qtscript_QPrintDialog_function_signatures[_id]);
}

static QScriptValue qtscript_QPrintDialog_toScriptValue(QScriptEngine *engine, QPrintDialog* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QPrintDialog_fromScriptValue(const QScriptValue &value, QPrintDialog* &out)
{
    out = qobject_cast<QPrintDialog*>(value.toQObject());
}

QScriptValue qtscript_create_QPrintDialog_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPrintDialog*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPrintDialog*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractPrintDialog*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPrintDialog_prototype_call, qtscript_QPrintDialog_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPrintDialog_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QPrintDialog*>(engine, qtscript_QPrintDialog_toScriptValue, 
        qtscript_QPrintDialog_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPrintDialog_static_call, proto, qtscript_QPrintDialog_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
