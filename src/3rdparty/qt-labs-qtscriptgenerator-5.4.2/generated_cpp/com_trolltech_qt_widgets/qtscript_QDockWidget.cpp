#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdockwidget.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdockwidget.h>
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
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QDockWidget.h"

static const char * const qtscript_QDockWidget_function_names[] = {
    "QDockWidget"
    // static
    // prototype
    , "allowedAreas"
    , "isAreaAllowed"
    , "setAllowedAreas"
    , "setTitleBarWidget"
    , "setWidget"
    , "titleBarWidget"
    , "toggleViewAction"
    , "widget"
    , "toString"
};

static const char * const qtscript_QDockWidget_function_signatures[] = {
    "QWidget parent, WindowFlags flags\nString title, QWidget parent, WindowFlags flags"
    // static
    // prototype
    , ""
    , "DockWidgetArea area"
    , "DockWidgetAreas areas"
    , "QWidget widget"
    , "QWidget widget"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QDockWidget_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QDockWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDockWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDockWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QDockWidget*)
Q_DECLARE_METATYPE(QDockWidget::DockWidgetFeature)
Q_DECLARE_METATYPE(QFlags<QDockWidget::DockWidgetFeature>)
Q_DECLARE_METATYPE(QFlags<Qt::DockWidgetArea>)
Q_DECLARE_METATYPE(Qt::DockWidgetArea)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QAction*)
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
// QDockWidget::DockWidgetFeature
//

static const QDockWidget::DockWidgetFeature qtscript_QDockWidget_DockWidgetFeature_values[] = {
    QDockWidget::NoDockWidgetFeatures
    , QDockWidget::DockWidgetClosable
    , QDockWidget::DockWidgetMovable
    , QDockWidget::DockWidgetFloatable
    , QDockWidget::AllDockWidgetFeatures
    , QDockWidget::DockWidgetVerticalTitleBar
    , QDockWidget::DockWidgetFeatureMask
    , QDockWidget::Reserved
};

static const char * const qtscript_QDockWidget_DockWidgetFeature_keys[] = {
    "NoDockWidgetFeatures"
    , "DockWidgetClosable"
    , "DockWidgetMovable"
    , "DockWidgetFloatable"
    , "AllDockWidgetFeatures"
    , "DockWidgetVerticalTitleBar"
    , "DockWidgetFeatureMask"
    , "Reserved"
};

