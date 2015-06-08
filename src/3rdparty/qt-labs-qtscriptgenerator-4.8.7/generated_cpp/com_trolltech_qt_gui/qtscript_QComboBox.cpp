#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qcombobox.h>
#include <QVariant>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcombobox.h>
#include <qcompleter.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qinputcontext.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlist.h>
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
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstringlist.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qvalidator.h>
#include <qwidget.h>

#include "qtscriptshell_QComboBox.h"

static const char * const qtscript_QComboBox_function_names[] = {
    "QComboBox"
    // static
    // prototype
    , "addItem"
    , "addItems"
    , "completer"
    , "findData"
    , "findText"
    , "hidePopup"
    , "insertItem"
    , "insertItems"
    , "insertSeparator"
    , "itemData"
    , "itemDelegate"
    , "itemIcon"
    , "itemText"
    , "lineEdit"
    , "minimumSizeHint"
    , "model"
    , "removeItem"
    , "rootModelIndex"
    , "setCompleter"
    , "setItemData"
    , "setItemDelegate"
    , "setItemIcon"
    , "setItemText"
    , "setLineEdit"
    , "setModel"
    , "setRootModelIndex"
    , "setValidator"
    , "setView"
    , "showPopup"
    , "sizeHint"
    , "validator"
    , "view"
    , "toString"
};

static const char * const qtscript_QComboBox_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "QIcon icon, String text, Object userData\nString text, Object userData"
    , "List texts"
    , ""
    , "Object data, int role, MatchFlags flags"
    , "String text, MatchFlags flags"
    , ""
    , "int index, QIcon icon, String text, Object userData\nint index, String text, Object userData"
    , "int index, List texts"
    , "int index"
    , "int index, int role"
    , ""
    , "int index"
    , "int index"
    , ""
    , ""
    , ""
    , "int index"
    , ""
    , "QCompleter c"
    , "int index, Object value, int role"
    , "QAbstractItemDelegate delegate"
    , "int index, QIcon icon"
    , "int index, String text"
    , "QLineEdit edit"
    , "QAbstractItemModel model"
    , "QModelIndex index"
    , "QValidator v"
    , "QAbstractItemView itemView"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QComboBox_function_lengths[] = {
    1
    // static
    // prototype
    , 3
    , 1
    , 0
    , 3
    , 2
    , 0
    , 4
    , 2
    , 1
    , 2
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 3
    , 1
    , 2
    , 2
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
};

static QScriptValue qtscript_QComboBox_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QComboBox::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QComboBox_metaObject()
{
    return &QComboBox::staticMetaObject;
}

Q_DECLARE_METATYPE(QComboBox*)
Q_DECLARE_METATYPE(QtScriptShell_QComboBox*)
Q_DECLARE_METATYPE(QComboBox::InsertPolicy)
Q_DECLARE_METATYPE(QComboBox::SizeAdjustPolicy)
Q_DECLARE_METATYPE(QCompleter*)
Q_DECLARE_METATYPE(QFlags<Qt::MatchFlag>)
Q_DECLARE_METATYPE(QAbstractItemDelegate*)
Q_DECLARE_METATYPE(QLineEdit*)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QValidator*)
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
// QComboBox::InsertPolicy
//

static const QComboBox::InsertPolicy qtscript_QComboBox_InsertPolicy_values[] = {
    QComboBox::NoInsert
    , QComboBox::InsertAtTop
    , QComboBox::InsertAtCurrent
    , QComboBox::InsertAtBottom
    , QComboBox::InsertAfterCurrent
    , QComboBox::InsertBeforeCurrent
    , QComboBox::InsertAlphabetically
};

static const char * const qtscript_QComboBox_InsertPolicy_keys[] = {
    "NoInsert"
    , "InsertAtTop"
    , "InsertAtCurrent"
    , "InsertAtBottom"
    , "InsertAfterCurrent"
    , "InsertBeforeCurrent"
    , "InsertAlphabetically"
};

static QString qtscript_QComboBox_InsertPolicy_toStringHelper(QComboBox::InsertPolicy value)
{
    const QMetaObject *meta = qtscript_QComboBox_metaObject();
    int idx = meta->indexOfEnumerator("InsertPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QComboBox_InsertPolicy_toScriptValue(QScriptEngine *engine, const QComboBox::InsertPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QComboBox"));
    return clazz.property(qtscript_QComboBox_InsertPolicy_toStringHelper(value));
}

