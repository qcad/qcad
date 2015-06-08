#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qwidget.h>
#include <QGesture>
#include <QIcon>
#include <QMessageBox>
#include <QVariant>
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
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QWidget.h"

static const char * const qtscript_QWidget_function_names[] = {
    "QWidget"
    // static
    , "keyboardGrabber"
    , "mouseGrabber"
    , "setTabOrder"
    // prototype
    , "actions"
    , "activateWindow"
    , "addAction"
    , "addActions"
    , "adjustSize"
    , "backgroundRole"
    , "childAt"
    , "clearFocus"
    , "clearMask"
    , "contentsMargins"
    , "contentsRect"
    , "createWinId"
    , "effectiveWinId"
    , "ensurePolished"
    , "focusProxy"
    , "focusWidget"
    , "foregroundRole"
    , "getContentsMargins"
    , "grabGesture"
    , "grabKeyboard"
    , "grabMouse"
    , "grabShortcut"
    , "graphicsEffect"
    , "graphicsProxyWidget"
    , "heightForWidth"
    , "inputContext"
    , "inputMethodQuery"
    , "insertAction"
    , "insertActions"
    , "isAncestorOf"
    , "isEnabledTo"
    , "isHidden"
    , "isLeftToRight"
    , "isRightToLeft"
    , "isVisibleTo"
    , "isWindow"
    , "layout"
    , "mapFrom"
    , "mapFromGlobal"
    , "mapFromParent"
    , "mapTo"
    , "mapToGlobal"
    , "mapToParent"
    , "mask"
    , "move"
    , "nativeParentWidget"
    , "nextInFocusChain"
    , "overrideWindowFlags"
    , "overrideWindowState"
    , "parentWidget"
    , "previousInFocusChain"
    , "releaseKeyboard"
    , "releaseMouse"
    , "releaseShortcut"
    , "removeAction"
    , "render"
    , "repaint"
    , "resize"
    , "restoreGeometry"
    , "saveGeometry"
    , "scroll"
    , "setAttribute"
    , "setBackgroundRole"
    , "setBaseSize"
    , "setContentsMargins"
    , "setFixedHeight"
    , "setFixedSize"
    , "setFixedWidth"
    , "setFocus"
    , "setFocusProxy"
    , "setForegroundRole"
    , "setGeometry"
    , "setGraphicsEffect"
    , "setInputContext"
    , "setLayout"
    , "setMask"
    , "setMaximumSize"
    , "setMinimumSize"
    , "setParent"
    , "setShortcutAutoRepeat"
    , "setShortcutEnabled"
    , "setSizeIncrement"
    , "setSizePolicy"
    , "setStyle"
    , "setWindowFlags"
    , "setWindowOpacity"
    , "setWindowRole"
    , "setWindowState"
    , "stackUnder"
    , "style"
    , "testAttribute"
    , "underMouse"
    , "ungrabGesture"
    , "unsetCursor"
    , "unsetLayoutDirection"
    , "unsetLocale"
    , "update"
    , "updateGeometry"
    , "visibleRegion"
    , "winId"
    , "window"
    , "windowFlags"
    , "windowOpacity"
    , "windowRole"
    , "windowState"
    , "windowType"
    , "toString"
};

