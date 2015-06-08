#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qworkspace.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbrush.h>
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
#include <qwidget.h>
#include <qworkspace.h>

#include "qtscriptshell_QWorkspace.h"

static const char * const qtscript_QWorkspace_function_names[] = {
    "QWorkspace"
    // static
    // prototype
    , "activeWindow"
    , "addWindow"
    , "sizeHint"
    , "windowList"
    , "toString"
};

static const char * const qtscript_QWorkspace_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
    , "QWidget w, WindowFlags flags"
    , ""
    , "WindowOrder order"
""
};

static const int qtscript_QWorkspace_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 2
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QWorkspace_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWorkspace::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWorkspace*)
Q_DECLARE_METATYPE(QtScriptShell_QWorkspace*)
Q_DECLARE_METATYPE(QWorkspace::WindowOrder)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)
Q_DECLARE_METATYPE(QList<QWidget*>)

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
// QWorkspace::WindowOrder
//

static const QWorkspace::WindowOrder qtscript_QWorkspace_WindowOrder_values[] = {
    QWorkspace::CreationOrder
    , QWorkspace::StackingOrder
};

static const char * const qtscript_QWorkspace_WindowOrder_keys[] = {
    "CreationOrder"
    , "StackingOrder"
};

static QString qtscript_QWorkspace_WindowOrder_toStringHelper(QWorkspace::WindowOrder value)
{
    if ((value >= QWorkspace::CreationOrder) && (value <= QWorkspace::StackingOrder))
        return qtscript_QWorkspace_WindowOrder_keys[static_cast<int>(value)-static_cast<int>(QWorkspace::CreationOrder)];
    return QString();
}

static QScriptValue qtscript_QWorkspace_WindowOrder_toScriptValue(QScriptEngine *engine, const QWorkspace::WindowOrder &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWorkspace"));
    return clazz.property(qtscript_QWorkspace_WindowOrder_toStringHelper(value));
}

static void qtscript_QWorkspace_WindowOrder_fromScriptValue(const QScriptValue &value, QWorkspace::WindowOrder &out)
{
    out = qvariant_cast<QWorkspace::WindowOrder>(value.toVariant());
}

static QScriptValue qtscript_construct_QWorkspace_WindowOrder(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QWorkspace::CreationOrder) && (arg <= QWorkspace::StackingOrder))
        return qScriptValueFromValue(engine,  static_cast<QWorkspace::WindowOrder>(arg));
    return context->throwError(QString::fromLatin1("WindowOrder(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWorkspace_WindowOrder_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWorkspace::WindowOrder value = qscriptvalue_cast<QWorkspace::WindowOrder>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWorkspace_WindowOrder_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWorkspace::WindowOrder value = qscriptvalue_cast<QWorkspace::WindowOrder>(context->thisObject());
    return QScriptValue(engine, qtscript_QWorkspace_WindowOrder_toStringHelper(value));
}

static QScriptValue qtscript_create_QWorkspace_WindowOrder_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWorkspace_WindowOrder,
        qtscript_QWorkspace_WindowOrder_valueOf, qtscript_QWorkspace_WindowOrder_toString);
    qScriptRegisterMetaType<QWorkspace::WindowOrder>(engine, qtscript_QWorkspace_WindowOrder_toScriptValue,
        qtscript_QWorkspace_WindowOrder_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWorkspace_WindowOrder_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWorkspace_WindowOrder_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWorkspace
//

static QScriptValue qtscript_QWorkspace_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QWorkspace* _q_self = qscriptvalue_cast<QWorkspace*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWorkspace.%0(): this object is not a QWorkspace")
            .arg(qtscript_QWorkspace_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->activeWindow();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QWidget* _q_result = _q_self->addWindow(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QWidget* _q_result = _q_self->addWindow(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QList<QWidget*> _q_result = _q_self->windowList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QWorkspace::WindowOrder _q_arg0 = qscriptvalue_cast<QWorkspace::WindowOrder>(context->argument(0));
        QList<QWidget*> _q_result = _q_self->windowList(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QWorkspace");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWorkspace_throw_ambiguity_error_helper(context,
        qtscript_QWorkspace_function_names[_id+1],
        qtscript_QWorkspace_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWorkspace_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWorkspace(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QWorkspace* _q_cpp_result = new QtScriptShell_QWorkspace();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWorkspace*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QWorkspace* _q_cpp_result = new QtScriptShell_QWorkspace(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWorkspace*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWorkspace_throw_ambiguity_error_helper(context,
        qtscript_QWorkspace_function_names[_id],
        qtscript_QWorkspace_function_signatures[_id]);
}

static QScriptValue qtscript_QWorkspace_toScriptValue(QScriptEngine *engine, QWorkspace* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QWorkspace_fromScriptValue(const QScriptValue &value, QWorkspace* &out)
{
    out = qobject_cast<QWorkspace*>(value.toQObject());
}

QScriptValue qtscript_create_QWorkspace_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWorkspace*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWorkspace*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWorkspace_prototype_call, qtscript_QWorkspace_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWorkspace_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QWorkspace*>(engine, qtscript_QWorkspace_toScriptValue, 
        qtscript_QWorkspace_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWorkspace_static_call, proto, qtscript_QWorkspace_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("WindowOrder"),
        qtscript_create_QWorkspace_WindowOrder_class(engine, ctor));
    return ctor;
}
