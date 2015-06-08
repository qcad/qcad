#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsvgrenderer.h>
#include <QByteArray>
#include <QMatrix>
#include <QRectF>
#include <QSize>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qmatrix.h>
#include <qobject.h>
#include <qpainter.h>
#include <qrect.h>
#include <qsize.h>
#include <qxmlstream.h>

#include "qtscriptshell_QSvgRenderer.h"

static const char * const qtscript_QSvgRenderer_function_names[] = {
    "QSvgRenderer"
    // static
    // prototype
    , "animated"
    , "animationDuration"
    , "boundsOnElement"
    , "defaultSize"
    , "elementExists"
    , "isValid"
    , "matrixForElement"
    , "setViewBox"
    , "viewBox"
    , "toString"
};

static const char * const qtscript_QSvgRenderer_function_signatures[] = {
    "QObject parent\nQXmlStreamReader contents, QObject parent\nQByteArray contents, QObject parent\nString filename, QObject parent"
    // static
    // prototype
    , ""
    , ""
    , "String id"
    , ""
    , "String id"
    , ""
    , "String id"
    , "QRect viewbox"
    , ""
""
};

static const int qtscript_QSvgRenderer_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 1
    , 0
    , 1
    , 0
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QSvgRenderer_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSvgRenderer::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSvgRenderer*)
Q_DECLARE_METATYPE(QtScriptShell_QSvgRenderer*)
Q_DECLARE_METATYPE(QXmlStreamReader*)

//
// QSvgRenderer
//

static QScriptValue qtscript_QSvgRenderer_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 9;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSvgRenderer* _q_self = qscriptvalue_cast<QSvgRenderer*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSvgRenderer.%0(): this object is not a QSvgRenderer")
            .arg(qtscript_QSvgRenderer_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->animated();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->animationDuration();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QRectF _q_result = _q_self->boundsOnElement(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->defaultSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->elementExists(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QMatrix _q_result = _q_self->matrixForElement(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        _q_self->setViewBox(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->viewBox();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9: {
    QString result = QString::fromLatin1("QSvgRenderer");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSvgRenderer_throw_ambiguity_error_helper(context,
        qtscript_QSvgRenderer_function_names[_id+1],
        qtscript_QSvgRenderer_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSvgRenderer_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSvgRenderer(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSvgRenderer* _q_cpp_result = new QtScriptShell_QSvgRenderer();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSvgRenderer*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QSvgRenderer* _q_cpp_result = new QtScriptShell_QSvgRenderer(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSvgRenderer*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QXmlStreamReader*>(context->argument(0))) {
            QXmlStreamReader* _q_arg0 = qscriptvalue_cast<QXmlStreamReader*>(context->argument(0));
            QtScriptShell_QSvgRenderer* _q_cpp_result = new QtScriptShell_QSvgRenderer(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSvgRenderer*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QtScriptShell_QSvgRenderer* _q_cpp_result = new QtScriptShell_QSvgRenderer(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSvgRenderer*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QSvgRenderer* _q_cpp_result = new QtScriptShell_QSvgRenderer(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSvgRenderer*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QXmlStreamReader*>(context->argument(0))
            && context->argument(1).isQObject()) {
            QXmlStreamReader* _q_arg0 = qscriptvalue_cast<QXmlStreamReader*>(context->argument(0));
            QObject* _q_arg1 = context->argument(1).toQObject();
            QtScriptShell_QSvgRenderer* _q_cpp_result = new QtScriptShell_QSvgRenderer(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSvgRenderer*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && context->argument(1).isQObject()) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            QObject* _q_arg1 = context->argument(1).toQObject();
            QtScriptShell_QSvgRenderer* _q_cpp_result = new QtScriptShell_QSvgRenderer(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSvgRenderer*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isQObject()) {
            QString _q_arg0 = context->argument(0).toString();
            QObject* _q_arg1 = context->argument(1).toQObject();
            QtScriptShell_QSvgRenderer* _q_cpp_result = new QtScriptShell_QSvgRenderer(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSvgRenderer*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSvgRenderer_throw_ambiguity_error_helper(context,
        qtscript_QSvgRenderer_function_names[_id],
        qtscript_QSvgRenderer_function_signatures[_id]);
}

static QScriptValue qtscript_QSvgRenderer_toScriptValue(QScriptEngine *engine, QSvgRenderer* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSvgRenderer_fromScriptValue(const QScriptValue &value, QSvgRenderer* &out)
{
    out = qobject_cast<QSvgRenderer*>(value.toQObject());
}

QScriptValue qtscript_create_QSvgRenderer_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSvgRenderer*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSvgRenderer*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSvgRenderer_prototype_call, qtscript_QSvgRenderer_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSvgRenderer_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSvgRenderer*>(engine, qtscript_QSvgRenderer_toScriptValue, 
        qtscript_QSvgRenderer_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSvgRenderer_static_call, proto, qtscript_QSvgRenderer_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
