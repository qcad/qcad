#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qprogressdialog.h>
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
#include <qkeysequence.h>
#include <qlabel.h>
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
#include <qprogressbar.h>
#include <qprogressdialog.h>
#include <qpushbutton.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QProgressDialog.h"

static const char * const qtscript_QProgressDialog_function_names[] = {
    "QProgressDialog"
    // static
    // prototype
    , "open"
    , "setBar"
    , "setCancelButton"
    , "setLabel"
    , "toString"
};

static const char * const qtscript_QProgressDialog_function_signatures[] = {
    "QWidget parent, WindowFlags flags\nString labelText, String cancelButtonText, int minimum, int maximum, QWidget parent, WindowFlags flags"
    // static
    // prototype
    , "QObject receiver, char member"
    , "QProgressBar bar"
    , "QPushButton button"
    , "QLabel label"
""
};

static const int qtscript_QProgressDialog_function_lengths[] = {
    6
    // static
    // prototype
    , 2
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QProgressDialog_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QProgressDialog::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QProgressDialog*)
Q_DECLARE_METATYPE(QtScriptShell_QProgressDialog*)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QProgressBar*)
Q_DECLARE_METATYPE(QPushButton*)
Q_DECLARE_METATYPE(QLabel*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)
Q_DECLARE_METATYPE(QDialog*)

//
// QProgressDialog
//

static QScriptValue qtscript_QProgressDialog_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QProgressDialog* _q_self = qscriptvalue_cast<QProgressDialog*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QProgressDialog.%0(): this object is not a QProgressDialog")
            .arg(qtscript_QProgressDialog_function_names[_id+1]));
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
    if (context->argumentCount() == 1) {
        QProgressBar* _q_arg0 = qscriptvalue_cast<QProgressBar*>(context->argument(0));
        _q_self->setBar(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QPushButton* _q_arg0 = qscriptvalue_cast<QPushButton*>(context->argument(0));
        _q_self->setCancelButton(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QLabel* _q_arg0 = qscriptvalue_cast<QLabel*>(context->argument(0));
        _q_self->setLabel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QProgressDialog");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QProgressDialog_throw_ambiguity_error_helper(context,
        qtscript_QProgressDialog_function_names[_id+1],
        qtscript_QProgressDialog_function_signatures[_id+1]);
}

static QScriptValue qtscript_QProgressDialog_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QProgressDialog(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QProgressDialog* _q_cpp_result = new QtScriptShell_QProgressDialog();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QProgressDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QProgressDialog* _q_cpp_result = new QtScriptShell_QProgressDialog(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QProgressDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QtScriptShell_QProgressDialog* _q_cpp_result = new QtScriptShell_QProgressDialog(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QProgressDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QtScriptShell_QProgressDialog* _q_cpp_result = new QtScriptShell_QProgressDialog(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QProgressDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 5) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QWidget* _q_arg4 = qscriptvalue_cast<QWidget*>(context->argument(4));
        QtScriptShell_QProgressDialog* _q_cpp_result = new QtScriptShell_QProgressDialog(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QProgressDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 6) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QWidget* _q_arg4 = qscriptvalue_cast<QWidget*>(context->argument(4));
        QFlags<Qt::WindowType> _q_arg5 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(5));
        QtScriptShell_QProgressDialog* _q_cpp_result = new QtScriptShell_QProgressDialog(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QProgressDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QProgressDialog_throw_ambiguity_error_helper(context,
        qtscript_QProgressDialog_function_names[_id],
        qtscript_QProgressDialog_function_signatures[_id]);
}

static QScriptValue qtscript_QProgressDialog_toScriptValue(QScriptEngine *engine, QProgressDialog* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QProgressDialog_fromScriptValue(const QScriptValue &value, QProgressDialog* &out)
{
    out = qobject_cast<QProgressDialog*>(value.toQObject());
}

QScriptValue qtscript_create_QProgressDialog_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QProgressDialog*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QProgressDialog*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDialog*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QProgressDialog_prototype_call, qtscript_QProgressDialog_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QProgressDialog_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QProgressDialog*>(engine, qtscript_QProgressDialog_toScriptValue, 
        qtscript_QProgressDialog_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QProgressDialog_static_call, proto, qtscript_QProgressDialog_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
