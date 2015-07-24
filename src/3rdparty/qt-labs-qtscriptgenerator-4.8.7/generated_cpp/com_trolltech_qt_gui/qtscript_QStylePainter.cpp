#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qstylepainter.h>
#include <QVariant>
#include <qbrush.h>
#include <qcolor.h>
#include <qfont.h>
#include <qimage.h>
#include <qline.h>
#include <qmatrix.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainterpath.h>
#include <qpalette.h>
#include <qpen.h>
#include <qpicture.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qstylepainter.h>
#include <qtransform.h>
#include <qvector.h>
#include <qwidget.h>

static const char * const qtscript_QStylePainter_function_names[] = {
    "QStylePainter"
    // static
    // prototype
    , "begin"
    , "drawComplexControl"
    , "drawControl"
    , "drawItemPixmap"
    , "drawItemText"
    , "drawPrimitive"
    , "style"
    , "toString"
};

static const char * const qtscript_QStylePainter_function_signatures[] = {
    "\nQPaintDevice pd, QWidget w\nQWidget w"
    // static
    // prototype
    , "QPaintDevice pd, QWidget w\nQWidget w"
    , "ComplexControl cc, QStyleOptionComplex opt"
    , "ControlElement ce, QStyleOption opt"
    , "QRect r, int flags, QPixmap pixmap"
    , "QRect r, int flags, QPalette pal, bool enabled, String text, ColorRole textRole"
    , "PrimitiveElement pe, QStyleOption opt"
    , ""
""
};

static const int qtscript_QStylePainter_function_lengths[] = {
    2
    // static
    // prototype
    , 2
    , 2
    , 2
    , 3
    , 6
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QStylePainter_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QStylePainter::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QStylePainter*)
Q_DECLARE_METATYPE(QPaintDevice*)
Q_DECLARE_METATYPE(QStyle::ComplexControl)
Q_DECLARE_METATYPE(QStyleOptionComplex)
Q_DECLARE_METATYPE(QStyle::ControlElement)
Q_DECLARE_METATYPE(QStyleOption)
Q_DECLARE_METATYPE(QPalette::ColorRole)
Q_DECLARE_METATYPE(QStyle::PrimitiveElement)
Q_DECLARE_METATYPE(QStyle*)
Q_DECLARE_METATYPE(QPainter*)

//
// QStylePainter
//

static QScriptValue qtscript_QStylePainter_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QStylePainter* _q_self = qscriptvalue_cast<QStylePainter*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QStylePainter.%0(): this object is not a QStylePainter")
            .arg(qtscript_QStylePainter_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        bool _q_result = _q_self->begin(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QPaintDevice* _q_arg0 = qscriptvalue_cast<QPaintDevice*>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        bool _q_result = _q_self->begin(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        QStyle::ComplexControl _q_arg0 = qscriptvalue_cast<QStyle::ComplexControl>(context->argument(0));
        QStyleOptionComplex _q_arg1 = qscriptvalue_cast<QStyleOptionComplex>(context->argument(1));
        _q_self->drawComplexControl(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        QStyle::ControlElement _q_arg0 = qscriptvalue_cast<QStyle::ControlElement>(context->argument(0));
        QStyleOption _q_arg1 = qscriptvalue_cast<QStyleOption>(context->argument(1));
        _q_self->drawControl(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 3) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QPixmap _q_arg2 = qscriptvalue_cast<QPixmap>(context->argument(2));
        _q_self->drawItemPixmap(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 5) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QPalette _q_arg2 = qscriptvalue_cast<QPalette>(context->argument(2));
        bool _q_arg3 = context->argument(3).toBoolean();
        QString _q_arg4 = context->argument(4).toString();
        _q_self->drawItemText(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QPalette _q_arg2 = qscriptvalue_cast<QPalette>(context->argument(2));
        bool _q_arg3 = context->argument(3).toBoolean();
        QString _q_arg4 = context->argument(4).toString();
        QPalette::ColorRole _q_arg5 = qscriptvalue_cast<QPalette::ColorRole>(context->argument(5));
        _q_self->drawItemText(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        QStyle::PrimitiveElement _q_arg0 = qscriptvalue_cast<QStyle::PrimitiveElement>(context->argument(0));
        QStyleOption _q_arg1 = qscriptvalue_cast<QStyleOption>(context->argument(1));
        _q_self->drawPrimitive(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QStyle* _q_result = _q_self->style();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7: {
    QString result = QString::fromLatin1("QStylePainter");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStylePainter_throw_ambiguity_error_helper(context,
        qtscript_QStylePainter_function_names[_id+1],
        qtscript_QStylePainter_function_signatures[_id+1]);
}

static QScriptValue qtscript_QStylePainter_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QStylePainter(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QStylePainter* _q_cpp_result = new QStylePainter();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QStylePainter* _q_cpp_result = new QStylePainter(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QPaintDevice* _q_arg0 = qscriptvalue_cast<QPaintDevice*>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QStylePainter* _q_cpp_result = new QStylePainter(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QStylePainter_throw_ambiguity_error_helper(context,
        qtscript_QStylePainter_function_names[_id],
        qtscript_QStylePainter_function_signatures[_id]);
}

QScriptValue qtscript_create_QStylePainter_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QStylePainter*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QStylePainter*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QPainter*>()));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QStylePainter_prototype_call, qtscript_QStylePainter_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QStylePainter_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QStylePainter*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QStylePainter_static_call, proto, qtscript_QStylePainter_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
