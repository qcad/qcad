#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qprintpreviewwidget.h>
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
#include <qprinter.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QPrintPreviewWidget.h"

static const char * const qtscript_QPrintPreviewWidget_function_names[] = {
    "QPrintPreviewWidget"
    // static
    // prototype
    , "currentPage"
    , "orientation"
    , "pageCount"
    , "setVisible"
    , "viewMode"
    , "zoomFactor"
    , "zoomMode"
    , "toString"
};

static const char * const qtscript_QPrintPreviewWidget_function_signatures[] = {
    "QPrinter printer, QWidget parent, WindowFlags flags\nQWidget parent, WindowFlags flags"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "bool visible"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QPrintPreviewWidget_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QPrintPreviewWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPrintPreviewWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPrintPreviewWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QPrintPreviewWidget*)
Q_DECLARE_METATYPE(QPrintPreviewWidget::ZoomMode)
Q_DECLARE_METATYPE(QPrintPreviewWidget::ViewMode)
Q_DECLARE_METATYPE(QPrinter::Orientation)
Q_DECLARE_METATYPE(QPrinter*)
Q_DECLARE_METATYPE(QWidget*)
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

//
// QPrintPreviewWidget::ZoomMode
//

static const QPrintPreviewWidget::ZoomMode qtscript_QPrintPreviewWidget_ZoomMode_values[] = {
    QPrintPreviewWidget::CustomZoom
    , QPrintPreviewWidget::FitToWidth
    , QPrintPreviewWidget::FitInView
};

static const char * const qtscript_QPrintPreviewWidget_ZoomMode_keys[] = {
    "CustomZoom"
    , "FitToWidth"
    , "FitInView"
};

static QString qtscript_QPrintPreviewWidget_ZoomMode_toStringHelper(QPrintPreviewWidget::ZoomMode value)
{
    if ((value >= QPrintPreviewWidget::CustomZoom) && (value <= QPrintPreviewWidget::FitInView))
        return qtscript_QPrintPreviewWidget_ZoomMode_keys[static_cast<int>(value)-static_cast<int>(QPrintPreviewWidget::CustomZoom)];
    return QString();
}

static QScriptValue qtscript_QPrintPreviewWidget_ZoomMode_toScriptValue(QScriptEngine *engine, const QPrintPreviewWidget::ZoomMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrintPreviewWidget"));
    return clazz.property(qtscript_QPrintPreviewWidget_ZoomMode_toStringHelper(value));
}

