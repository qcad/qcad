#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qslider.h>
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
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qslider.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QSlider.h"

static const char * const qtscript_QSlider_function_names[] = {
    "QSlider"
    // static
    // prototype
    , "minimumSizeHint"
    , "sizeHint"
    , "toString"
};

static const char * const qtscript_QSlider_function_signatures[] = {
    "QWidget parent\nOrientation orientation, QWidget parent"
    // static
    // prototype
    , ""
    , ""
""
};

static const int qtscript_QSlider_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QSlider_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSlider::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QSlider_metaObject()
{
    return &QSlider::staticMetaObject;
}

Q_DECLARE_METATYPE(QSlider*)
Q_DECLARE_METATYPE(QtScriptShell_QSlider*)
Q_DECLARE_METATYPE(QSlider::TickPosition)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QAbstractSlider*)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QSlider::TickPosition
//

static const QSlider::TickPosition qtscript_QSlider_TickPosition_values[] = {
    QSlider::NoTicks
    , QSlider::TicksAbove
    , QSlider::TicksBelow
    , QSlider::TicksBothSides
};

static const char * const qtscript_QSlider_TickPosition_keys[] = {
    "NoTicks"
    , "TicksAbove"
    , "TicksBelow"
    , "TicksBothSides"
};

static QString qtscript_QSlider_TickPosition_toStringHelper(QSlider::TickPosition value)
{
    const QMetaObject *meta = qtscript_QSlider_metaObject();
    int idx = meta->indexOfEnumerator("TickPosition");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QSlider_TickPosition_toScriptValue(QScriptEngine *engine, const QSlider::TickPosition &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSlider"));
    return clazz.property(qtscript_QSlider_TickPosition_toStringHelper(value));
}

static void qtscript_QSlider_TickPosition_fromScriptValue(const QScriptValue &value, QSlider::TickPosition &out)
{
    out = qvariant_cast<QSlider::TickPosition>(value.toVariant());
}

static QScriptValue qtscript_construct_QSlider_TickPosition(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QSlider_metaObject();
    int idx = meta->indexOfEnumerator("TickPosition");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QSlider::TickPosition>(arg));
    return context->throwError(QString::fromLatin1("TickPosition(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSlider_TickPosition_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSlider::TickPosition value = qscriptvalue_cast<QSlider::TickPosition>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSlider_TickPosition_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSlider::TickPosition value = qscriptvalue_cast<QSlider::TickPosition>(context->thisObject());
    return QScriptValue(engine, qtscript_QSlider_TickPosition_toStringHelper(value));
}

static QScriptValue qtscript_create_QSlider_TickPosition_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSlider_TickPosition,
        qtscript_QSlider_TickPosition_valueOf, qtscript_QSlider_TickPosition_toString);
    qScriptRegisterMetaType<QSlider::TickPosition>(engine, qtscript_QSlider_TickPosition_toScriptValue,
        qtscript_QSlider_TickPosition_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSlider_TickPosition_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSlider_TickPosition_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSlider
//

static QScriptValue qtscript_QSlider_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSlider* _q_self = qscriptvalue_cast<QSlider*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSlider.%0(): this object is not a QSlider")
            .arg(qtscript_QSlider_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
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
    QString result = QString::fromLatin1("QSlider");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSlider_throw_ambiguity_error_helper(context,
        qtscript_QSlider_function_names[_id+1],
        qtscript_QSlider_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSlider_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSlider(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSlider* _q_cpp_result = new QtScriptShell_QSlider();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSlider*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QSlider* _q_cpp_result = new QtScriptShell_QSlider(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSlider*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<Qt::Orientation>() == context->argument(0).toVariant().userType())) {
            Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
            QtScriptShell_QSlider* _q_cpp_result = new QtScriptShell_QSlider(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSlider*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QSlider* _q_cpp_result = new QtScriptShell_QSlider(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSlider*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSlider_throw_ambiguity_error_helper(context,
        qtscript_QSlider_function_names[_id],
        qtscript_QSlider_function_signatures[_id]);
}

static QScriptValue qtscript_QSlider_toScriptValue(QScriptEngine *engine, QSlider* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSlider_fromScriptValue(const QScriptValue &value, QSlider* &out)
{
    out = qobject_cast<QSlider*>(value.toQObject());
}

QScriptValue qtscript_create_QSlider_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSlider*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSlider*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractSlider*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSlider_prototype_call, qtscript_QSlider_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSlider_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSlider*>(engine, qtscript_QSlider_toScriptValue, 
        qtscript_QSlider_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSlider_static_call, proto, qtscript_QSlider_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("TickPosition"),
        qtscript_create_QSlider_TickPosition_class(engine, ctor));
    return ctor;
}
