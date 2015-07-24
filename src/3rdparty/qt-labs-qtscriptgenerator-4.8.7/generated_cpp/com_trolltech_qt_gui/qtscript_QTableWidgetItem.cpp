#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtablewidget.h>
#include <QVariant>
#include <qbrush.h>
#include <qdatastream.h>
#include <qfont.h>
#include <qicon.h>
#include <qsize.h>
#include <qtablewidget.h>

#include "qtscriptshell_QTableWidgetItem.h"

static const char * const qtscript_QTableWidgetItem_function_names[] = {
    "QTableWidgetItem"
    // static
    // prototype
    , "background"
    , "checkState"
    , "clone"
    , "column"
    , "data"
    , "flags"
    , "font"
    , "foreground"
    , "icon"
    , "isSelected"
    , "readFrom"
    , "row"
    , "setBackground"
    , "setCheckState"
    , "setData"
    , "setFlags"
    , "setFont"
    , "setForeground"
    , "setIcon"
    , "setSelected"
    , "setSizeHint"
    , "setStatusTip"
    , "setText"
    , "setTextAlignment"
    , "setToolTip"
    , "setWhatsThis"
    , "sizeHint"
    , "statusTip"
    , "tableWidget"
    , "text"
    , "textAlignment"
    , "toolTip"
    , "type"
    , "whatsThis"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QTableWidgetItem_function_signatures[] = {
    "QIcon icon, String text, int type\nString text, int type\nint type"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "int role"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QDataStream in"
    , ""
    , "QBrush brush"
    , "CheckState state"
    , "int role, Object value"
    , "ItemFlags flags"
    , "QFont font"
    , "QBrush brush"
    , "QIcon icon"
    , "bool select"
    , "QSize size"
    , "String statusTip"
    , "String text"
    , "int alignment"
    , "String toolTip"
    , "String whatsThis"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QDataStream out"
""
};

static const int qtscript_QTableWidgetItem_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
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
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QTableWidgetItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTableWidgetItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTableWidgetItem*)
Q_DECLARE_METATYPE(QtScriptShell_QTableWidgetItem*)
Q_DECLARE_METATYPE(QTableWidgetItem::ItemType)
Q_DECLARE_METATYPE(Qt::CheckState)
Q_DECLARE_METATYPE(QFlags<Qt::ItemFlag>)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(QTableWidget*)

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
// QTableWidgetItem::ItemType
//

static const QTableWidgetItem::ItemType qtscript_QTableWidgetItem_ItemType_values[] = {
    QTableWidgetItem::Type
    , QTableWidgetItem::UserType
};

static const char * const qtscript_QTableWidgetItem_ItemType_keys[] = {
    "Type"
    , "UserType"
};

