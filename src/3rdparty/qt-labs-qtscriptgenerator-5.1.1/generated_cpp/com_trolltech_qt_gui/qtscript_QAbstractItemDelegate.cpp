#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qabstractitemdelegate.h>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qvector.h>
#include <qwidget.h>

#include "qtscriptshell_QAbstractItemDelegate.h"

static const char * const qtscript_QAbstractItemDelegate_function_names[] = {
    "QAbstractItemDelegate"
    // static
    // prototype
    , "createEditor"
    , "destroyEditor"
    , "editorEvent"
    , "helpEvent"
    , "paint"
    , "paintingRoles"
    , "setEditorData"
    , "setModelData"
    , "sizeHint"
    , "updateEditorGeometry"
    , "toString"
};

static const char * const qtscript_QAbstractItemDelegate_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "QWidget parent, QStyleOptionViewItem option, QModelIndex index"
    , "QWidget editor, QModelIndex index"
    , "QEvent event, QAbstractItemModel model, QStyleOptionViewItem option, QModelIndex index"
    , "QHelpEvent event, QAbstractItemView view, QStyleOptionViewItem option, QModelIndex index"
    , "QPainter painter, QStyleOptionViewItem option, QModelIndex index"
    , ""
    , "QWidget editor, QModelIndex index"
    , "QWidget editor, QAbstractItemModel model, QModelIndex index"
    , "QStyleOptionViewItem option, QModelIndex index"
    , "QWidget editor, QStyleOptionViewItem option, QModelIndex index"
""
};

static const int qtscript_QAbstractItemDelegate_function_lengths[] = {
    1
    // static
    // prototype
    , 3
    , 2
    , 4
    , 4
    , 3
    , 0
    , 2
    , 3
    , 2
    , 3
    , 0
};

static QScriptValue qtscript_QAbstractItemDelegate_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractItemDelegate::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractItemDelegate*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractItemDelegate*)
Q_DECLARE_METATYPE(QAbstractItemDelegate::EndEditHint)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QStyleOptionViewItem)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QHelpEvent*)
Q_DECLARE_METATYPE(QAbstractItemView*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QVector<int >)

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
// QAbstractItemDelegate::EndEditHint
//

static const QAbstractItemDelegate::EndEditHint qtscript_QAbstractItemDelegate_EndEditHint_values[] = {
    QAbstractItemDelegate::NoHint
    , QAbstractItemDelegate::EditNextItem
    , QAbstractItemDelegate::EditPreviousItem
    , QAbstractItemDelegate::SubmitModelCache
    , QAbstractItemDelegate::RevertModelCache
};

static const char * const qtscript_QAbstractItemDelegate_EndEditHint_keys[] = {
    "NoHint"
    , "EditNextItem"
    , "EditPreviousItem"
    , "SubmitModelCache"
    , "RevertModelCache"
};

static QString qtscript_QAbstractItemDelegate_EndEditHint_toStringHelper(QAbstractItemDelegate::EndEditHint value)
{
    if ((value >= QAbstractItemDelegate::NoHint) && (value <= QAbstractItemDelegate::RevertModelCache))
        return qtscript_QAbstractItemDelegate_EndEditHint_keys[static_cast<int>(value)-static_cast<int>(QAbstractItemDelegate::NoHint)];
    return QString();
}

static QScriptValue qtscript_QAbstractItemDelegate_EndEditHint_toScriptValue(QScriptEngine *engine, const QAbstractItemDelegate::EndEditHint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractItemDelegate"));
    return clazz.property(qtscript_QAbstractItemDelegate_EndEditHint_toStringHelper(value));
}

