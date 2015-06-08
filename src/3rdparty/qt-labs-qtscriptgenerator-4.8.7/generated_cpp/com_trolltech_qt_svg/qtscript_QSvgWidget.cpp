#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsvgwidget.h>
#include <QByteArray>
#include <QSize>
#include <QSvgRenderer>
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
#include <qstyle.h>
#include <qsvgrenderer.h>
#include <qsvgwidget.h>
#include <qwidget.h>

#include "qtscriptshell_QSvgWidget.h"

static const char * const qtscript_QSvgWidget_function_names[] = {
    "QSvgWidget"
    // static
    // prototype
    , "renderer"
    , "sizeHint"
    , "toString"
};

static const char * const qtscript_QSvgWidget_function_signatures[] = {
    "QWidget parent\nString file, QWidget parent"
    // static
    // prototype
    , ""
    , ""
""
};

static const int qtscript_QSvgWidget_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QSvgWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSvgWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSvgWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QSvgWidget*)
Q_DECLARE_METATYPE(QSvgRenderer*)

//
// QSvgWidget
//

static QScriptValue qtscript_QSvgWidget_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSvgWidget* _q_self = qscriptvalue_cast<QSvgWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSvgWidget.%0(): this object is not a QSvgWidget")
            .arg(qtscript_QSvgWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QSvgRenderer* _q_result = _q_self->renderer();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QSvgWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSvgWidget_throw_ambiguity_error_helper(context,
        qtscript_QSvgWidget_function_names[_id+1],
        qtscript_QSvgWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSvgWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSvgWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSvgWidget* _q_cpp_result = new QtScriptShell_QSvgWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSvgWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QSvgWidget* _q_cpp_result = new QtScriptShell_QSvgWidget(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSvgWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QSvgWidget* _q_cpp_result = new QtScriptShell_QSvgWidget(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSvgWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QSvgWidget* _q_cpp_result = new QtScriptShell_QSvgWidget(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSvgWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSvgWidget_throw_ambiguity_error_helper(context,
        qtscript_QSvgWidget_function_names[_id],
        qtscript_QSvgWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QSvgWidget_toScriptValue(QScriptEngine *engine, QSvgWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSvgWidget_fromScriptValue(const QScriptValue &value, QSvgWidget* &out)
{
    out = qobject_cast<QSvgWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QSvgWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSvgWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSvgWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSvgWidget_prototype_call, qtscript_QSvgWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSvgWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSvgWidget*>(engine, qtscript_QSvgWidget_toScriptValue, 
        qtscript_QSvgWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSvgWidget_static_call, proto, qtscript_QSvgWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
