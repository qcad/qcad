#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtreewidget.h>
#include <QVariant>
#include <qbrush.h>
#include <qfont.h>
#include <qicon.h>
#include <qlist.h>
#include <qsize.h>
#include <qstringlist.h>
#include <qtreewidget.h>

#include "qtscriptshell_QTreeWidgetItem.h"

static const char * const qtscript_QTreeWidgetItem_function_names[] = {
    "QTreeWidgetItem"
    // static
    // prototype
    , "addChild"
    , "addChildren"
    , "background"
    , "checkState"
    , "child"
    , "childCount"
    , "childIndicatorPolicy"
    , "clone"
    , "columnCount"
    , "data"
    , "flags"
    , "font"
    , "foreground"
    , "icon"
    , "indexOfChild"
    , "insertChild"
    , "insertChildren"
    , "isDisabled"
    , "isExpanded"
    , "isFirstColumnSpanned"
    , "isHidden"
    , "isSelected"
    , "parent"
    , "removeChild"
    , "setBackground"
    , "setCheckState"
    , "setChildIndicatorPolicy"
    , "setData"
    , "setDisabled"
    , "setExpanded"
    , "setFirstColumnSpanned"
    , "setFlags"
    , "setFont"
    , "setForeground"
    , "setHidden"
    , "setIcon"
    , "setSelected"
    , "setSizeHint"
    , "setStatusTip"
    , "setText"
    , "setTextAlignment"
    , "setToolTip"
    , "setWhatsThis"
    , "sizeHint"
    , "sortChildren"
    , "statusTip"
    , "takeChild"
    , "takeChildren"
    , "text"
    , "textAlignment"
    , "toolTip"
    , "treeWidget"
    , "type"
    , "whatsThis"
    , "toString"
};

static const char * const qtscript_QTreeWidgetItem_function_signatures[] = {
    "QTreeWidget view, QTreeWidgetItem after, int type\nQTreeWidget view, List strings, int type\nQTreeWidget view, int type\nQTreeWidgetItem parent, QTreeWidgetItem after, int type\nQTreeWidgetItem parent, List strings, int type\nQTreeWidgetItem parent, int type\nList strings, int type\nint type"
    // static
    // prototype
    , "QTreeWidgetItem child"
    , "List children"
    , "int column"
    , "int column"
    , "int index"
    , ""
    , ""
    , ""
    , ""
    , "int column, int role"
    , ""
    , "int column"
    , "int column"
    , "int column"
    , "QTreeWidgetItem child"
    , "int index, QTreeWidgetItem child"
    , "int index, List children"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QTreeWidgetItem child"
    , "int column, QBrush brush"
    , "int column, CheckState state"
    , "ChildIndicatorPolicy policy"
    , "int column, int role, Object value"
    , "bool disabled"
    , "bool expand"
    , "bool span"
    , "ItemFlags flags"
    , "int column, QFont font"
    , "int column, QBrush brush"
    , "bool hide"
    , "int column, QIcon icon"
    , "bool select"
    , "int column, QSize size"
    , "int column, String statusTip"
    , "int column, String text"
    , "int column, int alignment"
    , "int column, String toolTip"
    , "int column, String whatsThis"
    , "int column"
    , "int column, SortOrder order"
    , "int column"
    , "int index"
    , ""
    , "int column"
    , "int column"
    , "int column"
    , ""
    , ""
    , "int column"
""
};

static const int qtscript_QTreeWidgetItem_function_lengths[] = {
    3
    // static
    // prototype
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 2
    , 2
    , 1
    , 3
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 1
    , 2
    , 1
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 1
    , 2
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QTreeWidgetItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTreeWidgetItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTreeWidgetItem*)
Q_DECLARE_METATYPE(QtScriptShell_QTreeWidgetItem*)
Q_DECLARE_METATYPE(QTreeWidgetItem::ItemType)
Q_DECLARE_METATYPE(QTreeWidgetItem::ChildIndicatorPolicy)
Q_DECLARE_METATYPE(QList<QTreeWidgetItem* >)
Q_DECLARE_METATYPE(Qt::CheckState)
Q_DECLARE_METATYPE(QFlags<Qt::ItemFlag>)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QTreeWidget*)

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
// QTreeWidgetItem::ItemType
//

static const QTreeWidgetItem::ItemType qtscript_QTreeWidgetItem_ItemType_values[] = {
    QTreeWidgetItem::Type
    , QTreeWidgetItem::UserType
};

