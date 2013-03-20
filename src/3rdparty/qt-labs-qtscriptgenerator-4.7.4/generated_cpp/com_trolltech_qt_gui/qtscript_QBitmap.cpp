#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qbitmap.h>
#include <QVariant>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qimage.h>
#include <qimagereader.h>
#include <qimagewriter.h>
#include <qiodevice.h>
#include <qmatrix.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qtransform.h>
#include <qwidget.h>

#include "qtscriptshell_QBitmap.h"

static const char * const qtscript_QBitmap_function_names[] = {
    "QBitmap"
    // static
    // prototype
    , "clear"
    , "transformed"
    , "toString"
};

static const char * const qtscript_QBitmap_function_signatures[] = {
    "\nQPixmap arg__1\nQSize arg__1\nString fileName, char format\nint w, int h"
    // static
    // prototype
    , ""
    , "QMatrix arg__1\nQTransform matrix"
""
};

static const int qtscript_QBitmap_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QBitmap_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QBitmap::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QBitmap*)
Q_DECLARE_METATYPE(QtScriptShell_QBitmap)
Q_DECLARE_METATYPE(QtScriptShell_QBitmap*)
Q_DECLARE_METATYPE(QPixmap*)

//
// QBitmap
//

static QScriptValue qtscript_QBitmap_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QBitmap* _q_self = qscriptvalue_cast<QBitmap*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QBitmap.%0(): this object is not a QBitmap")
            .arg(qtscript_QBitmap_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QMatrix>() == context->argument(0).toVariant().userType())) {
            QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
            QBitmap _q_result = _q_self->transformed(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTransform>() == context->argument(0).toVariant().userType())) {
            QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
            QBitmap _q_result = _q_self->transformed(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("QBitmap");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QBitmap_throw_ambiguity_error_helper(context,
        qtscript_QBitmap_function_names[_id+1],
        qtscript_QBitmap_function_signatures[_id+1]);
}

static QScriptValue qtscript_QBitmap_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QBitmap(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QBitmap _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QBitmap)_q_cpp_result));
        _q_cpp_result.__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPixmap>() == context->argument(0).toVariant().userType())) {
            QPixmap _q_arg0 = qscriptvalue_cast<QPixmap>(context->argument(0));
            QtScriptShell_QBitmap _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QBitmap)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<QSize>() == context->argument(0).toVariant().userType())) {
            QSize _q_arg0 = qscriptvalue_cast<QSize>(context->argument(0));
            QtScriptShell_QBitmap _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QBitmap)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && context->argument(1).isString()) {
            QString _q_arg0 = context->argument(0).toString();

          // TEMPLATE - core.convert_string_arg_to_char* - START
          QByteArray tmp__q_arg1 = context->argument(1).toString().toLatin1();
          const char * _q_arg1 = tmp__q_arg1.constData();
    // TEMPLATE - core.convert_string_arg_to_char* - END
                    QtScriptShell_QBitmap _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QBitmap)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QtScriptShell_QBitmap _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QBitmap)_q_cpp_result));
            _q_cpp_result.__qtscript_self = _q_result;
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QBitmap_throw_ambiguity_error_helper(context,
        qtscript_QBitmap_function_names[_id],
        qtscript_QBitmap_function_signatures[_id]);
}

QScriptValue qtscript_create_QBitmap_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QBitmap*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QBitmap*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QPixmap*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QBitmap_prototype_call, qtscript_QBitmap_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QBitmap_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QBitmap>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QBitmap*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QBitmap_static_call, proto, qtscript_QBitmap_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
