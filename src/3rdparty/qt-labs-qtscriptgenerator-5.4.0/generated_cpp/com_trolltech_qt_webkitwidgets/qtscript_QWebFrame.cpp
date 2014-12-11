#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qwebframe.h>
#include <QVariant>
#include <QNetworkRequest>
#include <QAction>
#include <QEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <qwebelement.h>
#include <qwebframe.h>
#include <qwebpage.h>

static const char * const qtscript_QWebFrame_function_names[] = {
    "QWebFrame"
    // static
    // prototype
    , "childFrames"
    , "documentElement"
    , "event"
    , "findFirstElement"
    , "frameName"
    , "geometry"
    , "hitTestContent"
    , "load"
    , "metaData"
    , "page"
    , "parentFrame"
    , "pos"
    , "render"
    , "scroll"
    , "scrollBarGeometry"
    , "scrollBarMaximum"
    , "scrollBarMinimum"
    , "scrollBarPolicy"
    , "scrollBarValue"
    , "scrollToAnchor"
    , "setContent"
    , "setFocus"
    , "setHtml"
    , "setScrollBarPolicy"
    , "setScrollBarValue"
    , "toHtml"
    , "toPlainText"
    , "toString"
};

static const char * const qtscript_QWebFrame_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , "QEvent arg__1"
    , "String selectorQuery"
    , ""
    , ""
    , "QPoint pos"
    , "QNetworkRequest request, Operation operation, QByteArray body\nQUrl url"
    , ""
    , ""
    , ""
    , ""
    , "QPainter arg__1, QRegion clip"
    , "int arg__1, int arg__2"
    , "Orientation orientation"
    , "Orientation orientation"
    , "Orientation orientation"
    , "Orientation orientation"
    , "Orientation orientation"
    , "String anchor"
    , "QByteArray data, String mimeType, QUrl baseUrl"
    , ""
    , "String html, QUrl baseUrl"
    , "Orientation orientation, ScrollBarPolicy policy"
    , "Orientation orientation, int value"
    , ""
    , ""
""
};

