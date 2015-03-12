#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgraphicsgridlayout.h>
#include <QVariant>
#include <qcoreevent.h>
#include <qgraphicsgridlayout.h>
#include <qgraphicsitem.h>
#include <qgraphicslayoutitem.h>
#include <qrect.h>
#include <qsize.h>
#include <qsizepolicy.h>

#include "qtscriptshell_QGraphicsGridLayout.h"

static const char * const qtscript_QGraphicsGridLayout_function_names[] = {
    "QGraphicsGridLayout"
    // static
    // prototype
    , "addItem"
    , "alignment"
    , "columnAlignment"
    , "columnCount"
    , "columnMaximumWidth"
    , "columnMinimumWidth"
    , "columnPreferredWidth"
    , "columnSpacing"
    , "columnStretchFactor"
    , "horizontalSpacing"
    , "itemAt"
    , "removeItem"
    , "rowAlignment"
    , "rowCount"
    , "rowMaximumHeight"
    , "rowMinimumHeight"
    , "rowPreferredHeight"
    , "rowSpacing"
    , "rowStretchFactor"
    , "setAlignment"
    , "setColumnAlignment"
    , "setColumnFixedWidth"
    , "setColumnMaximumWidth"
    , "setColumnMinimumWidth"
    , "setColumnPreferredWidth"
    , "setColumnSpacing"
    , "setColumnStretchFactor"
    , "setHorizontalSpacing"
    , "setRowAlignment"
    , "setRowFixedHeight"
    , "setRowMaximumHeight"
    , "setRowMinimumHeight"
    , "setRowPreferredHeight"
    , "setRowSpacing"
    , "setRowStretchFactor"
    , "setSpacing"
    , "setVerticalSpacing"
    , "verticalSpacing"
    , "toString"
};

static const char * const qtscript_QGraphicsGridLayout_function_signatures[] = {
    "QGraphicsLayoutItem parent"
    // static
    // prototype
    , "QGraphicsLayoutItem item, int row, int column, Alignment alignment\nQGraphicsLayoutItem item, int row, int column, int rowSpan, int columnSpan, Alignment alignment"
    , "QGraphicsLayoutItem item"
    , "int column"
    , ""
    , "int column"
    , "int column"
    , "int column"
    , "int column"
    , "int column"
    , ""
    , "int row, int column"
    , "QGraphicsLayoutItem item"
    , "int row"
    , ""
    , "int row"
    , "int row"
    , "int row"
    , "int row"
    , "int row"
    , "QGraphicsLayoutItem item, Alignment alignment"
    , "int column, Alignment alignment"
    , "int column, qreal width"
    , "int column, qreal width"
    , "int column, qreal width"
    , "int column, qreal width"
    , "int column, qreal spacing"
    , "int column, int stretch"
    , "qreal spacing"
    , "int row, Alignment alignment"
    , "int row, qreal height"
    , "int row, qreal height"
    , "int row, qreal height"
    , "int row, qreal height"
    , "int row, qreal spacing"
    , "int row, int stretch"
    , "qreal spacing"
    , "qreal spacing"
    , ""
""
};

static const int qtscript_QGraphicsGridLayout_function_lengths[] = {
    1
    // static
    // prototype
    , 6
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 2
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 1
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsGridLayout_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsGridLayout::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsGridLayout*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsGridLayout*)
Q_DECLARE_METATYPE(QGraphicsLayoutItem*)
Q_DECLARE_METATYPE(QFlags<Qt::AlignmentFlag>)
Q_DECLARE_METATYPE(QGraphicsLayout*)

//
// QGraphicsGridLayout
//

static QScriptValue qtscript_QGraphicsGridLayout_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 38;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsGridLayout* _q_self = qscriptvalue_cast<QGraphicsGridLayout*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsGridLayout.%0(): this object is not a QGraphicsGridLayout")
            .arg(qtscript_QGraphicsGridLayout_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 3) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->addItem(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg3 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(3));
        _q_self->addItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        _q_self->addItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg5 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(5));
        _q_self->addItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        QFlags<Qt::AlignmentFlag> _q_result = _q_self->alignment(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QFlags<Qt::AlignmentFlag> _q_result = _q_self->columnAlignment(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columnCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_result = _q_self->columnMaximumWidth(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_result = _q_self->columnMinimumWidth(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_result = _q_self->columnPreferredWidth(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_result = _q_self->columnSpacing(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->columnStretchFactor(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->horizontalSpacing();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QGraphicsLayoutItem* _q_result = _q_self->itemAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        _q_self->removeItem(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QFlags<Qt::AlignmentFlag> _q_result = _q_self->rowAlignment(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->rowCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_result = _q_self->rowMaximumHeight(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_result = _q_self->rowMinimumHeight(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_result = _q_self->rowPreferredHeight(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_result = _q_self->rowSpacing(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->rowStretchFactor(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 2) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        QFlags<Qt::AlignmentFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(1));
        _q_self->setAlignment(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(1));
        _q_self->setColumnAlignment(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setColumnFixedWidth(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setColumnMaximumWidth(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setColumnMinimumWidth(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setColumnPreferredWidth(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setColumnSpacing(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setColumnStretchFactor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setHorizontalSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(1));
        _q_self->setRowAlignment(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setRowFixedHeight(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setRowMaximumHeight(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setRowMinimumHeight(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setRowPreferredHeight(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 33:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->setRowSpacing(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setRowStretchFactor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setVerticalSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->verticalSpacing();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 38: {
    QString result = QString::fromLatin1("QGraphicsGridLayout");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsGridLayout_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsGridLayout_function_names[_id+1],
        qtscript_QGraphicsGridLayout_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsGridLayout_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsGridLayout(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsGridLayout* _q_cpp_result = new QtScriptShell_QGraphicsGridLayout();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsGridLayout*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QGraphicsLayoutItem* _q_arg0 = qscriptvalue_cast<QGraphicsLayoutItem*>(context->argument(0));
        QtScriptShell_QGraphicsGridLayout* _q_cpp_result = new QtScriptShell_QGraphicsGridLayout(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QGraphicsGridLayout*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsGridLayout_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsGridLayout_function_names[_id],
        qtscript_QGraphicsGridLayout_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsGridLayout_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsGridLayout*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsGridLayout*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsLayout*>()));
    for (int i = 0; i < 39; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsGridLayout_prototype_call, qtscript_QGraphicsGridLayout_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsGridLayout_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsGridLayout*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsGridLayout_static_call, proto, qtscript_QGraphicsGridLayout_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
