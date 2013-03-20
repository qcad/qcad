#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsortfilterproxymodel.h>
#include <QItemSelection>
#include <QSize>
#include <QStringList>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qitemselectionmodel.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qregexp.h>
#include <qsize.h>
#include <qsortfilterproxymodel.h>
#include <qstringlist.h>

#include "qtscriptshell_QSortFilterProxyModel.h"

static const char * const qtscript_QSortFilterProxyModel_function_names[] = {
    "QSortFilterProxyModel"
    // static
    // prototype
    , "buddy"
    , "canFetchMore"
    , "columnCount"
    , "data"
    , "dropMimeData"
    , "fetchMore"
    , "flags"
    , "hasChildren"
    , "headerData"
    , "index"
    , "insertColumns"
    , "insertRows"
    , "mapFromSource"
    , "mapSelectionFromSource"
    , "mapSelectionToSource"
    , "mapToSource"
    , "match"
    , "mimeData"
    , "mimeTypes"
    , "parent"
    , "removeColumns"
    , "removeRows"
    , "rowCount"
    , "setData"
    , "setHeaderData"
    , "setSourceModel"
    , "sort"
    , "sortColumn"
    , "sortOrder"
    , "span"
    , "supportedDropActions"
    , "toString"
};

static const char * const qtscript_QSortFilterProxyModel_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "QModelIndex index"
    , "QModelIndex parent"
    , "QModelIndex parent"
    , "QModelIndex index, int role"
    , "QMimeData data, DropAction action, int row, int column, QModelIndex parent"
    , "QModelIndex parent"
    , "QModelIndex index"
    , "QModelIndex parent"
    , "int section, Orientation orientation, int role"
    , "int row, int column, QModelIndex parent"
    , "int column, int count, QModelIndex parent"
    , "int row, int count, QModelIndex parent"
    , "QModelIndex sourceIndex"
    , "QItemSelection sourceSelection"
    , "QItemSelection proxySelection"
    , "QModelIndex proxyIndex"
    , "QModelIndex start, int role, Object value, int hits, MatchFlags flags"
    , "List indexes"
    , ""
    , "QModelIndex child"
    , "int column, int count, QModelIndex parent"
    , "int row, int count, QModelIndex parent"
    , "QModelIndex parent"
    , "QModelIndex index, Object value, int role"
    , "int section, Orientation orientation, Object value, int role"
    , "QAbstractItemModel sourceModel"
    , "int column, SortOrder order"
    , ""
    , ""
    , "QModelIndex index"
    , ""
""
};

static const int qtscript_QSortFilterProxyModel_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 1
    , 2
    , 5
    , 1
    , 1
    , 1
    , 3
    , 3
    , 3
    , 3
    , 1
    , 1
    , 1
    , 1
    , 5
    , 1
    , 0
    , 1
    , 3
    , 3
    , 1
    , 3
    , 4
    , 1
    , 2
    , 0
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QSortFilterProxyModel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSortFilterProxyModel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSortFilterProxyModel*)
Q_DECLARE_METATYPE(QtScriptShell_QSortFilterProxyModel*)
Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QMimeData*)
Q_DECLARE_METATYPE(Qt::DropAction)
Q_DECLARE_METATYPE(QFlags<Qt::ItemFlag>)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QItemSelection)
Q_DECLARE_METATYPE(QFlags<Qt::MatchFlag>)
Q_DECLARE_METATYPE(QList<QModelIndex>)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)

//
// QSortFilterProxyModel
//

