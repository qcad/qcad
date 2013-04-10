#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <videowidgetinterface.h>
#include <QVariant>
#include <qwidget.h>

#include "qtscriptshell_AbstractVideoWidget.h"

static const char * const qtscript_AbstractVideoWidget_function_names[] = {
    "AbstractVideoWidget"
    // static
    // prototype
    , "aspectRatio"
    , "brightness"
    , "contrast"
    , "hue"
    , "saturation"
    , "scaleMode"
    , "setAspectRatio"
    , "setBrightness"
    , "setContrast"
    , "setHue"
    , "setSaturation"
    , "setScaleMode"
    , "widget"
    , "toString"
};

static const char * const qtscript_AbstractVideoWidget_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "AspectRatio arg__1"
    , "qreal arg__1"
    , "qreal arg__1"
    , "qreal arg__1"
    , "qreal arg__1"
    , "ScaleMode arg__1"
    , ""
""
};

static const int qtscript_AbstractVideoWidget_function_lengths[] = {
    0
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_AbstractVideoWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("AbstractVideoWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Phonon::VideoWidgetInterface*)
Q_DECLARE_METATYPE(QtScriptShell_AbstractVideoWidget*)
Q_DECLARE_METATYPE(Phonon::VideoWidget::AspectRatio)
Q_DECLARE_METATYPE(Phonon::VideoWidget::ScaleMode)

//
// AbstractVideoWidget
//

static QScriptValue qtscript_AbstractVideoWidget_prototype_call(QScriptContext *context, QScriptEngine *)
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
    Phonon::VideoWidgetInterface* _q_self = qscriptvalue_cast<Phonon::VideoWidgetInterface*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("AbstractVideoWidget.%0(): this object is not a AbstractVideoWidget")
            .arg(qtscript_AbstractVideoWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        Phonon::VideoWidget::AspectRatio _q_result = _q_self->aspectRatio();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->brightness();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->contrast();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->hue();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->saturation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        Phonon::VideoWidget::ScaleMode _q_result = _q_self->scaleMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        Phonon::VideoWidget::AspectRatio _q_arg0 = qscriptvalue_cast<Phonon::VideoWidget::AspectRatio>(context->argument(0));
        _q_self->setAspectRatio(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setBrightness(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setContrast(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setHue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setSaturation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        Phonon::VideoWidget::ScaleMode _q_arg0 = qscriptvalue_cast<Phonon::VideoWidget::ScaleMode>(context->argument(0));
        _q_self->setScaleMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->widget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13: {
    QString result = QString::fromLatin1("AbstractVideoWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractVideoWidget_throw_ambiguity_error_helper(context,
        qtscript_AbstractVideoWidget_function_names[_id+1],
        qtscript_AbstractVideoWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_AbstractVideoWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("AbstractVideoWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_AbstractVideoWidget* _q_cpp_result = new QtScriptShell_AbstractVideoWidget();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((Phonon::VideoWidgetInterface*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_AbstractVideoWidget_throw_ambiguity_error_helper(context,
        qtscript_AbstractVideoWidget_function_names[_id],
        qtscript_AbstractVideoWidget_function_signatures[_id]);
}

QScriptValue qtscript_create_AbstractVideoWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Phonon::VideoWidgetInterface*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Phonon::VideoWidgetInterface*)0));
    for (int i = 0; i < 14; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_AbstractVideoWidget_prototype_call, qtscript_AbstractVideoWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_AbstractVideoWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<Phonon::VideoWidgetInterface*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_AbstractVideoWidget_static_call, proto, qtscript_AbstractVideoWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
