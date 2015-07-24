#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qsplashscreen.h>
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
#include <qsplashscreen.h>
#include <qstyle.h>
#include <qwidget.h>

#include "qtscriptshell_QSplashScreen.h"

static const char * const qtscript_QSplashScreen_function_names[] = {
    "QSplashScreen"
    // static
    // prototype
    , "finish"
    , "pixmap"
    , "setPixmap"
    , "toString"
};

static const char * const qtscript_QSplashScreen_function_signatures[] = {
    "QWidget parent, QPixmap pixmap, WindowFlags f\nQPixmap pixmap, WindowFlags f"
    // static
    // prototype
    , "QWidget w"
    , ""
    , "QPixmap pixmap"
""
};

static const int qtscript_QSplashScreen_function_lengths[] = {
    3
    // static
    // prototype
    , 1
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QSplashScreen_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSplashScreen::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSplashScreen*)
Q_DECLARE_METATYPE(QtScriptShell_QSplashScreen*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)

//
// QSplashScreen
//

static QScriptValue qtscript_QSplashScreen_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSplashScreen* _q_self = qscriptvalue_cast<QSplashScreen*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSplashScreen.%0(): this object is not a QSplashScreen")
            .arg(qtscript_QSplashScreen_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->finish(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QPixmap _q_result = _q_self->pixmap();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
        _q_self->setPixmap(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QSplashScreen");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSplashScreen_throw_ambiguity_error_helper(context,
        qtscript_QSplashScreen_function_names[_id+1],
        qtscript_QSplashScreen_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSplashScreen_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSplashScreen(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSplashScreen* _q_cpp_result = new QtScriptShell_QSplashScreen();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSplashScreen*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QSplashScreen* _q_cpp_result = new QtScriptShell_QSplashScreen(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSplashScreen*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QPixmap>() == context->argument(0).toVariant().userType())) {
            QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
            QtScriptShell_QSplashScreen* _q_cpp_result = new QtScriptShell_QSplashScreen(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSplashScreen*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))
            && (qMetaTypeId<QPixmap>() == context->argument(1).toVariant().userType())) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
            QtScriptShell_QSplashScreen* _q_cpp_result = new QtScriptShell_QSplashScreen(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSplashScreen*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QPixmap>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QFlags<Qt::WindowType> >() == context->argument(1).toVariant().userType())) {
            QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
            QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
            QtScriptShell_QSplashScreen* _q_cpp_result = new QtScriptShell_QSplashScreen(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSplashScreen*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QPixmap _q_arg1 = qscriptvalue_cast<QPixmap>(context->argument(1));
        QFlags<Qt::WindowType> _q_arg2 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(2));
        QtScriptShell_QSplashScreen* _q_cpp_result = new QtScriptShell_QSplashScreen(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSplashScreen*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSplashScreen_throw_ambiguity_error_helper(context,
        qtscript_QSplashScreen_function_names[_id],
        qtscript_QSplashScreen_function_signatures[_id]);
}

static QScriptValue qtscript_QSplashScreen_toScriptValue(QScriptEngine *engine, QSplashScreen* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSplashScreen_fromScriptValue(const QScriptValue &value, QSplashScreen* &out)
{
    out = qobject_cast<QSplashScreen*>(value.toQObject());
}

QScriptValue qtscript_create_QSplashScreen_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSplashScreen*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSplashScreen*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSplashScreen_prototype_call, qtscript_QSplashScreen_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSplashScreen_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSplashScreen*>(engine, qtscript_QSplashScreen_toScriptValue, 
        qtscript_QSplashScreen_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSplashScreen_static_call, proto, qtscript_QSplashScreen_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
