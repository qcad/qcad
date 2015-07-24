#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qcompleter.h>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qbytearray.h>
#include <qcompleter.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qrect.h>
#include <qstringlist.h>
#include <qwidget.h>

#include "qtscriptshell_QCompleter.h"

static const char * const qtscript_QCompleter_function_names[] = {
    "QCompleter"
    // static
    // prototype
    , "completionCount"
    , "completionModel"
    , "currentCompletion"
    , "currentIndex"
    , "currentRow"
    , "model"
    , "pathFromIndex"
    , "popup"
    , "setCurrentRow"
    , "setModel"
    , "setPopup"
    , "setWidget"
    , "splitPath"
    , "widget"
    , "toString"
};

static const char * const qtscript_QCompleter_function_signatures[] = {
    "QAbstractItemModel model, QObject parent\nQObject parent\nList completions, QObject parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QModelIndex index"
    , ""
    , "int row"
    , "QAbstractItemModel c"
    , "QAbstractItemView popup"
    , "QWidget widget"
    , "String path"
    , ""
""
};

static const int qtscript_QCompleter_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QCompleter_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QCompleter::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QCompleter*)
Q_DECLARE_METATYPE(QtScriptShell_QCompleter*)
Q_DECLARE_METATYPE(QCompleter::ModelSorting)
Q_DECLARE_METATYPE(QCompleter::CompletionMode)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QAbstractItemView*)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QCompleter::ModelSorting
//

static const QCompleter::ModelSorting qtscript_QCompleter_ModelSorting_values[] = {
    QCompleter::UnsortedModel
    , QCompleter::CaseSensitivelySortedModel
    , QCompleter::CaseInsensitivelySortedModel
};

static const char * const qtscript_QCompleter_ModelSorting_keys[] = {
    "UnsortedModel"
    , "CaseSensitivelySortedModel"
    , "CaseInsensitivelySortedModel"
};

static QString qtscript_QCompleter_ModelSorting_toStringHelper(QCompleter::ModelSorting value)
{
    if ((value >= QCompleter::UnsortedModel) && (value <= QCompleter::CaseInsensitivelySortedModel))
        return qtscript_QCompleter_ModelSorting_keys[static_cast<int>(value)-static_cast<int>(QCompleter::UnsortedModel)];
    return QString();
}

static QScriptValue qtscript_QCompleter_ModelSorting_toScriptValue(QScriptEngine *engine, const QCompleter::ModelSorting &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QCompleter"));
    return clazz.property(qtscript_QCompleter_ModelSorting_toStringHelper(value));
}

static void qtscript_QCompleter_ModelSorting_fromScriptValue(const QScriptValue &value, QCompleter::ModelSorting &out)
{
    out = qvariant_cast<QCompleter::ModelSorting>(value.toVariant());
}

