#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qnamespace.h>
#include <QGesture>
#include <QTextDocument>
#include <QVariant>

#include <qnamespace.h>
#include <qtextdocument.h>

static const char * const qtscript_Qt_function_names[] = {
    "Qt"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_Qt_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_Qt_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_Qt_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("Qt::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

struct qtscript_Qt_metaObject_helper : private QObject
{
    static const QMetaObject *get()
    { return &static_cast<qtscript_Qt_metaObject_helper*>(0)->staticQtMetaObject; }
};

static const QMetaObject *qtscript_Qt_metaObject()
{
    return qtscript_Qt_metaObject_helper::get();
}

Q_DECLARE_METATYPE(Qt::ShortcutContext)
Q_DECLARE_METATYPE(Qt::CheckState)
Q_DECLARE_METATYPE(Qt::FocusPolicy)
Q_DECLARE_METATYPE(Qt::DropAction)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)
Q_DECLARE_METATYPE(Qt::WindowType)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)
Q_DECLARE_METATYPE(Qt::DateFormat)
Q_DECLARE_METATYPE(Qt::TextFormat)
Q_DECLARE_METATYPE(Qt::PenJoinStyle)
Q_DECLARE_METATYPE(Qt::GestureFlag)
Q_DECLARE_METATYPE(QFlags<Qt::GestureFlag>)
Q_DECLARE_METATYPE(Qt::CaseSensitivity)
Q_DECLARE_METATYPE(Qt::EventPriority)
Q_DECLARE_METATYPE(Qt::ImageConversionFlag)
Q_DECLARE_METATYPE(QFlags<Qt::ImageConversionFlag>)
Q_DECLARE_METATYPE(Qt::BGMode)
Q_DECLARE_METATYPE(Qt::ConnectionType)
Q_DECLARE_METATYPE(Qt::ToolBarArea)
Q_DECLARE_METATYPE(QFlags<Qt::ToolBarArea>)
Q_DECLARE_METATYPE(Qt::CoordinateSystem)
Q_DECLARE_METATYPE(Qt::SizeMode)
Q_DECLARE_METATYPE(Qt::FocusReason)
Q_DECLARE_METATYPE(Qt::TileRule)
Q_DECLARE_METATYPE(Qt::WhiteSpaceMode)
Q_DECLARE_METATYPE(Qt::AspectRatioMode)
Q_DECLARE_METATYPE(Qt::SizeHint)
Q_DECLARE_METATYPE(Qt::AlignmentFlag)
Q_DECLARE_METATYPE(QFlags<Qt::AlignmentFlag>)
Q_DECLARE_METATYPE(Qt::ContextMenuPolicy)
Q_DECLARE_METATYPE(Qt::DockWidgetArea)
Q_DECLARE_METATYPE(QFlags<Qt::DockWidgetArea>)
Q_DECLARE_METATYPE(Qt::UIEffect)
Q_DECLARE_METATYPE(Qt::AnchorPoint)
Q_DECLARE_METATYPE(Qt::GlobalColor)
Q_DECLARE_METATYPE(Qt::KeyboardModifier)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(Qt::NavigationMode)
Q_DECLARE_METATYPE(Qt::ItemDataRole)
Q_DECLARE_METATYPE(Qt::ScrollBarPolicy)
Q_DECLARE_METATYPE(Qt::InputMethodHint)
Q_DECLARE_METATYPE(QFlags<Qt::InputMethodHint>)
Q_DECLARE_METATYPE(Qt::AnchorAttribute)
Q_DECLARE_METATYPE(Qt::WindowModality)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(Qt::PenStyle)
Q_DECLARE_METATYPE(Qt::ItemFlag)
Q_DECLARE_METATYPE(QFlags<Qt::ItemFlag>)
Q_DECLARE_METATYPE(Qt::Axis)
Q_DECLARE_METATYPE(Qt::TransformationMode)
Q_DECLARE_METATYPE(Qt::WindowFrameSection)
Q_DECLARE_METATYPE(Qt::HitTestAccuracy)
Q_DECLARE_METATYPE(Qt::CursorShape)
Q_DECLARE_METATYPE(Qt::ItemSelectionMode)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QFlags<Qt::Orientation>)
Q_DECLARE_METATYPE(Qt::InputMethodQuery)
Q_DECLARE_METATYPE(Qt::TimeSpec)
Q_DECLARE_METATYPE(Qt::ArrowType)
Q_DECLARE_METATYPE(Qt::FillRule)
Q_DECLARE_METATYPE(Qt::MaskMode)
Q_DECLARE_METATYPE(Qt::WindowState)
Q_DECLARE_METATYPE(QFlags<Qt::WindowState>)
Q_DECLARE_METATYPE(Qt::ToolBarAreaSizes)
Q_DECLARE_METATYPE(Qt::Corner)
Q_DECLARE_METATYPE(Qt::DayOfWeek)
Q_DECLARE_METATYPE(Qt::ClipOperation)
Q_DECLARE_METATYPE(Qt::LayoutDirection)
Q_DECLARE_METATYPE(Qt::ToolButtonStyle)
Q_DECLARE_METATYPE(Qt::DockWidgetAreaSizes)
Q_DECLARE_METATYPE(Qt::Key)
Q_DECLARE_METATYPE(Qt::ApplicationAttribute)
Q_DECLARE_METATYPE(Qt::TextFlag)
Q_DECLARE_METATYPE(Qt::BrushStyle)
Q_DECLARE_METATYPE(Qt::WidgetAttribute)
Q_DECLARE_METATYPE(Qt::TouchPointState)
Q_DECLARE_METATYPE(QFlags<Qt::TouchPointState>)
Q_DECLARE_METATYPE(Qt::TextInteractionFlag)
Q_DECLARE_METATYPE(QFlags<Qt::TextInteractionFlag>)
Q_DECLARE_METATYPE(Qt::MouseButton)
Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(Qt::MatchFlag)
Q_DECLARE_METATYPE(QFlags<Qt::MatchFlag>)
Q_DECLARE_METATYPE(Qt::PenCapStyle)
Q_DECLARE_METATYPE(Qt::TextElideMode)

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
// Qt::ShortcutContext
//

static const Qt::ShortcutContext qtscript_Qt_ShortcutContext_values[] = {
    Qt::WidgetShortcut
    , Qt::WindowShortcut
    , Qt::ApplicationShortcut
    , Qt::WidgetWithChildrenShortcut
};

static const char * const qtscript_Qt_ShortcutContext_keys[] = {
    "WidgetShortcut"
    , "WindowShortcut"
    , "ApplicationShortcut"
    , "WidgetWithChildrenShortcut"
};

static QString qtscript_Qt_ShortcutContext_toStringHelper(Qt::ShortcutContext value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ShortcutContext");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_ShortcutContext_toScriptValue(QScriptEngine *engine, const Qt::ShortcutContext &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ShortcutContext_toStringHelper(value));
}

