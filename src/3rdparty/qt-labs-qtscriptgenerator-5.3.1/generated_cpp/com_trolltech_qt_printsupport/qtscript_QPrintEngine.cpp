#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qprintengine.h>
#include <QVariant>

#include "qtscriptshell_QPrintEngine.h"

static const char * const qtscript_QPrintEngine_function_names[] = {
    "QPrintEngine"
    // static
    // prototype
    , "abort"
    , "metric"
    , "newPage"
    , "printerState"
    , "property"
    , "setProperty"
    , "toString"
};

static const char * const qtscript_QPrintEngine_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , "PaintDeviceMetric arg__1"
    , ""
    , ""
    , "PrintEnginePropertyKey key"
    , "PrintEnginePropertyKey key, Object value"
""
};

static const int qtscript_QPrintEngine_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QPrintEngine_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPrintEngine::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPrintEngine*)
Q_DECLARE_METATYPE(QtScriptShell_QPrintEngine*)
Q_DECLARE_METATYPE(QPrintEngine::PrintEnginePropertyKey)
Q_DECLARE_METATYPE(QPaintDevice::PaintDeviceMetric)
Q_DECLARE_METATYPE(QPrinter::PrinterState)

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
// QPrintEngine::PrintEnginePropertyKey
//

static const QPrintEngine::PrintEnginePropertyKey qtscript_QPrintEngine_PrintEnginePropertyKey_values[] = {
    QPrintEngine::PPK_CollateCopies
    , QPrintEngine::PPK_ColorMode
    , QPrintEngine::PPK_Creator
    , QPrintEngine::PPK_DocumentName
    , QPrintEngine::PPK_FullPage
    , QPrintEngine::PPK_NumberOfCopies
    , QPrintEngine::PPK_Orientation
    , QPrintEngine::PPK_OutputFileName
    , QPrintEngine::PPK_PageOrder
    , QPrintEngine::PPK_PageRect
    , QPrintEngine::PPK_PageSize
    , QPrintEngine::PPK_PaperRect
    , QPrintEngine::PPK_PaperSource
    , QPrintEngine::PPK_PrinterName
    , QPrintEngine::PPK_PrinterProgram
    , QPrintEngine::PPK_Resolution
    , QPrintEngine::PPK_SelectionOption
    , QPrintEngine::PPK_SupportedResolutions
    , QPrintEngine::PPK_WindowsPageSize
    , QPrintEngine::PPK_FontEmbedding
    , QPrintEngine::PPK_Duplex
    , QPrintEngine::PPK_PaperSources
    , QPrintEngine::PPK_CustomPaperSize
    , QPrintEngine::PPK_PageMargins
    , QPrintEngine::PPK_CopyCount
    , QPrintEngine::PPK_SupportsMultipleCopies
    , QPrintEngine::PPK_PaperName
    , QPrintEngine::PPK_QPageSize
    , QPrintEngine::PPK_QPageMargins
    , QPrintEngine::PPK_QPageLayout
    , QPrintEngine::PPK_CustomBase
};

static const char * const qtscript_QPrintEngine_PrintEnginePropertyKey_keys[] = {
    "PPK_CollateCopies"
    , "PPK_ColorMode"
    , "PPK_Creator"
    , "PPK_DocumentName"
    , "PPK_FullPage"
    , "PPK_NumberOfCopies"
    , "PPK_Orientation"
    , "PPK_OutputFileName"
    , "PPK_PageOrder"
    , "PPK_PageRect"
    , "PPK_PageSize"
    , "PPK_PaperRect"
    , "PPK_PaperSource"
    , "PPK_PrinterName"
    , "PPK_PrinterProgram"
    , "PPK_Resolution"
    , "PPK_SelectionOption"
    , "PPK_SupportedResolutions"
    , "PPK_WindowsPageSize"
    , "PPK_FontEmbedding"
    , "PPK_Duplex"
    , "PPK_PaperSources"
    , "PPK_CustomPaperSize"
    , "PPK_PageMargins"
    , "PPK_CopyCount"
    , "PPK_SupportsMultipleCopies"
    , "PPK_PaperName"
    , "PPK_QPageSize"
    , "PPK_QPageMargins"
    , "PPK_QPageLayout"
    , "PPK_CustomBase"
};

