#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qmdisubwindow.h>
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
#include <qmdiarea.h>
#include <qmdisubwindow.h>
#include <qmenu.h>
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
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QMdiSubWindow.h"

static const char * const qtscript_QMdiSubWindow_function_names[] = {
    "QMdiSubWindow"
    // static
    // prototype
    , "isShaded"
    , "maximizedButtonsWidget"
    , "maximizedSystemMenuIconWidget"
    , "mdiArea"
    , "minimumSizeHint"
    , "setOption"
    , "setSystemMenu"
    , "setWidget"
    , "sizeHint"
    , "systemMenu"
    , "testOption"
    , "widget"
    , "toString"
};

static const char * const qtscript_QMdiSubWindow_function_signatures[] = {
    "QWidget parent, WindowFlags flags"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "SubWindowOption option, bool on"
    , "QMenu systemMenu"
    , "QWidget widget"
    , ""
    , ""
    , "SubWindowOption arg__1"
    , ""
""
};

static const int qtscript_QMdiSubWindow_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 1
    , 1
    , 0
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QMdiSubWindow_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMdiSubWindow::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMdiSubWindow*)
Q_DECLARE_METATYPE(QtScriptShell_QMdiSubWindow*)
Q_DECLARE_METATYPE(QMdiSubWindow::SubWindowOption)
Q_DECLARE_METATYPE(QFlags<QMdiSubWindow::SubWindowOption>)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QMdiArea*)
Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)

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
// QMdiSubWindow::SubWindowOption
//

static const QMdiSubWindow::SubWindowOption qtscript_QMdiSubWindow_SubWindowOption_values[] = {
    QMdiSubWindow::AllowOutsideAreaHorizontally
    , QMdiSubWindow::AllowOutsideAreaVertically
    , QMdiSubWindow::RubberBandResize
    , QMdiSubWindow::RubberBandMove
};

static const char * const qtscript_QMdiSubWindow_SubWindowOption_keys[] = {
    "AllowOutsideAreaHorizontally"
    , "AllowOutsideAreaVertically"
    , "RubberBandResize"
    , "RubberBandMove"
};

static QString qtscript_QMdiSubWindow_SubWindowOption_toStringHelper(QMdiSubWindow::SubWindowOption value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QMdiSubWindow_SubWindowOption_values[i] == value)
            return QString::fromLatin1(qtscript_QMdiSubWindow_SubWindowOption_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QMdiSubWindow_SubWindowOption_toScriptValue(QScriptEngine *engine, const QMdiSubWindow::SubWindowOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QMdiSubWindow"));
    return clazz.property(qtscript_QMdiSubWindow_SubWindowOption_toStringHelper(value));
}

static void qtscript_QMdiSubWindow_SubWindowOption_fromScriptValue(const QScriptValue &value, QMdiSubWindow::SubWindowOption &out)
{
    out = qvariant_cast<QMdiSubWindow::SubWindowOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QMdiSubWindow_SubWindowOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QMdiSubWindow_SubWindowOption_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QMdiSubWindow::SubWindowOption>(arg));
    }
    return context->throwError(QString::fromLatin1("SubWindowOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QMdiSubWindow_SubWindowOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMdiSubWindow::SubWindowOption value = qscriptvalue_cast<QMdiSubWindow::SubWindowOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMdiSubWindow_SubWindowOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMdiSubWindow::SubWindowOption value = qscriptvalue_cast<QMdiSubWindow::SubWindowOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QMdiSubWindow_SubWindowOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QMdiSubWindow_SubWindowOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QMdiSubWindow_SubWindowOption,
        qtscript_QMdiSubWindow_SubWindowOption_valueOf, qtscript_QMdiSubWindow_SubWindowOption_toString);
    qScriptRegisterMetaType<QMdiSubWindow::SubWindowOption>(engine, qtscript_QMdiSubWindow_SubWindowOption_toScriptValue,
        qtscript_QMdiSubWindow_SubWindowOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QMdiSubWindow_SubWindowOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QMdiSubWindow_SubWindowOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QMdiSubWindow::SubWindowOptions
//

static QScriptValue qtscript_QMdiSubWindow_SubWindowOptions_toScriptValue(QScriptEngine *engine, const QMdiSubWindow::SubWindowOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QMdiSubWindow_SubWindowOptions_fromScriptValue(const QScriptValue &value, QMdiSubWindow::SubWindowOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QMdiSubWindow::SubWindowOptions>())
        out = qvariant_cast<QMdiSubWindow::SubWindowOptions>(var);
    else if (var.userType() == qMetaTypeId<QMdiSubWindow::SubWindowOption>())
        out = qvariant_cast<QMdiSubWindow::SubWindowOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QMdiSubWindow_SubWindowOptions(QScriptContext *context, QScriptEngine *engine)
{
    QMdiSubWindow::SubWindowOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QMdiSubWindow::SubWindowOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QMdiSubWindow::SubWindowOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("SubWindowOptions(): argument %0 is not of type SubWindowOption").arg(i));
            }
            result |= qvariant_cast<QMdiSubWindow::SubWindowOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QMdiSubWindow_SubWindowOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMdiSubWindow::SubWindowOptions value = qscriptvalue_cast<QMdiSubWindow::SubWindowOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMdiSubWindow_SubWindowOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMdiSubWindow::SubWindowOptions value = qscriptvalue_cast<QMdiSubWindow::SubWindowOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 4; ++i) {
        if ((value & qtscript_QMdiSubWindow_SubWindowOption_values[i]) == qtscript_QMdiSubWindow_SubWindowOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QMdiSubWindow_SubWindowOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QMdiSubWindow_SubWindowOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QMdiSubWindow::SubWindowOptions>() == otherObj.value<QMdiSubWindow::SubWindowOptions>())));
}