static void qtscript_Qt_ShortcutContext_fromScriptValue(const QScriptValue &value, Qt::ShortcutContext &out)
{
    out = qvariant_cast<Qt::ShortcutContext>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ShortcutContext(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ShortcutContext");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::ShortcutContext>(arg));
    return context->throwError(QString::fromLatin1("ShortcutContext(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ShortcutContext_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ShortcutContext value = qscriptvalue_cast<Qt::ShortcutContext>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ShortcutContext_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ShortcutContext value = qscriptvalue_cast<Qt::ShortcutContext>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ShortcutContext_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ShortcutContext_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ShortcutContext,
        qtscript_Qt_ShortcutContext_valueOf, qtscript_Qt_ShortcutContext_toString);
    qScriptRegisterMetaType<Qt::ShortcutContext>(engine, qtscript_Qt_ShortcutContext_toScriptValue,
        qtscript_Qt_ShortcutContext_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ShortcutContext_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ShortcutContext_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::CheckState
//

static const Qt::CheckState qtscript_Qt_CheckState_values[] = {
    Qt::Unchecked
    , Qt::PartiallyChecked
    , Qt::Checked
};

static const char * const qtscript_Qt_CheckState_keys[] = {
    "Unchecked"
    , "PartiallyChecked"
    , "Checked"
};

static QString qtscript_Qt_CheckState_toStringHelper(Qt::CheckState value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("CheckState");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_CheckState_toScriptValue(QScriptEngine *engine, const Qt::CheckState &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_CheckState_toStringHelper(value));
}

static void qtscript_Qt_CheckState_fromScriptValue(const QScriptValue &value, Qt::CheckState &out)
{
    out = qvariant_cast<Qt::CheckState>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_CheckState(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("CheckState");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::CheckState>(arg));
    return context->throwError(QString::fromLatin1("CheckState(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_CheckState_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::CheckState value = qscriptvalue_cast<Qt::CheckState>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_CheckState_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::CheckState value = qscriptvalue_cast<Qt::CheckState>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_CheckState_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_CheckState_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_CheckState,
        qtscript_Qt_CheckState_valueOf, qtscript_Qt_CheckState_toString);
    qScriptRegisterMetaType<Qt::CheckState>(engine, qtscript_Qt_CheckState_toScriptValue,
        qtscript_Qt_CheckState_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_CheckState_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_CheckState_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::FocusPolicy
//

static const Qt::FocusPolicy qtscript_Qt_FocusPolicy_values[] = {
    Qt::NoFocus
    , Qt::TabFocus
    , Qt::ClickFocus
    , Qt::StrongFocus
    , Qt::WheelFocus
};

static const char * const qtscript_Qt_FocusPolicy_keys[] = {
    "NoFocus"
    , "TabFocus"
    , "ClickFocus"
    , "StrongFocus"
    , "WheelFocus"
};

static QString qtscript_Qt_FocusPolicy_toStringHelper(Qt::FocusPolicy value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("FocusPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_FocusPolicy_toScriptValue(QScriptEngine *engine, const Qt::FocusPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_FocusPolicy_toStringHelper(value));
}

static void qtscript_Qt_FocusPolicy_fromScriptValue(const QScriptValue &value, Qt::FocusPolicy &out)
{
    out = qvariant_cast<Qt::FocusPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_FocusPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("FocusPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::FocusPolicy>(arg));
    return context->throwError(QString::fromLatin1("FocusPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_FocusPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::FocusPolicy value = qscriptvalue_cast<Qt::FocusPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_FocusPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::FocusPolicy value = qscriptvalue_cast<Qt::FocusPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_FocusPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_FocusPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_FocusPolicy,
        qtscript_Qt_FocusPolicy_valueOf, qtscript_Qt_FocusPolicy_toString);
    qScriptRegisterMetaType<Qt::FocusPolicy>(engine, qtscript_Qt_FocusPolicy_toScriptValue,
        qtscript_Qt_FocusPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_FocusPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_FocusPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::GestureType
//

static const Qt::GestureType qtscript_Qt_GestureType_values[] = {
    Qt::TapGesture
    , Qt::TapAndHoldGesture
    , Qt::PanGesture
    , Qt::PinchGesture
    , Qt::SwipeGesture
    , Qt::CustomGesture
    , Qt::LastGestureType
};

static const char * const qtscript_Qt_GestureType_keys[] = {
    "TapGesture"
    , "TapAndHoldGesture"
    , "PanGesture"
    , "PinchGesture"
    , "SwipeGesture"
    , "CustomGesture"
    , "LastGestureType"
};

static QString qtscript_Qt_GestureType_toStringHelper(Qt::GestureType value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("GestureType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_GestureType_toScriptValue(QScriptEngine *engine, const Qt::GestureType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_GestureType_toStringHelper(value));
}

static void qtscript_Qt_GestureType_fromScriptValue(const QScriptValue &value, Qt::GestureType &out)
{
    out = qvariant_cast<Qt::GestureType>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_GestureType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("GestureType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::GestureType>(arg));
    return context->throwError(QString::fromLatin1("GestureType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_GestureType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::GestureType value = qscriptvalue_cast<Qt::GestureType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_GestureType_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::GestureType value = qscriptvalue_cast<Qt::GestureType>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_GestureType_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_GestureType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_GestureType,
        qtscript_Qt_GestureType_valueOf, qtscript_Qt_GestureType_toString);
    qScriptRegisterMetaType<Qt::GestureType>(engine, qtscript_Qt_GestureType_toScriptValue,
        qtscript_Qt_GestureType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_GestureType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_GestureType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::DropAction
//

static const Qt::DropAction qtscript_Qt_DropAction_values[] = {
    Qt::IgnoreAction
    , Qt::CopyAction
    , Qt::MoveAction
    , Qt::LinkAction
    , Qt::ActionMask
    , Qt::TargetMoveAction
};

static const char * const qtscript_Qt_DropAction_keys[] = {
    "IgnoreAction"
    , "CopyAction"
    , "MoveAction"
    , "LinkAction"
    , "ActionMask"
    , "TargetMoveAction"
};

static QString qtscript_Qt_DropAction_toStringHelper(Qt::DropAction value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("DropAction");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_DropAction_toScriptValue(QScriptEngine *engine, const Qt::DropAction &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_DropAction_toStringHelper(value));
}

static void qtscript_Qt_DropAction_fromScriptValue(const QScriptValue &value, Qt::DropAction &out)
{
    out = qvariant_cast<Qt::DropAction>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_DropAction(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("DropAction");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::DropAction>(arg));
    return context->throwError(QString::fromLatin1("DropAction(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_DropAction_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DropAction value = qscriptvalue_cast<Qt::DropAction>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_DropAction_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DropAction value = qscriptvalue_cast<Qt::DropAction>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_DropAction_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_DropAction_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_DropAction,
        qtscript_Qt_DropAction_valueOf, qtscript_Qt_DropAction_toString);
    qScriptRegisterMetaType<Qt::DropAction>(engine, qtscript_Qt_DropAction_toScriptValue,
        qtscript_Qt_DropAction_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_DropAction_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_DropAction_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::DropActions
//

static QScriptValue qtscript_Qt_DropActions_toScriptValue(QScriptEngine *engine, const Qt::DropActions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_DropActions_fromScriptValue(const QScriptValue &value, Qt::DropActions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::DropActions>())
        out = qvariant_cast<Qt::DropActions>(var);
    else if (var.userType() == qMetaTypeId<Qt::DropAction>())
        out = qvariant_cast<Qt::DropAction>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_DropActions(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DropActions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::DropActions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::DropAction>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("DropActions(): argument %0 is not of type DropAction").arg(i));
            }
            result |= qvariant_cast<Qt::DropAction>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_DropActions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DropActions value = qscriptvalue_cast<Qt::DropActions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_DropActions_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DropActions value = qscriptvalue_cast<Qt::DropActions>(context->thisObject());
    QString result;
    for (int i = 0; i < 6; ++i) {
        if ((value & qtscript_Qt_DropAction_values[i]) == qtscript_Qt_DropAction_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_DropAction_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_DropActions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::DropActions>() == otherObj.value<Qt::DropActions>())));
}

static QScriptValue qtscript_create_Qt_DropActions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_DropActions, qtscript_Qt_DropActions_valueOf,
        qtscript_Qt_DropActions_toString, qtscript_Qt_DropActions_equals);
    qScriptRegisterMetaType<Qt::DropActions>(engine, qtscript_Qt_DropActions_toScriptValue,
        qtscript_Qt_DropActions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::WindowType
//

static const Qt::WindowType qtscript_Qt_WindowType_values[] = {
    Qt::WindowSoftkeysRespondHint
    , Qt::Widget
    , Qt::Window
    , Qt::Dialog
    , Qt::Sheet
    , Qt::Drawer
    , Qt::Popup
    , Qt::Tool
    , Qt::ToolTip
    , Qt::SplashScreen
    , Qt::Desktop
    , Qt::SubWindow
    , Qt::WindowType_Mask
    , Qt::MSWindowsFixedSizeDialogHint
    , Qt::MSWindowsOwnDC
    , Qt::X11BypassWindowManagerHint
    , Qt::FramelessWindowHint
    , Qt::WindowTitleHint
    , Qt::WindowSystemMenuHint
    , Qt::WindowMinimizeButtonHint
    , Qt::WindowMaximizeButtonHint
    , Qt::WindowMinMaxButtonsHint
    , Qt::WindowContextHelpButtonHint
    , Qt::WindowShadeButtonHint
    , Qt::WindowStaysOnTopHint
    , Qt::WindowOkButtonHint
    , Qt::WindowCancelButtonHint
    , Qt::CustomizeWindowHint
    , Qt::WindowStaysOnBottomHint
    , Qt::WindowCloseButtonHint
    , Qt::MacWindowToolBarButtonHint
    , Qt::BypassGraphicsProxyWidget
    , Qt::WindowSoftkeysVisibleHint
};

static const char * const qtscript_Qt_WindowType_keys[] = {
    "WindowSoftkeysRespondHint"
    , "Widget"
    , "Window"
    , "Dialog"
    , "Sheet"
    , "Drawer"
    , "Popup"
    , "Tool"
    , "ToolTip"
    , "SplashScreen"
    , "Desktop"
    , "SubWindow"
    , "WindowType_Mask"
    , "MSWindowsFixedSizeDialogHint"
    , "MSWindowsOwnDC"
    , "X11BypassWindowManagerHint"
    , "FramelessWindowHint"
    , "WindowTitleHint"
    , "WindowSystemMenuHint"
    , "WindowMinimizeButtonHint"
    , "WindowMaximizeButtonHint"
    , "WindowMinMaxButtonsHint"
    , "WindowContextHelpButtonHint"
    , "WindowShadeButtonHint"
    , "WindowStaysOnTopHint"
    , "WindowOkButtonHint"
    , "WindowCancelButtonHint"
    , "CustomizeWindowHint"
    , "WindowStaysOnBottomHint"
    , "WindowCloseButtonHint"
    , "MacWindowToolBarButtonHint"
    , "BypassGraphicsProxyWidget"
    , "WindowSoftkeysVisibleHint"
};

static QString qtscript_Qt_WindowType_toStringHelper(Qt::WindowType value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("WindowType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_WindowType_toScriptValue(QScriptEngine *engine, const Qt::WindowType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_WindowType_toStringHelper(value));
}

static void qtscript_Qt_WindowType_fromScriptValue(const QScriptValue &value, Qt::WindowType &out)
{
    out = qvariant_cast<Qt::WindowType>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_WindowType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("WindowType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::WindowType>(arg));
    return context->throwError(QString::fromLatin1("WindowType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_WindowType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowType value = qscriptvalue_cast<Qt::WindowType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_WindowType_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowType value = qscriptvalue_cast<Qt::WindowType>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_WindowType_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_WindowType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_WindowType,
        qtscript_Qt_WindowType_valueOf, qtscript_Qt_WindowType_toString);
    qScriptRegisterMetaType<Qt::WindowType>(engine, qtscript_Qt_WindowType_toScriptValue,
        qtscript_Qt_WindowType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 33; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_WindowType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_WindowType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::WindowFlags
//

static QScriptValue qtscript_Qt_WindowFlags_toScriptValue(QScriptEngine *engine, const Qt::WindowFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_WindowFlags_fromScriptValue(const QScriptValue &value, Qt::WindowFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::WindowFlags>())
        out = qvariant_cast<Qt::WindowFlags>(var);
    else if (var.userType() == qMetaTypeId<Qt::WindowType>())
        out = qvariant_cast<Qt::WindowType>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_WindowFlags(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::WindowFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::WindowType>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("WindowFlags(): argument %0 is not of type WindowType").arg(i));
            }
            result |= qvariant_cast<Qt::WindowType>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_WindowFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowFlags value = qscriptvalue_cast<Qt::WindowFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_WindowFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowFlags value = qscriptvalue_cast<Qt::WindowFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 33; ++i) {
        if ((value & qtscript_Qt_WindowType_values[i]) == qtscript_Qt_WindowType_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_WindowType_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_WindowFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::WindowFlags>() == otherObj.value<Qt::WindowFlags>())));
}

static QScriptValue qtscript_create_Qt_WindowFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_WindowFlags, qtscript_Qt_WindowFlags_valueOf,
        qtscript_Qt_WindowFlags_toString, qtscript_Qt_WindowFlags_equals);
    qScriptRegisterMetaType<Qt::WindowFlags>(engine, qtscript_Qt_WindowFlags_toScriptValue,
        qtscript_Qt_WindowFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::DateFormat
//

static const Qt::DateFormat qtscript_Qt_DateFormat_values[] = {
    Qt::TextDate
    , Qt::ISODate
    , Qt::SystemLocaleDate
    , Qt::LocaleDate
    , Qt::SystemLocaleShortDate
    , Qt::SystemLocaleLongDate
    , Qt::DefaultLocaleShortDate
    , Qt::DefaultLocaleLongDate
};

static const char * const qtscript_Qt_DateFormat_keys[] = {
    "TextDate"
    , "ISODate"
    , "SystemLocaleDate"
    , "LocaleDate"
    , "SystemLocaleShortDate"
    , "SystemLocaleLongDate"
    , "DefaultLocaleShortDate"
    , "DefaultLocaleLongDate"
};

static QString qtscript_Qt_DateFormat_toStringHelper(Qt::DateFormat value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("DateFormat");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_DateFormat_toScriptValue(QScriptEngine *engine, const Qt::DateFormat &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_DateFormat_toStringHelper(value));
}

static void qtscript_Qt_DateFormat_fromScriptValue(const QScriptValue &value, Qt::DateFormat &out)
{
    out = qvariant_cast<Qt::DateFormat>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_DateFormat(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("DateFormat");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::DateFormat>(arg));
    return context->throwError(QString::fromLatin1("DateFormat(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_DateFormat_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DateFormat value = qscriptvalue_cast<Qt::DateFormat>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_DateFormat_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DateFormat value = qscriptvalue_cast<Qt::DateFormat>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_DateFormat_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_DateFormat_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_DateFormat,
        qtscript_Qt_DateFormat_valueOf, qtscript_Qt_DateFormat_toString);
    qScriptRegisterMetaType<Qt::DateFormat>(engine, qtscript_Qt_DateFormat_toScriptValue,
        qtscript_Qt_DateFormat_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_DateFormat_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_DateFormat_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::TextFormat
//

static const Qt::TextFormat qtscript_Qt_TextFormat_values[] = {
    Qt::PlainText
    , Qt::RichText
    , Qt::AutoText
    , Qt::LogText
};

static const char * const qtscript_Qt_TextFormat_keys[] = {
    "PlainText"
    , "RichText"
    , "AutoText"
    , "LogText"
};

static QString qtscript_Qt_TextFormat_toStringHelper(Qt::TextFormat value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("TextFormat");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_TextFormat_toScriptValue(QScriptEngine *engine, const Qt::TextFormat &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_TextFormat_toStringHelper(value));
}

static void qtscript_Qt_TextFormat_fromScriptValue(const QScriptValue &value, Qt::TextFormat &out)
{
    out = qvariant_cast<Qt::TextFormat>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_TextFormat(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("TextFormat");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::TextFormat>(arg));
    return context->throwError(QString::fromLatin1("TextFormat(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_TextFormat_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TextFormat value = qscriptvalue_cast<Qt::TextFormat>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_TextFormat_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TextFormat value = qscriptvalue_cast<Qt::TextFormat>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_TextFormat_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_TextFormat_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_TextFormat,
        qtscript_Qt_TextFormat_valueOf, qtscript_Qt_TextFormat_toString);
    qScriptRegisterMetaType<Qt::TextFormat>(engine, qtscript_Qt_TextFormat_toScriptValue,
        qtscript_Qt_TextFormat_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_TextFormat_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_TextFormat_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::PenJoinStyle
//

static const Qt::PenJoinStyle qtscript_Qt_PenJoinStyle_values[] = {
    Qt::MiterJoin
    , Qt::BevelJoin
    , Qt::RoundJoin
    , Qt::SvgMiterJoin
    , Qt::MPenJoinStyle
};

static const char * const qtscript_Qt_PenJoinStyle_keys[] = {
    "MiterJoin"
    , "BevelJoin"
    , "RoundJoin"
    , "SvgMiterJoin"
    , "MPenJoinStyle"
};

static QString qtscript_Qt_PenJoinStyle_toStringHelper(Qt::PenJoinStyle value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("PenJoinStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_PenJoinStyle_toScriptValue(QScriptEngine *engine, const Qt::PenJoinStyle &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_PenJoinStyle_toStringHelper(value));
}

static void qtscript_Qt_PenJoinStyle_fromScriptValue(const QScriptValue &value, Qt::PenJoinStyle &out)
{
    out = qvariant_cast<Qt::PenJoinStyle>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_PenJoinStyle(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("PenJoinStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::PenJoinStyle>(arg));
    return context->throwError(QString::fromLatin1("PenJoinStyle(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_PenJoinStyle_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::PenJoinStyle value = qscriptvalue_cast<Qt::PenJoinStyle>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_PenJoinStyle_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::PenJoinStyle value = qscriptvalue_cast<Qt::PenJoinStyle>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_PenJoinStyle_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_PenJoinStyle_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_PenJoinStyle,
        qtscript_Qt_PenJoinStyle_valueOf, qtscript_Qt_PenJoinStyle_toString);
    qScriptRegisterMetaType<Qt::PenJoinStyle>(engine, qtscript_Qt_PenJoinStyle_toScriptValue,
        qtscript_Qt_PenJoinStyle_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_PenJoinStyle_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_PenJoinStyle_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::GestureFlag
//

static const Qt::GestureFlag qtscript_Qt_GestureFlag_values[] = {
    Qt::DontStartGestureOnChildren
    , Qt::ReceivePartialGestures
    , Qt::IgnoredGesturesPropagateToParent
};

static const char * const qtscript_Qt_GestureFlag_keys[] = {
    "DontStartGestureOnChildren"
    , "ReceivePartialGestures"
    , "IgnoredGesturesPropagateToParent"
};

static QString qtscript_Qt_GestureFlag_toStringHelper(Qt::GestureFlag value)
{
    for (int i = 0; i < 3; ++i) {
        if (qtscript_Qt_GestureFlag_values[i] == value)
            return QString::fromLatin1(qtscript_Qt_GestureFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_Qt_GestureFlag_toScriptValue(QScriptEngine *engine, const Qt::GestureFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_GestureFlag_toStringHelper(value));
}

static void qtscript_Qt_GestureFlag_fromScriptValue(const QScriptValue &value, Qt::GestureFlag &out)
{
    out = qvariant_cast<Qt::GestureFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_GestureFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 3; ++i) {
        if (qtscript_Qt_GestureFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<Qt::GestureFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("GestureFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_GestureFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::GestureFlag value = qscriptvalue_cast<Qt::GestureFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_GestureFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::GestureFlag value = qscriptvalue_cast<Qt::GestureFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_GestureFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_GestureFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_GestureFlag,
        qtscript_Qt_GestureFlag_valueOf, qtscript_Qt_GestureFlag_toString);
    qScriptRegisterMetaType<Qt::GestureFlag>(engine, qtscript_Qt_GestureFlag_toScriptValue,
        qtscript_Qt_GestureFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_GestureFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_GestureFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::GestureFlags
//

static QScriptValue qtscript_Qt_GestureFlags_toScriptValue(QScriptEngine *engine, const Qt::GestureFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_GestureFlags_fromScriptValue(const QScriptValue &value, Qt::GestureFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::GestureFlags>())
        out = qvariant_cast<Qt::GestureFlags>(var);
    else if (var.userType() == qMetaTypeId<Qt::GestureFlag>())
        out = qvariant_cast<Qt::GestureFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_GestureFlags(QScriptContext *context, QScriptEngine *engine)
{
    Qt::GestureFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::GestureFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::GestureFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("GestureFlags(): argument %0 is not of type GestureFlag").arg(i));
            }
            result |= qvariant_cast<Qt::GestureFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_GestureFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::GestureFlags value = qscriptvalue_cast<Qt::GestureFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_GestureFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::GestureFlags value = qscriptvalue_cast<Qt::GestureFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_Qt_GestureFlag_values[i]) == qtscript_Qt_GestureFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_GestureFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_GestureFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::GestureFlags>() == otherObj.value<Qt::GestureFlags>())));
}

static QScriptValue qtscript_create_Qt_GestureFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_GestureFlags, qtscript_Qt_GestureFlags_valueOf,
        qtscript_Qt_GestureFlags_toString, qtscript_Qt_GestureFlags_equals);
    qScriptRegisterMetaType<Qt::GestureFlags>(engine, qtscript_Qt_GestureFlags_toScriptValue,
        qtscript_Qt_GestureFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::CaseSensitivity
//

static const Qt::CaseSensitivity qtscript_Qt_CaseSensitivity_values[] = {
    Qt::CaseInsensitive
    , Qt::CaseSensitive
};

static const char * const qtscript_Qt_CaseSensitivity_keys[] = {
    "CaseInsensitive"
    , "CaseSensitive"
};

static QString qtscript_Qt_CaseSensitivity_toStringHelper(Qt::CaseSensitivity value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("CaseSensitivity");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_CaseSensitivity_toScriptValue(QScriptEngine *engine, const Qt::CaseSensitivity &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_CaseSensitivity_toStringHelper(value));
}

static void qtscript_Qt_CaseSensitivity_fromScriptValue(const QScriptValue &value, Qt::CaseSensitivity &out)
{
    out = qvariant_cast<Qt::CaseSensitivity>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_CaseSensitivity(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("CaseSensitivity");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::CaseSensitivity>(arg));
    return context->throwError(QString::fromLatin1("CaseSensitivity(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_CaseSensitivity_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::CaseSensitivity value = qscriptvalue_cast<Qt::CaseSensitivity>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_CaseSensitivity_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::CaseSensitivity value = qscriptvalue_cast<Qt::CaseSensitivity>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_CaseSensitivity_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_CaseSensitivity_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_CaseSensitivity,
        qtscript_Qt_CaseSensitivity_valueOf, qtscript_Qt_CaseSensitivity_toString);
    qScriptRegisterMetaType<Qt::CaseSensitivity>(engine, qtscript_Qt_CaseSensitivity_toScriptValue,
        qtscript_Qt_CaseSensitivity_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_CaseSensitivity_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_CaseSensitivity_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::EventPriority
//

static const Qt::EventPriority qtscript_Qt_EventPriority_values[] = {
    Qt::LowEventPriority
    , Qt::NormalEventPriority
    , Qt::HighEventPriority
};

static const char * const qtscript_Qt_EventPriority_keys[] = {
    "LowEventPriority"
    , "NormalEventPriority"
    , "HighEventPriority"
};

static QString qtscript_Qt_EventPriority_toStringHelper(Qt::EventPriority value)
{
    if ((value >= Qt::LowEventPriority) && (value <= Qt::HighEventPriority))
        return qtscript_Qt_EventPriority_keys[static_cast<int>(value)-static_cast<int>(Qt::LowEventPriority)];
    return QString();
}

static QScriptValue qtscript_Qt_EventPriority_toScriptValue(QScriptEngine *engine, const Qt::EventPriority &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_EventPriority_toStringHelper(value));
}

static void qtscript_Qt_EventPriority_fromScriptValue(const QScriptValue &value, Qt::EventPriority &out)
{
    out = qvariant_cast<Qt::EventPriority>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_EventPriority(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::LowEventPriority) && (arg <= Qt::HighEventPriority))
        return qScriptValueFromValue(engine,  static_cast<Qt::EventPriority>(arg));
    return context->throwError(QString::fromLatin1("EventPriority(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_EventPriority_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::EventPriority value = qscriptvalue_cast<Qt::EventPriority>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_EventPriority_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::EventPriority value = qscriptvalue_cast<Qt::EventPriority>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_EventPriority_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_EventPriority_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_EventPriority,
        qtscript_Qt_EventPriority_valueOf, qtscript_Qt_EventPriority_toString);
    qScriptRegisterMetaType<Qt::EventPriority>(engine, qtscript_Qt_EventPriority_toScriptValue,
        qtscript_Qt_EventPriority_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_EventPriority_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_EventPriority_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ImageConversionFlag
//

static const Qt::ImageConversionFlag qtscript_Qt_ImageConversionFlag_values[] = {
    Qt::AutoColor
    , Qt::MonoOnly
    , Qt::ColorMode_Mask
    , Qt::OrderedAlphaDither
    , Qt::DiffuseAlphaDither
    , Qt::AlphaDither_Mask
    , Qt::OrderedDither
    , Qt::ThresholdDither
    , Qt::Dither_Mask
    , Qt::PreferDither
    , Qt::AvoidDither
    , Qt::DitherMode_Mask
    , Qt::NoOpaqueDetection
    , Qt::NoFormatConversion
};

static const char * const qtscript_Qt_ImageConversionFlag_keys[] = {
    "AutoColor"
    , "MonoOnly"
    , "ColorMode_Mask"
    , "OrderedAlphaDither"
    , "DiffuseAlphaDither"
    , "AlphaDither_Mask"
    , "OrderedDither"
    , "ThresholdDither"
    , "Dither_Mask"
    , "PreferDither"
    , "AvoidDither"
    , "DitherMode_Mask"
    , "NoOpaqueDetection"
    , "NoFormatConversion"
};

static QString qtscript_Qt_ImageConversionFlag_toStringHelper(Qt::ImageConversionFlag value)
{
    for (int i = 0; i < 14; ++i) {
        if (qtscript_Qt_ImageConversionFlag_values[i] == value)
            return QString::fromLatin1(qtscript_Qt_ImageConversionFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_Qt_ImageConversionFlag_toScriptValue(QScriptEngine *engine, const Qt::ImageConversionFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ImageConversionFlag_toStringHelper(value));
}

static void qtscript_Qt_ImageConversionFlag_fromScriptValue(const QScriptValue &value, Qt::ImageConversionFlag &out)
{
    out = qvariant_cast<Qt::ImageConversionFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ImageConversionFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 14; ++i) {
        if (qtscript_Qt_ImageConversionFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<Qt::ImageConversionFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("ImageConversionFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ImageConversionFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ImageConversionFlag value = qscriptvalue_cast<Qt::ImageConversionFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ImageConversionFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ImageConversionFlag value = qscriptvalue_cast<Qt::ImageConversionFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ImageConversionFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ImageConversionFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ImageConversionFlag,
        qtscript_Qt_ImageConversionFlag_valueOf, qtscript_Qt_ImageConversionFlag_toString);
    qScriptRegisterMetaType<Qt::ImageConversionFlag>(engine, qtscript_Qt_ImageConversionFlag_toScriptValue,
        qtscript_Qt_ImageConversionFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 14; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ImageConversionFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ImageConversionFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ImageConversionFlags
//

static QScriptValue qtscript_Qt_ImageConversionFlags_toScriptValue(QScriptEngine *engine, const Qt::ImageConversionFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_ImageConversionFlags_fromScriptValue(const QScriptValue &value, Qt::ImageConversionFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::ImageConversionFlags>())
        out = qvariant_cast<Qt::ImageConversionFlags>(var);
    else if (var.userType() == qMetaTypeId<Qt::ImageConversionFlag>())
        out = qvariant_cast<Qt::ImageConversionFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_ImageConversionFlags(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ImageConversionFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::ImageConversionFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::ImageConversionFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ImageConversionFlags(): argument %0 is not of type ImageConversionFlag").arg(i));
            }
            result |= qvariant_cast<Qt::ImageConversionFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_ImageConversionFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ImageConversionFlags value = qscriptvalue_cast<Qt::ImageConversionFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ImageConversionFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ImageConversionFlags value = qscriptvalue_cast<Qt::ImageConversionFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 14; ++i) {
        if ((value & qtscript_Qt_ImageConversionFlag_values[i]) == qtscript_Qt_ImageConversionFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_ImageConversionFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_ImageConversionFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::ImageConversionFlags>() == otherObj.value<Qt::ImageConversionFlags>())));
}

static QScriptValue qtscript_create_Qt_ImageConversionFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_ImageConversionFlags, qtscript_Qt_ImageConversionFlags_valueOf,
        qtscript_Qt_ImageConversionFlags_toString, qtscript_Qt_ImageConversionFlags_equals);
    qScriptRegisterMetaType<Qt::ImageConversionFlags>(engine, qtscript_Qt_ImageConversionFlags_toScriptValue,
        qtscript_Qt_ImageConversionFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::GestureState
//

static const Qt::GestureState qtscript_Qt_GestureState_values[] = {
    Qt::NoGesture
    , Qt::GestureStarted
    , Qt::GestureUpdated
    , Qt::GestureFinished
    , Qt::GestureCanceled
};

static const char * const qtscript_Qt_GestureState_keys[] = {
    "NoGesture"
    , "GestureStarted"
    , "GestureUpdated"
    , "GestureFinished"
    , "GestureCanceled"
};

static QString qtscript_Qt_GestureState_toStringHelper(Qt::GestureState value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("GestureState");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_GestureState_toScriptValue(QScriptEngine *engine, const Qt::GestureState &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_GestureState_toStringHelper(value));
}

static void qtscript_Qt_GestureState_fromScriptValue(const QScriptValue &value, Qt::GestureState &out)
{
    out = qvariant_cast<Qt::GestureState>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_GestureState(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("GestureState");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::GestureState>(arg));
    return context->throwError(QString::fromLatin1("GestureState(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_GestureState_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::GestureState value = qscriptvalue_cast<Qt::GestureState>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_GestureState_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::GestureState value = qscriptvalue_cast<Qt::GestureState>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_GestureState_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_GestureState_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_GestureState,
        qtscript_Qt_GestureState_valueOf, qtscript_Qt_GestureState_toString);
    qScriptRegisterMetaType<Qt::GestureState>(engine, qtscript_Qt_GestureState_toScriptValue,
        qtscript_Qt_GestureState_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_GestureState_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_GestureState_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::BGMode
//

static const Qt::BGMode qtscript_Qt_BGMode_values[] = {
    Qt::TransparentMode
    , Qt::OpaqueMode
};

static const char * const qtscript_Qt_BGMode_keys[] = {
    "TransparentMode"
    , "OpaqueMode"
};

static QString qtscript_Qt_BGMode_toStringHelper(Qt::BGMode value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("BGMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_BGMode_toScriptValue(QScriptEngine *engine, const Qt::BGMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_BGMode_toStringHelper(value));
}

static void qtscript_Qt_BGMode_fromScriptValue(const QScriptValue &value, Qt::BGMode &out)
{
    out = qvariant_cast<Qt::BGMode>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_BGMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("BGMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::BGMode>(arg));
    return context->throwError(QString::fromLatin1("BGMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_BGMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::BGMode value = qscriptvalue_cast<Qt::BGMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_BGMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::BGMode value = qscriptvalue_cast<Qt::BGMode>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_BGMode_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_BGMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_BGMode,
        qtscript_Qt_BGMode_valueOf, qtscript_Qt_BGMode_toString);
    qScriptRegisterMetaType<Qt::BGMode>(engine, qtscript_Qt_BGMode_toScriptValue,
        qtscript_Qt_BGMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_BGMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_BGMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ConnectionType
//

static const Qt::ConnectionType qtscript_Qt_ConnectionType_values[] = {
    Qt::AutoConnection
    , Qt::DirectConnection
    , Qt::QueuedConnection
    , Qt::AutoCompatConnection
    , Qt::BlockingQueuedConnection
    , Qt::UniqueConnection
};

static const char * const qtscript_Qt_ConnectionType_keys[] = {
    "AutoConnection"
    , "DirectConnection"
    , "QueuedConnection"
    , "AutoCompatConnection"
    , "BlockingQueuedConnection"
    , "UniqueConnection"
};

static QString qtscript_Qt_ConnectionType_toStringHelper(Qt::ConnectionType value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ConnectionType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_ConnectionType_toScriptValue(QScriptEngine *engine, const Qt::ConnectionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ConnectionType_toStringHelper(value));
}

static void qtscript_Qt_ConnectionType_fromScriptValue(const QScriptValue &value, Qt::ConnectionType &out)
{
    out = qvariant_cast<Qt::ConnectionType>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ConnectionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ConnectionType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::ConnectionType>(arg));
    return context->throwError(QString::fromLatin1("ConnectionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ConnectionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ConnectionType value = qscriptvalue_cast<Qt::ConnectionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ConnectionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ConnectionType value = qscriptvalue_cast<Qt::ConnectionType>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ConnectionType_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ConnectionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ConnectionType,
        qtscript_Qt_ConnectionType_valueOf, qtscript_Qt_ConnectionType_toString);
    qScriptRegisterMetaType<Qt::ConnectionType>(engine, qtscript_Qt_ConnectionType_toScriptValue,
        qtscript_Qt_ConnectionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ConnectionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ConnectionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ToolBarArea
//

static const Qt::ToolBarArea qtscript_Qt_ToolBarArea_values[] = {
    Qt::NoToolBarArea
    , Qt::LeftToolBarArea
    , Qt::RightToolBarArea
    , Qt::TopToolBarArea
    , Qt::BottomToolBarArea
    , Qt::ToolBarArea_Mask
};

static const char * const qtscript_Qt_ToolBarArea_keys[] = {
    "NoToolBarArea"
    , "LeftToolBarArea"
    , "RightToolBarArea"
    , "TopToolBarArea"
    , "BottomToolBarArea"
    , "ToolBarArea_Mask"
};

static QString qtscript_Qt_ToolBarArea_toStringHelper(Qt::ToolBarArea value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ToolBarArea");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_ToolBarArea_toScriptValue(QScriptEngine *engine, const Qt::ToolBarArea &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ToolBarArea_toStringHelper(value));
}

static void qtscript_Qt_ToolBarArea_fromScriptValue(const QScriptValue &value, Qt::ToolBarArea &out)
{
    out = qvariant_cast<Qt::ToolBarArea>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ToolBarArea(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ToolBarArea");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::ToolBarArea>(arg));
    return context->throwError(QString::fromLatin1("ToolBarArea(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ToolBarArea_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ToolBarArea value = qscriptvalue_cast<Qt::ToolBarArea>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ToolBarArea_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ToolBarArea value = qscriptvalue_cast<Qt::ToolBarArea>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ToolBarArea_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ToolBarArea_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ToolBarArea,
        qtscript_Qt_ToolBarArea_valueOf, qtscript_Qt_ToolBarArea_toString);
    qScriptRegisterMetaType<Qt::ToolBarArea>(engine, qtscript_Qt_ToolBarArea_toScriptValue,
        qtscript_Qt_ToolBarArea_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ToolBarArea_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ToolBarArea_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ToolBarAreas
//

static QScriptValue qtscript_Qt_ToolBarAreas_toScriptValue(QScriptEngine *engine, const Qt::ToolBarAreas &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_ToolBarAreas_fromScriptValue(const QScriptValue &value, Qt::ToolBarAreas &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::ToolBarAreas>())
        out = qvariant_cast<Qt::ToolBarAreas>(var);
    else if (var.userType() == qMetaTypeId<Qt::ToolBarArea>())
        out = qvariant_cast<Qt::ToolBarArea>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_ToolBarAreas(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ToolBarAreas result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::ToolBarAreas>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::ToolBarArea>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ToolBarAreas(): argument %0 is not of type ToolBarArea").arg(i));
            }
            result |= qvariant_cast<Qt::ToolBarArea>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_ToolBarAreas_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ToolBarAreas value = qscriptvalue_cast<Qt::ToolBarAreas>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ToolBarAreas_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ToolBarAreas value = qscriptvalue_cast<Qt::ToolBarAreas>(context->thisObject());
    QString result;
    for (int i = 0; i < 6; ++i) {
        if ((value & qtscript_Qt_ToolBarArea_values[i]) == qtscript_Qt_ToolBarArea_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_ToolBarArea_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_ToolBarAreas_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::ToolBarAreas>() == otherObj.value<Qt::ToolBarAreas>())));
}

static QScriptValue qtscript_create_Qt_ToolBarAreas_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_ToolBarAreas, qtscript_Qt_ToolBarAreas_valueOf,
        qtscript_Qt_ToolBarAreas_toString, qtscript_Qt_ToolBarAreas_equals);
    qScriptRegisterMetaType<Qt::ToolBarAreas>(engine, qtscript_Qt_ToolBarAreas_toScriptValue,
        qtscript_Qt_ToolBarAreas_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::CoordinateSystem
//

static const Qt::CoordinateSystem qtscript_Qt_CoordinateSystem_values[] = {
    Qt::DeviceCoordinates
    , Qt::LogicalCoordinates
};

static const char * const qtscript_Qt_CoordinateSystem_keys[] = {
    "DeviceCoordinates"
    , "LogicalCoordinates"
};

static QString qtscript_Qt_CoordinateSystem_toStringHelper(Qt::CoordinateSystem value)
{
    if ((value >= Qt::DeviceCoordinates) && (value <= Qt::LogicalCoordinates))
        return qtscript_Qt_CoordinateSystem_keys[static_cast<int>(value)-static_cast<int>(Qt::DeviceCoordinates)];
    return QString();
}

static QScriptValue qtscript_Qt_CoordinateSystem_toScriptValue(QScriptEngine *engine, const Qt::CoordinateSystem &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_CoordinateSystem_toStringHelper(value));
}

static void qtscript_Qt_CoordinateSystem_fromScriptValue(const QScriptValue &value, Qt::CoordinateSystem &out)
{
    out = qvariant_cast<Qt::CoordinateSystem>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_CoordinateSystem(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::DeviceCoordinates) && (arg <= Qt::LogicalCoordinates))
        return qScriptValueFromValue(engine,  static_cast<Qt::CoordinateSystem>(arg));
    return context->throwError(QString::fromLatin1("CoordinateSystem(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_CoordinateSystem_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::CoordinateSystem value = qscriptvalue_cast<Qt::CoordinateSystem>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_CoordinateSystem_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::CoordinateSystem value = qscriptvalue_cast<Qt::CoordinateSystem>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_CoordinateSystem_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_CoordinateSystem_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_CoordinateSystem,
        qtscript_Qt_CoordinateSystem_valueOf, qtscript_Qt_CoordinateSystem_toString);
    qScriptRegisterMetaType<Qt::CoordinateSystem>(engine, qtscript_Qt_CoordinateSystem_toScriptValue,
        qtscript_Qt_CoordinateSystem_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_CoordinateSystem_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_CoordinateSystem_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::SizeMode
//

static const Qt::SizeMode qtscript_Qt_SizeMode_values[] = {
    Qt::AbsoluteSize
    , Qt::RelativeSize
};

static const char * const qtscript_Qt_SizeMode_keys[] = {
    "AbsoluteSize"
    , "RelativeSize"
};

static QString qtscript_Qt_SizeMode_toStringHelper(Qt::SizeMode value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("SizeMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_SizeMode_toScriptValue(QScriptEngine *engine, const Qt::SizeMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_SizeMode_toStringHelper(value));
}

static void qtscript_Qt_SizeMode_fromScriptValue(const QScriptValue &value, Qt::SizeMode &out)
{
    out = qvariant_cast<Qt::SizeMode>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_SizeMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("SizeMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::SizeMode>(arg));
    return context->throwError(QString::fromLatin1("SizeMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_SizeMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::SizeMode value = qscriptvalue_cast<Qt::SizeMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_SizeMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::SizeMode value = qscriptvalue_cast<Qt::SizeMode>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_SizeMode_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_SizeMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_SizeMode,
        qtscript_Qt_SizeMode_valueOf, qtscript_Qt_SizeMode_toString);
    qScriptRegisterMetaType<Qt::SizeMode>(engine, qtscript_Qt_SizeMode_toScriptValue,
        qtscript_Qt_SizeMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_SizeMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_SizeMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::FocusReason
//

static const Qt::FocusReason qtscript_Qt_FocusReason_values[] = {
    Qt::MouseFocusReason
    , Qt::TabFocusReason
    , Qt::BacktabFocusReason
    , Qt::ActiveWindowFocusReason
    , Qt::PopupFocusReason
    , Qt::ShortcutFocusReason
    , Qt::MenuBarFocusReason
    , Qt::OtherFocusReason
    , Qt::NoFocusReason
};

static const char * const qtscript_Qt_FocusReason_keys[] = {
    "MouseFocusReason"
    , "TabFocusReason"
    , "BacktabFocusReason"
    , "ActiveWindowFocusReason"
    , "PopupFocusReason"
    , "ShortcutFocusReason"
    , "MenuBarFocusReason"
    , "OtherFocusReason"
    , "NoFocusReason"
};

static QString qtscript_Qt_FocusReason_toStringHelper(Qt::FocusReason value)
{
    if ((value >= Qt::MouseFocusReason) && (value <= Qt::NoFocusReason))
        return qtscript_Qt_FocusReason_keys[static_cast<int>(value)-static_cast<int>(Qt::MouseFocusReason)];
    return QString();
}

static QScriptValue qtscript_Qt_FocusReason_toScriptValue(QScriptEngine *engine, const Qt::FocusReason &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_FocusReason_toStringHelper(value));
}

static void qtscript_Qt_FocusReason_fromScriptValue(const QScriptValue &value, Qt::FocusReason &out)
{
    out = qvariant_cast<Qt::FocusReason>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_FocusReason(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::MouseFocusReason) && (arg <= Qt::NoFocusReason))
        return qScriptValueFromValue(engine,  static_cast<Qt::FocusReason>(arg));
    return context->throwError(QString::fromLatin1("FocusReason(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_FocusReason_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::FocusReason value = qscriptvalue_cast<Qt::FocusReason>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_FocusReason_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::FocusReason value = qscriptvalue_cast<Qt::FocusReason>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_FocusReason_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_FocusReason_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_FocusReason,
        qtscript_Qt_FocusReason_valueOf, qtscript_Qt_FocusReason_toString);
    qScriptRegisterMetaType<Qt::FocusReason>(engine, qtscript_Qt_FocusReason_toScriptValue,
        qtscript_Qt_FocusReason_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 9; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_FocusReason_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_FocusReason_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::TileRule
//

static const Qt::TileRule qtscript_Qt_TileRule_values[] = {
    Qt::StretchTile
    , Qt::RepeatTile
    , Qt::RoundTile
};

static const char * const qtscript_Qt_TileRule_keys[] = {
    "StretchTile"
    , "RepeatTile"
    , "RoundTile"
};

static QString qtscript_Qt_TileRule_toStringHelper(Qt::TileRule value)
{
    if ((value >= Qt::StretchTile) && (value <= Qt::RoundTile))
        return qtscript_Qt_TileRule_keys[static_cast<int>(value)-static_cast<int>(Qt::StretchTile)];
    return QString();
}

static QScriptValue qtscript_Qt_TileRule_toScriptValue(QScriptEngine *engine, const Qt::TileRule &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_TileRule_toStringHelper(value));
}

static void qtscript_Qt_TileRule_fromScriptValue(const QScriptValue &value, Qt::TileRule &out)
{
    out = qvariant_cast<Qt::TileRule>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_TileRule(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::StretchTile) && (arg <= Qt::RoundTile))
        return qScriptValueFromValue(engine,  static_cast<Qt::TileRule>(arg));
    return context->throwError(QString::fromLatin1("TileRule(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_TileRule_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TileRule value = qscriptvalue_cast<Qt::TileRule>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_TileRule_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TileRule value = qscriptvalue_cast<Qt::TileRule>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_TileRule_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_TileRule_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_TileRule,
        qtscript_Qt_TileRule_valueOf, qtscript_Qt_TileRule_toString);
    qScriptRegisterMetaType<Qt::TileRule>(engine, qtscript_Qt_TileRule_toScriptValue,
        qtscript_Qt_TileRule_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_TileRule_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_TileRule_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::WhiteSpaceMode
//

static const Qt::WhiteSpaceMode qtscript_Qt_WhiteSpaceMode_values[] = {
    Qt::WhiteSpaceModeUndefined
    , Qt::WhiteSpaceNormal
    , Qt::WhiteSpacePre
    , Qt::WhiteSpaceNoWrap
};

static const char * const qtscript_Qt_WhiteSpaceMode_keys[] = {
    "WhiteSpaceModeUndefined"
    , "WhiteSpaceNormal"
    , "WhiteSpacePre"
    , "WhiteSpaceNoWrap"
};

static QString qtscript_Qt_WhiteSpaceMode_toStringHelper(Qt::WhiteSpaceMode value)
{
    if ((value >= Qt::WhiteSpaceModeUndefined) && (value <= Qt::WhiteSpaceNoWrap))
        return qtscript_Qt_WhiteSpaceMode_keys[static_cast<int>(value)-static_cast<int>(Qt::WhiteSpaceModeUndefined)];
    return QString();
}

static QScriptValue qtscript_Qt_WhiteSpaceMode_toScriptValue(QScriptEngine *engine, const Qt::WhiteSpaceMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_WhiteSpaceMode_toStringHelper(value));
}

static void qtscript_Qt_WhiteSpaceMode_fromScriptValue(const QScriptValue &value, Qt::WhiteSpaceMode &out)
{
    out = qvariant_cast<Qt::WhiteSpaceMode>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_WhiteSpaceMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::WhiteSpaceModeUndefined) && (arg <= Qt::WhiteSpaceNoWrap))
        return qScriptValueFromValue(engine,  static_cast<Qt::WhiteSpaceMode>(arg));
    return context->throwError(QString::fromLatin1("WhiteSpaceMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_WhiteSpaceMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WhiteSpaceMode value = qscriptvalue_cast<Qt::WhiteSpaceMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_WhiteSpaceMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WhiteSpaceMode value = qscriptvalue_cast<Qt::WhiteSpaceMode>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_WhiteSpaceMode_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_WhiteSpaceMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_WhiteSpaceMode,
        qtscript_Qt_WhiteSpaceMode_valueOf, qtscript_Qt_WhiteSpaceMode_toString);
    qScriptRegisterMetaType<Qt::WhiteSpaceMode>(engine, qtscript_Qt_WhiteSpaceMode_toScriptValue,
        qtscript_Qt_WhiteSpaceMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_WhiteSpaceMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_WhiteSpaceMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::AspectRatioMode
//

static const Qt::AspectRatioMode qtscript_Qt_AspectRatioMode_values[] = {
    Qt::IgnoreAspectRatio
    , Qt::KeepAspectRatio
    , Qt::KeepAspectRatioByExpanding
};

static const char * const qtscript_Qt_AspectRatioMode_keys[] = {
    "IgnoreAspectRatio"
    , "KeepAspectRatio"
    , "KeepAspectRatioByExpanding"
};

static QString qtscript_Qt_AspectRatioMode_toStringHelper(Qt::AspectRatioMode value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("AspectRatioMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_AspectRatioMode_toScriptValue(QScriptEngine *engine, const Qt::AspectRatioMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_AspectRatioMode_toStringHelper(value));
}

static void qtscript_Qt_AspectRatioMode_fromScriptValue(const QScriptValue &value, Qt::AspectRatioMode &out)
{
    out = qvariant_cast<Qt::AspectRatioMode>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_AspectRatioMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("AspectRatioMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::AspectRatioMode>(arg));
    return context->throwError(QString::fromLatin1("AspectRatioMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_AspectRatioMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::AspectRatioMode value = qscriptvalue_cast<Qt::AspectRatioMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_AspectRatioMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::AspectRatioMode value = qscriptvalue_cast<Qt::AspectRatioMode>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_AspectRatioMode_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_AspectRatioMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_AspectRatioMode,
        qtscript_Qt_AspectRatioMode_valueOf, qtscript_Qt_AspectRatioMode_toString);
    qScriptRegisterMetaType<Qt::AspectRatioMode>(engine, qtscript_Qt_AspectRatioMode_toScriptValue,
        qtscript_Qt_AspectRatioMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_AspectRatioMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_AspectRatioMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::SizeHint
//

static const Qt::SizeHint qtscript_Qt_SizeHint_values[] = {
    Qt::MinimumSize
    , Qt::PreferredSize
    , Qt::MaximumSize
    , Qt::MinimumDescent
    , Qt::NSizeHints
};

static const char * const qtscript_Qt_SizeHint_keys[] = {
    "MinimumSize"
    , "PreferredSize"
    , "MaximumSize"
    , "MinimumDescent"
    , "NSizeHints"
};

static QString qtscript_Qt_SizeHint_toStringHelper(Qt::SizeHint value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("SizeHint");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_SizeHint_toScriptValue(QScriptEngine *engine, const Qt::SizeHint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_SizeHint_toStringHelper(value));
}

static void qtscript_Qt_SizeHint_fromScriptValue(const QScriptValue &value, Qt::SizeHint &out)
{
    out = qvariant_cast<Qt::SizeHint>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_SizeHint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("SizeHint");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::SizeHint>(arg));
    return context->throwError(QString::fromLatin1("SizeHint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_SizeHint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::SizeHint value = qscriptvalue_cast<Qt::SizeHint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_SizeHint_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::SizeHint value = qscriptvalue_cast<Qt::SizeHint>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_SizeHint_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_SizeHint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_SizeHint,
        qtscript_Qt_SizeHint_valueOf, qtscript_Qt_SizeHint_toString);
    qScriptRegisterMetaType<Qt::SizeHint>(engine, qtscript_Qt_SizeHint_toScriptValue,
        qtscript_Qt_SizeHint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_SizeHint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_SizeHint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::AlignmentFlag
//

static const Qt::AlignmentFlag qtscript_Qt_AlignmentFlag_values[] = {
    Qt::AlignLeft
    , Qt::AlignRight
    , Qt::AlignHCenter
    , Qt::AlignJustify
    , Qt::AlignAbsolute
    , Qt::AlignHorizontal_Mask
    , Qt::AlignTop
    , Qt::AlignBottom
    , Qt::AlignVCenter
    , Qt::AlignCenter
    , Qt::AlignVertical_Mask
};

static const char * const qtscript_Qt_AlignmentFlag_keys[] = {
    "AlignLeft"
    , "AlignRight"
    , "AlignHCenter"
    , "AlignJustify"
    , "AlignAbsolute"
    , "AlignHorizontal_Mask"
    , "AlignTop"
    , "AlignBottom"
    , "AlignVCenter"
    , "AlignCenter"
    , "AlignVertical_Mask"
};

static QString qtscript_Qt_AlignmentFlag_toStringHelper(Qt::AlignmentFlag value)
{
    for (int i = 0; i < 11; ++i) {
        if (qtscript_Qt_AlignmentFlag_values[i] == value)
            return QString::fromLatin1(qtscript_Qt_AlignmentFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_Qt_AlignmentFlag_toScriptValue(QScriptEngine *engine, const Qt::AlignmentFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_AlignmentFlag_toStringHelper(value));
}

static void qtscript_Qt_AlignmentFlag_fromScriptValue(const QScriptValue &value, Qt::AlignmentFlag &out)
{
    out = qvariant_cast<Qt::AlignmentFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_AlignmentFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 11; ++i) {
        if (qtscript_Qt_AlignmentFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<Qt::AlignmentFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("AlignmentFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_AlignmentFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::AlignmentFlag value = qscriptvalue_cast<Qt::AlignmentFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_AlignmentFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::AlignmentFlag value = qscriptvalue_cast<Qt::AlignmentFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_AlignmentFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_AlignmentFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_AlignmentFlag,
        qtscript_Qt_AlignmentFlag_valueOf, qtscript_Qt_AlignmentFlag_toString);
    qScriptRegisterMetaType<Qt::AlignmentFlag>(engine, qtscript_Qt_AlignmentFlag_toScriptValue,
        qtscript_Qt_AlignmentFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 11; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_AlignmentFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_AlignmentFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::Alignment
//

static QScriptValue qtscript_Qt_Alignment_toScriptValue(QScriptEngine *engine, const Qt::Alignment &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_Alignment_fromScriptValue(const QScriptValue &value, Qt::Alignment &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::Alignment>())
        out = qvariant_cast<Qt::Alignment>(var);
    else if (var.userType() == qMetaTypeId<Qt::AlignmentFlag>())
        out = qvariant_cast<Qt::AlignmentFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_Alignment(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Alignment result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::Alignment>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::AlignmentFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("Alignment(): argument %0 is not of type AlignmentFlag").arg(i));
            }
            result |= qvariant_cast<Qt::AlignmentFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_Alignment_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Alignment value = qscriptvalue_cast<Qt::Alignment>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_Alignment_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Alignment value = qscriptvalue_cast<Qt::Alignment>(context->thisObject());
    QString result;
    for (int i = 0; i < 11; ++i) {
        if ((value & qtscript_Qt_AlignmentFlag_values[i]) == qtscript_Qt_AlignmentFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_AlignmentFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_Alignment_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::Alignment>() == otherObj.value<Qt::Alignment>())));
}

static QScriptValue qtscript_create_Qt_Alignment_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_Alignment, qtscript_Qt_Alignment_valueOf,
        qtscript_Qt_Alignment_toString, qtscript_Qt_Alignment_equals);
    qScriptRegisterMetaType<Qt::Alignment>(engine, qtscript_Qt_Alignment_toScriptValue,
        qtscript_Qt_Alignment_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::ContextMenuPolicy
//

static const Qt::ContextMenuPolicy qtscript_Qt_ContextMenuPolicy_values[] = {
    Qt::NoContextMenu
    , Qt::DefaultContextMenu
    , Qt::ActionsContextMenu
    , Qt::CustomContextMenu
    , Qt::PreventContextMenu
};

static const char * const qtscript_Qt_ContextMenuPolicy_keys[] = {
    "NoContextMenu"
    , "DefaultContextMenu"
    , "ActionsContextMenu"
    , "CustomContextMenu"
    , "PreventContextMenu"
};

static QString qtscript_Qt_ContextMenuPolicy_toStringHelper(Qt::ContextMenuPolicy value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ContextMenuPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_ContextMenuPolicy_toScriptValue(QScriptEngine *engine, const Qt::ContextMenuPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ContextMenuPolicy_toStringHelper(value));
}

static void qtscript_Qt_ContextMenuPolicy_fromScriptValue(const QScriptValue &value, Qt::ContextMenuPolicy &out)
{
    out = qvariant_cast<Qt::ContextMenuPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ContextMenuPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ContextMenuPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::ContextMenuPolicy>(arg));
    return context->throwError(QString::fromLatin1("ContextMenuPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ContextMenuPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ContextMenuPolicy value = qscriptvalue_cast<Qt::ContextMenuPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ContextMenuPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ContextMenuPolicy value = qscriptvalue_cast<Qt::ContextMenuPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ContextMenuPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ContextMenuPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ContextMenuPolicy,
        qtscript_Qt_ContextMenuPolicy_valueOf, qtscript_Qt_ContextMenuPolicy_toString);
    qScriptRegisterMetaType<Qt::ContextMenuPolicy>(engine, qtscript_Qt_ContextMenuPolicy_toScriptValue,
        qtscript_Qt_ContextMenuPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ContextMenuPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ContextMenuPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::DockWidgetArea
//

static const Qt::DockWidgetArea qtscript_Qt_DockWidgetArea_values[] = {
    Qt::NoDockWidgetArea
    , Qt::LeftDockWidgetArea
    , Qt::RightDockWidgetArea
    , Qt::TopDockWidgetArea
    , Qt::BottomDockWidgetArea
    , Qt::DockWidgetArea_Mask
};

static const char * const qtscript_Qt_DockWidgetArea_keys[] = {
    "NoDockWidgetArea"
    , "LeftDockWidgetArea"
    , "RightDockWidgetArea"
    , "TopDockWidgetArea"
    , "BottomDockWidgetArea"
    , "DockWidgetArea_Mask"
};

static QString qtscript_Qt_DockWidgetArea_toStringHelper(Qt::DockWidgetArea value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("DockWidgetArea");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_DockWidgetArea_toScriptValue(QScriptEngine *engine, const Qt::DockWidgetArea &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_DockWidgetArea_toStringHelper(value));
}

static void qtscript_Qt_DockWidgetArea_fromScriptValue(const QScriptValue &value, Qt::DockWidgetArea &out)
{
    out = qvariant_cast<Qt::DockWidgetArea>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_DockWidgetArea(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("DockWidgetArea");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::DockWidgetArea>(arg));
    return context->throwError(QString::fromLatin1("DockWidgetArea(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_DockWidgetArea_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DockWidgetArea value = qscriptvalue_cast<Qt::DockWidgetArea>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_DockWidgetArea_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DockWidgetArea value = qscriptvalue_cast<Qt::DockWidgetArea>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_DockWidgetArea_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_DockWidgetArea_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_DockWidgetArea,
        qtscript_Qt_DockWidgetArea_valueOf, qtscript_Qt_DockWidgetArea_toString);
    qScriptRegisterMetaType<Qt::DockWidgetArea>(engine, qtscript_Qt_DockWidgetArea_toScriptValue,
        qtscript_Qt_DockWidgetArea_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_DockWidgetArea_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_DockWidgetArea_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::DockWidgetAreas
//

static QScriptValue qtscript_Qt_DockWidgetAreas_toScriptValue(QScriptEngine *engine, const Qt::DockWidgetAreas &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_DockWidgetAreas_fromScriptValue(const QScriptValue &value, Qt::DockWidgetAreas &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::DockWidgetAreas>())
        out = qvariant_cast<Qt::DockWidgetAreas>(var);
    else if (var.userType() == qMetaTypeId<Qt::DockWidgetArea>())
        out = qvariant_cast<Qt::DockWidgetArea>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_DockWidgetAreas(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DockWidgetAreas result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::DockWidgetAreas>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::DockWidgetArea>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("DockWidgetAreas(): argument %0 is not of type DockWidgetArea").arg(i));
            }
            result |= qvariant_cast<Qt::DockWidgetArea>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_DockWidgetAreas_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DockWidgetAreas value = qscriptvalue_cast<Qt::DockWidgetAreas>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_DockWidgetAreas_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DockWidgetAreas value = qscriptvalue_cast<Qt::DockWidgetAreas>(context->thisObject());
    QString result;
    for (int i = 0; i < 6; ++i) {
        if ((value & qtscript_Qt_DockWidgetArea_values[i]) == qtscript_Qt_DockWidgetArea_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_DockWidgetArea_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_DockWidgetAreas_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::DockWidgetAreas>() == otherObj.value<Qt::DockWidgetAreas>())));
}

static QScriptValue qtscript_create_Qt_DockWidgetAreas_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_DockWidgetAreas, qtscript_Qt_DockWidgetAreas_valueOf,
        qtscript_Qt_DockWidgetAreas_toString, qtscript_Qt_DockWidgetAreas_equals);
    qScriptRegisterMetaType<Qt::DockWidgetAreas>(engine, qtscript_Qt_DockWidgetAreas_toScriptValue,
        qtscript_Qt_DockWidgetAreas_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::UIEffect
//

static const Qt::UIEffect qtscript_Qt_UIEffect_values[] = {
    Qt::UI_General
    , Qt::UI_AnimateMenu
    , Qt::UI_FadeMenu
    , Qt::UI_AnimateCombo
    , Qt::UI_AnimateTooltip
    , Qt::UI_FadeTooltip
    , Qt::UI_AnimateToolBox
};

static const char * const qtscript_Qt_UIEffect_keys[] = {
    "UI_General"
    , "UI_AnimateMenu"
    , "UI_FadeMenu"
    , "UI_AnimateCombo"
    , "UI_AnimateTooltip"
    , "UI_FadeTooltip"
    , "UI_AnimateToolBox"
};

static QString qtscript_Qt_UIEffect_toStringHelper(Qt::UIEffect value)
{
    if ((value >= Qt::UI_General) && (value <= Qt::UI_AnimateToolBox))
        return qtscript_Qt_UIEffect_keys[static_cast<int>(value)-static_cast<int>(Qt::UI_General)];
    return QString();
}

static QScriptValue qtscript_Qt_UIEffect_toScriptValue(QScriptEngine *engine, const Qt::UIEffect &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_UIEffect_toStringHelper(value));
}

static void qtscript_Qt_UIEffect_fromScriptValue(const QScriptValue &value, Qt::UIEffect &out)
{
    out = qvariant_cast<Qt::UIEffect>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_UIEffect(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::UI_General) && (arg <= Qt::UI_AnimateToolBox))
        return qScriptValueFromValue(engine,  static_cast<Qt::UIEffect>(arg));
    return context->throwError(QString::fromLatin1("UIEffect(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_UIEffect_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::UIEffect value = qscriptvalue_cast<Qt::UIEffect>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_UIEffect_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::UIEffect value = qscriptvalue_cast<Qt::UIEffect>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_UIEffect_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_UIEffect_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_UIEffect,
        qtscript_Qt_UIEffect_valueOf, qtscript_Qt_UIEffect_toString);
    qScriptRegisterMetaType<Qt::UIEffect>(engine, qtscript_Qt_UIEffect_toScriptValue,
        qtscript_Qt_UIEffect_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_UIEffect_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_UIEffect_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::AnchorPoint
//

static const Qt::AnchorPoint qtscript_Qt_AnchorPoint_values[] = {
    Qt::AnchorLeft
    , Qt::AnchorHorizontalCenter
    , Qt::AnchorRight
    , Qt::AnchorTop
    , Qt::AnchorVerticalCenter
    , Qt::AnchorBottom
};

static const char * const qtscript_Qt_AnchorPoint_keys[] = {
    "AnchorLeft"
    , "AnchorHorizontalCenter"
    , "AnchorRight"
    , "AnchorTop"
    , "AnchorVerticalCenter"
    , "AnchorBottom"
};

static QString qtscript_Qt_AnchorPoint_toStringHelper(Qt::AnchorPoint value)
{
    if ((value >= Qt::AnchorLeft) && (value <= Qt::AnchorBottom))
        return qtscript_Qt_AnchorPoint_keys[static_cast<int>(value)-static_cast<int>(Qt::AnchorLeft)];
    return QString();
}

static QScriptValue qtscript_Qt_AnchorPoint_toScriptValue(QScriptEngine *engine, const Qt::AnchorPoint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_AnchorPoint_toStringHelper(value));
}

static void qtscript_Qt_AnchorPoint_fromScriptValue(const QScriptValue &value, Qt::AnchorPoint &out)
{
    out = qvariant_cast<Qt::AnchorPoint>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_AnchorPoint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::AnchorLeft) && (arg <= Qt::AnchorBottom))
        return qScriptValueFromValue(engine,  static_cast<Qt::AnchorPoint>(arg));
    return context->throwError(QString::fromLatin1("AnchorPoint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_AnchorPoint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::AnchorPoint value = qscriptvalue_cast<Qt::AnchorPoint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_AnchorPoint_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::AnchorPoint value = qscriptvalue_cast<Qt::AnchorPoint>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_AnchorPoint_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_AnchorPoint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_AnchorPoint,
        qtscript_Qt_AnchorPoint_valueOf, qtscript_Qt_AnchorPoint_toString);
    qScriptRegisterMetaType<Qt::AnchorPoint>(engine, qtscript_Qt_AnchorPoint_toScriptValue,
        qtscript_Qt_AnchorPoint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_AnchorPoint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_AnchorPoint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::GlobalColor
//

static const Qt::GlobalColor qtscript_Qt_GlobalColor_values[] = {
    Qt::color0
    , Qt::color1
    , Qt::black
    , Qt::white
    , Qt::darkGray
    , Qt::gray
    , Qt::lightGray
    , Qt::red
    , Qt::green
    , Qt::blue
    , Qt::cyan
    , Qt::magenta
    , Qt::yellow
    , Qt::darkRed
    , Qt::darkGreen
    , Qt::darkBlue
    , Qt::darkCyan
    , Qt::darkMagenta
    , Qt::darkYellow
    , Qt::transparent
};

static const char * const qtscript_Qt_GlobalColor_keys[] = {
    "color0"
    , "color1"
    , "black"
    , "white"
    , "darkGray"
    , "gray"
    , "lightGray"
    , "red"
    , "green"
    , "blue"
    , "cyan"
    , "magenta"
    , "yellow"
    , "darkRed"
    , "darkGreen"
    , "darkBlue"
    , "darkCyan"
    , "darkMagenta"
    , "darkYellow"
    , "transparent"
};

static QString qtscript_Qt_GlobalColor_toStringHelper(Qt::GlobalColor value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("GlobalColor");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_GlobalColor_toScriptValue(QScriptEngine *engine, const Qt::GlobalColor &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_GlobalColor_toStringHelper(value));
}

static void qtscript_Qt_GlobalColor_fromScriptValue(const QScriptValue &value, Qt::GlobalColor &out)
{
    out = qvariant_cast<Qt::GlobalColor>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_GlobalColor(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("GlobalColor");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::GlobalColor>(arg));
    return context->throwError(QString::fromLatin1("GlobalColor(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_GlobalColor_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::GlobalColor value = qscriptvalue_cast<Qt::GlobalColor>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_GlobalColor_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::GlobalColor value = qscriptvalue_cast<Qt::GlobalColor>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_GlobalColor_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_GlobalColor_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_GlobalColor,
        qtscript_Qt_GlobalColor_valueOf, qtscript_Qt_GlobalColor_toString);
    qScriptRegisterMetaType<Qt::GlobalColor>(engine, qtscript_Qt_GlobalColor_toScriptValue,
        qtscript_Qt_GlobalColor_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 20; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_GlobalColor_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_GlobalColor_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::KeyboardModifier
//

static const Qt::KeyboardModifier qtscript_Qt_KeyboardModifier_values[] = {
    Qt::KeyboardModifierMask
    , Qt::NoModifier
    , Qt::ShiftModifier
    , Qt::ControlModifier
    , Qt::AltModifier
    , Qt::MetaModifier
    , Qt::KeypadModifier
    , Qt::GroupSwitchModifier
};

static const char * const qtscript_Qt_KeyboardModifier_keys[] = {
    "KeyboardModifierMask"
    , "NoModifier"
    , "ShiftModifier"
    , "ControlModifier"
    , "AltModifier"
    , "MetaModifier"
    , "KeypadModifier"
    , "GroupSwitchModifier"
};

static QString qtscript_Qt_KeyboardModifier_toStringHelper(Qt::KeyboardModifier value)
{
    for (int i = 0; i < 8; ++i) {
        if (qtscript_Qt_KeyboardModifier_values[i] == value)
            return QString::fromLatin1(qtscript_Qt_KeyboardModifier_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_Qt_KeyboardModifier_toScriptValue(QScriptEngine *engine, const Qt::KeyboardModifier &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_KeyboardModifier_toStringHelper(value));
}

static void qtscript_Qt_KeyboardModifier_fromScriptValue(const QScriptValue &value, Qt::KeyboardModifier &out)
{
    out = qvariant_cast<Qt::KeyboardModifier>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_KeyboardModifier(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 8; ++i) {
        if (qtscript_Qt_KeyboardModifier_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<Qt::KeyboardModifier>(arg));
    }
    return context->throwError(QString::fromLatin1("KeyboardModifier(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_KeyboardModifier_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::KeyboardModifier value = qscriptvalue_cast<Qt::KeyboardModifier>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_KeyboardModifier_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::KeyboardModifier value = qscriptvalue_cast<Qt::KeyboardModifier>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_KeyboardModifier_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_KeyboardModifier_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_KeyboardModifier,
        qtscript_Qt_KeyboardModifier_valueOf, qtscript_Qt_KeyboardModifier_toString);
    qScriptRegisterMetaType<Qt::KeyboardModifier>(engine, qtscript_Qt_KeyboardModifier_toScriptValue,
        qtscript_Qt_KeyboardModifier_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_KeyboardModifier_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_KeyboardModifier_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::KeyboardModifiers
//

static QScriptValue qtscript_Qt_KeyboardModifiers_toScriptValue(QScriptEngine *engine, const Qt::KeyboardModifiers &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_KeyboardModifiers_fromScriptValue(const QScriptValue &value, Qt::KeyboardModifiers &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::KeyboardModifiers>())
        out = qvariant_cast<Qt::KeyboardModifiers>(var);
    else if (var.userType() == qMetaTypeId<Qt::KeyboardModifier>())
        out = qvariant_cast<Qt::KeyboardModifier>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_KeyboardModifiers(QScriptContext *context, QScriptEngine *engine)
{
    Qt::KeyboardModifiers result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::KeyboardModifiers>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::KeyboardModifier>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("KeyboardModifiers(): argument %0 is not of type KeyboardModifier").arg(i));
            }
            result |= qvariant_cast<Qt::KeyboardModifier>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_KeyboardModifiers_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::KeyboardModifiers value = qscriptvalue_cast<Qt::KeyboardModifiers>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_KeyboardModifiers_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::KeyboardModifiers value = qscriptvalue_cast<Qt::KeyboardModifiers>(context->thisObject());
    QString result;
    for (int i = 0; i < 8; ++i) {
        if ((value & qtscript_Qt_KeyboardModifier_values[i]) == qtscript_Qt_KeyboardModifier_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_KeyboardModifier_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_KeyboardModifiers_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::KeyboardModifiers>() == otherObj.value<Qt::KeyboardModifiers>())));
}

static QScriptValue qtscript_create_Qt_KeyboardModifiers_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_KeyboardModifiers, qtscript_Qt_KeyboardModifiers_valueOf,
        qtscript_Qt_KeyboardModifiers_toString, qtscript_Qt_KeyboardModifiers_equals);
    qScriptRegisterMetaType<Qt::KeyboardModifiers>(engine, qtscript_Qt_KeyboardModifiers_toScriptValue,
        qtscript_Qt_KeyboardModifiers_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::NavigationMode
//

static const Qt::NavigationMode qtscript_Qt_NavigationMode_values[] = {
    Qt::NavigationModeNone
    , Qt::NavigationModeKeypadTabOrder
    , Qt::NavigationModeKeypadDirectional
    , Qt::NavigationModeCursorAuto
    , Qt::NavigationModeCursorForceVisible
};

static const char * const qtscript_Qt_NavigationMode_keys[] = {
    "NavigationModeNone"
    , "NavigationModeKeypadTabOrder"
    , "NavigationModeKeypadDirectional"
    , "NavigationModeCursorAuto"
    , "NavigationModeCursorForceVisible"
};

static QString qtscript_Qt_NavigationMode_toStringHelper(Qt::NavigationMode value)
{
    if ((value >= Qt::NavigationModeNone) && (value <= Qt::NavigationModeCursorForceVisible))
        return qtscript_Qt_NavigationMode_keys[static_cast<int>(value)-static_cast<int>(Qt::NavigationModeNone)];
    return QString();
}

static QScriptValue qtscript_Qt_NavigationMode_toScriptValue(QScriptEngine *engine, const Qt::NavigationMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_NavigationMode_toStringHelper(value));
}

static void qtscript_Qt_NavigationMode_fromScriptValue(const QScriptValue &value, Qt::NavigationMode &out)
{
    out = qvariant_cast<Qt::NavigationMode>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_NavigationMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::NavigationModeNone) && (arg <= Qt::NavigationModeCursorForceVisible))
        return qScriptValueFromValue(engine,  static_cast<Qt::NavigationMode>(arg));
    return context->throwError(QString::fromLatin1("NavigationMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_NavigationMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::NavigationMode value = qscriptvalue_cast<Qt::NavigationMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_NavigationMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::NavigationMode value = qscriptvalue_cast<Qt::NavigationMode>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_NavigationMode_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_NavigationMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_NavigationMode,
        qtscript_Qt_NavigationMode_valueOf, qtscript_Qt_NavigationMode_toString);
    qScriptRegisterMetaType<Qt::NavigationMode>(engine, qtscript_Qt_NavigationMode_toScriptValue,
        qtscript_Qt_NavigationMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_NavigationMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_NavigationMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ItemDataRole
//

static const Qt::ItemDataRole qtscript_Qt_ItemDataRole_values[] = {
    Qt::DisplayRole
    , Qt::DecorationRole
    , Qt::EditRole
    , Qt::ToolTipRole
    , Qt::StatusTipRole
    , Qt::WhatsThisRole
    , Qt::FontRole
    , Qt::TextAlignmentRole
    , Qt::BackgroundColorRole
    , Qt::TextColorRole
    , Qt::CheckStateRole
    , Qt::AccessibleTextRole
    , Qt::AccessibleDescriptionRole
    , Qt::SizeHintRole
    , Qt::InitialSortOrderRole
    , Qt::DisplayPropertyRole
    , Qt::DecorationPropertyRole
    , Qt::ToolTipPropertyRole
    , Qt::StatusTipPropertyRole
    , Qt::WhatsThisPropertyRole
    , Qt::UserRole
};

static const char * const qtscript_Qt_ItemDataRole_keys[] = {
    "DisplayRole"
    , "DecorationRole"
    , "EditRole"
    , "ToolTipRole"
    , "StatusTipRole"
    , "WhatsThisRole"
    , "FontRole"
    , "TextAlignmentRole"
    , "BackgroundColorRole"
    , "TextColorRole"
    , "CheckStateRole"
    , "AccessibleTextRole"
    , "AccessibleDescriptionRole"
    , "SizeHintRole"
    , "InitialSortOrderRole"
    , "DisplayPropertyRole"
    , "DecorationPropertyRole"
    , "ToolTipPropertyRole"
    , "StatusTipPropertyRole"
    , "WhatsThisPropertyRole"
    , "UserRole"
};

static QString qtscript_Qt_ItemDataRole_toStringHelper(Qt::ItemDataRole value)
{
    for (int i = 0; i < 21; ++i) {
        if (qtscript_Qt_ItemDataRole_values[i] == value)
            return QString::fromLatin1(qtscript_Qt_ItemDataRole_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_Qt_ItemDataRole_toScriptValue(QScriptEngine *engine, const Qt::ItemDataRole &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ItemDataRole_toStringHelper(value));
}

static void qtscript_Qt_ItemDataRole_fromScriptValue(const QScriptValue &value, Qt::ItemDataRole &out)
{
    out = qvariant_cast<Qt::ItemDataRole>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ItemDataRole(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 21; ++i) {
        if (qtscript_Qt_ItemDataRole_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<Qt::ItemDataRole>(arg));
    }
    return context->throwError(QString::fromLatin1("ItemDataRole(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ItemDataRole_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ItemDataRole value = qscriptvalue_cast<Qt::ItemDataRole>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ItemDataRole_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ItemDataRole value = qscriptvalue_cast<Qt::ItemDataRole>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ItemDataRole_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ItemDataRole_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ItemDataRole,
        qtscript_Qt_ItemDataRole_valueOf, qtscript_Qt_ItemDataRole_toString);
    qScriptRegisterMetaType<Qt::ItemDataRole>(engine, qtscript_Qt_ItemDataRole_toScriptValue,
        qtscript_Qt_ItemDataRole_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 21; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ItemDataRole_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ItemDataRole_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ScrollBarPolicy
//

static const Qt::ScrollBarPolicy qtscript_Qt_ScrollBarPolicy_values[] = {
    Qt::ScrollBarAsNeeded
    , Qt::ScrollBarAlwaysOff
    , Qt::ScrollBarAlwaysOn
};

static const char * const qtscript_Qt_ScrollBarPolicy_keys[] = {
    "ScrollBarAsNeeded"
    , "ScrollBarAlwaysOff"
    , "ScrollBarAlwaysOn"
};

static QString qtscript_Qt_ScrollBarPolicy_toStringHelper(Qt::ScrollBarPolicy value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ScrollBarPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_ScrollBarPolicy_toScriptValue(QScriptEngine *engine, const Qt::ScrollBarPolicy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ScrollBarPolicy_toStringHelper(value));
}

static void qtscript_Qt_ScrollBarPolicy_fromScriptValue(const QScriptValue &value, Qt::ScrollBarPolicy &out)
{
    out = qvariant_cast<Qt::ScrollBarPolicy>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ScrollBarPolicy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ScrollBarPolicy");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::ScrollBarPolicy>(arg));
    return context->throwError(QString::fromLatin1("ScrollBarPolicy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ScrollBarPolicy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ScrollBarPolicy value = qscriptvalue_cast<Qt::ScrollBarPolicy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ScrollBarPolicy_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ScrollBarPolicy value = qscriptvalue_cast<Qt::ScrollBarPolicy>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ScrollBarPolicy_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ScrollBarPolicy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ScrollBarPolicy,
        qtscript_Qt_ScrollBarPolicy_valueOf, qtscript_Qt_ScrollBarPolicy_toString);
    qScriptRegisterMetaType<Qt::ScrollBarPolicy>(engine, qtscript_Qt_ScrollBarPolicy_toScriptValue,
        qtscript_Qt_ScrollBarPolicy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ScrollBarPolicy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ScrollBarPolicy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::InputMethodHint
//

static const Qt::InputMethodHint qtscript_Qt_InputMethodHint_values[] = {
    Qt::ImhExclusiveInputMask
    , Qt::ImhNone
    , Qt::ImhHiddenText
    , Qt::ImhNoAutoUppercase
    , Qt::ImhPreferNumbers
    , Qt::ImhPreferUppercase
    , Qt::ImhPreferLowercase
    , Qt::ImhNoPredictiveText
    , Qt::ImhDigitsOnly
    , Qt::ImhFormattedNumbersOnly
    , Qt::ImhUppercaseOnly
    , Qt::ImhLowercaseOnly
    , Qt::ImhDialableCharactersOnly
    , Qt::ImhEmailCharactersOnly
    , Qt::ImhUrlCharactersOnly
};

static const char * const qtscript_Qt_InputMethodHint_keys[] = {
    "ImhExclusiveInputMask"
    , "ImhNone"
    , "ImhHiddenText"
    , "ImhNoAutoUppercase"
    , "ImhPreferNumbers"
    , "ImhPreferUppercase"
    , "ImhPreferLowercase"
    , "ImhNoPredictiveText"
    , "ImhDigitsOnly"
    , "ImhFormattedNumbersOnly"
    , "ImhUppercaseOnly"
    , "ImhLowercaseOnly"
    , "ImhDialableCharactersOnly"
    , "ImhEmailCharactersOnly"
    , "ImhUrlCharactersOnly"
};

static QString qtscript_Qt_InputMethodHint_toStringHelper(Qt::InputMethodHint value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("InputMethodHint");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_InputMethodHint_toScriptValue(QScriptEngine *engine, const Qt::InputMethodHint &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_InputMethodHint_toStringHelper(value));
}

static void qtscript_Qt_InputMethodHint_fromScriptValue(const QScriptValue &value, Qt::InputMethodHint &out)
{
    out = qvariant_cast<Qt::InputMethodHint>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_InputMethodHint(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("InputMethodHint");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::InputMethodHint>(arg));
    return context->throwError(QString::fromLatin1("InputMethodHint(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_InputMethodHint_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::InputMethodHint value = qscriptvalue_cast<Qt::InputMethodHint>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_InputMethodHint_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::InputMethodHint value = qscriptvalue_cast<Qt::InputMethodHint>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_InputMethodHint_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_InputMethodHint_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_InputMethodHint,
        qtscript_Qt_InputMethodHint_valueOf, qtscript_Qt_InputMethodHint_toString);
    qScriptRegisterMetaType<Qt::InputMethodHint>(engine, qtscript_Qt_InputMethodHint_toScriptValue,
        qtscript_Qt_InputMethodHint_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 15; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_InputMethodHint_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_InputMethodHint_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::InputMethodHints
//

static QScriptValue qtscript_Qt_InputMethodHints_toScriptValue(QScriptEngine *engine, const Qt::InputMethodHints &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_InputMethodHints_fromScriptValue(const QScriptValue &value, Qt::InputMethodHints &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::InputMethodHints>())
        out = qvariant_cast<Qt::InputMethodHints>(var);
    else if (var.userType() == qMetaTypeId<Qt::InputMethodHint>())
        out = qvariant_cast<Qt::InputMethodHint>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_InputMethodHints(QScriptContext *context, QScriptEngine *engine)
{
    Qt::InputMethodHints result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::InputMethodHints>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::InputMethodHint>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("InputMethodHints(): argument %0 is not of type InputMethodHint").arg(i));
            }
            result |= qvariant_cast<Qt::InputMethodHint>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_InputMethodHints_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::InputMethodHints value = qscriptvalue_cast<Qt::InputMethodHints>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_InputMethodHints_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::InputMethodHints value = qscriptvalue_cast<Qt::InputMethodHints>(context->thisObject());
    QString result;
    for (int i = 0; i < 15; ++i) {
        if ((value & qtscript_Qt_InputMethodHint_values[i]) == qtscript_Qt_InputMethodHint_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_InputMethodHint_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_InputMethodHints_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::InputMethodHints>() == otherObj.value<Qt::InputMethodHints>())));
}

static QScriptValue qtscript_create_Qt_InputMethodHints_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_InputMethodHints, qtscript_Qt_InputMethodHints_valueOf,
        qtscript_Qt_InputMethodHints_toString, qtscript_Qt_InputMethodHints_equals);
    qScriptRegisterMetaType<Qt::InputMethodHints>(engine, qtscript_Qt_InputMethodHints_toScriptValue,
        qtscript_Qt_InputMethodHints_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::AnchorAttribute
//

static const Qt::AnchorAttribute qtscript_Qt_AnchorAttribute_values[] = {
    Qt::AnchorName
    , Qt::AnchorHref
};

static const char * const qtscript_Qt_AnchorAttribute_keys[] = {
    "AnchorName"
    , "AnchorHref"
};

static QString qtscript_Qt_AnchorAttribute_toStringHelper(Qt::AnchorAttribute value)
{
    if ((value >= Qt::AnchorName) && (value <= Qt::AnchorHref))
        return qtscript_Qt_AnchorAttribute_keys[static_cast<int>(value)-static_cast<int>(Qt::AnchorName)];
    return QString();
}

static QScriptValue qtscript_Qt_AnchorAttribute_toScriptValue(QScriptEngine *engine, const Qt::AnchorAttribute &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_AnchorAttribute_toStringHelper(value));
}

static void qtscript_Qt_AnchorAttribute_fromScriptValue(const QScriptValue &value, Qt::AnchorAttribute &out)
{
    out = qvariant_cast<Qt::AnchorAttribute>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_AnchorAttribute(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::AnchorName) && (arg <= Qt::AnchorHref))
        return qScriptValueFromValue(engine,  static_cast<Qt::AnchorAttribute>(arg));
    return context->throwError(QString::fromLatin1("AnchorAttribute(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_AnchorAttribute_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::AnchorAttribute value = qscriptvalue_cast<Qt::AnchorAttribute>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_AnchorAttribute_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::AnchorAttribute value = qscriptvalue_cast<Qt::AnchorAttribute>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_AnchorAttribute_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_AnchorAttribute_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_AnchorAttribute,
        qtscript_Qt_AnchorAttribute_valueOf, qtscript_Qt_AnchorAttribute_toString);
    qScriptRegisterMetaType<Qt::AnchorAttribute>(engine, qtscript_Qt_AnchorAttribute_toScriptValue,
        qtscript_Qt_AnchorAttribute_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_AnchorAttribute_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_AnchorAttribute_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::WindowModality
//

static const Qt::WindowModality qtscript_Qt_WindowModality_values[] = {
    Qt::NonModal
    , Qt::WindowModal
    , Qt::ApplicationModal
};

static const char * const qtscript_Qt_WindowModality_keys[] = {
    "NonModal"
    , "WindowModal"
    , "ApplicationModal"
};

static QString qtscript_Qt_WindowModality_toStringHelper(Qt::WindowModality value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("WindowModality");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_WindowModality_toScriptValue(QScriptEngine *engine, const Qt::WindowModality &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_WindowModality_toStringHelper(value));
}

static void qtscript_Qt_WindowModality_fromScriptValue(const QScriptValue &value, Qt::WindowModality &out)
{
    out = qvariant_cast<Qt::WindowModality>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_WindowModality(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("WindowModality");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::WindowModality>(arg));
    return context->throwError(QString::fromLatin1("WindowModality(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_WindowModality_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowModality value = qscriptvalue_cast<Qt::WindowModality>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_WindowModality_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowModality value = qscriptvalue_cast<Qt::WindowModality>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_WindowModality_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_WindowModality_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_WindowModality,
        qtscript_Qt_WindowModality_valueOf, qtscript_Qt_WindowModality_toString);
    qScriptRegisterMetaType<Qt::WindowModality>(engine, qtscript_Qt_WindowModality_toScriptValue,
        qtscript_Qt_WindowModality_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_WindowModality_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_WindowModality_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::SortOrder
//

static const Qt::SortOrder qtscript_Qt_SortOrder_values[] = {
    Qt::AscendingOrder
    , Qt::DescendingOrder
};

static const char * const qtscript_Qt_SortOrder_keys[] = {
    "AscendingOrder"
    , "DescendingOrder"
};

static QString qtscript_Qt_SortOrder_toStringHelper(Qt::SortOrder value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("SortOrder");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_SortOrder_toScriptValue(QScriptEngine *engine, const Qt::SortOrder &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_SortOrder_toStringHelper(value));
}

static void qtscript_Qt_SortOrder_fromScriptValue(const QScriptValue &value, Qt::SortOrder &out)
{
    out = qvariant_cast<Qt::SortOrder>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_SortOrder(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("SortOrder");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::SortOrder>(arg));
    return context->throwError(QString::fromLatin1("SortOrder(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_SortOrder_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::SortOrder value = qscriptvalue_cast<Qt::SortOrder>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_SortOrder_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::SortOrder value = qscriptvalue_cast<Qt::SortOrder>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_SortOrder_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_SortOrder_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_SortOrder,
        qtscript_Qt_SortOrder_valueOf, qtscript_Qt_SortOrder_toString);
    qScriptRegisterMetaType<Qt::SortOrder>(engine, qtscript_Qt_SortOrder_toScriptValue,
        qtscript_Qt_SortOrder_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_SortOrder_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_SortOrder_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::PenStyle
//

static const Qt::PenStyle qtscript_Qt_PenStyle_values[] = {
    Qt::NoPen
    , Qt::SolidLine
    , Qt::DashLine
    , Qt::DotLine
    , Qt::DashDotLine
    , Qt::DashDotDotLine
    , Qt::CustomDashLine
    , Qt::MPenStyle
};

static const char * const qtscript_Qt_PenStyle_keys[] = {
    "NoPen"
    , "SolidLine"
    , "DashLine"
    , "DotLine"
    , "DashDotLine"
    , "DashDotDotLine"
    , "CustomDashLine"
    , "MPenStyle"
};

static QString qtscript_Qt_PenStyle_toStringHelper(Qt::PenStyle value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("PenStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_PenStyle_toScriptValue(QScriptEngine *engine, const Qt::PenStyle &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_PenStyle_toStringHelper(value));
}

static void qtscript_Qt_PenStyle_fromScriptValue(const QScriptValue &value, Qt::PenStyle &out)
{
    out = qvariant_cast<Qt::PenStyle>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_PenStyle(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("PenStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::PenStyle>(arg));
    return context->throwError(QString::fromLatin1("PenStyle(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_PenStyle_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::PenStyle value = qscriptvalue_cast<Qt::PenStyle>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_PenStyle_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::PenStyle value = qscriptvalue_cast<Qt::PenStyle>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_PenStyle_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_PenStyle_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_PenStyle,
        qtscript_Qt_PenStyle_valueOf, qtscript_Qt_PenStyle_toString);
    qScriptRegisterMetaType<Qt::PenStyle>(engine, qtscript_Qt_PenStyle_toScriptValue,
        qtscript_Qt_PenStyle_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_PenStyle_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_PenStyle_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ItemFlag
//

static const Qt::ItemFlag qtscript_Qt_ItemFlag_values[] = {
    Qt::NoItemFlags
    , Qt::ItemIsSelectable
    , Qt::ItemIsEditable
    , Qt::ItemIsDragEnabled
    , Qt::ItemIsDropEnabled
    , Qt::ItemIsUserCheckable
    , Qt::ItemIsEnabled
    , Qt::ItemIsTristate
};

static const char * const qtscript_Qt_ItemFlag_keys[] = {
    "NoItemFlags"
    , "ItemIsSelectable"
    , "ItemIsEditable"
    , "ItemIsDragEnabled"
    , "ItemIsDropEnabled"
    , "ItemIsUserCheckable"
    , "ItemIsEnabled"
    , "ItemIsTristate"
};

static QString qtscript_Qt_ItemFlag_toStringHelper(Qt::ItemFlag value)
{
    for (int i = 0; i < 8; ++i) {
        if (qtscript_Qt_ItemFlag_values[i] == value)
            return QString::fromLatin1(qtscript_Qt_ItemFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_Qt_ItemFlag_toScriptValue(QScriptEngine *engine, const Qt::ItemFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ItemFlag_toStringHelper(value));
}

static void qtscript_Qt_ItemFlag_fromScriptValue(const QScriptValue &value, Qt::ItemFlag &out)
{
    out = qvariant_cast<Qt::ItemFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ItemFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 8; ++i) {
        if (qtscript_Qt_ItemFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<Qt::ItemFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("ItemFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ItemFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ItemFlag value = qscriptvalue_cast<Qt::ItemFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ItemFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ItemFlag value = qscriptvalue_cast<Qt::ItemFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ItemFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ItemFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ItemFlag,
        qtscript_Qt_ItemFlag_valueOf, qtscript_Qt_ItemFlag_toString);
    qScriptRegisterMetaType<Qt::ItemFlag>(engine, qtscript_Qt_ItemFlag_toScriptValue,
        qtscript_Qt_ItemFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ItemFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ItemFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ItemFlags
//

static QScriptValue qtscript_Qt_ItemFlags_toScriptValue(QScriptEngine *engine, const Qt::ItemFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_ItemFlags_fromScriptValue(const QScriptValue &value, Qt::ItemFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::ItemFlags>())
        out = qvariant_cast<Qt::ItemFlags>(var);
    else if (var.userType() == qMetaTypeId<Qt::ItemFlag>())
        out = qvariant_cast<Qt::ItemFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_ItemFlags(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ItemFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::ItemFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::ItemFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("ItemFlags(): argument %0 is not of type ItemFlag").arg(i));
            }
            result |= qvariant_cast<Qt::ItemFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_ItemFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ItemFlags value = qscriptvalue_cast<Qt::ItemFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ItemFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ItemFlags value = qscriptvalue_cast<Qt::ItemFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 8; ++i) {
        if ((value & qtscript_Qt_ItemFlag_values[i]) == qtscript_Qt_ItemFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_ItemFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_ItemFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::ItemFlags>() == otherObj.value<Qt::ItemFlags>())));
}

static QScriptValue qtscript_create_Qt_ItemFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_ItemFlags, qtscript_Qt_ItemFlags_valueOf,
        qtscript_Qt_ItemFlags_toString, qtscript_Qt_ItemFlags_equals);
    qScriptRegisterMetaType<Qt::ItemFlags>(engine, qtscript_Qt_ItemFlags_toScriptValue,
        qtscript_Qt_ItemFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::Axis
//

static const Qt::Axis qtscript_Qt_Axis_values[] = {
    Qt::XAxis
    , Qt::YAxis
    , Qt::ZAxis
};

static const char * const qtscript_Qt_Axis_keys[] = {
    "XAxis"
    , "YAxis"
    , "ZAxis"
};

static QString qtscript_Qt_Axis_toStringHelper(Qt::Axis value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("Axis");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_Axis_toScriptValue(QScriptEngine *engine, const Qt::Axis &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_Axis_toStringHelper(value));
}

static void qtscript_Qt_Axis_fromScriptValue(const QScriptValue &value, Qt::Axis &out)
{
    out = qvariant_cast<Qt::Axis>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_Axis(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("Axis");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::Axis>(arg));
    return context->throwError(QString::fromLatin1("Axis(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_Axis_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Axis value = qscriptvalue_cast<Qt::Axis>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_Axis_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Axis value = qscriptvalue_cast<Qt::Axis>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_Axis_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_Axis_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_Axis,
        qtscript_Qt_Axis_valueOf, qtscript_Qt_Axis_toString);
    qScriptRegisterMetaType<Qt::Axis>(engine, qtscript_Qt_Axis_toScriptValue,
        qtscript_Qt_Axis_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_Axis_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_Axis_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::TransformationMode
//

static const Qt::TransformationMode qtscript_Qt_TransformationMode_values[] = {
    Qt::FastTransformation
    , Qt::SmoothTransformation
};

static const char * const qtscript_Qt_TransformationMode_keys[] = {
    "FastTransformation"
    , "SmoothTransformation"
};

static QString qtscript_Qt_TransformationMode_toStringHelper(Qt::TransformationMode value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("TransformationMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_TransformationMode_toScriptValue(QScriptEngine *engine, const Qt::TransformationMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_TransformationMode_toStringHelper(value));
}

static void qtscript_Qt_TransformationMode_fromScriptValue(const QScriptValue &value, Qt::TransformationMode &out)
{
    out = qvariant_cast<Qt::TransformationMode>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_TransformationMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("TransformationMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::TransformationMode>(arg));
    return context->throwError(QString::fromLatin1("TransformationMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_TransformationMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TransformationMode value = qscriptvalue_cast<Qt::TransformationMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_TransformationMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TransformationMode value = qscriptvalue_cast<Qt::TransformationMode>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_TransformationMode_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_TransformationMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_TransformationMode,
        qtscript_Qt_TransformationMode_valueOf, qtscript_Qt_TransformationMode_toString);
    qScriptRegisterMetaType<Qt::TransformationMode>(engine, qtscript_Qt_TransformationMode_toScriptValue,
        qtscript_Qt_TransformationMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_TransformationMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_TransformationMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::WindowFrameSection
//

static const Qt::WindowFrameSection qtscript_Qt_WindowFrameSection_values[] = {
    Qt::NoSection
    , Qt::LeftSection
    , Qt::TopLeftSection
    , Qt::TopSection
    , Qt::TopRightSection
    , Qt::RightSection
    , Qt::BottomRightSection
    , Qt::BottomSection
    , Qt::BottomLeftSection
    , Qt::TitleBarArea
};

static const char * const qtscript_Qt_WindowFrameSection_keys[] = {
    "NoSection"
    , "LeftSection"
    , "TopLeftSection"
    , "TopSection"
    , "TopRightSection"
    , "RightSection"
    , "BottomRightSection"
    , "BottomSection"
    , "BottomLeftSection"
    , "TitleBarArea"
};

static QString qtscript_Qt_WindowFrameSection_toStringHelper(Qt::WindowFrameSection value)
{
    if ((value >= Qt::NoSection) && (value <= Qt::TitleBarArea))
        return qtscript_Qt_WindowFrameSection_keys[static_cast<int>(value)-static_cast<int>(Qt::NoSection)];
    return QString();
}

static QScriptValue qtscript_Qt_WindowFrameSection_toScriptValue(QScriptEngine *engine, const Qt::WindowFrameSection &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_WindowFrameSection_toStringHelper(value));
}

static void qtscript_Qt_WindowFrameSection_fromScriptValue(const QScriptValue &value, Qt::WindowFrameSection &out)
{
    out = qvariant_cast<Qt::WindowFrameSection>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_WindowFrameSection(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::NoSection) && (arg <= Qt::TitleBarArea))
        return qScriptValueFromValue(engine,  static_cast<Qt::WindowFrameSection>(arg));
    return context->throwError(QString::fromLatin1("WindowFrameSection(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_WindowFrameSection_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowFrameSection value = qscriptvalue_cast<Qt::WindowFrameSection>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_WindowFrameSection_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowFrameSection value = qscriptvalue_cast<Qt::WindowFrameSection>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_WindowFrameSection_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_WindowFrameSection_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_WindowFrameSection,
        qtscript_Qt_WindowFrameSection_valueOf, qtscript_Qt_WindowFrameSection_toString);
    qScriptRegisterMetaType<Qt::WindowFrameSection>(engine, qtscript_Qt_WindowFrameSection_toScriptValue,
        qtscript_Qt_WindowFrameSection_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 10; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_WindowFrameSection_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_WindowFrameSection_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::HitTestAccuracy
//

static const Qt::HitTestAccuracy qtscript_Qt_HitTestAccuracy_values[] = {
    Qt::ExactHit
    , Qt::FuzzyHit
};

static const char * const qtscript_Qt_HitTestAccuracy_keys[] = {
    "ExactHit"
    , "FuzzyHit"
};

static QString qtscript_Qt_HitTestAccuracy_toStringHelper(Qt::HitTestAccuracy value)
{
    if ((value >= Qt::ExactHit) && (value <= Qt::FuzzyHit))
        return qtscript_Qt_HitTestAccuracy_keys[static_cast<int>(value)-static_cast<int>(Qt::ExactHit)];
    return QString();
}

static QScriptValue qtscript_Qt_HitTestAccuracy_toScriptValue(QScriptEngine *engine, const Qt::HitTestAccuracy &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_HitTestAccuracy_toStringHelper(value));
}

static void qtscript_Qt_HitTestAccuracy_fromScriptValue(const QScriptValue &value, Qt::HitTestAccuracy &out)
{
    out = qvariant_cast<Qt::HitTestAccuracy>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_HitTestAccuracy(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::ExactHit) && (arg <= Qt::FuzzyHit))
        return qScriptValueFromValue(engine,  static_cast<Qt::HitTestAccuracy>(arg));
    return context->throwError(QString::fromLatin1("HitTestAccuracy(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_HitTestAccuracy_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::HitTestAccuracy value = qscriptvalue_cast<Qt::HitTestAccuracy>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_HitTestAccuracy_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::HitTestAccuracy value = qscriptvalue_cast<Qt::HitTestAccuracy>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_HitTestAccuracy_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_HitTestAccuracy_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_HitTestAccuracy,
        qtscript_Qt_HitTestAccuracy_valueOf, qtscript_Qt_HitTestAccuracy_toString);
    qScriptRegisterMetaType<Qt::HitTestAccuracy>(engine, qtscript_Qt_HitTestAccuracy_toScriptValue,
        qtscript_Qt_HitTestAccuracy_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_HitTestAccuracy_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_HitTestAccuracy_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::CursorShape
//

static const Qt::CursorShape qtscript_Qt_CursorShape_values[] = {
    Qt::ArrowCursor
    , Qt::UpArrowCursor
    , Qt::CrossCursor
    , Qt::WaitCursor
    , Qt::IBeamCursor
    , Qt::SizeVerCursor
    , Qt::SizeHorCursor
    , Qt::SizeBDiagCursor
    , Qt::SizeFDiagCursor
    , Qt::SizeAllCursor
    , Qt::BlankCursor
    , Qt::SplitVCursor
    , Qt::SplitHCursor
    , Qt::PointingHandCursor
    , Qt::ForbiddenCursor
    , Qt::WhatsThisCursor
    , Qt::BusyCursor
    , Qt::OpenHandCursor
    , Qt::ClosedHandCursor
    , Qt::DragCopyCursor
    , Qt::DragMoveCursor
    , Qt::DragLinkCursor
    , Qt::BitmapCursor
    , Qt::CustomCursor
};

static const char * const qtscript_Qt_CursorShape_keys[] = {
    "ArrowCursor"
    , "UpArrowCursor"
    , "CrossCursor"
    , "WaitCursor"
    , "IBeamCursor"
    , "SizeVerCursor"
    , "SizeHorCursor"
    , "SizeBDiagCursor"
    , "SizeFDiagCursor"
    , "SizeAllCursor"
    , "BlankCursor"
    , "SplitVCursor"
    , "SplitHCursor"
    , "PointingHandCursor"
    , "ForbiddenCursor"
    , "WhatsThisCursor"
    , "BusyCursor"
    , "OpenHandCursor"
    , "ClosedHandCursor"
    , "DragCopyCursor"
    , "DragMoveCursor"
    , "DragLinkCursor"
    , "BitmapCursor"
    , "CustomCursor"
};

static QString qtscript_Qt_CursorShape_toStringHelper(Qt::CursorShape value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("CursorShape");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_CursorShape_toScriptValue(QScriptEngine *engine, const Qt::CursorShape &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_CursorShape_toStringHelper(value));
}

static void qtscript_Qt_CursorShape_fromScriptValue(const QScriptValue &value, Qt::CursorShape &out)
{
    out = qvariant_cast<Qt::CursorShape>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_CursorShape(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("CursorShape");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::CursorShape>(arg));
    return context->throwError(QString::fromLatin1("CursorShape(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_CursorShape_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::CursorShape value = qscriptvalue_cast<Qt::CursorShape>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_CursorShape_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::CursorShape value = qscriptvalue_cast<Qt::CursorShape>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_CursorShape_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_CursorShape_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_CursorShape,
        qtscript_Qt_CursorShape_valueOf, qtscript_Qt_CursorShape_toString);
    qScriptRegisterMetaType<Qt::CursorShape>(engine, qtscript_Qt_CursorShape_toScriptValue,
        qtscript_Qt_CursorShape_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 24; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_CursorShape_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_CursorShape_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ItemSelectionMode
//

static const Qt::ItemSelectionMode qtscript_Qt_ItemSelectionMode_values[] = {
    Qt::ContainsItemShape
    , Qt::IntersectsItemShape
    , Qt::ContainsItemBoundingRect
    , Qt::IntersectsItemBoundingRect
};

static const char * const qtscript_Qt_ItemSelectionMode_keys[] = {
    "ContainsItemShape"
    , "IntersectsItemShape"
    , "ContainsItemBoundingRect"
    , "IntersectsItemBoundingRect"
};

static QString qtscript_Qt_ItemSelectionMode_toStringHelper(Qt::ItemSelectionMode value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ItemSelectionMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_ItemSelectionMode_toScriptValue(QScriptEngine *engine, const Qt::ItemSelectionMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ItemSelectionMode_toStringHelper(value));
}

static void qtscript_Qt_ItemSelectionMode_fromScriptValue(const QScriptValue &value, Qt::ItemSelectionMode &out)
{
    out = qvariant_cast<Qt::ItemSelectionMode>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ItemSelectionMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ItemSelectionMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::ItemSelectionMode>(arg));
    return context->throwError(QString::fromLatin1("ItemSelectionMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ItemSelectionMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ItemSelectionMode value = qscriptvalue_cast<Qt::ItemSelectionMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ItemSelectionMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ItemSelectionMode value = qscriptvalue_cast<Qt::ItemSelectionMode>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ItemSelectionMode_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ItemSelectionMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ItemSelectionMode,
        qtscript_Qt_ItemSelectionMode_valueOf, qtscript_Qt_ItemSelectionMode_toString);
    qScriptRegisterMetaType<Qt::ItemSelectionMode>(engine, qtscript_Qt_ItemSelectionMode_toScriptValue,
        qtscript_Qt_ItemSelectionMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ItemSelectionMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ItemSelectionMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::Orientation
//

static const Qt::Orientation qtscript_Qt_Orientation_values[] = {
    Qt::Horizontal
    , Qt::Vertical
};

static const char * const qtscript_Qt_Orientation_keys[] = {
    "Horizontal"
    , "Vertical"
};

static QString qtscript_Qt_Orientation_toStringHelper(Qt::Orientation value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("Orientation");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_Orientation_toScriptValue(QScriptEngine *engine, const Qt::Orientation &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_Orientation_toStringHelper(value));
}

static void qtscript_Qt_Orientation_fromScriptValue(const QScriptValue &value, Qt::Orientation &out)
{
    out = qvariant_cast<Qt::Orientation>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_Orientation(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("Orientation");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::Orientation>(arg));
    return context->throwError(QString::fromLatin1("Orientation(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_Orientation_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Orientation value = qscriptvalue_cast<Qt::Orientation>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_Orientation_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Orientation value = qscriptvalue_cast<Qt::Orientation>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_Orientation_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_Orientation_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_Orientation,
        qtscript_Qt_Orientation_valueOf, qtscript_Qt_Orientation_toString);
    qScriptRegisterMetaType<Qt::Orientation>(engine, qtscript_Qt_Orientation_toScriptValue,
        qtscript_Qt_Orientation_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_Orientation_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_Orientation_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::Orientations
//

static QScriptValue qtscript_Qt_Orientations_toScriptValue(QScriptEngine *engine, const Qt::Orientations &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_Orientations_fromScriptValue(const QScriptValue &value, Qt::Orientations &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::Orientations>())
        out = qvariant_cast<Qt::Orientations>(var);
    else if (var.userType() == qMetaTypeId<Qt::Orientation>())
        out = qvariant_cast<Qt::Orientation>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_Orientations(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Orientations result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::Orientations>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::Orientation>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("Orientations(): argument %0 is not of type Orientation").arg(i));
            }
            result |= qvariant_cast<Qt::Orientation>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_Orientations_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Orientations value = qscriptvalue_cast<Qt::Orientations>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_Orientations_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Orientations value = qscriptvalue_cast<Qt::Orientations>(context->thisObject());
    QString result;
    for (int i = 0; i < 2; ++i) {
        if ((value & qtscript_Qt_Orientation_values[i]) == qtscript_Qt_Orientation_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_Orientation_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_Orientations_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::Orientations>() == otherObj.value<Qt::Orientations>())));
}

static QScriptValue qtscript_create_Qt_Orientations_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_Orientations, qtscript_Qt_Orientations_valueOf,
        qtscript_Qt_Orientations_toString, qtscript_Qt_Orientations_equals);
    qScriptRegisterMetaType<Qt::Orientations>(engine, qtscript_Qt_Orientations_toScriptValue,
        qtscript_Qt_Orientations_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::InputMethodQuery
//

static const Qt::InputMethodQuery qtscript_Qt_InputMethodQuery_values[] = {
    Qt::ImMicroFocus
    , Qt::ImFont
    , Qt::ImCursorPosition
    , Qt::ImSurroundingText
    , Qt::ImCurrentSelection
    , Qt::ImMaximumTextLength
    , Qt::ImAnchorPosition
};

static const char * const qtscript_Qt_InputMethodQuery_keys[] = {
    "ImMicroFocus"
    , "ImFont"
    , "ImCursorPosition"
    , "ImSurroundingText"
    , "ImCurrentSelection"
    , "ImMaximumTextLength"
    , "ImAnchorPosition"
};

static QString qtscript_Qt_InputMethodQuery_toStringHelper(Qt::InputMethodQuery value)
{
    if ((value >= Qt::ImMicroFocus) && (value <= Qt::ImAnchorPosition))
        return qtscript_Qt_InputMethodQuery_keys[static_cast<int>(value)-static_cast<int>(Qt::ImMicroFocus)];
    return QString();
}

static QScriptValue qtscript_Qt_InputMethodQuery_toScriptValue(QScriptEngine *engine, const Qt::InputMethodQuery &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_InputMethodQuery_toStringHelper(value));
}

static void qtscript_Qt_InputMethodQuery_fromScriptValue(const QScriptValue &value, Qt::InputMethodQuery &out)
{
    out = qvariant_cast<Qt::InputMethodQuery>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_InputMethodQuery(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::ImMicroFocus) && (arg <= Qt::ImAnchorPosition))
        return qScriptValueFromValue(engine,  static_cast<Qt::InputMethodQuery>(arg));
    return context->throwError(QString::fromLatin1("InputMethodQuery(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_InputMethodQuery_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::InputMethodQuery value = qscriptvalue_cast<Qt::InputMethodQuery>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_InputMethodQuery_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::InputMethodQuery value = qscriptvalue_cast<Qt::InputMethodQuery>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_InputMethodQuery_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_InputMethodQuery_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_InputMethodQuery,
        qtscript_Qt_InputMethodQuery_valueOf, qtscript_Qt_InputMethodQuery_toString);
    qScriptRegisterMetaType<Qt::InputMethodQuery>(engine, qtscript_Qt_InputMethodQuery_toScriptValue,
        qtscript_Qt_InputMethodQuery_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_InputMethodQuery_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_InputMethodQuery_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::TimeSpec
//

static const Qt::TimeSpec qtscript_Qt_TimeSpec_values[] = {
    Qt::LocalTime
    , Qt::UTC
    , Qt::OffsetFromUTC
};

static const char * const qtscript_Qt_TimeSpec_keys[] = {
    "LocalTime"
    , "UTC"
    , "OffsetFromUTC"
};

static QString qtscript_Qt_TimeSpec_toStringHelper(Qt::TimeSpec value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("TimeSpec");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_TimeSpec_toScriptValue(QScriptEngine *engine, const Qt::TimeSpec &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_TimeSpec_toStringHelper(value));
}

static void qtscript_Qt_TimeSpec_fromScriptValue(const QScriptValue &value, Qt::TimeSpec &out)
{
    out = qvariant_cast<Qt::TimeSpec>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_TimeSpec(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("TimeSpec");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::TimeSpec>(arg));
    return context->throwError(QString::fromLatin1("TimeSpec(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_TimeSpec_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TimeSpec value = qscriptvalue_cast<Qt::TimeSpec>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_TimeSpec_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TimeSpec value = qscriptvalue_cast<Qt::TimeSpec>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_TimeSpec_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_TimeSpec_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_TimeSpec,
        qtscript_Qt_TimeSpec_valueOf, qtscript_Qt_TimeSpec_toString);
    qScriptRegisterMetaType<Qt::TimeSpec>(engine, qtscript_Qt_TimeSpec_toScriptValue,
        qtscript_Qt_TimeSpec_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_TimeSpec_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_TimeSpec_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ArrowType
//

static const Qt::ArrowType qtscript_Qt_ArrowType_values[] = {
    Qt::NoArrow
    , Qt::UpArrow
    , Qt::DownArrow
    , Qt::LeftArrow
    , Qt::RightArrow
};

static const char * const qtscript_Qt_ArrowType_keys[] = {
    "NoArrow"
    , "UpArrow"
    , "DownArrow"
    , "LeftArrow"
    , "RightArrow"
};

static QString qtscript_Qt_ArrowType_toStringHelper(Qt::ArrowType value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ArrowType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_ArrowType_toScriptValue(QScriptEngine *engine, const Qt::ArrowType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ArrowType_toStringHelper(value));
}

static void qtscript_Qt_ArrowType_fromScriptValue(const QScriptValue &value, Qt::ArrowType &out)
{
    out = qvariant_cast<Qt::ArrowType>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ArrowType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ArrowType");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::ArrowType>(arg));
    return context->throwError(QString::fromLatin1("ArrowType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ArrowType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ArrowType value = qscriptvalue_cast<Qt::ArrowType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ArrowType_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ArrowType value = qscriptvalue_cast<Qt::ArrowType>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ArrowType_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ArrowType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ArrowType,
        qtscript_Qt_ArrowType_valueOf, qtscript_Qt_ArrowType_toString);
    qScriptRegisterMetaType<Qt::ArrowType>(engine, qtscript_Qt_ArrowType_toScriptValue,
        qtscript_Qt_ArrowType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ArrowType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ArrowType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::FillRule
//

static const Qt::FillRule qtscript_Qt_FillRule_values[] = {
    Qt::OddEvenFill
    , Qt::WindingFill
};

static const char * const qtscript_Qt_FillRule_keys[] = {
    "OddEvenFill"
    , "WindingFill"
};

static QString qtscript_Qt_FillRule_toStringHelper(Qt::FillRule value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("FillRule");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_FillRule_toScriptValue(QScriptEngine *engine, const Qt::FillRule &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_FillRule_toStringHelper(value));
}

static void qtscript_Qt_FillRule_fromScriptValue(const QScriptValue &value, Qt::FillRule &out)
{
    out = qvariant_cast<Qt::FillRule>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_FillRule(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("FillRule");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::FillRule>(arg));
    return context->throwError(QString::fromLatin1("FillRule(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_FillRule_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::FillRule value = qscriptvalue_cast<Qt::FillRule>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_FillRule_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::FillRule value = qscriptvalue_cast<Qt::FillRule>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_FillRule_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_FillRule_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_FillRule,
        qtscript_Qt_FillRule_valueOf, qtscript_Qt_FillRule_toString);
    qScriptRegisterMetaType<Qt::FillRule>(engine, qtscript_Qt_FillRule_toScriptValue,
        qtscript_Qt_FillRule_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_FillRule_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_FillRule_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::MaskMode
//

static const Qt::MaskMode qtscript_Qt_MaskMode_values[] = {
    Qt::MaskInColor
    , Qt::MaskOutColor
};

static const char * const qtscript_Qt_MaskMode_keys[] = {
    "MaskInColor"
    , "MaskOutColor"
};

static QString qtscript_Qt_MaskMode_toStringHelper(Qt::MaskMode value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("MaskMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_MaskMode_toScriptValue(QScriptEngine *engine, const Qt::MaskMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_MaskMode_toStringHelper(value));
}

static void qtscript_Qt_MaskMode_fromScriptValue(const QScriptValue &value, Qt::MaskMode &out)
{
    out = qvariant_cast<Qt::MaskMode>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_MaskMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("MaskMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::MaskMode>(arg));
    return context->throwError(QString::fromLatin1("MaskMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_MaskMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::MaskMode value = qscriptvalue_cast<Qt::MaskMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_MaskMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::MaskMode value = qscriptvalue_cast<Qt::MaskMode>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_MaskMode_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_MaskMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_MaskMode,
        qtscript_Qt_MaskMode_valueOf, qtscript_Qt_MaskMode_toString);
    qScriptRegisterMetaType<Qt::MaskMode>(engine, qtscript_Qt_MaskMode_toScriptValue,
        qtscript_Qt_MaskMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_MaskMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_MaskMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::WindowState
//

static const Qt::WindowState qtscript_Qt_WindowState_values[] = {
    Qt::WindowNoState
    , Qt::WindowMinimized
    , Qt::WindowMaximized
    , Qt::WindowFullScreen
    , Qt::WindowActive
};

static const char * const qtscript_Qt_WindowState_keys[] = {
    "WindowNoState"
    , "WindowMinimized"
    , "WindowMaximized"
    , "WindowFullScreen"
    , "WindowActive"
};

static QString qtscript_Qt_WindowState_toStringHelper(Qt::WindowState value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("WindowState");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_WindowState_toScriptValue(QScriptEngine *engine, const Qt::WindowState &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_WindowState_toStringHelper(value));
}

static void qtscript_Qt_WindowState_fromScriptValue(const QScriptValue &value, Qt::WindowState &out)
{
    out = qvariant_cast<Qt::WindowState>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_WindowState(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("WindowState");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::WindowState>(arg));
    return context->throwError(QString::fromLatin1("WindowState(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_WindowState_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowState value = qscriptvalue_cast<Qt::WindowState>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_WindowState_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowState value = qscriptvalue_cast<Qt::WindowState>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_WindowState_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_WindowState_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_WindowState,
        qtscript_Qt_WindowState_valueOf, qtscript_Qt_WindowState_toString);
    qScriptRegisterMetaType<Qt::WindowState>(engine, qtscript_Qt_WindowState_toScriptValue,
        qtscript_Qt_WindowState_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_WindowState_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_WindowState_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::WindowStates
//

static QScriptValue qtscript_Qt_WindowStates_toScriptValue(QScriptEngine *engine, const Qt::WindowStates &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_WindowStates_fromScriptValue(const QScriptValue &value, Qt::WindowStates &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::WindowStates>())
        out = qvariant_cast<Qt::WindowStates>(var);
    else if (var.userType() == qMetaTypeId<Qt::WindowState>())
        out = qvariant_cast<Qt::WindowState>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_WindowStates(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowStates result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::WindowStates>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::WindowState>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("WindowStates(): argument %0 is not of type WindowState").arg(i));
            }
            result |= qvariant_cast<Qt::WindowState>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_WindowStates_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowStates value = qscriptvalue_cast<Qt::WindowStates>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_WindowStates_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WindowStates value = qscriptvalue_cast<Qt::WindowStates>(context->thisObject());
    QString result;
    for (int i = 0; i < 5; ++i) {
        if ((value & qtscript_Qt_WindowState_values[i]) == qtscript_Qt_WindowState_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_WindowState_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_WindowStates_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::WindowStates>() == otherObj.value<Qt::WindowStates>())));
}

static QScriptValue qtscript_create_Qt_WindowStates_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_WindowStates, qtscript_Qt_WindowStates_valueOf,
        qtscript_Qt_WindowStates_toString, qtscript_Qt_WindowStates_equals);
    qScriptRegisterMetaType<Qt::WindowStates>(engine, qtscript_Qt_WindowStates_toScriptValue,
        qtscript_Qt_WindowStates_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::ToolBarAreaSizes
//

static const Qt::ToolBarAreaSizes qtscript_Qt_ToolBarAreaSizes_values[] = {
    Qt::NToolBarAreas
};

static const char * const qtscript_Qt_ToolBarAreaSizes_keys[] = {
    "NToolBarAreas"
};

static QString qtscript_Qt_ToolBarAreaSizes_toStringHelper(Qt::ToolBarAreaSizes value)
{
    if ((value >= Qt::NToolBarAreas) && (value <= Qt::NToolBarAreas))
        return qtscript_Qt_ToolBarAreaSizes_keys[static_cast<int>(value)-static_cast<int>(Qt::NToolBarAreas)];
    return QString();
}

static QScriptValue qtscript_Qt_ToolBarAreaSizes_toScriptValue(QScriptEngine *engine, const Qt::ToolBarAreaSizes &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ToolBarAreaSizes_toStringHelper(value));
}

static void qtscript_Qt_ToolBarAreaSizes_fromScriptValue(const QScriptValue &value, Qt::ToolBarAreaSizes &out)
{
    out = qvariant_cast<Qt::ToolBarAreaSizes>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ToolBarAreaSizes(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::NToolBarAreas) && (arg <= Qt::NToolBarAreas))
        return qScriptValueFromValue(engine,  static_cast<Qt::ToolBarAreaSizes>(arg));
    return context->throwError(QString::fromLatin1("ToolBarAreaSizes(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ToolBarAreaSizes_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ToolBarAreaSizes value = qscriptvalue_cast<Qt::ToolBarAreaSizes>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ToolBarAreaSizes_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ToolBarAreaSizes value = qscriptvalue_cast<Qt::ToolBarAreaSizes>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ToolBarAreaSizes_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ToolBarAreaSizes_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ToolBarAreaSizes,
        qtscript_Qt_ToolBarAreaSizes_valueOf, qtscript_Qt_ToolBarAreaSizes_toString);
    qScriptRegisterMetaType<Qt::ToolBarAreaSizes>(engine, qtscript_Qt_ToolBarAreaSizes_toScriptValue,
        qtscript_Qt_ToolBarAreaSizes_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ToolBarAreaSizes_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ToolBarAreaSizes_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::Corner
//

static const Qt::Corner qtscript_Qt_Corner_values[] = {
    Qt::TopLeftCorner
    , Qt::TopRightCorner
    , Qt::BottomLeftCorner
    , Qt::BottomRightCorner
};

static const char * const qtscript_Qt_Corner_keys[] = {
    "TopLeftCorner"
    , "TopRightCorner"
    , "BottomLeftCorner"
    , "BottomRightCorner"
};

static QString qtscript_Qt_Corner_toStringHelper(Qt::Corner value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("Corner");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_Corner_toScriptValue(QScriptEngine *engine, const Qt::Corner &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_Corner_toStringHelper(value));
}

static void qtscript_Qt_Corner_fromScriptValue(const QScriptValue &value, Qt::Corner &out)
{
    out = qvariant_cast<Qt::Corner>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_Corner(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("Corner");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::Corner>(arg));
    return context->throwError(QString::fromLatin1("Corner(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_Corner_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Corner value = qscriptvalue_cast<Qt::Corner>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_Corner_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Corner value = qscriptvalue_cast<Qt::Corner>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_Corner_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_Corner_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_Corner,
        qtscript_Qt_Corner_valueOf, qtscript_Qt_Corner_toString);
    qScriptRegisterMetaType<Qt::Corner>(engine, qtscript_Qt_Corner_toScriptValue,
        qtscript_Qt_Corner_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_Corner_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_Corner_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::DayOfWeek
//

static const Qt::DayOfWeek qtscript_Qt_DayOfWeek_values[] = {
    Qt::Monday
    , Qt::Tuesday
    , Qt::Wednesday
    , Qt::Thursday
    , Qt::Friday
    , Qt::Saturday
    , Qt::Sunday
};

static const char * const qtscript_Qt_DayOfWeek_keys[] = {
    "Monday"
    , "Tuesday"
    , "Wednesday"
    , "Thursday"
    , "Friday"
    , "Saturday"
    , "Sunday"
};

static QString qtscript_Qt_DayOfWeek_toStringHelper(Qt::DayOfWeek value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("DayOfWeek");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_DayOfWeek_toScriptValue(QScriptEngine *engine, const Qt::DayOfWeek &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_DayOfWeek_toStringHelper(value));
}

static void qtscript_Qt_DayOfWeek_fromScriptValue(const QScriptValue &value, Qt::DayOfWeek &out)
{
    out = qvariant_cast<Qt::DayOfWeek>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_DayOfWeek(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("DayOfWeek");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::DayOfWeek>(arg));
    return context->throwError(QString::fromLatin1("DayOfWeek(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_DayOfWeek_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DayOfWeek value = qscriptvalue_cast<Qt::DayOfWeek>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_DayOfWeek_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DayOfWeek value = qscriptvalue_cast<Qt::DayOfWeek>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_DayOfWeek_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_DayOfWeek_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_DayOfWeek,
        qtscript_Qt_DayOfWeek_valueOf, qtscript_Qt_DayOfWeek_toString);
    qScriptRegisterMetaType<Qt::DayOfWeek>(engine, qtscript_Qt_DayOfWeek_toScriptValue,
        qtscript_Qt_DayOfWeek_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_DayOfWeek_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_DayOfWeek_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ClipOperation
//

static const Qt::ClipOperation qtscript_Qt_ClipOperation_values[] = {
    Qt::NoClip
    , Qt::ReplaceClip
    , Qt::IntersectClip
    , Qt::UniteClip
};

static const char * const qtscript_Qt_ClipOperation_keys[] = {
    "NoClip"
    , "ReplaceClip"
    , "IntersectClip"
    , "UniteClip"
};

static QString qtscript_Qt_ClipOperation_toStringHelper(Qt::ClipOperation value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ClipOperation");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_ClipOperation_toScriptValue(QScriptEngine *engine, const Qt::ClipOperation &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ClipOperation_toStringHelper(value));
}

static void qtscript_Qt_ClipOperation_fromScriptValue(const QScriptValue &value, Qt::ClipOperation &out)
{
    out = qvariant_cast<Qt::ClipOperation>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ClipOperation(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ClipOperation");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::ClipOperation>(arg));
    return context->throwError(QString::fromLatin1("ClipOperation(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ClipOperation_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ClipOperation value = qscriptvalue_cast<Qt::ClipOperation>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ClipOperation_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ClipOperation value = qscriptvalue_cast<Qt::ClipOperation>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ClipOperation_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ClipOperation_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ClipOperation,
        qtscript_Qt_ClipOperation_valueOf, qtscript_Qt_ClipOperation_toString);
    qScriptRegisterMetaType<Qt::ClipOperation>(engine, qtscript_Qt_ClipOperation_toScriptValue,
        qtscript_Qt_ClipOperation_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ClipOperation_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ClipOperation_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::LayoutDirection
//

static const Qt::LayoutDirection qtscript_Qt_LayoutDirection_values[] = {
    Qt::LeftToRight
    , Qt::RightToLeft
    , Qt::LayoutDirectionAuto
};

static const char * const qtscript_Qt_LayoutDirection_keys[] = {
    "LeftToRight"
    , "RightToLeft"
    , "LayoutDirectionAuto"
};

static QString qtscript_Qt_LayoutDirection_toStringHelper(Qt::LayoutDirection value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("LayoutDirection");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_LayoutDirection_toScriptValue(QScriptEngine *engine, const Qt::LayoutDirection &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_LayoutDirection_toStringHelper(value));
}

static void qtscript_Qt_LayoutDirection_fromScriptValue(const QScriptValue &value, Qt::LayoutDirection &out)
{
    out = qvariant_cast<Qt::LayoutDirection>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_LayoutDirection(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("LayoutDirection");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::LayoutDirection>(arg));
    return context->throwError(QString::fromLatin1("LayoutDirection(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_LayoutDirection_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::LayoutDirection value = qscriptvalue_cast<Qt::LayoutDirection>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_LayoutDirection_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::LayoutDirection value = qscriptvalue_cast<Qt::LayoutDirection>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_LayoutDirection_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_LayoutDirection_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_LayoutDirection,
        qtscript_Qt_LayoutDirection_valueOf, qtscript_Qt_LayoutDirection_toString);
    qScriptRegisterMetaType<Qt::LayoutDirection>(engine, qtscript_Qt_LayoutDirection_toScriptValue,
        qtscript_Qt_LayoutDirection_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_LayoutDirection_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_LayoutDirection_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ToolButtonStyle
//

static const Qt::ToolButtonStyle qtscript_Qt_ToolButtonStyle_values[] = {
    Qt::ToolButtonIconOnly
    , Qt::ToolButtonTextOnly
    , Qt::ToolButtonTextBesideIcon
    , Qt::ToolButtonTextUnderIcon
    , Qt::ToolButtonFollowStyle
};

static const char * const qtscript_Qt_ToolButtonStyle_keys[] = {
    "ToolButtonIconOnly"
    , "ToolButtonTextOnly"
    , "ToolButtonTextBesideIcon"
    , "ToolButtonTextUnderIcon"
    , "ToolButtonFollowStyle"
};

static QString qtscript_Qt_ToolButtonStyle_toStringHelper(Qt::ToolButtonStyle value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ToolButtonStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_ToolButtonStyle_toScriptValue(QScriptEngine *engine, const Qt::ToolButtonStyle &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ToolButtonStyle_toStringHelper(value));
}

static void qtscript_Qt_ToolButtonStyle_fromScriptValue(const QScriptValue &value, Qt::ToolButtonStyle &out)
{
    out = qvariant_cast<Qt::ToolButtonStyle>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ToolButtonStyle(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ToolButtonStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::ToolButtonStyle>(arg));
    return context->throwError(QString::fromLatin1("ToolButtonStyle(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ToolButtonStyle_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ToolButtonStyle value = qscriptvalue_cast<Qt::ToolButtonStyle>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ToolButtonStyle_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ToolButtonStyle value = qscriptvalue_cast<Qt::ToolButtonStyle>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ToolButtonStyle_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ToolButtonStyle_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ToolButtonStyle,
        qtscript_Qt_ToolButtonStyle_valueOf, qtscript_Qt_ToolButtonStyle_toString);
    qScriptRegisterMetaType<Qt::ToolButtonStyle>(engine, qtscript_Qt_ToolButtonStyle_toScriptValue,
        qtscript_Qt_ToolButtonStyle_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ToolButtonStyle_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ToolButtonStyle_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::DockWidgetAreaSizes
//

static const Qt::DockWidgetAreaSizes qtscript_Qt_DockWidgetAreaSizes_values[] = {
    Qt::NDockWidgetAreas
};

static const char * const qtscript_Qt_DockWidgetAreaSizes_keys[] = {
    "NDockWidgetAreas"
};

static QString qtscript_Qt_DockWidgetAreaSizes_toStringHelper(Qt::DockWidgetAreaSizes value)
{
    if ((value >= Qt::NDockWidgetAreas) && (value <= Qt::NDockWidgetAreas))
        return qtscript_Qt_DockWidgetAreaSizes_keys[static_cast<int>(value)-static_cast<int>(Qt::NDockWidgetAreas)];
    return QString();
}

static QScriptValue qtscript_Qt_DockWidgetAreaSizes_toScriptValue(QScriptEngine *engine, const Qt::DockWidgetAreaSizes &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_DockWidgetAreaSizes_toStringHelper(value));
}

static void qtscript_Qt_DockWidgetAreaSizes_fromScriptValue(const QScriptValue &value, Qt::DockWidgetAreaSizes &out)
{
    out = qvariant_cast<Qt::DockWidgetAreaSizes>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_DockWidgetAreaSizes(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= Qt::NDockWidgetAreas) && (arg <= Qt::NDockWidgetAreas))
        return qScriptValueFromValue(engine,  static_cast<Qt::DockWidgetAreaSizes>(arg));
    return context->throwError(QString::fromLatin1("DockWidgetAreaSizes(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_DockWidgetAreaSizes_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DockWidgetAreaSizes value = qscriptvalue_cast<Qt::DockWidgetAreaSizes>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_DockWidgetAreaSizes_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::DockWidgetAreaSizes value = qscriptvalue_cast<Qt::DockWidgetAreaSizes>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_DockWidgetAreaSizes_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_DockWidgetAreaSizes_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_DockWidgetAreaSizes,
        qtscript_Qt_DockWidgetAreaSizes_valueOf, qtscript_Qt_DockWidgetAreaSizes_toString);
    qScriptRegisterMetaType<Qt::DockWidgetAreaSizes>(engine, qtscript_Qt_DockWidgetAreaSizes_toScriptValue,
        qtscript_Qt_DockWidgetAreaSizes_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_DockWidgetAreaSizes_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_DockWidgetAreaSizes_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::Key
//

static const Qt::Key qtscript_Qt_Key_values[] = {
    Qt::Key_Space
    , Qt::Key_Exclam
    , Qt::Key_QuoteDbl
    , Qt::Key_NumberSign
    , Qt::Key_Dollar
    , Qt::Key_Percent
    , Qt::Key_Ampersand
    , Qt::Key_Apostrophe
    , Qt::Key_ParenLeft
    , Qt::Key_ParenRight
    , Qt::Key_Asterisk
    , Qt::Key_Plus
    , Qt::Key_Comma
    , Qt::Key_Minus
    , Qt::Key_Period
    , Qt::Key_Slash
    , Qt::Key_0
    , Qt::Key_1
    , Qt::Key_2
    , Qt::Key_3
    , Qt::Key_4
    , Qt::Key_5
    , Qt::Key_6
    , Qt::Key_7
    , Qt::Key_8
    , Qt::Key_9
    , Qt::Key_Colon
    , Qt::Key_Semicolon
    , Qt::Key_Less
    , Qt::Key_Equal
    , Qt::Key_Greater
    , Qt::Key_Question
    , Qt::Key_At
    , Qt::Key_A
    , Qt::Key_B
    , Qt::Key_C
    , Qt::Key_D
    , Qt::Key_E
    , Qt::Key_F
    , Qt::Key_G
    , Qt::Key_H
    , Qt::Key_I
    , Qt::Key_J
    , Qt::Key_K
    , Qt::Key_L
    , Qt::Key_M
    , Qt::Key_N
    , Qt::Key_O
    , Qt::Key_P
    , Qt::Key_Q
    , Qt::Key_R
    , Qt::Key_S
    , Qt::Key_T
    , Qt::Key_U
    , Qt::Key_V
    , Qt::Key_W
    , Qt::Key_X
    , Qt::Key_Y
    , Qt::Key_Z
    , Qt::Key_BracketLeft
    , Qt::Key_Backslash
    , Qt::Key_BracketRight
    , Qt::Key_AsciiCircum
    , Qt::Key_Underscore
    , Qt::Key_QuoteLeft
    , Qt::Key_BraceLeft
    , Qt::Key_Bar
    , Qt::Key_BraceRight
    , Qt::Key_AsciiTilde
    , Qt::Key_nobreakspace
    , Qt::Key_exclamdown
    , Qt::Key_cent
    , Qt::Key_sterling
    , Qt::Key_currency
    , Qt::Key_yen
    , Qt::Key_brokenbar
    , Qt::Key_section
    , Qt::Key_diaeresis
    , Qt::Key_copyright
    , Qt::Key_ordfeminine
    , Qt::Key_guillemotleft
    , Qt::Key_notsign
    , Qt::Key_hyphen
    , Qt::Key_registered
    , Qt::Key_macron
    , Qt::Key_degree
    , Qt::Key_plusminus
    , Qt::Key_twosuperior
    , Qt::Key_threesuperior
    , Qt::Key_acute
    , Qt::Key_mu
    , Qt::Key_paragraph
    , Qt::Key_periodcentered
    , Qt::Key_cedilla
    , Qt::Key_onesuperior
    , Qt::Key_masculine
    , Qt::Key_guillemotright
    , Qt::Key_onequarter
    , Qt::Key_onehalf
    , Qt::Key_threequarters
    , Qt::Key_questiondown
    , Qt::Key_Agrave
    , Qt::Key_Aacute
    , Qt::Key_Acircumflex
    , Qt::Key_Atilde
    , Qt::Key_Adiaeresis
    , Qt::Key_Aring
    , Qt::Key_AE
    , Qt::Key_Ccedilla
    , Qt::Key_Egrave
    , Qt::Key_Eacute
    , Qt::Key_Ecircumflex
    , Qt::Key_Ediaeresis
    , Qt::Key_Igrave
    , Qt::Key_Iacute
    , Qt::Key_Icircumflex
    , Qt::Key_Idiaeresis
    , Qt::Key_ETH
    , Qt::Key_Ntilde
    , Qt::Key_Ograve
    , Qt::Key_Oacute
    , Qt::Key_Ocircumflex
    , Qt::Key_Otilde
    , Qt::Key_Odiaeresis
    , Qt::Key_multiply
    , Qt::Key_Ooblique
    , Qt::Key_Ugrave
    , Qt::Key_Uacute
    , Qt::Key_Ucircumflex
    , Qt::Key_Udiaeresis
    , Qt::Key_Yacute
    , Qt::Key_THORN
    , Qt::Key_ssharp
    , Qt::Key_division
    , Qt::Key_ydiaeresis
    , Qt::Key_Escape
    , Qt::Key_Tab
    , Qt::Key_Backtab
    , Qt::Key_Backspace
    , Qt::Key_Return
    , Qt::Key_Enter
    , Qt::Key_Insert
    , Qt::Key_Delete
    , Qt::Key_Pause
    , Qt::Key_Print
    , Qt::Key_SysReq
    , Qt::Key_Clear
    , Qt::Key_Home
    , Qt::Key_End
    , Qt::Key_Left
    , Qt::Key_Up
    , Qt::Key_Right
    , Qt::Key_Down
    , Qt::Key_PageUp
    , Qt::Key_PageDown
    , Qt::Key_Shift
    , Qt::Key_Control
    , Qt::Key_Meta
    , Qt::Key_Alt
    , Qt::Key_CapsLock
    , Qt::Key_NumLock
    , Qt::Key_ScrollLock
    , Qt::Key_F1
    , Qt::Key_F2
    , Qt::Key_F3
    , Qt::Key_F4
    , Qt::Key_F5
    , Qt::Key_F6
    , Qt::Key_F7
    , Qt::Key_F8
    , Qt::Key_F9
    , Qt::Key_F10
    , Qt::Key_F11
    , Qt::Key_F12
    , Qt::Key_F13
    , Qt::Key_F14
    , Qt::Key_F15
    , Qt::Key_F16
    , Qt::Key_F17
    , Qt::Key_F18
    , Qt::Key_F19
    , Qt::Key_F20
    , Qt::Key_F21
    , Qt::Key_F22
    , Qt::Key_F23
    , Qt::Key_F24
    , Qt::Key_F25
    , Qt::Key_F26
    , Qt::Key_F27
    , Qt::Key_F28
    , Qt::Key_F29
    , Qt::Key_F30
    , Qt::Key_F31
    , Qt::Key_F32
    , Qt::Key_F33
    , Qt::Key_F34
    , Qt::Key_F35
    , Qt::Key_Super_L
    , Qt::Key_Super_R
    , Qt::Key_Menu
    , Qt::Key_Hyper_L
    , Qt::Key_Hyper_R
    , Qt::Key_Help
    , Qt::Key_Direction_L
    , Qt::Key_Direction_R
    , Qt::Key_Back
    , Qt::Key_Forward
    , Qt::Key_Stop
    , Qt::Key_Refresh
    , Qt::Key_VolumeDown
    , Qt::Key_VolumeMute
    , Qt::Key_VolumeUp
    , Qt::Key_BassBoost
    , Qt::Key_BassUp
    , Qt::Key_BassDown
    , Qt::Key_TrebleUp
    , Qt::Key_TrebleDown
    , Qt::Key_MediaPlay
    , Qt::Key_MediaStop
    , Qt::Key_MediaPrevious
    , Qt::Key_MediaNext
    , Qt::Key_MediaRecord
    , Qt::Key_MediaPause
    , Qt::Key_MediaTogglePlayPause
    , Qt::Key_HomePage
    , Qt::Key_Favorites
    , Qt::Key_Search
    , Qt::Key_Standby
    , Qt::Key_OpenUrl
    , Qt::Key_LaunchMail
    , Qt::Key_LaunchMedia
    , Qt::Key_Launch0
    , Qt::Key_Launch1
    , Qt::Key_Launch2
    , Qt::Key_Launch3
    , Qt::Key_Launch4
    , Qt::Key_Launch5
    , Qt::Key_Launch6
    , Qt::Key_Launch7
    , Qt::Key_Launch8
    , Qt::Key_Launch9
    , Qt::Key_LaunchA
    , Qt::Key_LaunchB
    , Qt::Key_LaunchC
    , Qt::Key_LaunchD
    , Qt::Key_LaunchE
    , Qt::Key_LaunchF
    , Qt::Key_MonBrightnessUp
    , Qt::Key_MonBrightnessDown
    , Qt::Key_KeyboardLightOnOff
    , Qt::Key_KeyboardBrightnessUp
    , Qt::Key_KeyboardBrightnessDown
    , Qt::Key_PowerOff
    , Qt::Key_WakeUp
    , Qt::Key_Eject
    , Qt::Key_ScreenSaver
    , Qt::Key_WWW
    , Qt::Key_Memo
    , Qt::Key_LightBulb
    , Qt::Key_Shop
    , Qt::Key_History
    , Qt::Key_AddFavorite
    , Qt::Key_HotLinks
    , Qt::Key_BrightnessAdjust
    , Qt::Key_Finance
    , Qt::Key_Community
    , Qt::Key_AudioRewind
    , Qt::Key_BackForward
    , Qt::Key_ApplicationLeft
    , Qt::Key_ApplicationRight
    , Qt::Key_Book
    , Qt::Key_CD
    , Qt::Key_Calculator
    , Qt::Key_ToDoList
    , Qt::Key_ClearGrab
    , Qt::Key_Close
    , Qt::Key_Copy
    , Qt::Key_Cut
    , Qt::Key_Display
    , Qt::Key_DOS
    , Qt::Key_Documents
    , Qt::Key_Excel
    , Qt::Key_Explorer
    , Qt::Key_Game
    , Qt::Key_Go
    , Qt::Key_iTouch
    , Qt::Key_LogOff
    , Qt::Key_Market
    , Qt::Key_Meeting
    , Qt::Key_MenuKB
    , Qt::Key_MenuPB
    , Qt::Key_MySites
    , Qt::Key_News
    , Qt::Key_OfficeHome
    , Qt::Key_Option
    , Qt::Key_Paste
    , Qt::Key_Phone
    , Qt::Key_Calendar
    , Qt::Key_Reply
    , Qt::Key_Reload
    , Qt::Key_RotateWindows
    , Qt::Key_RotationPB
    , Qt::Key_RotationKB
    , Qt::Key_Save
    , Qt::Key_Send
    , Qt::Key_Spell
    , Qt::Key_SplitScreen
    , Qt::Key_Support
    , Qt::Key_TaskPane
    , Qt::Key_Terminal
    , Qt::Key_Tools
    , Qt::Key_Travel
    , Qt::Key_Video
    , Qt::Key_Word
    , Qt::Key_Xfer
    , Qt::Key_ZoomIn
    , Qt::Key_ZoomOut
    , Qt::Key_Away
    , Qt::Key_Messenger
    , Qt::Key_WebCam
    , Qt::Key_MailForward
    , Qt::Key_Pictures
    , Qt::Key_Music
    , Qt::Key_Battery
    , Qt::Key_Bluetooth
    , Qt::Key_WLAN
    , Qt::Key_UWB
    , Qt::Key_AudioForward
    , Qt::Key_AudioRepeat
    , Qt::Key_AudioRandomPlay
    , Qt::Key_Subtitle
    , Qt::Key_AudioCycleTrack
    , Qt::Key_Time
    , Qt::Key_Hibernate
    , Qt::Key_View
    , Qt::Key_TopMenu
    , Qt::Key_PowerDown
    , Qt::Key_Suspend
    , Qt::Key_ContrastAdjust
    , Qt::Key_LaunchG
    , Qt::Key_LaunchH
    , Qt::Key_AltGr
    , Qt::Key_Multi_key
    , Qt::Key_Kanji
    , Qt::Key_Muhenkan
    , Qt::Key_Henkan
    , Qt::Key_Romaji
    , Qt::Key_Hiragana
    , Qt::Key_Katakana
    , Qt::Key_Hiragana_Katakana
    , Qt::Key_Zenkaku
    , Qt::Key_Hankaku
    , Qt::Key_Zenkaku_Hankaku
    , Qt::Key_Touroku
    , Qt::Key_Massyo
    , Qt::Key_Kana_Lock
    , Qt::Key_Kana_Shift
    , Qt::Key_Eisu_Shift
    , Qt::Key_Eisu_toggle
    , Qt::Key_Hangul
    , Qt::Key_Hangul_Start
    , Qt::Key_Hangul_End
    , Qt::Key_Hangul_Hanja
    , Qt::Key_Hangul_Jamo
    , Qt::Key_Hangul_Romaja
    , Qt::Key_Codeinput
    , Qt::Key_Hangul_Jeonja
    , Qt::Key_Hangul_Banja
    , Qt::Key_Hangul_PreHanja
    , Qt::Key_Hangul_PostHanja
    , Qt::Key_SingleCandidate
    , Qt::Key_MultipleCandidate
    , Qt::Key_PreviousCandidate
    , Qt::Key_Hangul_Special
    , Qt::Key_Mode_switch
    , Qt::Key_Dead_Grave
    , Qt::Key_Dead_Acute
    , Qt::Key_Dead_Circumflex
    , Qt::Key_Dead_Tilde
    , Qt::Key_Dead_Macron
    , Qt::Key_Dead_Breve
    , Qt::Key_Dead_Abovedot
    , Qt::Key_Dead_Diaeresis
    , Qt::Key_Dead_Abovering
    , Qt::Key_Dead_Doubleacute
    , Qt::Key_Dead_Caron
    , Qt::Key_Dead_Cedilla
    , Qt::Key_Dead_Ogonek
    , Qt::Key_Dead_Iota
    , Qt::Key_Dead_Voiced_Sound
    , Qt::Key_Dead_Semivoiced_Sound
    , Qt::Key_Dead_Belowdot
    , Qt::Key_Dead_Hook
    , Qt::Key_Dead_Horn
    , Qt::Key_MediaLast
    , Qt::Key_Select
    , Qt::Key_Yes
    , Qt::Key_No
    , Qt::Key_Cancel
    , Qt::Key_Printer
    , Qt::Key_Execute
    , Qt::Key_Sleep
    , Qt::Key_Play
    , Qt::Key_Zoom
    , Qt::Key_Context1
    , Qt::Key_Context2
    , Qt::Key_Context3
    , Qt::Key_Context4
    , Qt::Key_Call
    , Qt::Key_Hangup
    , Qt::Key_Flip
    , Qt::Key_ToggleCallHangup
    , Qt::Key_VoiceDial
    , Qt::Key_LastNumberRedial
    , Qt::Key_Camera
    , Qt::Key_CameraFocus
    , Qt::Key_unknown
};

static const char * const qtscript_Qt_Key_keys[] = {
    "Key_Space"
    , "Key_Exclam"
    , "Key_QuoteDbl"
    , "Key_NumberSign"
    , "Key_Dollar"
    , "Key_Percent"
    , "Key_Ampersand"
    , "Key_Apostrophe"
    , "Key_ParenLeft"
    , "Key_ParenRight"
    , "Key_Asterisk"
    , "Key_Plus"
    , "Key_Comma"
    , "Key_Minus"
    , "Key_Period"
    , "Key_Slash"
    , "Key_0"
    , "Key_1"
    , "Key_2"
    , "Key_3"
    , "Key_4"
    , "Key_5"
    , "Key_6"
    , "Key_7"
    , "Key_8"
    , "Key_9"
    , "Key_Colon"
    , "Key_Semicolon"
    , "Key_Less"
    , "Key_Equal"
    , "Key_Greater"
    , "Key_Question"
    , "Key_At"
    , "Key_A"
    , "Key_B"
    , "Key_C"
    , "Key_D"
    , "Key_E"
    , "Key_F"
    , "Key_G"
    , "Key_H"
    , "Key_I"
    , "Key_J"
    , "Key_K"
    , "Key_L"
    , "Key_M"
    , "Key_N"
    , "Key_O"
    , "Key_P"
    , "Key_Q"
    , "Key_R"
    , "Key_S"
    , "Key_T"
    , "Key_U"
    , "Key_V"
    , "Key_W"
    , "Key_X"
    , "Key_Y"
    , "Key_Z"
    , "Key_BracketLeft"
    , "Key_Backslash"
    , "Key_BracketRight"
    , "Key_AsciiCircum"
    , "Key_Underscore"
    , "Key_QuoteLeft"
    , "Key_BraceLeft"
    , "Key_Bar"
    , "Key_BraceRight"
    , "Key_AsciiTilde"
    , "Key_nobreakspace"
    , "Key_exclamdown"
    , "Key_cent"
    , "Key_sterling"
    , "Key_currency"
    , "Key_yen"
    , "Key_brokenbar"
    , "Key_section"
    , "Key_diaeresis"
    , "Key_copyright"
    , "Key_ordfeminine"
    , "Key_guillemotleft"
    , "Key_notsign"
    , "Key_hyphen"
    , "Key_registered"
    , "Key_macron"
    , "Key_degree"
    , "Key_plusminus"
    , "Key_twosuperior"
    , "Key_threesuperior"
    , "Key_acute"
    , "Key_mu"
    , "Key_paragraph"
    , "Key_periodcentered"
    , "Key_cedilla"
    , "Key_onesuperior"
    , "Key_masculine"
    , "Key_guillemotright"
    , "Key_onequarter"
    , "Key_onehalf"
    , "Key_threequarters"
    , "Key_questiondown"
    , "Key_Agrave"
    , "Key_Aacute"
    , "Key_Acircumflex"
    , "Key_Atilde"
    , "Key_Adiaeresis"
    , "Key_Aring"
    , "Key_AE"
    , "Key_Ccedilla"
    , "Key_Egrave"
    , "Key_Eacute"
    , "Key_Ecircumflex"
    , "Key_Ediaeresis"
    , "Key_Igrave"
    , "Key_Iacute"
    , "Key_Icircumflex"
    , "Key_Idiaeresis"
    , "Key_ETH"
    , "Key_Ntilde"
    , "Key_Ograve"
    , "Key_Oacute"
    , "Key_Ocircumflex"
    , "Key_Otilde"
    , "Key_Odiaeresis"
    , "Key_multiply"
    , "Key_Ooblique"
    , "Key_Ugrave"
    , "Key_Uacute"
    , "Key_Ucircumflex"
    , "Key_Udiaeresis"
    , "Key_Yacute"
    , "Key_THORN"
    , "Key_ssharp"
    , "Key_division"
    , "Key_ydiaeresis"
    , "Key_Escape"
    , "Key_Tab"
    , "Key_Backtab"
    , "Key_Backspace"
    , "Key_Return"
    , "Key_Enter"
    , "Key_Insert"
    , "Key_Delete"
    , "Key_Pause"
    , "Key_Print"
    , "Key_SysReq"
    , "Key_Clear"
    , "Key_Home"
    , "Key_End"
    , "Key_Left"
    , "Key_Up"
    , "Key_Right"
    , "Key_Down"
    , "Key_PageUp"
    , "Key_PageDown"
    , "Key_Shift"
    , "Key_Control"
    , "Key_Meta"
    , "Key_Alt"
    , "Key_CapsLock"
    , "Key_NumLock"
    , "Key_ScrollLock"
    , "Key_F1"
    , "Key_F2"
    , "Key_F3"
    , "Key_F4"
    , "Key_F5"
    , "Key_F6"
    , "Key_F7"
    , "Key_F8"
    , "Key_F9"
    , "Key_F10"
    , "Key_F11"
    , "Key_F12"
    , "Key_F13"
    , "Key_F14"
    , "Key_F15"
    , "Key_F16"
    , "Key_F17"
    , "Key_F18"
    , "Key_F19"
    , "Key_F20"
    , "Key_F21"
    , "Key_F22"
    , "Key_F23"
    , "Key_F24"
    , "Key_F25"
    , "Key_F26"
    , "Key_F27"
    , "Key_F28"
    , "Key_F29"
    , "Key_F30"
    , "Key_F31"
    , "Key_F32"
    , "Key_F33"
    , "Key_F34"
    , "Key_F35"
    , "Key_Super_L"
    , "Key_Super_R"
    , "Key_Menu"
    , "Key_Hyper_L"
    , "Key_Hyper_R"
    , "Key_Help"
    , "Key_Direction_L"
    , "Key_Direction_R"
    , "Key_Back"
    , "Key_Forward"
    , "Key_Stop"
    , "Key_Refresh"
    , "Key_VolumeDown"
    , "Key_VolumeMute"
    , "Key_VolumeUp"
    , "Key_BassBoost"
    , "Key_BassUp"
    , "Key_BassDown"
    , "Key_TrebleUp"
    , "Key_TrebleDown"
    , "Key_MediaPlay"
    , "Key_MediaStop"
    , "Key_MediaPrevious"
    , "Key_MediaNext"
    , "Key_MediaRecord"
    , "Key_MediaPause"
    , "Key_MediaTogglePlayPause"
    , "Key_HomePage"
    , "Key_Favorites"
    , "Key_Search"
    , "Key_Standby"
    , "Key_OpenUrl"
    , "Key_LaunchMail"
    , "Key_LaunchMedia"
    , "Key_Launch0"
    , "Key_Launch1"
    , "Key_Launch2"
    , "Key_Launch3"
    , "Key_Launch4"
    , "Key_Launch5"
    , "Key_Launch6"
    , "Key_Launch7"
    , "Key_Launch8"
    , "Key_Launch9"
    , "Key_LaunchA"
    , "Key_LaunchB"
    , "Key_LaunchC"
    , "Key_LaunchD"
    , "Key_LaunchE"
    , "Key_LaunchF"
    , "Key_MonBrightnessUp"
    , "Key_MonBrightnessDown"
    , "Key_KeyboardLightOnOff"
    , "Key_KeyboardBrightnessUp"
    , "Key_KeyboardBrightnessDown"
    , "Key_PowerOff"
    , "Key_WakeUp"
    , "Key_Eject"
    , "Key_ScreenSaver"
    , "Key_WWW"
    , "Key_Memo"
    , "Key_LightBulb"
    , "Key_Shop"
    , "Key_History"
    , "Key_AddFavorite"
    , "Key_HotLinks"
    , "Key_BrightnessAdjust"
    , "Key_Finance"
    , "Key_Community"
    , "Key_AudioRewind"
    , "Key_BackForward"
    , "Key_ApplicationLeft"
    , "Key_ApplicationRight"
    , "Key_Book"
    , "Key_CD"
    , "Key_Calculator"
    , "Key_ToDoList"
    , "Key_ClearGrab"
    , "Key_Close"
    , "Key_Copy"
    , "Key_Cut"
    , "Key_Display"
    , "Key_DOS"
    , "Key_Documents"
    , "Key_Excel"
    , "Key_Explorer"
    , "Key_Game"
    , "Key_Go"
    , "Key_iTouch"
    , "Key_LogOff"
    , "Key_Market"
    , "Key_Meeting"
    , "Key_MenuKB"
    , "Key_MenuPB"
    , "Key_MySites"
    , "Key_News"
    , "Key_OfficeHome"
    , "Key_Option"
    , "Key_Paste"
    , "Key_Phone"
    , "Key_Calendar"
    , "Key_Reply"
    , "Key_Reload"
    , "Key_RotateWindows"
    , "Key_RotationPB"
    , "Key_RotationKB"
    , "Key_Save"
    , "Key_Send"
    , "Key_Spell"
    , "Key_SplitScreen"
    , "Key_Support"
    , "Key_TaskPane"
    , "Key_Terminal"
    , "Key_Tools"
    , "Key_Travel"
    , "Key_Video"
    , "Key_Word"
    , "Key_Xfer"
    , "Key_ZoomIn"
    , "Key_ZoomOut"
    , "Key_Away"
    , "Key_Messenger"
    , "Key_WebCam"
    , "Key_MailForward"
    , "Key_Pictures"
    , "Key_Music"
    , "Key_Battery"
    , "Key_Bluetooth"
    , "Key_WLAN"
    , "Key_UWB"
    , "Key_AudioForward"
    , "Key_AudioRepeat"
    , "Key_AudioRandomPlay"
    , "Key_Subtitle"
    , "Key_AudioCycleTrack"
    , "Key_Time"
    , "Key_Hibernate"
    , "Key_View"
    , "Key_TopMenu"
    , "Key_PowerDown"
    , "Key_Suspend"
    , "Key_ContrastAdjust"
    , "Key_LaunchG"
    , "Key_LaunchH"
    , "Key_AltGr"
    , "Key_Multi_key"
    , "Key_Kanji"
    , "Key_Muhenkan"
    , "Key_Henkan"
    , "Key_Romaji"
    , "Key_Hiragana"
    , "Key_Katakana"
    , "Key_Hiragana_Katakana"
    , "Key_Zenkaku"
    , "Key_Hankaku"
    , "Key_Zenkaku_Hankaku"
    , "Key_Touroku"
    , "Key_Massyo"
    , "Key_Kana_Lock"
    , "Key_Kana_Shift"
    , "Key_Eisu_Shift"
    , "Key_Eisu_toggle"
    , "Key_Hangul"
    , "Key_Hangul_Start"
    , "Key_Hangul_End"
    , "Key_Hangul_Hanja"
    , "Key_Hangul_Jamo"
    , "Key_Hangul_Romaja"
    , "Key_Codeinput"
    , "Key_Hangul_Jeonja"
    , "Key_Hangul_Banja"
    , "Key_Hangul_PreHanja"
    , "Key_Hangul_PostHanja"
    , "Key_SingleCandidate"
    , "Key_MultipleCandidate"
    , "Key_PreviousCandidate"
    , "Key_Hangul_Special"
    , "Key_Mode_switch"
    , "Key_Dead_Grave"
    , "Key_Dead_Acute"
    , "Key_Dead_Circumflex"
    , "Key_Dead_Tilde"
    , "Key_Dead_Macron"
    , "Key_Dead_Breve"
    , "Key_Dead_Abovedot"
    , "Key_Dead_Diaeresis"
    , "Key_Dead_Abovering"
    , "Key_Dead_Doubleacute"
    , "Key_Dead_Caron"
    , "Key_Dead_Cedilla"
    , "Key_Dead_Ogonek"
    , "Key_Dead_Iota"
    , "Key_Dead_Voiced_Sound"
    , "Key_Dead_Semivoiced_Sound"
    , "Key_Dead_Belowdot"
    , "Key_Dead_Hook"
    , "Key_Dead_Horn"
    , "Key_MediaLast"
    , "Key_Select"
    , "Key_Yes"
    , "Key_No"
    , "Key_Cancel"
    , "Key_Printer"
    , "Key_Execute"
    , "Key_Sleep"
    , "Key_Play"
    , "Key_Zoom"
    , "Key_Context1"
    , "Key_Context2"
    , "Key_Context3"
    , "Key_Context4"
    , "Key_Call"
    , "Key_Hangup"
    , "Key_Flip"
    , "Key_ToggleCallHangup"
    , "Key_VoiceDial"
    , "Key_LastNumberRedial"
    , "Key_Camera"
    , "Key_CameraFocus"
    , "Key_unknown"
};

static QString qtscript_Qt_Key_toStringHelper(Qt::Key value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("Key");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_Key_toScriptValue(QScriptEngine *engine, const Qt::Key &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_Key_toStringHelper(value));
}

static void qtscript_Qt_Key_fromScriptValue(const QScriptValue &value, Qt::Key &out)
{
    out = qvariant_cast<Qt::Key>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_Key(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("Key");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::Key>(arg));
    return context->throwError(QString::fromLatin1("Key(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_Key_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Key value = qscriptvalue_cast<Qt::Key>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_Key_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::Key value = qscriptvalue_cast<Qt::Key>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_Key_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_Key_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_Key,
        qtscript_Qt_Key_valueOf, qtscript_Qt_Key_toString);
    qScriptRegisterMetaType<Qt::Key>(engine, qtscript_Qt_Key_toScriptValue,
        qtscript_Qt_Key_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 417; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_Key_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_Key_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::ApplicationAttribute
//

static const Qt::ApplicationAttribute qtscript_Qt_ApplicationAttribute_values[] = {
    Qt::AA_ImmediateWidgetCreation
    , Qt::AA_MSWindowsUseDirect3DByDefault
    , Qt::AA_DontShowIconsInMenus
    , Qt::AA_NativeWindows
    , Qt::AA_DontCreateNativeWidgetSiblings
    , Qt::AA_MacPluginApplication
    , Qt::AA_DontUseNativeMenuBar
    , Qt::AA_MacDontSwapCtrlAndMeta
    , Qt::AA_S60DontConstructApplicationPanes
    , Qt::AA_S60DisablePartialScreenInputMode
    , Qt::AA_X11InitThreads
    , Qt::AA_CaptureMultimediaKeys
    , Qt::AA_AttributeCount
};

static const char * const qtscript_Qt_ApplicationAttribute_keys[] = {
    "AA_ImmediateWidgetCreation"
    , "AA_MSWindowsUseDirect3DByDefault"
    , "AA_DontShowIconsInMenus"
    , "AA_NativeWindows"
    , "AA_DontCreateNativeWidgetSiblings"
    , "AA_MacPluginApplication"
    , "AA_DontUseNativeMenuBar"
    , "AA_MacDontSwapCtrlAndMeta"
    , "AA_S60DontConstructApplicationPanes"
    , "AA_S60DisablePartialScreenInputMode"
    , "AA_X11InitThreads"
    , "AA_CaptureMultimediaKeys"
    , "AA_AttributeCount"
};

static QString qtscript_Qt_ApplicationAttribute_toStringHelper(Qt::ApplicationAttribute value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ApplicationAttribute");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_ApplicationAttribute_toScriptValue(QScriptEngine *engine, const Qt::ApplicationAttribute &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_ApplicationAttribute_toStringHelper(value));
}

static void qtscript_Qt_ApplicationAttribute_fromScriptValue(const QScriptValue &value, Qt::ApplicationAttribute &out)
{
    out = qvariant_cast<Qt::ApplicationAttribute>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_ApplicationAttribute(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("ApplicationAttribute");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::ApplicationAttribute>(arg));
    return context->throwError(QString::fromLatin1("ApplicationAttribute(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_ApplicationAttribute_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ApplicationAttribute value = qscriptvalue_cast<Qt::ApplicationAttribute>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_ApplicationAttribute_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::ApplicationAttribute value = qscriptvalue_cast<Qt::ApplicationAttribute>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_ApplicationAttribute_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_ApplicationAttribute_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_ApplicationAttribute,
        qtscript_Qt_ApplicationAttribute_valueOf, qtscript_Qt_ApplicationAttribute_toString);
    qScriptRegisterMetaType<Qt::ApplicationAttribute>(engine, qtscript_Qt_ApplicationAttribute_toScriptValue,
        qtscript_Qt_ApplicationAttribute_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 13; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_ApplicationAttribute_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_ApplicationAttribute_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::TextFlag
//

static const Qt::TextFlag qtscript_Qt_TextFlag_values[] = {
    Qt::TextSingleLine
    , Qt::TextDontClip
    , Qt::TextExpandTabs
    , Qt::TextShowMnemonic
    , Qt::TextWordWrap
    , Qt::TextWrapAnywhere
    , Qt::TextDontPrint
    , Qt::TextHideMnemonic
    , Qt::TextJustificationForced
    , Qt::TextForceLeftToRight
    , Qt::TextForceRightToLeft
    , Qt::TextLongestVariant
    , Qt::TextBypassShaping
    , Qt::TextIncludeTrailingSpaces
};

static const char * const qtscript_Qt_TextFlag_keys[] = {
    "TextSingleLine"
    , "TextDontClip"
    , "TextExpandTabs"
    , "TextShowMnemonic"
    , "TextWordWrap"
    , "TextWrapAnywhere"
    , "TextDontPrint"
    , "TextHideMnemonic"
    , "TextJustificationForced"
    , "TextForceLeftToRight"
    , "TextForceRightToLeft"
    , "TextLongestVariant"
    , "TextBypassShaping"
    , "TextIncludeTrailingSpaces"
};

static QString qtscript_Qt_TextFlag_toStringHelper(Qt::TextFlag value)
{
    for (int i = 0; i < 14; ++i) {
        if (qtscript_Qt_TextFlag_values[i] == value)
            return QString::fromLatin1(qtscript_Qt_TextFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_Qt_TextFlag_toScriptValue(QScriptEngine *engine, const Qt::TextFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_TextFlag_toStringHelper(value));
}

static void qtscript_Qt_TextFlag_fromScriptValue(const QScriptValue &value, Qt::TextFlag &out)
{
    out = qvariant_cast<Qt::TextFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_TextFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 14; ++i) {
        if (qtscript_Qt_TextFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<Qt::TextFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("TextFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_TextFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TextFlag value = qscriptvalue_cast<Qt::TextFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_TextFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TextFlag value = qscriptvalue_cast<Qt::TextFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_TextFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_TextFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_TextFlag,
        qtscript_Qt_TextFlag_valueOf, qtscript_Qt_TextFlag_toString);
    qScriptRegisterMetaType<Qt::TextFlag>(engine, qtscript_Qt_TextFlag_toScriptValue,
        qtscript_Qt_TextFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 14; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_TextFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_TextFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::BrushStyle
//

static const Qt::BrushStyle qtscript_Qt_BrushStyle_values[] = {
    Qt::NoBrush
    , Qt::SolidPattern
    , Qt::Dense1Pattern
    , Qt::Dense2Pattern
    , Qt::Dense3Pattern
    , Qt::Dense4Pattern
    , Qt::Dense5Pattern
    , Qt::Dense6Pattern
    , Qt::Dense7Pattern
    , Qt::HorPattern
    , Qt::VerPattern
    , Qt::CrossPattern
    , Qt::BDiagPattern
    , Qt::FDiagPattern
    , Qt::DiagCrossPattern
    , Qt::LinearGradientPattern
    , Qt::RadialGradientPattern
    , Qt::ConicalGradientPattern
    , Qt::TexturePattern
};

static const char * const qtscript_Qt_BrushStyle_keys[] = {
    "NoBrush"
    , "SolidPattern"
    , "Dense1Pattern"
    , "Dense2Pattern"
    , "Dense3Pattern"
    , "Dense4Pattern"
    , "Dense5Pattern"
    , "Dense6Pattern"
    , "Dense7Pattern"
    , "HorPattern"
    , "VerPattern"
    , "CrossPattern"
    , "BDiagPattern"
    , "FDiagPattern"
    , "DiagCrossPattern"
    , "LinearGradientPattern"
    , "RadialGradientPattern"
    , "ConicalGradientPattern"
    , "TexturePattern"
};

static QString qtscript_Qt_BrushStyle_toStringHelper(Qt::BrushStyle value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("BrushStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_BrushStyle_toScriptValue(QScriptEngine *engine, const Qt::BrushStyle &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_BrushStyle_toStringHelper(value));
}

static void qtscript_Qt_BrushStyle_fromScriptValue(const QScriptValue &value, Qt::BrushStyle &out)
{
    out = qvariant_cast<Qt::BrushStyle>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_BrushStyle(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("BrushStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::BrushStyle>(arg));
    return context->throwError(QString::fromLatin1("BrushStyle(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_BrushStyle_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::BrushStyle value = qscriptvalue_cast<Qt::BrushStyle>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_BrushStyle_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::BrushStyle value = qscriptvalue_cast<Qt::BrushStyle>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_BrushStyle_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_BrushStyle_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_BrushStyle,
        qtscript_Qt_BrushStyle_valueOf, qtscript_Qt_BrushStyle_toString);
    qScriptRegisterMetaType<Qt::BrushStyle>(engine, qtscript_Qt_BrushStyle_toScriptValue,
        qtscript_Qt_BrushStyle_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 19; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_BrushStyle_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_BrushStyle_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::WidgetAttribute
//

static const Qt::WidgetAttribute qtscript_Qt_WidgetAttribute_values[] = {
    Qt::WA_Disabled
    , Qt::WA_UnderMouse
    , Qt::WA_MouseTracking
    , Qt::WA_ContentsPropagated
    , Qt::WA_OpaquePaintEvent
    , Qt::WA_StaticContents
    , Qt::WA_LaidOut
    , Qt::WA_PaintOnScreen
    , Qt::WA_NoSystemBackground
    , Qt::WA_UpdatesDisabled
    , Qt::WA_Mapped
    , Qt::WA_MacNoClickThrough
    , Qt::WA_PaintOutsidePaintEvent
    , Qt::WA_InputMethodEnabled
    , Qt::WA_WState_Visible
    , Qt::WA_WState_Hidden
    , Qt::WA_ForceDisabled
    , Qt::WA_KeyCompression
    , Qt::WA_PendingMoveEvent
    , Qt::WA_PendingResizeEvent
    , Qt::WA_SetPalette
    , Qt::WA_SetFont
    , Qt::WA_SetCursor
    , Qt::WA_NoChildEventsFromChildren
    , Qt::WA_WindowModified
    , Qt::WA_Resized
    , Qt::WA_Moved
    , Qt::WA_PendingUpdate
    , Qt::WA_InvalidSize
    , Qt::WA_MacBrushedMetal
    , Qt::WA_CustomWhatsThis
    , Qt::WA_LayoutOnEntireRect
    , Qt::WA_OutsideWSRange
    , Qt::WA_GrabbedShortcut
    , Qt::WA_TransparentForMouseEvents
    , Qt::WA_PaintUnclipped
    , Qt::WA_SetWindowIcon
    , Qt::WA_NoMouseReplay
    , Qt::WA_DeleteOnClose
    , Qt::WA_RightToLeft
    , Qt::WA_SetLayoutDirection
    , Qt::WA_NoChildEventsForParent
    , Qt::WA_ForceUpdatesDisabled
    , Qt::WA_WState_Created
    , Qt::WA_WState_CompressKeys
    , Qt::WA_WState_InPaintEvent
    , Qt::WA_WState_Reparented
    , Qt::WA_WState_ConfigPending
    , Qt::WA_WState_Polished
    , Qt::WA_WState_DND
    , Qt::WA_WState_OwnSizePolicy
    , Qt::WA_WState_ExplicitShowHide
    , Qt::WA_ShowModal
    , Qt::WA_MouseNoMask
    , Qt::WA_GroupLeader
    , Qt::WA_NoMousePropagation
    , Qt::WA_Hover
    , Qt::WA_InputMethodTransparent
    , Qt::WA_QuitOnClose
    , Qt::WA_KeyboardFocusChange
    , Qt::WA_AcceptDrops
    , Qt::WA_DropSiteRegistered
    , Qt::WA_WindowPropagation
    , Qt::WA_NoX11EventCompression
    , Qt::WA_TintedBackground
    , Qt::WA_X11OpenGLOverlay
    , Qt::WA_AlwaysShowToolTips
    , Qt::WA_MacOpaqueSizeGrip
    , Qt::WA_SetStyle
    , Qt::WA_SetLocale
    , Qt::WA_MacShowFocusRect
    , Qt::WA_MacNormalSize
    , Qt::WA_MacSmallSize
    , Qt::WA_MacMiniSize
    , Qt::WA_LayoutUsesWidgetRect
    , Qt::WA_StyledBackground
    , Qt::WA_MSWindowsUseDirect3D
    , Qt::WA_CanHostQMdiSubWindowTitleBar
    , Qt::WA_MacAlwaysShowToolWindow
    , Qt::WA_StyleSheet
    , Qt::WA_ShowWithoutActivating
    , Qt::WA_X11BypassTransientForHint
    , Qt::WA_NativeWindow
    , Qt::WA_DontCreateNativeAncestors
    , Qt::WA_MacVariableSize
    , Qt::WA_DontShowOnScreen
    , Qt::WA_X11NetWmWindowTypeDesktop
    , Qt::WA_X11NetWmWindowTypeDock
    , Qt::WA_X11NetWmWindowTypeToolBar
    , Qt::WA_X11NetWmWindowTypeMenu
    , Qt::WA_X11NetWmWindowTypeUtility
    , Qt::WA_X11NetWmWindowTypeSplash
    , Qt::WA_X11NetWmWindowTypeDialog
    , Qt::WA_X11NetWmWindowTypeDropDownMenu
    , Qt::WA_X11NetWmWindowTypePopupMenu
    , Qt::WA_X11NetWmWindowTypeToolTip
    , Qt::WA_X11NetWmWindowTypeNotification
    , Qt::WA_X11NetWmWindowTypeCombo
    , Qt::WA_X11NetWmWindowTypeDND
    , Qt::WA_MacFrameworkScaled
    , Qt::WA_SetWindowModality
    , Qt::WA_WState_WindowOpacitySet
    , Qt::WA_TranslucentBackground
    , Qt::WA_AcceptTouchEvents
    , Qt::WA_WState_AcceptedTouchBeginEvent
    , Qt::WA_TouchPadAcceptSingleTouchEvents
    , Qt::WA_MergeSoftkeys
    , Qt::WA_MergeSoftkeysRecursively
    , Qt::WA_LockPortraitOrientation
    , Qt::WA_LockLandscapeOrientation
    , Qt::WA_AutoOrientation
    , Qt::WA_X11DoNotAcceptFocus
    , Qt::WA_SymbianNoSystemRotation
    , Qt::WA_MacNoShadow
    , Qt::WA_AttributeCount
};

static const char * const qtscript_Qt_WidgetAttribute_keys[] = {
    "WA_Disabled"
    , "WA_UnderMouse"
    , "WA_MouseTracking"
    , "WA_ContentsPropagated"
    , "WA_OpaquePaintEvent"
    , "WA_StaticContents"
    , "WA_LaidOut"
    , "WA_PaintOnScreen"
    , "WA_NoSystemBackground"
    , "WA_UpdatesDisabled"
    , "WA_Mapped"
    , "WA_MacNoClickThrough"
    , "WA_PaintOutsidePaintEvent"
    , "WA_InputMethodEnabled"
    , "WA_WState_Visible"
    , "WA_WState_Hidden"
    , "WA_ForceDisabled"
    , "WA_KeyCompression"
    , "WA_PendingMoveEvent"
    , "WA_PendingResizeEvent"
    , "WA_SetPalette"
    , "WA_SetFont"
    , "WA_SetCursor"
    , "WA_NoChildEventsFromChildren"
    , "WA_WindowModified"
    , "WA_Resized"
    , "WA_Moved"
    , "WA_PendingUpdate"
    , "WA_InvalidSize"
    , "WA_MacBrushedMetal"
    , "WA_CustomWhatsThis"
    , "WA_LayoutOnEntireRect"
    , "WA_OutsideWSRange"
    , "WA_GrabbedShortcut"
    , "WA_TransparentForMouseEvents"
    , "WA_PaintUnclipped"
    , "WA_SetWindowIcon"
    , "WA_NoMouseReplay"
    , "WA_DeleteOnClose"
    , "WA_RightToLeft"
    , "WA_SetLayoutDirection"
    , "WA_NoChildEventsForParent"
    , "WA_ForceUpdatesDisabled"
    , "WA_WState_Created"
    , "WA_WState_CompressKeys"
    , "WA_WState_InPaintEvent"
    , "WA_WState_Reparented"
    , "WA_WState_ConfigPending"
    , "WA_WState_Polished"
    , "WA_WState_DND"
    , "WA_WState_OwnSizePolicy"
    , "WA_WState_ExplicitShowHide"
    , "WA_ShowModal"
    , "WA_MouseNoMask"
    , "WA_GroupLeader"
    , "WA_NoMousePropagation"
    , "WA_Hover"
    , "WA_InputMethodTransparent"
    , "WA_QuitOnClose"
    , "WA_KeyboardFocusChange"
    , "WA_AcceptDrops"
    , "WA_DropSiteRegistered"
    , "WA_WindowPropagation"
    , "WA_NoX11EventCompression"
    , "WA_TintedBackground"
    , "WA_X11OpenGLOverlay"
    , "WA_AlwaysShowToolTips"
    , "WA_MacOpaqueSizeGrip"
    , "WA_SetStyle"
    , "WA_SetLocale"
    , "WA_MacShowFocusRect"
    , "WA_MacNormalSize"
    , "WA_MacSmallSize"
    , "WA_MacMiniSize"
    , "WA_LayoutUsesWidgetRect"
    , "WA_StyledBackground"
    , "WA_MSWindowsUseDirect3D"
    , "WA_CanHostQMdiSubWindowTitleBar"
    , "WA_MacAlwaysShowToolWindow"
    , "WA_StyleSheet"
    , "WA_ShowWithoutActivating"
    , "WA_X11BypassTransientForHint"
    , "WA_NativeWindow"
    , "WA_DontCreateNativeAncestors"
    , "WA_MacVariableSize"
    , "WA_DontShowOnScreen"
    , "WA_X11NetWmWindowTypeDesktop"
    , "WA_X11NetWmWindowTypeDock"
    , "WA_X11NetWmWindowTypeToolBar"
    , "WA_X11NetWmWindowTypeMenu"
    , "WA_X11NetWmWindowTypeUtility"
    , "WA_X11NetWmWindowTypeSplash"
    , "WA_X11NetWmWindowTypeDialog"
    , "WA_X11NetWmWindowTypeDropDownMenu"
    , "WA_X11NetWmWindowTypePopupMenu"
    , "WA_X11NetWmWindowTypeToolTip"
    , "WA_X11NetWmWindowTypeNotification"
    , "WA_X11NetWmWindowTypeCombo"
    , "WA_X11NetWmWindowTypeDND"
    , "WA_MacFrameworkScaled"
    , "WA_SetWindowModality"
    , "WA_WState_WindowOpacitySet"
    , "WA_TranslucentBackground"
    , "WA_AcceptTouchEvents"
    , "WA_WState_AcceptedTouchBeginEvent"
    , "WA_TouchPadAcceptSingleTouchEvents"
    , "WA_MergeSoftkeys"
    , "WA_MergeSoftkeysRecursively"
    , "WA_LockPortraitOrientation"
    , "WA_LockLandscapeOrientation"
    , "WA_AutoOrientation"
    , "WA_X11DoNotAcceptFocus"
    , "WA_SymbianNoSystemRotation"
    , "WA_MacNoShadow"
    , "WA_AttributeCount"
};

static QString qtscript_Qt_WidgetAttribute_toStringHelper(Qt::WidgetAttribute value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("WidgetAttribute");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_WidgetAttribute_toScriptValue(QScriptEngine *engine, const Qt::WidgetAttribute &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_WidgetAttribute_toStringHelper(value));
}

static void qtscript_Qt_WidgetAttribute_fromScriptValue(const QScriptValue &value, Qt::WidgetAttribute &out)
{
    out = qvariant_cast<Qt::WidgetAttribute>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_WidgetAttribute(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("WidgetAttribute");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::WidgetAttribute>(arg));
    return context->throwError(QString::fromLatin1("WidgetAttribute(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_WidgetAttribute_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WidgetAttribute value = qscriptvalue_cast<Qt::WidgetAttribute>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_WidgetAttribute_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::WidgetAttribute value = qscriptvalue_cast<Qt::WidgetAttribute>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_WidgetAttribute_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_WidgetAttribute_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_WidgetAttribute,
        qtscript_Qt_WidgetAttribute_valueOf, qtscript_Qt_WidgetAttribute_toString);
    qScriptRegisterMetaType<Qt::WidgetAttribute>(engine, qtscript_Qt_WidgetAttribute_toScriptValue,
        qtscript_Qt_WidgetAttribute_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 115; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_WidgetAttribute_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_WidgetAttribute_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::TouchPointState
//

static const Qt::TouchPointState qtscript_Qt_TouchPointState_values[] = {
    Qt::TouchPointPressed
    , Qt::TouchPointMoved
    , Qt::TouchPointStationary
    , Qt::TouchPointReleased
    , Qt::TouchPointStateMask
    , Qt::TouchPointPrimary
};

static const char * const qtscript_Qt_TouchPointState_keys[] = {
    "TouchPointPressed"
    , "TouchPointMoved"
    , "TouchPointStationary"
    , "TouchPointReleased"
    , "TouchPointStateMask"
    , "TouchPointPrimary"
};

static QString qtscript_Qt_TouchPointState_toStringHelper(Qt::TouchPointState value)
{
    for (int i = 0; i < 6; ++i) {
        if (qtscript_Qt_TouchPointState_values[i] == value)
            return QString::fromLatin1(qtscript_Qt_TouchPointState_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_Qt_TouchPointState_toScriptValue(QScriptEngine *engine, const Qt::TouchPointState &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_TouchPointState_toStringHelper(value));
}

static void qtscript_Qt_TouchPointState_fromScriptValue(const QScriptValue &value, Qt::TouchPointState &out)
{
    out = qvariant_cast<Qt::TouchPointState>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_TouchPointState(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 6; ++i) {
        if (qtscript_Qt_TouchPointState_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<Qt::TouchPointState>(arg));
    }
    return context->throwError(QString::fromLatin1("TouchPointState(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_TouchPointState_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TouchPointState value = qscriptvalue_cast<Qt::TouchPointState>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_TouchPointState_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TouchPointState value = qscriptvalue_cast<Qt::TouchPointState>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_TouchPointState_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_TouchPointState_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_TouchPointState,
        qtscript_Qt_TouchPointState_valueOf, qtscript_Qt_TouchPointState_toString);
    qScriptRegisterMetaType<Qt::TouchPointState>(engine, qtscript_Qt_TouchPointState_toScriptValue,
        qtscript_Qt_TouchPointState_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 6; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_TouchPointState_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_TouchPointState_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::TouchPointStates
//

static QScriptValue qtscript_Qt_TouchPointStates_toScriptValue(QScriptEngine *engine, const Qt::TouchPointStates &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_TouchPointStates_fromScriptValue(const QScriptValue &value, Qt::TouchPointStates &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::TouchPointStates>())
        out = qvariant_cast<Qt::TouchPointStates>(var);
    else if (var.userType() == qMetaTypeId<Qt::TouchPointState>())
        out = qvariant_cast<Qt::TouchPointState>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_TouchPointStates(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TouchPointStates result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::TouchPointStates>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::TouchPointState>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("TouchPointStates(): argument %0 is not of type TouchPointState").arg(i));
            }
            result |= qvariant_cast<Qt::TouchPointState>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_TouchPointStates_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TouchPointStates value = qscriptvalue_cast<Qt::TouchPointStates>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_TouchPointStates_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TouchPointStates value = qscriptvalue_cast<Qt::TouchPointStates>(context->thisObject());
    QString result;
    for (int i = 0; i < 6; ++i) {
        if ((value & qtscript_Qt_TouchPointState_values[i]) == qtscript_Qt_TouchPointState_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_TouchPointState_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_TouchPointStates_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::TouchPointStates>() == otherObj.value<Qt::TouchPointStates>())));
}

static QScriptValue qtscript_create_Qt_TouchPointStates_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_TouchPointStates, qtscript_Qt_TouchPointStates_valueOf,
        qtscript_Qt_TouchPointStates_toString, qtscript_Qt_TouchPointStates_equals);
    qScriptRegisterMetaType<Qt::TouchPointStates>(engine, qtscript_Qt_TouchPointStates_toScriptValue,
        qtscript_Qt_TouchPointStates_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::TextInteractionFlag
//

static const Qt::TextInteractionFlag qtscript_Qt_TextInteractionFlag_values[] = {
    Qt::NoTextInteraction
    , Qt::TextSelectableByMouse
    , Qt::TextSelectableByKeyboard
    , Qt::LinksAccessibleByMouse
    , Qt::LinksAccessibleByKeyboard
    , Qt::TextBrowserInteraction
    , Qt::TextEditable
    , Qt::TextEditorInteraction
};

static const char * const qtscript_Qt_TextInteractionFlag_keys[] = {
    "NoTextInteraction"
    , "TextSelectableByMouse"
    , "TextSelectableByKeyboard"
    , "LinksAccessibleByMouse"
    , "LinksAccessibleByKeyboard"
    , "TextBrowserInteraction"
    , "TextEditable"
    , "TextEditorInteraction"
};

static QString qtscript_Qt_TextInteractionFlag_toStringHelper(Qt::TextInteractionFlag value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("TextInteractionFlag");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_TextInteractionFlag_toScriptValue(QScriptEngine *engine, const Qt::TextInteractionFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_TextInteractionFlag_toStringHelper(value));
}

static void qtscript_Qt_TextInteractionFlag_fromScriptValue(const QScriptValue &value, Qt::TextInteractionFlag &out)
{
    out = qvariant_cast<Qt::TextInteractionFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_TextInteractionFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("TextInteractionFlag");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::TextInteractionFlag>(arg));
    return context->throwError(QString::fromLatin1("TextInteractionFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_TextInteractionFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TextInteractionFlag value = qscriptvalue_cast<Qt::TextInteractionFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_TextInteractionFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TextInteractionFlag value = qscriptvalue_cast<Qt::TextInteractionFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_TextInteractionFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_TextInteractionFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_TextInteractionFlag,
        qtscript_Qt_TextInteractionFlag_valueOf, qtscript_Qt_TextInteractionFlag_toString);
    qScriptRegisterMetaType<Qt::TextInteractionFlag>(engine, qtscript_Qt_TextInteractionFlag_toScriptValue,
        qtscript_Qt_TextInteractionFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_TextInteractionFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_TextInteractionFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::TextInteractionFlags
//

static QScriptValue qtscript_Qt_TextInteractionFlags_toScriptValue(QScriptEngine *engine, const Qt::TextInteractionFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_TextInteractionFlags_fromScriptValue(const QScriptValue &value, Qt::TextInteractionFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::TextInteractionFlags>())
        out = qvariant_cast<Qt::TextInteractionFlags>(var);
    else if (var.userType() == qMetaTypeId<Qt::TextInteractionFlag>())
        out = qvariant_cast<Qt::TextInteractionFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_TextInteractionFlags(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TextInteractionFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::TextInteractionFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::TextInteractionFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("TextInteractionFlags(): argument %0 is not of type TextInteractionFlag").arg(i));
            }
            result |= qvariant_cast<Qt::TextInteractionFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_TextInteractionFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TextInteractionFlags value = qscriptvalue_cast<Qt::TextInteractionFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_TextInteractionFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TextInteractionFlags value = qscriptvalue_cast<Qt::TextInteractionFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 8; ++i) {
        if ((value & qtscript_Qt_TextInteractionFlag_values[i]) == qtscript_Qt_TextInteractionFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_TextInteractionFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_TextInteractionFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::TextInteractionFlags>() == otherObj.value<Qt::TextInteractionFlags>())));
}

static QScriptValue qtscript_create_Qt_TextInteractionFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_TextInteractionFlags, qtscript_Qt_TextInteractionFlags_valueOf,
        qtscript_Qt_TextInteractionFlags_toString, qtscript_Qt_TextInteractionFlags_equals);
    qScriptRegisterMetaType<Qt::TextInteractionFlags>(engine, qtscript_Qt_TextInteractionFlags_toScriptValue,
        qtscript_Qt_TextInteractionFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::MouseButton
//

static const Qt::MouseButton qtscript_Qt_MouseButton_values[] = {
    Qt::NoButton
    , Qt::LeftButton
    , Qt::RightButton
    , Qt::MidButton
    , Qt::XButton1
    , Qt::XButton2
    , Qt::MouseButtonMask
};

static const char * const qtscript_Qt_MouseButton_keys[] = {
    "NoButton"
    , "LeftButton"
    , "RightButton"
    , "MidButton"
    , "XButton1"
    , "XButton2"
    , "MouseButtonMask"
};

static QString qtscript_Qt_MouseButton_toStringHelper(Qt::MouseButton value)
{
    for (int i = 0; i < 7; ++i) {
        if (qtscript_Qt_MouseButton_values[i] == value)
            return QString::fromLatin1(qtscript_Qt_MouseButton_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_Qt_MouseButton_toScriptValue(QScriptEngine *engine, const Qt::MouseButton &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_MouseButton_toStringHelper(value));
}

static void qtscript_Qt_MouseButton_fromScriptValue(const QScriptValue &value, Qt::MouseButton &out)
{
    out = qvariant_cast<Qt::MouseButton>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_MouseButton(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 7; ++i) {
        if (qtscript_Qt_MouseButton_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<Qt::MouseButton>(arg));
    }
    return context->throwError(QString::fromLatin1("MouseButton(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_MouseButton_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::MouseButton value = qscriptvalue_cast<Qt::MouseButton>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_MouseButton_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::MouseButton value = qscriptvalue_cast<Qt::MouseButton>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_MouseButton_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_MouseButton_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_MouseButton,
        qtscript_Qt_MouseButton_valueOf, qtscript_Qt_MouseButton_toString);
    qScriptRegisterMetaType<Qt::MouseButton>(engine, qtscript_Qt_MouseButton_toScriptValue,
        qtscript_Qt_MouseButton_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_MouseButton_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_MouseButton_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::MouseButtons
//

static QScriptValue qtscript_Qt_MouseButtons_toScriptValue(QScriptEngine *engine, const Qt::MouseButtons &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_MouseButtons_fromScriptValue(const QScriptValue &value, Qt::MouseButtons &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::MouseButtons>())
        out = qvariant_cast<Qt::MouseButtons>(var);
    else if (var.userType() == qMetaTypeId<Qt::MouseButton>())
        out = qvariant_cast<Qt::MouseButton>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_MouseButtons(QScriptContext *context, QScriptEngine *engine)
{
    Qt::MouseButtons result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::MouseButtons>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::MouseButton>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("MouseButtons(): argument %0 is not of type MouseButton").arg(i));
            }
            result |= qvariant_cast<Qt::MouseButton>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_MouseButtons_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::MouseButtons value = qscriptvalue_cast<Qt::MouseButtons>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_MouseButtons_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::MouseButtons value = qscriptvalue_cast<Qt::MouseButtons>(context->thisObject());
    QString result;
    for (int i = 0; i < 7; ++i) {
        if ((value & qtscript_Qt_MouseButton_values[i]) == qtscript_Qt_MouseButton_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_MouseButton_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_MouseButtons_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::MouseButtons>() == otherObj.value<Qt::MouseButtons>())));
}

static QScriptValue qtscript_create_Qt_MouseButtons_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_MouseButtons, qtscript_Qt_MouseButtons_valueOf,
        qtscript_Qt_MouseButtons_toString, qtscript_Qt_MouseButtons_equals);
    qScriptRegisterMetaType<Qt::MouseButtons>(engine, qtscript_Qt_MouseButtons_toScriptValue,
        qtscript_Qt_MouseButtons_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::MatchFlag
//

static const Qt::MatchFlag qtscript_Qt_MatchFlag_values[] = {
    Qt::MatchExactly
    , Qt::MatchContains
    , Qt::MatchStartsWith
    , Qt::MatchEndsWith
    , Qt::MatchRegExp
    , Qt::MatchWildcard
    , Qt::MatchFixedString
    , Qt::MatchCaseSensitive
    , Qt::MatchWrap
    , Qt::MatchRecursive
};

static const char * const qtscript_Qt_MatchFlag_keys[] = {
    "MatchExactly"
    , "MatchContains"
    , "MatchStartsWith"
    , "MatchEndsWith"
    , "MatchRegExp"
    , "MatchWildcard"
    , "MatchFixedString"
    , "MatchCaseSensitive"
    , "MatchWrap"
    , "MatchRecursive"
};

static QString qtscript_Qt_MatchFlag_toStringHelper(Qt::MatchFlag value)
{
    for (int i = 0; i < 10; ++i) {
        if (qtscript_Qt_MatchFlag_values[i] == value)
            return QString::fromLatin1(qtscript_Qt_MatchFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_Qt_MatchFlag_toScriptValue(QScriptEngine *engine, const Qt::MatchFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_MatchFlag_toStringHelper(value));
}

static void qtscript_Qt_MatchFlag_fromScriptValue(const QScriptValue &value, Qt::MatchFlag &out)
{
    out = qvariant_cast<Qt::MatchFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_MatchFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 10; ++i) {
        if (qtscript_Qt_MatchFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<Qt::MatchFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("MatchFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_MatchFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::MatchFlag value = qscriptvalue_cast<Qt::MatchFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_MatchFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::MatchFlag value = qscriptvalue_cast<Qt::MatchFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_MatchFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_MatchFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_MatchFlag,
        qtscript_Qt_MatchFlag_valueOf, qtscript_Qt_MatchFlag_toString);
    qScriptRegisterMetaType<Qt::MatchFlag>(engine, qtscript_Qt_MatchFlag_toScriptValue,
        qtscript_Qt_MatchFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 10; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_MatchFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_MatchFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::MatchFlags
//

static QScriptValue qtscript_Qt_MatchFlags_toScriptValue(QScriptEngine *engine, const Qt::MatchFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_Qt_MatchFlags_fromScriptValue(const QScriptValue &value, Qt::MatchFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<Qt::MatchFlags>())
        out = qvariant_cast<Qt::MatchFlags>(var);
    else if (var.userType() == qMetaTypeId<Qt::MatchFlag>())
        out = qvariant_cast<Qt::MatchFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_Qt_MatchFlags(QScriptContext *context, QScriptEngine *engine)
{
    Qt::MatchFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<Qt::MatchFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<Qt::MatchFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("MatchFlags(): argument %0 is not of type MatchFlag").arg(i));
            }
            result |= qvariant_cast<Qt::MatchFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_Qt_MatchFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::MatchFlags value = qscriptvalue_cast<Qt::MatchFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_MatchFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::MatchFlags value = qscriptvalue_cast<Qt::MatchFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 10; ++i) {
        if ((value & qtscript_Qt_MatchFlag_values[i]) == qtscript_Qt_MatchFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_Qt_MatchFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_Qt_MatchFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<Qt::MatchFlags>() == otherObj.value<Qt::MatchFlags>())));
}

static QScriptValue qtscript_create_Qt_MatchFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_Qt_MatchFlags, qtscript_Qt_MatchFlags_valueOf,
        qtscript_Qt_MatchFlags_toString, qtscript_Qt_MatchFlags_equals);
    qScriptRegisterMetaType<Qt::MatchFlags>(engine, qtscript_Qt_MatchFlags_toScriptValue,
        qtscript_Qt_MatchFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// Qt::PenCapStyle
//

static const Qt::PenCapStyle qtscript_Qt_PenCapStyle_values[] = {
    Qt::FlatCap
    , Qt::SquareCap
    , Qt::RoundCap
    , Qt::MPenCapStyle
};

static const char * const qtscript_Qt_PenCapStyle_keys[] = {
    "FlatCap"
    , "SquareCap"
    , "RoundCap"
    , "MPenCapStyle"
};

static QString qtscript_Qt_PenCapStyle_toStringHelper(Qt::PenCapStyle value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("PenCapStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_PenCapStyle_toScriptValue(QScriptEngine *engine, const Qt::PenCapStyle &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_PenCapStyle_toStringHelper(value));
}

static void qtscript_Qt_PenCapStyle_fromScriptValue(const QScriptValue &value, Qt::PenCapStyle &out)
{
    out = qvariant_cast<Qt::PenCapStyle>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_PenCapStyle(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("PenCapStyle");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::PenCapStyle>(arg));
    return context->throwError(QString::fromLatin1("PenCapStyle(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_PenCapStyle_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::PenCapStyle value = qscriptvalue_cast<Qt::PenCapStyle>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_PenCapStyle_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::PenCapStyle value = qscriptvalue_cast<Qt::PenCapStyle>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_PenCapStyle_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_PenCapStyle_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_PenCapStyle,
        qtscript_Qt_PenCapStyle_valueOf, qtscript_Qt_PenCapStyle_toString);
    qScriptRegisterMetaType<Qt::PenCapStyle>(engine, qtscript_Qt_PenCapStyle_toScriptValue,
        qtscript_Qt_PenCapStyle_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_PenCapStyle_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_PenCapStyle_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt::TextElideMode
//

static const Qt::TextElideMode qtscript_Qt_TextElideMode_values[] = {
    Qt::ElideLeft
    , Qt::ElideRight
    , Qt::ElideMiddle
    , Qt::ElideNone
};

static const char * const qtscript_Qt_TextElideMode_keys[] = {
    "ElideLeft"
    , "ElideRight"
    , "ElideMiddle"
    , "ElideNone"
};

static QString qtscript_Qt_TextElideMode_toStringHelper(Qt::TextElideMode value)
{
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("TextElideMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_Qt_TextElideMode_toScriptValue(QScriptEngine *engine, const Qt::TextElideMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("Qt"));
    return clazz.property(qtscript_Qt_TextElideMode_toStringHelper(value));
}

static void qtscript_Qt_TextElideMode_fromScriptValue(const QScriptValue &value, Qt::TextElideMode &out)
{
    out = qvariant_cast<Qt::TextElideMode>(value.toVariant());
}

static QScriptValue qtscript_construct_Qt_TextElideMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_Qt_metaObject();
    int idx = meta->indexOfEnumerator("TextElideMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Qt::TextElideMode>(arg));
    return context->throwError(QString::fromLatin1("TextElideMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_Qt_TextElideMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TextElideMode value = qscriptvalue_cast<Qt::TextElideMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_Qt_TextElideMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    Qt::TextElideMode value = qscriptvalue_cast<Qt::TextElideMode>(context->thisObject());
    return QScriptValue(engine, qtscript_Qt_TextElideMode_toStringHelper(value));
}

static QScriptValue qtscript_create_Qt_TextElideMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_Qt_TextElideMode,
        qtscript_Qt_TextElideMode_valueOf, qtscript_Qt_TextElideMode_toString);
    qScriptRegisterMetaType<Qt::TextElideMode>(engine, qtscript_Qt_TextElideMode_toScriptValue,
        qtscript_Qt_TextElideMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_Qt_TextElideMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_Qt_TextElideMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Qt
//

static QScriptValue qtscript_Qt_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("Qt cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_Qt_throw_ambiguity_error_helper(context,
        qtscript_Qt_function_names[_id],
        qtscript_Qt_function_signatures[_id]);
}

QScriptValue qtscript_create_Qt_class(QScriptEngine *engine)
{
    QScriptValue proto = QScriptValue();
    QScriptValue ctor = engine->newFunction(qtscript_Qt_static_call, proto, qtscript_Qt_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ShortcutContext"),
        qtscript_create_Qt_ShortcutContext_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("CheckState"),
        qtscript_create_Qt_CheckState_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FocusPolicy"),
        qtscript_create_Qt_FocusPolicy_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("GestureType"),
        qtscript_create_Qt_GestureType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("DropAction"),
        qtscript_create_Qt_DropAction_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("DropActions"),
        qtscript_create_Qt_DropActions_class(engine));
    ctor.setProperty(QString::fromLatin1("WindowType"),
        qtscript_create_Qt_WindowType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WindowFlags"),
        qtscript_create_Qt_WindowFlags_class(engine));
    ctor.setProperty(QString::fromLatin1("DateFormat"),
        qtscript_create_Qt_DateFormat_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TextFormat"),
        qtscript_create_Qt_TextFormat_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PenJoinStyle"),
        qtscript_create_Qt_PenJoinStyle_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("GestureFlag"),
        qtscript_create_Qt_GestureFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("GestureFlags"),
        qtscript_create_Qt_GestureFlags_class(engine));
    ctor.setProperty(QString::fromLatin1("CaseSensitivity"),
        qtscript_create_Qt_CaseSensitivity_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("EventPriority"),
        qtscript_create_Qt_EventPriority_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ImageConversionFlag"),
        qtscript_create_Qt_ImageConversionFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ImageConversionFlags"),
        qtscript_create_Qt_ImageConversionFlags_class(engine));
    ctor.setProperty(QString::fromLatin1("GestureState"),
        qtscript_create_Qt_GestureState_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("BGMode"),
        qtscript_create_Qt_BGMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ConnectionType"),
        qtscript_create_Qt_ConnectionType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ToolBarArea"),
        qtscript_create_Qt_ToolBarArea_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ToolBarAreas"),
        qtscript_create_Qt_ToolBarAreas_class(engine));
    ctor.setProperty(QString::fromLatin1("CoordinateSystem"),
        qtscript_create_Qt_CoordinateSystem_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SizeMode"),
        qtscript_create_Qt_SizeMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FocusReason"),
        qtscript_create_Qt_FocusReason_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TileRule"),
        qtscript_create_Qt_TileRule_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WhiteSpaceMode"),
        qtscript_create_Qt_WhiteSpaceMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("AspectRatioMode"),
        qtscript_create_Qt_AspectRatioMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SizeHint"),
        qtscript_create_Qt_SizeHint_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("AlignmentFlag"),
        qtscript_create_Qt_AlignmentFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Alignment"),
        qtscript_create_Qt_Alignment_class(engine));
    ctor.setProperty(QString::fromLatin1("ContextMenuPolicy"),
        qtscript_create_Qt_ContextMenuPolicy_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("DockWidgetArea"),
        qtscript_create_Qt_DockWidgetArea_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("DockWidgetAreas"),
        qtscript_create_Qt_DockWidgetAreas_class(engine));
    ctor.setProperty(QString::fromLatin1("UIEffect"),
        qtscript_create_Qt_UIEffect_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("AnchorPoint"),
        qtscript_create_Qt_AnchorPoint_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("GlobalColor"),
        qtscript_create_Qt_GlobalColor_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("KeyboardModifier"),
        qtscript_create_Qt_KeyboardModifier_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("KeyboardModifiers"),
        qtscript_create_Qt_KeyboardModifiers_class(engine));
    ctor.setProperty(QString::fromLatin1("NavigationMode"),
        qtscript_create_Qt_NavigationMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ItemDataRole"),
        qtscript_create_Qt_ItemDataRole_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ScrollBarPolicy"),
        qtscript_create_Qt_ScrollBarPolicy_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("InputMethodHint"),
        qtscript_create_Qt_InputMethodHint_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("InputMethodHints"),
        qtscript_create_Qt_InputMethodHints_class(engine));
    ctor.setProperty(QString::fromLatin1("AnchorAttribute"),
        qtscript_create_Qt_AnchorAttribute_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WindowModality"),
        qtscript_create_Qt_WindowModality_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SortOrder"),
        qtscript_create_Qt_SortOrder_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("PenStyle"),
        qtscript_create_Qt_PenStyle_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ItemFlag"),
        qtscript_create_Qt_ItemFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ItemFlags"),
        qtscript_create_Qt_ItemFlags_class(engine));
    ctor.setProperty(QString::fromLatin1("Axis"),
        qtscript_create_Qt_Axis_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TransformationMode"),
        qtscript_create_Qt_TransformationMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WindowFrameSection"),
        qtscript_create_Qt_WindowFrameSection_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("HitTestAccuracy"),
        qtscript_create_Qt_HitTestAccuracy_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("CursorShape"),
        qtscript_create_Qt_CursorShape_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ItemSelectionMode"),
        qtscript_create_Qt_ItemSelectionMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Orientation"),
        qtscript_create_Qt_Orientation_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Orientations"),
        qtscript_create_Qt_Orientations_class(engine));
    ctor.setProperty(QString::fromLatin1("InputMethodQuery"),
        qtscript_create_Qt_InputMethodQuery_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TimeSpec"),
        qtscript_create_Qt_TimeSpec_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ArrowType"),
        qtscript_create_Qt_ArrowType_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FillRule"),
        qtscript_create_Qt_FillRule_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("MaskMode"),
        qtscript_create_Qt_MaskMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WindowState"),
        qtscript_create_Qt_WindowState_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WindowStates"),
        qtscript_create_Qt_WindowStates_class(engine));
    ctor.setProperty(QString::fromLatin1("ToolBarAreaSizes"),
        qtscript_create_Qt_ToolBarAreaSizes_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Corner"),
        qtscript_create_Qt_Corner_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("DayOfWeek"),
        qtscript_create_Qt_DayOfWeek_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ClipOperation"),
        qtscript_create_Qt_ClipOperation_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("LayoutDirection"),
        qtscript_create_Qt_LayoutDirection_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ToolButtonStyle"),
        qtscript_create_Qt_ToolButtonStyle_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("DockWidgetAreaSizes"),
        qtscript_create_Qt_DockWidgetAreaSizes_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Key"),
        qtscript_create_Qt_Key_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ApplicationAttribute"),
        qtscript_create_Qt_ApplicationAttribute_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TextFlag"),
        qtscript_create_Qt_TextFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("BrushStyle"),
        qtscript_create_Qt_BrushStyle_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("WidgetAttribute"),
        qtscript_create_Qt_WidgetAttribute_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TouchPointState"),
        qtscript_create_Qt_TouchPointState_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TouchPointStates"),
        qtscript_create_Qt_TouchPointStates_class(engine));
    ctor.setProperty(QString::fromLatin1("TextInteractionFlag"),
        qtscript_create_Qt_TextInteractionFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TextInteractionFlags"),
        qtscript_create_Qt_TextInteractionFlags_class(engine));
    ctor.setProperty(QString::fromLatin1("MouseButton"),
        qtscript_create_Qt_MouseButton_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("MouseButtons"),
        qtscript_create_Qt_MouseButtons_class(engine));
    ctor.setProperty(QString::fromLatin1("MatchFlag"),
        qtscript_create_Qt_MatchFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("MatchFlags"),
        qtscript_create_Qt_MatchFlags_class(engine));
    ctor.setProperty(QString::fromLatin1("PenCapStyle"),
        qtscript_create_Qt_PenCapStyle_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TextElideMode"),
        qtscript_create_Qt_TextElideMode_class(engine, ctor));
    return ctor;
}