static const char * const qtscript_QTreeWidgetItem_ItemType_keys[] = {
    "Type"
    , "UserType"
};

static QString qtscript_QTreeWidgetItem_ItemType_toStringHelper(QTreeWidgetItem::ItemType value)
{
    for (int i = 0; i < 2; ++i) {
        if (qtscript_QTreeWidgetItem_ItemType_values[i] == value)
            return QString::fromLatin1(qtscript_QTreeWidgetItem_ItemType_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QTreeWidgetItem_ItemType_toScriptValue(QScriptEngine *engine, const QTreeWidgetItem::ItemType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTreeWidgetItem"));
    return clazz.property(qtscript_QTreeWidgetItem_ItemType_toStringHelper(value));
}

static void qtscript_QTreeWidgetItem_ItemType_fromScriptValue(const QScriptValue &value, QTreeWidgetItem::ItemType &out)
{
    out = qvariant_cast<QTreeWidgetItem::ItemType>(value.toVariant());
}

static QScriptValue qtscript_construct_QTreeWidgetItem_ItemType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 2; ++i) {
        if (qtscript_QTreeWidgetItem_ItemType_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QTreeWidgetItem::ItemType>(arg));
    }
    return context->throwError(QString::fromLatin1("ItemType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTreeWidgetItem_ItemType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTreeWidgetItem::ItemType value = qscriptvalue_cast<QTreeWidgetItem::ItemType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTreeWidgetItem_ItemType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTreeWidgetItem::ItemType value = qscriptvalue_cast<QTreeWidgetItem::ItemType>(context->thisObject());
    return QScriptValue(engine, qtscript_QTreeWidgetItem_ItemType_toStringHelper(value));
}

static QScriptValue qtscript_create_QTreeWidgetItem_ItemType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTreeWidgetItem_ItemType,
        qtscript_QTreeWidgetItem_ItemType_valueOf, qtscript_QTreeWidgetItem_ItemType_toString);
    qScriptRegisterMetaType<QTreeWidgetItem::ItemType>(engine, qtscript_QTreeWidgetItem_ItemType_toScriptValue,
        qtscript_QTreeWidgetItem_ItemType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTreeWidgetItem_ItemType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTreeWidgetItem_ItemType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTreeWidgetItem::ChildIndicatorPolicy
//

static const QTreeWidgetItem::ChildIndicatorPolicy qtscript_QTreeWidgetItem_ChildIndicatorPolicy_values[] = {
    QTreeWidgetItem::ShowIndicator
    , QTreeWidgetItem::DontShowIndicator
    , QTreeWidgetItem::DontShowIndicatorWhenChildless
};

static const char * const qtscript_QTreeWidgetItem_ChildIndicatorPolicy_keys[] = {
    "ShowIndicator"
    , "DontShowIndicator"
    , "DontShowIndicatorWhenChildless"
};

static QString qtscript_QTreeWidgetItem_ChildIndicatorPolicy_toStringHelper(QTreeWidgetItem::ChildIndicatorPolicy value)
{
    if ((value >= QTreeWidgetItem::ShowIndicator) && (value <= QTreeWidgetItem::DontShowIndicatorWhenChildless))
        return qtscript_QTreeWidgetItem_ChildIndicatorPolicy_keys[static_cast<int>(value)-static_cast<int>(QTreeWidgetItem::ShowIndicator)];
    return QString();
}

static QScriptValue qtscript_QTreeWidgetItem_ChildIndicatorPolicy_toScriptValue(QScriptEngine *engine, const QTreeWidgetItem::ChildIndicatorPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTreeWidgetItem"));
    return clazz.property(qtscript_QTreeWidgetItem_ChildIndicatorPolicy_toStringHelper(value));
}

static void qtscript_QTreeWidgetItem_ChildIndicatorPolicy_fromScriptValue(const QScriptValue &value, QTreeWidgetItem::ChildIndicatorPolicy &out)
{
    out = qvariant_cast<QTreeWidgetItem::ChildIndicatorPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_QTreeWidgetItem_ChildIndicatorPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTreeWidgetItem::ShowIndicator) && (arg <= QTreeWidgetItem::DontShowIndicatorWhenChildless))
        return qScriptValueFromValue(engine,  static_cast<QTreeWidgetItem::ChildIndicatorPolicy>(arg));
    return context->throwError(QString::fromLatin1("ChildIndicatorPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTreeWidgetItem_ChildIndicatorPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTreeWidgetItem::ChildIndicatorPolicy value = qscriptvalue_cast<QTreeWidgetItem::ChildIndicatorPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTreeWidgetItem_ChildIndicatorPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTreeWidgetItem::ChildIndicatorPolicy value = qscriptvalue_cast<QTreeWidgetItem::ChildIndicatorPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_QTreeWidgetItem_ChildIndicatorPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_QTreeWidgetItem_ChildIndicatorPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTreeWidgetItem_ChildIndicatorPolicy,
        qtscript_QTreeWidgetItem_ChildIndicatorPolicy_valueOf, qtscript_QTreeWidgetItem_ChildIndicatorPolicy_toString);
    qScriptRegisterMetaType<QTreeWidgetItem::ChildIndicatorPolicy>(engine, qtscript_QTreeWidgetItem_ChildIndicatorPolicy_toScriptValue,
        qtscript_QTreeWidgetItem_ChildIndicatorPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTreeWidgetItem_ChildIndicatorPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTreeWidgetItem_ChildIndicatorPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTreeWidgetItem
//

static QScriptValue qtscript_QTreeWidgetItem_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 54;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTreeWidgetItem* _q_self = qscriptvalue_cast<QTreeWidgetItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTreeWidgetItem.%0(): this object is not a QTreeWidgetItem")
            .arg(qtscript_QTreeWidgetItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        _q_self->addChild(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QList<QTreeWidgetItem*> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->addChildren(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QBrush _q_result = _q_self->background(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::CheckState _q_result = _q_self->checkState(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTreeWidgetItem* _q_result = _q_self->child(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->childCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QTreeWidgetItem::ChildIndicatorPolicy _q_result = _q_self->childIndicatorPolicy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QTreeWidgetItem* _q_result = _q_self->clone();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columnCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QVariant _q_result = _q_self->data(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QFlags<Qt::ItemFlag> _q_result = _q_self->flags();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QFont _q_result = _q_self->font(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QBrush _q_result = _q_self->foreground(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QIcon _q_result = _q_self->icon(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        int _q_result = _q_self->indexOfChild(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QTreeWidgetItem* _q_arg1 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(1));
        _q_self->insertChild(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<QTreeWidgetItem*> _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        _q_self->insertChildren(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isDisabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isExpanded();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isFirstColumnSpanned();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isHidden();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSelected();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        QTreeWidgetItem* _q_result = _q_self->parent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
        _q_self->removeChild(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QBrush _q_arg1 = qscriptvalue_cast<QBrush>(context->argument(1));
        _q_self->setBackground(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::CheckState _q_arg1 = qscriptvalue_cast<Qt::CheckState>(context->argument(1));
        _q_self->setCheckState(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QTreeWidgetItem::ChildIndicatorPolicy _q_arg0 = qscriptvalue_cast<QTreeWidgetItem::ChildIndicatorPolicy>(context->argument(0));
        _q_self->setChildIndicatorPolicy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QVariant _q_arg2 = context->argument(2).toVariant();
        _q_self->setData(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setDisabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setExpanded(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFirstColumnSpanned(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QFlags<Qt::ItemFlag> _q_arg0 = qscriptvalue_cast<QFlags<Qt::ItemFlag> >(context->argument(0));
        _q_self->setFlags(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QFont _q_arg1 = qscriptvalue_cast<QFont>(context->argument(1));
        _q_self->setFont(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QBrush _q_arg1 = qscriptvalue_cast<QBrush>(context->argument(1));
        _q_self->setForeground(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setHidden(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QIcon _q_arg1 = qscriptvalue_cast<QIcon>(context->argument(1));
        _q_self->setIcon(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSelected(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QSize _q_arg1 = qscriptvalue_cast<QSize>(context->argument(1));
        _q_self->setSizeHint(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setStatusTip(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setTextAlignment(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setToolTip(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setWhatsThis(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QSize _q_result = _q_self->sizeHint(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 44:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::SortOrder _q_arg1 = qscriptvalue_cast<Qt::SortOrder>(context->argument(1));
        _q_self->sortChildren(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->statusTip(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 46:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QTreeWidgetItem* _q_result = _q_self->takeChild(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {
        QList<QTreeWidgetItem* > _q_result = _q_self->takeChildren();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 48:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->text(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 49:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->textAlignment(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 50:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->toolTip(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 51:
    if (context->argumentCount() == 0) {
        QTreeWidget* _q_result = _q_self->treeWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 52:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->type();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 53:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->whatsThis(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 54: {
    QString result = QString::fromLatin1("QTreeWidgetItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTreeWidgetItem_throw_ambiguity_error_helper(context,
        qtscript_QTreeWidgetItem_function_names[_id+1],
        qtscript_QTreeWidgetItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTreeWidgetItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTreeWidgetItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QTreeWidget*>(context->argument(0))) {
            QTreeWidget* _q_arg0 = qscriptvalue_cast<QTreeWidget*>(context->argument(0));
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0))) {
            QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isArray()) {
            QStringList _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QTreeWidget*>(context->argument(0))
            && qscriptvalue_cast<QTreeWidgetItem*>(context->argument(1))) {
            QTreeWidget* _q_arg0 = qscriptvalue_cast<QTreeWidget*>(context->argument(0));
            QTreeWidgetItem* _q_arg1 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(1));
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QTreeWidget*>(context->argument(0))
            && context->argument(1).isArray()) {
            QTreeWidget* _q_arg0 = qscriptvalue_cast<QTreeWidget*>(context->argument(0));
            QStringList _q_arg1;
            qScriptValueToSequence(context->argument(1), _q_arg1);
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QTreeWidget*>(context->argument(0))
            && context->argument(1).isNumber()) {
            QTreeWidget* _q_arg0 = qscriptvalue_cast<QTreeWidget*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0))
            && qscriptvalue_cast<QTreeWidgetItem*>(context->argument(1))) {
            QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
            QTreeWidgetItem* _q_arg1 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(1));
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0))
            && context->argument(1).isArray()) {
            QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
            QStringList _q_arg1;
            qScriptValueToSequence(context->argument(1), _q_arg1);
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0))
            && context->argument(1).isNumber()) {
            QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isArray()
            && context->argument(1).isNumber()) {
            QStringList _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            int _q_arg1 = context->argument(1).toInt32();
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<QTreeWidget*>(context->argument(0))
            && qscriptvalue_cast<QTreeWidgetItem*>(context->argument(1))
            && context->argument(2).isNumber()) {
            QTreeWidget* _q_arg0 = qscriptvalue_cast<QTreeWidget*>(context->argument(0));
            QTreeWidgetItem* _q_arg1 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QTreeWidget*>(context->argument(0))
            && context->argument(1).isArray()
            && context->argument(2).isNumber()) {
            QTreeWidget* _q_arg0 = qscriptvalue_cast<QTreeWidget*>(context->argument(0));
            QStringList _q_arg1;
            qScriptValueToSequence(context->argument(1), _q_arg1);
            int _q_arg2 = context->argument(2).toInt32();
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0))
            && qscriptvalue_cast<QTreeWidgetItem*>(context->argument(1))
            && context->argument(2).isNumber()) {
            QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
            QTreeWidgetItem* _q_arg1 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0))
            && context->argument(1).isArray()
            && context->argument(2).isNumber()) {
            QTreeWidgetItem* _q_arg0 = qscriptvalue_cast<QTreeWidgetItem*>(context->argument(0));
            QStringList _q_arg1;
            qScriptValueToSequence(context->argument(1), _q_arg1);
            int _q_arg2 = context->argument(2).toInt32();
            QtScriptShell_QTreeWidgetItem* _q_cpp_result = new QtScriptShell_QTreeWidgetItem(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTreeWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTreeWidgetItem_throw_ambiguity_error_helper(context,
        qtscript_QTreeWidgetItem_function_names[_id],
        qtscript_QTreeWidgetItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QTreeWidgetItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTreeWidgetItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTreeWidgetItem*)0));
    for (int i = 0; i < 55; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTreeWidgetItem_prototype_call, qtscript_QTreeWidgetItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTreeWidgetItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTreeWidgetItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTreeWidgetItem_static_call, proto, qtscript_QTreeWidgetItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ItemType"),
        qtscript_create_QTreeWidgetItem_ItemType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ChildIndicatorPolicy"),
        qtscript_create_QTreeWidgetItem_ChildIndicatorPolicy_class(engine, ctor));
    return ctor;
}
