#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qgraphicsitem.h>
#include <QTextCursor>
#include <QVariant>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qgraphicstransform.h>
#include <qgraphicswidget.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qstyleoption.h>
#include <qtextcursor.h>
#include <qtextdocument.h>
#include <qtransform.h>
#include <qwidget.h>

#include "qtscriptshell_QGraphicsTextItem.h"

static const char * const qtscript_QGraphicsTextItem_function_names[] = {
    "QGraphicsTextItem"
    // static
    // prototype
    , "adjustSize"
    , "defaultTextColor"
    , "document"
    , "font"
    , "openExternalLinks"
    , "setDefaultTextColor"
    , "setDocument"
    , "setFont"
    , "setHtml"
    , "setOpenExternalLinks"
    , "setPlainText"
    , "setTabChangesFocus"
    , "setTextCursor"
    , "setTextInteractionFlags"
    , "setTextWidth"
    , "tabChangesFocus"
    , "textCursor"
    , "textInteractionFlags"
    , "textWidth"
    , "toHtml"
    , "toPlainText"
    , "toString"
};

static const char * const qtscript_QGraphicsTextItem_function_signatures[] = {
    "QGraphicsItem parent, QGraphicsScene scene\nString text, QGraphicsItem parent, QGraphicsScene scene"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QColor c"
    , "QTextDocument document"
    , "QFont font"
    , "String html"
    , "bool open"
    , "String text"
    , "bool b"
    , "QTextCursor cursor"
    , "TextInteractionFlags flags"
    , "qreal width"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QGraphicsTextItem_function_lengths[] = {
    3
    // static
    // prototype
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
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsTextItem_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsTextItem::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsTextItem*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsTextItem*)
Q_DECLARE_METATYPE(QTextDocument*)
Q_DECLARE_METATYPE(QTextCursor)
Q_DECLARE_METATYPE(QFlags<Qt::TextInteractionFlag>)
Q_DECLARE_METATYPE(QGraphicsObject*)

//
// QGraphicsTextItem
//

static QScriptValue qtscript_QGraphicsTextItem_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 21;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsTextItem* _q_self = qscriptvalue_cast<QGraphicsTextItem*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsTextItem.%0(): this object is not a QGraphicsTextItem")
            .arg(qtscript_QGraphicsTextItem_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->adjustSize();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->defaultTextColor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QTextDocument* _q_result = _q_self->document();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QFont _q_result = _q_self->font();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->openExternalLinks();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QColor _q_arg0 = qscriptvalue_cast<QColor>(context->argument(0));
        _q_self->setDefaultTextColor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QTextDocument* _q_arg0 = qscriptvalue_cast<QTextDocument*>(context->argument(0));
        _q_self->setDocument(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QFont _q_arg0 = qscriptvalue_cast<QFont>(context->argument(0));
        _q_self->setFont(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setHtml(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setOpenExternalLinks(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setPlainText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setTabChangesFocus(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
        _q_self->setTextCursor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QFlags<Qt::TextInteractionFlag> _q_arg0 = qscriptvalue_cast<QFlags<Qt::TextInteractionFlag> >(context->argument(0));
        _q_self->setTextInteractionFlags(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setTextWidth(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->tabChangesFocus();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QTextCursor _q_result = _q_self->textCursor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QFlags<Qt::TextInteractionFlag> _q_result = _q_self->textInteractionFlags();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->textWidth();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toHtml();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toPlainText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21: {
    QString result = QString::fromLatin1("QGraphicsTextItem");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsTextItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsTextItem_function_names[_id+1],
        qtscript_QGraphicsTextItem_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsTextItem_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsTextItem(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsTextItem* _q_cpp_result = new QtScriptShell_QGraphicsTextItem();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsTextItem*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QtScriptShell_QGraphicsTextItem* _q_cpp_result = new QtScriptShell_QGraphicsTextItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsTextItem*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QGraphicsTextItem* _q_cpp_result = new QtScriptShell_QGraphicsTextItem(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsTextItem*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<QGraphicsItem*>(context->argument(0))
            && qscriptvalue_cast<QGraphicsScene*>(context->argument(1))) {
            QGraphicsItem* _q_arg0 = qscriptvalue_cast<QGraphicsItem*>(context->argument(0));
            QGraphicsScene* _q_arg1 = qscriptvalue_cast<QGraphicsScene*>(context->argument(1));
            QtScriptShell_QGraphicsTextItem* _q_cpp_result = new QtScriptShell_QGraphicsTextItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsTextItem*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()
            && qscriptvalue_cast<QGraphicsItem*>(context->argument(1))) {
            QString _q_arg0 = context->argument(0).toString();
            QGraphicsItem* _q_arg1 = qscriptvalue_cast<QGraphicsItem*>(context->argument(1));
            QtScriptShell_QGraphicsTextItem* _q_cpp_result = new QtScriptShell_QGraphicsTextItem(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsTextItem*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        QString _q_arg0 = context->argument(0).toString();
        QGraphicsItem* _q_arg1 = qscriptvalue_cast<QGraphicsItem*>(context->argument(1));
        QGraphicsScene* _q_arg2 = qscriptvalue_cast<QGraphicsScene*>(context->argument(2));
        QtScriptShell_QGraphicsTextItem* _q_cpp_result = new QtScriptShell_QGraphicsTextItem(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsTextItem*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsTextItem_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsTextItem_function_names[_id],
        qtscript_QGraphicsTextItem_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsTextItem_toScriptValue(QScriptEngine *engine, QGraphicsTextItem* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsTextItem_fromScriptValue(const QScriptValue &value, QGraphicsTextItem* &out)
{
    out = qobject_cast<QGraphicsTextItem*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsTextItem_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsTextItem*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsTextItem*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsObject*>()));
    for (int i = 0; i < 22; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsTextItem_prototype_call, qtscript_QGraphicsTextItem_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsTextItem_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGraphicsTextItem*>(engine, qtscript_QGraphicsTextItem_toScriptValue, 
        qtscript_QGraphicsTextItem_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsTextItem_static_call, proto, qtscript_QGraphicsTextItem_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