static QString qtscript_QDockWidget_DockWidgetFeature_toStringHelper(QDockWidget::DockWidgetFeature value)
{
    for (int i = 0; i < 8; ++i) {
        if (qtscript_QDockWidget_DockWidgetFeature_values[i] == value)
            return QString::fromLatin1(qtscript_QDockWidget_DockWidgetFeature_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QDockWidget_DockWidgetFeature_toScriptValue(QScriptEngine *engine, const QDockWidget::DockWidgetFeature &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDockWidget"));
    return clazz.property(qtscript_QDockWidget_DockWidgetFeature_toStringHelper(value));
}

static void qtscript_QDockWidget_DockWidgetFeature_fromScriptValue(const QScriptValue &value, QDockWidget::DockWidgetFeature &out)
{
    out = qvariant_cast<QDockWidget::DockWidgetFeature>(value.toVariant());
}

static QScriptValue qtscript_construct_QDockWidget_DockWidgetFeature(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 8; ++i) {
        if (qtscript_QDockWidget_DockWidgetFeature_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QDockWidget::DockWidgetFeature>(arg));
    }
    return context->throwError(QString::fromLatin1("DockWidgetFeature(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDockWidget_DockWidgetFeature_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDockWidget::DockWidgetFeature value = qscriptvalue_cast<QDockWidget::DockWidgetFeature>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDockWidget_DockWidgetFeature_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDockWidget::DockWidgetFeature value = qscriptvalue_cast<QDockWidget::DockWidgetFeature>(context->thisObject());
    return QScriptValue(engine, qtscript_QDockWidget_DockWidgetFeature_toStringHelper(value));
}

static QScriptValue qtscript_create_QDockWidget_DockWidgetFeature_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDockWidget_DockWidgetFeature,
        qtscript_QDockWidget_DockWidgetFeature_valueOf, qtscript_QDockWidget_DockWidgetFeature_toString);
    qScriptRegisterMetaType<QDockWidget::DockWidgetFeature>(engine, qtscript_QDockWidget_DockWidgetFeature_toScriptValue,
        qtscript_QDockWidget_DockWidgetFeature_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDockWidget_DockWidgetFeature_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDockWidget_DockWidgetFeature_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDockWidget::DockWidgetFeatures
//

static QScriptValue qtscript_QDockWidget_DockWidgetFeatures_toScriptValue(QScriptEngine *engine, const QDockWidget::DockWidgetFeatures &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QDockWidget_DockWidgetFeatures_fromScriptValue(const QScriptValue &value, QDockWidget::DockWidgetFeatures &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QDockWidget::DockWidgetFeatures>())
        out = qvariant_cast<QDockWidget::DockWidgetFeatures>(var);
    else if (var.userType() == qMetaTypeId<QDockWidget::DockWidgetFeature>())
        out = qvariant_cast<QDockWidget::DockWidgetFeature>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QDockWidget_DockWidgetFeatures(QScriptContext *context, QScriptEngine *engine)
{
    QDockWidget::DockWidgetFeatures result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QDockWidget::DockWidgetFeatures>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QDockWidget::DockWidgetFeature>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("DockWidgetFeatures(): argument %0 is not of type DockWidgetFeature").arg(i));
            }
            result |= qvariant_cast<QDockWidget::DockWidgetFeature>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QDockWidget_DockWidgetFeatures_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDockWidget::DockWidgetFeatures value = qscriptvalue_cast<QDockWidget::DockWidgetFeatures>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDockWidget_DockWidgetFeatures_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDockWidget::DockWidgetFeatures value = qscriptvalue_cast<QDockWidget::DockWidgetFeatures>(context->thisObject());
    QString result;
    for (int i = 0; i < 8; ++i) {
        if ((value & qtscript_QDockWidget_DockWidgetFeature_values[i]) == qtscript_QDockWidget_DockWidgetFeature_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QDockWidget_DockWidgetFeature_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QDockWidget_DockWidgetFeatures_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QDockWidget::DockWidgetFeatures>() == otherObj.value<QDockWidget::DockWidgetFeatures>())));
}

static QScriptValue qtscript_create_QDockWidget_DockWidgetFeatures_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QDockWidget_DockWidgetFeatures, qtscript_QDockWidget_DockWidgetFeatures_valueOf,
        qtscript_QDockWidget_DockWidgetFeatures_toString, qtscript_QDockWidget_DockWidgetFeatures_equals);
    qScriptRegisterMetaType<QDockWidget::DockWidgetFeatures>(engine, qtscript_QDockWidget_DockWidgetFeatures_toScriptValue,
        qtscript_QDockWidget_DockWidgetFeatures_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QDockWidget
//

static QScriptValue qtscript_QDockWidget_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 8;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDockWidget* _q_self = qscriptvalue_cast<QDockWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDockWidget.%0(): this object is not a QDockWidget")
            .arg(qtscript_QDockWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QFlags<Qt::DockWidgetArea> _q_result = _q_self->allowedAreas();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        Qt::DockWidgetArea _q_arg0 = qscriptvalue_cast<Qt::DockWidgetArea>(context->argument(0));
        bool _q_result = _q_self->isAreaAllowed(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QFlags<Qt::DockWidgetArea> _q_arg0 = qscriptvalue_cast<QFlags<Qt::DockWidgetArea> >(context->argument(0));
        _q_self->setAllowedAreas(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setTitleBarWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->titleBarWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->toggleViewAction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->widget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QDockWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDockWidget_throw_ambiguity_error_helper(context,
        qtscript_QDockWidget_function_names[_id+1],
        qtscript_QDockWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDockWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDockWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QDockWidget* _q_cpp_result = new QtScriptShell_QDockWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDockWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QDockWidget* _q_cpp_result = new QtScriptShell_QDockWidget(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDockWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QDockWidget* _q_cpp_result = new QtScriptShell_QDockWidget(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDockWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && (qMetaTypeId<QFlags<Qt::WindowType> >() == context->argument(1).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
            QtScriptShell_QDockWidget* _q_cpp_result = new QtScriptShell_QDockWidget(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDockWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QtScriptShell_QDockWidget* _q_cpp_result = new QtScriptShell_QDockWidget(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDockWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QFlags<Qt::WindowType> _q_arg2 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(2));
        QtScriptShell_QDockWidget* _q_cpp_result = new QtScriptShell_QDockWidget(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDockWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDockWidget_throw_ambiguity_error_helper(context,
        qtscript_QDockWidget_function_names[_id],
        qtscript_QDockWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QDockWidget_toScriptValue(QScriptEngine *engine, QDockWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QDockWidget_fromScriptValue(const QScriptValue &value, QDockWidget* &out)
{
    out = qobject_cast<QDockWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QDockWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDockWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDockWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDockWidget_prototype_call, qtscript_QDockWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDockWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QDockWidget*>(engine, qtscript_QDockWidget_toScriptValue, 
        qtscript_QDockWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDockWidget_static_call, proto, qtscript_QDockWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("DockWidgetFeature"),
        qtscript_create_QDockWidget_DockWidgetFeature_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("DockWidgetFeatures"),
        qtscript_create_QDockWidget_DockWidgetFeatures_class(engine));
    return ctor;
}
