#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qmainwindow.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdockwidget.h>
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
#include <qmainwindow.h>
#include <qmargins.h>
#include <qmenu.h>
#include <qmenubar.h>
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
#include <qstatusbar.h>
#include <qstyle.h>
#include <qtoolbar.h>
#include <qwidget.h>

#include "qtscriptshell_QMainWindow.h"

static const char * const qtscript_QMainWindow_function_names[] = {
    "QMainWindow"
    // static
    // prototype
    , "addDockWidget"
    , "addToolBar"
    , "addToolBarBreak"
    , "centralWidget"
    , "corner"
    , "createPopupMenu"
    , "dockWidgetArea"
    , "insertToolBar"
    , "insertToolBarBreak"
    , "isSeparator"
    , "menuBar"
    , "menuWidget"
    , "removeDockWidget"
    , "removeToolBar"
    , "removeToolBarBreak"
    , "restoreDockWidget"
    , "restoreState"
    , "saveState"
    , "setCentralWidget"
    , "setCorner"
    , "setMenuBar"
    , "setMenuWidget"
    , "setStatusBar"
    , "setTabPosition"
    , "splitDockWidget"
    , "statusBar"
    , "tabPosition"
    , "tabifiedDockWidgets"
    , "tabifyDockWidget"
    , "toolBarArea"
    , "toolBarBreak"
    , "toString"
};

static const char * const qtscript_QMainWindow_function_signatures[] = {
    "QWidget parent, WindowFlags flags"
    // static
    // prototype
    , "DockWidgetArea area, QDockWidget dockwidget\nDockWidgetArea area, QDockWidget dockwidget, Orientation orientation"
    , "QToolBar toolbar\nToolBarArea area, QToolBar toolbar\nString title"
    , "ToolBarArea area"
    , ""
    , "Corner corner"
    , ""
    , "QDockWidget dockwidget"
    , "QToolBar before, QToolBar toolbar"
    , "QToolBar before"
    , "QPoint pos"
    , ""
    , ""
    , "QDockWidget dockwidget"
    , "QToolBar toolbar"
    , "QToolBar before"
    , "QDockWidget dockwidget"
    , "QByteArray state, int version"
    , "int version"
    , "QWidget widget"
    , "Corner corner, DockWidgetArea area"
    , "QMenuBar menubar"
    , "QWidget menubar"
    , "QStatusBar statusbar"
    , "DockWidgetAreas areas, TabPosition tabPosition"
    , "QDockWidget after, QDockWidget dockwidget, Orientation orientation"
    , ""
    , "DockWidgetArea area"
    , "QDockWidget dockwidget"
    , "QDockWidget first, QDockWidget second"
    , "QToolBar toolbar"
    , "QToolBar toolbar"
""
};

static const int qtscript_QMainWindow_function_lengths[] = {
    2
    // static
    // prototype
    , 3
    , 2
    , 1
    , 0
    , 1
    , 0
    , 1
    , 2
    , 1
    , 1
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 2
    , 3
    , 0
    , 1
    , 1
    , 2
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QMainWindow_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMainWindow::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QMainWindow_metaObject()
{
    return &QMainWindow::staticMetaObject;
}

Q_DECLARE_METATYPE(QMainWindow*)
Q_DECLARE_METATYPE(QtScriptShell_QMainWindow*)
Q_DECLARE_METATYPE(QMainWindow::DockOption)
Q_DECLARE_METATYPE(QFlags<QMainWindow::DockOption>)
Q_DECLARE_METATYPE(Qt::DockWidgetArea)
Q_DECLARE_METATYPE(QDockWidget*)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QToolBar*)
Q_DECLARE_METATYPE(Qt::ToolBarArea)
Q_DECLARE_METATYPE(Qt::Corner)
Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(QMenuBar*)
Q_DECLARE_METATYPE(QStatusBar*)
Q_DECLARE_METATYPE(QFlags<Qt::DockWidgetArea>)
Q_DECLARE_METATYPE(QTabWidget::TabPosition)
Q_DECLARE_METATYPE(QList<QDockWidget*>)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)

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
// QMainWindow::DockOption
//

static const QMainWindow::DockOption qtscript_QMainWindow_DockOption_values[] = {
    QMainWindow::AnimatedDocks
    , QMainWindow::AllowNestedDocks
    , QMainWindow::AllowTabbedDocks
    , QMainWindow::ForceTabbedDocks
    , QMainWindow::VerticalTabs
};

static const char * const qtscript_QMainWindow_DockOption_keys[] = {
    "AnimatedDocks"
    , "AllowNestedDocks"
    , "AllowTabbedDocks"
    , "ForceTabbedDocks"
    , "VerticalTabs"
};

