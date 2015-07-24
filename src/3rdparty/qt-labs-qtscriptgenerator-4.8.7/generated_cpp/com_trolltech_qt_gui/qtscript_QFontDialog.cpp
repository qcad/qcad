#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qfontdialog.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qfontdialog.h>
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

#include "qtscriptshell_QFontDialog.h"

static const char * const qtscript_QFontDialog_function_names[] = {
    "QFontDialog"
    // static
    , "getFont"
    // prototype
    , "open"
    , "selectedFont"
    , "setOption"
    , "testOption"
    , "toString"
};

static const char * const qtscript_QFontDialog_function_signatures[] = {
    "QWidget parent\nQFont initial, QWidget parent"
    // static
    , "QWidget parent\nQFont initial, QWidget parent\nQFont initial, QWidget parent, String title\nbool ok, QFont initial, QWidget parent, String title, FontDialogOptions options"
    // prototype
    , "QObject receiver, char member"
    , ""
    , "FontDialogOption option, bool on"
    , "FontDialogOption option"
""
};

static const int qtscript_QFontDialog_function_lengths[] = {
    2
    // static
    , 5
    // prototype
    , 2
    , 0
    , 2
    , 1
    , 0
};

static QScriptValue qtscript_QFontDialog_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFontDialog::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QFontDialog_metaObject()
{
    return &QFontDialog::staticMetaObject;
}

Q_DECLARE_METATYPE(QFontDialog*)
Q_DECLARE_METATYPE(QtScriptShell_QFontDialog*)
Q_DECLARE_METATYPE(QFontDialog::FontDialogOption)
Q_DECLARE_METATYPE(QFlags<QFontDialog::FontDialogOption>)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(bool*)
Q_DECLARE_METATYPE(QDialog*)


    Q_DECLARE_METATYPE(QScriptValue)
    
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
// QFontDialog::FontDialogOption
//

static const QFontDialog::FontDialogOption qtscript_QFontDialog_FontDialogOption_values[] = {
    QFontDialog::NoButtons
    , QFontDialog::DontUseNativeDialog
};

static const char * const qtscript_QFontDialog_FontDialogOption_keys[] = {
    "NoButtons"
    , "DontUseNativeDialog"
};