static QString qtscript_QPrintEngine_PrintEnginePropertyKey_toStringHelper(QPrintEngine::PrintEnginePropertyKey value)
{
    for (int i = 0; i < 31; ++i) {
        if (qtscript_QPrintEngine_PrintEnginePropertyKey_values[i] == value)
            return QString::fromLatin1(qtscript_QPrintEngine_PrintEnginePropertyKey_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QPrintEngine_PrintEnginePropertyKey_toScriptValue(QScriptEngine *engine, const QPrintEngine::PrintEnginePropertyKey &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPrintEngine"));
    return clazz.property(qtscript_QPrintEngine_PrintEnginePropertyKey_toStringHelper(value));
}

static void qtscript_QPrintEngine_PrintEnginePropertyKey_fromScriptValue(const QScriptValue &value, QPrintEngine::PrintEnginePropertyKey &out)
{
    out = qvariant_cast<QPrintEngine::PrintEnginePropertyKey>(value.toVariant());
}

static QScriptValue qtscript_construct_QPrintEngine_PrintEnginePropertyKey(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 31; ++i) {
        if (qtscript_QPrintEngine_PrintEnginePropertyKey_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QPrintEngine::PrintEnginePropertyKey>(arg));
    }
    return context->throwError(QString::fromLatin1("PrintEnginePropertyKey(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPrintEngine_PrintEnginePropertyKey_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPrintEngine::PrintEnginePropertyKey value = qscriptvalue_cast<QPrintEngine::PrintEnginePropertyKey>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPrintEngine_PrintEnginePropertyKey_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPrintEngine::PrintEnginePropertyKey value = qscriptvalue_cast<QPrintEngine::PrintEnginePropertyKey>(context->thisObject());
    return QScriptValue(engine, qtscript_QPrintEngine_PrintEnginePropertyKey_toStringHelper(value));
}

static QScriptValue qtscript_create_QPrintEngine_PrintEnginePropertyKey_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPrintEngine_PrintEnginePropertyKey,
        qtscript_QPrintEngine_PrintEnginePropertyKey_valueOf, qtscript_QPrintEngine_PrintEnginePropertyKey_toString);
    qScriptRegisterMetaType<QPrintEngine::PrintEnginePropertyKey>(engine, qtscript_QPrintEngine_PrintEnginePropertyKey_toScriptValue,
        qtscript_QPrintEngine_PrintEnginePropertyKey_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 31; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPrintEngine_PrintEnginePropertyKey_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPrintEngine_PrintEnginePropertyKey_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPrintEngine
//

static QScriptValue qtscript_QPrintEngine_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QPrintEngine* _q_self = qscriptvalue_cast<QPrintEngine*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPrintEngine.%0(): this object is not a QPrintEngine")
            .arg(qtscript_QPrintEngine_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->abort();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QPaintDevice::PaintDeviceMetric _q_arg0 = qscriptvalue_cast<QPaintDevice::PaintDeviceMetric>(context->argument(0));
        int _q_result = _q_self->metric(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->newPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QPrinter::PrinterState _q_result = _q_self->printerState();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QPrintEngine::PrintEnginePropertyKey _q_arg0 = qscriptvalue_cast<QPrintEngine::PrintEnginePropertyKey>(context->argument(0));
        QVariant _q_result = _q_self->property(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        QPrintEngine::PrintEnginePropertyKey _q_arg0 = qscriptvalue_cast<QPrintEngine::PrintEnginePropertyKey>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setProperty(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6: {
    QString result = QString::fromLatin1("QPrintEngine");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPrintEngine_throw_ambiguity_error_helper(context,
        qtscript_QPrintEngine_function_names[_id+1],
        qtscript_QPrintEngine_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPrintEngine_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPrintEngine(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPrintEngine* _q_cpp_result = new QtScriptShell_QPrintEngine();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPrintEngine*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPrintEngine_throw_ambiguity_error_helper(context,
        qtscript_QPrintEngine_function_names[_id],
        qtscript_QPrintEngine_function_signatures[_id]);
}

QScriptValue qtscript_create_QPrintEngine_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPrintEngine*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPrintEngine*)0));
    for (int i = 0; i < 7; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPrintEngine_prototype_call, qtscript_QPrintEngine_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPrintEngine_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPrintEngine*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPrintEngine_static_call, proto, qtscript_QPrintEngine_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("PrintEnginePropertyKey"),
        qtscript_create_QPrintEngine_PrintEnginePropertyKey_class(engine, ctor));
    return ctor;
}
