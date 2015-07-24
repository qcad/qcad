#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qstackedwidget.h>
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
#include <qstackedwidget.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QStackedWidget.h"

static const char * const qtscript_QStackedWidget_function_names[] = {
    "QStackedWidget"
    // static
    // prototype
    , "addWidget"
    , "currentWidget"
    , "indexOf"
    , "insertWidget"
    , "removeWidget"
    , "widget"
    , "toString"
};

static const char * const qtscript_QStackedWidget_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "QWidget w"
    , ""
    , "QWidget arg__1"
    , "int index, QWidget w"
    , "QWidget w"
    , "int arg__1"
""
};

static const int qtscript_QStackedWidget_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 1
    , 2
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QStackedWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStackedWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStackedWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QStackedWidget*)
Q_DECLARE_METATYPE(QFrame*)

//
// QStackedWidget
//

static QScriptValue qtscript_QStackedWidget_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 6;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QStackedWidget* _q_self = qscriptvalue_cast<QStackedWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStackedWidget.%0(): this object is not a QStackedWidget")
            .arg(qtscript_QStackedWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_result = _q_self->addWidget(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->currentWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_result = _q_self->indexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        int _q_result = _q_self->insertWidget(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->removeWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_result = _q_self->widget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QStackedWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStackedWidget_throw_ambiguity_error_helper(context,
        qtscript_QStackedWidget_function_names[_id+1],
        qtscript_QStackedWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStackedWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStackedWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStackedWidget* _q_cpp_result = new QtScriptShell_QStackedWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStackedWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QStackedWidget* _q_cpp_result = new QtScriptShell_QStackedWidget(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStackedWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStackedWidget_throw_ambiguity_error_helper(context,
        qtscript_QStackedWidget_function_names[_id],
        qtscript_QStackedWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QStackedWidget_toScriptValue(QScriptEngine *engine, QStackedWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QStackedWidget_fromScriptValue(const QScriptValue &value, QStackedWidget* &out)
{
    out = qobject_cast<QStackedWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QStackedWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStackedWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStackedWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QFrame*>()));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStackedWidget_prototype_call, qtscript_QStackedWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStackedWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QStackedWidget*>(engine, qtscript_QStackedWidget_toScriptValue, 
        qtscript_QStackedWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStackedWidget_static_call, proto, qtscript_QStackedWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
