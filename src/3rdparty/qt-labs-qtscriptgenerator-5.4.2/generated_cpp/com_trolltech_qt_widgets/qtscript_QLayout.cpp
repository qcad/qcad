#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qlayout.h>
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
#include <qwidget.h>

#include "qtscriptshell_QLayout.h"

static const char * const qtscript_QLayout_function_names[] = {
    "QLayout"
    // static
    , "closestAcceptableSize"
    // prototype
    , "activate"
    , "addItem"
    , "addWidget"
    , "contentsMargins"
    , "contentsRect"
    , "count"
    , "getContentsMargins"
    , "indexOf"
    , "isEnabled"
    , "itemAt"
    , "menuBar"
    , "parentWidget"
    , "removeItem"
    , "removeWidget"
    , "setAlignment"
    , "setContentsMargins"
    , "setEnabled"
    , "setMenuBar"
    , "takeAt"
    , "totalHeightForWidth"
    , "totalMaximumSize"
    , "totalMinimumSize"
    , "totalSizeHint"
    , "update"
    , "toString"
};

static const char * const qtscript_QLayout_function_signatures[] = {
    "\nQWidget parent"
    // static
    , "QWidget w, QSize s"
    // prototype
    , ""
    , "QLayoutItem arg__1"
    , "QWidget w"
    , ""
    , ""
    , ""
    , "int left, int top, int right, int bottom"
    , "QWidget arg__1"
    , ""
    , "int index"
    , ""
    , ""
    , "QLayoutItem arg__1"
    , "QWidget w"
    , "QLayout l, Alignment alignment\nQWidget w, Alignment alignment"
    , "QMargins margins\nint left, int top, int right, int bottom"
    , "bool arg__1"
    , "QWidget w"
    , "int index"
    , "int w"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QLayout_function_lengths[] = {
    1
    // static
    , 2
    // prototype
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
    , 4
    , 1
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 2
    , 4
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QLayout_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QLayout::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QLayout_metaObject()
{
    return &QLayout::staticMetaObject;
}

Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(QtScriptShell_QLayout*)
Q_DECLARE_METATYPE(QLayout::SizeConstraint)
Q_DECLARE_METATYPE(QLayoutItem*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QMargins)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(QFlags<Qt::AlignmentFlag>)
Q_DECLARE_METATYPE(const QWidget*)

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
// QLayout::SizeConstraint
//

static const QLayout::SizeConstraint qtscript_QLayout_SizeConstraint_values[] = {
    QLayout::SetDefaultConstraint
    , QLayout::SetNoConstraint
    , QLayout::SetMinimumSize
    , QLayout::SetFixedSize
    , QLayout::SetMaximumSize
    , QLayout::SetMinAndMaxSize
};

static const char * const qtscript_QLayout_SizeConstraint_keys[] = {
    "SetDefaultConstraint"
    , "SetNoConstraint"
    , "SetMinimumSize"
    , "SetFixedSize"
    , "SetMaximumSize"
    , "SetMinAndMaxSize"
};

static QString qtscript_QLayout_SizeConstraint_toStringHelper(QLayout::SizeConstraint value)
{
    const QMetaObject *meta = qtscript_QLayout_metaObject();
    int idx = meta->indexOfEnumerator("SizeConstraint");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QLayout_SizeConstraint_toScriptValue(QScriptEngine *engine, const QLayout::SizeConstraint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLayout"));
    return clazz.property(qtscript_QLayout_SizeConstraint_toStringHelper(value));
}

static void qtscript_QLayout_SizeConstraint_fromScriptValue(const QScriptValue &value, QLayout::SizeConstraint &out)
{
    out = qvariant_cast<QLayout::SizeConstraint>(value.toVariant());
}

static QScriptValue qtscript_construct_QLayout_SizeConstraint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QLayout_metaObject();
    int idx = meta->indexOfEnumerator("SizeConstraint");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QLayout::SizeConstraint>(arg));
    return context->throwError(QString::fromLatin1("SizeConstraint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLayout_SizeConstraint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLayout::SizeConstraint value = qscriptvalue_cast<QLayout::SizeConstraint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLayout_SizeConstraint_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLayout::SizeConstraint value = qscriptvalue_cast<QLayout::SizeConstraint>(context->thisObject());
    return QScriptValue(engine, qtscript_QLayout_SizeConstraint_toStringHelper(value));
}

static QScriptValue qtscript_create_QLayout_SizeConstraint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLayout_SizeConstraint,
        qtscript_QLayout_SizeConstraint_valueOf, qtscript_QLayout_SizeConstraint_toString);
    qScriptRegisterMetaType<QLayout::SizeConstraint>(engine, qtscript_QLayout_SizeConstraint_toScriptValue,
        qtscript_QLayout_SizeConstraint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLayout_SizeConstraint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLayout_SizeConstraint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLayout
//

static QScriptValue qtscript_QLayout_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 24;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QLayout* _q_self = qscriptvalue_cast<QLayout*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QLayout.%0(): this object is not a QLayout")
            .arg(qtscript_QLayout_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->activate();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QLayoutItem* _q_arg0 = qscriptvalue_cast<QLayoutItem*>(context->argument(0));
        _q_self->addItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->addWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QMargins _q_result = _q_self->contentsMargins();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->contentsRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 4) {
        int* _q_arg0 = qscriptvalue_cast<int*>(context->argument(0));
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
        int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
        _q_self->getContentsMargins(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_result = _q_self->indexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QLayoutItem* _q_result = _q_self->itemAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->menuBar();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->parentWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QLayoutItem* _q_arg0 = qscriptvalue_cast<QLayoutItem*>(context->argument(0));
        _q_self->removeItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->removeWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QLayout*>(context->argument(0))
            && (qMetaTypeId<QFlags<Qt::AlignmentFlag> >() == context->argument(1).toVariant().userType())) {
            QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
            QFlags<Qt::AlignmentFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(1));
            bool _q_result = _q_self->setAlignment(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && (qMetaTypeId<QFlags<Qt::AlignmentFlag> >() == context->argument(1).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QFlags<Qt::AlignmentFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(1));
            bool _q_result = _q_self->setAlignment(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QMargins _q_arg0 = qscriptvalue_cast<QMargins>(context->argument(0));
        _q_self->setContentsMargins(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setContentsMargins(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setMenuBar(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QLayoutItem* _q_result = _q_self->takeAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->totalHeightForWidth(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->totalMaximumSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->totalMinimumSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->totalSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        _q_self->update();
        return context->engine()->undefinedValue();
    }
    break;

    case 24: {
    QString result = QString::fromLatin1("QLayout");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLayout_throw_ambiguity_error_helper(context,
        qtscript_QLayout_function_names[_id+2],
        qtscript_QLayout_function_signatures[_id+2]);
}

static QScriptValue qtscript_QLayout_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QLayout(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QLayout* _q_cpp_result = new QtScriptShell_QLayout();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QLayout* _q_cpp_result = new QtScriptShell_QLayout(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        const QWidget* _q_arg0 = qscriptvalue_cast<const QWidget*>(context->argument(0));
        QSize _q_arg1 = qscriptvalue_cast<QSize>(context->argument(1));
        QSize _q_result = QLayout::closestAcceptableSize(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLayout_throw_ambiguity_error_helper(context,
        qtscript_QLayout_function_names[_id],
        qtscript_QLayout_function_signatures[_id]);
}

static QScriptValue qtscript_QLayout_toScriptValue(QScriptEngine *engine, QLayout* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QLayout_fromScriptValue(const QScriptValue &value, QLayout* &out)
{
    out = qobject_cast<QLayout*>(value.toQObject());
}

QScriptValue qtscript_create_QLayout_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QLayout*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QLayout*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    proto.setProperty(QString::fromLatin1("__QLayoutItem__"),
        engine->defaultPrototype(qMetaTypeId<QLayoutItem*>()),
        QScriptValue::SkipInEnumeration);
    for (int i = 0; i < 25; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLayout_prototype_call, qtscript_QLayout_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QLayout_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QLayout*>(engine, qtscript_QLayout_toScriptValue, 
        qtscript_QLayout_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QLayout_static_call, proto, qtscript_QLayout_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLayout_static_call,
            qtscript_QLayout_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QLayout_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("SizeConstraint"),
        qtscript_create_QLayout_SizeConstraint_class(engine, ctor));
    return ctor;
}
