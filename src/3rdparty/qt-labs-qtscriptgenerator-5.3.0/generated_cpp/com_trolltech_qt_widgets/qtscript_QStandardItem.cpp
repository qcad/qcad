#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qstandarditemmodel.h>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbrush.h>
#include <qfont.h>
#include <qicon.h>
#include <qlist.h>
#include <qsize.h>
#include <qstandarditemmodel.h>

#include "qtscriptshell_QStandardItem.h"

static const char * const qtscript_QStandardItem_function_names[] = {
    "QStandardItem"
    // static
    // prototype
    , "accessibleDescription"
    , "accessibleText"
    , "appendColumn"
    , "appendRow"
    , "appendRows"
    , "background"
    , "checkState"
    , "child"
    , "clone"
    , "column"
    , "columnCount"
    , "data"
    , "flags"
    , "font"
    , "foreground"
    , "hasChildren"
    , "icon"
    , "index"
    , "insertColumn"
    , "insertColumns"
    , "insertRow"
    , "insertRows"
    , "isCheckable"
    , "isDragEnabled"
    , "isDropEnabled"
    , "isEditable"
    , "isEnabled"
    , "isSelectable"
    , "isTristate"
    , "model"
    , "parent"
    , "removeColumn"
    , "removeColumns"
    , "removeRow"
    , "removeRows"
    , "row"
    , "rowCount"
    , "setAccessibleDescription"
    , "setAccessibleText"
    , "setBackground"
    , "setCheckState"
    , "setCheckable"
    , "setChild"
    , "setColumnCount"
    , "setData"
    , "setDragEnabled"
    , "setDropEnabled"
    , "setEditable"
    , "setEnabled"
    , "setFlags"
    , "setFont"
    , "setForeground"
    , "setIcon"
    , "setRowCount"
    , "setSelectable"
    , "setSizeHint"
    , "setStatusTip"
    , "setText"
    , "setTextAlignment"
    , "setToolTip"
    , "setTristate"
    , "setWhatsThis"
    , "sizeHint"
    , "sortChildren"
    , "statusTip"
    , "takeChild"
    , "takeColumn"
    , "takeRow"
    , "text"
    , "textAlignment"
    , "toolTip"
    , "type"
    , "whatsThis"
    , "toString"
};

static const char * const qtscript_QStandardItem_function_signatures[] = {
    "\nQIcon icon, String text\nString text\nint rows, int columns"
    // static
    // prototype
    , ""
    , ""
    , "List items"
    , "QStandardItem item\nList items"
    , "List items"
    , ""
    , ""
    , "int row, int column"
    , ""
    , ""
    , ""
    , "int role"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int column, List items"
    , "int column, int count"
    , "int row, QStandardItem item\nint row, List items"
    , "int row, List items\nint row, int count"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int column"
    , "int column, int count"
    , "int row"
    , "int row, int count"
    , ""
    , ""
    , "String accessibleDescription"
    , "String accessibleText"
    , "QBrush brush"
    , "CheckState checkState"
    , "bool checkable"
    , "int row, QStandardItem item\nint row, int column, QStandardItem item"
    , "int columns"
    , "Object value, int role"
    , "bool dragEnabled"
    , "bool dropEnabled"
    , "bool editable"
    , "bool enabled"
    , "ItemFlags flags"
    , "QFont font"
    , "QBrush brush"
    , "QIcon icon"
    , "int rows"
    , "bool selectable"
    , "QSize sizeHint"
    , "String statusTip"
    , "String text"
    , "Alignment textAlignment"
    , "String toolTip"
    , "bool tristate"
    , "String whatsThis"
    , ""
    , "int column, SortOrder order"
    , ""
    , "int row, int column"
    , "int column"
    , "int row"
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QStandardItem_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 1
    , 0
    , 0
    , 2
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 2
    , 2
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 2
    , 1
    , 2
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 3
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 2
    , 0
    , 2
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QStandardItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStandardItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStandardItem*)
Q_DECLARE_METATYPE(QtScriptShell_QStandardItem*)
Q_DECLARE_METATYPE(QStandardItem::ItemType)
Q_DECLARE_METATYPE(QList<QStandardItem* >)
Q_DECLARE_METATYPE(Qt::CheckState)
Q_DECLARE_METATYPE(QFlags<Qt::ItemFlag>)
Q_DECLARE_METATYPE(QStandardItemModel*)
Q_DECLARE_METATYPE(QFlags<Qt::AlignmentFlag>)
Q_DECLARE_METATYPE(Qt::SortOrder)

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
// QStandardItem::ItemType
//

