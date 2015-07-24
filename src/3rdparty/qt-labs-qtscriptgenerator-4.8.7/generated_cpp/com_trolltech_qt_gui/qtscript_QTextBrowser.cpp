#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtextbrowser.h>
#include <QTextEdit>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qinputcontext.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qmenu.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qprinter.h>
#include <qrect.h>
#include <qregion.h>
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstringlist.h>
#include <qstyle.h>
#include <qtextbrowser.h>
#include <qtextcursor.h>
#include <qtextdocument.h>
#include <qtextformat.h>
#include <qurl.h>
#include <qwidget.h>

#include "qtscriptshell_QTextBrowser.h"

static const char * const qtscript_QTextBrowser_function_names[] = {
    "QTextBrowser"
    // static
    // prototype
    , "backwardHistoryCount"
    , "clearHistory"
    , "forwardHistoryCount"
    , "historyTitle"
    , "historyUrl"
    , "isBackwardAvailable"
    , "isForwardAvailable"
    , "toString"
};

static const char * const qtscript_QTextBrowser_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "int arg__1"
    , "int arg__1"
    , ""
    , ""
""
};

static const int qtscript_QTextBrowser_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTextBrowser_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextBrowser::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextBrowser*)
Q_DECLARE_METATYPE(QtScriptShell_QTextBrowser*)
Q_DECLARE_METATYPE(QTextEdit*)

//
// QTextBrowser
//

static QScriptValue qtscript_QTextBrowser_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 7;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextBrowser* _q_self = qscriptvalue_cast<QTextBrowser*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextBrowser.%0(): this object is not a QTextBrowser")
            .arg(qtscript_QTextBrowser_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->backwardHistoryCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->clearHistory();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->forwardHistoryCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->historyTitle(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QUrl _q_result = _q_self->historyUrl(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isBackwardAvailable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isForwardAvailable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7: {
    QString result = QString::fromLatin1("QTextBrowser");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextBrowser_throw_ambiguity_error_helper(context,
        qtscript_QTextBrowser_function_names[_id+1],
        qtscript_QTextBrowser_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextBrowser_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextBrowser(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTextBrowser* _q_cpp_result = new QtScriptShell_QTextBrowser();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTextBrowser*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QTextBrowser* _q_cpp_result = new QtScriptShell_QTextBrowser(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTextBrowser*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextBrowser_throw_ambiguity_error_helper(context,
        qtscript_QTextBrowser_function_names[_id],
        qtscript_QTextBrowser_function_signatures[_id]);
}

static QScriptValue qtscript_QTextBrowser_toScriptValue(QScriptEngine *engine, QTextBrowser* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTextBrowser_fromScriptValue(const QScriptValue &value, QTextBrowser* &out)
{
    out = qobject_cast<QTextBrowser*>(value.toQObject());
}

QScriptValue qtscript_create_QTextBrowser_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextBrowser*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextBrowser*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QTextEdit*>()));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextBrowser_prototype_call, qtscript_QTextBrowser_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextBrowser_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTextBrowser*>(engine, qtscript_QTextBrowser_toScriptValue, 
        qtscript_QTextBrowser_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextBrowser_static_call, proto, qtscript_QTextBrowser_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