static QString qtscript_QMainWindow_DockOption_toStringHelper(QMainWindow::DockOption value)
{
    const QMetaObject *meta = qtscript_QMainWindow_metaObject();
    int idx = meta->indexOfEnumerator("DockOption");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QMainWindow_DockOption_toScriptValue(QScriptEngine *engine, const QMainWindow::DockOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QMainWindow"));
    return clazz.property(qtscript_QMainWindow_DockOption_toStringHelper(value));
}

static void qtscript_QMainWindow_DockOption_fromScriptValue(const QScriptValue &value, QMainWindow::DockOption &out)
{
    out = qvariant_cast<QMainWindow::DockOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QMainWindow_DockOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QMainWindow_metaObject();
    int idx = meta->indexOfEnumerator("DockOption");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QMainWindow::DockOption>(arg));
    return context->throwError(QString::fromLatin1("DockOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QMainWindow_DockOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMainWindow::DockOption value = qscriptvalue_cast<QMainWindow::DockOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMainWindow_DockOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMainWindow::DockOption value = qscriptvalue_cast<QMainWindow::DockOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QMainWindow_DockOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QMainWindow_DockOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QMainWindow_DockOption,
        qtscript_QMainWindow_DockOption_valueOf, qtscript_QMainWindow_DockOption_toString);
    qScriptRegisterMetaType<QMainWindow::DockOption>(engine, qtscript_QMainWindow_DockOption_toScriptValue,
        qtscript_QMainWindow_DockOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QMainWindow_DockOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QMainWindow_DockOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QMainWindow::DockOptions
//

static QScriptValue qtscript_QMainWindow_DockOptions_toScriptValue(QScriptEngine *engine, const QMainWindow::DockOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QMainWindow_DockOptions_fromScriptValue(const QScriptValue &value, QMainWindow::DockOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QMainWindow::DockOptions>())
        out = qvariant_cast<QMainWindow::DockOptions>(var);
    else if (var.userType() == qMetaTypeId<QMainWindow::DockOption>())
        out = qvariant_cast<QMainWindow::DockOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QMainWindow_DockOptions(QScriptContext *context, QScriptEngine *engine)
{
    QMainWindow::DockOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QMainWindow::DockOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QMainWindow::DockOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("DockOptions(): argument %0 is not of type DockOption").arg(i));
            }
            result |= qvariant_cast<QMainWindow::DockOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QMainWindow_DockOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QMainWindow::DockOptions value = qscriptvalue_cast<QMainWindow::DockOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QMainWindow_DockOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QMainWindow::DockOptions value = qscriptvalue_cast<QMainWindow::DockOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 5; ++i) {
        if ((value & qtscript_QMainWindow_DockOption_values[i]) == qtscript_QMainWindow_DockOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QMainWindow_DockOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QMainWindow_DockOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QMainWindow::DockOptions>() == otherObj.value<QMainWindow::DockOptions>())));
}

