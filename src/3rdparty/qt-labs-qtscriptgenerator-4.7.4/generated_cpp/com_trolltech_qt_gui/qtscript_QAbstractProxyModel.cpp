#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractproxymodel.h>
#include <QItemSelection>
#include <QSize>
#include <QStringList>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qabstractproxymodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdatastream.h>
#include <qitemselectionmodel.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qstringlist.h>

#include "qtscriptshell_QAbstractProxyModel.h"

static const char * const qtscript_QAbstractProxyModel_function_names[] = {
    "QAbstractProxyModel"
    // static
    // prototype
    , "mapFromSource"
    , "mapSelectionFromSource"
    , "mapSelectionToSource"
    , "mapToSource"
    , "setSourceModel"
    , "sourceModel"
    , "toString"
};

static const char * const qtscript_QAbstractProxyModel_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "QModelIndex sourceIndex"
    , "QItemSelection selection"
    , "QItemSelection selection"
    , "QModelIndex proxyIndex"
    , "QAbstractItemModel sourceModel"
    , ""
""
};

static const int qtscript_QAbstractProxyModel_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QAbstractProxyModel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractProxyModel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractProxyModel*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractProxyModel*)
Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QItemSelection)
Q_DECLARE_METATYPE(QAbstractItemModel*)

//
// QAbstractProxyModel
//

static QScriptValue qtscript_QAbstractProxyModel_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 6;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractProxyModel* _q_self = qscriptvalue_cast<QAbstractProxyModel*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractProxyModel.%0(): this object is not a QAbstractProxyModel")
            .arg(qtscript_QAbstractProxyModel_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_result = _q_self->mapFromSource(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QItemSelection _q_arg0 = qscriptvalue_cast<QItemSelection>(context->argument(0));
        QItemSelection _q_result = _q_self->mapSelectionFromSource(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QItemSelection _q_arg0 = qscriptvalue_cast<QItemSelection>(context->argument(0));
        QItemSelection _q_result = _q_self->mapSelectionToSource(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_result = _q_self->mapToSource(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QAbstractItemModel* _q_arg0 = qscriptvalue_cast<QAbstractItemModel*>(context->argument(0));
        _q_self->setSourceModel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QAbstractItemModel* _q_result = _q_self->sourceModel();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QAbstractProxyModel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractProxyModel_throw_ambiguity_error_helper(context,
        qtscript_QAbstractProxyModel_function_names[_id+1],
        qtscript_QAbstractProxyModel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractProxyModel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractProxyModel(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractProxyModel* _q_cpp_result = new QtScriptShell_QAbstractProxyModel();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractProxyModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QAbstractProxyModel* _q_cpp_result = new QtScriptShell_QAbstractProxyModel(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractProxyModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractProxyModel_throw_ambiguity_error_helper(context,
        qtscript_QAbstractProxyModel_function_names[_id],
        qtscript_QAbstractProxyModel_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractProxyModel_toScriptValue(QScriptEngine *engine, QAbstractProxyModel* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractProxyModel_fromScriptValue(const QScriptValue &value, QAbstractProxyModel* &out)
{
    out = qobject_cast<QAbstractProxyModel*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractProxyModel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractProxyModel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractProxyModel*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractItemModel*>()));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractProxyModel_prototype_call, qtscript_QAbstractProxyModel_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractProxyModel_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractProxyModel*>(engine, qtscript_QAbstractProxyModel_toScriptValue, 
        qtscript_QAbstractProxyModel_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractProxyModel_static_call, proto, qtscript_QAbstractProxyModel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
