#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsplitter.h>
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
#include <qsplitter.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QSplitterHandle.h"

static const char * const qtscript_QSplitterHandle_function_names[] = {
    "QSplitterHandle"
    // static
    // prototype
    , "opaqueResize"
    , "orientation"
    , "setOrientation"
    , "sizeHint"
    , "splitter"
    , "toString"
};

static const char * const qtscript_QSplitterHandle_function_signatures[] = {
    "Orientation o, QSplitter parent"
    // static
    // prototype
    , ""
    , ""
    , "Orientation o"
    , ""
    , ""
""
};

static const int qtscript_QSplitterHandle_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QSplitterHandle_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSplitterHandle::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSplitterHandle*)
Q_DECLARE_METATYPE(QtScriptShell_QSplitterHandle*)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QSplitter*)

//
// QSplitterHandle
//

static QScriptValue qtscript_QSplitterHandle_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSplitterHandle* _q_self = qscriptvalue_cast<QSplitterHandle*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSplitterHandle.%0(): this object is not a QSplitterHandle")
            .arg(qtscript_QSplitterHandle_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->opaqueResize();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        Qt::Orientation _q_result = _q_self->orientation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        _q_self->setOrientation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QSplitter* _q_result = _q_self->splitter();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QSplitterHandle");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSplitterHandle_throw_ambiguity_error_helper(context,
        qtscript_QSplitterHandle_function_names[_id+1],
        qtscript_QSplitterHandle_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSplitterHandle_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSplitterHandle(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        QSplitter* _q_arg1 = qscriptvalue_cast<QSplitter*>(context->argument(1));
        QtScriptShell_QSplitterHandle* _q_cpp_result = new QtScriptShell_QSplitterHandle(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSplitterHandle*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSplitterHandle_throw_ambiguity_error_helper(context,
        qtscript_QSplitterHandle_function_names[_id],
        qtscript_QSplitterHandle_function_signatures[_id]);
}

static QScriptValue qtscript_QSplitterHandle_toScriptValue(QScriptEngine *engine, QSplitterHandle* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSplitterHandle_fromScriptValue(const QScriptValue &value, QSplitterHandle* &out)
{
    out = qobject_cast<QSplitterHandle*>(value.toQObject());
}

QScriptValue qtscript_create_QSplitterHandle_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSplitterHandle*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSplitterHandle*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSplitterHandle_prototype_call, qtscript_QSplitterHandle_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSplitterHandle_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSplitterHandle*>(engine, qtscript_QSplitterHandle_toScriptValue, 
        qtscript_QSplitterHandle_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSplitterHandle_static_call, proto, qtscript_QSplitterHandle_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