static const char * const qtscript_QWidget_function_signatures[] = {
    "QWidget parent, WindowFlags f"
    // static
    , ""
    , ""
    , "QWidget arg__1, QWidget arg__2"
    // prototype
    , ""
    , ""
    , "QAction action"
    , "List actions"
    , ""
    , ""
    , "QPoint p\nint x, int y"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int left, int top, int right, int bottom"
    , "GestureType type, GestureFlags flags"
    , ""
    , "\nQCursor arg__1"
    , "QKeySequence key, ShortcutContext context"
    , ""
    , ""
    , "int arg__1"
    , ""
    , "InputMethodQuery arg__1"
    , "QAction before, QAction action"
    , "QAction before, List actions"
    , "QWidget child"
    , "QWidget arg__1"
    , ""
    , ""
    , ""
    , "QWidget arg__1"
    , ""
    , ""
    , "QWidget arg__1, QPoint arg__2"
    , "QPoint arg__1"
    , "QPoint arg__1"
    , "QWidget arg__1, QPoint arg__2"
    , "QPoint arg__1"
    , "QPoint arg__1"
    , ""
    , "int x, int y"
    , ""
    , ""
    , "WindowFlags type"
    , "WindowStates state"
    , ""
    , ""
    , ""
    , ""
    , "int id"
    , "QAction action"
    , "QPaintDevice target, QPoint targetOffset, QRegion sourceRegion, RenderFlags renderFlags\nQPainter painter, QPoint targetOffset, QRegion sourceRegion, RenderFlags renderFlags"
    , "QRect arg__1\nQRegion arg__1\nint x, int y, int w, int h"
    , "int w, int h"
    , "QByteArray geometry"
    , ""
    , "int dx, int dy\nint dx, int dy, QRect arg__3"
    , "WidgetAttribute arg__1, bool on"
    , "ColorRole arg__1"
    , "int basew, int baseh"
    , "QMargins margins\nint left, int top, int right, int bottom"
    , "int h"
    , "QSize arg__1\nint w, int h"
    , "int w"
    , "FocusReason reason"
    , "QWidget arg__1"
    , "ColorRole arg__1"
    , "int x, int y, int w, int h"
    , "QGraphicsEffect effect"
    , "QInputContext arg__1"
    , "QLayout arg__1"
    , "QBitmap arg__1\nQRegion arg__1"
    , "int maxw, int maxh"
    , "int minw, int minh"
    , "QWidget parent\nQWidget parent, WindowFlags f"
    , "int id, bool enable"
    , "int id, bool enable"
    , "int w, int h"
    , "Policy horizontal, Policy vertical"
    , "QStyle arg__1"
    , "WindowFlags type"
    , "qreal level"
    , "String arg__1"
    , "WindowStates state"
    , "QWidget arg__1"
    , ""
    , "WidgetAttribute arg__1"
    , ""
    , "GestureType type"
    , ""
    , ""
    , ""
    , "QRect arg__1\nQRegion arg__1\nint x, int y, int w, int h"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QWidget_function_lengths[] = {
    2
    // static
    , 0
    , 0
    , 2
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
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
    , 0
    , 4
    , 2
    , 0
    , 1
    , 2
    , 0
    , 0
    , 1
    , 0
    , 1
    , 2
    , 2
    , 1
    , 1
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 2
    , 1
    , 1
    , 2
    , 1
    , 1
    , 0
    , 2
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 4
    , 4
    , 2
    , 1
    , 0
    , 3
    , 2
    , 1
    , 2
    , 4
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 4
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 1
    , 0
    , 1
    , 0
    , 0
    , 0
    , 4
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QtScriptShell_QWidget*)
Q_DECLARE_METATYPE(QWidget::RenderFlag)
Q_DECLARE_METATYPE(QFlags<QWidget::RenderFlag>)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QList<QAction*>)
Q_DECLARE_METATYPE(QPalette::ColorRole)
Q_DECLARE_METATYPE(QMargins)
Q_DECLARE_METATYPE(WId)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(QFlags<Qt::GestureFlag>)
Q_DECLARE_METATYPE(Qt::ShortcutContext)
Q_DECLARE_METATYPE(QGraphicsEffect*)
Q_DECLARE_METATYPE(QGraphicsProxyWidget*)
Q_DECLARE_METATYPE(QInputContext*)
Q_DECLARE_METATYPE(Qt::InputMethodQuery)
Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)
Q_DECLARE_METATYPE(QFlags<Qt::WindowState>)
Q_DECLARE_METATYPE(QPaintDevice*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(Qt::WidgetAttribute)
Q_DECLARE_METATYPE(Qt::FocusReason)
Q_DECLARE_METATYPE(QSizePolicy::Policy)
Q_DECLARE_METATYPE(QStyle*)
Q_DECLARE_METATYPE(Qt::WindowType)

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
// QWidget::RenderFlag
//

static const QWidget::RenderFlag qtscript_QWidget_RenderFlag_values[] = {
    QWidget::DrawWindowBackground
    , QWidget::DrawChildren
    , QWidget::IgnoreMask
};

static const char * const qtscript_QWidget_RenderFlag_keys[] = {
    "DrawWindowBackground"
    , "DrawChildren"
    , "IgnoreMask"
};

static QString qtscript_QWidget_RenderFlag_toStringHelper(QWidget::RenderFlag value)
{
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QWidget_RenderFlag_values[i] == value)
            return QString::fromLatin1(qtscript_QWidget_RenderFlag_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QWidget_RenderFlag_toScriptValue(QScriptEngine *engine, const QWidget::RenderFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWidget"));
    return clazz.property(qtscript_QWidget_RenderFlag_toStringHelper(value));
}

static void qtscript_QWidget_RenderFlag_fromScriptValue(const QScriptValue &value, QWidget::RenderFlag &out)
{
    out = qvariant_cast<QWidget::RenderFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QWidget_RenderFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 3; ++i) {
        if (qtscript_QWidget_RenderFlag_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QWidget::RenderFlag>(arg));
    }
    return context->throwError(QString::fromLatin1("RenderFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWidget_RenderFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWidget::RenderFlag value = qscriptvalue_cast<QWidget::RenderFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWidget_RenderFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWidget::RenderFlag value = qscriptvalue_cast<QWidget::RenderFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QWidget_RenderFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QWidget_RenderFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWidget_RenderFlag,
        qtscript_QWidget_RenderFlag_valueOf, qtscript_QWidget_RenderFlag_toString);
    qScriptRegisterMetaType<QWidget::RenderFlag>(engine, qtscript_QWidget_RenderFlag_toScriptValue,
        qtscript_QWidget_RenderFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWidget_RenderFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWidget_RenderFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWidget::RenderFlags
//

static QScriptValue qtscript_QWidget_RenderFlags_toScriptValue(QScriptEngine *engine, const QWidget::RenderFlags &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QWidget_RenderFlags_fromScriptValue(const QScriptValue &value, QWidget::RenderFlags &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QWidget::RenderFlags>())
        out = qvariant_cast<QWidget::RenderFlags>(var);
    else if (var.userType() == qMetaTypeId<QWidget::RenderFlag>())
        out = qvariant_cast<QWidget::RenderFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QWidget_RenderFlags(QScriptContext *context, QScriptEngine *engine)
{
    QWidget::RenderFlags result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QWidget::RenderFlags>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QWidget::RenderFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("RenderFlags(): argument %0 is not of type RenderFlag").arg(i));
            }
            result |= qvariant_cast<QWidget::RenderFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QWidget_RenderFlags_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWidget::RenderFlags value = qscriptvalue_cast<QWidget::RenderFlags>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWidget_RenderFlags_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWidget::RenderFlags value = qscriptvalue_cast<QWidget::RenderFlags>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QWidget_RenderFlag_values[i]) == qtscript_QWidget_RenderFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QWidget_RenderFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QWidget_RenderFlags_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QWidget::RenderFlags>() == otherObj.value<QWidget::RenderFlags>())));
}

