#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qcoreevent.h>
#include <QVariant>
#include <qcoreevent.h>

#include "qtscriptshell_QEvent.h"

static const char * const qtscript_QEvent_function_names[] = {
    "QEvent"
    // static
    , "registerEventType"
    // prototype
    , "accept"
    , "ignore"
    , "isAccepted"
    , "operator_assign"
    , "setAccepted"
    , "spontaneous"
    , "type"
    , "toString"
};

static const char * const qtscript_QEvent_function_signatures[] = {
    "Type type\nQEvent other"
    // static
    , "int hint"
    // prototype
    , ""
    , ""
    , ""
    , "QEvent other"
    , "bool accepted"
    , ""
    , ""
""
};

static const int qtscript_QEvent_function_lengths[] = {
    1
    // static
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QEvent_metaObject()
{
    return &QEvent::staticMetaObject;
}

Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QtScriptShell_QEvent*)
Q_DECLARE_METATYPE(QEvent::Type)

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
// QEvent::Type
//

static const QEvent::Type qtscript_QEvent_Type_values[] = {
    QEvent::None
    , QEvent::Timer
    , QEvent::MouseButtonPress
    , QEvent::MouseButtonRelease
    , QEvent::MouseButtonDblClick
    , QEvent::MouseMove
    , QEvent::KeyPress
    , QEvent::KeyRelease
    , QEvent::FocusIn
    , QEvent::FocusOut
    , QEvent::Enter
    , QEvent::Leave
    , QEvent::Paint
    , QEvent::Move
    , QEvent::Resize
    , QEvent::Create
    , QEvent::Destroy
    , QEvent::Show
    , QEvent::Hide
    , QEvent::Close
    , QEvent::Quit
    , QEvent::ParentChange
    , QEvent::ThreadChange
    , QEvent::FocusAboutToChange
    , QEvent::WindowActivate
    , QEvent::WindowDeactivate
    , QEvent::ShowToParent
    , QEvent::HideToParent
    , QEvent::Wheel
    , QEvent::WindowTitleChange
    , QEvent::WindowIconChange
    , QEvent::ApplicationWindowIconChange
    , QEvent::ApplicationFontChange
    , QEvent::ApplicationLayoutDirectionChange
    , QEvent::ApplicationPaletteChange
    , QEvent::PaletteChange
    , QEvent::Clipboard
    , QEvent::Speech
    , QEvent::MetaCall
    , QEvent::SockAct
    , QEvent::ShortcutOverride
    , QEvent::DeferredDelete
    , QEvent::DragEnter
    , QEvent::DragMove
    , QEvent::DragLeave
    , QEvent::Drop
    , QEvent::DragResponse
    , QEvent::ChildAdded
    , QEvent::ChildPolished
    , QEvent::ChildRemoved
    , QEvent::ShowWindowRequest
    , QEvent::PolishRequest
    , QEvent::Polish
    , QEvent::LayoutRequest
    , QEvent::UpdateRequest
    , QEvent::UpdateLater
    , QEvent::EmbeddingControl
    , QEvent::ActivateControl
    , QEvent::DeactivateControl
    , QEvent::ContextMenu
    , QEvent::InputMethod
    , QEvent::TabletMove
    , QEvent::LocaleChange
    , QEvent::LanguageChange
    , QEvent::LayoutDirectionChange
    , QEvent::Style
    , QEvent::TabletPress
    , QEvent::TabletRelease
    , QEvent::OkRequest
    , QEvent::HelpRequest
    , QEvent::IconDrag
    , QEvent::FontChange
    , QEvent::EnabledChange
    , QEvent::ActivationChange
    , QEvent::StyleChange
    , QEvent::IconTextChange
    , QEvent::ModifiedChange
    , QEvent::WindowBlocked
    , QEvent::WindowUnblocked
    , QEvent::WindowStateChange
    , QEvent::MouseTrackingChange
    , QEvent::ToolTip
    , QEvent::WhatsThis
    , QEvent::StatusTip
    , QEvent::ActionChanged
    , QEvent::ActionAdded
    , QEvent::ActionRemoved
    , QEvent::FileOpen
    , QEvent::Shortcut
    , QEvent::WhatsThisClicked
    , QEvent::ToolBarChange
    , QEvent::ApplicationActivate
    , QEvent::ApplicationDeactivate
    , QEvent::QueryWhatsThis
    , QEvent::EnterWhatsThisMode
    , QEvent::LeaveWhatsThisMode
    , QEvent::ZOrderChange
    , QEvent::HoverEnter
    , QEvent::HoverLeave
    , QEvent::HoverMove
    , QEvent::ParentAboutToChange
    , QEvent::WinEventAct
    , QEvent::AcceptDropsChange
    , QEvent::ZeroTimerEvent
    , QEvent::GraphicsSceneMouseMove
    , QEvent::GraphicsSceneMousePress
    , QEvent::GraphicsSceneMouseRelease
    , QEvent::GraphicsSceneMouseDoubleClick
    , QEvent::GraphicsSceneContextMenu
    , QEvent::GraphicsSceneHoverEnter
    , QEvent::GraphicsSceneHoverMove
    , QEvent::GraphicsSceneHoverLeave
    , QEvent::GraphicsSceneHelp
    , QEvent::GraphicsSceneDragEnter
    , QEvent::GraphicsSceneDragMove
    , QEvent::GraphicsSceneDragLeave
    , QEvent::GraphicsSceneDrop
    , QEvent::GraphicsSceneWheel
    , QEvent::KeyboardLayoutChange
    , QEvent::DynamicPropertyChange
    , QEvent::TabletEnterProximity
    , QEvent::TabletLeaveProximity
    , QEvent::NonClientAreaMouseMove
    , QEvent::NonClientAreaMouseButtonPress
    , QEvent::NonClientAreaMouseButtonRelease
    , QEvent::NonClientAreaMouseButtonDblClick
    , QEvent::MacSizeChange
    , QEvent::ContentsRectChange
    , QEvent::MacGLWindowChange
    , QEvent::FutureCallOut
    , QEvent::GraphicsSceneResize
    , QEvent::GraphicsSceneMove
    , QEvent::CursorChange
    , QEvent::ToolTipChange
    , QEvent::NetworkReplyUpdated
    , QEvent::GrabMouse
    , QEvent::UngrabMouse
    , QEvent::GrabKeyboard
    , QEvent::UngrabKeyboard
    , QEvent::MacGLClearDrawable
    , QEvent::StateMachineSignal
    , QEvent::StateMachineWrapped
    , QEvent::TouchBegin
    , QEvent::TouchUpdate
    , QEvent::TouchEnd
    , QEvent::NativeGesture
    , QEvent::Gesture
    , QEvent::RequestSoftwareInputPanel
    , QEvent::CloseSoftwareInputPanel
    , QEvent::GestureOverride
    , QEvent::WinIdChange
    , QEvent::ScrollPrepare
    , QEvent::Scroll
    , QEvent::Expose
    , QEvent::InputMethodQuery
    , QEvent::OrientationChange
    , QEvent::TouchCancel
    , QEvent::ThemeChange
    , QEvent::SockClose
    , QEvent::PlatformPanel
    , QEvent::StyleAnimationUpdate
    , QEvent::ApplicationStateChange
    , QEvent::WindowChangeInternal
    , QEvent::User
    , QEvent::MaxUser
};

