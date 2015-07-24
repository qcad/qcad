#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qstackedlayout.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qlist.h>
#include <qmargins.h>
#include <qobject.h>
#include <qrect.h>
#include <qsize.h>
#include <qstackedlayout.h>
#include <qwidget.h>

#include "qtscriptshell_QStackedLayout.h"

static const char * const qtscript_QStackedLayout_function_names[] = {
    "QStackedLayout"
    // static
    // prototype
    , "addStackedWidget"
    , "currentWidget"
    , "insertWidget"
    , "widget"
    , "toString"
};

static const char * const qtscript_QStackedLayout_function_signatures[] = {
    "\nQLayout parentLayout\nQWidget parent"
    // static
    // prototype
    , "QWidget w"
    , ""
    , "int index, QWidget w"
    , "int arg__1"
""
};

static const int qtscript_QStackedLayout_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QStackedLayout_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStackedLayout::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QStackedLayout_metaObject()
{
    return &QStackedLayout::staticMetaObject;
}

Q_DECLARE_METATYPE(QStackedLayout*)
Q_DECLARE_METATYPE(QtScriptShell_QStackedLayout*)
Q_DECLARE_METATYPE(QStackedLayout::StackingMode)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QLayout*)

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
// QStackedLayout::StackingMode
//

static const QStackedLayout::StackingMode qtscript_QStackedLayout_StackingMode_values[] = {
    QStackedLayout::StackOne
    , QStackedLayout::StackAll
};

static const char * const qtscript_QStackedLayout_StackingMode_keys[] = {
    "StackOne"
    , "StackAll"
};

static QString qtscript_QStackedLayout_StackingMode_toStringHelper(QStackedLayout::StackingMode value)
{
    const QMetaObject *meta = qtscript_QStackedLayout_metaObject();
    int idx = meta->indexOfEnumerator("StackingMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QStackedLayout_StackingMode_toScriptValue(QScriptEngine *engine, const QStackedLayout::StackingMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStackedLayout"));
    return clazz.property(qtscript_QStackedLayout_StackingMode_toStringHelper(value));
}

static void qtscript_QStackedLayout_StackingMode_fromScriptValue(const QScriptValue &value, QStackedLayout::StackingMode &out)
{
    out = qvariant_cast<QStackedLayout::StackingMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QStackedLayout_StackingMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QStackedLayout_metaObject();
    int idx = meta->indexOfEnumerator("StackingMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QStackedLayout::StackingMode>(arg));
    return context->throwError(QString::fromLatin1("StackingMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStackedLayout_StackingMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStackedLayout::StackingMode value = qscriptvalue_cast<QStackedLayout::StackingMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStackedLayout_StackingMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStackedLayout::StackingMode value = qscriptvalue_cast<QStackedLayout::StackingMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QStackedLayout_StackingMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QStackedLayout_StackingMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStackedLayout_StackingMode,
        qtscript_QStackedLayout_StackingMode_valueOf, qtscript_QStackedLayout_StackingMode_toString);
    qScriptRegisterMetaType<QStackedLayout::StackingMode>(engine, qtscript_QStackedLayout_StackingMode_toScriptValue,
        qtscript_QStackedLayout_StackingMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStackedLayout_StackingMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStackedLayout_StackingMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStackedLayout
//

static QScriptValue qtscript_QStackedLayout_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStackedLayout* _q_self = qscriptvalue_cast<QStackedLayout*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStackedLayout.%0(): this object is not a QStackedLayout")
            .arg(qtscript_QStackedLayout_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_result = _q_self->addWidget(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->currentWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        int _q_result = _q_self->insertWidget(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_result = _q_self->widget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QStackedLayout");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStackedLayout_throw_ambiguity_error_helper(context,
        qtscript_QStackedLayout_function_names[_id+1],
        qtscript_QStackedLayout_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStackedLayout_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStackedLayout(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStackedLayout* _q_cpp_result = new QtScriptShell_QStackedLayout();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStackedLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QLayout*>(context->argument(0))) {
            QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
            QtScriptShell_QStackedLayout* _q_cpp_result = new QtScriptShell_QStackedLayout(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStackedLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QStackedLayout* _q_cpp_result = new QtScriptShell_QStackedLayout(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStackedLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStackedLayout_throw_ambiguity_error_helper(context,
        qtscript_QStackedLayout_function_names[_id],
        qtscript_QStackedLayout_function_signatures[_id]);
}

static QScriptValue qtscript_QStackedLayout_toScriptValue(QScriptEngine *engine, QStackedLayout* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QStackedLayout_fromScriptValue(const QScriptValue &value, QStackedLayout* &out)
{
    out = qobject_cast<QStackedLayout*>(value.toQObject());
}

QScriptValue qtscript_create_QStackedLayout_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStackedLayout*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStackedLayout*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QLayout*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStackedLayout_prototype_call, qtscript_QStackedLayout_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStackedLayout_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QStackedLayout*>(engine, qtscript_QStackedLayout_toScriptValue, 
        qtscript_QStackedLayout_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStackedLayout_static_call, proto, qtscript_QStackedLayout_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("StackingMode"),
        qtscript_create_QStackedLayout_StackingMode_class(engine, ctor));
    return ctor;
}
