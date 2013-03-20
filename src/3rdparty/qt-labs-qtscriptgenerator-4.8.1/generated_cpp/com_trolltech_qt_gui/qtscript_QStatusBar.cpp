#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qstatusbar.h>
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
#include <qstatusbar.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QStatusBar.h"

static const char * const qtscript_QStatusBar_function_names[] = {
    "QStatusBar"
    // static
    // prototype
    , "addPermanentWidget"
    , "addWidget"
    , "currentMessage"
    , "insertPermanentWidget"
    , "insertWidget"
    , "removeWidget"
    , "toString"
};

static const char * const qtscript_QStatusBar_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "QWidget widget, int stretch"
    , "QWidget widget, int stretch"
    , ""
    , "int index, QWidget widget, int stretch"
    , "int index, QWidget widget, int stretch"
    , "QWidget widget"
""
};

static const int qtscript_QStatusBar_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 2
    , 0
    , 3
    , 3
    , 1
    , 0
};

static QScriptValue qtscript_QStatusBar_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStatusBar::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStatusBar*)
Q_DECLARE_METATYPE(QtScriptShell_QStatusBar*)

//
// QStatusBar
//

static QScriptValue qtscript_QStatusBar_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStatusBar* _q_self = qscriptvalue_cast<QStatusBar*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStatusBar.%0(): this object is not a QStatusBar")
            .arg(qtscript_QStatusBar_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->addPermanentWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->addPermanentWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->addWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->addWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->currentMessage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        int _q_result = _q_self->insertPermanentWidget(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        int _q_result = _q_self->insertPermanentWidget(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        int _q_result = _q_self->insertWidget(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        int _q_result = _q_self->insertWidget(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->removeWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QStatusBar");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStatusBar_throw_ambiguity_error_helper(context,
        qtscript_QStatusBar_function_names[_id+1],
        qtscript_QStatusBar_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStatusBar_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStatusBar(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStatusBar* _q_cpp_result = new QtScriptShell_QStatusBar();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStatusBar*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QStatusBar* _q_cpp_result = new QtScriptShell_QStatusBar(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStatusBar*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStatusBar_throw_ambiguity_error_helper(context,
        qtscript_QStatusBar_function_names[_id],
        qtscript_QStatusBar_function_signatures[_id]);
}

static QScriptValue qtscript_QStatusBar_toScriptValue(QScriptEngine *engine, QStatusBar* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QStatusBar_fromScriptValue(const QScriptValue &value, QStatusBar* &out)
{
    out = qobject_cast<QStatusBar*>(value.toQObject());
}

QScriptValue qtscript_create_QStatusBar_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStatusBar*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStatusBar*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStatusBar_prototype_call, qtscript_QStatusBar_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStatusBar_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QStatusBar*>(engine, qtscript_QStatusBar_toScriptValue, 
        qtscript_QStatusBar_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStatusBar_static_call, proto, qtscript_QStatusBar_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
