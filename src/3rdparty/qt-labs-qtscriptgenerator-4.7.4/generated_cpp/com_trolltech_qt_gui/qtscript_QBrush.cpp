#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qbrush.h>
#include <QPixmap>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qdatastream.h>
#include <qimage.h>
#include <qmatrix.h>
#include <qpixmap.h>
#include <qtransform.h>

static const char * const qtscript_QBrush_function_names[] = {
    "QBrush"
    // static
    // prototype
    , "color"
    , "gradient"
    , "isOpaque"
    , "matrix"
    , "equals"
    , "readFrom"
    , "setColor"
    , "setMatrix"
    , "setStyle"
    , "setTexture"
    , "setTextureImage"
    , "setTransform"
    , "style"
    , "texture"
    , "textureImage"
    , "transform"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QBrush_function_signatures[] = {
    "\nBrushStyle bs\nGlobalColor color, QPixmap pixmap\nQBrush brush\nQColor color, BrushStyle bs\nQColor color, QPixmap pixmap\nQGradient gradient\nQImage image\nQPixmap pixmap"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "QBrush b"
    , "QDataStream arg__1"
    , "GlobalColor color\nQColor color"
    , "QMatrix mat"
    , "BrushStyle arg__1"
    , "QPixmap pixmap"
    , "QImage image"
    , "QTransform arg__1"
    , ""
    , ""
    , ""
    , ""
    , "QDataStream arg__1"
""
};

static const int qtscript_QBrush_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QBrush_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QBrush::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QBrush*)
Q_DECLARE_METATYPE(QGradient*)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(Qt::GlobalColor)
Q_DECLARE_METATYPE(Qt::BrushStyle)

//
// QBrush
//

static QScriptValue qtscript_QBrush_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 17;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QBrush* _q_self = qscriptvalue_cast<QBrush*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QBrush.%0(): this object is not a QBrush")
            .arg(qtscript_QBrush_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->color();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QGradient* _q_result = const_cast<QGradient*>(_q_self->gradient());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isOpaque();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QMatrix _q_result = _q_self->matrix();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::GlobalColor>() == context->argument(0).toVariant().userType())) {
            Qt::GlobalColor _q_arg0 = qscriptvalue_cast<Qt::GlobalColor>(context->argument(0));
            _q_self->setColor(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QColor>() == context->argument(0).toVariant().userType())) {
            QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
            _q_self->setColor(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
        _q_self->setMatrix(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        Qt::BrushStyle _q_arg0 = qscriptvalue_cast<Qt::BrushStyle>(context->argument(0));
        _q_self->setStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        _q_self->setTexture(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
        _q_self->setTextureImage(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        _q_self->setTransform(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        Qt::BrushStyle _q_result = _q_self->style();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QPixmap _q_result = _q_self->texture();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->textureImage();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QTransform _q_result = _q_self->transform();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 17: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QBrush_throw_ambiguity_error_helper(context,
        qtscript_QBrush_function_names[_id+1],
        qtscript_QBrush_function_signatures[_id+1]);
}

static QScriptValue qtscript_QBrush_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QBrush(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QBrush _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Qt::BrushStyle>() == context->argument(0).toVariant().userType())) {
            Qt::BrushStyle _q_arg0 = qscriptvalue_cast<Qt::BrushStyle>(context->argument(0));
            QBrush _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QBrush>() == context->argument(0).toVariant().userType())) {
            QBrush _q_arg0 = qscriptvalue_cast<QBrush>(context->argument(0));
            QBrush _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QColor>() == context->argument(0).toVariant().userType())) {
            QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
            QBrush _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (qscriptvalue_cast<QGradient*>(context->argument(0))) {

        QGradient & _q_arg0 = *qscriptvalue_cast<QGradient*>(context->argument(0));
                    QBrush _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QImage>() == context->argument(0).toVariant().userType())) {
            QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
            QBrush _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QPixmap>() == context->argument(0).toVariant().userType())) {
            QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
            QBrush _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<Qt::GlobalColor>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())) {
            Qt::GlobalColor _q_arg0 = qscriptvalue_cast<Qt::GlobalColor>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            QBrush _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QColor>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::BrushStyle>() == context->argument(1).toVariant().userType())) {
            QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
            Qt::BrushStyle _q_arg1 = qscriptvalue_cast<Qt::BrushStyle>(context->argument(1));
            QBrush _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QColor>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())) {
            QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            QBrush _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QBrush_throw_ambiguity_error_helper(context,
        qtscript_QBrush_function_names[_id],
        qtscript_QBrush_function_signatures[_id]);
}

QScriptValue qtscript_create_QBrush_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QBrush*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QBrush*)0));
    for (int i = 0; i < 18; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QBrush_prototype_call, qtscript_QBrush_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QBrush_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QBrush>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QBrush*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QBrush_static_call, proto, qtscript_QBrush_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
