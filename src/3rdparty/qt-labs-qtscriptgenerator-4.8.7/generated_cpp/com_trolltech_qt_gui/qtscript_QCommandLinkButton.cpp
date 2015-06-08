#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qcommandlinkbutton.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbuttongroup.h>
#include <qbytearray.h>
#include <qcommandlinkbutton.h>
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
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QCommandLinkButton.h"

static const char * const qtscript_QCommandLinkButton_function_names[] = {
    "QCommandLinkButton"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QCommandLinkButton_function_signatures[] = {
    "QWidget parent\nString text, QWidget parent\nString text, String description, QWidget parent"
    // static
    // prototype
""
};

static const int qtscript_QCommandLinkButton_function_lengths[] = {
    3
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QCommandLinkButton_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QCommandLinkButton::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QCommandLinkButton*)
Q_DECLARE_METATYPE(QtScriptShell_QCommandLinkButton*)
Q_DECLARE_METATYPE(QPushButton*)

//
// QCommandLinkButton
//

static QScriptValue qtscript_QCommandLinkButton_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QCommandLinkButton* _q_self = qscriptvalue_cast<QCommandLinkButton*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QCommandLinkButton.%0(): this object is not a QCommandLinkButton")
            .arg(qtscript_QCommandLinkButton_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QCommandLinkButton");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QCommandLinkButton_throw_ambiguity_error_helper(context,
        qtscript_QCommandLinkButton_function_names[_id+1],
        qtscript_QCommandLinkButton_function_signatures[_id+1]);
}

static QScriptValue qtscript_QCommandLinkButton_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QCommandLinkButton(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QCommandLinkButton* _q_cpp_result = new QtScriptShell_QCommandLinkButton();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCommandLinkButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QCommandLinkButton* _q_cpp_result = new QtScriptShell_QCommandLinkButton(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCommandLinkButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QCommandLinkButton* _q_cpp_result = new QtScriptShell_QCommandLinkButton(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCommandLinkButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QtScriptShell_QCommandLinkButton* _q_cpp_result = new QtScriptShell_QCommandLinkButton(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCommandLinkButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QString _q_arg1 = context->argument(1).toString();
            QtScriptShell_QCommandLinkButton* _q_cpp_result = new QtScriptShell_QCommandLinkButton(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCommandLinkButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QString _q_arg1 = context->argument(1).toString();
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        QtScriptShell_QCommandLinkButton* _q_cpp_result = new QtScriptShell_QCommandLinkButton(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QCommandLinkButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QCommandLinkButton_throw_ambiguity_error_helper(context,
        qtscript_QCommandLinkButton_function_names[_id],
        qtscript_QCommandLinkButton_function_signatures[_id]);
}

static QScriptValue qtscript_QCommandLinkButton_toScriptValue(QScriptEngine *engine, QCommandLinkButton* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QCommandLinkButton_fromScriptValue(const QScriptValue &value, QCommandLinkButton* &out)
{
    out = qobject_cast<QCommandLinkButton*>(value.toQObject());
}

QScriptValue qtscript_create_QCommandLinkButton_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QCommandLinkButton*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QCommandLinkButton*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QPushButton*>()));

    qScriptRegisterMetaType<QCommandLinkButton*>(engine, qtscript_QCommandLinkButton_toScriptValue, 
        qtscript_QCommandLinkButton_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QCommandLinkButton_static_call, proto, qtscript_QCommandLinkButton_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
