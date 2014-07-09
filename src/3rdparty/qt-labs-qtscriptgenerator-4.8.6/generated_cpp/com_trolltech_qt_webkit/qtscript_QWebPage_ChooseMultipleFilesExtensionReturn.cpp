#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qwebpage.h>
#include <QVariant>

#include "qtscriptshell_QWebPage_ChooseMultipleFilesExtensionReturn.h"

static const char * const qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_function_names[] = {
    "QWebPage_ChooseMultipleFilesExtensionReturn"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_function_signatures[] = {
    ""
    // static
    // prototype
""
};

static const int qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_function_lengths[] = {
    0
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWebPage_ChooseMultipleFilesExtensionReturn::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWebPage::ChooseMultipleFilesExtensionReturn*)
Q_DECLARE_METATYPE(QtScriptShell_QWebPage_ChooseMultipleFilesExtensionReturn*)
Q_DECLARE_METATYPE(QWebPage::ExtensionReturn*)

//
// QWebPage_ChooseMultipleFilesExtensionReturn
//

static QScriptValue qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QWebPage::ChooseMultipleFilesExtensionReturn* _q_self = qscriptvalue_cast<QWebPage::ChooseMultipleFilesExtensionReturn*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWebPage_ChooseMultipleFilesExtensionReturn.%0(): this object is not a QWebPage_ChooseMultipleFilesExtensionReturn")
            .arg(qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QWebPage_ChooseMultipleFilesExtensionReturn");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_throw_ambiguity_error_helper(context,
        qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_function_names[_id+1],
        qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWebPage_ChooseMultipleFilesExtensionReturn(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QWebPage_ChooseMultipleFilesExtensionReturn* _q_cpp_result = new QtScriptShell_QWebPage_ChooseMultipleFilesExtensionReturn();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QWebPage::ChooseMultipleFilesExtensionReturn*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_throw_ambiguity_error_helper(context,
        qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_function_names[_id],
        qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_function_signatures[_id]);
}

QScriptValue qtscript_create_QWebPage_ChooseMultipleFilesExtensionReturn_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWebPage::ChooseMultipleFilesExtensionReturn*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWebPage::ChooseMultipleFilesExtensionReturn*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWebPage::ExtensionReturn*>()));

    engine->setDefaultPrototype(qMetaTypeId<QWebPage::ChooseMultipleFilesExtensionReturn*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_static_call, proto, qtscript_QWebPage_ChooseMultipleFilesExtensionReturn_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
