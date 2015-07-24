#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qevent.h>
#include <QVariant>
#include <qcoreevent.h>

#include "qtscriptshell_QKeyEvent.h"

static const char * const qtscript_QKeyEvent_function_names[] = {
    "QKeyEvent"
    // static
    // prototype
    , "count"
    , "isAutoRepeat"
    , "key"
    , "matches"
    , "nativeModifiers"
    , "nativeScanCode"
    , "nativeVirtualKey"
    , "text"
    , "toString"
};

static const char * const qtscript_QKeyEvent_function_signatures[] = {
    "Type type, int key, KeyboardModifiers modifiers, String text, bool autorep, ushort count\nType type, int key, KeyboardModifiers modifiers, unsigned int nativeScanCode, unsigned int nativeVirtualKey, unsigned int nativeModifiers, String text, bool autorep, ushort count"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "StandardKey key"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QKeyEvent_function_lengths[] = {
    9
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QKeyEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QKeyEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QKeyEvent*)
Q_DECLARE_METATYPE(QtScriptShell_QKeyEvent*)
Q_DECLARE_METATYPE(QKeySequence::StandardKey)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QInputEvent*)

//
// QKeyEvent
//

static QScriptValue qtscript_QKeyEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 8;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QKeyEvent* _q_self = qscriptvalue_cast<QKeyEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QKeyEvent.%0(): this object is not a QKeyEvent")
            .arg(qtscript_QKeyEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isAutoRepeat();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->key();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QKeySequence::StandardKey _q_arg0 = qscriptvalue_cast<QKeySequence::StandardKey>(context->argument(0));
        bool _q_result = _q_self->matches(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        unsigned int _q_result = _q_self->nativeModifiers();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        unsigned int _q_result = _q_self->nativeScanCode();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        unsigned int _q_result = _q_self->nativeVirtualKey();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QKeyEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QKeyEvent_throw_ambiguity_error_helper(context,
        qtscript_QKeyEvent_function_names[_id+1],
        qtscript_QKeyEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QKeyEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QKeyEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 3) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QFlags<Qt::KeyboardModifier> _q_arg2 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(2));
        QtScriptShell_QKeyEvent* _q_cpp_result = new QtScriptShell_QKeyEvent(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QKeyEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 4) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QFlags<Qt::KeyboardModifier> _q_arg2 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(2));
        QString _q_arg3 = context->argument(3).toString();
        QtScriptShell_QKeyEvent* _q_cpp_result = new QtScriptShell_QKeyEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QKeyEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 5) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QFlags<Qt::KeyboardModifier> _q_arg2 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(2));
        QString _q_arg3 = context->argument(3).toString();
        bool _q_arg4 = context->argument(4).toBoolean();
        QtScriptShell_QKeyEvent* _q_cpp_result = new QtScriptShell_QKeyEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QKeyEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 6) {
        if ((qMetaTypeId<QEvent::Type>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && (qMetaTypeId<QFlags<Qt::KeyboardModifier> >() == context->argument(2).toVariant().userType())
            && context->argument(3).isString()
            && context->argument(4).isBoolean()
            && (qMetaTypeId<ushort>() == context->argument(5).toVariant().userType())) {
            QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QFlags<Qt::KeyboardModifier> _q_arg2 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(2));
            QString _q_arg3 = context->argument(3).toString();
            bool _q_arg4 = context->argument(4).toBoolean();
            ushort _q_arg5 = qscriptvalue_cast<ushort>(context->argument(5));
            QtScriptShell_QKeyEvent* _q_cpp_result = new QtScriptShell_QKeyEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QKeyEvent*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QEvent::Type>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && (qMetaTypeId<QFlags<Qt::KeyboardModifier> >() == context->argument(2).toVariant().userType())
            && context->argument(3).isNumber()
            && context->argument(4).isNumber()
            && context->argument(5).isNumber()) {
            QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QFlags<Qt::KeyboardModifier> _q_arg2 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(2));
            uint _q_arg3 = context->argument(3).toUInt32();
            uint _q_arg4 = context->argument(4).toUInt32();
            uint _q_arg5 = context->argument(5).toUInt32();
            QtScriptShell_QKeyEvent* _q_cpp_result = new QtScriptShell_QKeyEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QKeyEvent*)_q_cpp_result));
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 7) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QFlags<Qt::KeyboardModifier> _q_arg2 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(2));
        uint _q_arg3 = context->argument(3).toUInt32();
        uint _q_arg4 = context->argument(4).toUInt32();
        uint _q_arg5 = context->argument(5).toUInt32();
        QString _q_arg6 = context->argument(6).toString();
        QtScriptShell_QKeyEvent* _q_cpp_result = new QtScriptShell_QKeyEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QKeyEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 8) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QFlags<Qt::KeyboardModifier> _q_arg2 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(2));
        uint _q_arg3 = context->argument(3).toUInt32();
        uint _q_arg4 = context->argument(4).toUInt32();
        uint _q_arg5 = context->argument(5).toUInt32();
        QString _q_arg6 = context->argument(6).toString();
        bool _q_arg7 = context->argument(7).toBoolean();
        QtScriptShell_QKeyEvent* _q_cpp_result = new QtScriptShell_QKeyEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QKeyEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 9) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QFlags<Qt::KeyboardModifier> _q_arg2 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(2));
        uint _q_arg3 = context->argument(3).toUInt32();
        uint _q_arg4 = context->argument(4).toUInt32();
        uint _q_arg5 = context->argument(5).toUInt32();
        QString _q_arg6 = context->argument(6).toString();
        bool _q_arg7 = context->argument(7).toBoolean();
        ushort _q_arg8 = qscriptvalue_cast<ushort>(context->argument(8));
        QtScriptShell_QKeyEvent* _q_cpp_result = new QtScriptShell_QKeyEvent(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5, _q_arg6, _q_arg7, _q_arg8);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QKeyEvent*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QKeyEvent_throw_ambiguity_error_helper(context,
        qtscript_QKeyEvent_function_names[_id],
        qtscript_QKeyEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QKeyEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QKeyEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QKeyEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QInputEvent*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QKeyEvent_prototype_call, qtscript_QKeyEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QKeyEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QKeyEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QKeyEvent_static_call, proto, qtscript_QKeyEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
