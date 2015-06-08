#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qlineedit.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcompleter.h>
#include <qcoreevent.h>
#include <qcursor.h>
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
#include <qmenu.h>
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
#include <qvalidator.h>
#include <qwidget.h>

#include "qtscriptshell_QLineEdit.h"

static const char * const qtscript_QLineEdit_function_names[] = {
    "QLineEdit"
    // static
    // prototype
    , "backspace"
    , "completer"
    , "createStandardContextMenu"
    , "cursorBackward"
    , "cursorForward"
    , "cursorPositionAt"
    , "cursorWordBackward"
    , "cursorWordForward"
    , "del"
    , "deselect"
    , "end"
    , "getTextMargins"
    , "home"
    , "insert"
    , "minimumSizeHint"
    , "selectionStart"
    , "setCompleter"
    , "setSelection"
    , "setTextMargins"
    , "setValidator"
    , "sizeHint"
    , "textMargins"
    , "validator"
    , "toString"
};

static const char * const qtscript_QLineEdit_function_signatures[] = {
    "QWidget parent\nString arg__1, QWidget parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , "bool mark, int steps"
    , "bool mark, int steps"
    , "QPoint pos"
    , "bool mark"
    , "bool mark"
    , ""
    , ""
    , "bool mark"
    , "int left, int top, int right, int bottom"
    , "bool mark"
    , "String arg__1"
    , ""
    , ""
    , "QCompleter completer"
    , "int arg__1, int arg__2"
    , "QMargins margins\nint left, int top, int right, int bottom"
    , "QValidator arg__1"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QLineEdit_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 2
    , 2
    , 1
    , 1
    , 1
    , 0
    , 0
    , 1
    , 4
    , 1
    , 1
    , 0
    , 0
    , 1
    , 2
    , 4
    , 1
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QLineEdit_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QLineEdit::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QLineEdit_metaObject()
{
    return &QLineEdit::staticMetaObject;
}

Q_DECLARE_METATYPE(QLineEdit*)
Q_DECLARE_METATYPE(QtScriptShell_QLineEdit*)
Q_DECLARE_METATYPE(QLineEdit::EchoMode)
Q_DECLARE_METATYPE(QCompleter*)
Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(QMargins)
Q_DECLARE_METATYPE(const QValidator*)
Q_DECLARE_METATYPE(QWidget*)

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
// QLineEdit::EchoMode
//

static const QLineEdit::EchoMode qtscript_QLineEdit_EchoMode_values[] = {
    QLineEdit::Normal
    , QLineEdit::NoEcho
    , QLineEdit::Password
    , QLineEdit::PasswordEchoOnEdit
};

static const char * const qtscript_QLineEdit_EchoMode_keys[] = {
    "Normal"
    , "NoEcho"
    , "Password"
    , "PasswordEchoOnEdit"
};

static QString qtscript_QLineEdit_EchoMode_toStringHelper(QLineEdit::EchoMode value)
{
    const QMetaObject *meta = qtscript_QLineEdit_metaObject();
    int idx = meta->indexOfEnumerator("EchoMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QLineEdit_EchoMode_toScriptValue(QScriptEngine *engine, const QLineEdit::EchoMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QLineEdit"));
    return clazz.property(qtscript_QLineEdit_EchoMode_toStringHelper(value));
}

static void qtscript_QLineEdit_EchoMode_fromScriptValue(const QScriptValue &value, QLineEdit::EchoMode &out)
{
    out = qvariant_cast<QLineEdit::EchoMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QLineEdit_EchoMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QLineEdit_metaObject();
    int idx = meta->indexOfEnumerator("EchoMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QLineEdit::EchoMode>(arg));
    return context->throwError(QString::fromLatin1("EchoMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QLineEdit_EchoMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QLineEdit::EchoMode value = qscriptvalue_cast<QLineEdit::EchoMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QLineEdit_EchoMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QLineEdit::EchoMode value = qscriptvalue_cast<QLineEdit::EchoMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QLineEdit_EchoMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QLineEdit_EchoMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QLineEdit_EchoMode,
        qtscript_QLineEdit_EchoMode_valueOf, qtscript_QLineEdit_EchoMode_toString);
    qScriptRegisterMetaType<QLineEdit::EchoMode>(engine, qtscript_QLineEdit_EchoMode_toScriptValue,
        qtscript_QLineEdit_EchoMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QLineEdit_EchoMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QLineEdit_EchoMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QLineEdit
//

static QScriptValue qtscript_QLineEdit_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 23;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QLineEdit* _q_self = qscriptvalue_cast<QLineEdit*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QLineEdit.%0(): this object is not a QLineEdit")
            .arg(qtscript_QLineEdit_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->backspace();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QCompleter* _q_result = _q_self->completer();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QMenu* _q_result = _q_self->createStandardContextMenu();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->cursorBackward(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        bool _q_arg0 = context->argument(0).toBoolean();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->cursorBackward(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->cursorForward(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        bool _q_arg0 = context->argument(0).toBoolean();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->cursorForward(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        int _q_result = _q_self->cursorPositionAt(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->cursorWordBackward(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->cursorWordForward(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        _q_self->del();
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        _q_self->deselect();
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->end(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 4) {
        int* _q_arg0 = qscriptvalue_cast<int*>(context->argument(0));
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
        int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
        _q_self->getTextMargins(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->home(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->insert(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->selectionStart();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QCompleter* _q_arg0 = qscriptvalue_cast<QCompleter*>(context->argument(0));
        _q_self->setCompleter(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setSelection(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QMargins _q_arg0 = qscriptvalue_cast<QMargins>(context->argument(0));
        _q_self->setTextMargins(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setTextMargins(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        const QValidator* _q_arg0 = qscriptvalue_cast<const QValidator*>(context->argument(0));
        _q_self->setValidator(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        QMargins _q_result = _q_self->textMargins();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        const QValidator* _q_result = const_cast<const QValidator*>(_q_self->validator());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23: {
    QString result = QString::fromLatin1("QLineEdit");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLineEdit_throw_ambiguity_error_helper(context,
        qtscript_QLineEdit_function_names[_id+1],
        qtscript_QLineEdit_function_signatures[_id+1]);
}

static QScriptValue qtscript_QLineEdit_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QLineEdit(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QLineEdit* _q_cpp_result = new QtScriptShell_QLineEdit();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLineEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QLineEdit* _q_cpp_result = new QtScriptShell_QLineEdit(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLineEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QLineEdit* _q_cpp_result = new QtScriptShell_QLineEdit(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLineEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QLineEdit* _q_cpp_result = new QtScriptShell_QLineEdit(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLineEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLineEdit_throw_ambiguity_error_helper(context,
        qtscript_QLineEdit_function_names[_id],
        qtscript_QLineEdit_function_signatures[_id]);
}

static QScriptValue qtscript_QLineEdit_toScriptValue(QScriptEngine *engine, QLineEdit* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QLineEdit_fromScriptValue(const QScriptValue &value, QLineEdit* &out)
{
    out = qobject_cast<QLineEdit*>(value.toQObject());
}

QScriptValue qtscript_create_QLineEdit_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QLineEdit*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QLineEdit*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 24; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLineEdit_prototype_call, qtscript_QLineEdit_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QLineEdit_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QLineEdit*>(engine, qtscript_QLineEdit_toScriptValue, 
        qtscript_QLineEdit_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QLineEdit_static_call, proto, qtscript_QLineEdit_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("EchoMode"),
        qtscript_create_QLineEdit_EchoMode_class(engine, ctor));
    return ctor;
}
