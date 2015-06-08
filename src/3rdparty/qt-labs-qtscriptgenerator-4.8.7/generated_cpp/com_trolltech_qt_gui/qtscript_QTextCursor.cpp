#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qtextcursor.h>
#include <QTextBlock>
#include <QTextDocumentFragment>
#include <QVariant>
#include <qimage.h>
#include <qtextcursor.h>
#include <qtextdocument.h>
#include <qtextdocumentfragment.h>
#include <qtextformat.h>
#include <qtextlist.h>
#include <qtextobject.h>
#include <qtexttable.h>

static const char * const qtscript_QTextCursor_function_names[] = {
    "QTextCursor"
    // static
    // prototype
    , "anchor"
    , "atBlockEnd"
    , "atBlockStart"
    , "atEnd"
    , "atStart"
    , "beginEditBlock"
    , "block"
    , "blockCharFormat"
    , "blockFormat"
    , "blockNumber"
    , "charFormat"
    , "clearSelection"
    , "columnNumber"
    , "createList"
    , "currentFrame"
    , "currentList"
    , "currentTable"
    , "deleteChar"
    , "deletePreviousChar"
    , "document"
    , "endEditBlock"
    , "hasComplexSelection"
    , "hasSelection"
    , "insertBlock"
    , "insertFragment"
    , "insertFrame"
    , "insertHtml"
    , "insertImage"
    , "insertList"
    , "insertTable"
    , "insertText"
    , "isCopyOf"
    , "isNull"
    , "joinPreviousEditBlock"
    , "keepPositionOnInsert"
    , "mergeBlockCharFormat"
    , "mergeBlockFormat"
    , "mergeCharFormat"
    , "movePosition"
    , "equals"
    , "operator_less"
    , "position"
    , "positionInBlock"
    , "removeSelectedText"
    , "select"
    , "selectedTableCells"
    , "selectedText"
    , "selection"
    , "selectionEnd"
    , "selectionStart"
    , "setBlockCharFormat"
    , "setBlockFormat"
    , "setCharFormat"
    , "setKeepPositionOnInsert"
    , "setPosition"
    , "setVerticalMovementX"
    , "setVisualNavigation"
    , "verticalMovementX"
    , "visualNavigation"
    , "toString"
};

static const char * const qtscript_QTextCursor_function_signatures[] = {
    "\nQTextDocument document\nQTextFrame frame\nQTextBlock block\nQTextCursor cursor"
    // static
    // prototype
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
    , ""
    , ""
    , ""
    , "Style style\nQTextListFormat format"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "\nQTextBlockFormat format\nQTextBlockFormat format, QTextCharFormat charFormat"
    , "QTextDocumentFragment fragment"
    , "QTextFrameFormat format"
    , "String html"
    , "QImage image, String name\nString name\nQTextImageFormat format\nQTextImageFormat format, Position alignment"
    , "Style style\nQTextListFormat format"
    , "int rows, int cols\nint rows, int cols, QTextTableFormat format"
    , "String text\nString text, QTextCharFormat format"
    , "QTextCursor other"
    , ""
    , ""
    , ""
    , "QTextCharFormat modifier"
    , "QTextBlockFormat modifier"
    , "QTextCharFormat modifier"
    , "MoveOperation op, MoveMode arg__2, int n"
    , "QTextCursor rhs"
    , "QTextCursor rhs"
    , ""
    , ""
    , ""
    , "SelectionType selection"
    , "int firstRow, int numRows, int firstColumn, int numColumns"
    , ""
    , ""
    , ""
    , ""
    , "QTextCharFormat format"
    , "QTextBlockFormat format"
    , "QTextCharFormat format"
    , "bool b"
    , "int pos, MoveMode mode"
    , "int x"
    , "bool b"
    , ""
    , ""
""
};

static const int qtscript_QTextCursor_function_lengths[] = {
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
    , 2
    , 1
    , 1
    , 1
    , 2
    , 1
    , 3
    , 2
    , 1
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 3
    , 1
    , 1
    , 0
    , 0
    , 0
    , 1
    , 4
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 2
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTextCursor_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextCursor::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTextCursor)
Q_DECLARE_METATYPE(QTextCursor*)
Q_DECLARE_METATYPE(QTextCursor::MoveMode)
Q_DECLARE_METATYPE(QTextCursor::MoveOperation)
Q_DECLARE_METATYPE(QTextCursor::SelectionType)
Q_DECLARE_METATYPE(QTextBlock)
Q_DECLARE_METATYPE(QTextCharFormat)
Q_DECLARE_METATYPE(QTextBlockFormat)
Q_DECLARE_METATYPE(QTextListFormat::Style)
Q_DECLARE_METATYPE(QTextList*)
Q_DECLARE_METATYPE(QTextListFormat)
Q_DECLARE_METATYPE(QTextFrame*)
Q_DECLARE_METATYPE(QTextTable*)
Q_DECLARE_METATYPE(QTextDocument*)
Q_DECLARE_METATYPE(QTextDocumentFragment)
Q_DECLARE_METATYPE(QTextFrameFormat)
Q_DECLARE_METATYPE(QTextImageFormat)
Q_DECLARE_METATYPE(QTextFrameFormat::Position)
Q_DECLARE_METATYPE(QTextTableFormat)
Q_DECLARE_METATYPE(int*)

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
// QTextCursor::MoveMode
//