static QString qtscript_QFontDialog_FontDialogOption_toStringHelper(QFontDialog::FontDialogOption value)
{
    const QMetaObject *meta = qtscript_QFontDialog_metaObject();
    int idx = meta->indexOfEnumerator("FontDialogOption");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QFontDialog_FontDialogOption_toScriptValue(QScriptEngine *engine, const QFontDialog::FontDialogOption &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFontDialog"));
    return clazz.property(qtscript_QFontDialog_FontDialogOption_toStringHelper(value));
}

static void qtscript_QFontDialog_FontDialogOption_fromScriptValue(const QScriptValue &value, QFontDialog::FontDialogOption &out)
{
    out = qvariant_cast<QFontDialog::FontDialogOption>(value.toVariant());
}

static QScriptValue qtscript_construct_QFontDialog_FontDialogOption(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QFontDialog_metaObject();
    int idx = meta->indexOfEnumerator("FontDialogOption");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QFontDialog::FontDialogOption>(arg));
    return context->throwError(QString::fromLatin1("FontDialogOption(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFontDialog_FontDialogOption_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFontDialog::FontDialogOption value = qscriptvalue_cast<QFontDialog::FontDialogOption>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFontDialog_FontDialogOption_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFontDialog::FontDialogOption value = qscriptvalue_cast<QFontDialog::FontDialogOption>(context->thisObject());
    return QScriptValue(engine, qtscript_QFontDialog_FontDialogOption_toStringHelper(value));
}

static QScriptValue qtscript_create_QFontDialog_FontDialogOption_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFontDialog_FontDialogOption,
        qtscript_QFontDialog_FontDialogOption_valueOf, qtscript_QFontDialog_FontDialogOption_toString);
    qScriptRegisterMetaType<QFontDialog::FontDialogOption>(engine, qtscript_QFontDialog_FontDialogOption_toScriptValue,
        qtscript_QFontDialog_FontDialogOption_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFontDialog_FontDialogOption_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFontDialog_FontDialogOption_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFontDialog::FontDialogOptions
//

static QScriptValue qtscript_QFontDialog_FontDialogOptions_toScriptValue(QScriptEngine *engine, const QFontDialog::FontDialogOptions &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QFontDialog_FontDialogOptions_fromScriptValue(const QScriptValue &value, QFontDialog::FontDialogOptions &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QFontDialog::FontDialogOptions>())
        out = qvariant_cast<QFontDialog::FontDialogOptions>(var);
    else if (var.userType() == qMetaTypeId<QFontDialog::FontDialogOption>())
        out = qvariant_cast<QFontDialog::FontDialogOption>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QFontDialog_FontDialogOptions(QScriptContext *context, QScriptEngine *engine)
{
    QFontDialog::FontDialogOptions result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QFontDialog::FontDialogOptions>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QFontDialog::FontDialogOption>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("FontDialogOptions(): argument %0 is not of type FontDialogOption").arg(i));
            }
            result |= qvariant_cast<QFontDialog::FontDialogOption>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QFontDialog_FontDialogOptions_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFontDialog::FontDialogOptions value = qscriptvalue_cast<QFontDialog::FontDialogOptions>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFontDialog_FontDialogOptions_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFontDialog::FontDialogOptions value = qscriptvalue_cast<QFontDialog::FontDialogOptions>(context->thisObject());
    QString result;
    for (int i = 0; i < 2; ++i) {
        if ((value & qtscript_QFontDialog_FontDialogOption_values[i]) == qtscript_QFontDialog_FontDialogOption_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QFontDialog_FontDialogOption_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QFontDialog_FontDialogOptions_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QFontDialog::FontDialogOptions>() == otherObj.value<QFontDialog::FontDialogOptions>())));
}

