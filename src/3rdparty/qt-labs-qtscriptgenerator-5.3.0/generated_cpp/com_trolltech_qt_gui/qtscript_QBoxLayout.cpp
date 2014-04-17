#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qboxlayout.h>
#include <QVariant>
#include <qboxlayout.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qlist.h>
#include <qmargins.h>
#include <qobject.h>
#include <qrect.h>
#include <qsize.h>
#include <qwidget.h>

#include "qtscriptshell_QBoxLayout.h"

static const char * const qtscript_QBoxLayout_function_names[] = {
    "QBoxLayout"
    // static
    // prototype
    , "addLayout"
    , "addSpacerItem"
    , "addSpacing"
    , "addStretch"
    , "addStrut"
    , "addWidget"
    , "direction"
    , "insertItem"
    , "insertLayout"
    , "insertSpacerItem"
    , "insertSpacing"
    , "insertStretch"
    , "insertWidget"
    , "setDirection"
    , "setSpacing"
    , "setStretch"
    , "setStretchFactor"
    , "spacing"
    , "stretch"
    , "toString"
};

static const char * const qtscript_QBoxLayout_function_signatures[] = {
    "Direction arg__1, QWidget parent"
    // static
    // prototype
    , "QLayout layout, int stretch"
    , "QSpacerItem spacerItem"
    , "int size"
    , "int stretch"
    , "int arg__1"
    , "QWidget arg__1, int stretch, Alignment alignment"
    , ""
    , "int index, QLayoutItem arg__2"
    , "int index, QLayout layout, int stretch"
    , "int index, QSpacerItem spacerItem"
    , "int index, int size"
    , "int index, int stretch"
    , "int index, QWidget widget, int stretch, Alignment alignment"
    , "Direction arg__1"
    , "int spacing"
    , "int index, int stretch"
    , "QLayout l, int stretch\nQWidget w, int stretch"
    , ""
    , "int index"
""
};

static const int qtscript_QBoxLayout_function_lengths[] = {
    2
    // static
    // prototype
    , 2
    , 1
    , 1
    , 1
    , 1
    , 3
    , 0
    , 2
    , 3
    , 2
    , 2
    , 2
    , 4
    , 1
    , 1
    , 2
    , 2
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QBoxLayout_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QBoxLayout::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QBoxLayout*)
Q_DECLARE_METATYPE(QtScriptShell_QBoxLayout*)
Q_DECLARE_METATYPE(QBoxLayout::Direction)
Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(QSpacerItem*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QFlags<Qt::AlignmentFlag>)
Q_DECLARE_METATYPE(QLayoutItem*)

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
// QBoxLayout::Direction
//

static const QBoxLayout::Direction qtscript_QBoxLayout_Direction_values[] = {
    QBoxLayout::LeftToRight
    , QBoxLayout::RightToLeft
    , QBoxLayout::TopToBottom
    , QBoxLayout::BottomToTop
};

static const char * const qtscript_QBoxLayout_Direction_keys[] = {
    "LeftToRight"
    , "RightToLeft"
    , "TopToBottom"
    , "BottomToTop"
};

static QString qtscript_QBoxLayout_Direction_toStringHelper(QBoxLayout::Direction value)
{
    if ((value >= QBoxLayout::LeftToRight) && (value <= QBoxLayout::BottomToTop))
        return qtscript_QBoxLayout_Direction_keys[static_cast<int>(value)-static_cast<int>(QBoxLayout::LeftToRight)];
    return QString();
}

static QScriptValue qtscript_QBoxLayout_Direction_toScriptValue(QScriptEngine *engine, const QBoxLayout::Direction &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QBoxLayout"));
    return clazz.property(qtscript_QBoxLayout_Direction_toStringHelper(value));
}

static void qtscript_QBoxLayout_Direction_fromScriptValue(const QScriptValue &value, QBoxLayout::Direction &out)
{
    out = qvariant_cast<QBoxLayout::Direction>(value.toVariant());
}

