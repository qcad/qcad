#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtoolbar.h>
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
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qtoolbar.h>
#include <qwidget.h>

#include "qtscriptshell_QToolBar.h"

static const char * const qtscript_QToolBar_function_names[] = {
    "QToolBar"
    // static
    // prototype
    , "actionAt"
    , "actionGeometry"
    , "addAction"
    , "addSeparator"
    , "addWidget"
    , "allowedAreas"
    , "clear"
    , "iconSize"
    , "insertSeparator"
    , "insertWidget"
    , "isAreaAllowed"
    , "isFloatable"
    , "isFloating"
    , "orientation"
    , "setAllowedAreas"
    , "setFloatable"
    , "setMovable"
    , "setOrientation"
    , "toggleViewAction"
    , "toolButtonStyle"
    , "widgetForAction"
    , "toString"
};

static const char * const qtscript_QToolBar_function_signatures[] = {
    "QWidget parent\nString title, QWidget parent"
    // static
    // prototype
    , "QPoint p\nint x, int y"
    , "QAction action"
    , "QIcon icon, String text\nString text"
    , ""
    , "QWidget widget"
    , ""
    , ""
    , ""
    , "QAction before"
    , "QAction before, QWidget widget"
    , "ToolBarArea area"
    , ""
    , ""
    , ""
    , "ToolBarAreas areas"
    , "bool floatable"
    , "bool movable"
    , "Orientation orientation"
    , ""
    , ""
    , "QAction action"
""
};

static const int qtscript_QToolBar_function_lengths[] = {
    2
    // static
    // prototype
    , 2
    , 1
    , 2
    , 0
    , 1
    , 0
    , 0
    , 0
    , 1
    , 2
    , 1
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QToolBar_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QToolBar::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QToolBar*)
Q_DECLARE_METATYPE(QtScriptShell_QToolBar*)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QFlags<Qt::ToolBarArea>)
Q_DECLARE_METATYPE(Qt::ToolBarArea)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(Qt::ToolButtonStyle)

//
// QToolBar
//

static QScriptValue qtscript_QToolBar_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 21;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QToolBar* _q_self = qscriptvalue_cast<QToolBar*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QToolBar.%0(): this object is not a QToolBar")
            .arg(qtscript_QToolBar_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QAction* _q_result = _q_self->actionAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QAction* _q_result = _q_self->actionAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        QRect _q_result = _q_self->actionGeometry(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QAction* _q_result = _q_self->addAction(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QAction* _q_result = _q_self->addAction(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->addSeparator();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QAction* _q_result = _q_self->addWidget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QFlags<Qt::ToolBarArea> _q_result = _q_self->allowedAreas();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->iconSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        QAction* _q_result = _q_self->insertSeparator(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QAction* _q_result = _q_self->insertWidget(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        Qt::ToolBarArea _q_arg0 = qscriptvalue_cast<Qt::ToolBarArea>(context->argument(0));
        bool _q_result = _q_self->isAreaAllowed(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isFloatable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isFloating();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        Qt::Orientation _q_result = _q_self->orientation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QFlags<Qt::ToolBarArea> _q_arg0 = qscriptvalue_cast<QFlags<Qt::ToolBarArea> >(context->argument(0));
        _q_self->setAllowedAreas(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFloatable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setMovable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        _q_self->setOrientation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->toggleViewAction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        Qt::ToolButtonStyle _q_result = _q_self->toolButtonStyle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        QWidget* _q_result = _q_self->widgetForAction(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21: {
    QString result = QString::fromLatin1("QToolBar");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QToolBar_throw_ambiguity_error_helper(context,
        qtscript_QToolBar_function_names[_id+1],
        qtscript_QToolBar_function_signatures[_id+1]);
}

static QScriptValue qtscript_QToolBar_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QToolBar(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QToolBar* _q_cpp_result = new QtScriptShell_QToolBar();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QToolBar*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QToolBar* _q_cpp_result = new QtScriptShell_QToolBar(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QToolBar*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QToolBar* _q_cpp_result = new QtScriptShell_QToolBar(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QToolBar*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QToolBar* _q_cpp_result = new QtScriptShell_QToolBar(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QToolBar*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QToolBar_throw_ambiguity_error_helper(context,
        qtscript_QToolBar_function_names[_id],
        qtscript_QToolBar_function_signatures[_id]);
}

static QScriptValue qtscript_QToolBar_toScriptValue(QScriptEngine *engine, QToolBar* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QToolBar_fromScriptValue(const QScriptValue &value, QToolBar* &out)
{
    out = qobject_cast<QToolBar*>(value.toQObject());
}

QScriptValue qtscript_create_QToolBar_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QToolBar*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QToolBar*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 22; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QToolBar_prototype_call, qtscript_QToolBar_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QToolBar_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QToolBar*>(engine, qtscript_QToolBar_toScriptValue, 
        qtscript_QToolBar_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QToolBar_static_call, proto, qtscript_QToolBar_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