static void qtscript_QComboBox_InsertPolicy_fromScriptValue(const QScriptValue &value, QComboBox::InsertPolicy &out)
{
    out = qvariant_cast<QComboBox::InsertPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_QComboBox_InsertPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QComboBox_metaObject();
    int idx = meta->indexOfEnumerator("InsertPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QComboBox::InsertPolicy>(arg));
    return context->throwError(QString::fromLatin1("InsertPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QComboBox_InsertPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QComboBox::InsertPolicy value = qscriptvalue_cast<QComboBox::InsertPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QComboBox_InsertPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QComboBox::InsertPolicy value = qscriptvalue_cast<QComboBox::InsertPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_QComboBox_InsertPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_QComboBox_InsertPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QComboBox_InsertPolicy,
        qtscript_QComboBox_InsertPolicy_valueOf, qtscript_QComboBox_InsertPolicy_toString);
    qScriptRegisterMetaType<QComboBox::InsertPolicy>(engine, qtscript_QComboBox_InsertPolicy_toScriptValue,
        qtscript_QComboBox_InsertPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QComboBox_InsertPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QComboBox_InsertPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QComboBox::SizeAdjustPolicy
//

static const QComboBox::SizeAdjustPolicy qtscript_QComboBox_SizeAdjustPolicy_values[] = {
    QComboBox::AdjustToContents
    , QComboBox::AdjustToContentsOnFirstShow
    , QComboBox::AdjustToMinimumContentsLength
    , QComboBox::AdjustToMinimumContentsLengthWithIcon
};

static const char * const qtscript_QComboBox_SizeAdjustPolicy_keys[] = {
    "AdjustToContents"
    , "AdjustToContentsOnFirstShow"
    , "AdjustToMinimumContentsLength"
    , "AdjustToMinimumContentsLengthWithIcon"
};

static QString qtscript_QComboBox_SizeAdjustPolicy_toStringHelper(QComboBox::SizeAdjustPolicy value)
{
    const QMetaObject *meta = qtscript_QComboBox_metaObject();
    int idx = meta->indexOfEnumerator("SizeAdjustPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QComboBox_SizeAdjustPolicy_toScriptValue(QScriptEngine *engine, const QComboBox::SizeAdjustPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QComboBox"));
    return clazz.property(qtscript_QComboBox_SizeAdjustPolicy_toStringHelper(value));
}

static void qtscript_QComboBox_SizeAdjustPolicy_fromScriptValue(const QScriptValue &value, QComboBox::SizeAdjustPolicy &out)
{
    out = qvariant_cast<QComboBox::SizeAdjustPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_QComboBox_SizeAdjustPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QComboBox_metaObject();
    int idx = meta->indexOfEnumerator("SizeAdjustPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QComboBox::SizeAdjustPolicy>(arg));
    return context->throwError(QString::fromLatin1("SizeAdjustPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QComboBox_SizeAdjustPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QComboBox::SizeAdjustPolicy value = qscriptvalue_cast<QComboBox::SizeAdjustPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QComboBox_SizeAdjustPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    QComboBox::SizeAdjustPolicy value = qscriptvalue_cast<QComboBox::SizeAdjustPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_QComboBox_SizeAdjustPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_QComboBox_SizeAdjustPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QComboBox_SizeAdjustPolicy,
        qtscript_QComboBox_SizeAdjustPolicy_valueOf, qtscript_QComboBox_SizeAdjustPolicy_toString);
    qScriptRegisterMetaType<QComboBox::SizeAdjustPolicy>(engine, qtscript_QComboBox_SizeAdjustPolicy_toScriptValue,
        qtscript_QComboBox_SizeAdjustPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QComboBox_SizeAdjustPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QComboBox_SizeAdjustPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QComboBox
//

static QScriptValue qtscript_QComboBox_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 32;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QComboBox* _q_self = qscriptvalue_cast<QComboBox*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QComboBox.%0(): this object is not a QComboBox")
            .arg(qtscript_QComboBox_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->addItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QIcon>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            _q_self->addItem(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && true) {
            QString _q_arg0 = context->argument(0).toString();
            QVariant _q_arg1 = context->argument(1).toVariant();
            _q_self->addItem(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QVariant _q_arg2 = context->argument(2).toVariant();
        _q_self->addItem(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->addItems(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QCompleter* _q_result = _q_self->completer();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        int _q_result = _q_self->findData(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->findData(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        int _q_arg1 = context->argument(1).toInt32();
        QFlags<Qt::MatchFlag> _q_arg2 = qscriptvalue_cast<QFlags<Qt::MatchFlag> >(context->argument(2));
        int _q_result = _q_self->findData(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->findText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<Qt::MatchFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::MatchFlag> >(context->argument(1));
        int _q_result = _q_self->findText(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->hidePopup();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->insertItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        if (context->argument(0).isNumber()
            && (qMetaTypeId<QIcon>() == context->argument(1).toVariant().userType())
            && context->argument(2).isString()) {
            int _q_arg0 = context->argument(0).toInt32();
            QIcon _q_arg1 = qscriptvalue_cast<QIcon>(context->argument(1));
            QString _q_arg2 = context->argument(2).toString();
            _q_self->insertItem(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isString()
            && true) {
            int _q_arg0 = context->argument(0).toInt32();
            QString _q_arg1 = context->argument(1).toString();
            QVariant _q_arg2 = context->argument(2).toVariant();
            _q_self->insertItem(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        QIcon _q_arg1 = qscriptvalue_cast<QIcon>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        QVariant _q_arg3 = context->argument(3).toVariant();
        _q_self->insertItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QStringList _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        _q_self->insertItems(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->insertSeparator(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_result = _q_self->itemData(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QVariant _q_result = _q_self->itemData(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QAbstractItemDelegate* _q_result = _q_self->itemDelegate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QIcon _q_result = _q_self->itemIcon(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->itemText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QLineEdit* _q_result = _q_self->lineEdit();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QAbstractItemModel* _q_result = _q_self->model();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->removeItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QModelIndex _q_result = _q_self->rootModelIndex();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QCompleter* _q_arg0 = qscriptvalue_cast<QCompleter*>(context->argument(0));
        _q_self->setCompleter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setItemData(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_arg1 = context->argument(1).toVariant();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->setItemData(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QAbstractItemDelegate* _q_arg0 = qscriptvalue_cast<QAbstractItemDelegate*>(context->argument(0));
        _q_self->setItemDelegate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QIcon _q_arg1 = qscriptvalue_cast<QIcon>(context->argument(1));
        _q_self->setItemIcon(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setItemText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QLineEdit* _q_arg0 = qscriptvalue_cast<QLineEdit*>(context->argument(0));
        _q_self->setLineEdit(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QAbstractItemModel* _q_arg0 = qscriptvalue_cast<QAbstractItemModel*>(context->argument(0));
        _q_self->setModel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        _q_self->setRootModelIndex(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QValidator* _q_arg0 = qscriptvalue_cast<QValidator*>(context->argument(0));
        _q_self->setValidator(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QAbstractItemView* _q_arg0 = qscriptvalue_cast<QAbstractItemView*>(context->argument(0));
        _q_self->setView(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        _q_self->showPopup();
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        QValidator* _q_result = const_cast<QValidator*>(_q_self->validator());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        QAbstractItemView* _q_result = _q_self->view();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32: {
    QString result = QString::fromLatin1("QComboBox");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QComboBox_throw_ambiguity_error_helper(context,
        qtscript_QComboBox_function_names[_id+1],
        qtscript_QComboBox_function_signatures[_id+1]);
}

static QScriptValue qtscript_QComboBox_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QComboBox(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QComboBox* _q_cpp_result = new QtScriptShell_QComboBox();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QComboBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QComboBox* _q_cpp_result = new QtScriptShell_QComboBox(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QComboBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QComboBox_throw_ambiguity_error_helper(context,
        qtscript_QComboBox_function_names[_id],
        qtscript_QComboBox_function_signatures[_id]);
}

static QScriptValue qtscript_QComboBox_toScriptValue(QScriptEngine *engine, QComboBox* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QComboBox_fromScriptValue(const QScriptValue &value, QComboBox* &out)
{
    out = qobject_cast<QComboBox*>(value.toQObject());
}

QScriptValue qtscript_create_QComboBox_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QComboBox*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QComboBox*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 33; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QComboBox_prototype_call, qtscript_QComboBox_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QComboBox_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QComboBox*>(engine, qtscript_QComboBox_toScriptValue, 
        qtscript_QComboBox_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QComboBox_static_call, proto, qtscript_QComboBox_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("InsertPolicy"),
        qtscript_create_QComboBox_InsertPolicy_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SizeAdjustPolicy"),
        qtscript_create_QComboBox_SizeAdjustPolicy_class(engine, ctor));
    return ctor;
}
