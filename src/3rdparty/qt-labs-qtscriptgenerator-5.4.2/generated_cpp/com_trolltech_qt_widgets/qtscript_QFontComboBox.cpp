#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qfontcombobox.h>
#include <QVariant>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcompleter.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qfontcombobox.h>
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
#include <qstringlist.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qvalidator.h>
#include <qwidget.h>

#include "qtscriptshell_QFontComboBox.h"

static const char * const qtscript_QFontComboBox_function_names[] = {
    "QFontComboBox"
    // static
    // prototype
    , "toString"
};

static const char * const qtscript_QFontComboBox_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
""
};

static const int qtscript_QFontComboBox_function_lengths[] = {
    1
    // static
    // prototype
    , 0
};

static QScriptValue qtscript_QFontComboBox_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFontComboBox::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFontComboBox*)
Q_DECLARE_METATYPE(QtScriptShell_QFontComboBox*)
Q_DECLARE_METATYPE(QFontComboBox::FontFilter)
Q_DECLARE_METATYPE(QFlags<QFontComboBox::FontFilter>)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QComboBox*)

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

static QScriptValue qtscript_create_flags_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString,
    QScriptEngine::FunctionSignature equals)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("equals"),
        engine->newFunction(equals), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto);
}

//
// QFontComboBox::FontFilter
//

static const QFontComboBox::FontFilter qtscript_QFontComboBox_FontFilter_values[] = {
    QFontComboBox::AllFonts
    , QFontComboBox::ScalableFonts
    , QFontComboBox::NonScalableFonts
    , QFontComboBox::MonospacedFonts
    , QFontComboBox::ProportionalFonts
};

static const char * const qtscript_QFontComboBox_FontFilter_keys[] = {
    "AllFonts"
    , "ScalableFonts"
    , "NonScalableFonts"
    , "MonospacedFonts"
    , "ProportionalFonts"
};

static QString qtscript_QFontComboBox_FontFilter_toStringHelper(QFontComboBox::FontFilter value)
{
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QFontComboBox_FontFilter_values[i] == value)
            return QString::fromLatin1(qtscript_QFontComboBox_FontFilter_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QFontComboBox_FontFilter_toScriptValue(QScriptEngine *engine, const QFontComboBox::FontFilter &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFontComboBox"));
    return clazz.property(qtscript_QFontComboBox_FontFilter_toStringHelper(value));
}

static void qtscript_QFontComboBox_FontFilter_fromScriptValue(const QScriptValue &value, QFontComboBox::FontFilter &out)
{
    out = qvariant_cast<QFontComboBox::FontFilter>(value.toVariant());
}

static QScriptValue qtscript_construct_QFontComboBox_FontFilter(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 5; ++i) {
        if (qtscript_QFontComboBox_FontFilter_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QFontComboBox::FontFilter>(arg));
    }
    return context->throwError(QString::fromLatin1("FontFilter(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFontComboBox_FontFilter_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFontComboBox::FontFilter value = qscriptvalue_cast<QFontComboBox::FontFilter>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFontComboBox_FontFilter_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFontComboBox::FontFilter value = qscriptvalue_cast<QFontComboBox::FontFilter>(context->thisObject());
    return QScriptValue(engine, qtscript_QFontComboBox_FontFilter_toStringHelper(value));
}

static QScriptValue qtscript_create_QFontComboBox_FontFilter_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFontComboBox_FontFilter,
        qtscript_QFontComboBox_FontFilter_valueOf, qtscript_QFontComboBox_FontFilter_toString);
    qScriptRegisterMetaType<QFontComboBox::FontFilter>(engine, qtscript_QFontComboBox_FontFilter_toScriptValue,
        qtscript_QFontComboBox_FontFilter_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 5; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFontComboBox_FontFilter_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFontComboBox_FontFilter_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFontComboBox::FontFilters
//

static QScriptValue qtscript_QFontComboBox_FontFilters_toScriptValue(QScriptEngine *engine, const QFontComboBox::FontFilters &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QFontComboBox_FontFilters_fromScriptValue(const QScriptValue &value, QFontComboBox::FontFilters &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QFontComboBox::FontFilters>())
        out = qvariant_cast<QFontComboBox::FontFilters>(var);
    else if (var.userType() == qMetaTypeId<QFontComboBox::FontFilter>())
        out = qvariant_cast<QFontComboBox::FontFilter>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QFontComboBox_FontFilters(QScriptContext *context, QScriptEngine *engine)
{
    QFontComboBox::FontFilters result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QFontComboBox::FontFilters>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QFontComboBox::FontFilter>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("FontFilters(): argument %0 is not of type FontFilter").arg(i));
            }
            result |= qvariant_cast<QFontComboBox::FontFilter>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QFontComboBox_FontFilters_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFontComboBox::FontFilters value = qscriptvalue_cast<QFontComboBox::FontFilters>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFontComboBox_FontFilters_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFontComboBox::FontFilters value = qscriptvalue_cast<QFontComboBox::FontFilters>(context->thisObject());
    QString result;
    for (int i = 0; i < 5; ++i) {
        if ((value & qtscript_QFontComboBox_FontFilter_values[i]) == qtscript_QFontComboBox_FontFilter_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QFontComboBox_FontFilter_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QFontComboBox_FontFilters_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QFontComboBox::FontFilters>() == otherObj.value<QFontComboBox::FontFilters>())));
}

static QScriptValue qtscript_create_QFontComboBox_FontFilters_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QFontComboBox_FontFilters, qtscript_QFontComboBox_FontFilters_valueOf,
        qtscript_QFontComboBox_FontFilters_toString, qtscript_QFontComboBox_FontFilters_equals);
    qScriptRegisterMetaType<QFontComboBox::FontFilters>(engine, qtscript_QFontComboBox_FontFilters_toScriptValue,
        qtscript_QFontComboBox_FontFilters_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QFontComboBox
//

static QScriptValue qtscript_QFontComboBox_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QFontComboBox* _q_self = qscriptvalue_cast<QFontComboBox*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFontComboBox.%0(): this object is not a QFontComboBox")
            .arg(qtscript_QFontComboBox_function_names[_id+1]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QFontComboBox");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFontComboBox_throw_ambiguity_error_helper(context,
        qtscript_QFontComboBox_function_names[_id+1],
        qtscript_QFontComboBox_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFontComboBox_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFontComboBox(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QFontComboBox* _q_cpp_result = new QtScriptShell_QFontComboBox();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFontComboBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QFontComboBox* _q_cpp_result = new QtScriptShell_QFontComboBox(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFontComboBox*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFontComboBox_throw_ambiguity_error_helper(context,
        qtscript_QFontComboBox_function_names[_id],
        qtscript_QFontComboBox_function_signatures[_id]);
}

static QScriptValue qtscript_QFontComboBox_toScriptValue(QScriptEngine *engine, QFontComboBox* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QFontComboBox_fromScriptValue(const QScriptValue &value, QFontComboBox* &out)
{
    out = qobject_cast<QFontComboBox*>(value.toQObject());
}

QScriptValue qtscript_create_QFontComboBox_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFontComboBox*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFontComboBox*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QComboBox*>()));

    qScriptRegisterMetaType<QFontComboBox*>(engine, qtscript_QFontComboBox_toScriptValue, 
        qtscript_QFontComboBox_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFontComboBox_static_call, proto, qtscript_QFontComboBox_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("FontFilter"),
        qtscript_create_QFontComboBox_FontFilter_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FontFilters"),
        qtscript_create_QFontComboBox_FontFilters_class(engine));
    return ctor;
}
