#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtoolbox.h>
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
#include <qtoolbox.h>
#include <qwidget.h>

#include "qtscriptshell_QToolBox.h"

static const char * const qtscript_QToolBox_function_names[] = {
    "QToolBox"
    // static
    // prototype
    , "addItem"
    , "currentWidget"
    , "indexOf"
    , "insertItem"
    , "isItemEnabled"
    , "itemIcon"
    , "itemText"
    , "itemToolTip"
    , "removeItem"
    , "setItemEnabled"
    , "setItemIcon"
    , "setItemText"
    , "setItemToolTip"
    , "widget"
    , "toString"
};

static const char * const qtscript_QToolBox_function_signatures[] = {
    "QWidget parent, WindowFlags f"
    // static
    // prototype
    , "QWidget widget, QIcon icon, String text\nQWidget widget, String text"
    , ""
    , "QWidget widget"
    , "int index, QWidget widget, QIcon icon, String text\nint index, QWidget widget, String text"
    , "int index"
    , "int index"
    , "int index"
    , "int index"
    , "int index"
    , "int index, bool enabled"
    , "int index, QIcon icon"
    , "int index, String text"
    , "int index, String toolTip"
    , "int index"
""
};

static const int qtscript_QToolBox_function_lengths[] = {
    2
    // static
    // prototype
    , 3
    , 0
    , 1
    , 4
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 2
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QToolBox_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QToolBox::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QToolBox*)
Q_DECLARE_METATYPE(QtScriptShell_QToolBox*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)
Q_DECLARE_METATYPE(QFrame*)

//
// QToolBox
//

static QScriptValue qtscript_QToolBox_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QToolBox* _q_self = qscriptvalue_cast<QToolBox*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QToolBox.%0(): this object is not a QToolBox")
            .arg(qtscript_QToolBox_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        int _q_result = _q_self->addItem(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QIcon _q_arg1 = qscriptvalue_cast<QIcon>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        int _q_result = _q_self->addItem(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->currentWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_result = _q_self->indexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        int _q_result = _q_self->insertItem(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QIcon _q_arg2 = qscriptvalue_cast<QIcon>(context->argument(2));
        QString _q_arg3 = context->argument(3).toString();
        int _q_result = _q_self->insertItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isItemEnabled(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QIcon _q_result = _q_self->itemIcon(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->itemText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->itemToolTip(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->removeItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setItemEnabled(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QIcon _q_arg1 = qscriptvalue_cast<QIcon>(context->argument(1));
        _q_self->setItemIcon(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setItemText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setItemToolTip(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_result = _q_self->widget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14: {
    QString result = QString::fromLatin1("QToolBox");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QToolBox_throw_ambiguity_error_helper(context,
        qtscript_QToolBox_function_names[_id+1],
        qtscript_QToolBox_function_signatures[_id+1]);
}

static QScriptValue qtscript_QToolBox_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QToolBox(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QToolBox* _q_cpp_result = new QtScriptShell_QToolBox();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QToolBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QToolBox* _q_cpp_result = new QtScriptShell_QToolBox(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QToolBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QtScriptShell_QToolBox* _q_cpp_result = new QtScriptShell_QToolBox(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QToolBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QToolBox_throw_ambiguity_error_helper(context,
        qtscript_QToolBox_function_names[_id],
        qtscript_QToolBox_function_signatures[_id]);
}

static QScriptValue qtscript_QToolBox_toScriptValue(QScriptEngine *engine, QToolBox* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QToolBox_fromScriptValue(const QScriptValue &value, QToolBox* &out)
{
    out = qobject_cast<QToolBox*>(value.toQObject());
}

QScriptValue qtscript_create_QToolBox_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QToolBox*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QToolBox*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QFrame*>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QToolBox_prototype_call, qtscript_QToolBox_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QToolBox_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QToolBox*>(engine, qtscript_QToolBox_toScriptValue, 
        qtscript_QToolBox_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QToolBox_static_call, proto, qtscript_QToolBox_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