static const QTextCursor::MoveMode qtscript_QTextCursor_MoveMode_values[] = {
    QTextCursor::MoveAnchor
    , QTextCursor::KeepAnchor
};

static const char * const qtscript_QTextCursor_MoveMode_keys[] = {
    "MoveAnchor"
    , "KeepAnchor"
};

static QString qtscript_QTextCursor_MoveMode_toStringHelper(QTextCursor::MoveMode value)
{
    if ((value >= QTextCursor::MoveAnchor) && (value <= QTextCursor::KeepAnchor))
        return qtscript_QTextCursor_MoveMode_keys[static_cast<int>(value)-static_cast<int>(QTextCursor::MoveAnchor)];
    return QString();
}

static QScriptValue qtscript_QTextCursor_MoveMode_toScriptValue(QScriptEngine *engine, const QTextCursor::MoveMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextCursor"));
    return clazz.property(qtscript_QTextCursor_MoveMode_toStringHelper(value));
}

static void qtscript_QTextCursor_MoveMode_fromScriptValue(const QScriptValue &value, QTextCursor::MoveMode &out)
{
    out = qvariant_cast<QTextCursor::MoveMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextCursor_MoveMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextCursor::MoveAnchor) && (arg <= QTextCursor::KeepAnchor))
        return qScriptValueFromValue(engine,  static_cast<QTextCursor::MoveMode>(arg));
    return context->throwError(QString::fromLatin1("MoveMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextCursor_MoveMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextCursor::MoveMode value = qscriptvalue_cast<QTextCursor::MoveMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextCursor_MoveMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextCursor::MoveMode value = qscriptvalue_cast<QTextCursor::MoveMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextCursor_MoveMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextCursor_MoveMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextCursor_MoveMode,
        qtscript_QTextCursor_MoveMode_valueOf, qtscript_QTextCursor_MoveMode_toString);
    qScriptRegisterMetaType<QTextCursor::MoveMode>(engine, qtscript_QTextCursor_MoveMode_toScriptValue,
        qtscript_QTextCursor_MoveMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextCursor_MoveMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextCursor_MoveMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextCursor::MoveOperation
//

static const QTextCursor::MoveOperation qtscript_QTextCursor_MoveOperation_values[] = {
    QTextCursor::NoMove
    , QTextCursor::Start
    , QTextCursor::Up
    , QTextCursor::StartOfLine
    , QTextCursor::StartOfBlock
    , QTextCursor::StartOfWord
    , QTextCursor::PreviousBlock
    , QTextCursor::PreviousCharacter
    , QTextCursor::PreviousWord
    , QTextCursor::Left
    , QTextCursor::WordLeft
    , QTextCursor::End
    , QTextCursor::Down
    , QTextCursor::EndOfLine
    , QTextCursor::EndOfWord
    , QTextCursor::EndOfBlock
    , QTextCursor::NextBlock
    , QTextCursor::NextCharacter
    , QTextCursor::NextWord
    , QTextCursor::Right
    , QTextCursor::WordRight
    , QTextCursor::NextCell
    , QTextCursor::PreviousCell
    , QTextCursor::NextRow
    , QTextCursor::PreviousRow
};

static const char * const qtscript_QTextCursor_MoveOperation_keys[] = {
    "NoMove"
    , "Start"
    , "Up"
    , "StartOfLine"
    , "StartOfBlock"
    , "StartOfWord"
    , "PreviousBlock"
    , "PreviousCharacter"
    , "PreviousWord"
    , "Left"
    , "WordLeft"
    , "End"
    , "Down"
    , "EndOfLine"
    , "EndOfWord"
    , "EndOfBlock"
    , "NextBlock"
    , "NextCharacter"
    , "NextWord"
    , "Right"
    , "WordRight"
    , "NextCell"
    , "PreviousCell"
    , "NextRow"
    , "PreviousRow"
};

static QString qtscript_QTextCursor_MoveOperation_toStringHelper(QTextCursor::MoveOperation value)
{
    if ((value >= QTextCursor::NoMove) && (value <= QTextCursor::PreviousRow))
        return qtscript_QTextCursor_MoveOperation_keys[static_cast<int>(value)-static_cast<int>(QTextCursor::NoMove)];
    return QString();
}

static QScriptValue qtscript_QTextCursor_MoveOperation_toScriptValue(QScriptEngine *engine, const QTextCursor::MoveOperation &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextCursor"));
    return clazz.property(qtscript_QTextCursor_MoveOperation_toStringHelper(value));
}

static void qtscript_QTextCursor_MoveOperation_fromScriptValue(const QScriptValue &value, QTextCursor::MoveOperation &out)
{
    out = qvariant_cast<QTextCursor::MoveOperation>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextCursor_MoveOperation(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextCursor::NoMove) && (arg <= QTextCursor::PreviousRow))
        return qScriptValueFromValue(engine,  static_cast<QTextCursor::MoveOperation>(arg));
    return context->throwError(QString::fromLatin1("MoveOperation(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextCursor_MoveOperation_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextCursor::MoveOperation value = qscriptvalue_cast<QTextCursor::MoveOperation>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextCursor_MoveOperation_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextCursor::MoveOperation value = qscriptvalue_cast<QTextCursor::MoveOperation>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextCursor_MoveOperation_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextCursor_MoveOperation_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextCursor_MoveOperation,
        qtscript_QTextCursor_MoveOperation_valueOf, qtscript_QTextCursor_MoveOperation_toString);
    qScriptRegisterMetaType<QTextCursor::MoveOperation>(engine, qtscript_QTextCursor_MoveOperation_toScriptValue,
        qtscript_QTextCursor_MoveOperation_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 25; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextCursor_MoveOperation_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextCursor_MoveOperation_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextCursor::SelectionType
//

static const QTextCursor::SelectionType qtscript_QTextCursor_SelectionType_values[] = {
    QTextCursor::WordUnderCursor
    , QTextCursor::LineUnderCursor
    , QTextCursor::BlockUnderCursor
    , QTextCursor::Document
};

static const char * const qtscript_QTextCursor_SelectionType_keys[] = {
    "WordUnderCursor"
    , "LineUnderCursor"
    , "BlockUnderCursor"
    , "Document"
};

static QString qtscript_QTextCursor_SelectionType_toStringHelper(QTextCursor::SelectionType value)
{
    if ((value >= QTextCursor::WordUnderCursor) && (value <= QTextCursor::Document))
        return qtscript_QTextCursor_SelectionType_keys[static_cast<int>(value)-static_cast<int>(QTextCursor::WordUnderCursor)];
    return QString();
}

static QScriptValue qtscript_QTextCursor_SelectionType_toScriptValue(QScriptEngine *engine, const QTextCursor::SelectionType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextCursor"));
    return clazz.property(qtscript_QTextCursor_SelectionType_toStringHelper(value));
}

static void qtscript_QTextCursor_SelectionType_fromScriptValue(const QScriptValue &value, QTextCursor::SelectionType &out)
{
    out = qvariant_cast<QTextCursor::SelectionType>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextCursor_SelectionType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextCursor::WordUnderCursor) && (arg <= QTextCursor::Document))
        return qScriptValueFromValue(engine,  static_cast<QTextCursor::SelectionType>(arg));
    return context->throwError(QString::fromLatin1("SelectionType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextCursor_SelectionType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextCursor::SelectionType value = qscriptvalue_cast<QTextCursor::SelectionType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextCursor_SelectionType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextCursor::SelectionType value = qscriptvalue_cast<QTextCursor::SelectionType>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextCursor_SelectionType_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextCursor_SelectionType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextCursor_SelectionType,
        qtscript_QTextCursor_SelectionType_valueOf, qtscript_QTextCursor_SelectionType_toString);
    qScriptRegisterMetaType<QTextCursor::SelectionType>(engine, qtscript_QTextCursor_SelectionType_toScriptValue,
        qtscript_QTextCursor_SelectionType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextCursor_SelectionType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextCursor_SelectionType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextCursor
//

static QScriptValue qtscript_QTextCursor_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 59;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextCursor* _q_self = qscriptvalue_cast<QTextCursor*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextCursor.%0(): this object is not a QTextCursor")
            .arg(qtscript_QTextCursor_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->anchor();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->atBlockEnd();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->atBlockStart();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->atEnd();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->atStart();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        _q_self->beginEditBlock();
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QTextBlock _q_result = _q_self->block();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QTextCharFormat _q_result = _q_self->blockCharFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QTextBlockFormat _q_result = _q_self->blockFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->blockNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        QTextCharFormat _q_result = _q_self->charFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        _q_self->clearSelection();
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->columnNumber();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QTextListFormat::Style>() == context->argument(0).toVariant().userType())) {
            QTextListFormat::Style _q_arg0 = qscriptvalue_cast<QTextListFormat::Style>(context->argument(0));
            QTextList* _q_result = _q_self->createList(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTextListFormat>() == context->argument(0).toVariant().userType())) {
            QTextListFormat _q_arg0 = qscriptvalue_cast<QTextListFormat>(context->argument(0));
            QTextList* _q_result = _q_self->createList(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QTextFrame* _q_result = _q_self->currentFrame();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QTextList* _q_result = _q_self->currentList();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QTextTable* _q_result = _q_self->currentTable();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        _q_self->deleteChar();
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        _q_self->deletePreviousChar();
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QTextDocument* _q_result = _q_self->document();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        _q_self->endEditBlock();
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasComplexSelection();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->hasSelection();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        _q_self->insertBlock();
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 1) {
        QTextBlockFormat _q_arg0 = qscriptvalue_cast<QTextBlockFormat>(context->argument(0));
        _q_self->insertBlock(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QTextBlockFormat _q_arg0 = qscriptvalue_cast<QTextBlockFormat>(context->argument(0));
        QTextCharFormat _q_arg1 = qscriptvalue_cast<QTextCharFormat>(context->argument(1));
        _q_self->insertBlock(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        QTextDocumentFragment _q_arg0 = qscriptvalue_cast<QTextDocumentFragment>(context->argument(0));
        _q_self->insertFragment(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        QTextFrameFormat _q_arg0 = qscriptvalue_cast<QTextFrameFormat>(context->argument(0));
        QTextFrame* _q_result = _q_self->insertFrame(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->insertHtml(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QImage>() == context->argument(0).toVariant().userType())) {
            QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
            _q_self->insertImage(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            _q_self->insertImage(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QTextImageFormat>() == context->argument(0).toVariant().userType())) {
            QTextImageFormat _q_arg0 = qscriptvalue_cast<QTextImageFormat>(context->argument(0));
            _q_self->insertImage(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QImage>() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QImage _q_arg0 = qscriptvalue_cast<QImage>(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            _q_self->insertImage(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QTextImageFormat>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QTextFrameFormat::Position>() == context->argument(1).toVariant().userType())) {
            QTextImageFormat _q_arg0 = qscriptvalue_cast<QTextImageFormat>(context->argument(0));
            QTextFrameFormat::Position _q_arg1 = qscriptvalue_cast<QTextFrameFormat::Position>(context->argument(1));
            _q_self->insertImage(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QTextListFormat::Style>() == context->argument(0).toVariant().userType())) {
            QTextListFormat::Style _q_arg0 = qscriptvalue_cast<QTextListFormat::Style>(context->argument(0));
            QTextList* _q_result = _q_self->insertList(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QTextListFormat>() == context->argument(0).toVariant().userType())) {
            QTextListFormat _q_arg0 = qscriptvalue_cast<QTextListFormat>(context->argument(0));
            QTextList* _q_result = _q_self->insertList(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    break;

    case 29:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QTextTable* _q_result = _q_self->insertTable(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QTextTableFormat _q_arg2 = qscriptvalue_cast<QTextTableFormat>(context->argument(2));
        QTextTable* _q_result = _q_self->insertTable(_q_arg0, _q_arg1, _q_arg2);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->insertText(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QTextCharFormat _q_arg1 = qscriptvalue_cast<QTextCharFormat>(context->argument(1));
        _q_self->insertText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
        bool _q_result = _q_self->isCopyOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isNull();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        _q_self->joinPreviousEditBlock();
        return context->engine()->undefinedValue();
    }
    break;

    case 34:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->keepPositionOnInsert();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 1) {
        QTextCharFormat _q_arg0 = qscriptvalue_cast<QTextCharFormat>(context->argument(0));
        _q_self->mergeBlockCharFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        QTextBlockFormat _q_arg0 = qscriptvalue_cast<QTextBlockFormat>(context->argument(0));
        _q_self->mergeBlockFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        QTextCharFormat _q_arg0 = qscriptvalue_cast<QTextCharFormat>(context->argument(0));
        _q_self->mergeCharFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 38:
    if (context->argumentCount() == 1) {
        QTextCursor::MoveOperation _q_arg0 = qscriptvalue_cast<QTextCursor::MoveOperation>(context->argument(0));
        bool _q_result = _q_self->movePosition(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QTextCursor::MoveOperation _q_arg0 = qscriptvalue_cast<QTextCursor::MoveOperation>(context->argument(0));
        QTextCursor::MoveMode _q_arg1 = qscriptvalue_cast<QTextCursor::MoveMode>(context->argument(1));
        bool _q_result = _q_self->movePosition(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QTextCursor::MoveOperation _q_arg0 = qscriptvalue_cast<QTextCursor::MoveOperation>(context->argument(0));
        QTextCursor::MoveMode _q_arg1 = qscriptvalue_cast<QTextCursor::MoveMode>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        bool _q_result = _q_self->movePosition(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 39:
    if (context->argumentCount() == 1) {
        QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 40:
    if (context->argumentCount() == 1) {
        QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
        bool _q_result = _q_self->operator<(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 41:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->position();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 42:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->positionInBlock();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 43:
    if (context->argumentCount() == 0) {
        _q_self->removeSelectedText();
        return context->engine()->undefinedValue();
    }
    break;

    case 44:
    if (context->argumentCount() == 1) {
        QTextCursor::SelectionType _q_arg0 = qscriptvalue_cast<QTextCursor::SelectionType>(context->argument(0));
        _q_self->select(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 45:
    if (context->argumentCount() == 4) {
        int* _q_arg0 = qscriptvalue_cast<int*>(context->argument(0));
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
        int* _q_arg3 = qscriptvalue_cast<int*>(context->argument(3));
        _q_self->selectedTableCells(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 46:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->selectedText();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 47:
    if (context->argumentCount() == 0) {
        QTextDocumentFragment _q_result = _q_self->selection();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 48:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->selectionEnd();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 49:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->selectionStart();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 50:
    if (context->argumentCount() == 1) {
        QTextCharFormat _q_arg0 = qscriptvalue_cast<QTextCharFormat>(context->argument(0));
        _q_self->setBlockCharFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 51:
    if (context->argumentCount() == 1) {
        QTextBlockFormat _q_arg0 = qscriptvalue_cast<QTextBlockFormat>(context->argument(0));
        _q_self->setBlockFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 52:
    if (context->argumentCount() == 1) {
        QTextCharFormat _q_arg0 = qscriptvalue_cast<QTextCharFormat>(context->argument(0));
        _q_self->setCharFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 53:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setKeepPositionOnInsert(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 54:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setPosition(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QTextCursor::MoveMode _q_arg1 = qscriptvalue_cast<QTextCursor::MoveMode>(context->argument(1));
        _q_self->setPosition(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 55:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setVerticalMovementX(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 56:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setVisualNavigation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 57:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->verticalMovementX();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 58:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->visualNavigation();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 59: {
    QString result = QString::fromLatin1("QTextCursor");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextCursor_throw_ambiguity_error_helper(context,
        qtscript_QTextCursor_function_names[_id+1],
        qtscript_QTextCursor_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextCursor_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextCursor(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QTextCursor _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QTextDocument*>(context->argument(0))) {
            QTextDocument* _q_arg0 = qscriptvalue_cast<QTextDocument*>(context->argument(0));
            QTextCursor _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (qscriptvalue_cast<QTextFrame*>(context->argument(0))) {
            QTextFrame* _q_arg0 = qscriptvalue_cast<QTextFrame*>(context->argument(0));
            QTextCursor _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QTextBlock>() == context->argument(0).toVariant().userType())) {
            QTextBlock _q_arg0 = qscriptvalue_cast<QTextBlock>(context->argument(0));
            QTextCursor _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QTextCursor>() == context->argument(0).toVariant().userType())) {
            QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
            QTextCursor _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextCursor_throw_ambiguity_error_helper(context,
        qtscript_QTextCursor_function_names[_id],
        qtscript_QTextCursor_function_signatures[_id]);
}

QScriptValue qtscript_create_QTextCursor_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextCursor*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextCursor*)0));
    for (int i = 0; i < 60; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextCursor_prototype_call, qtscript_QTextCursor_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextCursor_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QTextCursor>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QTextCursor*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextCursor_static_call, proto, qtscript_QTextCursor_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("MoveMode"),
        qtscript_create_QTextCursor_MoveMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("MoveOperation"),
        qtscript_create_QTextCursor_MoveOperation_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SelectionType"),
        qtscript_create_QTextCursor_SelectionType_class(engine, ctor));
    return ctor;
}
