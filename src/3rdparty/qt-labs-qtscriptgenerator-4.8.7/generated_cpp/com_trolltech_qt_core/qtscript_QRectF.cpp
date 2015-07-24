#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qrect.h>
#include <QVariant>
#include <qdatastream.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>

static const char * const qtscript_QRectF_function_names[] = {
    "QRectF"
    // static
    // prototype
    , "adjust"
    , "adjusted"
    , "bottom"
    , "bottomLeft"
    , "bottomRight"
    , "center"
    , "contains"
    , "height"
    , "intersected"
    , "intersects"
    , "isEmpty"
    , "isNull"
    , "isValid"
    , "left"
    , "moveBottom"
    , "moveBottomLeft"
    , "moveBottomRight"
    , "moveCenter"
    , "moveLeft"
    , "moveRight"
    , "moveTo"
    , "moveTop"
    , "moveTopLeft"
    , "moveTopRight"
    , "normalized"
    , "equals"
    , "readFrom"
    , "right"
    , "setBottom"
    , "setBottomLeft"
    , "setBottomRight"
    , "setCoords"
    , "setHeight"
    , "setLeft"
    , "setRect"
    , "setRight"
    , "setSize"
    , "setTop"
    , "setTopLeft"
    , "setTopRight"
    , "setWidth"
    , "setX"
    , "setY"
    , "size"
    , "toAlignedRect"
    , "toRect"
    , "top"
    , "topLeft"
    , "topRight"
    , "translate"
    , "translated"
    , "united"
    , "width"
    , "writeTo"
    , "x"
    , "y"
    , "toString"
};

static const char * const qtscript_QRectF_function_signatures[] = {
    "\nQPointF topleft, QPointF bottomRight\nQPointF topleft, QSizeF size\nQRect rect\nqreal left, qreal top, qreal width, qreal height"
    // static
    // prototype
    , "qreal x1, qreal y1, qreal x2, qreal y2"
    , "qreal x1, qreal y1, qreal x2, qreal y2"
    , ""
    , ""
    , ""
    , ""
    , "QPointF p\nQRectF r\nqreal x, qreal y"
    , ""
    , "QRectF other"
    , "QRectF r"
    , ""
    , ""
    , ""
    , ""
    , "qreal pos"
    , "QPointF p"
    , "QPointF p"
    , "QPointF p"
    , "qreal pos"
    , "qreal pos"
    , "QPointF p\nqreal x, qreal t"
    , "qreal pos"
    , "QPointF p"
    , "QPointF p"
    , ""
    , "QRectF arg__2"
    , "QDataStream arg__1"
    , ""
    , "qreal pos"
    , "QPointF p"
    , "QPointF p"
    , "qreal x1, qreal y1, qreal x2, qreal y2"
    , "qreal h"
    , "qreal pos"
    , "qreal x, qreal y, qreal w, qreal h"
    , "qreal pos"
    , "QSizeF s"
    , "qreal pos"
    , "QPointF p"
    , "QPointF p"
    , "qreal w"
    , "qreal pos"
    , "qreal pos"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QPointF p\nqreal dx, qreal dy"
    , "QPointF p\nqreal dx, qreal dy"
    , "QRectF other"
    , ""
    , "QDataStream arg__1"
    , ""
    , ""
""
};

static const int qtscript_QRectF_function_lengths[] = {
    4
    // static
    // prototype
    , 4
    , 4
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 1
    , 1
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
    , 2
    , 1
    , 1
    , 1
    , 0
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 4
    , 1
    , 1
    , 4
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
    , 0
    , 0
    , 2
    , 2
    , 1
    , 0
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QRectF_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QRectF::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QRectF*)
Q_DECLARE_METATYPE(QDataStream*)

//
// QRectF
//

static QScriptValue qtscript_QRectF_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 56;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QRectF* _q_self = qscriptvalue_cast<QRectF*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QRectF.%0(): this object is not a QRectF")
            .arg(qtscript_QRectF_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->adjust(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QRectF _q_result = _q_self->adjusted(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->bottom();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->bottomLeft();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->bottomRight();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->center();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            bool _q_result = _q_self->contains(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            bool _q_result = _q_self->contains(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        bool _q_result = _q_self->contains(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->height();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QRectF _q_result = _q_self->intersected(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        bool _q_result = _q_self->intersects(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->left();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->moveBottom(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->moveBottomLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->moveBottomRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->moveCenter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->moveLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->moveRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->moveTo(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->moveTo(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->moveTop(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->moveTopLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->moveTopRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QRectF _q_result = _q_self->normalized();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        bool _q_result = operator==(*_q_self, _q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->right();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setBottom(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setBottomLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setBottomRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->setCoords(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setHeight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->setRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        QSizeF _q_arg0 = qscriptvalue_cast<QSizeF>(context->argument(0));
        _q_self->setSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setTop(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setTopLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setTopRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setX(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setY(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 0) {
        QSizeF _q_result = _q_self->size();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 44:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->toAlignedRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 45:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->toRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 46:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->top();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->topLeft();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->topRight();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 49:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->translate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->translate(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 50:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        QRectF _q_result = _q_self->translated(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QRectF _q_result = _q_self->translated(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 51:
    if (context->argumentCount() == 1) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        QRectF _q_result = _q_self->united(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 52:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->width();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 53:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 54:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->x();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 55:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->y();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 56: {
    QString result;
    QDebug d(&result);
    d << *_q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRectF_throw_ambiguity_error_helper(context,
        qtscript_QRectF_function_names[_id+1],
        qtscript_QRectF_function_signatures[_id+1]);
}

static QScriptValue qtscript_QRectF_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QRectF(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QRectF _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        QRectF _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPointF>() == context->argument(1).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
            QRectF _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QSizeF>() == context->argument(1).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QSizeF _q_arg1 = qscriptvalue_cast<QSizeF>(context->argument(1));
            QRectF _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QRectF _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRectF_throw_ambiguity_error_helper(context,
        qtscript_QRectF_function_names[_id],
        qtscript_QRectF_function_signatures[_id]);
}

QScriptValue qtscript_create_QRectF_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QRectF*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QRectF*)0));
    for (int i = 0; i < 57; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QRectF_prototype_call, qtscript_QRectF_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QRectF_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QRectF>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QRectF*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QRectF_static_call, proto, qtscript_QRectF_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
