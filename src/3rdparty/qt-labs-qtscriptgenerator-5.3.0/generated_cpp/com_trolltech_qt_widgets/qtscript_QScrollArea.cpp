#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qscrollarea.h>
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
#include <qscrollarea.h>
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QScrollArea.h"

static const char * const qtscript_QScrollArea_function_names[] = {
    "QScrollArea"
    // static
    // prototype
    , "ensureVisible"
    , "ensureWidgetVisible"
    , "setWidget"
    , "takeWidget"
    , "widget"
    , "toString"
};

static const char * const qtscript_QScrollArea_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "int x, int y, int xmargin, int ymargin"
    , "QWidget childWidget, int xmargin, int ymargin"
    , "QWidget widget"
    , ""
    , ""
""
};

static const int qtscript_QScrollArea_function_lengths[] = {
    1
    // static
    // prototype
    , 4
    , 3
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QScrollArea_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QScrollArea::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QScrollArea*)
Q_DECLARE_METATYPE(QtScriptShell_QScrollArea*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QAbstractScrollArea*)

//
// QScrollArea
//

static QScriptValue qtscript_QScrollArea_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QScrollArea* _q_self = qscriptvalue_cast<QScrollArea*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QScrollArea.%0(): this object is not a QScrollArea")
            .arg(qtscript_QScrollArea_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->ensureVisible(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->ensureVisible(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->ensureVisible(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->ensureWidgetVisible(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->ensureWidgetVisible(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->ensureWidgetVisible(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->takeWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->widget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QScrollArea");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QScrollArea_throw_ambiguity_error_helper(context,
        qtscript_QScrollArea_function_names[_id+1],
        qtscript_QScrollArea_function_signatures[_id+1]);
}

static QScriptValue qtscript_QScrollArea_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QScrollArea(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QScrollArea* _q_cpp_result = new QtScriptShell_QScrollArea();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QScrollArea*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QScrollArea* _q_cpp_result = new QtScriptShell_QScrollArea(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QScrollArea*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QScrollArea_throw_ambiguity_error_helper(context,
        qtscript_QScrollArea_function_names[_id],
        qtscript_QScrollArea_function_signatures[_id]);
}

static QScriptValue qtscript_QScrollArea_toScriptValue(QScriptEngine *engine, QScrollArea* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QScrollArea_fromScriptValue(const QScriptValue &value, QScrollArea* &out)
{
    out = qobject_cast<QScrollArea*>(value.toQObject());
}

QScriptValue qtscript_create_QScrollArea_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QScrollArea*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QScrollArea*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractScrollArea*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QScrollArea_prototype_call, qtscript_QScrollArea_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QScrollArea_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QScrollArea*>(engine, qtscript_QScrollArea_toScriptValue, 
        qtscript_QScrollArea_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QScrollArea_static_call, proto, qtscript_QScrollArea_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
