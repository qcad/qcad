#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qwizard.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
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
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>
#include <qwizard.h>

#include "qtscriptshell_QWizardPage.h"

static const char * const qtscript_QWizardPage_function_names[] = {
    "QWizardPage"
    // static
    // prototype
    , "buttonText"
    , "cleanupPage"
    , "initializePage"
    , "isCommitPage"
    , "isComplete"
    , "isFinalPage"
    , "nextId"
    , "pixmap"
    , "setButtonText"
    , "setCommitPage"
    , "setFinalPage"
    , "setPixmap"
    , "validatePage"
    , "toString"
};

static const char * const qtscript_QWizardPage_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "WizardButton which"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "WizardPixmap which"
    , "WizardButton which, String text"
    , "bool commitPage"
    , "bool finalPage"
    , "WizardPixmap which, QPixmap pixmap"
    , ""
""
};

static const int qtscript_QWizardPage_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 2
    , 1
    , 1
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QWizardPage_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWizardPage::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWizardPage*)
Q_DECLARE_METATYPE(QtScriptShell_QWizardPage*)
Q_DECLARE_METATYPE(QWizard::WizardButton)
Q_DECLARE_METATYPE(QWizard::WizardPixmap)

//
// QWizardPage
//

static QScriptValue qtscript_QWizardPage_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 13;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QWizardPage* _q_self = qscriptvalue_cast<QWizardPage*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWizardPage.%0(): this object is not a QWizardPage")
            .arg(qtscript_QWizardPage_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QWizard::WizardButton _q_arg0 = qscriptvalue_cast<QWizard::WizardButton>(context->argument(0));
        QString _q_result = _q_self->buttonText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->cleanupPage();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->initializePage();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isCommitPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isComplete();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isFinalPage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->nextId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QWizard::WizardPixmap _q_arg0 = qscriptvalue_cast<QWizard::WizardPixmap>(context->argument(0));
        QPixmap _q_result = _q_self->pixmap(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        QWizard::WizardButton _q_arg0 = qscriptvalue_cast<QWizard::WizardButton>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setButtonText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setCommitPage(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setFinalPage(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        QWizard::WizardPixmap _q_arg0 = qscriptvalue_cast<QWizard::WizardPixmap>(context->argument(0));
        QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
        _q_self->setPixmap(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->validatePage();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13: {
    QString result = QString::fromLatin1("QWizardPage");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWizardPage_throw_ambiguity_error_helper(context,
        qtscript_QWizardPage_function_names[_id+1],
        qtscript_QWizardPage_function_signatures[_id+1]);
}

static QScriptValue qtscript_QWizardPage_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QWizardPage(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QWizardPage* _q_cpp_result = new QtScriptShell_QWizardPage();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWizardPage*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QWizardPage* _q_cpp_result = new QtScriptShell_QWizardPage(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QWizardPage*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QWizardPage_throw_ambiguity_error_helper(context,
        qtscript_QWizardPage_function_names[_id],
        qtscript_QWizardPage_function_signatures[_id]);
}

static QScriptValue qtscript_QWizardPage_toScriptValue(QScriptEngine *engine, QWizardPage* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QWizardPage_fromScriptValue(const QScriptValue &value, QWizardPage* &out)
{
    out = qobject_cast<QWizardPage*>(value.toQObject());
}

QScriptValue qtscript_create_QWizardPage_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWizardPage*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QWizardPage*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 14; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWizardPage_prototype_call, qtscript_QWizardPage_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWizardPage_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QWizardPage*>(engine, qtscript_QWizardPage_toScriptValue, 
        qtscript_QWizardPage_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QWizardPage_static_call, proto, qtscript_QWizardPage_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
