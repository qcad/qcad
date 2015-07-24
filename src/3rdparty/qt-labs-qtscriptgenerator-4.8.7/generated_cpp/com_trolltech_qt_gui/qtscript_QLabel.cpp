#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qlabel.h>
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
#include <qlabel.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qmovie.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpicture.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QLabel.h"

static const char * const qtscript_QLabel_function_names[] = {
    "QLabel"
    // static
    // prototype
    , "buddy"
    , "minimumSizeHint"
    , "movie"
    , "picture_private"
    , "selectionStart"
    , "setBuddy"
    , "setSelection"
    , "toString"
};

static const char * const qtscript_QLabel_function_signatures[] = {
    "QWidget parent, WindowFlags f\nString text, QWidget parent, WindowFlags f"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QWidget arg__1"
    , "int arg__1, int arg__2"
""
};

static const int qtscript_QLabel_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QLabel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QLabel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QLabel*)
Q_DECLARE_METATYPE(QtScriptShell_QLabel*)
Q_DECLARE_METATYPE(QMovie*)
Q_DECLARE_METATYPE(QPicture*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)
Q_DECLARE_METATYPE(QFrame*)

//
// QLabel
//

static QScriptValue qtscript_QLabel_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QLabel* _q_self = qscriptvalue_cast<QLabel*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QLabel.%0(): this object is not a QLabel")
            .arg(qtscript_QLabel_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->buddy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QMovie* _q_result = _q_self->movie();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QPicture* _q_result = const_cast<QPicture*>(_q_self->picture());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->selectionStart();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setBuddy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setSelection(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 7: {
    QString result = QString::fromLatin1("QLabel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLabel_throw_ambiguity_error_helper(context,
        qtscript_QLabel_function_names[_id+1],
        qtscript_QLabel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QLabel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QLabel(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QLabel* _q_cpp_result = new QtScriptShell_QLabel();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLabel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QLabel* _q_cpp_result = new QtScriptShell_QLabel(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLabel*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QLabel* _q_cpp_result = new QtScriptShell_QLabel(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLabel*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && (qMetaTypeId<QFlags<Qt::WindowType> >() == context->argument(1).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
            QtScriptShell_QLabel* _q_cpp_result = new QtScriptShell_QLabel(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLabel*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && qscriptvalue_cast<QWidget*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
            QtScriptShell_QLabel* _q_cpp_result = new QtScriptShell_QLabel(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLabel*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QFlags<Qt::WindowType> _q_arg2 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(2));
        QtScriptShell_QLabel* _q_cpp_result = new QtScriptShell_QLabel(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QLabel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QLabel_throw_ambiguity_error_helper(context,
        qtscript_QLabel_function_names[_id],
        qtscript_QLabel_function_signatures[_id]);
}

static QScriptValue qtscript_QLabel_toScriptValue(QScriptEngine *engine, QLabel* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QLabel_fromScriptValue(const QScriptValue &value, QLabel* &out)
{
    out = qobject_cast<QLabel*>(value.toQObject());
}

QScriptValue qtscript_create_QLabel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QLabel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QLabel*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QFrame*>()));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLabel_prototype_call, qtscript_QLabel_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QLabel_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QLabel*>(engine, qtscript_QLabel_toScriptValue, 
        qtscript_QLabel_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QLabel_static_call, proto, qtscript_QLabel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