static QScriptValue qtscript_QSortFilterProxyModel_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 31;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSortFilterProxyModel* _q_self = qscriptvalue_cast<QSortFilterProxyModel*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSortFilterProxyModel.%0(): this object is not a QSortFilterProxyModel")
            .arg(qtscript_QSortFilterProxyModel_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_result = _q_self->buddy(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        bool _q_result = _q_self->canFetchMore(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columnCount();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_result = _q_self->columnCount(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QVariant _q_result = _q_self->data(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QVariant _q_result = _q_self->data(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 5) {
        QMimeData* _q_arg0 = qscriptvalue_cast<QMimeData*>(context->argument(0));
        Qt::DropAction _q_arg1 = qscriptvalue_cast<Qt::DropAction>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QModelIndex _q_arg4 = qscriptvalue_cast<QModelIndex>(context->argument(4));
        bool _q_result = _q_self->dropMimeData(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        _q_self->fetchMore(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QFlags<Qt::ItemFlag> _q_result = _q_self->flags(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasChildren();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        bool _q_result = _q_self->hasChildren(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
        QVariant _q_result = _q_self->headerData(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        QVariant _q_result = _q_self->headerData(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_result = _q_self->index(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        QModelIndex _q_result = _q_self->index(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->insertColumns(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->insertColumns(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->insertRows(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->insertRows(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_result = _q_self->mapFromSource(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QItemSelection _q_arg0 = qscriptvalue_cast<QItemSelection>(context->argument(0));
        QItemSelection _q_result = _q_self->mapSelectionFromSource(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QItemSelection _q_arg0 = qscriptvalue_cast<QItemSelection>(context->argument(0));
        QItemSelection _q_result = _q_self->mapSelectionToSource(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_result = _q_self->mapToSource(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 3) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QVariant _q_arg2 = context->argument(2).toVariant();
        QList<QModelIndex> _q_result = _q_self->match(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QVariant _q_arg2 = context->argument(2).toVariant();
        int _q_arg3 = context->argument(3).toInt32();
        QList<QModelIndex> _q_result = _q_self->match(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QVariant _q_arg2 = context->argument(2).toVariant();
        int _q_arg3 = context->argument(3).toInt32();
        QFlags<Qt::MatchFlag> _q_arg4 = qscriptvalue_cast<QFlags<Qt::MatchFlag> >(context->argument(4));
        QList<QModelIndex> _q_result = _q_self->match(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QList<QModelIndex> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QMimeData* _q_result = _q_self->mimeData(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->mimeTypes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_result = _q_self->parent(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->removeColumns(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->removeColumns(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->removeRows(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->removeRows(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->rowCount();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_result = _q_self->rowCount(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        bool _q_result = _q_self->setData(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        int _q_arg2 = context->argument(2).toInt32();
        bool _q_result = _q_self->setData(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
        QVariant _q_arg2 = context->argument(2).toVariant();
        bool _q_result = _q_self->setHeaderData(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
        QVariant _q_arg2 = context->argument(2).toVariant();
        int _q_arg3 = context->argument(3).toInt32();
        bool _q_result = _q_self->setHeaderData(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QAbstractItemModel* _q_arg0 = qscriptvalue_cast<QAbstractItemModel*>(context->argument(0));
        _q_self->setSourceModel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->sort(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::SortOrder _q_arg1 = qscriptvalue_cast<Qt::SortOrder>(context->argument(1));
        _q_self->sort(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->sortColumn();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        Qt::SortOrder _q_result = _q_self->sortOrder();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QSize _q_result = _q_self->span(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        QFlags<Qt::DropAction> _q_result = _q_self->supportedDropActions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 31: {
    QString result = QString::fromLatin1("QSortFilterProxyModel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSortFilterProxyModel_throw_ambiguity_error_helper(context,
        qtscript_QSortFilterProxyModel_function_names[_id+1],
        qtscript_QSortFilterProxyModel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSortFilterProxyModel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSortFilterProxyModel(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSortFilterProxyModel* _q_cpp_result = new QtScriptShell_QSortFilterProxyModel();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QSortFilterProxyModel*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QSortFilterProxyModel* _q_cpp_result = new QtScriptShell_QSortFilterProxyModel(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QSortFilterProxyModel*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSortFilterProxyModel_throw_ambiguity_error_helper(context,
        qtscript_QSortFilterProxyModel_function_names[_id],
        qtscript_QSortFilterProxyModel_function_signatures[_id]);
}

QScriptValue qtscript_create_QSortFilterProxyModel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSortFilterProxyModel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSortFilterProxyModel*)0));
    for (int i = 0; i < 32; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSortFilterProxyModel_prototype_call, qtscript_QSortFilterProxyModel_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSortFilterProxyModel_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSortFilterProxyModel*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSortFilterProxyModel_static_call, proto, qtscript_QSortFilterProxyModel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