static QString qtscript_QTableWidgetItem_ItemType_toStringHelper(QTableWidgetItem::ItemType value)
{
    for (int i = 0; i < 2; ++i) {
        if (qtscript_QTableWidgetItem_ItemType_values[i] == value)
            return QString::fromLatin1(qtscript_QTableWidgetItem_ItemType_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QTableWidgetItem_ItemType_toScriptValue(QScriptEngine *engine, const QTableWidgetItem::ItemType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTableWidgetItem"));
    return clazz.property(qtscript_QTableWidgetItem_ItemType_toStringHelper(value));
}

static void qtscript_QTableWidgetItem_ItemType_fromScriptValue(const QScriptValue &value, QTableWidgetItem::ItemType &out)
{
    out = qvariant_cast<QTableWidgetItem::ItemType>(value.toVariant());
}

static QScriptValue qtscript_construct_QTableWidgetItem_ItemType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 2; ++i) {
        if (qtscript_QTableWidgetItem_ItemType_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QTableWidgetItem::ItemType>(arg));
    }
    return context->throwError(QString::fromLatin1("ItemType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTableWidgetItem_ItemType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTableWidgetItem::ItemType value = qscriptvalue_cast<QTableWidgetItem::ItemType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTableWidgetItem_ItemType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTableWidgetItem::ItemType value = qscriptvalue_cast<QTableWidgetItem::ItemType>(context->thisObject());
    return QScriptValue(engine, qtscript_QTableWidgetItem_ItemType_toStringHelper(value));
}

static QScriptValue qtscript_create_QTableWidgetItem_ItemType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTableWidgetItem_ItemType,
        qtscript_QTableWidgetItem_ItemType_valueOf, qtscript_QTableWidgetItem_ItemType_toString);
    qScriptRegisterMetaType<QTableWidgetItem::ItemType>(engine, qtscript_QTableWidgetItem_ItemType_toScriptValue,
        qtscript_QTableWidgetItem_ItemType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTableWidgetItem_ItemType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTableWidgetItem_ItemType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTableWidgetItem
//

static QScriptValue qtscript_QTableWidgetItem_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 35;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTableWidgetItem* _q_self = qscriptvalue_cast<QTableWidgetItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTableWidgetItem.%0(): this object is not a QTableWidgetItem")
            .arg(qtscript_QTableWidgetItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->background();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        Qt::CheckState _q_result = _q_self->checkState();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QTableWidgetItem* _q_result = _q_self->clone();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->column();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_result = _q_self->data(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QFlags<Qt::ItemFlag> _q_result = _q_self->flags();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QFont _q_result = _q_self->font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QBrush _q_result = _q_self->foreground();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QIcon _q_result = _q_self->icon();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSelected();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->row();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        _q_self->setBackground(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        Qt::CheckState _q_arg0 = qscriptvalue_cast<Qt::CheckState>(context->argument(0));
        _q_self->setCheckState(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setData(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QFlags<Qt::ItemFlag> _q_arg0 = qscriptvalue_cast<QFlags<Qt::ItemFlag> >(context->argument(0));
        _q_self->setFlags(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        _q_self->setFont(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        _q_self->setForeground(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        _q_self->setIcon(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSelected(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        _q_self->setSizeHint(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setStatusTip(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setTextAlignment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setToolTip(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setWhatsThis(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->statusTip();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        QTableWidget* _q_result = _q_self->tableWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->textAlignment();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toolTip();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->type();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->whatsThis();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 35: {
    QString result = QString::fromLatin1("QTableWidgetItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTableWidgetItem_throw_ambiguity_error_helper(context,
        qtscript_QTableWidgetItem_function_names[_id+1],
        qtscript_QTableWidgetItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTableWidgetItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTableWidgetItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTableWidgetItem* _q_cpp_result = new QtScriptShell_QTableWidgetItem();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTableWidgetItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QTableWidgetItem* _q_cpp_result = new QtScriptShell_QTableWidgetItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTableWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QtScriptShell_QTableWidgetItem* _q_cpp_result = new QtScriptShell_QTableWidgetItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTableWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QIcon>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            QtScriptShell_QTableWidgetItem* _q_cpp_result = new QtScriptShell_QTableWidgetItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTableWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_arg1 = context->argument(1).toInt32();
            QtScriptShell_QTableWidgetItem* _q_cpp_result = new QtScriptShell_QTableWidgetItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTableWidgetItem*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        int _q_arg2 = context->argument(2).toInt32();
        QtScriptShell_QTableWidgetItem* _q_cpp_result = new QtScriptShell_QTableWidgetItem(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QTableWidgetItem*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTableWidgetItem_throw_ambiguity_error_helper(context,
        qtscript_QTableWidgetItem_function_names[_id],
        qtscript_QTableWidgetItem_function_signatures[_id]);
}

QScriptValue qtscript_create_QTableWidgetItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTableWidgetItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTableWidgetItem*)0));
    for (int i = 0; i < 36; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTableWidgetItem_prototype_call, qtscript_QTableWidgetItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTableWidgetItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTableWidgetItem*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTableWidgetItem_static_call, proto, qtscript_QTableWidgetItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ItemType"),
        qtscript_create_QTableWidgetItem_ItemType_class(engine, ctor));
    return ctor;
}