static const char * const qtscript_QEvent_Type_keys[] = {
    "None"
    , "Timer"
    , "MouseButtonPress"
    , "MouseButtonRelease"
    , "MouseButtonDblClick"
    , "MouseMove"
    , "KeyPress"
    , "KeyRelease"
    , "FocusIn"
    , "FocusOut"
    , "Enter"
    , "Leave"
    , "Paint"
    , "Move"
    , "Resize"
    , "Create"
    , "Destroy"
    , "Show"
    , "Hide"
    , "Close"
    , "Quit"
    , "ParentChange"
    , "ThreadChange"
    , "FocusAboutToChange"
    , "WindowActivate"
    , "WindowDeactivate"
    , "ShowToParent"
    , "HideToParent"
    , "Wheel"
    , "WindowTitleChange"
    , "WindowIconChange"
    , "ApplicationWindowIconChange"
    , "ApplicationFontChange"
    , "ApplicationLayoutDirectionChange"
    , "ApplicationPaletteChange"
    , "PaletteChange"
    , "Clipboard"
    , "Speech"
    , "MetaCall"
    , "SockAct"
    , "ShortcutOverride"
    , "DeferredDelete"
    , "DragEnter"
    , "DragMove"
    , "DragLeave"
    , "Drop"
    , "DragResponse"
    , "ChildAdded"
    , "ChildPolished"
    , "ChildRemoved"
    , "ShowWindowRequest"
    , "PolishRequest"
    , "Polish"
    , "LayoutRequest"
    , "UpdateRequest"
    , "UpdateLater"
    , "EmbeddingControl"
    , "ActivateControl"
    , "DeactivateControl"
    , "ContextMenu"
    , "InputMethod"
    , "TabletMove"
    , "LocaleChange"
    , "LanguageChange"
    , "LayoutDirectionChange"
    , "Style"
    , "TabletPress"
    , "TabletRelease"
    , "OkRequest"
    , "HelpRequest"
    , "IconDrag"
    , "FontChange"
    , "EnabledChange"
    , "ActivationChange"
    , "StyleChange"
    , "IconTextChange"
    , "ModifiedChange"
    , "WindowBlocked"
    , "WindowUnblocked"
    , "WindowStateChange"
    , "MouseTrackingChange"
    , "ToolTip"
    , "WhatsThis"
    , "StatusTip"
    , "ActionChanged"
    , "ActionAdded"
    , "ActionRemoved"
    , "FileOpen"
    , "Shortcut"
    , "WhatsThisClicked"
    , "ToolBarChange"
    , "ApplicationActivate"
    , "ApplicationDeactivate"
    , "QueryWhatsThis"
    , "EnterWhatsThisMode"
    , "LeaveWhatsThisMode"
    , "ZOrderChange"
    , "HoverEnter"
    , "HoverLeave"
    , "HoverMove"
    , "ParentAboutToChange"
    , "WinEventAct"
    , "AcceptDropsChange"
    , "ZeroTimerEvent"
    , "GraphicsSceneMouseMove"
    , "GraphicsSceneMousePress"
    , "GraphicsSceneMouseRelease"
    , "GraphicsSceneMouseDoubleClick"
    , "GraphicsSceneContextMenu"
    , "GraphicsSceneHoverEnter"
    , "GraphicsSceneHoverMove"
    , "GraphicsSceneHoverLeave"
    , "GraphicsSceneHelp"
    , "GraphicsSceneDragEnter"
    , "GraphicsSceneDragMove"
    , "GraphicsSceneDragLeave"
    , "GraphicsSceneDrop"
    , "GraphicsSceneWheel"
    , "KeyboardLayoutChange"
    , "DynamicPropertyChange"
    , "TabletEnterProximity"
    , "TabletLeaveProximity"
    , "NonClientAreaMouseMove"
    , "NonClientAreaMouseButtonPress"
    , "NonClientAreaMouseButtonRelease"
    , "NonClientAreaMouseButtonDblClick"
    , "MacSizeChange"
    , "ContentsRectChange"
    , "MacGLWindowChange"
    , "FutureCallOut"
    , "GraphicsSceneResize"
    , "GraphicsSceneMove"
    , "CursorChange"
    , "ToolTipChange"
    , "NetworkReplyUpdated"
    , "GrabMouse"
    , "UngrabMouse"
    , "GrabKeyboard"
    , "UngrabKeyboard"
    , "MacGLClearDrawable"
    , "StateMachineSignal"
    , "StateMachineWrapped"
    , "TouchBegin"
    , "TouchUpdate"
    , "TouchEnd"
    , "NativeGesture"
    , "Gesture"
    , "RequestSoftwareInputPanel"
    , "CloseSoftwareInputPanel"
    , "GestureOverride"
    , "WinIdChange"
    , "ScrollPrepare"
    , "Scroll"
    , "Expose"
    , "InputMethodQuery"
    , "OrientationChange"
    , "TouchCancel"
    , "ThemeChange"
    , "SockClose"
    , "PlatformPanel"
    , "StyleAnimationUpdate"
    , "ApplicationStateChange"
    , "WindowChangeInternal"
    , "User"
    , "MaxUser"
};

