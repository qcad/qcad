#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qmdiarea.h>
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
#include <qmdiarea.h>
#include <qmdisubwindow.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QMdiArea.h"

static const char * const qtscript_QMdiArea_function_names[] = {
    "QMdiArea"
    // static
    // prototype
    , "activeSubWindow"
    , "addSubWindow"
    , "currentSubWindow"
    , "removeSubWindow"
    , "setOption"
    , "subWindowList"
    , "testOption"
    , "toString"
};

static const char * const qtscript_QMdiArea_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
    , "QWidget widget, WindowFlags flags"
    , ""
    , "QWidget widget"
    , "AreaOption option, bool on"
    , "WindowOrder order"
    , "AreaOption opton"
""
};

static const int qtscript_QMdiArea_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 2
    , 0
    , 1
    , 2
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QMdiArea_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMdiArea::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QMdiArea_metaObject()
{
    return &QMdiArea::staticMetaObject;
}

Q_DECLARE_METATYPE(QMdiArea*)
Q_DECLARE_METATYPE(QtScriptShell_QMdiArea*)
Q_DECLARE_METATYPE(QMdiArea::WindowOrder)
Q_DECLARE_METATYPE(QMdiArea::ViewMode)
Q_DECLARE_METATYPE(QMdiArea::AreaOption)
Q_DECLARE_METATYPE(QFlags<QMdiArea::AreaOption>)
Q_DECLARE_METATYPE(QMdiSubWindow*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)
Q_DECLARE_METATYPE(QList<QMdiSubWindow*>)
Q_DECLARE_METATYPE(QAbstractScrollArea*)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QMdiArea::WindowOrder
//

static const QMdiArea::WindowOrder qtscript_QMdiArea_WindowOrder_values[] = {
    QMdiArea::CreationOrder
    , QMdiArea::StackingOrder
    , QMdiArea::ActivationHistoryOrder
};

static const char * const qtscript_QMdiArea_WindowOrder_keys[] = {
    "CreationOrder"
    , "StackingOrder"
    , "ActivationHistoryOrder"
};