static QScriptValue qtscript_create_QMdiSubWindow_SubWindowOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QMdiSubWindow_SubWindowOptions, qtscript_QMdiSubWindow_SubWindowOptions_valueOf,
        qtscript_QMdiSubWindow_SubWindowOptions_toString, qtscript_QMdiSubWindow_SubWindowOptions_equals);
    qScriptRegisterMetaType<QMdiSubWindow::SubWindowOptions>(engine, qtscript_QMdiSubWindow_SubWindowOptions_toScriptValue,
        qtscript_QMdiSubWindow_SubWindowOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QMdiSubWindow
//

static QScriptValue qtscript_QMdiSubWindow_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 12;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QMdiSubWindow* _q_self = qscriptvalue_cast<QMdiSubWindow*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMdiSubWindow.%0(): this object is not a QMdiSubWindow")
            .arg(qtscript_QMdiSubWindow_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isShaded();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->maximizedButtonsWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->maximizedSystemMenuIconWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QMdiArea* _q_result = _q_self->mdiArea();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QMdiSubWindow::SubWindowOption _q_arg0 = qscriptvalue_cast<QMdiSubWindow::SubWindowOption>(context->argument(0));
        _q_self->setOption(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QMdiSubWindow::SubWindowOption _q_arg0 = qscriptvalue_cast<QMdiSubWindow::SubWindowOption>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QMenu* _q_arg0 = qscriptvalue_cast<QMenu*>(context->argument(0));
        _q_self->setSystemMenu(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QMenu* _q_result = _q_self->systemMenu();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QMdiSubWindow::SubWindowOption _q_arg0 = qscriptvalue_cast<QMdiSubWindow::SubWindowOption>(context->argument(0));
        bool _q_result = _q_self->testOption(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->widget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12: {
    QString result = QString::fromLatin1("QMdiSubWindow");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMdiSubWindow_throw_ambiguity_error_helper(context,
        qtscript_QMdiSubWindow_function_names[_id+1],
        qtscript_QMdiSubWindow_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMdiSubWindow_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMdiSubWindow(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QMdiSubWindow* _q_cpp_result = new QtScriptShell_QMdiSubWindow();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMdiSubWindow*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QMdiSubWindow* _q_cpp_result = new QtScriptShell_QMdiSubWindow(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMdiSubWindow*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QtScriptShell_QMdiSubWindow* _q_cpp_result = new QtScriptShell_QMdiSubWindow(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMdiSubWindow*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMdiSubWindow_throw_ambiguity_error_helper(context,
        qtscript_QMdiSubWindow_function_names[_id],
        qtscript_QMdiSubWindow_function_signatures[_id]);
}

static QScriptValue qtscript_QMdiSubWindow_toScriptValue(QScriptEngine *engine, QMdiSubWindow* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QMdiSubWindow_fromScriptValue(const QScriptValue &value, QMdiSubWindow* &out)
{
    out = qobject_cast<QMdiSubWindow*>(value.toQObject());
}

QScriptValue qtscript_create_QMdiSubWindow_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMdiSubWindow*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMdiSubWindow*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 13; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMdiSubWindow_prototype_call, qtscript_QMdiSubWindow_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMdiSubWindow_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QMdiSubWindow*>(engine, qtscript_QMdiSubWindow_toScriptValue, 
        qtscript_QMdiSubWindow_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMdiSubWindow_static_call, proto, qtscript_QMdiSubWindow_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("SubWindowOption"),
        qtscript_create_QMdiSubWindow_SubWindowOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SubWindowOptions"),
        qtscript_create_QMdiSubWindow_SubWindowOptions_class(engine));
    return ctor;
}