static void qtscript_QAbstractItemDelegate_EndEditHint_fromScriptValue(const QScriptValue &value, QAbstractItemDelegate::EndEditHint &out)
{
    out = qvariant_cast<QAbstractItemDelegate::EndEditHint>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractItemDelegate_EndEditHint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractItemDelegate::NoHint) && (arg <= QAbstractItemDelegate::RevertModelCache))
        return qScriptValueFromValue(engine,  static_cast<QAbstractItemDelegate::EndEditHint>(arg));
    return context->throwError(QString::fromLatin1("EndEditHint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractItemDelegate_EndEditHint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemDelegate::EndEditHint value = qscriptvalue_cast<QAbstractItemDelegate::EndEditHint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractItemDelegate_EndEditHint_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemDelegate::EndEditHint value = qscriptvalue_cast<QAbstractItemDelegate::EndEditHint>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractItemDelegate_EndEditHint_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractItemDelegate_EndEditHint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractItemDelegate_EndEditHint,
        qtscript_QAbstractItemDelegate_EndEditHint_valueOf, qtscript_QAbstractItemDelegate_EndEditHint_toString);
    qScriptRegisterMetaType<QAbstractItemDelegate::EndEditHint>(engine, qtscript_QAbstractItemDelegate_EndEditHint_toScriptValue,
        qtscript_QAbstractItemDelegate_EndEditHint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractItemDelegate_EndEditHint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractItemDelegate_EndEditHint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractItemDelegate
//

static QScriptValue qtscript_QAbstractItemDelegate_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 10;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractItemDelegate* _q_self = qscriptvalue_cast<QAbstractItemDelegate*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractItemDelegate.%0(): this object is not a QAbstractItemDelegate")
            .arg(qtscript_QAbstractItemDelegate_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QStyleOptionViewItem _q_arg1 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(1));
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        QWidget* _q_result = _q_self->createEditor(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        _q_self->destroyEditor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 4) {
        QEvent* _q_arg0 = qscriptvalue_cast<QEvent*>(context->argument(0));
        QAbstractItemModel* _q_arg1 = qscriptvalue_cast<QAbstractItemModel*>(context->argument(1));
        QStyleOptionViewItem _q_arg2 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(2));
        QModelIndex _q_arg3 = qscriptvalue_cast<QModelIndex>(context->argument(3));
        bool _q_result = _q_self->editorEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 4) {
        QHelpEvent* _q_arg0 = qscriptvalue_cast<QHelpEvent*>(context->argument(0));
        QAbstractItemView* _q_arg1 = qscriptvalue_cast<QAbstractItemView*>(context->argument(1));
        QStyleOptionViewItem _q_arg2 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(2));
        QModelIndex _q_arg3 = qscriptvalue_cast<QModelIndex>(context->argument(3));
        bool _q_result = _q_self->helpEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 3) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QStyleOptionViewItem _q_arg1 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(1));
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        _q_self->paint(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QVector<int > _q_result = _q_self->paintingRoles();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        _q_self->setEditorData(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QAbstractItemModel* _q_arg1 = qscriptvalue_cast<QAbstractItemModel*>(context->argument(1));
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        _q_self->setModelData(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QStyleOptionViewItem _q_arg0 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(0));
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        QSize _q_result = _q_self->sizeHint(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QStyleOptionViewItem _q_arg1 = qscriptvalue_cast<QStyleOptionViewItem>(context->argument(1));
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        _q_self->updateEditorGeometry(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 10: {
    QString result = QString::fromLatin1("QAbstractItemDelegate");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractItemDelegate_throw_ambiguity_error_helper(context,
        qtscript_QAbstractItemDelegate_function_names[_id+1],
        qtscript_QAbstractItemDelegate_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractItemDelegate_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractItemDelegate(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractItemDelegate* _q_cpp_result = new QtScriptShell_QAbstractItemDelegate();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractItemDelegate*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QAbstractItemDelegate* _q_cpp_result = new QtScriptShell_QAbstractItemDelegate(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractItemDelegate*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractItemDelegate_throw_ambiguity_error_helper(context,
        qtscript_QAbstractItemDelegate_function_names[_id],
        qtscript_QAbstractItemDelegate_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractItemDelegate_toScriptValue(QScriptEngine *engine, QAbstractItemDelegate* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractItemDelegate_fromScriptValue(const QScriptValue &value, QAbstractItemDelegate* &out)
{
    out = qobject_cast<QAbstractItemDelegate*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractItemDelegate_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractItemDelegate*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractItemDelegate*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractItemDelegate_prototype_call, qtscript_QAbstractItemDelegate_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractItemDelegate_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractItemDelegate*>(engine, qtscript_QAbstractItemDelegate_toScriptValue, 
        qtscript_QAbstractItemDelegate_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractItemDelegate_static_call, proto, qtscript_QAbstractItemDelegate_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("EndEditHint"),
        qtscript_create_QAbstractItemDelegate_EndEditHint_class(engine, ctor));
    return ctor;
}
