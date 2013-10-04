#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractitemview.h>
#include <QVariant>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
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

#include "qtscriptshell_QAbstractItemView.h"

static const char * const qtscript_QAbstractItemView_function_names[] = {
    "QAbstractItemView"
    // static
    // prototype
    , "closePersistentEditor"
    , "currentIndex"
    , "indexAt"
    , "indexWidget"
    , "itemDelegate"
    , "itemDelegateForColumn"
    , "itemDelegateForRow"
    , "keyboardSearch"
    , "model"
    , "openPersistentEditor"
    , "rootIndex"
    , "scrollTo"
    , "selectionModel"
    , "setIndexWidget"
    , "setItemDelegate"
    , "setItemDelegateForColumn"
    , "setItemDelegateForRow"
    , "setModel"
    , "setSelectionModel"
    , "sizeHintForColumn"
    , "sizeHintForIndex"
    , "sizeHintForRow"
    , "visualRect"
    , "toString"
};

static const char * const qtscript_QAbstractItemView_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "QModelIndex index"
    , ""
    , "QPoint point"
    , "QModelIndex index"
    , "\nQModelIndex index"
    , "int column"
    , "int row"
    , "String search"
    , ""
    , "QModelIndex index"
    , ""
    , "QModelIndex index, ScrollHint hint"
    , ""
    , "QModelIndex index, QWidget widget"
    , "QAbstractItemDelegate delegate"
    , "int column, QAbstractItemDelegate delegate"
    , "int row, QAbstractItemDelegate delegate"
    , "QAbstractItemModel model"
    , "QItemSelectionModel selectionModel"
    , "int column"
    , "QModelIndex index"
    , "int row"
    , "QModelIndex index"
""
};

static const int qtscript_QAbstractItemView_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 1
    , 0
    , 2
    , 0
    , 2
    , 1
    , 2
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QAbstractItemView_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractItemView::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QAbstractItemView_metaObject()
{
    return &QAbstractItemView::staticMetaObject;
}

Q_DECLARE_METATYPE(QAbstractItemView*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractItemView*)
Q_DECLARE_METATYPE(QAbstractItemView::DragDropMode)
Q_DECLARE_METATYPE(QAbstractItemView::SelectionBehavior)
Q_DECLARE_METATYPE(QAbstractItemView::EditTrigger)
Q_DECLARE_METATYPE(QFlags<QAbstractItemView::EditTrigger>)
Q_DECLARE_METATYPE(QAbstractItemView::ScrollMode)
Q_DECLARE_METATYPE(QAbstractItemView::ScrollHint)
Q_DECLARE_METATYPE(QAbstractItemView::SelectionMode)
Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QAbstractItemDelegate*)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QItemSelectionModel*)
Q_DECLARE_METATYPE(QAbstractScrollArea*)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QAbstractItemView::DragDropMode
//

static const QAbstractItemView::DragDropMode qtscript_QAbstractItemView_DragDropMode_values[] = {
    QAbstractItemView::NoDragDrop
    , QAbstractItemView::DragOnly
    , QAbstractItemView::DropOnly
    , QAbstractItemView::DragDrop
    , QAbstractItemView::InternalMove
};

static const char * const qtscript_QAbstractItemView_DragDropMode_keys[] = {
    "NoDragDrop"
    , "DragOnly"
    , "DropOnly"
    , "DragDrop"
    , "InternalMove"
};

static QString qtscript_QAbstractItemView_DragDropMode_toStringHelper(QAbstractItemView::DragDropMode value)
{
    const QMetaObject *meta = qtscript_QAbstractItemView_metaObject();
    int idx = meta->indexOfEnumerator("DragDropMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractItemView_DragDropMode_toScriptValue(QScriptEngine *engine, const QAbstractItemView::DragDropMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractItemView"));
    return clazz.property(qtscript_QAbstractItemView_DragDropMode_toStringHelper(value));
}

