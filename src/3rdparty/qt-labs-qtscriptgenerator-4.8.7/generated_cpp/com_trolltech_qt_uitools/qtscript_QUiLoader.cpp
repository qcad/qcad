#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <quiloader.h>
#include <QVariant>
#include <qaction.h>
#include <qactiongroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdir.h>
#include <qiodevice.h>
#include <qlayout.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>
#include <quiloader.h>
#include <qwidget.h>

#include "qtscriptshell_QUiLoader.h"

static const char * const qtscript_QUiLoader_function_names[] = {
    "QUiLoader"
    // static
    // prototype
    , "addPluginPath"
    , "availableLayouts"
    , "availableWidgets"
    , "clearPluginPaths"
    , "createAction"
    , "createActionGroup"
    , "createLayout"
    , "createWidget"
    , "isLanguageChangeEnabled"
    , "isScriptingEnabled"
    , "isTranslationEnabled"
    , "load"
    , "pluginPaths"
    , "setLanguageChangeEnabled"
    , "setScriptingEnabled"
    , "setTranslationEnabled"
    , "setWorkingDirectory"
    , "workingDirectory"
    , "toString"
};

static const char * const qtscript_QUiLoader_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "String path"
    , ""
    , ""
    , ""
    , "QObject parent, String name"
    , "QObject parent, String name"
    , "String className, QObject parent, String name"
    , "String className, QWidget parent, String name"
    , ""
    , ""
    , ""
    , "QIODevice device, QWidget parentWidget"
    , ""
    , "bool enabled"
    , "bool enabled"
    , "bool enabled"
    , "QDir dir"
    , ""
""
};

static const int qtscript_QUiLoader_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
    , 0
    , 2
    , 2
    , 3
    , 3
    , 0
    , 0
    , 0
    , 2
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QUiLoader_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QUiLoader::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QUiLoader*)
Q_DECLARE_METATYPE(QtScriptShell_QUiLoader*)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QActionGroup*)
Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QDir)

//
// QUiLoader
//

static QScriptValue qtscript_QUiLoader_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 18;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QUiLoader* _q_self = qscriptvalue_cast<QUiLoader*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QUiLoader.%0(): this object is not a QUiLoader")
            .arg(qtscript_QUiLoader_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->addPluginPath(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->availableLayouts();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->availableWidgets();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        _q_self->clearPluginPaths();
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QAction* _q_result = _q_self->createAction();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QAction* _q_result = _q_self->createAction(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QString _q_arg1 = context->argument(1).toString();
        QAction* _q_result = _q_self->createAction(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QActionGroup* _q_result = _q_self->createActionGroup();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QActionGroup* _q_result = _q_self->createActionGroup(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QString _q_arg1 = context->argument(1).toString();
        QActionGroup* _q_result = _q_self->createActionGroup(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QLayout* _q_result = _q_self->createLayout(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QLayout* _q_result = _q_self->createLayout(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QString _q_arg2 = context->argument(2).toString();
        QLayout* _q_result = _q_self->createLayout(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QWidget* _q_result = _q_self->createWidget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QWidget* _q_result = _q_self->createWidget(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        QWidget* _q_result = _q_self->createWidget(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isLanguageChangeEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isScriptingEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isTranslationEnabled();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        QWidget* _q_result = _q_self->load(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QIODevice* _q_arg0 = qscriptvalue_cast<QIODevice*>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QWidget* _q_result = _q_self->load(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->pluginPaths();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setLanguageChangeEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setScriptingEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setTranslationEnabled(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QDir _q_arg0 = qscriptvalue_cast<QDir>(context->argument(0));
        _q_self->setWorkingDirectory(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QDir _q_result = _q_self->workingDirectory();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18: {
    QString result = QString::fromLatin1("QUiLoader");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUiLoader_throw_ambiguity_error_helper(context,
        qtscript_QUiLoader_function_names[_id+1],
        qtscript_QUiLoader_function_signatures[_id+1]);
}

static QScriptValue qtscript_QUiLoader_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QUiLoader(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QUiLoader* _q_cpp_result = new QtScriptShell_QUiLoader();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QUiLoader*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QUiLoader* _q_cpp_result = new QtScriptShell_QUiLoader(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QUiLoader*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QUiLoader_throw_ambiguity_error_helper(context,
        qtscript_QUiLoader_function_names[_id],
        qtscript_QUiLoader_function_signatures[_id]);
}

static QScriptValue qtscript_QUiLoader_toScriptValue(QScriptEngine *engine, QUiLoader* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QUiLoader_fromScriptValue(const QScriptValue &value, QUiLoader* &out)
{
    out = qobject_cast<QUiLoader*>(value.toQObject());
}

QScriptValue qtscript_create_QUiLoader_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QUiLoader*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QUiLoader*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 19; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QUiLoader_prototype_call, qtscript_QUiLoader_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QUiLoader_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QUiLoader*>(engine, qtscript_QUiLoader_toScriptValue, 
        qtscript_QUiLoader_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QUiLoader_static_call, proto, qtscript_QUiLoader_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
