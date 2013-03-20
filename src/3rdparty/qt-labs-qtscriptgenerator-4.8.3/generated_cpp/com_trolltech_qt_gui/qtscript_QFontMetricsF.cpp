#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qfontmetrics.h>
#include <QVariant>
#include <qfont.h>
#include <qpaintdevice.h>
#include <qrect.h>
#include <qsize.h>

static const char * const qtscript_QFontMetricsF_function_names[] = {
    "QFontMetricsF"
    // static
    // prototype
    , "ascent"
    , "averageCharWidth"
    , "boundingRect"
    , "descent"
    , "elidedText"
    , "height"
    , "inFont"
    , "inFontUcs4"
    , "leading"
    , "leftBearing"
    , "lineSpacing"
    , "lineWidth"
    , "maxWidth"
    , "minLeftBearing"
    , "minRightBearing"
    , "overlinePos"
    , "rightBearing"
    , "size"
    , "strikeOutPos"
    , "tightBoundingRect"
    , "underlinePos"
    , "width"
    , "xHeight"
    , "toString"
};

static const char * const qtscript_QFontMetricsF_function_signatures[] = {
    "QFont arg__1\nQFont arg__1, QPaintDevice pd"
    // static
    // prototype
    , ""
    , ""
    , "char arg__1\nQRectF r, int flags, String string, int tabstops, int tabarray\nString string"
    , ""
    , "String text, TextElideMode mode, qreal width, int flags"
    , ""
    , "char arg__1"
    , "uint ucs4"
    , ""
    , "char arg__1"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "char arg__1"
    , "int flags, String str, int tabstops, int tabarray"
    , ""
    , "String text"
    , ""
    , "char arg__1\nString string"
    , ""
""
};

static const int qtscript_QFontMetricsF_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 5
    , 0
    , 4
    , 0
    , 1
    , 1
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 4
    , 0
    , 1
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QFontMetricsF_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFontMetricsF::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFontMetricsF*)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(Qt::TextElideMode)
Q_DECLARE_METATYPE(QPaintDevice*)

//
// QFontMetricsF
//

static QScriptValue qtscript_QFontMetricsF_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 23;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QFontMetricsF* _q_self = qscriptvalue_cast<QFontMetricsF*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFontMetricsF.%0(): this object is not a QFontMetricsF")
            .arg(qtscript_QFontMetricsF_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->ascent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->averageCharWidth();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QChar>() == context->argument(0).toVariant().userType())) {
            QChar _q_arg0 = qscriptvalue_cast<QChar>(context->argument(0));
            QRectF _q_result = _q_self->boundingRect(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QRectF _q_result = _q_self->boundingRect(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 5) {
        QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QString _q_arg2 = context->argument(2).toString();
        int _q_arg3 = context->argument(3).toInt32();
        int* _q_arg4 = qscriptvalue_cast<int*>(context->argument(4));
        QRectF _q_result = _q_self->boundingRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->descent();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        Qt::TextElideMode _q_arg1 = qscriptvalue_cast<Qt::TextElideMode>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        QString _q_result = _q_self->elidedText(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        Qt::TextElideMode _q_arg1 = qscriptvalue_cast<Qt::TextElideMode>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        int _q_arg3 = context->argument(3).toInt32();
        QString _q_result = _q_self->elidedText(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->height();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QChar _q_arg0 = qscriptvalue_cast<QChar>(context->argument(0));
        bool _q_result = _q_self->inFont(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        uint _q_arg0 = context->argument(0).toUInt32();
        bool _q_result = _q_self->inFontUcs4(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->leading();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QChar _q_arg0 = qscriptvalue_cast<QChar>(context->argument(0));
        qreal _q_result = _q_self->leftBearing(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->lineSpacing();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->lineWidth();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->maxWidth();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->minLeftBearing();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->minRightBearing();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->overlinePos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QChar _q_arg0 = qscriptvalue_cast<QChar>(context->argument(0));
        qreal _q_result = _q_self->rightBearing(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        int _q_arg2 = context->argument(2).toInt32();
        int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
        QSizeF _q_result = _q_self->size(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->strikeOutPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QRectF _q_result = _q_self->tightBoundingRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->underlinePos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QChar>() == context->argument(0).toVariant().userType())) {
            QChar _q_arg0 = qscriptvalue_cast<QChar>(context->argument(0));
            qreal _q_result = _q_self->width(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            qreal _q_result = _q_self->width(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->xHeight();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23: {
    QString result = QString::fromLatin1("QFontMetricsF");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFontMetricsF_throw_ambiguity_error_helper(context,
        qtscript_QFontMetricsF_function_names[_id+1],
        qtscript_QFontMetricsF_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFontMetricsF_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFontMetricsF(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        QFontMetricsF* _q_cpp_result = new QFontMetricsF(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        QPaintDevice* _q_arg1 = qscriptvalue_cast<QPaintDevice*>(context->argument(1));
        QFontMetricsF* _q_cpp_result = new QFontMetricsF(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFontMetricsF_throw_ambiguity_error_helper(context,
        qtscript_QFontMetricsF_function_names[_id],
        qtscript_QFontMetricsF_function_signatures[_id]);
}

QScriptValue qtscript_create_QFontMetricsF_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFontMetricsF*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFontMetricsF*)0));
    for (int i = 0; i < 24; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFontMetricsF_prototype_call, qtscript_QFontMetricsF_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFontMetricsF_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QFontMetricsF*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFontMetricsF_static_call, proto, qtscript_QFontMetricsF_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
