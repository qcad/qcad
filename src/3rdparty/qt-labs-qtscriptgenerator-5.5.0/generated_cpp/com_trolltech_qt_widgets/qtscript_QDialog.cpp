#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdialog.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdialog.h>
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

#include "qtscriptshell_QDialog.h"

static const char * const qtscript_QDialog_function_names[] = {
    "QDialog"
    // static
    // prototype
    , "minimumSizeHint"
    , "result"
    , "setResult"
    , "setVisible"
    , "sizeHint"
    , "toString"
};

static const char * const qtscript_QDialog_function_signatures[] = {
    "QWidget parent, WindowFlags f"
    // static
    // prototype
    , ""
    , ""
    , "int r"
    , "bool visible"
    , ""
""
};

static const int qtscript_QDialog_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QDialog_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDialog::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDialog*)
Q_DECLARE_METATYPE(QtScriptShell_QDialog*)
Q_DECLARE_METATYPE(QDialog::DialogCode)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)

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
// QDialog::DialogCode
//

static const QDialog::DialogCode qtscript_QDialog_DialogCode_values[] = {
    QDialog::Rejected
    , QDialog::Accepted
};

static const char * const qtscript_QDialog_DialogCode_keys[] = {
    "Rejected"
    , "Accepted"
};

static QString qtscript_QDialog_DialogCode_toStringHelper(QDialog::DialogCode value)
{
    if ((value >= QDialog::Rejected) && (value <= QDialog::Accepted))
        return qtscript_QDialog_DialogCode_keys[static_cast<int>(value)-static_cast<int>(QDialog::Rejected)];
    return QString();
}

static QScriptValue qtscript_QDialog_DialogCode_toScriptValue(QScriptEngine *engine, const QDialog::DialogCode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QDialog"));
    return clazz.property(qtscript_QDialog_DialogCode_toStringHelper(value));
}

static void qtscript_QDialog_DialogCode_fromScriptValue(const QScriptValue &value, QDialog::DialogCode &out)
{
    out = qvariant_cast<QDialog::DialogCode>(value.toVariant());
}

static QScriptValue qtscript_construct_QDialog_DialogCode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QDialog::Rejected) && (arg <= QDialog::Accepted))
        return qScriptValueFromValue(engine,  static_cast<QDialog::DialogCode>(arg));
    return context->throwError(QString::fromLatin1("DialogCode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QDialog_DialogCode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QDialog::DialogCode value = qscriptvalue_cast<QDialog::DialogCode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QDialog_DialogCode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QDialog::DialogCode value = qscriptvalue_cast<QDialog::DialogCode>(context->thisObject());
    return QScriptValue(engine, qtscript_QDialog_DialogCode_toStringHelper(value));
}

static QScriptValue qtscript_create_QDialog_DialogCode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QDialog_DialogCode,
        qtscript_QDialog_DialogCode_valueOf, qtscript_QDialog_DialogCode_toString);
    qScriptRegisterMetaType<QDialog::DialogCode>(engine, qtscript_QDialog_DialogCode_toScriptValue,
        qtscript_QDialog_DialogCode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QDialog_DialogCode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QDialog_DialogCode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QDialog
//

static QScriptValue qtscript_QDialog_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDialog* _q_self = qscriptvalue_cast<QDialog*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDialog.%0(): this object is not a QDialog")
            .arg(qtscript_QDialog_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->result();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setResult(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setVisible(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QDialog");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDialog_throw_ambiguity_error_helper(context,
        qtscript_QDialog_function_names[_id+1],
        qtscript_QDialog_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDialog_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QDialog(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QDialog* _q_cpp_result = new QtScriptShell_QDialog();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QDialog* _q_cpp_result = new QtScriptShell_QDialog(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QtScriptShell_QDialog* _q_cpp_result = new QtScriptShell_QDialog(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QDialog_throw_ambiguity_error_helper(context,
        qtscript_QDialog_function_names[_id],
        qtscript_QDialog_function_signatures[_id]);
}

static QScriptValue qtscript_QDialog_toScriptValue(QScriptEngine *engine, QDialog* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QDialog_fromScriptValue(const QScriptValue &value, QDialog* &out)
{
    out = qobject_cast<QDialog*>(value.toQObject());
}

QScriptValue qtscript_create_QDialog_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDialog*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDialog*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDialog_prototype_call, qtscript_QDialog_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDialog_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QDialog*>(engine, qtscript_QDialog_toScriptValue, 
        qtscript_QDialog_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDialog_static_call, proto, qtscript_QDialog_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("DialogCode"),
        qtscript_create_QDialog_DialogCode_class(engine, ctor));
    return ctor;
}
