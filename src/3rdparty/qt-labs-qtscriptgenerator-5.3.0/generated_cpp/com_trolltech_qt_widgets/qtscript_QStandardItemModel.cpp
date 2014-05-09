#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qstandarditemmodel.h>
#include <QSize>
#include <QStringList>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qstandarditemmodel.h>
#include <qstringlist.h>
#include <qvector.h>

#include "qtscriptshell_QStandardItemModel.h"

static const char * const qtscript_QStandardItemModel_function_names[] = {
    "QStandardItemModel"
    // static
    // prototype
    , "appendColumn"
    , "appendRow"
    , "clear"
    , "findItems"
    , "horizontalHeaderItem"
    , "indexFromItem"
    , "insertColumn"
    , "insertRow"
    , "invisibleRootItem"
    , "item"
    , "itemFromIndex"
    , "itemPrototype"
    , "setColumnCount"
    , "setHorizontalHeaderItem"
    , "setHorizontalHeaderLabels"
    , "setItem"
    , "setItemPrototype"
    , "setItemRoleNames"
    , "setRowCount"
    , "setVerticalHeaderItem"
    , "setVerticalHeaderLabels"
    , "takeColumn"
    , "takeHorizontalHeaderItem"
    , "takeItem"
    , "takeRow"
    , "takeVerticalHeaderItem"
    , "verticalHeaderItem"
    , "toString"
};

static const char * const qtscript_QStandardItemModel_function_signatures[] = {
    "QObject parent\nint rows, int columns, QObject parent"
    // static
    // prototype
    , "List items"
    , "QStandardItem item\nList items"
    , ""
    , "String text, MatchFlags flags, int column"
    , "int column"
    , "QStandardItem item"
    , "int column, List items"
    , "int row, QStandardItem item\nint row, List items"
    , ""
    , "int row, int column"
    , "QModelIndex index"
    , ""
    , "int columns"
    , "int column, QStandardItem item"
    , "List labels"
    , "int row, QStandardItem item\nint row, int column, QStandardItem item"
    , "QStandardItem item"
    , "HashMap roleNames"
    , "int rows"
    , "int row, QStandardItem item"
    , "List labels"
    , "int column"
    , "int column"
    , "int row, int column"
    , "int row"
    , "int row"
    , "int row"
""
};

static const int qtscript_QStandardItemModel_function_lengths[] = {
    3
    // static
    // prototype
    , 1
    , 1
    , 0
    , 3
    , 1
    , 1
    , 2
    , 2
    , 0
    , 2
    , 1
    , 0
    , 1
    , 2
    , 1
    , 3
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QStandardItemModel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStandardItemModel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStandardItemModel*)
Q_DECLARE_METATYPE(QtScriptShell_QStandardItemModel*)
Q_DECLARE_METATYPE(QStandardItem*)
Q_DECLARE_METATYPE(QList<QStandardItem* >)
Q_DECLARE_METATYPE(QFlags<Qt::MatchFlag>)
Q_DECLARE_METATYPE(const QStandardItem*)
template <> \
struct QMetaTypeId< QHash<int,QByteArray > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QHash<int,QByteArray > >("QHash<int,QByteArray >")); \
        return metatype_id.load(); \
    } \
};
Q_DECLARE_METATYPE(QAbstractItemModel*)

//
// QStandardItemModel
//