static QScriptValue qtscript_construct_QBoxLayout_Direction(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QBoxLayout::LeftToRight) && (arg <= QBoxLayout::BottomToTop))
        return qScriptValueFromValue(engine,  static_cast<QBoxLayout::Direction>(arg));
    return context->throwError(QString::fromLatin1("Direction(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QBoxLayout_Direction_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QBoxLayout::Direction value = qscriptvalue_cast<QBoxLayout::Direction>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QBoxLayout_Direction_toString(QScriptContext *context, QScriptEngine *engine)
{
    QBoxLayout::Direction value = qscriptvalue_cast<QBoxLayout::Direction>(context->thisObject());
    return QScriptValue(engine, qtscript_QBoxLayout_Direction_toStringHelper(value));
}

static QScriptValue qtscript_create_QBoxLayout_Direction_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QBoxLayout_Direction,
        qtscript_QBoxLayout_Direction_valueOf, qtscript_QBoxLayout_Direction_toString);
    qScriptRegisterMetaType<QBoxLayout::Direction>(engine, qtscript_QBoxLayout_Direction_toScriptValue,
        qtscript_QBoxLayout_Direction_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QBoxLayout_Direction_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QBoxLayout_Direction_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QBoxLayout
//

static QScriptValue qtscript_QBoxLayout_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 19;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QBoxLayout* _q_self = qscriptvalue_cast<QBoxLayout*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QBoxLayout.%0(): this object is not a QBoxLayout")
            .arg(qtscript_QBoxLayout_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
        _q_self->addLayout(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->addLayout(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QSpacerItem* _q_arg0 = qscriptvalue_cast<QSpacerItem*>(context->argument(0));
        _q_self->addSpacerItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->addSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->addStretch();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->addStretch(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->addStrut(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg2 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(2));
        _q_self->addWidget(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QBoxLayout::Direction _q_result = _q_self->direction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QLayoutItem* _q_arg1 = qscriptvalue_cast<QLayoutItem*>(context->argument(1));
        _q_self->insertItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QLayout* _q_arg1 = qscriptvalue_cast<QLayout*>(context->argument(1));
        _q_self->insertLayout(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QLayout* _q_arg1 = qscriptvalue_cast<QLayout*>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->insertLayout(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QSpacerItem* _q_arg1 = qscriptvalue_cast<QSpacerItem*>(context->argument(1));
        _q_self->insertSpacerItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->insertSpacing(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->insertStretch(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->insertStretch(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        _q_self->insertWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->insertWidget(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg3 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(3));
        _q_self->insertWidget(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QBoxLayout::Direction _q_arg0 = qscriptvalue_cast<QBoxLayout::Direction>(context->argument(0));
        _q_self->setDirection(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setStretch(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QLayout*>(context->argument(0))
            && context->argument(1).isNumber()) {
            QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            bool _q_result = _q_self->setStretchFactor(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && context->argument(1).isNumber()) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            bool _q_result = _q_self->setStretchFactor(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->spacing();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->stretch(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19: {
    QString result = QString::fromLatin1("QBoxLayout");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QBoxLayout_throw_ambiguity_error_helper(context,
        qtscript_QBoxLayout_function_names[_id+1],
        qtscript_QBoxLayout_function_signatures[_id+1]);
}

static QScriptValue qtscript_QBoxLayout_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QBoxLayout(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QBoxLayout::Direction _q_arg0 = qscriptvalue_cast<QBoxLayout::Direction>(context->argument(0));
        QtScriptShell_QBoxLayout* _q_cpp_result = new QtScriptShell_QBoxLayout(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QBoxLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QBoxLayout::Direction _q_arg0 = qscriptvalue_cast<QBoxLayout::Direction>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QBoxLayout* _q_cpp_result = new QtScriptShell_QBoxLayout(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QBoxLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QBoxLayout_throw_ambiguity_error_helper(context,
        qtscript_QBoxLayout_function_names[_id],
        qtscript_QBoxLayout_function_signatures[_id]);
}

static QScriptValue qtscript_QBoxLayout_toScriptValue(QScriptEngine *engine, QBoxLayout* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QBoxLayout_fromScriptValue(const QScriptValue &value, QBoxLayout* &out)
{
    out = qobject_cast<QBoxLayout*>(value.toQObject());
}

QScriptValue qtscript_create_QBoxLayout_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QBoxLayout*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QBoxLayout*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QLayout*>()));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QBoxLayout_prototype_call, qtscript_QBoxLayout_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QBoxLayout_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QBoxLayout*>(engine, qtscript_QBoxLayout_toScriptValue, 
        qtscript_QBoxLayout_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QBoxLayout_static_call, proto, qtscript_QBoxLayout_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Direction"),
        qtscript_create_QBoxLayout_Direction_class(engine, ctor));
    return ctor;
}
