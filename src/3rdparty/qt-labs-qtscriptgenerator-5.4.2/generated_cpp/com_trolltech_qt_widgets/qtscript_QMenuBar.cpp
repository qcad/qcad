#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qmenubar.h>
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
#include <qmenubar.h>
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

#include "qtscriptshell_QMenuBar.h"

static const char * const qtscript_QMenuBar_function_names[] = {
    "QMenuBar"
    // static
    // prototype
    , "actionAt"
    , "actionGeometry"
    , "activeAction"
    , "addAction"
    , "addMenu"
    , "addSeparator"
    , "clear"
    , "cornerWidget"
    , "insertMenu"
    , "insertSeparator"
    , "minimumSizeHint"
    , "setActiveAction"
    , "setCornerWidget"
    , "sizeHint"
    , "toString"
};

static const char * const qtscript_QMenuBar_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "QPoint arg__1"
    , "QAction arg__1"
    , ""
    , "String text"
    , "QMenu menu\nQIcon icon, String title\nString title"
    , ""
    , ""
    , "Corner corner"
    , "QAction before, QMenu menu"
    , "QAction before"
    , ""
    , "QAction action"
    , "QWidget w, Corner corner"
    , ""
""
};

static const int qtscript_QMenuBar_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 0
    , 1
    , 2
    , 0
    , 0
    , 1
    , 2
    , 1
    , 0
    , 1
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QMenuBar_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMenuBar::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMenuBar*)
Q_DECLARE_METATYPE(QtScriptShell_QMenuBar*)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(Qt::Corner)
Q_DECLARE_METATYPE(QWidget*)

//
// QMenuBar
//

static QScriptValue qtscript_QMenuBar_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 14;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QMenuBar* _q_self = qscriptvalue_cast<QMenuBar*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMenuBar.%0(): this object is not a QMenuBar")
            .arg(qtscript_QMenuBar_function_names[_id+1]));
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
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->addSeparator();
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
        QWidget* _q_result = _q_self->cornerWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        Qt::Corner _q_arg0 = qscriptvalue_cast<Qt::Corner>(context->argument(0));
        QWidget* _q_result = _q_self->cornerWidget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        QMenu* _q_arg1 = qscriptvalue_cast<QMenu*>(context->argument(1));
        QAction* _q_result = _q_self->insertMenu(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        QAction* _q_result = _q_self->insertSeparator(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QAction* _q_arg0 = qscriptvalue_cast<QAction*>(context->argument(0));
        _q_self->setActiveAction(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setCornerWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        Qt::Corner _q_arg1 = qscriptvalue_cast<Qt::Corner>(context->argument(1));
        _q_self->setCornerWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14: {
    QString result = QString::fromLatin1("QMenuBar");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMenuBar_throw_ambiguity_error_helper(context,
        qtscript_QMenuBar_function_names[_id+1],
        qtscript_QMenuBar_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMenuBar_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMenuBar(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QMenuBar* _q_cpp_result = new QtScriptShell_QMenuBar();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMenuBar*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QMenuBar* _q_cpp_result = new QtScriptShell_QMenuBar(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QMenuBar*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMenuBar_throw_ambiguity_error_helper(context,
        qtscript_QMenuBar_function_names[_id],
        qtscript_QMenuBar_function_signatures[_id]);
}

static QScriptValue qtscript_QMenuBar_toScriptValue(QScriptEngine *engine, QMenuBar* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QMenuBar_fromScriptValue(const QScriptValue &value, QMenuBar* &out)
{
    out = qobject_cast<QMenuBar*>(value.toQObject());
}

QScriptValue qtscript_create_QMenuBar_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMenuBar*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMenuBar*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMenuBar_prototype_call, qtscript_QMenuBar_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMenuBar_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QMenuBar*>(engine, qtscript_QMenuBar_toScriptValue, 
        qtscript_QMenuBar_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMenuBar_static_call, proto, qtscript_QMenuBar_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
