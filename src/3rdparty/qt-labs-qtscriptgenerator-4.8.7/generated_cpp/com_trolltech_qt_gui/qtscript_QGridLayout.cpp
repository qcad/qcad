#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgridlayout.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qgridlayout.h>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qlist.h>
#include <qmargins.h>
#include <qobject.h>
#include <qrect.h>
#include <qsize.h>
#include <qwidget.h>

#include "qtscriptshell_QGridLayout.h"

static const char * const qtscript_QGridLayout_function_names[] = {
    "QGridLayout"
    // static
    // prototype
    , "addItem"
    , "addLayout"
    , "addWidget"
    , "cellRect"
    , "columnCount"
    , "columnMinimumWidth"
    , "columnStretch"
    , "getItemPosition"
    , "horizontalSpacing"
    , "itemAtPosition"
    , "originCorner"
    , "rowCount"
    , "rowMinimumHeight"
    , "rowStretch"
    , "setColumnMinimumWidth"
    , "setColumnStretch"
    , "setDefaultPositioning"
    , "setHorizontalSpacing"
    , "setOriginCorner"
    , "setRowMinimumHeight"
    , "setRowStretch"
    , "setSpacing"
    , "setVerticalSpacing"
    , "spacing"
    , "verticalSpacing"
    , "toString"
};

static const char * const qtscript_QGridLayout_function_signatures[] = {
    "\nQWidget parent"
    // static
    // prototype
    , "QLayoutItem item, int row, int column, int rowSpan, int columnSpan, Alignment arg__6"
    , "QLayout arg__1, int row, int column, Alignment arg__4\nQLayout arg__1, int row, int column, int rowSpan, int columnSpan, Alignment arg__6"
    , "QWidget arg__1, int row, int column, Alignment arg__4\nQWidget arg__1, int row, int column, int rowSpan, int columnSpan, Alignment arg__6"
    , "int row, int column"
    , ""
    , "int column"
    , "int column"
    , "int idx, int row, int column, int rowSpan, int columnSpan"
    , ""
    , "int row, int column"
    , ""
    , ""
    , "int row"
    , "int row"
    , "int column, int minSize"
    , "int column, int stretch"
    , "int n, Orientation orient"
    , "int spacing"
    , "Corner arg__1"
    , "int row, int minSize"
    , "int row, int stretch"
    , "int spacing"
    , "int spacing"
    , ""
    , ""
""
};

static const int qtscript_QGridLayout_function_lengths[] = {
    1
    // static
    // prototype
    , 6
    , 6
    , 6
    , 2
    , 0
    , 1
    , 1
    , 5
    , 0
    , 2
    , 0
    , 0
    , 1
    , 1
    , 2
    , 2
    , 2
    , 1
    , 1
    , 2
    , 2
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QGridLayout_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGridLayout::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGridLayout*)
Q_DECLARE_METATYPE(QtScriptShell_QGridLayout*)
Q_DECLARE_METATYPE(QLayoutItem*)
Q_DECLARE_METATYPE(QFlags<Qt::AlignmentFlag>)
Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(Qt::Corner)
Q_DECLARE_METATYPE(Qt::Orientation)

//
// QGridLayout
//

static QScriptValue qtscript_QGridLayout_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 25;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGridLayout* _q_self = qscriptvalue_cast<QGridLayout*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGridLayout.%0(): this object is not a QGridLayout")
            .arg(qtscript_QGridLayout_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 3) {
        QLayoutItem* _q_arg0 = qscriptvalue_cast<QLayoutItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->addItem(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QLayoutItem* _q_arg0 = qscriptvalue_cast<QLayoutItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->addItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        QLayoutItem* _q_arg0 = qscriptvalue_cast<QLayoutItem*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        _q_self->addItem(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        QLayoutItem* _q_arg0 = qscriptvalue_cast<QLayoutItem*>(context->argument(0));
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
    if (context->argumentCount() == 3) {
        QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->addLayout(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg3 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(3));
        _q_self->addLayout(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        _q_self->addLayout(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        QLayout* _q_arg0 = qscriptvalue_cast<QLayout*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg5 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(5));
        _q_self->addLayout(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        _q_self->addWidget(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg3 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(3));
        _q_self->addWidget(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        _q_self->addWidget(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        int _q_arg4 = context->argument(4).toInt32();
        QFlags<Qt::AlignmentFlag> _q_arg5 = qscriptvalue_cast<QFlags<Qt::AlignmentFlag> >(context->argument(5));
        _q_self->addWidget(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QRect _q_result = _q_self->cellRect(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columnCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->columnMinimumWidth(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->columnStretch(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 5) {
        int _q_arg0 = context->argument(0).toInt32();
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
        int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
        int* _q_arg4 = qscriptvalue_cast<int*>(context->argument(4));
        _q_self->getItemPosition(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->horizontalSpacing();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QLayoutItem* _q_result = _q_self->itemAtPosition(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        Qt::Corner _q_result = _q_self->originCorner();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->rowCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->rowMinimumHeight(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->rowStretch(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setColumnMinimumWidth(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setColumnStretch(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
        _q_self->setDefaultPositioning(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setHorizontalSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        Qt::Corner _q_arg0 = qscriptvalue_cast<Qt::Corner>(context->argument(0));
        _q_self->setOriginCorner(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setRowMinimumHeight(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setRowStretch(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setVerticalSpacing(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->spacing();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->verticalSpacing();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25: {
    QString result = QString::fromLatin1("QGridLayout");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGridLayout_throw_ambiguity_error_helper(context,
        qtscript_QGridLayout_function_names[_id+1],
        qtscript_QGridLayout_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGridLayout_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGridLayout(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGridLayout* _q_cpp_result = new QtScriptShell_QGridLayout();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGridLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QGridLayout* _q_cpp_result = new QtScriptShell_QGridLayout(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGridLayout*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGridLayout_throw_ambiguity_error_helper(context,
        qtscript_QGridLayout_function_names[_id],
        qtscript_QGridLayout_function_signatures[_id]);
}

static QScriptValue qtscript_QGridLayout_toScriptValue(QScriptEngine *engine, QGridLayout* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGridLayout_fromScriptValue(const QScriptValue &value, QGridLayout* &out)
{
    out = qobject_cast<QGridLayout*>(value.toQObject());
}

QScriptValue qtscript_create_QGridLayout_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGridLayout*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGridLayout*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QLayout*>()));
    for (int i = 0; i < 26; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGridLayout_prototype_call, qtscript_QGridLayout_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGridLayout_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGridLayout*>(engine, qtscript_QGridLayout_toScriptValue, 
        qtscript_QGridLayout_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGridLayout_static_call, proto, qtscript_QGridLayout_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
