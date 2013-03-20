#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicswebview.h>
#include <QVariant>
#include <qaction.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsitem.h>
#include <qgraphicslayout.h>
#include <qgraphicslayoutitem.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qgraphicstransform.h>
#include <qgraphicswidget.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlist.h>
#include <qnetworkrequest.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qtransform.h>
#include <qurl.h>
#include <qwebpage.h>
#include <qwebsettings.h>
#include <qwidget.h>

#include "qtscriptshell_QGraphicsWebView.h"

static const char * const qtscript_QGraphicsWebView_function_names[] = {
    "QGraphicsWebView"
    // static
    // prototype
    , "findText"
    , "history"
    , "load"
    , "page"
    , "pageAction"
    , "setContent"
    , "setHtml"
    , "setPage"
    , "setRenderHint"
    , "settings"
    , "triggerPageAction"
    , "toString"
};

static const char * const qtscript_QGraphicsWebView_function_signatures[] = {
    "QGraphicsItem parent"
    // static
    // prototype
    , "String subString, FindFlags options"
    , ""
    , "QNetworkRequest request, Operation operation, QByteArray body\nQUrl url"
    , ""
    , "WebAction action"
    , "QByteArray data, String mimeType, QUrl baseUrl"
    , "String html, QUrl baseUrl"
    , "QWebPage arg__1"
    , "RenderHint arg__1, bool enabled"
    , ""
    , "WebAction action, bool checked"
""
};

static const int qtscript_QGraphicsWebView_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 0
    , 3
    , 0
    , 1
    , 3
    , 2
    , 1
    , 2
    , 0
    , 2
    , 0
};

static QScriptValue qtscript_QGraphicsWebView_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsWebView::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsWebView*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsWebView*)
Q_DECLARE_METATYPE(QFlags<QWebPage::FindFlag>)
Q_DECLARE_METATYPE(QWebHistory*)
Q_DECLARE_METATYPE(QNetworkAccessManager::Operation)
Q_DECLARE_METATYPE(QWebPage*)
Q_DECLARE_METATYPE(QWebPage::WebAction)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QPainter::RenderHint)
Q_DECLARE_METATYPE(QWebSettings*)
Q_DECLARE_METATYPE(QGraphicsWidget*)

//
// QGraphicsWebView
//

static QScriptValue qtscript_QGraphicsWebView_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 11;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsWebView* _q_self = qscriptvalue_cast<QGraphicsWebView*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsWebView.%0(): this object is not a QGraphicsWebView")
            .arg(qtscript_QGraphicsWebView_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->findText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<QWebPage::FindFlag> _q_arg1 = qscriptvalue_cast<QFlags<QWebPage::FindFlag> >(context->argument(1));
        bool _q_result = _q_self->findText(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QWebHistory* _q_result = _q_self->history();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
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

    case 3:
    if (context->argumentCount() == 0) {
        QWebPage* _q_result = _q_self->page();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QWebPage::WebAction _q_arg0 = qscriptvalue_cast<QWebPage::WebAction>(context->argument(0));
        QAction* _q_result = _q_self->pageAction(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
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

    case 6:
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

    case 7:
    if (context->argumentCount() == 1) {
        QWebPage* _q_arg0 = qscriptvalue_cast<QWebPage*>(context->argument(0));
        _q_self->setPage(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QPainter::RenderHint _q_arg0 = qscriptvalue_cast<QPainter::RenderHint>(context->argument(0));
        _q_self->setRenderHint(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QPainter::RenderHint _q_arg0 = qscriptvalue_cast<QPainter::RenderHint>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setRenderHint(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QWebSettings* _q_result = _q_self->settings();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QWebPage::WebAction _q_arg0 = qscriptvalue_cast<QWebPage::WebAction>(context->argument(0));
        _q_self->triggerPageAction(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QWebPage::WebAction _q_arg0 = qscriptvalue_cast<QWebPage::WebAction>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->triggerPageAction(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11: {
    QString result = QString::fromLatin1("QGraphicsWebView");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsWebView_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsWebView_function_names[_id+1],
        qtscript_QGraphicsWebView_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsWebView_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsWebView(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsWebView* _q_cpp_result = new QtScriptShell_QGraphicsWebView();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsWebView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
        QtScriptShell_QGraphicsWebView* _q_cpp_result = new QtScriptShell_QGraphicsWebView(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsWebView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsWebView_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsWebView_function_names[_id],
        qtscript_QGraphicsWebView_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsWebView_toScriptValue(QScriptEngine *engine, QGraphicsWebView* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsWebView_fromScriptValue(const QScriptValue &value, QGraphicsWebView* &out)
{
    out = qobject_cast<QGraphicsWebView*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsWebView_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsWebView*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsWebView*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsWidget*>()));
    for (int i = 0; i < 12; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsWebView_prototype_call, qtscript_QGraphicsWebView_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsWebView_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGraphicsWebView*>(engine, qtscript_QGraphicsWebView_toScriptValue, 
        qtscript_QGraphicsWebView_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsWebView_static_call, proto, qtscript_QGraphicsWebView_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