static QScriptValue qtscript_create_QMainWindow_DockOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QMainWindow_DockOptions, qtscript_QMainWindow_DockOptions_valueOf,
        qtscript_QMainWindow_DockOptions_toString, qtscript_QMainWindow_DockOptions_equals);
    qScriptRegisterMetaType<QMainWindow::DockOptions>(engine, qtscript_QMainWindow_DockOptions_toScriptValue,
        qtscript_QMainWindow_DockOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QMainWindow
//

static QScriptValue qtscript_QMainWindow_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 31;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QMainWindow* _q_self = qscriptvalue_cast<QMainWindow*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMainWindow.%0(): this object is not a QMainWindow")
            .arg(qtscript_QMainWindow_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        Qt::DockWidgetArea _q_arg0 = qscriptvalue_cast<Qt::DockWidgetArea>(context->argument(0));
        QDockWidget* _q_arg1 = qscriptvalue_cast<QDockWidget*>(context->argument(1));
        _q_self->addDockWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        Qt::DockWidgetArea _q_arg0 = qscriptvalue_cast<Qt::DockWidgetArea>(context->argument(0));
        QDockWidget* _q_arg1 = qscriptvalue_cast<QDockWidget*>(context->argument(1));
        Qt::Orientation _q_arg2 = qscriptvalue_cast<Qt::Orientation>(context->argument(2));
        _q_self->addDockWidget(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QToolBar*>(context->argument(0))) {
            QToolBar* _q_arg0 = qscriptvalue_cast<QToolBar*>(context->argument(0));
            _q_self->addToolBar(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QToolBar* _q_result = _q_self->addToolBar(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        Qt::ToolBarArea _q_arg0 = qscriptvalue_cast<Qt::ToolBarArea>(context->argument(0));
        QToolBar* _q_arg1 = qscriptvalue_cast<QToolBar*>(context->argument(1));
        _q_self->addToolBar(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->addToolBarBreak();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        Qt::ToolBarArea _q_arg0 = qscriptvalue_cast<Qt::ToolBarArea>(context->argument(0));
        _q_self->addToolBarBreak(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->centralWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        Qt::Corner _q_arg0 = qscriptvalue_cast<Qt::Corner>(context->argument(0));
        Qt::DockWidgetArea _q_result = _q_self->corner(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QMenu* _q_result = _q_self->createPopupMenu();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QDockWidget* _q_arg0 = qscriptvalue_cast<QDockWidget*>(context->argument(0));
        Qt::DockWidgetArea _q_result = _q_self->dockWidgetArea(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        QToolBar* _q_arg0 = qscriptvalue_cast<QToolBar*>(context->argument(0));
        QToolBar* _q_arg1 = qscriptvalue_cast<QToolBar*>(context->argument(1));
        _q_self->insertToolBar(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QToolBar* _q_arg0 = qscriptvalue_cast<QToolBar*>(context->argument(0));
        _q_self->insertToolBarBreak(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        bool _q_result = _q_self->isSeparator(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QMenuBar* _q_result = _q_self->menuBar();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->menuWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QDockWidget* _q_arg0 = qscriptvalue_cast<QDockWidget*>(context->argument(0));
        _q_self->removeDockWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QToolBar* _q_arg0 = qscriptvalue_cast<QToolBar*>(context->argument(0));
        _q_self->removeToolBar(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QToolBar* _q_arg0 = qscriptvalue_cast<QToolBar*>(context->argument(0));
        _q_self->removeToolBarBreak(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QDockWidget* _q_arg0 = qscriptvalue_cast<QDockWidget*>(context->argument(0));
        bool _q_result = _q_self->restoreDockWidget(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        bool _q_result = _q_self->restoreState(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->restoreState(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->saveState();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QByteArray _q_result = _q_self->saveState(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setCentralWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 2) {
        Qt::Corner _q_arg0 = qscriptvalue_cast<Qt::Corner>(context->argument(0));
        Qt::DockWidgetArea _q_arg1 = qscriptvalue_cast<Qt::DockWidgetArea>(context->argument(1));
        _q_self->setCorner(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QMenuBar* _q_arg0 = qscriptvalue_cast<QMenuBar*>(context->argument(0));
        _q_self->setMenuBar(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setMenuWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QStatusBar* _q_arg0 = qscriptvalue_cast<QStatusBar*>(context->argument(0));
        _q_self->setStatusBar(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 2) {
        QFlags<Qt::DockWidgetArea> _q_arg0 = qscriptvalue_cast<QFlags<Qt::DockWidgetArea> >(context->argument(0));
        QTabWidget::TabPosition _q_arg1 = qscriptvalue_cast<QTabWidget::TabPosition>(context->argument(1));
        _q_self->setTabPosition(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 3) {
        QDockWidget* _q_arg0 = qscriptvalue_cast<QDockWidget*>(context->argument(0));
        QDockWidget* _q_arg1 = qscriptvalue_cast<QDockWidget*>(context->argument(1));
        Qt::Orientation _q_arg2 = qscriptvalue_cast<Qt::Orientation>(context->argument(2));
        _q_self->splitDockWidget(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        QStatusBar* _q_result = _q_self->statusBar();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        Qt::DockWidgetArea _q_arg0 = qscriptvalue_cast<Qt::DockWidgetArea>(context->argument(0));
        QTabWidget::TabPosition _q_result = _q_self->tabPosition(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QDockWidget* _q_arg0 = qscriptvalue_cast<QDockWidget*>(context->argument(0));
        QList<QDockWidget*> _q_result = _q_self->tabifiedDockWidgets(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 2) {
        QDockWidget* _q_arg0 = qscriptvalue_cast<QDockWidget*>(context->argument(0));
        QDockWidget* _q_arg1 = qscriptvalue_cast<QDockWidget*>(context->argument(1));
        _q_self->tabifyDockWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QToolBar* _q_arg0 = qscriptvalue_cast<QToolBar*>(context->argument(0));
        Qt::ToolBarArea _q_result = _q_self->toolBarArea(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QToolBar* _q_arg0 = qscriptvalue_cast<QToolBar*>(context->argument(0));
        bool _q_result = _q_self->toolBarBreak(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 31: {
    QString result = QString::fromLatin1("QMainWindow");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMainWindow_throw_ambiguity_error_helper(context,
        qtscript_QMainWindow_function_names[_id+1],
        qtscript_QMainWindow_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMainWindow_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMainWindow(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QMainWindow* _q_cpp_result = new QtScriptShell_QMainWindow();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMainWindow*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QMainWindow* _q_cpp_result = new QtScriptShell_QMainWindow(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMainWindow*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QtScriptShell_QMainWindow* _q_cpp_result = new QtScriptShell_QMainWindow(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMainWindow*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMainWindow_throw_ambiguity_error_helper(context,
        qtscript_QMainWindow_function_names[_id],
        qtscript_QMainWindow_function_signatures[_id]);
}

static QScriptValue qtscript_QMainWindow_toScriptValue(QScriptEngine *engine, QMainWindow* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QMainWindow_fromScriptValue(const QScriptValue &value, QMainWindow* &out)
{
    out = qobject_cast<QMainWindow*>(value.toQObject());
}

QScriptValue qtscript_create_QMainWindow_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMainWindow*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMainWindow*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 32; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMainWindow_prototype_call, qtscript_QMainWindow_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMainWindow_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QMainWindow*>(engine, qtscript_QMainWindow_toScriptValue, 
        qtscript_QMainWindow_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMainWindow_static_call, proto, qtscript_QMainWindow_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("DockOption"),
        qtscript_create_QMainWindow_DockOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("DockOptions"),
        qtscript_create_QMainWindow_DockOptions_class(engine));
    return ctor;
}
