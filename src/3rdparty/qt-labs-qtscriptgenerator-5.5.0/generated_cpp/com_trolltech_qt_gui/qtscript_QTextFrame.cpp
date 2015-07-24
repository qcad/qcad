#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtextobject.h>
#include <QTextCursor>
#include <QTextFrame>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qtextcursor.h>
#include <qtextdocument.h>
#include <qtextformat.h>
#include <qtextobject.h>

#include "qtscriptshell_QTextFrame.h"

static const char * const qtscript_QTextFrame_function_names[] = {
    "QTextFrame"
    // static
    // prototype
    , "begin"
    , "childFrames"
    , "end"
    , "firstCursorPosition"
    , "firstPosition"
    , "frameFormat"
    , "lastCursorPosition"
    , "lastPosition"
    , "parentFrame"
    , "setFrameFormat"
    , "toString"
};

static const char * const qtscript_QTextFrame_function_signatures[] = {
    "QTextDocument doc"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QTextFrameFormat format"
""
};

static const int qtscript_QTextFrame_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QTextFrame_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextFrame::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextFrame*)
Q_DECLARE_METATYPE(QtScriptShell_QTextFrame*)
Q_DECLARE_METATYPE(QTextFrame::iterator)
Q_DECLARE_METATYPE(QList<QTextFrame* >)
Q_DECLARE_METATYPE(QTextCursor)
Q_DECLARE_METATYPE(QTextFrameFormat)
Q_DECLARE_METATYPE(QTextDocument*)
Q_DECLARE_METATYPE(QTextObject*)

//
// QTextFrame
//

static QScriptValue qtscript_QTextFrame_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 10;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextFrame* _q_self = qscriptvalue_cast<QTextFrame*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextFrame.%0(): this object is not a QTextFrame")
            .arg(qtscript_QTextFrame_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QTextFrame::iterator _q_result = _q_self->begin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QList<QTextFrame* > _q_result = _q_self->childFrames();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QTextFrame::iterator _q_result = _q_self->end();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QTextCursor _q_result = _q_self->firstCursorPosition();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->firstPosition();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QTextFrameFormat _q_result = _q_self->frameFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QTextCursor _q_result = _q_self->lastCursorPosition();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->lastPosition();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QTextFrame* _q_result = _q_self->parentFrame();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QTextFrameFormat _q_arg0 = qscriptvalue_cast<QTextFrameFormat>(context->argument(0));
        _q_self->setFrameFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10: {
    QString result = QString::fromLatin1("QTextFrame");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextFrame_throw_ambiguity_error_helper(context,
        qtscript_QTextFrame_function_names[_id+1],
        qtscript_QTextFrame_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextFrame_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextFrame(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QTextDocument* _q_arg0 = qscriptvalue_cast<QTextDocument*>(context->argument(0));
        QtScriptShell_QTextFrame* _q_cpp_result = new QtScriptShell_QTextFrame(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTextFrame*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextFrame_throw_ambiguity_error_helper(context,
        qtscript_QTextFrame_function_names[_id],
        qtscript_QTextFrame_function_signatures[_id]);
}

static QScriptValue qtscript_QTextFrame_toScriptValue(QScriptEngine *engine, QTextFrame* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTextFrame_fromScriptValue(const QScriptValue &value, QTextFrame* &out)
{
    out = qobject_cast<QTextFrame*>(value.toQObject());
}

QScriptValue qtscript_create_QTextFrame_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextFrame*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextFrame*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTextObject*>()));
    for (int i = 0; i < 11; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextFrame_prototype_call, qtscript_QTextFrame_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextFrame_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTextFrame*>(engine, qtscript_QTextFrame_toScriptValue, 
        qtscript_QTextFrame_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextFrame_static_call, proto, qtscript_QTextFrame_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
