#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qabstractbutton.h>
#include <QVariant>
#include <qabstractbutton.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbuttongroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
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

#include "qtscriptshell_QAbstractButton.h"

static const char * const qtscript_QAbstractButton_function_names[] = {
    "QAbstractButton"
    // static
    // prototype
    , "group"
    , "toString"
};

static const char * const qtscript_QAbstractButton_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
""
};

static const int qtscript_QAbstractButton_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
};

static QScriptValue qtscript_QAbstractButton_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractButton::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractButton*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractButton*)
Q_DECLARE_METATYPE(QButtonGroup*)
Q_DECLARE_METATYPE(QWidget*)

//
// QAbstractButton
//

static QScriptValue qtscript_QAbstractButton_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractButton* _q_self = qscriptvalue_cast<QAbstractButton*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractButton.%0(): this object is not a QAbstractButton")
            .arg(qtscript_QAbstractButton_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QButtonGroup* _q_result = _q_self->group();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("QAbstractButton");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractButton_throw_ambiguity_error_helper(context,
        qtscript_QAbstractButton_function_names[_id+1],
        qtscript_QAbstractButton_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractButton_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractButton(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractButton* _q_cpp_result = new QtScriptShell_QAbstractButton();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QAbstractButton* _q_cpp_result = new QtScriptShell_QAbstractButton(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractButton_throw_ambiguity_error_helper(context,
        qtscript_QAbstractButton_function_names[_id],
        qtscript_QAbstractButton_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractButton_toScriptValue(QScriptEngine *engine, QAbstractButton* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractButton_fromScriptValue(const QScriptValue &value, QAbstractButton* &out)
{
    out = qobject_cast<QAbstractButton*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractButton_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractButton*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractButton*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractButton_prototype_call, qtscript_QAbstractButton_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractButton_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractButton*>(engine, qtscript_QAbstractButton_toScriptValue, 
        qtscript_QAbstractButton_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractButton_static_call, proto, qtscript_QAbstractButton_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
