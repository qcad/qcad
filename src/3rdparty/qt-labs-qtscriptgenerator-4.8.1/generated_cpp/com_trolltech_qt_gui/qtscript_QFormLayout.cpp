#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qformlayout.h>
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

#include "qtscriptshell_QFormLayout.h"

static const char * const qtscript_QFormLayout_function_names[] = {
    "QFormLayout"
    // static
    // prototype
    , "addRow"
    , "getItemPosition"
    , "getLayoutPosition"
    , "getWidgetPosition"
    , "insertRow"
    , "itemAt"
    , "labelForField"
    , "rowCount"
    , "setItem_private"
    , "setLayout"
    , "setSpacing"
    , "setWidget"
    , "spacing"
    , "toString"
};

static const char * const qtscript_QFormLayout_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "QLayout layout\nQWidget label, QLayout field\nQWidget label, QWidget field\nQWidget widget\nString labelText, QLayout field\nString labelText, QWidget field"
    , "int index, int rowPtr, ItemRole rolePtr"
    , "QLayout layout, int rowPtr, ItemRole rolePtr"
    , "QWidget widget, int rowPtr, ItemRole rolePtr"
    , "int row, QLayout layout\nint row, QWidget label, QLayout field\nint row, QWidget label, QWidget field\nint row, QWidget widget\nint row, String labelText, QLayout field\nint row, String labelText, QWidget field"
    , "int row, ItemRole role"
    , "QLayout field\nQWidget field"
    , ""
    , "int row, ItemRole role, QLayoutItem item"
    , "int row, ItemRole role, QLayout layout"
    , "int arg__1"
    , "int row, ItemRole role, QWidget widget"
    , ""
""
};

static const int qtscript_QFormLayout_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 3
    , 3
    , 3
    , 3
    , 2
    , 1
    , 0
    , 3
    , 3
    , 1
    , 3
    , 0
    , 0
};

static QScriptValue qtscript_QFormLayout_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFormLayout::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QFormLayout_metaObject()
{
    return &QFormLayout::staticMetaObject;
}

Q_DECLARE_METATYPE(QFormLayout*)
Q_DECLARE_METATYPE(QtScriptShell_QFormLayout*)
Q_DECLARE_METATYPE(QFormLayout::FieldGrowthPolicy)
Q_DECLARE_METATYPE(QFormLayout::RowWrapPolicy)
Q_DECLARE_METATYPE(QFormLayout::ItemRole)
Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(QFormLayout::ItemRole*)
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
// QFormLayout::FieldGrowthPolicy
//

static const QFormLayout::FieldGrowthPolicy qtscript_QFormLayout_FieldGrowthPolicy_values[] = {
    QFormLayout::FieldsStayAtSizeHint
    , QFormLayout::ExpandingFieldsGrow
    , QFormLayout::AllNonFixedFieldsGrow
};

static const char * const qtscript_QFormLayout_FieldGrowthPolicy_keys[] = {
    "FieldsStayAtSizeHint"
    , "ExpandingFieldsGrow"
    , "AllNonFixedFieldsGrow"
};

static QString qtscript_QFormLayout_FieldGrowthPolicy_toStringHelper(QFormLayout::FieldGrowthPolicy value)
{
    const QMetaObject *meta = qtscript_QFormLayout_metaObject();
    int idx = meta->indexOfEnumerator("FieldGrowthPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QFormLayout_FieldGrowthPolicy_toScriptValue(QScriptEngine *engine, const QFormLayout::FieldGrowthPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFormLayout"));
    return clazz.property(qtscript_QFormLayout_FieldGrowthPolicy_toStringHelper(value));
}

