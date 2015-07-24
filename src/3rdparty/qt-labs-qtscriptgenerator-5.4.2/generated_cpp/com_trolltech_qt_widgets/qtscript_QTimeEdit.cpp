#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdatetimeedit.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcalendarwidget.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdatetime.h>
#include <qdatetimeedit.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlineedit.h>
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
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QTimeEdit.h"

static const char * const qtscript_QTimeEdit_function_names[] = {
    "QTimeEdit"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QTimeEdit_function_signatures[] = {
    "QWidget parent\nQTime time, QWidget parent"
    // static
    // prototype
""
};

static const int qtscript_QTimeEdit_function_lengths[] = {
    2
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QTimeEdit_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTimeEdit::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTimeEdit*)
Q_DECLARE_METATYPE(QtScriptShell_QTimeEdit*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QDateTimeEdit*)

//
// QTimeEdit
//

static QScriptValue qtscript_QTimeEdit_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QTimeEdit* _q_self = qscriptvalue_cast<QTimeEdit*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTimeEdit.%0(): this object is not a QTimeEdit")
            .arg(qtscript_QTimeEdit_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QTimeEdit");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTimeEdit_throw_ambiguity_error_helper(context,
        qtscript_QTimeEdit_function_names[_id+1],
        qtscript_QTimeEdit_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTimeEdit_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTimeEdit(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTimeEdit* _q_cpp_result = new QtScriptShell_QTimeEdit();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTimeEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QTimeEdit* _q_cpp_result = new QtScriptShell_QTimeEdit(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTimeEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QTime>() == context->argument(0).toVariant().userType())) {
            QTime _q_arg0 = qscriptvalue_cast<QTime>(context->argument(0));
            QtScriptShell_QTimeEdit* _q_cpp_result = new QtScriptShell_QTimeEdit(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTimeEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QTime _q_arg0 = qscriptvalue_cast<QTime>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QTimeEdit* _q_cpp_result = new QtScriptShell_QTimeEdit(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTimeEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTimeEdit_throw_ambiguity_error_helper(context,
        qtscript_QTimeEdit_function_names[_id],
        qtscript_QTimeEdit_function_signatures[_id]);
}

static QScriptValue qtscript_QTimeEdit_toScriptValue(QScriptEngine *engine, QTimeEdit* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTimeEdit_fromScriptValue(const QScriptValue &value, QTimeEdit* &out)
{
    out = qobject_cast<QTimeEdit*>(value.toQObject());
}

QScriptValue qtscript_create_QTimeEdit_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTimeEdit*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTimeEdit*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDateTimeEdit*>()));

    qScriptRegisterMetaType<QTimeEdit*>(engine, qtscript_QTimeEdit_toScriptValue, 
        qtscript_QTimeEdit_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTimeEdit_static_call, proto, qtscript_QTimeEdit_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
