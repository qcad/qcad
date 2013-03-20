#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <videowidget.h>
#include <QVariant>
#include <path.h>
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
#include <qimage.h>
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

#include "qtscriptshell_VideoWidget.h"

static const char * const qtscript_VideoWidget_function_names[] = {
    "VideoWidget"
    // static
    // prototype
    , "snapshot"
    , "toString"
};

static const char * const qtscript_VideoWidget_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
""
};

static const int qtscript_VideoWidget_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
};

static QScriptValue qtscript_VideoWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("VideoWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_VideoWidget_metaObject()
{
    return &Phonon::VideoWidget::staticMetaObject;
}

Q_DECLARE_METATYPE(Phonon::VideoWidget*)
Q_DECLARE_METATYPE(QtScriptShell_VideoWidget*)
Q_DECLARE_METATYPE(Phonon::VideoWidget::AspectRatio)
Q_DECLARE_METATYPE(Phonon::VideoWidget::ScaleMode)
Q_DECLARE_METATYPE(Phonon::AbstractVideoOutput*)
Q_DECLARE_METATYPE(Phonon::MediaNode*)

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
// Phonon::VideoWidget::AspectRatio
//

static const Phonon::VideoWidget::AspectRatio qtscript_VideoWidget_AspectRatio_values[] = {
    Phonon::VideoWidget::AspectRatioAuto
    , Phonon::VideoWidget::AspectRatioWidget
    , Phonon::VideoWidget::AspectRatio4_3
    , Phonon::VideoWidget::AspectRatio16_9
};

static const char * const qtscript_VideoWidget_AspectRatio_keys[] = {
    "AspectRatioAuto"
    , "AspectRatioWidget"
    , "AspectRatio4_3"
    , "AspectRatio16_9"
};

static QString qtscript_VideoWidget_AspectRatio_toStringHelper(Phonon::VideoWidget::AspectRatio value)
{
    const QMetaObject *meta = qtscript_VideoWidget_metaObject();
    int idx = meta->indexOfEnumerator("AspectRatio");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_VideoWidget_AspectRatio_toScriptValue(QScriptEngine *engine, const Phonon::VideoWidget::AspectRatio &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("VideoWidget"));
    return clazz.property(qtscript_VideoWidget_AspectRatio_toStringHelper(value));
}

static void qtscript_VideoWidget_AspectRatio_fromScriptValue(const QScriptValue &value, Phonon::VideoWidget::AspectRatio &out)
{
    out = qvariant_cast<Phonon::VideoWidget::AspectRatio>(value.toVariant());
}

static QScriptValue qtscript_construct_VideoWidget_AspectRatio(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_VideoWidget_metaObject();
    int idx = meta->indexOfEnumerator("AspectRatio");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Phonon::VideoWidget::AspectRatio>(arg));
    return context->throwError(QString::fromLatin1("AspectRatio(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_VideoWidget_AspectRatio_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::VideoWidget::AspectRatio value = qscriptvalue_cast<Phonon::VideoWidget::AspectRatio>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_VideoWidget_AspectRatio_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::VideoWidget::AspectRatio value = qscriptvalue_cast<Phonon::VideoWidget::AspectRatio>(context->thisObject());
    return QScriptValue(engine, qtscript_VideoWidget_AspectRatio_toStringHelper(value));
}

static QScriptValue qtscript_create_VideoWidget_AspectRatio_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_VideoWidget_AspectRatio,
        qtscript_VideoWidget_AspectRatio_valueOf, qtscript_VideoWidget_AspectRatio_toString);
    qScriptRegisterMetaType<Phonon::VideoWidget::AspectRatio>(engine, qtscript_VideoWidget_AspectRatio_toScriptValue,
        qtscript_VideoWidget_AspectRatio_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_VideoWidget_AspectRatio_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_VideoWidget_AspectRatio_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// Phonon::VideoWidget::ScaleMode
//

static const Phonon::VideoWidget::ScaleMode qtscript_VideoWidget_ScaleMode_values[] = {
    Phonon::VideoWidget::FitInView
    , Phonon::VideoWidget::ScaleAndCrop
};

static const char * const qtscript_VideoWidget_ScaleMode_keys[] = {
    "FitInView"
    , "ScaleAndCrop"
};

static QString qtscript_VideoWidget_ScaleMode_toStringHelper(Phonon::VideoWidget::ScaleMode value)
{
    const QMetaObject *meta = qtscript_VideoWidget_metaObject();
    int idx = meta->indexOfEnumerator("ScaleMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_VideoWidget_ScaleMode_toScriptValue(QScriptEngine *engine, const Phonon::VideoWidget::ScaleMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("VideoWidget"));
    return clazz.property(qtscript_VideoWidget_ScaleMode_toStringHelper(value));
}

static void qtscript_VideoWidget_ScaleMode_fromScriptValue(const QScriptValue &value, Phonon::VideoWidget::ScaleMode &out)
{
    out = qvariant_cast<Phonon::VideoWidget::ScaleMode>(value.toVariant());
}

static QScriptValue qtscript_construct_VideoWidget_ScaleMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_VideoWidget_metaObject();
    int idx = meta->indexOfEnumerator("ScaleMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<Phonon::VideoWidget::ScaleMode>(arg));
    return context->throwError(QString::fromLatin1("ScaleMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_VideoWidget_ScaleMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::VideoWidget::ScaleMode value = qscriptvalue_cast<Phonon::VideoWidget::ScaleMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_VideoWidget_ScaleMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    Phonon::VideoWidget::ScaleMode value = qscriptvalue_cast<Phonon::VideoWidget::ScaleMode>(context->thisObject());
    return QScriptValue(engine, qtscript_VideoWidget_ScaleMode_toStringHelper(value));
}

static QScriptValue qtscript_create_VideoWidget_ScaleMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_VideoWidget_ScaleMode,
        qtscript_VideoWidget_ScaleMode_valueOf, qtscript_VideoWidget_ScaleMode_toString);
    qScriptRegisterMetaType<Phonon::VideoWidget::ScaleMode>(engine, qtscript_VideoWidget_ScaleMode_toScriptValue,
        qtscript_VideoWidget_ScaleMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_VideoWidget_ScaleMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_VideoWidget_ScaleMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// VideoWidget
//

static QScriptValue qtscript_VideoWidget_prototype_call(QScriptContext *context, QScriptEngine *)
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
    Phonon::VideoWidget* _q_self = qscriptvalue_cast<Phonon::VideoWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("VideoWidget.%0(): this object is not a VideoWidget")
            .arg(qtscript_VideoWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QImage _q_result = _q_self->snapshot();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("VideoWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_VideoWidget_throw_ambiguity_error_helper(context,
        qtscript_VideoWidget_function_names[_id+1],
        qtscript_VideoWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_VideoWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("VideoWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_VideoWidget* _q_cpp_result = new QtScriptShell_VideoWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::VideoWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_VideoWidget* _q_cpp_result = new QtScriptShell_VideoWidget(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Phonon::VideoWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_VideoWidget_throw_ambiguity_error_helper(context,
        qtscript_VideoWidget_function_names[_id],
        qtscript_VideoWidget_function_signatures[_id]);
}

static QScriptValue qtscript_VideoWidget_toScriptValue(QScriptEngine *engine, Phonon::VideoWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_VideoWidget_fromScriptValue(const QScriptValue &value, Phonon::VideoWidget* &out)
{
    out = qobject_cast<Phonon::VideoWidget*>(value.toQObject());
}

QScriptValue qtscript_create_VideoWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::VideoWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::VideoWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    proto.setProperty(QString::fromLatin1("__AbstractVideoOutput__"),
        engine->defaultPrototype(qMetaTypeId<Phonon::AbstractVideoOutput*>()),
        QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("__MediaNode__"),
        engine->defaultPrototype(qMetaTypeId<Phonon::MediaNode*>()),
        QScriptValue::SkipInEnumeration);
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_VideoWidget_prototype_call, qtscript_VideoWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_VideoWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<Phonon::VideoWidget*>(engine, qtscript_VideoWidget_toScriptValue, 
        qtscript_VideoWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_VideoWidget_static_call, proto, qtscript_VideoWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("AspectRatio"),
        qtscript_create_VideoWidget_AspectRatio_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ScaleMode"),
        qtscript_create_VideoWidget_ScaleMode_class(engine, ctor));
    return ctor;
}
