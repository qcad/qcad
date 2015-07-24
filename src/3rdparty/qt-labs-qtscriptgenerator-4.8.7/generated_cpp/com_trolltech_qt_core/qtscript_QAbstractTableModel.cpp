#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qabstractitemmodel.h>
#include <QSize>
#include <QStringList>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdatastream.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qstringlist.h>

#include "qtscriptshell_QAbstractTableModel.h"

static const char * const qtscript_QAbstractTableModel_function_names[] = {
    "QAbstractTableModel"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QAbstractTableModel_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
""
};

static const int qtscript_QAbstractTableModel_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QAbstractTableModel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractTableModel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractTableModel*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractTableModel*)
Q_DECLARE_METATYPE(QAbstractItemModel*)

//
// QAbstractTableModel
//

static QScriptValue qtscript_QAbstractTableModel_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 0;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractTableModel* _q_self = qscriptvalue_cast<QAbstractTableModel*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractTableModel.%0(): this object is not a QAbstractTableModel")
            .arg(qtscript_QAbstractTableModel_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QAbstractTableModel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractTableModel_throw_ambiguity_error_helper(context,
        qtscript_QAbstractTableModel_function_names[_id+1],
        qtscript_QAbstractTableModel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractTableModel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractTableModel(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractTableModel* _q_cpp_result = new QtScriptShell_QAbstractTableModel();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractTableModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QAbstractTableModel* _q_cpp_result = new QtScriptShell_QAbstractTableModel(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractTableModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractTableModel_throw_ambiguity_error_helper(context,
        qtscript_QAbstractTableModel_function_names[_id],
        qtscript_QAbstractTableModel_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractTableModel_toScriptValue(QScriptEngine *engine, QAbstractTableModel* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractTableModel_fromScriptValue(const QScriptValue &value, QAbstractTableModel* &out)
{
    out = qobject_cast<QAbstractTableModel*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractTableModel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractTableModel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractTableModel*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractItemModel*>()));

    qScriptRegisterMetaType<QAbstractTableModel*>(engine, qtscript_QAbstractTableModel_toScriptValue, 
        qtscript_QAbstractTableModel_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractTableModel_static_call, proto, qtscript_QAbstractTableModel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
