#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qprogressbar.h>
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
#include <qprogressbar.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QProgressBar.h"

static const char * const qtscript_QProgressBar_function_names[] = {
    "QProgressBar"
    // static
    // prototype
    , "minimumSizeHint"
    , "sizeHint"
    , "toString"
};

static const char * const qtscript_QProgressBar_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
    , ""
""
};

static const int qtscript_QProgressBar_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QProgressBar_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QProgressBar::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QProgressBar_metaObject()
{
    return &QProgressBar::staticMetaObject;
}

Q_DECLARE_METATYPE(QProgressBar*)
Q_DECLARE_METATYPE(QtScriptShell_QProgressBar*)
Q_DECLARE_METATYPE(QProgressBar::Direction)

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
// QProgressBar::Direction
//

static const QProgressBar::Direction qtscript_QProgressBar_Direction_values[] = {
    QProgressBar::TopToBottom
    , QProgressBar::BottomToTop
};

static const char * const qtscript_QProgressBar_Direction_keys[] = {
    "TopToBottom"
    , "BottomToTop"
};

static QString qtscript_QProgressBar_Direction_toStringHelper(QProgressBar::Direction value)
{
    const QMetaObject *meta = qtscript_QProgressBar_metaObject();
    int idx = meta->indexOfEnumerator("Direction");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QProgressBar_Direction_toScriptValue(QScriptEngine *engine, const QProgressBar::Direction &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QProgressBar"));
    return clazz.property(qtscript_QProgressBar_Direction_toStringHelper(value));
}

static void qtscript_QProgressBar_Direction_fromScriptValue(const QScriptValue &value, QProgressBar::Direction &out)
{
    out = qvariant_cast<QProgressBar::Direction>(value.toVariant());
}

static QScriptValue qtscript_construct_QProgressBar_Direction(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QProgressBar_metaObject();
    int idx = meta->indexOfEnumerator("Direction");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QProgressBar::Direction>(arg));
    return context->throwError(QString::fromLatin1("Direction(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QProgressBar_Direction_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QProgressBar::Direction value = qscriptvalue_cast<QProgressBar::Direction>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QProgressBar_Direction_toString(QScriptContext *context, QScriptEngine *engine)
{
    QProgressBar::Direction value = qscriptvalue_cast<QProgressBar::Direction>(context->thisObject());
    return QScriptValue(engine, qtscript_QProgressBar_Direction_toStringHelper(value));
}

static QScriptValue qtscript_create_QProgressBar_Direction_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QProgressBar_Direction,
        qtscript_QProgressBar_Direction_valueOf, qtscript_QProgressBar_Direction_toString);
    qScriptRegisterMetaType<QProgressBar::Direction>(engine, qtscript_QProgressBar_Direction_toScriptValue,
        qtscript_QProgressBar_Direction_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QProgressBar_Direction_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QProgressBar_Direction_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QProgressBar
//

static QScriptValue qtscript_QProgressBar_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QProgressBar* _q_self = qscriptvalue_cast<QProgressBar*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QProgressBar.%0(): this object is not a QProgressBar")
            .arg(qtscript_QProgressBar_function_names[_id+1]));
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
    QString result = QString::fromLatin1("QProgressBar");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QProgressBar_throw_ambiguity_error_helper(context,
        qtscript_QProgressBar_function_names[_id+1],
        qtscript_QProgressBar_function_signatures[_id+1]);
}

static QScriptValue qtscript_QProgressBar_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QProgressBar(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QProgressBar* _q_cpp_result = new QtScriptShell_QProgressBar();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QProgressBar*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QProgressBar* _q_cpp_result = new QtScriptShell_QProgressBar(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QProgressBar*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QProgressBar_throw_ambiguity_error_helper(context,
        qtscript_QProgressBar_function_names[_id],
        qtscript_QProgressBar_function_signatures[_id]);
}

static QScriptValue qtscript_QProgressBar_toScriptValue(QScriptEngine *engine, QProgressBar* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QProgressBar_fromScriptValue(const QScriptValue &value, QProgressBar* &out)
{
    out = qobject_cast<QProgressBar*>(value.toQObject());
}

QScriptValue qtscript_create_QProgressBar_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QProgressBar*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QProgressBar*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QProgressBar_prototype_call, qtscript_QProgressBar_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QProgressBar_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QProgressBar*>(engine, qtscript_QProgressBar_toScriptValue, 
        qtscript_QProgressBar_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QProgressBar_static_call, proto, qtscript_QProgressBar_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Direction"),
        qtscript_create_QProgressBar_Direction_class(engine, ctor));
    return ctor;
}
