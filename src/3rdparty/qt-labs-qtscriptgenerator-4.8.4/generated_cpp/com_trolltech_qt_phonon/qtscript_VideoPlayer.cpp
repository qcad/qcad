#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <videoplayer.h>
#include <QVariant>
#include <audiooutput.h>
#include <mediaobject.h>
#include <mediasource.h>
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
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qwidget.h>
#include <videowidget.h>

#include "qtscriptshell_VideoPlayer.h"

static const char * const qtscript_VideoPlayer_function_names[] = {
    "VideoPlayer"
    // static
    // prototype
    , "audioOutput"
    , "currentTime"
    , "isPaused"
    , "isPlaying"
    , "mediaObject"
    , "totalTime"
    , "videoWidget"
    , "volume"
    , "toString"
};

static const char * const qtscript_VideoPlayer_function_signatures[] = {
    "Category category, QWidget parent\nQWidget parent"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_VideoPlayer_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_VideoPlayer_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("VideoPlayer::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::VideoPlayer*)
Q_DECLARE_METATYPE(QtScriptShell_VideoPlayer*)
Q_DECLARE_METATYPE(Phonon::AudioOutput*)
Q_DECLARE_METATYPE(Phonon::MediaObject*)
Q_DECLARE_METATYPE(Phonon::VideoWidget*)

//
// VideoPlayer
//

static QScriptValue qtscript_VideoPlayer_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 8;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Phonon::VideoPlayer* _q_self = qscriptvalue_cast<Phonon::VideoPlayer*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("VideoPlayer.%0(): this object is not a VideoPlayer")
            .arg(qtscript_VideoPlayer_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        Phonon::AudioOutput* _q_result = _q_self->audioOutput();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->currentTime();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isPaused();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isPlaying();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        Phonon::MediaObject* _q_result = _q_self->mediaObject();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->totalTime();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        Phonon::VideoWidget* _q_result = _q_self->videoWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        float _q_result = _q_self->volume();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("VideoPlayer");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_VideoPlayer_throw_ambiguity_error_helper(context,
        qtscript_VideoPlayer_function_names[_id+1],
        qtscript_VideoPlayer_function_signatures[_id+1]);
}

static QScriptValue qtscript_VideoPlayer_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("VideoPlayer(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_VideoPlayer* _q_cpp_result = new QtScriptShell_VideoPlayer();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::VideoPlayer*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<Phonon::Category>() == context->argument(0).toVariant().userType())) {
            Phonon::Category _q_arg0 = qscriptvalue_cast<Phonon::Category>(context->argument(0));
            QtScriptShell_VideoPlayer* _q_cpp_result = new QtScriptShell_VideoPlayer(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::VideoPlayer*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_VideoPlayer* _q_cpp_result = new QtScriptShell_VideoPlayer(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::VideoPlayer*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        Phonon::Category _q_arg0 = qscriptvalue_cast<Phonon::Category>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_VideoPlayer* _q_cpp_result = new QtScriptShell_VideoPlayer(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::VideoPlayer*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_VideoPlayer_throw_ambiguity_error_helper(context,
        qtscript_VideoPlayer_function_names[_id],
        qtscript_VideoPlayer_function_signatures[_id]);
}

static QScriptValue qtscript_VideoPlayer_toScriptValue(QScriptEngine *engine, Phonon::VideoPlayer* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_VideoPlayer_fromScriptValue(const QScriptValue &value, Phonon::VideoPlayer* &out)
{
    out = qobject_cast<Phonon::VideoPlayer*>(value.toQObject());
}

QScriptValue qtscript_create_VideoPlayer_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::VideoPlayer*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::VideoPlayer*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_VideoPlayer_prototype_call, qtscript_VideoPlayer_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_VideoPlayer_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<Phonon::VideoPlayer*>(engine, qtscript_VideoPlayer_toScriptValue, 
        qtscript_VideoPlayer_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_VideoPlayer_static_call, proto, qtscript_VideoPlayer_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
