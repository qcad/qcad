#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qwebinspector.h>
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
#include <qwebpage.h>
#include <qwidget.h>

#include "qtscriptshell_QWebInspector.h"

static const char * const qtscript_QWebInspector_function_names[] = {
    "QWebInspector"
    // static
    // prototype
    , "page"
    , "setPage"
    , "sizeHint"
    , "toString"
};

static const char * const qtscript_QWebInspector_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
    , "QWebPage page"
    , ""
""
};

static const int qtscript_QWebInspector_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QWebInspector_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWebInspector::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWebInspector*)
Q_DECLARE_METATYPE(QtScriptShell_QWebInspector*)
Q_DECLARE_METATYPE(QWebPage*)

//
// QWebInspector
//

static QScriptValue qtscript_QWebInspector_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QWebInspector* _q_self = qscriptvalue_cast<QWebInspector*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWebInspector.%0(): this object is not a QWebInspector")
            .arg(qtscript_QWebInspector_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QWebPage* _q_result = _q_self->page();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QWebPage* _q_arg0 = qscriptvalue_cast<QWebPage*>(context->argument(0));
        _q_self->setPage(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QWebInspector");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebInspector_throw_ambiguity_error_helper(context,
        qtscript_QWebInspector_function_names[_id+1],
        qtscript_QWebInspector_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWebInspector_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWebInspector(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QWebInspector* _q_cpp_result = new QtScriptShell_QWebInspector();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWebInspector*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QWebInspector* _q_cpp_result = new QtScriptShell_QWebInspector(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWebInspector*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebInspector_throw_ambiguity_error_helper(context,
        qtscript_QWebInspector_function_names[_id],
        qtscript_QWebInspector_function_signatures[_id]);
}

static QScriptValue qtscript_QWebInspector_toScriptValue(QScriptEngine *engine, QWebInspector* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QWebInspector_fromScriptValue(const QScriptValue &value, QWebInspector* &out)
{
    out = qobject_cast<QWebInspector*>(value.toQObject());
}

QScriptValue qtscript_create_QWebInspector_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWebInspector*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWebInspector*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWebInspector_prototype_call, qtscript_QWebInspector_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWebInspector_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QWebInspector*>(engine, qtscript_QWebInspector_toScriptValue, 
        qtscript_QWebInspector_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWebInspector_static_call, proto, qtscript_QWebInspector_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
