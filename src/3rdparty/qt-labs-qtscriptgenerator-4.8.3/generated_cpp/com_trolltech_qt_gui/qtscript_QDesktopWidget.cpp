#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qdesktopwidget.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdesktopwidget.h>
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

#include "qtscriptshell_QDesktopWidget.h"

static const char * const qtscript_QDesktopWidget_function_names[] = {
    "QDesktopWidget"
    // static
    // prototype
    , "availableGeometry"
    , "numScreens"
    , "screen"
    , "screenGeometry"
    , "screenNumber"
    , "toString"
};

static const char * const qtscript_QDesktopWidget_function_signatures[] = {
    ""
    // static
    // prototype
    , "QPoint point\nQWidget widget\nint screen"
    , ""
    , "int screen"
    , "QPoint point\nQWidget widget\nint screen"
    , "QPoint arg__1\nQWidget widget"
""
};

static const int qtscript_QDesktopWidget_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 0
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QDesktopWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDesktopWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDesktopWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QDesktopWidget*)

//
// QDesktopWidget
//

static QScriptValue qtscript_QDesktopWidget_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QDesktopWidget* _q_self = qscriptvalue_cast<QDesktopWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDesktopWidget.%0(): this object is not a QDesktopWidget")
            .arg(qtscript_QDesktopWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->availableGeometry();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QRect _q_result = _q_self->availableGeometry(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QRect _q_result = _q_self->availableGeometry(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QRect _q_result = _q_self->availableGeometry(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->numScreens();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->screen();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_result = _q_self->screen(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->screenGeometry();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QRect _q_result = _q_self->screenGeometry(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QRect _q_result = _q_self->screenGeometry(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QRect _q_result = _q_self->screenGeometry(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->screenNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            int _q_result = _q_self->screenNumber(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            int _q_result = _q_self->screenNumber(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QDesktopWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDesktopWidget_throw_ambiguity_error_helper(context,
        qtscript_QDesktopWidget_function_names[_id+1],
        qtscript_QDesktopWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDesktopWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDesktopWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QDesktopWidget* _q_cpp_result = new QtScriptShell_QDesktopWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDesktopWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDesktopWidget_throw_ambiguity_error_helper(context,
        qtscript_QDesktopWidget_function_names[_id],
        qtscript_QDesktopWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QDesktopWidget_toScriptValue(QScriptEngine *engine, QDesktopWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QDesktopWidget_fromScriptValue(const QScriptValue &value, QDesktopWidget* &out)
{
    out = qobject_cast<QDesktopWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QDesktopWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDesktopWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDesktopWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDesktopWidget_prototype_call, qtscript_QDesktopWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDesktopWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QDesktopWidget*>(engine, qtscript_QDesktopWidget_toScriptValue, 
        qtscript_QDesktopWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDesktopWidget_static_call, proto, qtscript_QDesktopWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