static QScriptValue qtscript_construct_QCompleter_ModelSorting(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QCompleter::UnsortedModel) && (arg <= QCompleter::CaseInsensitivelySortedModel))
        return qScriptValueFromValue(engine,  static_cast<QCompleter::ModelSorting>(arg));
    return context->throwError(QString::fromLatin1("ModelSorting(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QCompleter_ModelSorting_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QCompleter::ModelSorting value = qscriptvalue_cast<QCompleter::ModelSorting>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QCompleter_ModelSorting_toString(QScriptContext *context, QScriptEngine *engine)
{
    QCompleter::ModelSorting value = qscriptvalue_cast<QCompleter::ModelSorting>(context->thisObject());
    return QScriptValue(engine, qtscript_QCompleter_ModelSorting_toStringHelper(value));
}

static QScriptValue qtscript_create_QCompleter_ModelSorting_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QCompleter_ModelSorting,
        qtscript_QCompleter_ModelSorting_valueOf, qtscript_QCompleter_ModelSorting_toString);
    qScriptRegisterMetaType<QCompleter::ModelSorting>(engine, qtscript_QCompleter_ModelSorting_toScriptValue,
        qtscript_QCompleter_ModelSorting_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QCompleter_ModelSorting_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QCompleter_ModelSorting_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QCompleter::CompletionMode
//

static const QCompleter::CompletionMode qtscript_QCompleter_CompletionMode_values[] = {
    QCompleter::PopupCompletion
    , QCompleter::UnfilteredPopupCompletion
    , QCompleter::InlineCompletion
};

static const char * const qtscript_QCompleter_CompletionMode_keys[] = {
    "PopupCompletion"
    , "UnfilteredPopupCompletion"
    , "InlineCompletion"
};

static QString qtscript_QCompleter_CompletionMode_toStringHelper(QCompleter::CompletionMode value)
{
    if ((value >= QCompleter::PopupCompletion) && (value <= QCompleter::InlineCompletion))
        return qtscript_QCompleter_CompletionMode_keys[static_cast<int>(value)-static_cast<int>(QCompleter::PopupCompletion)];
    return QString();
}

static QScriptValue qtscript_QCompleter_CompletionMode_toScriptValue(QScriptEngine *engine, const QCompleter::CompletionMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QCompleter"));
    return clazz.property(qtscript_QCompleter_CompletionMode_toStringHelper(value));
}

static void qtscript_QCompleter_CompletionMode_fromScriptValue(const QScriptValue &value, QCompleter::CompletionMode &out)
{
    out = qvariant_cast<QCompleter::CompletionMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QCompleter_CompletionMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QCompleter::PopupCompletion) && (arg <= QCompleter::InlineCompletion))
        return qScriptValueFromValue(engine,  static_cast<QCompleter::CompletionMode>(arg));
    return context->throwError(QString::fromLatin1("CompletionMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QCompleter_CompletionMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QCompleter::CompletionMode value = qscriptvalue_cast<QCompleter::CompletionMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QCompleter_CompletionMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QCompleter::CompletionMode value = qscriptvalue_cast<QCompleter::CompletionMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QCompleter_CompletionMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QCompleter_CompletionMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QCompleter_CompletionMode,
        qtscript_QCompleter_CompletionMode_valueOf, qtscript_QCompleter_CompletionMode_toString);
    qScriptRegisterMetaType<QCompleter::CompletionMode>(engine, qtscript_QCompleter_CompletionMode_toScriptValue,
        qtscript_QCompleter_CompletionMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QCompleter_CompletionMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QCompleter_CompletionMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QCompleter
//

static QScriptValue qtscript_QCompleter_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 14;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QCompleter* _q_self = qscriptvalue_cast<QCompleter*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QCompleter.%0(): this object is not a QCompleter")
            .arg(qtscript_QCompleter_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->completionCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QAbstractItemModel* _q_result = _q_self->completionModel();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->currentCompletion();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QModelIndex _q_result = _q_self->currentIndex();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentRow();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QAbstractItemModel* _q_result = _q_self->model();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QString _q_result = _q_self->pathFromIndex(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QAbstractItemView* _q_result = _q_self->popup();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->setCurrentRow(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QAbstractItemModel* _q_arg0 = qscriptvalue_cast<QAbstractItemModel*>(context->argument(0));
        _q_self->setModel(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QAbstractItemView* _q_arg0 = qscriptvalue_cast<QAbstractItemView*>(context->argument(0));
        _q_self->setPopup(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QStringList _q_result = _q_self->splitPath(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->widget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14: {
    QString result = QString::fromLatin1("QCompleter");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QCompleter_throw_ambiguity_error_helper(context,
        qtscript_QCompleter_function_names[_id+1],
        qtscript_QCompleter_function_signatures[_id+1]);
}

static QScriptValue qtscript_QCompleter_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QCompleter(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QCompleter* _q_cpp_result = new QtScriptShell_QCompleter();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCompleter*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QAbstractItemModel*>(context->argument(0))) {
            QAbstractItemModel* _q_arg0 = qscriptvalue_cast<QAbstractItemModel*>(context->argument(0));
            QtScriptShell_QCompleter* _q_cpp_result = new QtScriptShell_QCompleter(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCompleter*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QCompleter* _q_cpp_result = new QtScriptShell_QCompleter(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCompleter*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isArray()) {
            QStringList _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            QtScriptShell_QCompleter* _q_cpp_result = new QtScriptShell_QCompleter(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCompleter*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QAbstractItemModel*>(context->argument(0))
            && context->argument(1).isQObject()) {
            QAbstractItemModel* _q_arg0 = qscriptvalue_cast<QAbstractItemModel*>(context->argument(0));
            QObject* _q_arg1 = context->argument(1).toQObject();
            QtScriptShell_QCompleter* _q_cpp_result = new QtScriptShell_QCompleter(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCompleter*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isArray()
            && context->argument(1).isQObject()) {
            QStringList _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            QObject* _q_arg1 = context->argument(1).toQObject();
            QtScriptShell_QCompleter* _q_cpp_result = new QtScriptShell_QCompleter(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCompleter*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QCompleter_throw_ambiguity_error_helper(context,
        qtscript_QCompleter_function_names[_id],
        qtscript_QCompleter_function_signatures[_id]);
}

static QScriptValue qtscript_QCompleter_toScriptValue(QScriptEngine *engine, QCompleter* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QCompleter_fromScriptValue(const QScriptValue &value, QCompleter* &out)
{
    out = qobject_cast<QCompleter*>(value.toQObject());
}

QScriptValue qtscript_create_QCompleter_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QCompleter*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QCompleter*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QCompleter_prototype_call, qtscript_QCompleter_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QCompleter_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QCompleter*>(engine, qtscript_QCompleter_toScriptValue, 
        qtscript_QCompleter_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QCompleter_static_call, proto, qtscript_QCompleter_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ModelSorting"),
        qtscript_create_QCompleter_ModelSorting_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("CompletionMode"),
        qtscript_create_QCompleter_CompletionMode_class(engine, ctor));
    return ctor;
}