static void qtscript_QPrintPreviewWidget_ZoomMode_fromScriptValue(const QScriptValue &value, QPrintPreviewWidget::ZoomMode &out)
{
    out = qvariant_cast<QPrintPreviewWidget::ZoomMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrintPreviewWidget_ZoomMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPrintPreviewWidget::CustomZoom) && (arg <= QPrintPreviewWidget::FitInView))
        return qScriptValueFromValue(engine,  static_cast<QPrintPreviewWidget::ZoomMode>(arg));
    return context->throwError(QString::fromLatin1("ZoomMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrintPreviewWidget_ZoomMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrintPreviewWidget::ZoomMode value = qscriptvalue_cast<QPrintPreviewWidget::ZoomMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrintPreviewWidget_ZoomMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrintPreviewWidget::ZoomMode value = qscriptvalue_cast<QPrintPreviewWidget::ZoomMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrintPreviewWidget_ZoomMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrintPreviewWidget_ZoomMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrintPreviewWidget_ZoomMode,
        qtscript_QPrintPreviewWidget_ZoomMode_valueOf, qtscript_QPrintPreviewWidget_ZoomMode_toString);
    qScriptRegisterMetaType<QPrintPreviewWidget::ZoomMode>(engine, qtscript_QPrintPreviewWidget_ZoomMode_toScriptValue,
        qtscript_QPrintPreviewWidget_ZoomMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrintPreviewWidget_ZoomMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrintPreviewWidget_ZoomMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrintPreviewWidget::ViewMode
//

static const QPrintPreviewWidget::ViewMode qtscript_QPrintPreviewWidget_ViewMode_values[] = {
    QPrintPreviewWidget::SinglePageView
    , QPrintPreviewWidget::FacingPagesView
    , QPrintPreviewWidget::AllPagesView
};

static const char * const qtscript_QPrintPreviewWidget_ViewMode_keys[] = {
    "SinglePageView"
    , "FacingPagesView"
    , "AllPagesView"
};

static QString qtscript_QPrintPreviewWidget_ViewMode_toStringHelper(QPrintPreviewWidget::ViewMode value)
{
    if ((value >= QPrintPreviewWidget::SinglePageView) && (value <= QPrintPreviewWidget::AllPagesView))
        return qtscript_QPrintPreviewWidget_ViewMode_keys[static_cast<int>(value)-static_cast<int>(QPrintPreviewWidget::SinglePageView)];
    return QString();
}

static QScriptValue qtscript_QPrintPreviewWidget_ViewMode_toScriptValue(QScriptEngine *engine, const QPrintPreviewWidget::ViewMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrintPreviewWidget"));
    return clazz.property(qtscript_QPrintPreviewWidget_ViewMode_toStringHelper(value));
}

static void qtscript_QPrintPreviewWidget_ViewMode_fromScriptValue(const QScriptValue &value, QPrintPreviewWidget::ViewMode &out)
{
    out = qvariant_cast<QPrintPreviewWidget::ViewMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrintPreviewWidget_ViewMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QPrintPreviewWidget::SinglePageView) && (arg <= QPrintPreviewWidget::AllPagesView))
        return qScriptValueFromValue(engine,  static_cast<QPrintPreviewWidget::ViewMode>(arg));
    return context->throwError(QString::fromLatin1("ViewMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrintPreviewWidget_ViewMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrintPreviewWidget::ViewMode value = qscriptvalue_cast<QPrintPreviewWidget::ViewMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrintPreviewWidget_ViewMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrintPreviewWidget::ViewMode value = qscriptvalue_cast<QPrintPreviewWidget::ViewMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrintPreviewWidget_ViewMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrintPreviewWidget_ViewMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrintPreviewWidget_ViewMode,
        qtscript_QPrintPreviewWidget_ViewMode_valueOf, qtscript_QPrintPreviewWidget_ViewMode_toString);
    qScriptRegisterMetaType<QPrintPreviewWidget::ViewMode>(engine, qtscript_QPrintPreviewWidget_ViewMode_toScriptValue,
        qtscript_QPrintPreviewWidget_ViewMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrintPreviewWidget_ViewMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrintPreviewWidget_ViewMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrintPreviewWidget
//

static QScriptValue qtscript_QPrintPreviewWidget_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QPrintPreviewWidget* _q_self = qscriptvalue_cast<QPrintPreviewWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPrintPreviewWidget.%0(): this object is not a QPrintPreviewWidget")
            .arg(qtscript_QPrintPreviewWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPrinter::Orientation _q_result = _q_self->orientation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->pageCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setVisible(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QPrintPreviewWidget::ViewMode _q_result = _q_self->viewMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->zoomFactor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QPrintPreviewWidget::ZoomMode _q_result = _q_self->zoomMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7: {
    QString result = QString::fromLatin1("QPrintPreviewWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPrintPreviewWidget_throw_ambiguity_error_helper(context,
        qtscript_QPrintPreviewWidget_function_names[_id+1],
        qtscript_QPrintPreviewWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPrintPreviewWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPrintPreviewWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPrintPreviewWidget* _q_cpp_result = new QtScriptShell_QPrintPreviewWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPrintPreviewWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QPrinter*>(context->argument(0))) {
            QPrinter* _q_arg0 = qscriptvalue_cast<QPrinter*>(context->argument(0));
            QtScriptShell_QPrintPreviewWidget* _q_cpp_result = new QtScriptShell_QPrintPreviewWidget(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPrintPreviewWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QPrintPreviewWidget* _q_cpp_result = new QtScriptShell_QPrintPreviewWidget(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPrintPreviewWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QPrinter*>(context->argument(0))
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QPrinter* _q_arg0 = qscriptvalue_cast<QPrinter*>(context->argument(0));
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QtScriptShell_QPrintPreviewWidget* _q_cpp_result = new QtScriptShell_QPrintPreviewWidget(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPrintPreviewWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && (qMetaTypeId<QFlags<Qt::WindowType> >() == context->argument(1).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
            QtScriptShell_QPrintPreviewWidget* _q_cpp_result = new QtScriptShell_QPrintPreviewWidget(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPrintPreviewWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QPrinter* _q_arg0 = qscriptvalue_cast<QPrinter*>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QFlags<Qt::WindowType> _q_arg2 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(2));
        QtScriptShell_QPrintPreviewWidget* _q_cpp_result = new QtScriptShell_QPrintPreviewWidget(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPrintPreviewWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPrintPreviewWidget_throw_ambiguity_error_helper(context,
        qtscript_QPrintPreviewWidget_function_names[_id],
        qtscript_QPrintPreviewWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QPrintPreviewWidget_toScriptValue(QScriptEngine *engine, QPrintPreviewWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QPrintPreviewWidget_fromScriptValue(const QScriptValue &value, QPrintPreviewWidget* &out)
{
    out = qobject_cast<QPrintPreviewWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QPrintPreviewWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPrintPreviewWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPrintPreviewWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPrintPreviewWidget_prototype_call, qtscript_QPrintPreviewWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPrintPreviewWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QPrintPreviewWidget*>(engine, qtscript_QPrintPreviewWidget_toScriptValue, 
        qtscript_QPrintPreviewWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPrintPreviewWidget_static_call, proto, qtscript_QPrintPreviewWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ZoomMode"),
        qtscript_create_QPrintPreviewWidget_ZoomMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ViewMode"),
        qtscript_create_QPrintPreviewWidget_ViewMode_class(engine, ctor));
    return ctor;
}