static void qtscript_QAbstractItemView_DragDropMode_fromScriptValue(const QScriptValue &value, QAbstractItemView::DragDropMode &out)
{
    out = qvariant_cast<QAbstractItemView::DragDropMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractItemView_DragDropMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractItemView_metaObject();
    int idx = meta->indexOfEnumerator("DragDropMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractItemView::DragDropMode>(arg));
    return context->throwError(QString::fromLatin1("DragDropMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractItemView_DragDropMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::DragDropMode value = qscriptvalue_cast<QAbstractItemView::DragDropMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractItemView_DragDropMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::DragDropMode value = qscriptvalue_cast<QAbstractItemView::DragDropMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractItemView_DragDropMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractItemView_DragDropMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractItemView_DragDropMode,
        qtscript_QAbstractItemView_DragDropMode_valueOf, qtscript_QAbstractItemView_DragDropMode_toString);
    qScriptRegisterMetaType<QAbstractItemView::DragDropMode>(engine, qtscript_QAbstractItemView_DragDropMode_toScriptValue,
        qtscript_QAbstractItemView_DragDropMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractItemView_DragDropMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractItemView_DragDropMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractItemView::SelectionBehavior
//

static const QAbstractItemView::SelectionBehavior qtscript_QAbstractItemView_SelectionBehavior_values[] = {
    QAbstractItemView::SelectItems
    , QAbstractItemView::SelectRows
    , QAbstractItemView::SelectColumns
};

static const char * const qtscript_QAbstractItemView_SelectionBehavior_keys[] = {
    "SelectItems"
    , "SelectRows"
    , "SelectColumns"
};

static QString qtscript_QAbstractItemView_SelectionBehavior_toStringHelper(QAbstractItemView::SelectionBehavior value)
{
    const QMetaObject *meta = qtscript_QAbstractItemView_metaObject();
    int idx = meta->indexOfEnumerator("SelectionBehavior");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractItemView_SelectionBehavior_toScriptValue(QScriptEngine *engine, const QAbstractItemView::SelectionBehavior &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractItemView"));
    return clazz.property(qtscript_QAbstractItemView_SelectionBehavior_toStringHelper(value));
}

static void qtscript_QAbstractItemView_SelectionBehavior_fromScriptValue(const QScriptValue &value, QAbstractItemView::SelectionBehavior &out)
{
    out = qvariant_cast<QAbstractItemView::SelectionBehavior>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractItemView_SelectionBehavior(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractItemView_metaObject();
    int idx = meta->indexOfEnumerator("SelectionBehavior");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractItemView::SelectionBehavior>(arg));
    return context->throwError(QString::fromLatin1("SelectionBehavior(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractItemView_SelectionBehavior_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::SelectionBehavior value = qscriptvalue_cast<QAbstractItemView::SelectionBehavior>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractItemView_SelectionBehavior_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::SelectionBehavior value = qscriptvalue_cast<QAbstractItemView::SelectionBehavior>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractItemView_SelectionBehavior_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractItemView_SelectionBehavior_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractItemView_SelectionBehavior,
        qtscript_QAbstractItemView_SelectionBehavior_valueOf, qtscript_QAbstractItemView_SelectionBehavior_toString);
    qScriptRegisterMetaType<QAbstractItemView::SelectionBehavior>(engine, qtscript_QAbstractItemView_SelectionBehavior_toScriptValue,
        qtscript_QAbstractItemView_SelectionBehavior_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractItemView_SelectionBehavior_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractItemView_SelectionBehavior_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractItemView::EditTrigger
//

static const QAbstractItemView::EditTrigger qtscript_QAbstractItemView_EditTrigger_values[] = {
    QAbstractItemView::NoEditTriggers
    , QAbstractItemView::CurrentChanged
    , QAbstractItemView::DoubleClicked
    , QAbstractItemView::SelectedClicked
    , QAbstractItemView::EditKeyPressed
    , QAbstractItemView::AnyKeyPressed
    , QAbstractItemView::AllEditTriggers
};

static const char * const qtscript_QAbstractItemView_EditTrigger_keys[] = {
    "NoEditTriggers"
    , "CurrentChanged"
    , "DoubleClicked"
    , "SelectedClicked"
    , "EditKeyPressed"
    , "AnyKeyPressed"
    , "AllEditTriggers"
};

static QString qtscript_QAbstractItemView_EditTrigger_toStringHelper(QAbstractItemView::EditTrigger value)
{
    for (int i = 0; i < 7; ++i) {
        if (qtscript_QAbstractItemView_EditTrigger_values[i] == value)
            return QString::fromLatin1(qtscript_QAbstractItemView_EditTrigger_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QAbstractItemView_EditTrigger_toScriptValue(QScriptEngine *engine, const QAbstractItemView::EditTrigger &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractItemView"));
    return clazz.property(qtscript_QAbstractItemView_EditTrigger_toStringHelper(value));
}

static void qtscript_QAbstractItemView_EditTrigger_fromScriptValue(const QScriptValue &value, QAbstractItemView::EditTrigger &out)
{
    out = qvariant_cast<QAbstractItemView::EditTrigger>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractItemView_EditTrigger(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 7; ++i) {
        if (qtscript_QAbstractItemView_EditTrigger_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QAbstractItemView::EditTrigger>(arg));
    }
    return context->throwError(QString::fromLatin1("EditTrigger(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractItemView_EditTrigger_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::EditTrigger value = qscriptvalue_cast<QAbstractItemView::EditTrigger>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractItemView_EditTrigger_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::EditTrigger value = qscriptvalue_cast<QAbstractItemView::EditTrigger>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractItemView_EditTrigger_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractItemView_EditTrigger_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractItemView_EditTrigger,
        qtscript_QAbstractItemView_EditTrigger_valueOf, qtscript_QAbstractItemView_EditTrigger_toString);
    qScriptRegisterMetaType<QAbstractItemView::EditTrigger>(engine, qtscript_QAbstractItemView_EditTrigger_toScriptValue,
        qtscript_QAbstractItemView_EditTrigger_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractItemView_EditTrigger_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractItemView_EditTrigger_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractItemView::EditTriggers
//

static QScriptValue qtscript_QAbstractItemView_EditTriggers_toScriptValue(QScriptEngine *engine, const QAbstractItemView::EditTriggers &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QAbstractItemView_EditTriggers_fromScriptValue(const QScriptValue &value, QAbstractItemView::EditTriggers &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QAbstractItemView::EditTriggers>())
        out = qvariant_cast<QAbstractItemView::EditTriggers>(var);
    else if (var.userType() == qMetaTypeId<QAbstractItemView::EditTrigger>())
        out = qvariant_cast<QAbstractItemView::EditTrigger>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QAbstractItemView_EditTriggers(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::EditTriggers result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QAbstractItemView::EditTriggers>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QAbstractItemView::EditTrigger>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("EditTriggers(): argument %0 is not of type EditTrigger").arg(i));
            }
            result |= qvariant_cast<QAbstractItemView::EditTrigger>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QAbstractItemView_EditTriggers_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::EditTriggers value = qscriptvalue_cast<QAbstractItemView::EditTriggers>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractItemView_EditTriggers_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::EditTriggers value = qscriptvalue_cast<QAbstractItemView::EditTriggers>(context->thisObject());
    QString result;
    for (int i = 0; i < 7; ++i) {
        if ((value & qtscript_QAbstractItemView_EditTrigger_values[i]) == qtscript_QAbstractItemView_EditTrigger_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QAbstractItemView_EditTrigger_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QAbstractItemView_EditTriggers_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QAbstractItemView::EditTriggers>() == otherObj.value<QAbstractItemView::EditTriggers>())));
}

static QScriptValue qtscript_create_QAbstractItemView_EditTriggers_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QAbstractItemView_EditTriggers, qtscript_QAbstractItemView_EditTriggers_valueOf,
        qtscript_QAbstractItemView_EditTriggers_toString, qtscript_QAbstractItemView_EditTriggers_equals);
    qScriptRegisterMetaType<QAbstractItemView::EditTriggers>(engine, qtscript_QAbstractItemView_EditTriggers_toScriptValue,
        qtscript_QAbstractItemView_EditTriggers_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QAbstractItemView::ScrollMode
//

static const QAbstractItemView::ScrollMode qtscript_QAbstractItemView_ScrollMode_values[] = {
    QAbstractItemView::ScrollPerItem
    , QAbstractItemView::ScrollPerPixel
};

static const char * const qtscript_QAbstractItemView_ScrollMode_keys[] = {
    "ScrollPerItem"
    , "ScrollPerPixel"
};

static QString qtscript_QAbstractItemView_ScrollMode_toStringHelper(QAbstractItemView::ScrollMode value)
{
    const QMetaObject *meta = qtscript_QAbstractItemView_metaObject();
    int idx = meta->indexOfEnumerator("ScrollMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractItemView_ScrollMode_toScriptValue(QScriptEngine *engine, const QAbstractItemView::ScrollMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractItemView"));
    return clazz.property(qtscript_QAbstractItemView_ScrollMode_toStringHelper(value));
}

static void qtscript_QAbstractItemView_ScrollMode_fromScriptValue(const QScriptValue &value, QAbstractItemView::ScrollMode &out)
{
    out = qvariant_cast<QAbstractItemView::ScrollMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractItemView_ScrollMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractItemView_metaObject();
    int idx = meta->indexOfEnumerator("ScrollMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractItemView::ScrollMode>(arg));
    return context->throwError(QString::fromLatin1("ScrollMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractItemView_ScrollMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::ScrollMode value = qscriptvalue_cast<QAbstractItemView::ScrollMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractItemView_ScrollMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::ScrollMode value = qscriptvalue_cast<QAbstractItemView::ScrollMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractItemView_ScrollMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractItemView_ScrollMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractItemView_ScrollMode,
        qtscript_QAbstractItemView_ScrollMode_valueOf, qtscript_QAbstractItemView_ScrollMode_toString);
    qScriptRegisterMetaType<QAbstractItemView::ScrollMode>(engine, qtscript_QAbstractItemView_ScrollMode_toScriptValue,
        qtscript_QAbstractItemView_ScrollMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractItemView_ScrollMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractItemView_ScrollMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractItemView::ScrollHint
//

static const QAbstractItemView::ScrollHint qtscript_QAbstractItemView_ScrollHint_values[] = {
    QAbstractItemView::EnsureVisible
    , QAbstractItemView::PositionAtTop
    , QAbstractItemView::PositionAtBottom
    , QAbstractItemView::PositionAtCenter
};

static const char * const qtscript_QAbstractItemView_ScrollHint_keys[] = {
    "EnsureVisible"
    , "PositionAtTop"
    , "PositionAtBottom"
    , "PositionAtCenter"
};

static QString qtscript_QAbstractItemView_ScrollHint_toStringHelper(QAbstractItemView::ScrollHint value)
{
    const QMetaObject *meta = qtscript_QAbstractItemView_metaObject();
    int idx = meta->indexOfEnumerator("ScrollHint");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractItemView_ScrollHint_toScriptValue(QScriptEngine *engine, const QAbstractItemView::ScrollHint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractItemView"));
    return clazz.property(qtscript_QAbstractItemView_ScrollHint_toStringHelper(value));
}

static void qtscript_QAbstractItemView_ScrollHint_fromScriptValue(const QScriptValue &value, QAbstractItemView::ScrollHint &out)
{
    out = qvariant_cast<QAbstractItemView::ScrollHint>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractItemView_ScrollHint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractItemView_metaObject();
    int idx = meta->indexOfEnumerator("ScrollHint");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractItemView::ScrollHint>(arg));
    return context->throwError(QString::fromLatin1("ScrollHint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractItemView_ScrollHint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::ScrollHint value = qscriptvalue_cast<QAbstractItemView::ScrollHint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractItemView_ScrollHint_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::ScrollHint value = qscriptvalue_cast<QAbstractItemView::ScrollHint>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractItemView_ScrollHint_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractItemView_ScrollHint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractItemView_ScrollHint,
        qtscript_QAbstractItemView_ScrollHint_valueOf, qtscript_QAbstractItemView_ScrollHint_toString);
    qScriptRegisterMetaType<QAbstractItemView::ScrollHint>(engine, qtscript_QAbstractItemView_ScrollHint_toScriptValue,
        qtscript_QAbstractItemView_ScrollHint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractItemView_ScrollHint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractItemView_ScrollHint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractItemView::SelectionMode
//

static const QAbstractItemView::SelectionMode qtscript_QAbstractItemView_SelectionMode_values[] = {
    QAbstractItemView::NoSelection
    , QAbstractItemView::SingleSelection
    , QAbstractItemView::MultiSelection
    , QAbstractItemView::ExtendedSelection
    , QAbstractItemView::ContiguousSelection
};

static const char * const qtscript_QAbstractItemView_SelectionMode_keys[] = {
    "NoSelection"
    , "SingleSelection"
    , "MultiSelection"
    , "ExtendedSelection"
    , "ContiguousSelection"
};

static QString qtscript_QAbstractItemView_SelectionMode_toStringHelper(QAbstractItemView::SelectionMode value)
{
    const QMetaObject *meta = qtscript_QAbstractItemView_metaObject();
    int idx = meta->indexOfEnumerator("SelectionMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QAbstractItemView_SelectionMode_toScriptValue(QScriptEngine *engine, const QAbstractItemView::SelectionMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractItemView"));
    return clazz.property(qtscript_QAbstractItemView_SelectionMode_toStringHelper(value));
}

static void qtscript_QAbstractItemView_SelectionMode_fromScriptValue(const QScriptValue &value, QAbstractItemView::SelectionMode &out)
{
    out = qvariant_cast<QAbstractItemView::SelectionMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractItemView_SelectionMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QAbstractItemView_metaObject();
    int idx = meta->indexOfEnumerator("SelectionMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QAbstractItemView::SelectionMode>(arg));
    return context->throwError(QString::fromLatin1("SelectionMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractItemView_SelectionMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::SelectionMode value = qscriptvalue_cast<QAbstractItemView::SelectionMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractItemView_SelectionMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractItemView::SelectionMode value = qscriptvalue_cast<QAbstractItemView::SelectionMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractItemView_SelectionMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractItemView_SelectionMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractItemView_SelectionMode,
        qtscript_QAbstractItemView_SelectionMode_valueOf, qtscript_QAbstractItemView_SelectionMode_toString);
    qScriptRegisterMetaType<QAbstractItemView::SelectionMode>(engine, qtscript_QAbstractItemView_SelectionMode_toScriptValue,
        qtscript_QAbstractItemView_SelectionMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractItemView_SelectionMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractItemView_SelectionMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractItemView
//

static QScriptValue qtscript_QAbstractItemView_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 23;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractItemView* _q_self = qscriptvalue_cast<QAbstractItemView*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractItemView.%0(): this object is not a QAbstractItemView")
            .arg(qtscript_QAbstractItemView_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        _q_self->closePersistentEditor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QModelIndex _q_result = _q_self->currentIndex();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QModelIndex _q_result = _q_self->indexAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QWidget* _q_result = _q_self->indexWidget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QAbstractItemDelegate* _q_result = _q_self->itemDelegate();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QAbstractItemDelegate* _q_result = _q_self->itemDelegate(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QAbstractItemDelegate* _q_result = _q_self->itemDelegateForColumn(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QAbstractItemDelegate* _q_result = _q_self->itemDelegateForRow(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->keyboardSearch(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QAbstractItemModel* _q_result = _q_self->model();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        _q_self->openPersistentEditor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QModelIndex _q_result = _q_self->rootIndex();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        _q_self->scrollTo(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QAbstractItemView::ScrollHint _q_arg1 = qscriptvalue_cast<QAbstractItemView::ScrollHint>(context->argument(1));
        _q_self->scrollTo(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QItemSelectionModel* _q_result = _q_self->selectionModel();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        _q_self->setIndexWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QAbstractItemDelegate* _q_arg0 = qscriptvalue_cast<QAbstractItemDelegate*>(context->argument(0));
        _q_self->setItemDelegate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QAbstractItemDelegate* _q_arg1 = qscriptvalue_cast<QAbstractItemDelegate*>(context->argument(1));
        _q_self->setItemDelegateForColumn(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QAbstractItemDelegate* _q_arg1 = qscriptvalue_cast<QAbstractItemDelegate*>(context->argument(1));
        _q_self->setItemDelegateForRow(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QAbstractItemModel* _q_arg0 = qscriptvalue_cast<QAbstractItemModel*>(context->argument(0));
        _q_self->setModel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QItemSelectionModel* _q_arg0 = qscriptvalue_cast<QItemSelectionModel*>(context->argument(0));
        _q_self->setSelectionModel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->sizeHintForColumn(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QSize _q_result = _q_self->sizeHintForIndex(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->sizeHintForRow(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QRect _q_result = _q_self->visualRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23: {
    QString result = QString::fromLatin1("QAbstractItemView");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractItemView_throw_ambiguity_error_helper(context,
        qtscript_QAbstractItemView_function_names[_id+1],
        qtscript_QAbstractItemView_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractItemView_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractItemView(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractItemView* _q_cpp_result = new QtScriptShell_QAbstractItemView();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractItemView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QAbstractItemView* _q_cpp_result = new QtScriptShell_QAbstractItemView(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractItemView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractItemView_throw_ambiguity_error_helper(context,
        qtscript_QAbstractItemView_function_names[_id],
        qtscript_QAbstractItemView_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractItemView_toScriptValue(QScriptEngine *engine, QAbstractItemView* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractItemView_fromScriptValue(const QScriptValue &value, QAbstractItemView* &out)
{
    out = qobject_cast<QAbstractItemView*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractItemView_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractItemView*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractItemView*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractScrollArea*>()));
    for (int i = 0; i < 24; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractItemView_prototype_call, qtscript_QAbstractItemView_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractItemView_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractItemView*>(engine, qtscript_QAbstractItemView_toScriptValue, 
        qtscript_QAbstractItemView_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractItemView_static_call, proto, qtscript_QAbstractItemView_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("DragDropMode"),
        qtscript_create_QAbstractItemView_DragDropMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SelectionBehavior"),
        qtscript_create_QAbstractItemView_SelectionBehavior_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("EditTrigger"),
        qtscript_create_QAbstractItemView_EditTrigger_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("EditTriggers"),
        qtscript_create_QAbstractItemView_EditTriggers_class(engine));
    ctor.setProperty(QString::fromLatin1("ScrollMode"),
        qtscript_create_QAbstractItemView_ScrollMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ScrollHint"),
        qtscript_create_QAbstractItemView_ScrollHint_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SelectionMode"),
        qtscript_create_QAbstractItemView_SelectionMode_class(engine, ctor));
    return ctor;
}
