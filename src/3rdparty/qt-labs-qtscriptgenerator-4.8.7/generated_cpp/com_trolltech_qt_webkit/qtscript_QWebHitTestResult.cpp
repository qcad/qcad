#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qwebframe.h>
#include <QVariant>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qurl.h>
#include <qwebelement.h>
#include <qwebframe.h>

static const char * const qtscript_QWebHitTestResult_function_names[] = {
    "QWebHitTestResult"
    // static
    // prototype
    , "alternateText"
    , "boundingRect"
    , "element"
    , "enclosingBlockElement"
    , "frame"
    , "imageUrl"
    , "isContentEditable"
    , "isContentSelected"
    , "isNull"
    , "linkElement"
    , "linkTargetFrame"
    , "linkText"
    , "linkTitle"
    , "linkUrl"
    , "pixmap"
    , "pos"
    , "title"
    , "toString"
};

static const char * const qtscript_QWebHitTestResult_function_signatures[] = {
    "\nQWebHitTestResult other"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QWebHitTestResult_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QWebHitTestResult_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWebHitTestResult::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWebHitTestResult)
Q_DECLARE_METATYPE(QWebHitTestResult*)
Q_DECLARE_METATYPE(QWebFrame*)

//
// QWebHitTestResult
//

static QScriptValue qtscript_QWebHitTestResult_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 17;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QWebHitTestResult* _q_self = qscriptvalue_cast<QWebHitTestResult*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWebHitTestResult.%0(): this object is not a QWebHitTestResult")
            .arg(qtscript_QWebHitTestResult_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->alternateText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->boundingRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QWebElement _q_result = _q_self->element();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QWebElement _q_result = _q_self->enclosingBlockElement();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QWebFrame* _q_result = _q_self->frame();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QUrl _q_result = _q_self->imageUrl();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isContentEditable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isContentSelected();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QWebElement _q_result = _q_self->linkElement();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QWebFrame* _q_result = _q_self->linkTargetFrame();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->linkText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QUrl _q_result = _q_self->linkTitle();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QUrl _q_result = _q_self->linkUrl();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QPixmap _q_result = _q_self->pixmap();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->title();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17: {
    QString result = QString::fromLatin1("QWebHitTestResult");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebHitTestResult_throw_ambiguity_error_helper(context,
        qtscript_QWebHitTestResult_function_names[_id+1],
        qtscript_QWebHitTestResult_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWebHitTestResult_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWebHitTestResult(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QWebHitTestResult _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWebHitTestResult _q_arg0 = qscriptvalue_cast<QWebHitTestResult>(context->argument(0));
        QWebHitTestResult _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebHitTestResult_throw_ambiguity_error_helper(context,
        qtscript_QWebHitTestResult_function_names[_id],
        qtscript_QWebHitTestResult_function_signatures[_id]);
}

QScriptValue qtscript_create_QWebHitTestResult_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWebHitTestResult*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWebHitTestResult*)0));
    for (int i = 0; i < 18; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWebHitTestResult_prototype_call, qtscript_QWebHitTestResult_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWebHitTestResult_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QWebHitTestResult>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QWebHitTestResult*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWebHitTestResult_static_call, proto, qtscript_QWebHitTestResult_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
