#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtoolbutton.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbuttongroup.h>
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
#include <qstyleoption.h>
#include <qtoolbutton.h>
#include <qwidget.h>

#include "qtscriptshell_QToolButton.h"

static const char * const qtscript_QToolButton_function_names[] = {
    "QToolButton"
    // static
    // prototype
    , "defaultAction"
    , "menu"
    , "minimumSizeHint"
    , "setMenu"
    , "sizeHint"
    , "toString"
};

static const char * const qtscript_QToolButton_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "QMenu menu"
    , ""
""
};

static const int qtscript_QToolButton_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QToolButton_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QToolButton::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QToolButton_metaObject()
{
    return &QToolButton::staticMetaObject;
}

Q_DECLARE_METATYPE(QToolButton*)
Q_DECLARE_METATYPE(QtScriptShell_QToolButton*)
Q_DECLARE_METATYPE(QToolButton::ToolButtonPopupMode)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QAbstractButton*)

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
// QToolButton::ToolButtonPopupMode
//

static const QToolButton::ToolButtonPopupMode qtscript_QToolButton_ToolButtonPopupMode_values[] = {
    QToolButton::DelayedPopup
    , QToolButton::MenuButtonPopup
    , QToolButton::InstantPopup
};

static const char * const qtscript_QToolButton_ToolButtonPopupMode_keys[] = {
    "DelayedPopup"
    , "MenuButtonPopup"
    , "InstantPopup"
};

static QString qtscript_QToolButton_ToolButtonPopupMode_toStringHelper(QToolButton::ToolButtonPopupMode value)
{
    const QMetaObject *meta = qtscript_QToolButton_metaObject();
    int idx = meta->indexOfEnumerator("ToolButtonPopupMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QToolButton_ToolButtonPopupMode_toScriptValue(QScriptEngine *engine, const QToolButton::ToolButtonPopupMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QToolButton"));
    return clazz.property(qtscript_QToolButton_ToolButtonPopupMode_toStringHelper(value));
}

static void qtscript_QToolButton_ToolButtonPopupMode_fromScriptValue(const QScriptValue &value, QToolButton::ToolButtonPopupMode &out)
{
    out = qvariant_cast<QToolButton::ToolButtonPopupMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QToolButton_ToolButtonPopupMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QToolButton_metaObject();
    int idx = meta->indexOfEnumerator("ToolButtonPopupMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QToolButton::ToolButtonPopupMode>(arg));
    return context->throwError(QString::fromLatin1("ToolButtonPopupMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QToolButton_ToolButtonPopupMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QToolButton::ToolButtonPopupMode value = qscriptvalue_cast<QToolButton::ToolButtonPopupMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QToolButton_ToolButtonPopupMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QToolButton::ToolButtonPopupMode value = qscriptvalue_cast<QToolButton::ToolButtonPopupMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QToolButton_ToolButtonPopupMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QToolButton_ToolButtonPopupMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QToolButton_ToolButtonPopupMode,
        qtscript_QToolButton_ToolButtonPopupMode_valueOf, qtscript_QToolButton_ToolButtonPopupMode_toString);
    qScriptRegisterMetaType<QToolButton::ToolButtonPopupMode>(engine, qtscript_QToolButton_ToolButtonPopupMode_toScriptValue,
        qtscript_QToolButton_ToolButtonPopupMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QToolButton_ToolButtonPopupMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QToolButton_ToolButtonPopupMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QToolButton
//

static QScriptValue qtscript_QToolButton_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QToolButton* _q_self = qscriptvalue_cast<QToolButton*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QToolButton.%0(): this object is not a QToolButton")
            .arg(qtscript_QToolButton_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->defaultAction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QMenu* _q_result = _q_self->menu();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QMenu* _q_arg0 = qscriptvalue_cast<QMenu*>(context->argument(0));
        _q_self->setMenu(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QToolButton");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QToolButton_throw_ambiguity_error_helper(context,
        qtscript_QToolButton_function_names[_id+1],
        qtscript_QToolButton_function_signatures[_id+1]);
}

static QScriptValue qtscript_QToolButton_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QToolButton(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QToolButton* _q_cpp_result = new QtScriptShell_QToolButton();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QToolButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QToolButton* _q_cpp_result = new QtScriptShell_QToolButton(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QToolButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QToolButton_throw_ambiguity_error_helper(context,
        qtscript_QToolButton_function_names[_id],
        qtscript_QToolButton_function_signatures[_id]);
}

static QScriptValue qtscript_QToolButton_toScriptValue(QScriptEngine *engine, QToolButton* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QToolButton_fromScriptValue(const QScriptValue &value, QToolButton* &out)
{
    out = qobject_cast<QToolButton*>(value.toQObject());
}

QScriptValue qtscript_create_QToolButton_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QToolButton*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QToolButton*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractButton*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QToolButton_prototype_call, qtscript_QToolButton_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QToolButton_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QToolButton*>(engine, qtscript_QToolButton_toScriptValue, 
        qtscript_QToolButton_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QToolButton_static_call, proto, qtscript_QToolButton_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ToolButtonPopupMode"),
        qtscript_create_QToolButton_ToolButtonPopupMode_class(engine, ctor));
    return ctor;
}
