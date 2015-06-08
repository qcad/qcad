#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qlistview.h>
#include <QVariant>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
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
#include <qitemselectionmodel.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlistview.h>
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
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QListView.h"

static const char * const qtscript_QListView_function_names[] = {
    "QListView"
    // static
    // prototype
    , "clearPropertyFlags"
    , "isRowHidden"
    , "setRowHidden"
    , "toString"
};

static const char * const qtscript_QListView_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
    , "int row"
    , "int row, bool hide"
""
};

static const int qtscript_QListView_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QListView_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QListView::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QListView_metaObject()
{
    return &QListView::staticMetaObject;
}

Q_DECLARE_METATYPE(QListView*)
Q_DECLARE_METATYPE(QtScriptShell_QListView*)
Q_DECLARE_METATYPE(QListView::ResizeMode)
Q_DECLARE_METATYPE(QListView::LayoutMode)
Q_DECLARE_METATYPE(QListView::ViewMode)
Q_DECLARE_METATYPE(QListView::Flow)
Q_DECLARE_METATYPE(QListView::Movement)
Q_DECLARE_METATYPE(QAbstractItemView*)

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
// QListView::ResizeMode
//

static const QListView::ResizeMode qtscript_QListView_ResizeMode_values[] = {
    QListView::Fixed
    , QListView::Adjust
};

static const char * const qtscript_QListView_ResizeMode_keys[] = {
    "Fixed"
    , "Adjust"
};

static QString qtscript_QListView_ResizeMode_toStringHelper(QListView::ResizeMode value)
{
    const QMetaObject *meta = qtscript_QListView_metaObject();
    int idx = meta->indexOfEnumerator("ResizeMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QListView_ResizeMode_toScriptValue(QScriptEngine *engine, const QListView::ResizeMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QListView"));
    return clazz.property(qtscript_QListView_ResizeMode_toStringHelper(value));
}

