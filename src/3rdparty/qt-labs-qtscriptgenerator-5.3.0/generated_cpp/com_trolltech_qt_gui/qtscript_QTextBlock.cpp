#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtextobject.h>
#include <QTextBlock>
#include <QTextLayout>
#include <QVariant>
#include <qtextdocument.h>
#include <qtextformat.h>
#include <qtextlayout.h>
#include <qtextlist.h>
#include <qtextobject.h>
#include <qvector.h>

static const char * const qtscript_QTextBlock_function_names[] = {
    "QTextBlock"
    // static
    // prototype
    , "begin"
    , "blockFormat"
    , "blockFormatIndex"
    , "blockNumber"
    , "charFormat"
    , "charFormatIndex"
    , "clearLayout"
    , "contains"
    , "document"
    , "end"
    , "firstLineNumber"
    , "fragmentIndex"
    , "isValid"
    , "isVisible"
    , "layout"
    , "length"
    , "lineCount"
    , "next"
    , "equals"
    , "operator_less"
    , "position"
    , "previous"
    , "revision"
    , "setLineCount"
    , "setRevision"
    , "setUserData"
    , "setUserState"
    , "setVisible"
    , "text"
    , "textDirection"
    , "textFormats"
    , "textList"
    , "userData"
    , "userState"
    , "toString"
};

static const char * const qtscript_QTextBlock_function_signatures[] = {
    "\nQTextBlock o"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "int position"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QTextBlock o"
    , "QTextBlock o"
    , ""
    , ""
    , ""
    , "int count"
    , "int rev"
    , "QTextBlockUserData data"
    , "int state"
    , "bool visible"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QTextBlock_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
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

static QScriptValue qtscript_QTextBlock_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextBlock::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextBlock)
Q_DECLARE_METATYPE(QTextBlock*)
Q_DECLARE_METATYPE(QTextBlock::iterator)
Q_DECLARE_METATYPE(QTextBlockFormat)
Q_DECLARE_METATYPE(QTextCharFormat)
Q_DECLARE_METATYPE(const QTextDocument*)
Q_DECLARE_METATYPE(QTextLayout*)
Q_DECLARE_METATYPE(QTextBlockUserData*)
Q_DECLARE_METATYPE(Qt::LayoutDirection)
Q_DECLARE_METATYPE(QTextLayout::FormatRange)
Q_DECLARE_METATYPE(QVector<QTextLayout::FormatRange >)
Q_DECLARE_METATYPE(QTextList*)

//
// QTextBlock
//

static QScriptValue qtscript_QTextBlock_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 34;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextBlock* _q_self = qscriptvalue_cast<QTextBlock*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextBlock.%0(): this object is not a QTextBlock")
            .arg(qtscript_QTextBlock_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QTextBlock::iterator _q_result = _q_self->begin();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QTextBlockFormat _q_result = _q_self->blockFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->blockFormatIndex();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->blockNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QTextCharFormat _q_result = _q_self->charFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->charFormatIndex();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        _q_self->clearLayout();
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->contains(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        const QTextDocument* _q_result = const_cast<const QTextDocument*>(_q_self->document());
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QTextBlock::iterator _q_result = _q_self->end();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->firstLineNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->fragmentIndex();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isVisible();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QTextLayout* _q_result = _q_self->layout();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->length();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->lineCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        QTextBlock _q_result = _q_self->next();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QTextBlock _q_arg0 = qscriptvalue_cast<QTextBlock>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QTextBlock _q_arg0 = qscriptvalue_cast<QTextBlock>(context->argument(0));
        bool _q_result = _q_self->operator<(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->position();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        QTextBlock _q_result = _q_self->previous();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->revision();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setLineCount(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setRevision(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QTextBlockUserData* _q_arg0 = qscriptvalue_cast<QTextBlockUserData*>(context->argument(0));
        _q_self->setUserData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setUserState(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setVisible(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->text();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 29:
    if (context->argumentCount() == 0) {
        Qt::LayoutDirection _q_result = _q_self->textDirection();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 0) {
        QVector<QTextLayout::FormatRange > _q_result = _q_self->textFormats();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 31:
    if (context->argumentCount() == 0) {
        QTextList* _q_result = _q_self->textList();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        QTextBlockUserData* _q_result = _q_self->userData();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->userState();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34: {
    QString result = QString::fromLatin1("QTextBlock");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextBlock_throw_ambiguity_error_helper(context,
        qtscript_QTextBlock_function_names[_id+1],
        qtscript_QTextBlock_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextBlock_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextBlock(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTextBlock _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QTextBlock _q_arg0 = qscriptvalue_cast<QTextBlock>(context->argument(0));
        QTextBlock _q_cpp_result(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextBlock_throw_ambiguity_error_helper(context,
        qtscript_QTextBlock_function_names[_id],
        qtscript_QTextBlock_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextBlock_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextBlock*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextBlock*)0));
    for (int i = 0; i < 35; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextBlock_prototype_call, qtscript_QTextBlock_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextBlock_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextBlock>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextBlock*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextBlock_static_call, proto, qtscript_QTextBlock_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
