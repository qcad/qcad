#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicsproxywidget.h>
#include <QVariant>
#include <qaction.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsitem.h>
#include <qgraphicslayout.h>
#include <qgraphicslayoutitem.h>
#include <qgraphicsproxywidget.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qgraphicstransform.h>
#include <qgraphicswidget.h>
#include <qkeysequence.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qtransform.h>
#include <qwidget.h>

#include "qtscriptshell_QGraphicsProxyWidget.h"

static const char * const qtscript_QGraphicsProxyWidget_function_names[] = {
    "QGraphicsProxyWidget"
    // static
    // prototype
    , "createProxyForChildWidget"
    , "setWidget"
    , "subWidgetRect"
    , "widget"
    , "toString"
};

static const char * const qtscript_QGraphicsProxyWidget_function_signatures[] = {
    "QGraphicsItem parent, WindowFlags wFlags"
    // static
    // prototype
    , "QWidget child"
    , "QWidget widget"
    , "QWidget widget"
    , ""
""
};

static const int qtscript_QGraphicsProxyWidget_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsProxyWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsProxyWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsProxyWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsProxyWidget*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)
Q_DECLARE_METATYPE(QGraphicsWidget*)

//
// QGraphicsProxyWidget
//

static QScriptValue qtscript_QGraphicsProxyWidget_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGraphicsProxyWidget* _q_self = qscriptvalue_cast<QGraphicsProxyWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsProxyWidget.%0(): this object is not a QGraphicsProxyWidget")
            .arg(qtscript_QGraphicsProxyWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QGraphicsProxyWidget* _q_result = _q_self->createProxyForChildWidget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QRectF _q_result = _q_self->subWidgetRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->widget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QGraphicsProxyWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsProxyWidget_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsProxyWidget_function_names[_id+1],
        qtscript_QGraphicsProxyWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsProxyWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsProxyWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsProxyWidget* _q_cpp_result = new QtScriptShell_QGraphicsProxyWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsProxyWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QtScriptShell_QGraphicsProxyWidget* _q_cpp_result = new QtScriptShell_QGraphicsProxyWidget(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsProxyWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QtScriptShell_QGraphicsProxyWidget* _q_cpp_result = new QtScriptShell_QGraphicsProxyWidget(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsProxyWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsProxyWidget_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsProxyWidget_function_names[_id],
        qtscript_QGraphicsProxyWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsProxyWidget_toScriptValue(QScriptEngine *engine, QGraphicsProxyWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsProxyWidget_fromScriptValue(const QScriptValue &value, QGraphicsProxyWidget* &out)
{
    out = qobject_cast<QGraphicsProxyWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsProxyWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsProxyWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsProxyWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsWidget*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsProxyWidget_prototype_call, qtscript_QGraphicsProxyWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsProxyWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGraphicsProxyWidget*>(engine, qtscript_QGraphicsProxyWidget_toScriptValue, 
        qtscript_QGraphicsProxyWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsProxyWidget_static_call, proto, qtscript_QGraphicsProxyWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
