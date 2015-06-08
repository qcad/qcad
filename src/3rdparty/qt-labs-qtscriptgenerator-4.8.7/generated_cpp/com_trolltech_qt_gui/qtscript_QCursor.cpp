#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qcursor.h>
#include <QPixmap>
#include <QVariant>
#include <qbitmap.h>
#include <qcursor.h>
#include <qdatastream.h>
#include <qpixmap.h>
#include <qpoint.h>

static const char * const qtscript_QCursor_function_names[] = {
    "QCursor"
    // static
    , "pos"
    , "setPos"
    // prototype
    , "bitmap"
    , "hotSpot"
    , "mask"
    , "pixmap"
    , "readFrom"
    , "setShape"
    , "shape"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QCursor_function_signatures[] = {
    "\nCursorShape shape\nQBitmap bitmap, QBitmap mask, int hotX, int hotY\nQCursor cursor\nQPixmap pixmap, int hotX, int hotY"
    // static
    , ""
    , "QPoint p\nint x, int y"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "QDataStream inS"
    , "CursorShape newShape"
    , ""
    , "QDataStream outS"
""
};

static const int qtscript_QCursor_function_lengths[] = {
    4
    // static
    , 0
    , 2
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QCursor_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QCursor::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QCursor*)
Q_DECLARE_METATYPE(QBitmap*)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(Qt::CursorShape)

//
// QCursor
//

static QScriptValue qtscript_QCursor_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QCursor* _q_self = qscriptvalue_cast<QCursor*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QCursor.%0(): this object is not a QCursor")
            .arg(qtscript_QCursor_function_names[_id+3]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QBitmap* _q_result = const_cast<QBitmap*>(_q_self->bitmap());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->hotSpot();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QBitmap* _q_result = const_cast<QBitmap*>(_q_self->mask());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QPixmap _q_result = _q_self->pixmap();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        Qt::CursorShape _q_arg0 = qscriptvalue_cast<Qt::CursorShape>(context->argument(0));
        _q_self->setShape(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        Qt::CursorShape _q_result = _q_self->shape();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QCursor");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QCursor_throw_ambiguity_error_helper(context,
        qtscript_QCursor_function_names[_id+3],
        qtscript_QCursor_function_signatures[_id+3]);
}

static QScriptValue qtscript_QCursor_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QCursor(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QCursor _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::CursorShape>() == context->argument(0).toVariant().userType())) {
            Qt::CursorShape _q_arg0 = qscriptvalue_cast<Qt::CursorShape>(context->argument(0));
            QCursor _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QCursor>() == context->argument(0).toVariant().userType())) {
            QCursor _q_arg0 = qscriptvalue_cast<QCursor>(context->argument(0));
            QCursor _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QPixmap>() == context->argument(0).toVariant().userType())) {
            QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
            QCursor _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QBitmap>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QBitmap>() == context->argument(1).toVariant().userType())) {
            QBitmap _q_arg0 = qscriptvalue_cast<QBitmap>(context->argument(0));
            QBitmap _q_arg1 = qscriptvalue_cast<QBitmap>(context->argument(1));
            QCursor _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QPixmap>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            QCursor _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QBitmap>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QBitmap>() == context->argument(1).toVariant().userType())
            && context->argument(2).isNumber()) {
            QBitmap _q_arg0 = qscriptvalue_cast<QBitmap>(context->argument(0));
            QBitmap _q_arg1 = qscriptvalue_cast<QBitmap>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            QCursor _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QPixmap>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            QCursor _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 4) {
        QBitmap _q_arg0 = qscriptvalue_cast<QBitmap>(context->argument(0));
        QBitmap _q_arg1 = qscriptvalue_cast<QBitmap>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QCursor _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPoint _q_result = QCursor::pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QCursor::setPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QCursor::setPos(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QCursor_throw_ambiguity_error_helper(context,
        qtscript_QCursor_function_names[_id],
        qtscript_QCursor_function_signatures[_id]);
}

QScriptValue qtscript_create_QCursor_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QCursor*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QCursor*)0));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QCursor_prototype_call, qtscript_QCursor_function_lengths[i+3]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QCursor_function_names[i+3]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QCursor>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QCursor*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QCursor_static_call, proto, qtscript_QCursor_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QCursor_static_call,
            qtscript_QCursor_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QCursor_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
