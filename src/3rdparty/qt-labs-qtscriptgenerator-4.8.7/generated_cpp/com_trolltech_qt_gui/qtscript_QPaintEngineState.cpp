#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qpaintengine.h>
#include <QPainterPath>
#include <QVariant>
#include <qbrush.h>
#include <qfont.h>
#include <qmatrix.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpen.h>
#include <qpoint.h>
#include <qregion.h>
#include <qtransform.h>

#include "qtscriptshell_QPaintEngineState.h"

static const char * const qtscript_QPaintEngineState_function_names[] = {
    "QPaintEngineState"
    // static
    // prototype
    , "backgroundBrush"
    , "backgroundMode"
    , "brush"
    , "brushNeedsResolving"
    , "brushOrigin"
    , "clipOperation"
    , "clipPath"
    , "clipRegion"
    , "compositionMode"
    , "font"
    , "isClipEnabled"
    , "matrix"
    , "opacity"
    , "painter"
    , "pen"
    , "penNeedsResolving"
    , "renderHints"
    , "state"
    , "transform"
    , "toString"
};

static const char * const qtscript_QPaintEngineState_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QPaintEngineState_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QPaintEngineState_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPaintEngineState::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPaintEngineState*)
Q_DECLARE_METATYPE(QtScriptShell_QPaintEngineState*)
Q_DECLARE_METATYPE(Qt::BGMode)
Q_DECLARE_METATYPE(Qt::ClipOperation)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(QPainter::CompositionMode)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QFlags<QPainter::RenderHint>)
Q_DECLARE_METATYPE(QFlags<QPaintEngine::DirtyFlag>)

//
// QPaintEngineState
//

static QScriptValue qtscript_QPaintEngineState_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 19;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPaintEngineState* _q_self = qscriptvalue_cast<QPaintEngineState*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPaintEngineState.%0(): this object is not a QPaintEngineState")
            .arg(qtscript_QPaintEngineState_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->backgroundBrush();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        Qt::BGMode _q_result = _q_self->backgroundMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->brush();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->brushNeedsResolving();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->brushOrigin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        Qt::ClipOperation _q_result = _q_self->clipOperation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QPainterPath _q_result = _q_self->clipPath();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QRegion _q_result = _q_self->clipRegion();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QPainter::CompositionMode _q_result = _q_self->compositionMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QFont _q_result = _q_self->font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isClipEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QMatrix _q_result = _q_self->matrix();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->opacity();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QPainter* _q_result = _q_self->painter();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QPen _q_result = _q_self->pen();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->penNeedsResolving();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QFlags<QPainter::RenderHint> _q_result = _q_self->renderHints();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QFlags<QPaintEngine::DirtyFlag> _q_result = _q_self->state();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QTransform _q_result = _q_self->transform();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19: {
    QString result = QString::fromLatin1("QPaintEngineState");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPaintEngineState_throw_ambiguity_error_helper(context,
        qtscript_QPaintEngineState_function_names[_id+1],
        qtscript_QPaintEngineState_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPaintEngineState_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPaintEngineState(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPaintEngineState* _q_cpp_result = new QtScriptShell_QPaintEngineState();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPaintEngineState*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPaintEngineState_throw_ambiguity_error_helper(context,
        qtscript_QPaintEngineState_function_names[_id],
        qtscript_QPaintEngineState_function_signatures[_id]);
}

QScriptValue qtscript_create_QPaintEngineState_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPaintEngineState*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPaintEngineState*)0));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPaintEngineState_prototype_call, qtscript_QPaintEngineState_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPaintEngineState_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPaintEngineState*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPaintEngineState_static_call, proto, qtscript_QPaintEngineState_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
