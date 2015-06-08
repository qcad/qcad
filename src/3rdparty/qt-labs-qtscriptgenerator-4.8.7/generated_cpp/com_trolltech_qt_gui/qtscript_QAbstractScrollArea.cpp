#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractscrollarea.h>
#include <QVariant>
#include <qabstractscrollarea.h>
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
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QAbstractScrollArea.h"

static const char * const qtscript_QAbstractScrollArea_function_names[] = {
    "QAbstractScrollArea"
    // static
    // prototype
    , "addScrollBarWidget"
    , "cornerWidget"
    , "horizontalScrollBar"
    , "maximumViewportSize"
    , "minimumSizeHint"
    , "scrollBarWidgets"
    , "setCornerWidget"
    , "setHorizontalScrollBar"
    , "setVerticalScrollBar"
    , "setViewport"
    , "verticalScrollBar"
    , "viewport"
    , "toString"
};

static const char * const qtscript_QAbstractScrollArea_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "QWidget widget, Alignment alignment"
    , ""
    , ""
    , ""
    , ""
    , "Alignment alignment"
    , "QWidget widget"
    , "QScrollBar scrollbar"
    , "QScrollBar scrollbar"
    , "QWidget widget"
    , ""
    , ""
""
};

static const int qtscript_QAbstractScrollArea_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QAbstractScrollArea_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractScrollArea::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractScrollArea*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractScrollArea*)
Q_DECLARE_METATYPE(QFlags<Qt::AlignmentFlag>)
Q_DECLARE_METATYPE(QScrollBar*)
Q_DECLARE_METATYPE(QList<QWidget*>)
Q_DECLARE_METATYPE(QFrame*)

//
// QAbstractScrollArea
//

static QScriptValue qtscript_QAbstractScrollArea_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 12;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractScrollArea* _q_self = qscriptvalue_cast<QAbstractScrollArea*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractScrollArea.%0(): this object is not a QAbstractScrollArea")
            .arg(qtscript_QAbstractScrollArea_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::AlignmentFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(1));
        _q_self->addScrollBarWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->cornerWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QScrollBar* _q_result = _q_self->horizontalScrollBar();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->maximumViewportSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QFlags<Qt::AlignmentFlag> _q_arg0 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(0));
        QList<QWidget*> _q_result = _q_self->scrollBarWidgets(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setCornerWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QScrollBar* _q_arg0 = qscriptvalue_cast<QScrollBar*>(context->argument(0));
        _q_self->setHorizontalScrollBar(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QScrollBar* _q_arg0 = qscriptvalue_cast<QScrollBar*>(context->argument(0));
        _q_self->setVerticalScrollBar(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setViewport(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QScrollBar* _q_result = _q_self->verticalScrollBar();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->viewport();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12: {
    QString result = QString::fromLatin1("QAbstractScrollArea");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractScrollArea_throw_ambiguity_error_helper(context,
        qtscript_QAbstractScrollArea_function_names[_id+1],
        qtscript_QAbstractScrollArea_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractScrollArea_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractScrollArea(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractScrollArea* _q_cpp_result = new QtScriptShell_QAbstractScrollArea();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractScrollArea*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QAbstractScrollArea* _q_cpp_result = new QtScriptShell_QAbstractScrollArea(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractScrollArea*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractScrollArea_throw_ambiguity_error_helper(context,
        qtscript_QAbstractScrollArea_function_names[_id],
        qtscript_QAbstractScrollArea_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractScrollArea_toScriptValue(QScriptEngine *engine, QAbstractScrollArea* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractScrollArea_fromScriptValue(const QScriptValue &value, QAbstractScrollArea* &out)
{
    out = qobject_cast<QAbstractScrollArea*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractScrollArea_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractScrollArea*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractScrollArea*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QFrame*>()));
    for (int i = 0; i < 13; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractScrollArea_prototype_call, qtscript_QAbstractScrollArea_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractScrollArea_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractScrollArea*>(engine, qtscript_QAbstractScrollArea_toScriptValue, 
        qtscript_QAbstractScrollArea_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractScrollArea_static_call, proto, qtscript_QAbstractScrollArea_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