static QString qtscript_QEvent_Type_toStringHelper(QEvent::Type value)
{
    const QMetaObject *meta = qtscript_QEvent_metaObject();
    int idx = meta->indexOfEnumerator("Type");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QEvent_Type_toScriptValue(QScriptEngine *engine, const QEvent::Type &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QEvent"));
    return clazz.property(qtscript_QEvent_Type_toStringHelper(value));
}

static void qtscript_QEvent_Type_fromScriptValue(const QScriptValue &value, QEvent::Type &out)
{
    out = qvariant_cast<QEvent::Type>(value.toVariant());
}

static QScriptValue qtscript_construct_QEvent_Type(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QEvent_metaObject();
    int idx = meta->indexOfEnumerator("Type");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QEvent::Type>(arg));
    return context->throwError(QString::fromLatin1("Type(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QEvent_Type_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QEvent::Type value = qscriptvalue_cast<QEvent::Type>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QEvent_Type_toString(QScriptContext *context, QScriptEngine *engine)
{
    QEvent::Type value = qscriptvalue_cast<QEvent::Type>(context->thisObject());
    return QScriptValue(engine, qtscript_QEvent_Type_toStringHelper(value));
}

static QScriptValue qtscript_create_QEvent_Type_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QEvent_Type,
        qtscript_QEvent_Type_valueOf, qtscript_QEvent_Type_toString);
    qScriptRegisterMetaType<QEvent::Type>(engine, qtscript_QEvent_Type_toScriptValue,
        qtscript_QEvent_Type_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 165; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QEvent_Type_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QEvent_Type_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QEvent
//

static QScriptValue qtscript_QEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 7;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QEvent* _q_self = qscriptvalue_cast<QEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QEvent.%0(): this object is not a QEvent")
            .arg(qtscript_QEvent_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->accept();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->ignore();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isAccepted();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QEvent _q_arg0 = qscriptvalue_cast<QEvent>(context->argument(0));
        QEvent& _q_result = _q_self->operator=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setAccepted(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->spontaneous();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QEvent::Type _q_result = _q_self->type();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7: {
    QString result;
    QDebug d(&result);
    d << _q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QEvent_throw_ambiguity_error_helper(context,
        qtscript_QEvent_function_names[_id+2],
        qtscript_QEvent_function_signatures[_id+2]);
}

static QScriptValue qtscript_QEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QEvent::Type>() == context->argument(0).toVariant().userType())) {
            QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
            QtScriptShell_QEvent* _q_cpp_result = new QtScriptShell_QEvent(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QEvent*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QEvent>() == context->argument(0).toVariant().userType())) {
            QEvent _q_arg0 = qscriptvalue_cast<QEvent>(context->argument(0));
            QtScriptShell_QEvent* _q_cpp_result = new QtScriptShell_QEvent(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QEvent*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = QEvent::registerEventType();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = QEvent::registerEventType(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QEvent_throw_ambiguity_error_helper(context,
        qtscript_QEvent_function_names[_id],
        qtscript_QEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QEvent*)0));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QEvent_prototype_call, qtscript_QEvent_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QEvent_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QEvent_static_call, proto, qtscript_QEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QEvent_static_call,
            qtscript_QEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Type"),
        qtscript_create_QEvent_Type_class(engine, ctor));
    return ctor;
}