static void qtscript_QListView_ResizeMode_fromScriptValue(const QScriptValue &value, QListView::ResizeMode &out)
{
    out = qvariant_cast<QListView::ResizeMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QListView_ResizeMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QListView_metaObject();
    int idx = meta->indexOfEnumerator("ResizeMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QListView::ResizeMode>(arg));
    return context->throwError(QString::fromLatin1("ResizeMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QListView_ResizeMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QListView::ResizeMode value = qscriptvalue_cast<QListView::ResizeMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QListView_ResizeMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QListView::ResizeMode value = qscriptvalue_cast<QListView::ResizeMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QListView_ResizeMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QListView_ResizeMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QListView_ResizeMode,
        qtscript_QListView_ResizeMode_valueOf, qtscript_QListView_ResizeMode_toString);
    qScriptRegisterMetaType<QListView::ResizeMode>(engine, qtscript_QListView_ResizeMode_toScriptValue,
        qtscript_QListView_ResizeMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QListView_ResizeMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QListView_ResizeMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QListView::LayoutMode
//

static const QListView::LayoutMode qtscript_QListView_LayoutMode_values[] = {
    QListView::SinglePass
    , QListView::Batched
};

static const char * const qtscript_QListView_LayoutMode_keys[] = {
    "SinglePass"
    , "Batched"
};

static QString qtscript_QListView_LayoutMode_toStringHelper(QListView::LayoutMode value)
{
    const QMetaObject *meta = qtscript_QListView_metaObject();
    int idx = meta->indexOfEnumerator("LayoutMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QListView_LayoutMode_toScriptValue(QScriptEngine *engine, const QListView::LayoutMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QListView"));
    return clazz.property(qtscript_QListView_LayoutMode_toStringHelper(value));
}

static void qtscript_QListView_LayoutMode_fromScriptValue(const QScriptValue &value, QListView::LayoutMode &out)
{
    out = qvariant_cast<QListView::LayoutMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QListView_LayoutMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QListView_metaObject();
    int idx = meta->indexOfEnumerator("LayoutMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QListView::LayoutMode>(arg));
    return context->throwError(QString::fromLatin1("LayoutMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QListView_LayoutMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QListView::LayoutMode value = qscriptvalue_cast<QListView::LayoutMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QListView_LayoutMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QListView::LayoutMode value = qscriptvalue_cast<QListView::LayoutMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QListView_LayoutMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QListView_LayoutMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QListView_LayoutMode,
        qtscript_QListView_LayoutMode_valueOf, qtscript_QListView_LayoutMode_toString);
    qScriptRegisterMetaType<QListView::LayoutMode>(engine, qtscript_QListView_LayoutMode_toScriptValue,
        qtscript_QListView_LayoutMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QListView_LayoutMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QListView_LayoutMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QListView::ViewMode
//

static const QListView::ViewMode qtscript_QListView_ViewMode_values[] = {
    QListView::ListMode
    , QListView::IconMode
};

static const char * const qtscript_QListView_ViewMode_keys[] = {
    "ListMode"
    , "IconMode"
};

static QString qtscript_QListView_ViewMode_toStringHelper(QListView::ViewMode value)
{
    const QMetaObject *meta = qtscript_QListView_metaObject();
    int idx = meta->indexOfEnumerator("ViewMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QListView_ViewMode_toScriptValue(QScriptEngine *engine, const QListView::ViewMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QListView"));
    return clazz.property(qtscript_QListView_ViewMode_toStringHelper(value));
}

static void qtscript_QListView_ViewMode_fromScriptValue(const QScriptValue &value, QListView::ViewMode &out)
{
    out = qvariant_cast<QListView::ViewMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QListView_ViewMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QListView_metaObject();
    int idx = meta->indexOfEnumerator("ViewMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QListView::ViewMode>(arg));
    return context->throwError(QString::fromLatin1("ViewMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QListView_ViewMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QListView::ViewMode value = qscriptvalue_cast<QListView::ViewMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QListView_ViewMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QListView::ViewMode value = qscriptvalue_cast<QListView::ViewMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QListView_ViewMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QListView_ViewMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QListView_ViewMode,
        qtscript_QListView_ViewMode_valueOf, qtscript_QListView_ViewMode_toString);
    qScriptRegisterMetaType<QListView::ViewMode>(engine, qtscript_QListView_ViewMode_toScriptValue,
        qtscript_QListView_ViewMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QListView_ViewMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QListView_ViewMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QListView::Flow
//

static const QListView::Flow qtscript_QListView_Flow_values[] = {
    QListView::LeftToRight
    , QListView::TopToBottom
};

static const char * const qtscript_QListView_Flow_keys[] = {
    "LeftToRight"
    , "TopToBottom"
};

static QString qtscript_QListView_Flow_toStringHelper(QListView::Flow value)
{
    const QMetaObject *meta = qtscript_QListView_metaObject();
    int idx = meta->indexOfEnumerator("Flow");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QListView_Flow_toScriptValue(QScriptEngine *engine, const QListView::Flow &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QListView"));
    return clazz.property(qtscript_QListView_Flow_toStringHelper(value));
}

static void qtscript_QListView_Flow_fromScriptValue(const QScriptValue &value, QListView::Flow &out)
{
    out = qvariant_cast<QListView::Flow>(value.toVariant());
}

static QScriptValue qtscript_construct_QListView_Flow(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QListView_metaObject();
    int idx = meta->indexOfEnumerator("Flow");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QListView::Flow>(arg));
    return context->throwError(QString::fromLatin1("Flow(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QListView_Flow_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QListView::Flow value = qscriptvalue_cast<QListView::Flow>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QListView_Flow_toString(QScriptContext *context, QScriptEngine *engine)
{
    QListView::Flow value = qscriptvalue_cast<QListView::Flow>(context->thisObject());
    return QScriptValue(engine, qtscript_QListView_Flow_toStringHelper(value));
}

static QScriptValue qtscript_create_QListView_Flow_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QListView_Flow,
        qtscript_QListView_Flow_valueOf, qtscript_QListView_Flow_toString);
    qScriptRegisterMetaType<QListView::Flow>(engine, qtscript_QListView_Flow_toScriptValue,
        qtscript_QListView_Flow_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QListView_Flow_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QListView_Flow_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QListView::Movement
//

static const QListView::Movement qtscript_QListView_Movement_values[] = {
    QListView::Static
    , QListView::Free
    , QListView::Snap
};

static const char * const qtscript_QListView_Movement_keys[] = {
    "Static"
    , "Free"
    , "Snap"
};

static QString qtscript_QListView_Movement_toStringHelper(QListView::Movement value)
{
    const QMetaObject *meta = qtscript_QListView_metaObject();
    int idx = meta->indexOfEnumerator("Movement");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QListView_Movement_toScriptValue(QScriptEngine *engine, const QListView::Movement &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QListView"));
    return clazz.property(qtscript_QListView_Movement_toStringHelper(value));
}

static void qtscript_QListView_Movement_fromScriptValue(const QScriptValue &value, QListView::Movement &out)
{
    out = qvariant_cast<QListView::Movement>(value.toVariant());
}

static QScriptValue qtscript_construct_QListView_Movement(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QListView_metaObject();
    int idx = meta->indexOfEnumerator("Movement");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QListView::Movement>(arg));
    return context->throwError(QString::fromLatin1("Movement(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QListView_Movement_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QListView::Movement value = qscriptvalue_cast<QListView::Movement>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QListView_Movement_toString(QScriptContext *context, QScriptEngine *engine)
{
    QListView::Movement value = qscriptvalue_cast<QListView::Movement>(context->thisObject());
    return QScriptValue(engine, qtscript_QListView_Movement_toStringHelper(value));
}

static QScriptValue qtscript_create_QListView_Movement_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QListView_Movement,
        qtscript_QListView_Movement_valueOf, qtscript_QListView_Movement_toString);
    qScriptRegisterMetaType<QListView::Movement>(engine, qtscript_QListView_Movement_toScriptValue,
        qtscript_QListView_Movement_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QListView_Movement_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QListView_Movement_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QListView
//

static QScriptValue qtscript_QListView_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QListView* _q_self = qscriptvalue_cast<QListView*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QListView.%0(): this object is not a QListView")
            .arg(qtscript_QListView_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->clearPropertyFlags();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isRowHidden(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setRowHidden(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QListView");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QListView_throw_ambiguity_error_helper(context,
        qtscript_QListView_function_names[_id+1],
        qtscript_QListView_function_signatures[_id+1]);
}

static QScriptValue qtscript_QListView_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QListView(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QListView* _q_cpp_result = new QtScriptShell_QListView();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QListView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QListView* _q_cpp_result = new QtScriptShell_QListView(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QListView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QListView_throw_ambiguity_error_helper(context,
        qtscript_QListView_function_names[_id],
        qtscript_QListView_function_signatures[_id]);
}

static QScriptValue qtscript_QListView_toScriptValue(QScriptEngine *engine, QListView* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QListView_fromScriptValue(const QScriptValue &value, QListView* &out)
{
    out = qobject_cast<QListView*>(value.toQObject());
}

QScriptValue qtscript_create_QListView_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QListView*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QListView*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractItemView*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QListView_prototype_call, qtscript_QListView_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QListView_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QListView*>(engine, qtscript_QListView_toScriptValue, 
        qtscript_QListView_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QListView_static_call, proto, qtscript_QListView_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ResizeMode"),
        qtscript_create_QListView_ResizeMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("LayoutMode"),
        qtscript_create_QListView_LayoutMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ViewMode"),
        qtscript_create_QListView_ViewMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Flow"),
        qtscript_create_QListView_Flow_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Movement"),
        qtscript_create_QListView_Movement_class(engine, ctor));
    return ctor;
}