static QScriptValue qtscript_create_QFontDialog_FontDialogOptions_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QFontDialog_FontDialogOptions, qtscript_QFontDialog_FontDialogOptions_valueOf,
        qtscript_QFontDialog_FontDialogOptions_toString, qtscript_QFontDialog_FontDialogOptions_equals);
    qScriptRegisterMetaType<QFontDialog::FontDialogOptions>(engine, qtscript_QFontDialog_FontDialogOptions_toScriptValue,
        qtscript_QFontDialog_FontDialogOptions_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QFontDialog
//

static QScriptValue qtscript_QFontDialog_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QFontDialog* _q_self = qscriptvalue_cast<QFontDialog*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFontDialog.%0(): this object is not a QFontDialog")
            .arg(qtscript_QFontDialog_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        char* _q_arg1 = qscriptvalue_cast<char*>(context->argument(1));
        _q_self->open(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QFont _q_result = _q_self->selectedFont();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QFontDialog::FontDialogOption _q_arg0 = qscriptvalue_cast<QFontDialog::FontDialogOption>(context->argument(0));
        _q_self->setOption(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QFontDialog::FontDialogOption _q_arg0 = qscriptvalue_cast<QFontDialog::FontDialogOption>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QFontDialog::FontDialogOption _q_arg0 = qscriptvalue_cast<QFontDialog::FontDialogOption>(context->argument(0));
        bool _q_result = _q_self->testOption(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4: {
    QString result = QString::fromLatin1("QFontDialog");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFontDialog_throw_ambiguity_error_helper(context,
        qtscript_QFontDialog_function_names[_id+2],
        qtscript_QFontDialog_function_signatures[_id+2]);
}

static QScriptValue qtscript_QFontDialog_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFontDialog(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QFontDialog* _q_cpp_result = new QtScriptShell_QFontDialog();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFontDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QFontDialog* _q_cpp_result = new QtScriptShell_QFontDialog(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFontDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QFont>() == context->argument(0).toVariant().userType())) {
            QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
            QtScriptShell_QFontDialog* _q_cpp_result = new QtScriptShell_QFontDialog(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFontDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QFontDialog* _q_cpp_result = new QtScriptShell_QFontDialog(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFontDialog*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg0 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  QFont _q_result = QFontDialog::getFont(_q_arg0);
        
          // TEMPLATE - core.convert_to_null_or_wrap - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = qScriptValueFromValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_wrap - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg0 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                      QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QFont _q_result = QFontDialog::getFont(_q_arg0, _q_arg1);
            
          // TEMPLATE - core.convert_to_null_or_wrap - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = qScriptValueFromValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_wrap - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
        } else if ((qMetaTypeId<QFont>() == context->argument(0).toVariant().userType())) {

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg0 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                      QFont _q_arg1 = qscriptvalue_cast<QFont>(context->argument(0));
            QFont _q_result = QFontDialog::getFont(_q_arg0, _q_arg1);
            
          // TEMPLATE - core.convert_to_null_or_wrap - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = qScriptValueFromValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_wrap - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
        }
    }
    if (context->argumentCount() == 2) {

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg0 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  QFont _q_arg1 = qscriptvalue_cast<QFont>(context->argument(0));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QFont _q_result = QFontDialog::getFont(_q_arg0, _q_arg1, _q_arg2);
        
          // TEMPLATE - core.convert_to_null_or_wrap - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = qScriptValueFromValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_wrap - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    if (context->argumentCount() == 3) {

          // TEMPLATE - core.prepare_removed_bool*_argument - START
          bool __ok;
          bool *_q_arg0 = &__ok;
    // TEMPLATE - core.prepare_removed_bool*_argument - END
                  QFont _q_arg1 = qscriptvalue_cast<QFont>(context->argument(0));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QString _q_arg3 = context->argument(2).toString();
        QFont _q_result = QFontDialog::getFont(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        
          // TEMPLATE - core.convert_to_null_or_wrap - START
          QScriptValue _q_convertedResult;
          if (!__ok)
              _q_convertedResult = context->engine()->nullValue();
          else
              _q_convertedResult = qScriptValueFromValue(context->engine(), _q_result);
    // TEMPLATE - core.convert_to_null_or_wrap - END
          return qScriptValueFromValue(context->engine(), _q_convertedResult);
    }
    if (context->argumentCount() == 5) {
        bool* _q_arg0 = qscriptvalue_cast<bool*>(context->argument(0));
        QFont _q_arg1 = qscriptvalue_cast<QFont>(context->argument(1));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        QString _q_arg3 = context->argument(3).toString();
        QFlags<QFontDialog::FontDialogOption> _q_arg4 = qscriptvalue_cast<QFlags<QFontDialog::FontDialogOption> >(context->argument(4));
        QFont _q_result = QFontDialog::getFont(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFontDialog_throw_ambiguity_error_helper(context,
        qtscript_QFontDialog_function_names[_id],
        qtscript_QFontDialog_function_signatures[_id]);
}

static QScriptValue qtscript_QFontDialog_toScriptValue(QScriptEngine *engine, QFontDialog* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QFontDialog_fromScriptValue(const QScriptValue &value, QFontDialog* &out)
{
    out = qobject_cast<QFontDialog*>(value.toQObject());
}

QScriptValue qtscript_create_QFontDialog_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFontDialog*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFontDialog*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDialog*>()));
    for (int i = 0; i < 5; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFontDialog_prototype_call, qtscript_QFontDialog_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFontDialog_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QFontDialog*>(engine, qtscript_QFontDialog_toScriptValue, 
        qtscript_QFontDialog_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFontDialog_static_call, proto, qtscript_QFontDialog_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFontDialog_static_call,
            qtscript_QFontDialog_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QFontDialog_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("FontDialogOption"),
        qtscript_create_QFontDialog_FontDialogOption_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("FontDialogOptions"),
        qtscript_create_QFontDialog_FontDialogOptions_class(engine));
    return ctor;
}