static void qtscript_QFormLayout_FieldGrowthPolicy_fromScriptValue(const QScriptValue &value, QFormLayout::FieldGrowthPolicy &out)
{
    out = qvariant_cast<QFormLayout::FieldGrowthPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_QFormLayout_FieldGrowthPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QFormLayout_metaObject();
    int idx = meta->indexOfEnumerator("FieldGrowthPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QFormLayout::FieldGrowthPolicy>(arg));
    return context->throwError(QString::fromLatin1("FieldGrowthPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFormLayout_FieldGrowthPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFormLayout::FieldGrowthPolicy value = qscriptvalue_cast<QFormLayout::FieldGrowthPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFormLayout_FieldGrowthPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFormLayout::FieldGrowthPolicy value = qscriptvalue_cast<QFormLayout::FieldGrowthPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_QFormLayout_FieldGrowthPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_QFormLayout_FieldGrowthPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFormLayout_FieldGrowthPolicy,
        qtscript_QFormLayout_FieldGrowthPolicy_valueOf, qtscript_QFormLayout_FieldGrowthPolicy_toString);
    qScriptRegisterMetaType<QFormLayout::FieldGrowthPolicy>(engine, qtscript_QFormLayout_FieldGrowthPolicy_toScriptValue,
        qtscript_QFormLayout_FieldGrowthPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFormLayout_FieldGrowthPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFormLayout_FieldGrowthPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFormLayout::RowWrapPolicy
//

static const QFormLayout::RowWrapPolicy qtscript_QFormLayout_RowWrapPolicy_values[] = {
    QFormLayout::DontWrapRows
    , QFormLayout::WrapLongRows
    , QFormLayout::WrapAllRows
};

static const char * const qtscript_QFormLayout_RowWrapPolicy_keys[] = {
    "DontWrapRows"
    , "WrapLongRows"
    , "WrapAllRows"
};

static QString qtscript_QFormLayout_RowWrapPolicy_toStringHelper(QFormLayout::RowWrapPolicy value)
{
    const QMetaObject *meta = qtscript_QFormLayout_metaObject();
    int idx = meta->indexOfEnumerator("RowWrapPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QFormLayout_RowWrapPolicy_toScriptValue(QScriptEngine *engine, const QFormLayout::RowWrapPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFormLayout"));
    return clazz.property(qtscript_QFormLayout_RowWrapPolicy_toStringHelper(value));
}

static void qtscript_QFormLayout_RowWrapPolicy_fromScriptValue(const QScriptValue &value, QFormLayout::RowWrapPolicy &out)
{
    out = qvariant_cast<QFormLayout::RowWrapPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_QFormLayout_RowWrapPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QFormLayout_metaObject();
    int idx = meta->indexOfEnumerator("RowWrapPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QFormLayout::RowWrapPolicy>(arg));
    return context->throwError(QString::fromLatin1("RowWrapPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFormLayout_RowWrapPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFormLayout::RowWrapPolicy value = qscriptvalue_cast<QFormLayout::RowWrapPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFormLayout_RowWrapPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFormLayout::RowWrapPolicy value = qscriptvalue_cast<QFormLayout::RowWrapPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_QFormLayout_RowWrapPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_QFormLayout_RowWrapPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFormLayout_RowWrapPolicy,
        qtscript_QFormLayout_RowWrapPolicy_valueOf, qtscript_QFormLayout_RowWrapPolicy_toString);
    qScriptRegisterMetaType<QFormLayout::RowWrapPolicy>(engine, qtscript_QFormLayout_RowWrapPolicy_toScriptValue,
        qtscript_QFormLayout_RowWrapPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFormLayout_RowWrapPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFormLayout_RowWrapPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFormLayout::ItemRole
//

static const QFormLayout::ItemRole qtscript_QFormLayout_ItemRole_values[] = {
    QFormLayout::LabelRole
    , QFormLayout::FieldRole
    , QFormLayout::SpanningRole
};

static const char * const qtscript_QFormLayout_ItemRole_keys[] = {
    "LabelRole"
    , "FieldRole"
    , "SpanningRole"
};

static QString qtscript_QFormLayout_ItemRole_toStringHelper(QFormLayout::ItemRole value)
{
    const QMetaObject *meta = qtscript_QFormLayout_metaObject();
    int idx = meta->indexOfEnumerator("ItemRole");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QFormLayout_ItemRole_toScriptValue(QScriptEngine *engine, const QFormLayout::ItemRole &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFormLayout"));
    return clazz.property(qtscript_QFormLayout_ItemRole_toStringHelper(value));
}

static void qtscript_QFormLayout_ItemRole_fromScriptValue(const QScriptValue &value, QFormLayout::ItemRole &out)
{
    out = qvariant_cast<QFormLayout::ItemRole>(value.toVariant());
}

static QScriptValue qtscript_construct_QFormLayout_ItemRole(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QFormLayout_metaObject();
    int idx = meta->indexOfEnumerator("ItemRole");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QFormLayout::ItemRole>(arg));
    return context->throwError(QString::fromLatin1("ItemRole(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFormLayout_ItemRole_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFormLayout::ItemRole value = qscriptvalue_cast<QFormLayout::ItemRole>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFormLayout_ItemRole_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFormLayout::ItemRole value = qscriptvalue_cast<QFormLayout::ItemRole>(context->thisObject());
    return QScriptValue(engine, qtscript_QFormLayout_ItemRole_toStringHelper(value));
}

static QScriptValue qtscript_create_QFormLayout_ItemRole_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFormLayout_ItemRole,
        qtscript_QFormLayout_ItemRole_valueOf, qtscript_QFormLayout_ItemRole_toString);
    qScriptRegisterMetaType<QFormLayout::ItemRole>(engine, qtscript_QFormLayout_ItemRole_toScriptValue,
        qtscript_QFormLayout_ItemRole_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFormLayout_ItemRole_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFormLayout_ItemRole_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFormLayout
//

static QScriptValue qtscript_QFormLayout_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 13;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QFormLayout* _q_self = qscriptvalue_cast<QFormLayout*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFormLayout.%0(): this object is not a QFormLayout")
            .arg(qtscript_QFormLayout_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QLayout*>(context->argument(0))) {
            QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
            _q_self->addRow(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            _q_self->addRow(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && qscriptvalue_cast<QLayout*>(context->argument(1))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QLayout* _q_arg1 = qscriptvalue_cast<QLayout*>(context->argument(1));
            _q_self->addRow(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            _q_self->addRow(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && qscriptvalue_cast<QLayout*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            QLayout* _q_arg1 = qscriptvalue_cast<QLayout*>(context->argument(1));
            _q_self->addRow(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            _q_self->addRow(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        QFormLayout::ItemRole* _q_arg2 = qscriptvalue_cast<QFormLayout::ItemRole*>(context->argument(2));
        _q_self->getItemPosition(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        QFormLayout::ItemRole* _q_arg2 = qscriptvalue_cast<QFormLayout::ItemRole*>(context->argument(2));
        _q_self->getLayoutPosition(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        QFormLayout::ItemRole* _q_arg2 = qscriptvalue_cast<QFormLayout::ItemRole*>(context->argument(2));
        _q_self->getWidgetPosition(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isNumber()
            && qscriptvalue_cast<QLayout*>(context->argument(1))) {
            int _q_arg0 = context->argument(0).toInt32();
            QLayout* _q_arg1 = qscriptvalue_cast<QLayout*>(context->argument(1));
            _q_self->insertRow(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            int _q_arg0 = context->argument(0).toInt32();
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            _q_self->insertRow(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if (context->argument(0).isNumber()
            && qscriptvalue_cast<QWidget*>(context->argument(1))
            && qscriptvalue_cast<QLayout*>(context->argument(2))) {
            int _q_arg0 = context->argument(0).toInt32();
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QLayout* _q_arg2 = qscriptvalue_cast<QLayout*>(context->argument(2));
            _q_self->insertRow(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<QWidget*>(context->argument(1))
            && qscriptvalue_cast<QWidget*>(context->argument(2))) {
            int _q_arg0 = context->argument(0).toInt32();
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
            _q_self->insertRow(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isString()
            && qscriptvalue_cast<QLayout*>(context->argument(2))) {
            int _q_arg0 = context->argument(0).toInt32();
            QString _q_arg1 = context->argument(1).toString();
            QLayout* _q_arg2 = qscriptvalue_cast<QLayout*>(context->argument(2));
            _q_self->insertRow(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isString()
            && qscriptvalue_cast<QWidget*>(context->argument(2))) {
            int _q_arg0 = context->argument(0).toInt32();
            QString _q_arg1 = context->argument(1).toString();
            QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
            _q_self->insertRow(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QFormLayout::ItemRole _q_arg1 = qscriptvalue_cast<QFormLayout::ItemRole>(context->argument(1));
        QLayoutItem* _q_result = _q_self->itemAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QLayout*>(context->argument(0))) {
            QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
            QWidget* _q_result = _q_self->labelForField(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QWidget* _q_result = _q_self->labelForField(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->rowCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QFormLayout::ItemRole _q_arg1 = qscriptvalue_cast<QFormLayout::ItemRole>(context->argument(1));
        QLayoutItem* _q_arg2 = qscriptvalue_cast<QLayoutItem*>(context->argument(2));
        _q_self->setItem(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QFormLayout::ItemRole _q_arg1 = qscriptvalue_cast<QFormLayout::ItemRole>(context->argument(1));
        QLayout* _q_arg2 = qscriptvalue_cast<QLayout*>(context->argument(2));
        _q_self->setLayout(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QFormLayout::ItemRole _q_arg1 = qscriptvalue_cast<QFormLayout::ItemRole>(context->argument(1));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        _q_self->setWidget(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->spacing();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13: {
    QString result = QString::fromLatin1("QFormLayout");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFormLayout_throw_ambiguity_error_helper(context,
        qtscript_QFormLayout_function_names[_id+1],
        qtscript_QFormLayout_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFormLayout_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFormLayout(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QFormLayout* _q_cpp_result = new QtScriptShell_QFormLayout();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFormLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QFormLayout* _q_cpp_result = new QtScriptShell_QFormLayout(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFormLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFormLayout_throw_ambiguity_error_helper(context,
        qtscript_QFormLayout_function_names[_id],
        qtscript_QFormLayout_function_signatures[_id]);
}

static QScriptValue qtscript_QFormLayout_toScriptValue(QScriptEngine *engine, QFormLayout* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QFormLayout_fromScriptValue(const QScriptValue &value, QFormLayout* &out)
{
    out = qobject_cast<QFormLayout*>(value.toQObject());
}

QScriptValue qtscript_create_QFormLayout_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFormLayout*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFormLayout*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QLayout*>()));
    for (int i = 0; i < 14; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFormLayout_prototype_call, qtscript_QFormLayout_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFormLayout_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QFormLayout*>(engine, qtscript_QFormLayout_toScriptValue, 
        qtscript_QFormLayout_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFormLayout_static_call, proto, qtscript_QFormLayout_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("FieldGrowthPolicy"),
        qtscript_create_QFormLayout_FieldGrowthPolicy_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("RowWrapPolicy"),
        qtscript_create_QFormLayout_RowWrapPolicy_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ItemRole"),
        qtscript_create_QFormLayout_ItemRole_class(engine, ctor));
    return ctor;
}
