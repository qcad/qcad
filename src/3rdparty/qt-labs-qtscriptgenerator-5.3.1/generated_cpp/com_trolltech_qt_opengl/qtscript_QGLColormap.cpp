#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qglcolormap.h>
#include <QVariant>
#include <qcolor.h>
#include <qglcolormap.h>

#include "qtscriptshell_QGLColormap.h"

static const char * const qtscript_QGLColormap_function_names[] = {
    "QGLColormap"
    // static
    // prototype
    , "entryColor"
    , "entryRgb"
    , "find"
    , "findNearest"
    , "isEmpty"
    , "setEntries"
    , "setEntry"
    , "size"
    , "toString"
};

static const char * const qtscript_QGLColormap_function_signatures[] = {
    "\nQGLColormap arg__1"
    // static
    // prototype
    , "int idx"
    , "int idx"
    , "unsigned int color"
    , "unsigned int color"
    , ""
    , "int count, unsigned int colors, int base"
    , "int idx, QColor color\nint idx, unsigned int color"
    , ""
""
};

static const int qtscript_QGLColormap_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 1
    , 1
    , 0
    , 3
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QGLColormap_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGLColormap::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGLColormap)
Q_DECLARE_METATYPE(QGLColormap*)
Q_DECLARE_METATYPE(QtScriptShell_QGLColormap)
Q_DECLARE_METATYPE(QtScriptShell_QGLColormap*)
Q_DECLARE_METATYPE(const unsigned int*)

//
// QGLColormap
//

static QScriptValue qtscript_QGLColormap_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QGLColormap* _q_self = qscriptvalue_cast<QGLColormap*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGLColormap.%0(): this object is not a QGLColormap")
            .arg(qtscript_QGLColormap_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QColor _q_result = _q_self->entryColor(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        unsigned int _q_result = _q_self->entryRgb(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        uint _q_arg0 = context->argument(0).toUInt32();
        int _q_result = _q_self->find(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        uint _q_arg0 = context->argument(0).toUInt32();
        int _q_result = _q_self->findNearest(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        const uint* _q_arg1 = qscriptvalue_cast<const uint*>(context->argument(1));
        _q_self->setEntries(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        const uint* _q_arg1 = qscriptvalue_cast<const uint*>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->setEntries(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isNumber()
            && (qMetaTypeId<QColor>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QColor _q_arg1 = qscriptvalue_cast<QColor>(context->argument(1));
            _q_self->setEntry(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            uint _q_arg1 = context->argument(1).toUInt32();
            _q_self->setEntry(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->size();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QGLColormap");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLColormap_throw_ambiguity_error_helper(context,
        qtscript_QGLColormap_function_names[_id+1],
        qtscript_QGLColormap_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGLColormap_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGLColormap(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGLColormap _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGLColormap)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QGLColormap _q_arg0 = qscriptvalue_cast<QGLColormap>(context->argument(0));
        QtScriptShell_QGLColormap _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGLColormap)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLColormap_throw_ambiguity_error_helper(context,
        qtscript_QGLColormap_function_names[_id],
        qtscript_QGLColormap_function_signatures[_id]);
}

QScriptValue qtscript_create_QGLColormap_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGLColormap*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGLColormap*)0));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLColormap_prototype_call, qtscript_QGLColormap_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGLColormap_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGLColormap>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QGLColormap*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGLColormap_static_call, proto, qtscript_QGLColormap_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