static QScriptValue qtscript_QStandardItemModel_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 27;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QStandardItemModel* _q_self = qscriptvalue_cast<QStandardItemModel*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStandardItemModel.%0(): this object is not a QStandardItemModel")
            .arg(qtscript_QStandardItemModel_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QList<QStandardItem*> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->appendColumn(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QStandardItem*>(context->argument(0))) {
            QStandardItem* _q_arg0 = qscriptvalue_cast<QStandardItem*>(context->argument(0));
            _q_self->appendRow(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isArray()) {
            QList<QStandardItem*> _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            _q_self->appendRow(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QList<QStandardItem* > _q_result = _q_self->findItems(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<Qt::MatchFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::MatchFlag> >(context->argument(1));
        QList<QStandardItem* > _q_result = _q_self->findItems(_q_arg0, _q_arg1);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<Qt::MatchFlag> _q_arg1 = qscriptvalue_cast<QFlags<Qt::MatchFlag> >(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QList<QStandardItem* > _q_result = _q_self->findItems(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QStandardItem* _q_result = _q_self->horizontalHeaderItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        const QStandardItem* _q_arg0 = qscriptvalue_cast<const QStandardItem*>(context->argument(0));
        QModelIndex _q_result = _q_self->indexFromItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<QStandardItem*> _q_arg1;
        qScriptValueToSequence(context->argument(1), _q_arg1);
        _q_self->insertColumn(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        if (context->argument(0).isNumber()
            && qscriptvalue_cast<QStandardItem*>(context->argument(1))) {
            int _q_arg0 = context->argument(0).toInt32();
            QStandardItem* _q_arg1 = qscriptvalue_cast<QStandardItem*>(context->argument(1));
            _q_self->insertRow(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isArray()) {
            int _q_arg0 = context->argument(0).toInt32();
            QList<QStandardItem*> _q_arg1;
            qScriptValueToSequence(context->argument(1), _q_arg1);
            _q_self->insertRow(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QStandardItem* _q_result = _q_self->invisibleRootItem();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QStandardItem* _q_result = _q_self->item(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QStandardItem* _q_result = _q_self->item(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QStandardItem* _q_result = _q_self->itemFromIndex(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        const QStandardItem* _q_result = const_cast<const QStandardItem*>(_q_self->itemPrototype());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setColumnCount(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QStandardItem* _q_arg1 = qscriptvalue_cast<QStandardItem*>(context->argument(1));
        _q_self->setHorizontalHeaderItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setHorizontalHeaderLabels(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QStandardItem* _q_arg1 = qscriptvalue_cast<QStandardItem*>(context->argument(1));
        _q_self->setItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QStandardItem* _q_arg2 = qscriptvalue_cast<QStandardItem*>(context->argument(2));
        _q_self->setItem(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        const QStandardItem* _q_arg0 = qscriptvalue_cast<const QStandardItem*>(context->argument(0));
        _q_self->setItemPrototype(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QHash<int,QByteArray> _q_arg0 = qscriptvalue_cast<QHash<int,QByteArray> >(context->argument(0));
        _q_self->setItemRoleNames(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setRowCount(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QStandardItem* _q_arg1 = qscriptvalue_cast<QStandardItem*>(context->argument(1));
        _q_self->setVerticalHeaderItem(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QStringList _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setVerticalHeaderLabels(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<QStandardItem* > _q_result = _q_self->takeColumn(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QStandardItem* _q_result = _q_self->takeHorizontalHeaderItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QStandardItem* _q_result = _q_self->takeItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QStandardItem* _q_result = _q_self->takeItem(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QList<QStandardItem* > _q_result = _q_self->takeRow(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QStandardItem* _q_result = _q_self->takeVerticalHeaderItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QStandardItem* _q_result = _q_self->verticalHeaderItem(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27: {
    QString result = QString::fromLatin1("QStandardItemModel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStandardItemModel_throw_ambiguity_error_helper(context,
        qtscript_QStandardItemModel_function_names[_id+1],
        qtscript_QStandardItemModel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStandardItemModel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStandardItemModel(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QStandardItemModel* _q_cpp_result = new QtScriptShell_QStandardItemModel();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStandardItemModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QStandardItemModel* _q_cpp_result = new QtScriptShell_QStandardItemModel(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStandardItemModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QtScriptShell_QStandardItemModel* _q_cpp_result = new QtScriptShell_QStandardItemModel(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStandardItemModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QObject* _q_arg2 = context->argument(2).toQObject();
        QtScriptShell_QStandardItemModel* _q_cpp_result = new QtScriptShell_QStandardItemModel(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QStandardItemModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStandardItemModel_throw_ambiguity_error_helper(context,
        qtscript_QStandardItemModel_function_names[_id],
        qtscript_QStandardItemModel_function_signatures[_id]);
}

static QScriptValue qtscript_QStandardItemModel_toScriptValue(QScriptEngine *engine, QStandardItemModel* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QStandardItemModel_fromScriptValue(const QScriptValue &value, QStandardItemModel* &out)
{
    out = qobject_cast<QStandardItemModel*>(value.toQObject());
}

QScriptValue qtscript_create_QStandardItemModel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStandardItemModel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStandardItemModel*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractItemModel*>()));
    for (int i = 0; i < 28; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStandardItemModel_prototype_call, qtscript_QStandardItemModel_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStandardItemModel_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QStandardItemModel*>(engine, qtscript_QStandardItemModel_toScriptValue, 
        qtscript_QStandardItemModel_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStandardItemModel_static_call, proto, qtscript_QStandardItemModel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
