#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgraphicsitemanimation.h>
#include <QPair>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qgraphicsitem.h>
#include <qgraphicsitemanimation.h>
#include <qlist.h>
#include <qmatrix.h>
#include <qobject.h>
#include <qpair.h>
#include <qpoint.h>
#include <qtimeline.h>

#include "qtscriptshell_QGraphicsItemAnimation.h"

static const char * const qtscript_QGraphicsItemAnimation_function_names[] = {
    "QGraphicsItemAnimation"
    // static
    // prototype
    , "clear"
    , "horizontalScaleAt"
    , "horizontalShearAt"
    , "item"
    , "matrixAt"
    , "posAt"
    , "posList"
    , "rotationAt"
    , "rotationList"
    , "scaleList"
    , "setItem"
    , "setPosAt"
    , "setRotationAt"
    , "setScaleAt"
    , "setShearAt"
    , "setTimeLine"
    , "setTranslationAt"
    , "shearList"
    , "timeLine"
    , "translationList"
    , "verticalScaleAt"
    , "verticalShearAt"
    , "xTranslationAt"
    , "yTranslationAt"
    , "toString"
};

static const char * const qtscript_QGraphicsItemAnimation_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , "qreal step"
    , "qreal step"
    , ""
    , "qreal step"
    , "qreal step"
    , ""
    , "qreal step"
    , ""
    , ""
    , "QGraphicsItem item"
    , "qreal step, QPointF pos"
    , "qreal step, qreal angle"
    , "qreal step, qreal sx, qreal sy"
    , "qreal step, qreal sh, qreal sv"
    , "QTimeLine timeLine"
    , "qreal step, qreal dx, qreal dy"
    , ""
    , ""
    , ""
    , "qreal step"
    , "qreal step"
    , "qreal step"
    , "qreal step"
""
};

static const int qtscript_QGraphicsItemAnimation_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 1
    , 0
    , 1
    , 1
    , 0
    , 1
    , 0
    , 0
    , 1
    , 2
    , 2
    , 3
    , 3
    , 1
    , 3
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QGraphicsItemAnimation_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsItemAnimation::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsItemAnimation*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsItemAnimation*)
template <> \
struct QMetaTypeId< QPair<qreal,QPointF > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QPair<qreal,QPointF > >("QPair<qreal,QPointF >")); \
        return metatype_id.load(); \
    } \
};
template <> \
struct QMetaTypeId< QList<QPair<qreal,QPointF > > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QList<QPair<qreal,QPointF > > >("QList<QPair<qreal,QPointF > >")); \
        return metatype_id.load(); \
    } \
};
template <> \
struct QMetaTypeId< QPair<qreal,qreal > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QPair<qreal,qreal > >("QPair<qreal,qreal >")); \
        return metatype_id.load(); \
    } \
};
template <> \
struct QMetaTypeId< QList<QPair<qreal,qreal > > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QList<QPair<qreal,qreal > > >("QList<QPair<qreal,qreal > >")); \
        return metatype_id.load(); \
    } \
};
Q_DECLARE_METATYPE(QTimeLine*)

//
// QGraphicsItemAnimation
//

static QScriptValue qtscript_QGraphicsItemAnimation_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 24;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsItemAnimation* _q_self = qscriptvalue_cast<QGraphicsItemAnimation*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsItemAnimation.%0(): this object is not a QGraphicsItemAnimation")
            .arg(qtscript_QGraphicsItemAnimation_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_result = _q_self->horizontalScaleAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_result = _q_self->horizontalShearAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QGraphicsItem* _q_result = _q_self->item();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QMatrix _q_result = _q_self->matrixAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QPointF _q_result = _q_self->posAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QList<QPair<qreal,QPointF > > _q_result = _q_self->posList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_result = _q_self->rotationAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QList<QPair<qreal,qreal > > _q_result = _q_self->rotationList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QList<QPair<qreal,QPointF > > _q_result = _q_self->scaleList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        _q_self->setItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
        _q_self->setPosAt(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setRotationAt(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->setScaleAt(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->setShearAt(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QTimeLine* _q_arg0 = qscriptvalue_cast<QTimeLine*>(context->argument(0));
        _q_self->setTimeLine(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 3) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        _q_self->setTranslationAt(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QList<QPair<qreal,QPointF > > _q_result = _q_self->shearList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QTimeLine* _q_result = _q_self->timeLine();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QList<QPair<qreal,QPointF > > _q_result = _q_self->translationList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_result = _q_self->verticalScaleAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_result = _q_self->verticalShearAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_result = _q_self->xTranslationAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_result = _q_self->yTranslationAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24: {
    QString result = QString::fromLatin1("QGraphicsItemAnimation");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsItemAnimation_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsItemAnimation_function_names[_id+1],
        qtscript_QGraphicsItemAnimation_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsItemAnimation_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsItemAnimation(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsItemAnimation* _q_cpp_result = new QtScriptShell_QGraphicsItemAnimation();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsItemAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QGraphicsItemAnimation* _q_cpp_result = new QtScriptShell_QGraphicsItemAnimation(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsItemAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsItemAnimation_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsItemAnimation_function_names[_id],
        qtscript_QGraphicsItemAnimation_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsItemAnimation_toScriptValue(QScriptEngine *engine, QGraphicsItemAnimation* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsItemAnimation_fromScriptValue(const QScriptValue &value, QGraphicsItemAnimation* &out)
{
    out = qobject_cast<QGraphicsItemAnimation*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsItemAnimation_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsItemAnimation*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsItemAnimation*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 25; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsItemAnimation_prototype_call, qtscript_QGraphicsItemAnimation_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsItemAnimation_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGraphicsItemAnimation*>(engine, qtscript_QGraphicsItemAnimation_toScriptValue, 
        qtscript_QGraphicsItemAnimation_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsItemAnimation_static_call, proto, qtscript_QGraphicsItemAnimation_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
