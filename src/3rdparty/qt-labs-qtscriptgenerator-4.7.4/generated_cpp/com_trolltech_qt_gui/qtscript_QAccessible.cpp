#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qaccessible.h>
#include <QVariant>
#include <qaccessible.h>
#include <qobject.h>

#include "qtscriptshell_QAccessible.h"

static const char * const qtscript_QAccessible_function_names[] = {
    "QAccessible"
    // static
    , "isActive"
    , "queryAccessibleInterface"
    , "setRootObject"
    , "updateAccessibility"
    // prototype
    , "toString"
};

static const char * const qtscript_QAccessible_function_signatures[] = {
    ""
    // static
    , ""
    , "QObject arg__1"
    , "QObject arg__1"
    , "QObject arg__1, int who, Event reason"
    // prototype
""
};

static const int qtscript_QAccessible_function_lengths[] = {
    0
    // static
    , 0
    , 1
    , 1
    , 3
    // prototype
    , 0
};

static QScriptValue qtscript_QAccessible_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAccessible::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAccessible*)
Q_DECLARE_METATYPE(QtScriptShell_QAccessible*)
Q_DECLARE_METATYPE(QAccessible::Method)
Q_DECLARE_METATYPE(QAccessible::Role)
Q_DECLARE_METATYPE(QAccessible::Action)
Q_DECLARE_METATYPE(QAccessible::Event)
Q_DECLARE_METATYPE(QAccessible::RelationFlag)
Q_DECLARE_METATYPE(QFlags<QAccessible::RelationFlag>)
Q_DECLARE_METATYPE(QAccessible::StateFlag)
Q_DECLARE_METATYPE(QFlags<QAccessible::StateFlag>)
Q_DECLARE_METATYPE(QAccessible::Text)
Q_DECLARE_METATYPE(QAccessibleInterface*)

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
// QAccessible::Method
//

static const QAccessible::Method qtscript_QAccessible_Method_values[] = {
    QAccessible::ListSupportedMethods
    , QAccessible::SetCursorPosition
    , QAccessible::GetCursorPosition
    , QAccessible::ForegroundColor
    , QAccessible::BackgroundColor
};

static const char * const qtscript_QAccessible_Method_keys[] = {
    "ListSupportedMethods"
    , "SetCursorPosition"
    , "GetCursorPosition"
    , "ForegroundColor"
    , "BackgroundColor"
};

static QString qtscript_QAccessible_Method_toStringHelper(QAccessible::Method value)
{
    if ((value >= QAccessible::ListSupportedMethods) && (value <= QAccessible::BackgroundColor))
        return qtscript_QAccessible_Method_keys[static_cast<int>(value)-static_cast<int>(QAccessible::ListSupportedMethods)];
    return QString();
}

static QScriptValue qtscript_QAccessible_Method_toScriptValue(QScriptEngine *engine, const QAccessible::Method &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_Method_toStringHelper(value));
}

