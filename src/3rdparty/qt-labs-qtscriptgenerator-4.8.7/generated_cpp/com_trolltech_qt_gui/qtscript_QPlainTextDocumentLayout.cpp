#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qplaintextedit.h>
#include <QAbstractTextDocumentLayout>
#include <QVariant>
#include <qpainter.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <qtextdocument.h>
#include <qtextobject.h>

#include "qtscriptshell_QPlainTextDocumentLayout.h"

static const char * const qtscript_QPlainTextDocumentLayout_function_names[] = {
    "QPlainTextDocumentLayout"
    // static
    // prototype
    , "blockBoundingRect"
    , "documentSize"
    , "draw"
    , "ensureBlockLayout"
    , "frameBoundingRect"
    , "hitTest"
    , "pageCount"
    , "requestUpdate"
    , "toString"
};

static const char * const qtscript_QPlainTextDocumentLayout_function_signatures[] = {
    "QTextDocument document"
    // static
    // prototype
    , "QTextBlock block"
    , ""
    , "QPainter arg__1, QAbstractTextDocumentLayout_PaintContext arg__2"
    , "QTextBlock block"
    , "QTextFrame arg__1"
    , "QPointF arg__1, HitTestAccuracy arg__2"
    , ""
    , ""
""
};

static const int qtscript_QPlainTextDocumentLayout_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 0
    , 2
    , 1
    , 1
    , 2
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QPlainTextDocumentLayout_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPlainTextDocumentLayout::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPlainTextDocumentLayout*)
Q_DECLARE_METATYPE(QtScriptShell_QPlainTextDocumentLayout*)
Q_DECLARE_METATYPE(QTextBlock)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QAbstractTextDocumentLayout::PaintContext)
Q_DECLARE_METATYPE(QTextFrame*)
Q_DECLARE_METATYPE(Qt::HitTestAccuracy)
Q_DECLARE_METATYPE(QTextDocument*)

//
// QPlainTextDocumentLayout
//

static QScriptValue qtscript_QPlainTextDocumentLayout_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QPlainTextDocumentLayout* _q_self = qscriptvalue_cast<QPlainTextDocumentLayout*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPlainTextDocumentLayout.%0(): this object is not a QPlainTextDocumentLayout")
            .arg(qtscript_QPlainTextDocumentLayout_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QTextBlock _q_arg0 = qscriptvalue_cast<QTextBlock>(context->argument(0));
        QRectF _q_result = _q_self->blockBoundingRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QSizeF _q_result = _q_self->documentSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QAbstractTextDocumentLayout::PaintContext _q_arg1 = qscriptvalue_cast<QAbstractTextDocumentLayout::PaintContext>(context->argument(1));
        _q_self->draw(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QTextBlock _q_arg0 = qscriptvalue_cast<QTextBlock>(context->argument(0));
        _q_self->ensureBlockLayout(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QTextFrame* _q_arg0 = qscriptvalue_cast<QTextFrame*>(context->argument(0));
        QRectF _q_result = _q_self->frameBoundingRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        Qt::HitTestAccuracy _q_arg1 = qscriptvalue_cast<Qt::HitTestAccuracy>(context->argument(1));
        int _q_result = _q_self->hitTest(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->pageCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        _q_self->requestUpdate();
        return context->engine()->undefinedValue();
    }
    break;

    case 8: {
    QString result = QString::fromLatin1("QPlainTextDocumentLayout");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPlainTextDocumentLayout_throw_ambiguity_error_helper(context,
        qtscript_QPlainTextDocumentLayout_function_names[_id+1],
        qtscript_QPlainTextDocumentLayout_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPlainTextDocumentLayout_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPlainTextDocumentLayout(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QTextDocument* _q_arg0 = qscriptvalue_cast<QTextDocument*>(context->argument(0));
        QtScriptShell_QPlainTextDocumentLayout* _q_cpp_result = new QtScriptShell_QPlainTextDocumentLayout(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue((QPlainTextDocumentLayout*)_q_cpp_result));
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPlainTextDocumentLayout_throw_ambiguity_error_helper(context,
        qtscript_QPlainTextDocumentLayout_function_names[_id],
        qtscript_QPlainTextDocumentLayout_function_signatures[_id]);
}

QScriptValue qtscript_create_QPlainTextDocumentLayout_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPlainTextDocumentLayout*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPlainTextDocumentLayout*)0));
    for (int i = 0; i < 9; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPlainTextDocumentLayout_prototype_call, qtscript_QPlainTextDocumentLayout_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPlainTextDocumentLayout_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QPlainTextDocumentLayout*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPlainTextDocumentLayout_static_call, proto, qtscript_QPlainTextDocumentLayout_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
