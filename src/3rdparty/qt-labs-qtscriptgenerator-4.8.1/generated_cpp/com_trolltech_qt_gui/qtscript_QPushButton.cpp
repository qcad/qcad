#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpushbutton.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbuttongroup.h>
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
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qmenu.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qpushbutton.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QPushButton.h"

static const char * const qtscript_QPushButton_function_names[] = {
    "QPushButton"
    // static
    // prototype
    , "menu"
    , "minimumSizeHint"
    , "setMenu"
    , "sizeHint"
    , "toString"
};

static const char * const qtscript_QPushButton_function_signatures[] = {
    "QWidget parent\nQIcon icon, String text, QWidget parent\nString text, QWidget parent"
    // static
    // prototype
    , ""
    , ""
    , "QMenu menu"
    , ""
""
};

static const int qtscript_QPushButton_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QPushButton_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPushButton::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPushButton*)
Q_DECLARE_METATYPE(QtScriptShell_QPushButton*)
Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(QAbstractButton*)

//
// QPushButton
//

static QScriptValue qtscript_QPushButton_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QPushButton* _q_self = qscriptvalue_cast<QPushButton*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPushButton.%0(): this object is not a QPushButton")
            .arg(qtscript_QPushButton_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QMenu* _q_result = _q_self->menu();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QMenu* _q_arg0 = qscriptvalue_cast<QMenu*>(context->argument(0));
        _q_self->setMenu(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QPushButton");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPushButton_throw_ambiguity_error_helper(context,
        qtscript_QPushButton_function_names[_id+1],
        qtscript_QPushButton_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPushButton_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPushButton(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPushButton* _q_cpp_result = new QtScriptShell_QPushButton();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPushButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QPushButton* _q_cpp_result = new QtScriptShell_QPushButton(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPushButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QPushButton* _q_cpp_result = new QtScriptShell_QPushButton(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPushButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QIcon>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QtScriptShell_QPushButton* _q_cpp_result = new QtScriptShell_QPushButton(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPushButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QtScriptShell_QPushButton* _q_cpp_result = new QtScriptShell_QPushButton(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPushButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        QtScriptShell_QPushButton* _q_cpp_result = new QtScriptShell_QPushButton(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPushButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPushButton_throw_ambiguity_error_helper(context,
        qtscript_QPushButton_function_names[_id],
        qtscript_QPushButton_function_signatures[_id]);
}

static QScriptValue qtscript_QPushButton_toScriptValue(QScriptEngine *engine, QPushButton* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QPushButton_fromScriptValue(const QScriptValue &value, QPushButton* &out)
{
    out = qobject_cast<QPushButton*>(value.toQObject());
}

QScriptValue qtscript_create_QPushButton_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPushButton*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPushButton*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractButton*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPushButton_prototype_call, qtscript_QPushButton_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPushButton_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QPushButton*>(engine, qtscript_QPushButton_toScriptValue, 
        qtscript_QPushButton_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPushButton_static_call, proto, qtscript_QPushButton_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