static const int qtscript_QWebFrame_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 1
    , 3
    , 0
    , 0
    , 0
    , 0
    , 2
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 3
    , 0
    , 2
    , 2
    , 2
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QWebFrame_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWebFrame::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWebFrame*)
Q_DECLARE_METATYPE(QWebFrame::RenderLayer)
Q_DECLARE_METATYPE(QList<QWebFrame* >)
//Q_DECLARE_METATYPE(QWebElement)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QWebHitTestResult)
//Q_DECLARE_METATYPE(QNetworkRequest)
Q_DECLARE_METATYPE(QNetworkAccessManager::Operation)
template <> \
struct QMetaTypeId< QMultiMap<QString,QString > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QMultiMap<QString,QString > >("QMultiMap<QString,QString >")); \
        return metatype_id.load(); \
    } \
};
Q_DECLARE_METATYPE(QWebPage*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(Qt::ScrollBarPolicy)

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
// QWebFrame::RenderLayer
//

static const QWebFrame::RenderLayer qtscript_QWebFrame_RenderLayer_values[] = {
    QWebFrame::ContentsLayer
    , QWebFrame::ScrollBarLayer
    , QWebFrame::PanIconLayer
    , QWebFrame::AllLayers
};

static const char * const qtscript_QWebFrame_RenderLayer_keys[] = {
    "ContentsLayer"
    , "ScrollBarLayer"
    , "PanIconLayer"
    , "AllLayers"
};

static QString qtscript_QWebFrame_RenderLayer_toStringHelper(QWebFrame::RenderLayer value)
{
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QWebFrame_RenderLayer_values[i] == value)
            return QString::fromLatin1(qtscript_QWebFrame_RenderLayer_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QWebFrame_RenderLayer_toScriptValue(QScriptEngine *engine, const QWebFrame::RenderLayer &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QWebFrame"));
    return clazz.property(qtscript_QWebFrame_RenderLayer_toStringHelper(value));
}

static void qtscript_QWebFrame_RenderLayer_fromScriptValue(const QScriptValue &value, QWebFrame::RenderLayer &out)
{
    out = qvariant_cast<QWebFrame::RenderLayer>(value.toVariant());
}

static QScriptValue qtscript_construct_QWebFrame_RenderLayer(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 4; ++i) {
        if (qtscript_QWebFrame_RenderLayer_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QWebFrame::RenderLayer>(arg));
    }
    return context->throwError(QString::fromLatin1("RenderLayer(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QWebFrame_RenderLayer_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QWebFrame::RenderLayer value = qscriptvalue_cast<QWebFrame::RenderLayer>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QWebFrame_RenderLayer_toString(QScriptContext *context, QScriptEngine *engine)
{
    QWebFrame::RenderLayer value = qscriptvalue_cast<QWebFrame::RenderLayer>(context->thisObject());
    return QScriptValue(engine, qtscript_QWebFrame_RenderLayer_toStringHelper(value));
}

static QScriptValue qtscript_create_QWebFrame_RenderLayer_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QWebFrame_RenderLayer,
        qtscript_QWebFrame_RenderLayer_valueOf, qtscript_QWebFrame_RenderLayer_toString);
    qScriptRegisterMetaType<QWebFrame::RenderLayer>(engine, qtscript_QWebFrame_RenderLayer_toScriptValue,
        qtscript_QWebFrame_RenderLayer_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QWebFrame_RenderLayer_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QWebFrame_RenderLayer_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QWebFrame
//

static QScriptValue qtscript_QWebFrame_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QWebFrame* _q_self = qscriptvalue_cast<QWebFrame*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWebFrame.%0(): this object is not a QWebFrame")
            .arg(qtscript_QWebFrame_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QList<QWebFrame* > _q_result = _q_self->childFrames();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWebElement _q_result = _q_self->documentElement();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QEvent* _q_arg0 = qscriptvalue_cast<QEvent*>(context->argument(0));
        bool _q_result = _q_self->event(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QWebElement _q_result = _q_self->findFirstElement(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->frameName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->geometry();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QWebHitTestResult _q_result = _q_self->hitTestContent(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QNetworkRequest>() == context->argument(0).toVariant().userType())) {
            QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
            _q_self->load(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QUrl>() == context->argument(0).toVariant().userType())) {
            QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
            _q_self->load(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
        QNetworkAccessManager::Operation _q_arg1 = qscriptvalue_cast<QNetworkAccessManager::Operation>(context->argument(1));
        _q_self->load(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QNetworkRequest _q_arg0 = qscriptvalue_cast<QNetworkRequest>(context->argument(0));
        QNetworkAccessManager::Operation _q_arg1 = qscriptvalue_cast<QNetworkAccessManager::Operation>(context->argument(1));
        QByteArray _q_arg2 = qscriptvalue_cast<QByteArray>(context->argument(2));
        _q_self->load(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QMultiMap<QString,QString > _q_result = _q_self->metaData();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QWebPage* _q_result = _q_self->page();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QWebFrame* _q_result = _q_self->parentFrame();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        _q_self->render(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRegion _q_arg1 = qscriptvalue_cast<QRegion>(context->argument(1));
        _q_self->render(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->scroll(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        QRect _q_result = _q_self->scrollBarGeometry(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        int _q_result = _q_self->scrollBarMaximum(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        int _q_result = _q_self->scrollBarMinimum(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        Qt::ScrollBarPolicy _q_result = _q_self->scrollBarPolicy(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        int _q_result = _q_self->scrollBarValue(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->scrollToAnchor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        _q_self->setContent(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setContent(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QUrl _q_arg2 = qscriptvalue_cast<QUrl>(context->argument(2));
        _q_self->setContent(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        _q_self->setFocus();
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setHtml(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QUrl _q_arg1 = qscriptvalue_cast<QUrl>(context->argument(1));
        _q_self->setHtml(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 2) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        Qt::ScrollBarPolicy _q_arg1 = qscriptvalue_cast<Qt::ScrollBarPolicy>(context->argument(1));
        _q_self->setScrollBarPolicy(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 2) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setScrollBarValue(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toHtml();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toPlainText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 27: {
    QString result = QString::fromLatin1("QWebFrame");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebFrame_throw_ambiguity_error_helper(context,
        qtscript_QWebFrame_function_names[_id+1],
        qtscript_QWebFrame_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWebFrame_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QWebFrame cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWebFrame_throw_ambiguity_error_helper(context,
        qtscript_QWebFrame_function_names[_id],
        qtscript_QWebFrame_function_signatures[_id]);
}

QScriptValue qtscript_create_QWebFrame_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWebFrame*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWebFrame*)0));
    for (int i = 0; i < 28; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWebFrame_prototype_call, qtscript_QWebFrame_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWebFrame_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QWebFrame*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWebFrame_static_call, proto, qtscript_QWebFrame_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("RenderLayer"),
        qtscript_create_QWebFrame_RenderLayer_class(engine, ctor));
    return ctor;
}
