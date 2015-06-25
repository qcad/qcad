#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qrubberband.h>
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
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QRubberBand.h"

static const char * const qtscript_QRubberBand_function_names[] = {
    "QRubberBand"
    // static
    // prototype
    , "moveRubberBand"
    , "resizeRubberBand"
    , "setRubberBandGeometry"
    , "shape"
    , "toString"
};

static const char * const qtscript_QRubberBand_function_signatures[] = {
    "Shape arg__1, QWidget arg__2"
    // static
    // prototype
    , "QPoint p\nint x, int y"
    , "QSize s\nint w, int h"
    , "QRect r\nint x, int y, int w, int h"
    , ""
""
};

static const int qtscript_QRubberBand_function_lengths[] = {
    2
    // static
    // prototype
    , 2
    , 2
    , 4
    , 0
    , 0
};

static QScriptValue qtscript_QRubberBand_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QRubberBand::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QRubberBand*)
Q_DECLARE_METATYPE(QtScriptShell_QRubberBand*)
Q_DECLARE_METATYPE(QRubberBand::Shape)
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
// QRubberBand::Shape
//

static const QRubberBand::Shape qtscript_QRubberBand_Shape_values[] = {
    QRubberBand::Line
    , QRubberBand::Rectangle
};

static const char * const qtscript_QRubberBand_Shape_keys[] = {
    "Line"
    , "Rectangle"
};

static QString qtscript_QRubberBand_Shape_toStringHelper(QRubberBand::Shape value)
{
    if ((value >= QRubberBand::Line) && (value <= QRubberBand::Rectangle))
        return qtscript_QRubberBand_Shape_keys[static_cast<int>(value)-static_cast<int>(QRubberBand::Line)];
    return QString();
}

static QScriptValue qtscript_QRubberBand_Shape_toScriptValue(QScriptEngine *engine, const QRubberBand::Shape &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QRubberBand"));
    return clazz.property(qtscript_QRubberBand_Shape_toStringHelper(value));
}

static void qtscript_QRubberBand_Shape_fromScriptValue(const QScriptValue &value, QRubberBand::Shape &out)
{
    out = qvariant_cast<QRubberBand::Shape>(value.toVariant());
}

static QScriptValue qtscript_construct_QRubberBand_Shape(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QRubberBand::Line) && (arg <= QRubberBand::Rectangle))
        return qScriptValueFromValue(engine,  static_cast<QRubberBand::Shape>(arg));
    return context->throwError(QString::fromLatin1("Shape(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QRubberBand_Shape_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QRubberBand::Shape value = qscriptvalue_cast<QRubberBand::Shape>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QRubberBand_Shape_toString(QScriptContext *context, QScriptEngine *engine)
{
    QRubberBand::Shape value = qscriptvalue_cast<QRubberBand::Shape>(context->thisObject());
    return QScriptValue(engine, qtscript_QRubberBand_Shape_toStringHelper(value));
}

static QScriptValue qtscript_create_QRubberBand_Shape_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QRubberBand_Shape,
        qtscript_QRubberBand_Shape_valueOf, qtscript_QRubberBand_Shape_toString);
    qScriptRegisterMetaType<QRubberBand::Shape>(engine, qtscript_QRubberBand_Shape_toScriptValue,
        qtscript_QRubberBand_Shape_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QRubberBand_Shape_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QRubberBand_Shape_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QRubberBand
//

static QScriptValue qtscript_QRubberBand_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 4;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QRubberBand* _q_self = qscriptvalue_cast<QRubberBand*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QRubberBand.%0(): this object is not a QRubberBand")
            .arg(qtscript_QRubberBand_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->move(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->move(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
        _q_self->resize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->resize(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
        _q_self->setGeometry(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        _q_self->setGeometry(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QRubberBand::Shape _q_result = _q_self->shape();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QRubberBand");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRubberBand_throw_ambiguity_error_helper(context,
        qtscript_QRubberBand_function_names[_id+1],
        qtscript_QRubberBand_function_signatures[_id+1]);
}

static QScriptValue qtscript_QRubberBand_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QRubberBand(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QRubberBand::Shape _q_arg0 = qscriptvalue_cast<QRubberBand::Shape>(context->argument(0));
        QtScriptShell_QRubberBand* _q_cpp_result = new QtScriptShell_QRubberBand(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QRubberBand*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QRubberBand::Shape _q_arg0 = qscriptvalue_cast<QRubberBand::Shape>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QRubberBand* _q_cpp_result = new QtScriptShell_QRubberBand(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QRubberBand*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QRubberBand_throw_ambiguity_error_helper(context,
        qtscript_QRubberBand_function_names[_id],
        qtscript_QRubberBand_function_signatures[_id]);
}

static QScriptValue qtscript_QRubberBand_toScriptValue(QScriptEngine *engine, QRubberBand* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QRubberBand_fromScriptValue(const QScriptValue &value, QRubberBand* &out)
{
    out = qobject_cast<QRubberBand*>(value.toQObject());
}

QScriptValue qtscript_create_QRubberBand_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QRubberBand*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QRubberBand*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QRubberBand_prototype_call, qtscript_QRubberBand_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QRubberBand_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QRubberBand*>(engine, qtscript_QRubberBand_toScriptValue, 
        qtscript_QRubberBand_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QRubberBand_static_call, proto, qtscript_QRubberBand_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Shape"),
        qtscript_create_QRubberBand_Shape_class(engine, ctor));
    return ctor;
}
