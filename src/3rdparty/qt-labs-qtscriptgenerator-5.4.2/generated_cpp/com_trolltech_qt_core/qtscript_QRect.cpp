#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qrect.h>
#include <QVariant>
#include <qmargins.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>

static const char * const qtscript_QRect_function_names[] = {
    "QRect"
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
    , "marginsAdded"
    , "marginsRemoved"
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
    , "operator_add_assign"
    , "equals"
    , "operator_subtract_assign"
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
    , "top"
    , "topLeft"
    , "topRight"
    , "translate"
    , "translated"
    , "united"
    , "width"
    , "x"
    , "y"
    , "toString"
};

static const char * const qtscript_QRect_function_signatures[] = {
    "\nQPoint topleft, QPoint bottomright\nQPoint topleft, QSize size\nint left, int top, int width, int height"
    // static
    // prototype
    , "int x1, int y1, int x2, int y2"
    , "int x1, int y1, int x2, int y2"
    , ""
    , ""
    , ""
    , ""
    , "QPoint p, bool proper\nQRect r, bool proper\nint x, int y\nint x, int y, bool proper"
    , ""
    , "QRect other"
    , "QRect r"
    , ""
    , ""
    , ""
    , ""
    , "QMargins margins"
    , "QMargins margins"
    , "int pos"
    , "QPoint p"
    , "QPoint p"
    , "QPoint p"
    , "int pos"
    , "int pos"
    , "QPoint p\nint x, int t"
    , "int pos"
    , "QPoint p"
    , "QPoint p"
    , ""
    , "QMargins margins"
    , "QRect arg__2"
    , "QMargins margins"
    , ""
    , "int pos"
    , "QPoint p"
    , "QPoint p"
    , "int x1, int y1, int x2, int y2"
    , "int h"
    , "int pos"
    , "int x, int y, int w, int h"
    , "int pos"
    , "QSize s"
    , "int pos"
    , "QPoint p"
    , "QPoint p"
    , "int w"
    , "int x"
    , "int y"
    , ""
    , ""
    , ""
    , ""
    , "QPoint p\nint dx, int dy"
    , "QPoint p\nint dx, int dy"
    , "QRect other"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QRect_function_lengths[] = {
    4
    // static
    // prototype
    , 4
    , 4
    , 0
    , 0
    , 0
    , 0
    , 3
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
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 0
    , 1
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
    , 2
    , 2
    , 1
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QRect_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QRect::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QRect*)
Q_DECLARE_METATYPE(QMargins)

//
// QRect
//

static QScriptValue qtscript_QRect_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QRect* _q_self = qscriptvalue_cast<QRect*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QRect.%0(): this object is not a QRect")
            .arg(qtscript_QRect_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->adjust(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QRect _q_result = _q_self->adjusted(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->bottom();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->bottomLeft();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->bottomRight();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->center();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            bool _q_result = _q_self->contains(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            bool _q_result = _q_self->contains(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && context->argument(1).isBoolean()) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            bool _q_result = _q_self->contains(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && context->argument(1).isBoolean()) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            bool _q_arg1 = context->argument(1).toBoolean();
            bool _q_result = _q_self->contains(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            bool _q_result = _q_self->contains(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_arg2 = context->argument(2).toBoolean();
        bool _q_result = _q_self->contains(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->height();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        QRect _q_result = _q_self->intersected(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
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
        int _q_result = _q_self->left();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QMargins _q_arg0 = qscriptvalue_cast<QMargins>(context->argument(0));
        QRect _q_result = _q_self->marginsAdded(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QMargins _q_arg0 = qscriptvalue_cast<QMargins>(context->argument(0));
        QRect _q_result = _q_self->marginsRemoved(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->moveBottom(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->moveBottomLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->moveBottomRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->moveCenter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->moveLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->moveRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->moveTo(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->moveTo(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->moveTop(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->moveTopLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->moveTopRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->normalized();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        QMargins _q_arg0 = qscriptvalue_cast<QMargins>(context->argument(0));
        QRect& _q_result = _q_self->operator+=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        bool _q_result = operator==(*_q_self, _q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QMargins _q_arg0 = qscriptvalue_cast<QMargins>(context->argument(0));
        QRect& _q_result = _q_self->operator-=(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->right();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setBottom(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->setBottomLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->setBottomRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setCoords(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setHeight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        _q_self->setSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setTop(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 41:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->setTopLeft(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 42:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->setTopRight(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 43:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setX(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setY(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 46:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->size();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->top();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->topLeft();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 49:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->topRight();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 50:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->translate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->translate(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 51:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QRect _q_result = _q_self->translated(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QRect _q_result = _q_self->translated(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 52:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        QRect _q_result = _q_self->united(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 53:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->width();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 54:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->x();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 55:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->y();
        return QScriptValue(context->engine(), _q_result);
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
    return qtscript_QRect_throw_ambiguity_error_helper(context,
        qtscript_QRect_function_names[_id+1],
        qtscript_QRect_function_signatures[_id+1]);
}

static QScriptValue qtscript_QRect_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QRect(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QRect _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QPoint>() == context->argument(1).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
            QRect _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QSize>() == context->argument(1).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QSize _q_arg1 = qscriptvalue_cast<QSize>(context->argument(1));
            QRect _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QRect _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRect_throw_ambiguity_error_helper(context,
        qtscript_QRect_function_names[_id],
        qtscript_QRect_function_signatures[_id]);
}

QScriptValue qtscript_create_QRect_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QRect*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QRect*)0));
    for (int i = 0; i < 57; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QRect_prototype_call, qtscript_QRect_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QRect_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QRect>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QRect*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QRect_static_call, proto, qtscript_QRect_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