static QString qtscript_QMdiArea_WindowOrder_toStringHelper(QMdiArea::WindowOrder value)
{
    const QMetaObject *meta = qtscript_QMdiArea_metaObject();
    int idx = meta->indexOfEnumerator("WindowOrder");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QMdiArea_WindowOrder_toScriptValue(QScriptEngine *engine, const QMdiArea::WindowOrder &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QMdiArea"));
    return clazz.property(qtscript_QMdiArea_WindowOrder_toStringHelper(value));
}

static void qtscript_QMdiArea_WindowOrder_fromScriptValue(const QScriptValue &value, QMdiArea::WindowOrder &out)
{
    out = qvariant_cast<QMdiArea::WindowOrder>(value.toVariant());
}

static QScriptValue qtscript_construct_QMdiArea_WindowOrder(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QMdiArea_metaObject();
    int idx = meta->indexOfEnumerator("WindowOrder");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QMdiArea::WindowOrder>(arg));
    return context->throwError(QString::fromLatin1("WindowOrder(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QMdiArea_WindowOrder_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMdiArea::WindowOrder value = qscriptvalue_cast<QMdiArea::WindowOrder>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMdiArea_WindowOrder_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMdiArea::WindowOrder value = qscriptvalue_cast<QMdiArea::WindowOrder>(context->thisObject());
    return QScriptValue(engine, qtscript_QMdiArea_WindowOrder_toStringHelper(value));
}

static QScriptValue qtscript_create_QMdiArea_WindowOrder_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QMdiArea_WindowOrder,
        qtscript_QMdiArea_WindowOrder_valueOf, qtscript_QMdiArea_WindowOrder_toString);
    qScriptRegisterMetaType<QMdiArea::WindowOrder>(engine, qtscript_QMdiArea_WindowOrder_toScriptValue,
        qtscript_QMdiArea_WindowOrder_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QMdiArea_WindowOrder_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QMdiArea_WindowOrder_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QMdiArea::ViewMode
//

static const QMdiArea::ViewMode qtscript_QMdiArea_ViewMode_values[] = {
    QMdiArea::SubWindowView
    , QMdiArea::TabbedView
};

static const char * const qtscript_QMdiArea_ViewMode_keys[] = {
    "SubWindowView"
    , "TabbedView"
};

static QString qtscript_QMdiArea_ViewMode_toStringHelper(QMdiArea::ViewMode value)
{
    const QMetaObject *meta = qtscript_QMdiArea_metaObject();
    int idx = meta->indexOfEnumerator("ViewMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QMdiArea_ViewMode_toScriptValue(QScriptEngine *engine, const QMdiArea::ViewMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QMdiArea"));
    return clazz.property(qtscript_QMdiArea_ViewMode_toStringHelper(value));
}

static void qtscript_QMdiArea_ViewMode_fromScriptValue(const QScriptValue &value, QMdiArea::ViewMode &out)
{
    out = qvariant_cast<QMdiArea::ViewMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QMdiArea_ViewMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QMdiArea_metaObject();
    int idx = meta->indexOfEnumerator("ViewMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QMdiArea::ViewMode>(arg));
    return context->throwError(QString::fromLatin1("ViewMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QMdiArea_ViewMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMdiArea::ViewMode value = qscriptvalue_cast<QMdiArea::ViewMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMdiArea_ViewMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMdiArea::ViewMode value = qscriptvalue_cast<QMdiArea::ViewMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QMdiArea_ViewMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QMdiArea_ViewMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QMdiArea_ViewMode,
        qtscript_QMdiArea_ViewMode_valueOf, qtscript_QMdiArea_ViewMode_toString);
    qScriptRegisterMetaType<QMdiArea::ViewMode>(engine, qtscript_QMdiArea_ViewMode_toScriptValue,
        qtscript_QMdiArea_ViewMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QMdiArea_ViewMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QMdiArea_ViewMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QMdiArea::AreaOption
//

static const QMdiArea::AreaOption qtscript_QMdiArea_AreaOption_values[] = {
    QMdiArea::DontMaximizeSubWindowOnActivation
};

static const char * const qtscript_QMdiArea_AreaOption_keys[] = {
    "DontMaximizeSubWindowOnActivation"
};

static QString qtscript_QMdiArea_AreaOption_toStringHelper(QMdiArea::AreaOption value)
{
    if ((value >= QMdiArea::DontMaximizeSubWindowOnActivation) && (value <= QMdiArea::DontMaximizeSubWindowOnActivation))
        return qtscript_QMdiArea_AreaOption_keys[static_cast<int>(value)-static_cast<int>(QMdiArea::DontMaximizeSubWindowOnActivation)];
    return QString();
}

static QScriptValue qtscript_QMdiArea_AreaOption_toScriptValue(QScriptEngine *engine, const QMdiArea::AreaOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QMdiArea"));
    return clazz.property(qtscript_QMdiArea_AreaOption_toStringHelper(value));
}

static void qtscript_QMdiArea_AreaOption_fromScriptValue(const QScriptValue &value, QMdiArea::AreaOption &out)
{
    out = qvariant_cast<QMdiArea::AreaOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QMdiArea_AreaOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QMdiArea::DontMaximizeSubWindowOnActivation) && (arg <= QMdiArea::DontMaximizeSubWindowOnActivation))
        return qScriptValueFromValue(engine,  static_cast<QMdiArea::AreaOption>(arg));
    return context->throwError(QString::fromLatin1("AreaOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QMdiArea_AreaOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMdiArea::AreaOption value = qscriptvalue_cast<QMdiArea::AreaOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMdiArea_AreaOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMdiArea::AreaOption value = qscriptvalue_cast<QMdiArea::AreaOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QMdiArea_AreaOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QMdiArea_AreaOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QMdiArea_AreaOption,
        qtscript_QMdiArea_AreaOption_valueOf, qtscript_QMdiArea_AreaOption_toString);
    qScriptRegisterMetaType<QMdiArea::AreaOption>(engine, qtscript_QMdiArea_AreaOption_toScriptValue,
        qtscript_QMdiArea_AreaOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QMdiArea_AreaOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QMdiArea_AreaOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QMdiArea::AreaOptions
//

static QScriptValue qtscript_QMdiArea_AreaOptions_toScriptValue(QScriptEngine *engine, const QMdiArea::AreaOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QMdiArea_AreaOptions_fromScriptValue(const QScriptValue &value, QMdiArea::AreaOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QMdiArea::AreaOptions>())
        out = qvariant_cast<QMdiArea::AreaOptions>(var);
    else if (var.userType() == qMetaTypeId<QMdiArea::AreaOption>())
        out = qvariant_cast<QMdiArea::AreaOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QMdiArea_AreaOptions(QScriptContext *context, QScriptEngine *engine)
{
    QMdiArea::AreaOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QMdiArea::AreaOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QMdiArea::AreaOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("AreaOptions(): argument %0 is not of type AreaOption").arg(i));
            }
            result |= qvariant_cast<QMdiArea::AreaOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QMdiArea_AreaOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMdiArea::AreaOptions value = qscriptvalue_cast<QMdiArea::AreaOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMdiArea_AreaOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMdiArea::AreaOptions value = qscriptvalue_cast<QMdiArea::AreaOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 1; ++i) {
        if ((value & qtscript_QMdiArea_AreaOption_values[i]) == qtscript_QMdiArea_AreaOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QMdiArea_AreaOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QMdiArea_AreaOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QMdiArea::AreaOptions>() == otherObj.value<QMdiArea::AreaOptions>())));
}

static QScriptValue qtscript_create_QMdiArea_AreaOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QMdiArea_AreaOptions, qtscript_QMdiArea_AreaOptions_valueOf,
        qtscript_QMdiArea_AreaOptions_toString, qtscript_QMdiArea_AreaOptions_equals);
    qScriptRegisterMetaType<QMdiArea::AreaOptions>(engine, qtscript_QMdiArea_AreaOptions_toScriptValue,
        qtscript_QMdiArea_AreaOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QMdiArea
//

static QScriptValue qtscript_QMdiArea_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 7;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QMdiArea* _q_self = qscriptvalue_cast<QMdiArea*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMdiArea.%0(): this object is not a QMdiArea")
            .arg(qtscript_QMdiArea_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QMdiSubWindow* _q_result = _q_self->activeSubWindow();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QMdiSubWindow* _q_result = _q_self->addSubWindow(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QMdiSubWindow* _q_result = _q_self->addSubWindow(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QMdiSubWindow* _q_result = _q_self->currentSubWindow();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->removeSubWindow(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QMdiArea::AreaOption _q_arg0 = qscriptvalue_cast<QMdiArea::AreaOption>(context->argument(0));
        _q_self->setOption(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QMdiArea::AreaOption _q_arg0 = qscriptvalue_cast<QMdiArea::AreaOption>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QList<QMdiSubWindow*> _q_result = _q_self->subWindowList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QMdiArea::WindowOrder _q_arg0 = qscriptvalue_cast<QMdiArea::WindowOrder>(context->argument(0));
        QList<QMdiSubWindow*> _q_result = _q_self->subWindowList(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QMdiArea::AreaOption _q_arg0 = qscriptvalue_cast<QMdiArea::AreaOption>(context->argument(0));
        bool _q_result = _q_self->testOption(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7: {
    QString result = QString::fromLatin1("QMdiArea");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMdiArea_throw_ambiguity_error_helper(context,
        qtscript_QMdiArea_function_names[_id+1],
        qtscript_QMdiArea_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMdiArea_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMdiArea(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QMdiArea* _q_cpp_result = new QtScriptShell_QMdiArea();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMdiArea*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QMdiArea* _q_cpp_result = new QtScriptShell_QMdiArea(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMdiArea*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMdiArea_throw_ambiguity_error_helper(context,
        qtscript_QMdiArea_function_names[_id],
        qtscript_QMdiArea_function_signatures[_id]);
}

static QScriptValue qtscript_QMdiArea_toScriptValue(QScriptEngine *engine, QMdiArea* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QMdiArea_fromScriptValue(const QScriptValue &value, QMdiArea* &out)
{
    out = qobject_cast<QMdiArea*>(value.toQObject());
}

QScriptValue qtscript_create_QMdiArea_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMdiArea*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMdiArea*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractScrollArea*>()));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMdiArea_prototype_call, qtscript_QMdiArea_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMdiArea_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QMdiArea*>(engine, qtscript_QMdiArea_toScriptValue, 
        qtscript_QMdiArea_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMdiArea_static_call, proto, qtscript_QMdiArea_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("WindowOrder"),
        qtscript_create_QMdiArea_WindowOrder_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ViewMode"),
        qtscript_create_QMdiArea_ViewMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("AreaOption"),
        qtscript_create_QMdiArea_AreaOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("AreaOptions"),
        qtscript_create_QMdiArea_AreaOptions_class(engine));
    return ctor;
}