static const QStandardItem::ItemType qtscript_QStandardItem_ItemType_values[] = {
    QStandardItem::Type
    , QStandardItem::UserType
};

static const char * const qtscript_QStandardItem_ItemType_keys[] = {
    "Type"
    , "UserType"
};

static QString qtscript_QStandardItem_ItemType_toStringHelper(QStandardItem::ItemType value)
{
    for (int i = 0; i < 2; ++i) {
        if (qtscript_QStandardItem_ItemType_values[i] == value)
            return QString::fromLatin1(qtscript_QStandardItem_ItemType_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QStandardItem_ItemType_toScriptValue(QScriptEngine *engine, const QStandardItem::ItemType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QStandardItem"));
    return clazz.property(qtscript_QStandardItem_ItemType_toStringHelper(value));
}

static void qtscript_QStandardItem_ItemType_fromScriptValue(const QScriptValue &value, QStandardItem::ItemType &out)
{
    out = qvariant_cast<QStandardItem::ItemType>(value.toVariant());
}

static QScriptValue qtscript_construct_QStandardItem_ItemType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 2; ++i) {
        if (qtscript_QStandardItem_ItemType_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QStandardItem::ItemType>(arg));
    }
    return context->throwError(QString::fromLatin1("ItemType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QStandardItem_ItemType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QStandardItem::ItemType value = qscriptvalue_cast<QStandardItem::ItemType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QStandardItem_ItemType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QStandardItem::ItemType value = qscriptvalue_cast<QStandardItem::ItemType>(context->thisObject());
    return QScriptValue(engine, qtscript_QStandardItem_ItemType_toStringHelper(value));
}

static QScriptValue qtscript_create_QStandardItem_ItemType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QStandardItem_ItemType,
        qtscript_QStandardItem_ItemType_valueOf, qtscript_QStandardItem_ItemType_toString);
    qScriptRegisterMetaType<QStandardItem::ItemType>(engine, qtscript_QStandardItem_ItemType_toScriptValue,
        qtscript_QStandardItem_ItemType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QStandardItem_ItemType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QStandardItem_ItemType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QStandardItem
//

static QScriptValue qtscript_QStandardItem_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 73;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QStandardItem* _q_self = qscriptvalue_cast<QStandardItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStandardItem.%0(): this object is not a QStandardItem")
            .arg(qtscript_QStandardItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->accessibleDescription();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->accessibleText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QList<QStandardItem*> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->appendColumn(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QStandardItem*>(context->argument(0))) {
            QStandardItem* _q_arg0 = qscriptvalue_cast<QStandardItem*>(context->argument(0));
            _q_self->appendRow(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isArray()) {
            QList<QStandardItem*> _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            _q_self->appendRow(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QList<QStandardItem*> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->appendRows(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->background();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        Qt::CheckState _q_result = _q_self->checkState();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QStandardItem* _q_result = _q_self->child(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QStandardItem* _q_result = _q_self->child(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QStandardItem* _q_result = _q_self->clone();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->column();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columnCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->data();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_result = _q_self->data(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QFlags<Qt::ItemFlag> _q_result = _q_self->flags();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QFont _q_result = _q_self->font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->foreground();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasChildren();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QIcon _q_result = _q_self->icon();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QModelIndex _q_result = _q_self->index();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<QStandardItem*> _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        _q_self->insertColumn(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->insertColumns(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isNumber()
            && qscriptvalue_cast<QStandardItem*>(context->argument(1))) {
            int _q_arg0 = context->argument(0).toInt32();
            QStandardItem* _q_arg1 = qscriptvalue_cast<QStandardItem*>(context->argument(1));
            _q_self->insertRow(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isArray()) {
            int _q_arg0 = context->argument(0).toInt32();
            QList<QStandardItem*> _q_arg1;
            qScriptValueToSequence(context->argument(1), _q_arg1);
            _q_self->insertRow(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 21:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isNumber()
            && context->argument(1).isArray()) {
            int _q_arg0 = context->argument(0).toInt32();
            QList<QStandardItem*> _q_arg1;
            qScriptValueToSequence(context->argument(1), _q_arg1);
            _q_self->insertRows(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->insertRows(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isCheckable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isDragEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isDropEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEditable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSelectable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isTristate();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        QStandardItemModel* _q_result = _q_self->model();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        QStandardItem* _q_result = _q_self->parent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->removeColumn(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->removeColumns(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->removeRow(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->removeRows(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->row();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->rowCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setAccessibleDescription(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setAccessibleText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        _q_self->setBackground(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        Qt::CheckState _q_arg0 = qscriptvalue_cast<Qt::CheckState>(context->argument(0));
        _q_self->setCheckState(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setCheckable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QStandardItem* _q_arg1 = qscriptvalue_cast<QStandardItem*>(context->argument(1));
        _q_self->setChild(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QStandardItem* _q_arg2 = qscriptvalue_cast<QStandardItem*>(context->argument(2));
        _q_self->setChild(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setColumnCount(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        _q_self->setData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setData(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setDragEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 46:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setDropEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 47:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setEditable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 48:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 49:
    if (context->argumentCount() == 1) {
        QFlags<Qt::ItemFlag> _q_arg0 = qscriptvalue_cast<QFlags<Qt::ItemFlag> >(context->argument(0));
        _q_self->setFlags(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 50:
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        _q_self->setFont(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 51:
    if (context->argumentCount() == 1) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        _q_self->setForeground(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 52:
    if (context->argumentCount() == 1) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        _q_self->setIcon(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 53:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setRowCount(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 54:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSelectable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 55:
    if (context->argumentCount() == 1) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        _q_self->setSizeHint(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 56:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setStatusTip(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 57:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 58:
    if (context->argumentCount() == 1) {
        QFlags<Qt::AlignmentFlag> _q_arg0 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(0));
        _q_self->setTextAlignment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 59:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setToolTip(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 60:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setTristate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 61:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setWhatsThis(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 62:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 63:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->sortChildren(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::SortOrder _q_arg1 = qscriptvalue_cast<Qt::SortOrder>(context->argument(1));
        _q_self->sortChildren(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 64:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->statusTip();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 65:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QStandardItem* _q_result = _q_self->takeChild(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QStandardItem* _q_result = _q_self->takeChild(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 66:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<QStandardItem* > _q_result = _q_self->takeColumn(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 67:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<QStandardItem* > _q_result = _q_self->takeRow(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 68:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 69:
    if (context->argumentCount() == 0) {
        QFlags<Qt::AlignmentFlag> _q_result = _q_self->textAlignment();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 70:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toolTip();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 71:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->type();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 72:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->whatsThis();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 73: {
    QString result = QString::fromLatin1("QStandardItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStandardItem_throw_ambiguity_error_helper(context,
        qtscript_QStandardItem_function_names[_id+1],
        qtscript_QStandardItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStandardItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStandardItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStandardItem* _q_cpp_result = new QtScriptShell_QStandardItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStandardItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QStandardItem* _q_cpp_result = new QtScriptShell_QStandardItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStandardItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QtScriptShell_QStandardItem* _q_cpp_result = new QtScriptShell_QStandardItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStandardItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QIcon>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QtScriptShell_QStandardItem* _q_cpp_result = new QtScriptShell_QStandardItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStandardItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QtScriptShell_QStandardItem* _q_cpp_result = new QtScriptShell_QStandardItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QStandardItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStandardItem_throw_ambiguity_error_helper(context,
        qtscript_QStandardItem_function_names[_id],
        qtscript_QStandardItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QStandardItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStandardItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStandardItem*)0));
    for (int i = 0; i < 74; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStandardItem_prototype_call, qtscript_QStandardItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStandardItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QStandardItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStandardItem_static_call, proto, qtscript_QStandardItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ItemType"),
        qtscript_create_QStandardItem_ItemType_class(engine, ctor));
    return ctor;
}