static void qtscript_QAccessible_Method_fromScriptValue(const QScriptValue &value, QAccessible::Method &out)
{
    out = qvariant_cast<QAccessible::Method>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_Method(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAccessible::ListSupportedMethods) && (arg <= QAccessible::BackgroundColor))
        return qScriptValueFromValue(engine,  static_cast<QAccessible::Method>(arg));
    return context->throwError(QString::fromLatin1("Method(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_Method_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Method value = qscriptvalue_cast<QAccessible::Method>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_Method_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Method value = qscriptvalue_cast<QAccessible::Method>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_Method_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_Method_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_Method,
        qtscript_QAccessible_Method_valueOf, qtscript_QAccessible_Method_toString);
    qScriptRegisterMetaType<QAccessible::Method>(engine, qtscript_QAccessible_Method_toScriptValue,
        qtscript_QAccessible_Method_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_Method_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_Method_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible::Role
//

static const QAccessible::Role qtscript_QAccessible_Role_values[] = {
    QAccessible::NoRole
    , QAccessible::TitleBar
    , QAccessible::MenuBar
    , QAccessible::ScrollBar
    , QAccessible::Grip
    , QAccessible::Sound
    , QAccessible::Cursor
    , QAccessible::Caret
    , QAccessible::AlertMessage
    , QAccessible::Window
    , QAccessible::Client
    , QAccessible::PopupMenu
    , QAccessible::MenuItem
    , QAccessible::ToolTip
    , QAccessible::Application
    , QAccessible::Document
    , QAccessible::Pane
    , QAccessible::Chart
    , QAccessible::Dialog
    , QAccessible::Border
    , QAccessible::Grouping
    , QAccessible::Separator
    , QAccessible::ToolBar
    , QAccessible::StatusBar
    , QAccessible::Table
    , QAccessible::ColumnHeader
    , QAccessible::RowHeader
    , QAccessible::Column
    , QAccessible::Row
    , QAccessible::Cell
    , QAccessible::Link
    , QAccessible::HelpBalloon
    , QAccessible::Assistant
    , QAccessible::List
    , QAccessible::ListItem
    , QAccessible::Tree
    , QAccessible::TreeItem
    , QAccessible::PageTab
    , QAccessible::PropertyPage
    , QAccessible::Indicator
    , QAccessible::Graphic
    , QAccessible::StaticText
    , QAccessible::EditableText
    , QAccessible::PushButton
    , QAccessible::CheckBox
    , QAccessible::RadioButton
    , QAccessible::ComboBox
    , QAccessible::ProgressBar
    , QAccessible::Dial
    , QAccessible::HotkeyField
    , QAccessible::Slider
    , QAccessible::SpinBox
    , QAccessible::Canvas
    , QAccessible::Animation
    , QAccessible::Equation
    , QAccessible::ButtonDropDown
    , QAccessible::ButtonMenu
    , QAccessible::ButtonDropGrid
    , QAccessible::Whitespace
    , QAccessible::PageTabList
    , QAccessible::Clock
    , QAccessible::Splitter
    , QAccessible::LayeredPane
    , QAccessible::UserRole
};

static const char * const qtscript_QAccessible_Role_keys[] = {
    "NoRole"
    , "TitleBar"
    , "MenuBar"
    , "ScrollBar"
    , "Grip"
    , "Sound"
    , "Cursor"
    , "Caret"
    , "AlertMessage"
    , "Window"
    , "Client"
    , "PopupMenu"
    , "MenuItem"
    , "ToolTip"
    , "Application"
    , "Document"
    , "Pane"
    , "Chart"
    , "Dialog"
    , "Border"
    , "Grouping"
    , "Separator"
    , "ToolBar"
    , "StatusBar"
    , "Table"
    , "ColumnHeader"
    , "RowHeader"
    , "Column"
    , "Row"
    , "Cell"
    , "Link"
    , "HelpBalloon"
    , "Assistant"
    , "List"
    , "ListItem"
    , "Tree"
    , "TreeItem"
    , "PageTab"
    , "PropertyPage"
    , "Indicator"
    , "Graphic"
    , "StaticText"
    , "EditableText"
    , "PushButton"
    , "CheckBox"
    , "RadioButton"
    , "ComboBox"
    , "ProgressBar"
    , "Dial"
    , "HotkeyField"
    , "Slider"
    , "SpinBox"
    , "Canvas"
    , "Animation"
    , "Equation"
    , "ButtonDropDown"
    , "ButtonMenu"
    , "ButtonDropGrid"
    , "Whitespace"
    , "PageTabList"
    , "Clock"
    , "Splitter"
    , "LayeredPane"
    , "UserRole"
};

static QString qtscript_QAccessible_Role_toStringHelper(QAccessible::Role value)
{
    for (int i = 0; i < 64; ++i) {
        if (qtscript_QAccessible_Role_values[i] == value)
            return QString::fromLatin1(qtscript_QAccessible_Role_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QAccessible_Role_toScriptValue(QScriptEngine *engine, const QAccessible::Role &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_Role_toStringHelper(value));
}

static void qtscript_QAccessible_Role_fromScriptValue(const QScriptValue &value, QAccessible::Role &out)
{
    out = qvariant_cast<QAccessible::Role>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_Role(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 64; ++i) {
        if (qtscript_QAccessible_Role_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QAccessible::Role>(arg));
    }
    return context->throwError(QString::fromLatin1("Role(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_Role_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Role value = qscriptvalue_cast<QAccessible::Role>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_Role_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Role value = qscriptvalue_cast<QAccessible::Role>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_Role_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_Role_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_Role,
        qtscript_QAccessible_Role_valueOf, qtscript_QAccessible_Role_toString);
    qScriptRegisterMetaType<QAccessible::Role>(engine, qtscript_QAccessible_Role_toScriptValue,
        qtscript_QAccessible_Role_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 64; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_Role_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_Role_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible::Action
//

static const QAccessible::Action qtscript_QAccessible_Action_values[] = {
    QAccessible::AddToSelection
    , QAccessible::ExtendSelection
    , QAccessible::RemoveSelection
    , QAccessible::ClearSelection
    , QAccessible::Select
    , QAccessible::Cancel
    , QAccessible::Accept
    , QAccessible::Decrease
    , QAccessible::Increase
    , QAccessible::SetFocus
    , QAccessible::Press
    , QAccessible::DefaultAction
};

static const char * const qtscript_QAccessible_Action_keys[] = {
    "AddToSelection"
    , "ExtendSelection"
    , "RemoveSelection"
    , "ClearSelection"
    , "Select"
    , "Cancel"
    , "Accept"
    , "Decrease"
    , "Increase"
    , "SetFocus"
    , "Press"
    , "DefaultAction"
};

static QString qtscript_QAccessible_Action_toStringHelper(QAccessible::Action value)
{
    if ((value >= QAccessible::AddToSelection) && (value <= QAccessible::DefaultAction))
        return qtscript_QAccessible_Action_keys[static_cast<int>(value)-static_cast<int>(QAccessible::AddToSelection)];
    return QString();
}

static QScriptValue qtscript_QAccessible_Action_toScriptValue(QScriptEngine *engine, const QAccessible::Action &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_Action_toStringHelper(value));
}

static void qtscript_QAccessible_Action_fromScriptValue(const QScriptValue &value, QAccessible::Action &out)
{
    out = qvariant_cast<QAccessible::Action>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_Action(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAccessible::AddToSelection) && (arg <= QAccessible::DefaultAction))
        return qScriptValueFromValue(engine,  static_cast<QAccessible::Action>(arg));
    return context->throwError(QString::fromLatin1("Action(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_Action_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Action value = qscriptvalue_cast<QAccessible::Action>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_Action_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Action value = qscriptvalue_cast<QAccessible::Action>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_Action_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_Action_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_Action,
        qtscript_QAccessible_Action_valueOf, qtscript_QAccessible_Action_toString);
    qScriptRegisterMetaType<QAccessible::Action>(engine, qtscript_QAccessible_Action_toScriptValue,
        qtscript_QAccessible_Action_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 12; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_Action_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_Action_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible::Event
//

static const QAccessible::Event qtscript_QAccessible_Event_values[] = {
    QAccessible::SoundPlayed
    , QAccessible::Alert
    , QAccessible::ForegroundChanged
    , QAccessible::MenuStart
    , QAccessible::MenuEnd
    , QAccessible::PopupMenuStart
    , QAccessible::PopupMenuEnd
    , QAccessible::ContextHelpStart
    , QAccessible::ContextHelpEnd
    , QAccessible::DragDropStart
    , QAccessible::DragDropEnd
    , QAccessible::DialogStart
    , QAccessible::DialogEnd
    , QAccessible::ScrollingStart
    , QAccessible::ScrollingEnd
    , QAccessible::MenuCommand
    , QAccessible::ObjectCreated
    , QAccessible::ObjectDestroyed
    , QAccessible::ObjectShow
    , QAccessible::ObjectHide
    , QAccessible::ObjectReorder
    , QAccessible::Focus
    , QAccessible::Selection
    , QAccessible::SelectionAdd
    , QAccessible::SelectionRemove
    , QAccessible::SelectionWithin
    , QAccessible::StateChanged
    , QAccessible::LocationChanged
    , QAccessible::NameChanged
    , QAccessible::DescriptionChanged
    , QAccessible::ValueChanged
    , QAccessible::ParentChanged
    , QAccessible::HelpChanged
    , QAccessible::DefaultActionChanged
    , QAccessible::AcceleratorChanged
};

static const char * const qtscript_QAccessible_Event_keys[] = {
    "SoundPlayed"
    , "Alert"
    , "ForegroundChanged"
    , "MenuStart"
    , "MenuEnd"
    , "PopupMenuStart"
    , "PopupMenuEnd"
    , "ContextHelpStart"
    , "ContextHelpEnd"
    , "DragDropStart"
    , "DragDropEnd"
    , "DialogStart"
    , "DialogEnd"
    , "ScrollingStart"
    , "ScrollingEnd"
    , "MenuCommand"
    , "ObjectCreated"
    , "ObjectDestroyed"
    , "ObjectShow"
    , "ObjectHide"
    , "ObjectReorder"
    , "Focus"
    , "Selection"
    , "SelectionAdd"
    , "SelectionRemove"
    , "SelectionWithin"
    , "StateChanged"
    , "LocationChanged"
    , "NameChanged"
    , "DescriptionChanged"
    , "ValueChanged"
    , "ParentChanged"
    , "HelpChanged"
    , "DefaultActionChanged"
    , "AcceleratorChanged"
};

static QString qtscript_QAccessible_Event_toStringHelper(QAccessible::Event value)
{
    for (int i = 0; i < 35; ++i) {
        if (qtscript_QAccessible_Event_values[i] == value)
            return QString::fromLatin1(qtscript_QAccessible_Event_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QAccessible_Event_toScriptValue(QScriptEngine *engine, const QAccessible::Event &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_Event_toStringHelper(value));
}

static void qtscript_QAccessible_Event_fromScriptValue(const QScriptValue &value, QAccessible::Event &out)
{
    out = qvariant_cast<QAccessible::Event>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_Event(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 35; ++i) {
        if (qtscript_QAccessible_Event_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QAccessible::Event>(arg));
    }
    return context->throwError(QString::fromLatin1("Event(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_Event_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Event value = qscriptvalue_cast<QAccessible::Event>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_Event_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Event value = qscriptvalue_cast<QAccessible::Event>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_Event_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_Event_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_Event,
        qtscript_QAccessible_Event_valueOf, qtscript_QAccessible_Event_toString);
    qScriptRegisterMetaType<QAccessible::Event>(engine, qtscript_QAccessible_Event_toScriptValue,
        qtscript_QAccessible_Event_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 35; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_Event_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_Event_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible::RelationFlag
//

static const QAccessible::RelationFlag qtscript_QAccessible_RelationFlag_values[] = {
    QAccessible::Unrelated
    , QAccessible::Self
    , QAccessible::Ancestor
    , QAccessible::Child
    , QAccessible::Descendent
    , QAccessible::Sibling
    , QAccessible::HierarchyMask
    , QAccessible::Up
    , QAccessible::Down
    , QAccessible::Left
    , QAccessible::Right
    , QAccessible::Covers
    , QAccessible::Covered
    , QAccessible::GeometryMask
    , QAccessible::FocusChild
    , QAccessible::Label
    , QAccessible::Labelled
    , QAccessible::Controller
    , QAccessible::Controlled
    , QAccessible::LogicalMask
};

static const char * const qtscript_QAccessible_RelationFlag_keys[] = {
    "Unrelated"
    , "Self"
    , "Ancestor"
    , "Child"
    , "Descendent"
    , "Sibling"
    , "HierarchyMask"
    , "Up"
    , "Down"
    , "Left"
    , "Right"
    , "Covers"
    , "Covered"
    , "GeometryMask"
    , "FocusChild"
    , "Label"
    , "Labelled"
    , "Controller"
    , "Controlled"
    , "LogicalMask"
};

static QString qtscript_QAccessible_RelationFlag_toStringHelper(QAccessible::RelationFlag value)
{
    for (int i = 0; i < 20; ++i) {
        if (qtscript_QAccessible_RelationFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QAccessible_RelationFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QAccessible_RelationFlag_toScriptValue(QScriptEngine *engine, const QAccessible::RelationFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_RelationFlag_toStringHelper(value));
}

static void qtscript_QAccessible_RelationFlag_fromScriptValue(const QScriptValue &value, QAccessible::RelationFlag &out)
{
    out = qvariant_cast<QAccessible::RelationFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_RelationFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 20; ++i) {
        if (qtscript_QAccessible_RelationFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QAccessible::RelationFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("RelationFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_RelationFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::RelationFlag value = qscriptvalue_cast<QAccessible::RelationFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_RelationFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::RelationFlag value = qscriptvalue_cast<QAccessible::RelationFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_RelationFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_RelationFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_RelationFlag,
        qtscript_QAccessible_RelationFlag_valueOf, qtscript_QAccessible_RelationFlag_toString);
    qScriptRegisterMetaType<QAccessible::RelationFlag>(engine, qtscript_QAccessible_RelationFlag_toScriptValue,
        qtscript_QAccessible_RelationFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 20; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_RelationFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_RelationFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible::Relation
//

static QScriptValue qtscript_QAccessible_Relation_toScriptValue(QScriptEngine *engine, const QAccessible::Relation &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QAccessible_Relation_fromScriptValue(const QScriptValue &value, QAccessible::Relation &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QAccessible::Relation>())
        out = qvariant_cast<QAccessible::Relation>(var);
    else if (var.userType() == qMetaTypeId<QAccessible::RelationFlag>())
        out = qvariant_cast<QAccessible::RelationFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QAccessible_Relation(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Relation result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QAccessible::Relation>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QAccessible::RelationFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("Relation(): argument %0 is not of type RelationFlag").arg(i));
            }
            result |= qvariant_cast<QAccessible::RelationFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QAccessible_Relation_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Relation value = qscriptvalue_cast<QAccessible::Relation>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_Relation_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Relation value = qscriptvalue_cast<QAccessible::Relation>(context->thisObject());
    QString result;
    for (int i = 0; i < 20; ++i) {
        if ((value & qtscript_QAccessible_RelationFlag_values[i]) == qtscript_QAccessible_RelationFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QAccessible_RelationFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QAccessible_Relation_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QAccessible::Relation>() == otherObj.value<QAccessible::Relation>())));
}

static QScriptValue qtscript_create_QAccessible_Relation_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QAccessible_Relation, qtscript_QAccessible_Relation_valueOf,
        qtscript_QAccessible_Relation_toString, qtscript_QAccessible_Relation_equals);
    qScriptRegisterMetaType<QAccessible::Relation>(engine, qtscript_QAccessible_Relation_toScriptValue,
        qtscript_QAccessible_Relation_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QAccessible::StateFlag
//

static const QAccessible::StateFlag qtscript_QAccessible_StateFlag_values[] = {
    QAccessible::Modal
    , QAccessible::Normal
    , QAccessible::Unavailable
    , QAccessible::Selected
    , QAccessible::Focused
    , QAccessible::Pressed
    , QAccessible::Checked
    , QAccessible::Mixed
    , QAccessible::ReadOnly
    , QAccessible::HotTracked
    , QAccessible::DefaultButton
    , QAccessible::Expanded
    , QAccessible::Collapsed
    , QAccessible::Busy
    , QAccessible::Marqueed
    , QAccessible::Animated
    , QAccessible::Invisible
    , QAccessible::Offscreen
    , QAccessible::Sizeable
    , QAccessible::Movable
    , QAccessible::SelfVoicing
    , QAccessible::Focusable
    , QAccessible::Selectable
    , QAccessible::Linked
    , QAccessible::Traversed
    , QAccessible::MultiSelectable
    , QAccessible::ExtSelectable
    , QAccessible::HasInvokeExtension
    , QAccessible::Protected
    , QAccessible::HasPopup
};

static const char * const qtscript_QAccessible_StateFlag_keys[] = {
    "Modal"
    , "Normal"
    , "Unavailable"
    , "Selected"
    , "Focused"
    , "Pressed"
    , "Checked"
    , "Mixed"
    , "ReadOnly"
    , "HotTracked"
    , "DefaultButton"
    , "Expanded"
    , "Collapsed"
    , "Busy"
    , "Marqueed"
    , "Animated"
    , "Invisible"
    , "Offscreen"
    , "Sizeable"
    , "Movable"
    , "SelfVoicing"
    , "Focusable"
    , "Selectable"
    , "Linked"
    , "Traversed"
    , "MultiSelectable"
    , "ExtSelectable"
    , "HasInvokeExtension"
    , "Protected"
    , "HasPopup"
};

static QString qtscript_QAccessible_StateFlag_toStringHelper(QAccessible::StateFlag value)
{
    for (int i = 0; i < 30; ++i) {
        if (qtscript_QAccessible_StateFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QAccessible_StateFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QAccessible_StateFlag_toScriptValue(QScriptEngine *engine, const QAccessible::StateFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_StateFlag_toStringHelper(value));
}

static void qtscript_QAccessible_StateFlag_fromScriptValue(const QScriptValue &value, QAccessible::StateFlag &out)
{
    out = qvariant_cast<QAccessible::StateFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_StateFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 30; ++i) {
        if (qtscript_QAccessible_StateFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QAccessible::StateFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("StateFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_StateFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::StateFlag value = qscriptvalue_cast<QAccessible::StateFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_StateFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::StateFlag value = qscriptvalue_cast<QAccessible::StateFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_StateFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_StateFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_StateFlag,
        qtscript_QAccessible_StateFlag_valueOf, qtscript_QAccessible_StateFlag_toString);
    qScriptRegisterMetaType<QAccessible::StateFlag>(engine, qtscript_QAccessible_StateFlag_toScriptValue,
        qtscript_QAccessible_StateFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 30; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_StateFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_StateFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible::State
//

static QScriptValue qtscript_QAccessible_State_toScriptValue(QScriptEngine *engine, const QAccessible::State &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QAccessible_State_fromScriptValue(const QScriptValue &value, QAccessible::State &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QAccessible::State>())
        out = qvariant_cast<QAccessible::State>(var);
    else if (var.userType() == qMetaTypeId<QAccessible::StateFlag>())
        out = qvariant_cast<QAccessible::StateFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QAccessible_State(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::State result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QAccessible::State>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QAccessible::StateFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("State(): argument %0 is not of type StateFlag").arg(i));
            }
            result |= qvariant_cast<QAccessible::StateFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QAccessible_State_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::State value = qscriptvalue_cast<QAccessible::State>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_State_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::State value = qscriptvalue_cast<QAccessible::State>(context->thisObject());
    QString result;
    for (int i = 0; i < 30; ++i) {
        if ((value & qtscript_QAccessible_StateFlag_values[i]) == qtscript_QAccessible_StateFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QAccessible_StateFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QAccessible_State_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QAccessible::State>() == otherObj.value<QAccessible::State>())));
}

static QScriptValue qtscript_create_QAccessible_State_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QAccessible_State, qtscript_QAccessible_State_valueOf,
        qtscript_QAccessible_State_toString, qtscript_QAccessible_State_equals);
    qScriptRegisterMetaType<QAccessible::State>(engine, qtscript_QAccessible_State_toScriptValue,
        qtscript_QAccessible_State_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QAccessible::Text
//

static const QAccessible::Text qtscript_QAccessible_Text_values[] = {
    QAccessible::Name
    , QAccessible::Description
    , QAccessible::Value
    , QAccessible::Help
    , QAccessible::Accelerator
    , QAccessible::UserText
};

static const char * const qtscript_QAccessible_Text_keys[] = {
    "Name"
    , "Description"
    , "Value"
    , "Help"
    , "Accelerator"
    , "UserText"
};

static QString qtscript_QAccessible_Text_toStringHelper(QAccessible::Text value)
{
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QAccessible_Text_values[i] == value)
            return QString::fromLatin1(qtscript_QAccessible_Text_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QAccessible_Text_toScriptValue(QScriptEngine *engine, const QAccessible::Text &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAccessible"));
    return clazz.property(qtscript_QAccessible_Text_toStringHelper(value));
}

static void qtscript_QAccessible_Text_fromScriptValue(const QScriptValue &value, QAccessible::Text &out)
{
    out = qvariant_cast<QAccessible::Text>(value.toVariant());
}

static QScriptValue qtscript_construct_QAccessible_Text(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 6; ++i) {
        if (qtscript_QAccessible_Text_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QAccessible::Text>(arg));
    }
    return context->throwError(QString::fromLatin1("Text(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAccessible_Text_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Text value = qscriptvalue_cast<QAccessible::Text>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAccessible_Text_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAccessible::Text value = qscriptvalue_cast<QAccessible::Text>(context->thisObject());
    return QScriptValue(engine, qtscript_QAccessible_Text_toStringHelper(value));
}

static QScriptValue qtscript_create_QAccessible_Text_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAccessible_Text,
        qtscript_QAccessible_Text_valueOf, qtscript_QAccessible_Text_toString);
    qScriptRegisterMetaType<QAccessible::Text>(engine, qtscript_QAccessible_Text_toScriptValue,
        qtscript_QAccessible_Text_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAccessible_Text_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAccessible_Text_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAccessible
//

static QScriptValue qtscript_QAccessible_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAccessible* _q_self = qscriptvalue_cast<QAccessible*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAccessible.%0(): this object is not a QAccessible")
            .arg(qtscript_QAccessible_function_names[_id+5]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QAccessible");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessible_throw_ambiguity_error_helper(context,
        qtscript_QAccessible_function_names[_id+5],
        qtscript_QAccessible_function_signatures[_id+5]);
}

static QScriptValue qtscript_QAccessible_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAccessible(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAccessible* _q_cpp_result = new QtScriptShell_QAccessible();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QAccessible*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = QAccessible::isActive();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QAccessibleInterface* _q_result = QAccessible::queryAccessibleInterface(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QAccessible::setRootObject(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 3) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        int _q_arg1 = context->argument(1).toInt32();
        QAccessible::Event _q_arg2 = qscriptvalue_cast<QAccessible::Event>(context->argument(2));
        QAccessible::updateAccessibility(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAccessible_throw_ambiguity_error_helper(context,
        qtscript_QAccessible_function_names[_id],
        qtscript_QAccessible_function_signatures[_id]);
}

QScriptValue qtscript_create_QAccessible_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAccessible*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAccessible*)0));

    engine->setDefaultPrototype(qMetaTypeId<QAccessible*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAccessible_static_call, proto, qtscript_QAccessible_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAccessible_static_call,
            qtscript_QAccessible_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QAccessible_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Method"),
        qtscript_create_QAccessible_Method_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Role"),
        qtscript_create_QAccessible_Role_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Action"),
        qtscript_create_QAccessible_Action_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Event"),
        qtscript_create_QAccessible_Event_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("RelationFlag"),
        qtscript_create_QAccessible_RelationFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Relation"),
        qtscript_create_QAccessible_Relation_class(engine));
    ctor.setProperty(QString::fromLatin1("StateFlag"),
        qtscript_create_QAccessible_StateFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("State"),
        qtscript_create_QAccessible_State_class(engine));
    ctor.setProperty(QString::fromLatin1("Text"),
        qtscript_create_QAccessible_Text_class(engine, ctor));
    return ctor;
}
