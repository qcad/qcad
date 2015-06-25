#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qmenu.h>
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
#include <qmenu.h>
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
#include <qwidget.h>

#include "qtscriptshell_QMenu.h"

static const char * const qtscript_QMenu_function_names[] = {
    "QMenu"
    // static
    , "exec"
    // prototype
    , "actionAt"
    , "actionGeometry"
    , "activeAction"
    , "addAction"
    , "addMenu"
    , "addSection"
    , "addSeparator"
    , "clear"
    , "defaultAction"
    , "exec"
    , "hideTearOffMenu"
    , "insertMenu"
    , "insertSection"
    , "insertSeparator"
    , "isEmpty"
    , "isTearOffMenuVisible"
    , "menuAction"
    , "popup"
    , "setActiveAction"
    , "setDefaultAction"
    , "sizeHint"
    , "toString"
};

static const char * const qtscript_QMenu_function_signatures[] = {
    "QWidget parent\nString title, QWidget parent"
    // static
    , "List actions, QPoint pos, QAction at, QWidget parent"
    // prototype
    , "QPoint arg__1"
    , "QAction arg__1"
    , ""
    , "QIcon icon, String text\nString text"
    , "QMenu menu\nQIcon icon, String title\nString title"
    , "QIcon icon, String text\nString text"
    , ""
    , ""
    , ""
    , "\nQPoint pos, QAction at"
    , ""
    , "QAction before, QMenu menu"
    , "QAction before, QIcon icon, String text\nQAction before, String text"
    , "QAction before"
    , ""
    , ""
    , ""
    , "QPoint pos, QAction at"
    , "QAction act"
    , "QAction arg__1"
    , ""
""
};

static const int qtscript_QMenu_function_lengths[] = {
    2
    // static
    , 4
    // prototype
    , 1
    , 1
    , 0
    , 2
    , 2
    , 2
    , 0
    , 0
    , 0
    , 2
    , 0
    , 2
    , 3
    , 1
    , 0
    , 0
    , 0
    , 2
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QMenu_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMenu::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(QtScriptShell_QMenu*)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QList<QAction* >)
Q_DECLARE_METATYPE(QWidget*)

//
// QMenu
//

static QScriptValue qtscript_QMenu_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QMenu* _q_self = qscriptvalue_cast<QMenu*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMenu.%0(): this object is not a QMenu")
            .arg(qtscript_QMenu_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QAction* _q_result = _q_self->actionAt(_q_arg0);
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
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->activeAction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
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

    case 4:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QMenu*>(context->argument(0))) {
            QMenu* _q_arg0 = qscriptvalue_cast<QMenu*>(context->argument(0));
            QAction* _q_result = _q_self->addMenu(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QMenu* _q_result = _q_self->addMenu(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QMenu* _q_result = _q_self->addMenu(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QAction* _q_result = _q_self->addSection(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QAction* _q_result = _q_self->addSection(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->addSeparator();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->defaultAction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->exec();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QAction* _q_result = _q_self->exec(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QAction* _q_arg1 = qscriptvalue_cast<QAction*>(context->argument(1));
        QAction* _q_result = _q_self->exec(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        _q_self->hideTearOffMenu();
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        QMenu* _q_arg1 = qscriptvalue_cast<QMenu*>(context->argument(1));
        QAction* _q_result = _q_self->insertMenu(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QAction* _q_result = _q_self->insertSection(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        QIcon _q_arg1 = qscriptvalue_cast<QIcon>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        QAction* _q_result = _q_self->insertSection(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        QAction* _q_result = _q_self->insertSeparator(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isTearOffMenuVisible();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->menuAction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->popup(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QAction* _q_arg1 = qscriptvalue_cast<QAction*>(context->argument(1));
        _q_self->popup(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        _q_self->setActiveAction(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        _q_self->setDefaultAction(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21: {
    QString result = QString::fromLatin1("QMenu");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMenu_throw_ambiguity_error_helper(context,
        qtscript_QMenu_function_names[_id+2],
        qtscript_QMenu_function_signatures[_id+2]);
}

static QScriptValue qtscript_QMenu_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMenu(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QMenu* _q_cpp_result = new QtScriptShell_QMenu();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMenu*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QMenu* _q_cpp_result = new QtScriptShell_QMenu(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMenu*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QMenu* _q_cpp_result = new QtScriptShell_QMenu(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMenu*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QMenu* _q_cpp_result = new QtScriptShell_QMenu(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMenu*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QList<QAction*> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        QAction* _q_result = QMenu::exec(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QList<QAction*> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        QAction* _q_arg2 = qscriptvalue_cast<QAction*>(context->argument(2));
        QAction* _q_result = QMenu::exec(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QList<QAction*> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
        QAction* _q_arg2 = qscriptvalue_cast<QAction*>(context->argument(2));
        QWidget* _q_arg3 = qscriptvalue_cast<QWidget*>(context->argument(3));
        QAction* _q_result = QMenu::exec(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMenu_throw_ambiguity_error_helper(context,
        qtscript_QMenu_function_names[_id],
        qtscript_QMenu_function_signatures[_id]);
}

static QScriptValue qtscript_QMenu_toScriptValue(QScriptEngine *engine, QMenu* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QMenu_fromScriptValue(const QScriptValue &value, QMenu* &out)
{
    out = qobject_cast<QMenu*>(value.toQObject());
}

QScriptValue qtscript_create_QMenu_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMenu*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMenu*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 22; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMenu_prototype_call, qtscript_QMenu_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMenu_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QMenu*>(engine, qtscript_QMenu_toScriptValue, 
        qtscript_QMenu_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMenu_static_call, proto, qtscript_QMenu_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMenu_static_call,
            qtscript_QMenu_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QMenu_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