static QScriptValue qtscript_create_QWidget_RenderFlags_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QWidget_RenderFlags, qtscript_QWidget_RenderFlags_valueOf,
        qtscript_QWidget_RenderFlags_toString, qtscript_QWidget_RenderFlags_equals);
    qScriptRegisterMetaType<QWidget::RenderFlags>(engine, qtscript_QWidget_RenderFlags_toScriptValue,
        qtscript_QWidget_RenderFlags_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QWidget
//

static QScriptValue qtscript_QWidget_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 106;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QWidget* _q_self = qscriptvalue_cast<QWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWidget.%0(): this object is not a QWidget")
            .arg(qtscript_QWidget_function_names[_id+4]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<QAction*> _q_result = _q_self->actions();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->activateWindow();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        _q_self->addAction(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QList<QAction*> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->addActions(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        _q_self->adjustSize();
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QPalette::ColorRole _q_result = _q_self->backgroundRole();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QWidget* _q_result = _q_self->childAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QWidget* _q_result = _q_self->childAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        _q_self->clearFocus();
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        _q_self->clearMask();
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QMargins _q_result = _q_self->contentsMargins();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->contentsRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        _q_self->createWinId();
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        WId _q_result = _q_self->effectiveWinId();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        _q_self->ensurePolished();
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->focusProxy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->focusWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QPalette::ColorRole _q_result = _q_self->foregroundRole();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 4) {
        int* _q_arg0 = qscriptvalue_cast<int*>(context->argument(0));
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
        int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
        _q_self->getContentsMargins(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        Qt::GestureType _q_arg0 = qscriptvalue_cast<Qt::GestureType>(context->argument(0));
        _q_self->grabGesture(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        Qt::GestureType _q_arg0 = qscriptvalue_cast<Qt::GestureType>(context->argument(0));
        QFlags<Qt::GestureFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::GestureFlag> >(context->argument(1));
        _q_self->grabGesture(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        _q_self->grabKeyboard();
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        _q_self->grabMouse();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QCursor _q_arg0 = qscriptvalue_cast<QCursor>(context->argument(0));
        _q_self->grabMouse(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QKeySequence _q_arg0 = qscriptvalue_cast<QKeySequence>(context->argument(0));
        int _q_result = _q_self->grabShortcut(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QKeySequence _q_arg0 = qscriptvalue_cast<QKeySequence>(context->argument(0));
        Qt::ShortcutContext _q_arg1 = qscriptvalue_cast<Qt::ShortcutContext>(context->argument(1));
        int _q_result = _q_self->grabShortcut(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        QGraphicsEffect* _q_result = _q_self->graphicsEffect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        QGraphicsProxyWidget* _q_result = _q_self->graphicsProxyWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->heightForWidth(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        QInputContext* _q_result = _q_self->inputContext();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        Qt::InputMethodQuery _q_arg0 = qscriptvalue_cast<Qt::InputMethodQuery>(context->argument(0));
        QVariant _q_result = _q_self->inputMethodQuery(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 2) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        QAction* _q_arg1 = qscriptvalue_cast<QAction*>(context->argument(1));
        _q_self->insertAction(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 2) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        QList<QAction*> _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        _q_self->insertActions(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        bool _q_result = _q_self->isAncestorOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        bool _q_result = _q_self->isEnabledTo(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isHidden();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isLeftToRight();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isRightToLeft();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        bool _q_result = _q_self->isVisibleTo(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isWindow();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 36:
    if (context->argumentCount() == 0) {
        QLayout* _q_result = _q_self->layout();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        QPoint _q_result = _q_self->mapFrom(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QPoint _q_result = _q_self->mapFromGlobal(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QPoint _q_result = _q_self->mapFromParent(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 40:
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        QPoint _q_result = _q_self->mapTo(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QPoint _q_result = _q_self->mapToGlobal(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QPoint _q_result = _q_self->mapToParent(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 43:
    if (context->argumentCount() == 0) {
        QRegion _q_result = _q_self->mask();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 44:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->move(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->nativeParentWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 46:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->nextInFocusChain();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 1) {
        QFlags<Qt::WindowType> _q_arg0 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(0));
        _q_self->overrideWindowFlags(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 48:
    if (context->argumentCount() == 1) {
        QFlags<Qt::WindowState> _q_arg0 = qscriptvalue_cast<QFlags<Qt::WindowState> >(context->argument(0));
        _q_self->overrideWindowState(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 49:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->parentWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 50:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->previousInFocusChain();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 51:
    if (context->argumentCount() == 0) {
        _q_self->releaseKeyboard();
        return context->engine()->undefinedValue();
    }
    break;

    case 52:
    if (context->argumentCount() == 0) {
        _q_self->releaseMouse();
        return context->engine()->undefinedValue();
    }
    break;

    case 53:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->releaseShortcut(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 54:
    if (context->argumentCount() == 1) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        _q_self->removeAction(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 55:
    if (context->argumentCount() == 1) {
        QPaintDevice* _q_arg0 = qscriptvalue_cast<QPaintDevice*>(context->argument(0));
        _q_self->render(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QPaintDevice*>(context->argument(0))
            && (qMetaTypeId<QPoint>() == context->argument(1).toVariant().userType())) {
            QPaintDevice* _q_arg0 = qscriptvalue_cast<QPaintDevice*>(context->argument(0));
            QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
            _q_self->render(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QPainter*>(context->argument(0))
            && (qMetaTypeId<QPoint>() == context->argument(1).toVariant().userType())) {
            QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
            QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
            _q_self->render(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<QPaintDevice*>(context->argument(0))
            && (qMetaTypeId<QPoint>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRegion>() == context->argument(2).toVariant().userType())) {
            QPaintDevice* _q_arg0 = qscriptvalue_cast<QPaintDevice*>(context->argument(0));
            QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
            QRegion _q_arg2 = qscriptvalue_cast<QRegion>(context->argument(2));
            _q_self->render(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QPainter*>(context->argument(0))
            && (qMetaTypeId<QPoint>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRegion>() == context->argument(2).toVariant().userType())) {
            QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
            QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
            QRegion _q_arg2 = qscriptvalue_cast<QRegion>(context->argument(2));
            _q_self->render(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        if (qscriptvalue_cast<QPaintDevice*>(context->argument(0))
            && (qMetaTypeId<QPoint>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRegion>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QFlags<QWidget::RenderFlag> >() == context->argument(3).toVariant().userType())) {
            QPaintDevice* _q_arg0 = qscriptvalue_cast<QPaintDevice*>(context->argument(0));
            QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
            QRegion _q_arg2 = qscriptvalue_cast<QRegion>(context->argument(2));
            QFlags<QWidget::RenderFlag> _q_arg3 = qscriptvalue_cast<QFlags<QWidget::RenderFlag> >(context->argument(3));
            _q_self->render(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<QPainter*>(context->argument(0))
            && (qMetaTypeId<QPoint>() == context->argument(1).toVariant().userType())
            && (qMetaTypeId<QRegion>() == context->argument(2).toVariant().userType())
            && (qMetaTypeId<QFlags<QWidget::RenderFlag> >() == context->argument(3).toVariant().userType())) {
            QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
            QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
            QRegion _q_arg2 = qscriptvalue_cast<QRegion>(context->argument(2));
            QFlags<QWidget::RenderFlag> _q_arg3 = qscriptvalue_cast<QFlags<QWidget::RenderFlag> >(context->argument(3));
            _q_self->render(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 56:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            _q_self->repaint(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRegion>() == context->argument(0).toVariant().userType())) {
            QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
            _q_self->repaint(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->repaint(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 57:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->resize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 58:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        bool _q_result = _q_self->restoreGeometry(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 59:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->saveGeometry();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 60:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->scroll(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
        _q_self->scroll(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 61:
    if (context->argumentCount() == 1) {
        Qt::WidgetAttribute _q_arg0 = qscriptvalue_cast<Qt::WidgetAttribute>(context->argument(0));
        _q_self->setAttribute(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        Qt::WidgetAttribute _q_arg0 = qscriptvalue_cast<Qt::WidgetAttribute>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setAttribute(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 62:
    if (context->argumentCount() == 1) {
        QPalette::ColorRole _q_arg0 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(0));
        _q_self->setBackgroundRole(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 63:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setBaseSize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 64:
    if (context->argumentCount() == 1) {
        QMargins _q_arg0 = qscriptvalue_cast<QMargins>(context->argument(0));
        _q_self->setContentsMargins(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setContentsMargins(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 65:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setFixedHeight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 66:
    if (context->argumentCount() == 1) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        _q_self->setFixedSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setFixedSize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 67:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setFixedWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 68:
    if (context->argumentCount() == 1) {
        Qt::FocusReason _q_arg0 = qscriptvalue_cast<Qt::FocusReason>(context->argument(0));
        _q_self->setFocus(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 69:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setFocusProxy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 70:
    if (context->argumentCount() == 1) {
        QPalette::ColorRole _q_arg0 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(0));
        _q_self->setForegroundRole(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 71:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setGeometry(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 72:
    if (context->argumentCount() == 1) {
        QGraphicsEffect* _q_arg0 = qscriptvalue_cast<QGraphicsEffect*>(context->argument(0));
        _q_self->setGraphicsEffect(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 73:
    if (context->argumentCount() == 1) {
        QInputContext* _q_arg0 = qscriptvalue_cast<QInputContext*>(context->argument(0));
        _q_self->setInputContext(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 74:
    if (context->argumentCount() == 1) {
        QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
        _q_self->setLayout(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 75:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QBitmap>() == context->argument(0).toVariant().userType())) {
            QBitmap _q_arg0 = qscriptvalue_cast<QBitmap>(context->argument(0));
            _q_self->setMask(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRegion>() == context->argument(0).toVariant().userType())) {
            QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
            _q_self->setMask(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 76:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setMaximumSize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 77:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setMinimumSize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 78:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setParent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        _q_self->setParent(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 79:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setShortcutAutoRepeat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setShortcutAutoRepeat(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 80:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setShortcutEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setShortcutEnabled(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 81:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setSizeIncrement(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 82:
    if (context->argumentCount() == 2) {
        QSizePolicy::Policy _q_arg0 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(0));
        QSizePolicy::Policy _q_arg1 = qscriptvalue_cast<QSizePolicy::Policy>(context->argument(1));
        _q_self->setSizePolicy(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 83:
    if (context->argumentCount() == 1) {
        QStyle* _q_arg0 = qscriptvalue_cast<QStyle*>(context->argument(0));
        _q_self->setStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 84:
    if (context->argumentCount() == 1) {
        QFlags<Qt::WindowType> _q_arg0 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(0));
        _q_self->setWindowFlags(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 85:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setWindowOpacity(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 86:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setWindowRole(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 87:
    if (context->argumentCount() == 1) {
        QFlags<Qt::WindowState> _q_arg0 = qscriptvalue_cast<QFlags<Qt::WindowState> >(context->argument(0));
        _q_self->setWindowState(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 88:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->stackUnder(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 89:
    if (context->argumentCount() == 0) {
        QStyle* _q_result = _q_self->style();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 90:
    if (context->argumentCount() == 1) {
        Qt::WidgetAttribute _q_arg0 = qscriptvalue_cast<Qt::WidgetAttribute>(context->argument(0));
        bool _q_result = _q_self->testAttribute(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 91:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->underMouse();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 92:
    if (context->argumentCount() == 1) {
        Qt::GestureType _q_arg0 = qscriptvalue_cast<Qt::GestureType>(context->argument(0));
        _q_self->ungrabGesture(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 93:
    if (context->argumentCount() == 0) {
        _q_self->unsetCursor();
        return context->engine()->undefinedValue();
    }
    break;

    case 94:
    if (context->argumentCount() == 0) {
        _q_self->unsetLayoutDirection();
        return context->engine()->undefinedValue();
    }
    break;

    case 95:
    if (context->argumentCount() == 0) {
        _q_self->unsetLocale();
        return context->engine()->undefinedValue();
    }
    break;

    case 96:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            _q_self->update(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRegion>() == context->argument(0).toVariant().userType())) {
            QRegion _q_arg0 = qscriptvalue_cast<QRegion>(context->argument(0));
            _q_self->update(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->update(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 97:
    if (context->argumentCount() == 0) {
        _q_self->updateGeometry();
        return context->engine()->undefinedValue();
    }
    break;

    case 98:
    if (context->argumentCount() == 0) {
        QRegion _q_result = _q_self->visibleRegion();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 99:
    if (context->argumentCount() == 0) {
        WId _q_result = _q_self->winId();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 100:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->window();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 101:
    if (context->argumentCount() == 0) {
        QFlags<Qt::WindowType> _q_result = _q_self->windowFlags();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 102:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->windowOpacity();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 103:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->windowRole();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 104:
    if (context->argumentCount() == 0) {
        QFlags<Qt::WindowState> _q_result = _q_self->windowState();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 105:
    if (context->argumentCount() == 0) {
        Qt::WindowType _q_result = _q_self->windowType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 106: {
    QString result = QString::fromLatin1("QWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWidget_throw_ambiguity_error_helper(context,
        qtscript_QWidget_function_names[_id+4],
        qtscript_QWidget_function_signatures[_id+4]);
}

static QScriptValue qtscript_QWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QWidget* _q_cpp_result = new QtScriptShell_QWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QWidget* _q_cpp_result = new QtScriptShell_QWidget(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QtScriptShell_QWidget* _q_cpp_result = new QtScriptShell_QWidget(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = QWidget::keyboardGrabber();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = QWidget::mouseGrabber();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QWidget::setTabOrder(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWidget_throw_ambiguity_error_helper(context,
        qtscript_QWidget_function_names[_id],
        qtscript_QWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QWidget_toScriptValue(QScriptEngine *engine, QWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QWidget_fromScriptValue(const QScriptValue &value, QWidget* &out)
{
    out = qobject_cast<QWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    proto.setProperty(QString::fromLatin1("__QPaintDevice__"),
        engine->defaultPrototype(qMetaTypeId<QPaintDevice*>()),
        QScriptValue::SkipInEnumeration);
    for (int i = 0; i < 107; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWidget_prototype_call, qtscript_QWidget_function_lengths[i+4]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWidget_function_names[i+4]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QWidget*>(engine, qtscript_QWidget_toScriptValue, 
        qtscript_QWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWidget_static_call, proto, qtscript_QWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWidget_static_call,
            qtscript_QWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("RenderFlag"),
        qtscript_create_QWidget_RenderFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("RenderFlags"),
        qtscript_create_QWidget_RenderFlags_class(engine));
    return ctor;
}
