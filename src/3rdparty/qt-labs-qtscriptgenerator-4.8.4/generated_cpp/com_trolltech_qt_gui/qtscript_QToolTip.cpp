#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtooltip.h>
#include <QVariant>
#include <qfont.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qrect.h>
#include <qwidget.h>

static const char * const qtscript_QToolTip_function_names[] = {
    "QToolTip"
    // static
    , "font"
    , "hideText"
    , "isVisible"
    , "palette"
    , "setFont"
    , "setPalette"
    , "showText"
    , "text"
    // prototype
    , "toString"
};

static const char * const qtscript_QToolTip_function_signatures[] = {
    ""
    // static
    , ""
    , ""
    , ""
    , ""
    , "QFont arg__1"
    , "QPalette arg__1"
    , "QPoint pos, String text, QWidget w\nQPoint pos, String text, QWidget w, QRect rect"
    , ""
    // prototype
""
};

static const int qtscript_QToolTip_function_lengths[] = {
    0
    // static
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 4
    , 0
    // prototype
    , 0
};

static QScriptValue qtscript_QToolTip_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QToolTip::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QToolTip*)

//
// QToolTip
//

static QScriptValue qtscript_QToolTip_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QToolTip* _q_self = qscriptvalue_cast<QToolTip*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QToolTip.%0(): this object is not a QToolTip")
            .arg(qtscript_QToolTip_function_names[_id+9]));
    }

    switch (_id) {
    case 0: {
    QString result = QString::fromLatin1("QToolTip");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QToolTip_throw_ambiguity_error_helper(context,
        qtscript_QToolTip_function_names[_id+9],
        qtscript_QToolTip_function_signatures[_id+9]);
}

static QScriptValue qtscript_QToolTip_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QToolTip cannot be constructed"));
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QFont _q_result = QToolTip::font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QToolTip::hideText();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = QToolTip::isVisible();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QPalette _q_result = QToolTip::palette();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        QToolTip::setFont(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QPalette _q_arg0 = qscriptvalue_cast<QPalette>(context->argument(0));
        QToolTip::setPalette(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QToolTip::showText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        QToolTip::showText(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        QRect _q_arg3 = qscriptvalue_cast<QRect>(context->argument(3));
        QToolTip::showText(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QString _q_result = QToolTip::text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QToolTip_throw_ambiguity_error_helper(context,
        qtscript_QToolTip_function_names[_id],
        qtscript_QToolTip_function_signatures[_id]);
}

QScriptValue qtscript_create_QToolTip_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QToolTip*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QToolTip*)0));

    engine->setDefaultPrototype(qMetaTypeId<QToolTip*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QToolTip_static_call, proto, qtscript_QToolTip_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QToolTip_static_call,
            qtscript_QToolTip_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QToolTip_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
