#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qcolumnview.h>
#include <QVariant>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcolumnview.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qinputcontext.h>
#include <qitemselectionmodel.h>
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
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QColumnView.h"

static const char * const qtscript_QColumnView_function_names[] = {
    "QColumnView"
    // static
    // prototype
    , "columnWidths"
    , "previewWidget"
    , "setColumnWidths"
    , "setPreviewWidget"
    , "toString"
};

static const char * const qtscript_QColumnView_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
    , ""
    , "List list"
    , "QWidget widget"
""
};

static const int qtscript_QColumnView_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QColumnView_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QColumnView::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QColumnView*)
Q_DECLARE_METATYPE(QtScriptShell_QColumnView*)
Q_DECLARE_METATYPE(QList<int>)
Q_DECLARE_METATYPE(QAbstractItemView*)

//
// QColumnView
//

static QScriptValue qtscript_QColumnView_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QColumnView* _q_self = qscriptvalue_cast<QColumnView*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QColumnView.%0(): this object is not a QColumnView")
            .arg(qtscript_QColumnView_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<int> _q_result = _q_self->columnWidths();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->previewWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QList<int> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setColumnWidths(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setPreviewWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QColumnView");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QColumnView_throw_ambiguity_error_helper(context,
        qtscript_QColumnView_function_names[_id+1],
        qtscript_QColumnView_function_signatures[_id+1]);
}

static QScriptValue qtscript_QColumnView_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QColumnView(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QColumnView* _q_cpp_result = new QtScriptShell_QColumnView();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QColumnView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QColumnView* _q_cpp_result = new QtScriptShell_QColumnView(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QColumnView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QColumnView_throw_ambiguity_error_helper(context,
        qtscript_QColumnView_function_names[_id],
        qtscript_QColumnView_function_signatures[_id]);
}

static QScriptValue qtscript_QColumnView_toScriptValue(QScriptEngine *engine, QColumnView* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QColumnView_fromScriptValue(const QScriptValue &value, QColumnView* &out)
{
    out = qobject_cast<QColumnView*>(value.toQObject());
}

QScriptValue qtscript_create_QColumnView_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QColumnView*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QColumnView*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractItemView*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QColumnView_prototype_call, qtscript_QColumnView_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QColumnView_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QColumnView*>(engine, qtscript_QColumnView_toScriptValue, 
        qtscript_QColumnView_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QColumnView_static_call, proto, qtscript_QColumnView_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
