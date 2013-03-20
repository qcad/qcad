#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qkeysequence.h>
#include <QVariant>
#include <qdatastream.h>
#include <qkeysequence.h>
#include <qlist.h>

static const char * const qtscript_QKeySequence_function_names[] = {
    "QKeySequence"
    // static
    , "fromString"
    , "keyBindings"
    , "mnemonic"
    // prototype
    , "count"
    , "isEmpty"
    , "matches"
    , "operator_cast_int"
    , "equals"
    , "operator_less"
    , "operator_subscript"
    , "readFrom"
    , "toString"
    , "writeTo"
};

static const char * const qtscript_QKeySequence_function_signatures[] = {
    "\nStandardKey key\nQKeySequence ks\nString key\nString key, SequenceFormat format\nint k1, int k2, int k3, int k4"
    // static
    , "String str, SequenceFormat format"
    , "StandardKey key"
    , "String text"
    // prototype
    , ""
    , ""
    , "QKeySequence seq"
    , ""
    , "QKeySequence other"
    , "QKeySequence ks"
    , "uint i"
    , "QDataStream out"
    , "SequenceFormat format"
    , "QDataStream in"
};

static const int qtscript_QKeySequence_function_lengths[] = {
    4
    // static
    , 2
    , 1
    , 1
    // prototype
    , 0
    , 0
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
};

static QScriptValue qtscript_QKeySequence_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QKeySequence::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QKeySequence*)
Q_DECLARE_METATYPE(QKeySequence::SequenceFormat)
Q_DECLARE_METATYPE(QKeySequence::StandardKey)
Q_DECLARE_METATYPE(QKeySequence::SequenceMatch)
Q_DECLARE_METATYPE(QDataStream*)
Q_DECLARE_METATYPE(QList<QKeySequence>)

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
// QKeySequence::SequenceFormat
//

static const QKeySequence::SequenceFormat qtscript_QKeySequence_SequenceFormat_values[] = {
    QKeySequence::NativeText
    , QKeySequence::PortableText
};

static const char * const qtscript_QKeySequence_SequenceFormat_keys[] = {
    "NativeText"
    , "PortableText"
};

static QString qtscript_QKeySequence_SequenceFormat_toStringHelper(QKeySequence::SequenceFormat value)
{
    if ((value >= QKeySequence::NativeText) && (value <= QKeySequence::PortableText))
        return qtscript_QKeySequence_SequenceFormat_keys[static_cast<int>(value)-static_cast<int>(QKeySequence::NativeText)];
    return QString();
}

static QScriptValue qtscript_QKeySequence_SequenceFormat_toScriptValue(QScriptEngine *engine, const QKeySequence::SequenceFormat &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QKeySequence"));
    return clazz.property(qtscript_QKeySequence_SequenceFormat_toStringHelper(value));
}

static void qtscript_QKeySequence_SequenceFormat_fromScriptValue(const QScriptValue &value, QKeySequence::SequenceFormat &out)
{
    out = qvariant_cast<QKeySequence::SequenceFormat>(value.toVariant());
}

static QScriptValue qtscript_construct_QKeySequence_SequenceFormat(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QKeySequence::NativeText) && (arg <= QKeySequence::PortableText))
        return qScriptValueFromValue(engine,  static_cast<QKeySequence::SequenceFormat>(arg));
    return context->throwError(QString::fromLatin1("SequenceFormat(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QKeySequence_SequenceFormat_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QKeySequence::SequenceFormat value = qscriptvalue_cast<QKeySequence::SequenceFormat>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QKeySequence_SequenceFormat_toString(QScriptContext *context, QScriptEngine *engine)
{
    QKeySequence::SequenceFormat value = qscriptvalue_cast<QKeySequence::SequenceFormat>(context->thisObject());
    return QScriptValue(engine, qtscript_QKeySequence_SequenceFormat_toStringHelper(value));
}

static QScriptValue qtscript_create_QKeySequence_SequenceFormat_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QKeySequence_SequenceFormat,
        qtscript_QKeySequence_SequenceFormat_valueOf, qtscript_QKeySequence_SequenceFormat_toString);
    qScriptRegisterMetaType<QKeySequence::SequenceFormat>(engine, qtscript_QKeySequence_SequenceFormat_toScriptValue,
        qtscript_QKeySequence_SequenceFormat_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QKeySequence_SequenceFormat_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QKeySequence_SequenceFormat_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QKeySequence::StandardKey
//

static const QKeySequence::StandardKey qtscript_QKeySequence_StandardKey_values[] = {
    QKeySequence::UnknownKey
    , QKeySequence::HelpContents
    , QKeySequence::WhatsThis
    , QKeySequence::Open
    , QKeySequence::Close
    , QKeySequence::Save
    , QKeySequence::New
    , QKeySequence::Delete
    , QKeySequence::Cut
    , QKeySequence::Copy
    , QKeySequence::Paste
    , QKeySequence::Undo
    , QKeySequence::Redo
    , QKeySequence::Back
    , QKeySequence::Forward
    , QKeySequence::Refresh
    , QKeySequence::ZoomIn
    , QKeySequence::ZoomOut
    , QKeySequence::Print
    , QKeySequence::AddTab
    , QKeySequence::NextChild
    , QKeySequence::PreviousChild
    , QKeySequence::Find
    , QKeySequence::FindNext
    , QKeySequence::FindPrevious
    , QKeySequence::Replace
    , QKeySequence::SelectAll
    , QKeySequence::Bold
    , QKeySequence::Italic
    , QKeySequence::Underline
    , QKeySequence::MoveToNextChar
    , QKeySequence::MoveToPreviousChar
    , QKeySequence::MoveToNextWord
    , QKeySequence::MoveToPreviousWord
    , QKeySequence::MoveToNextLine
    , QKeySequence::MoveToPreviousLine
    , QKeySequence::MoveToNextPage
    , QKeySequence::MoveToPreviousPage
    , QKeySequence::MoveToStartOfLine
    , QKeySequence::MoveToEndOfLine
    , QKeySequence::MoveToStartOfBlock
    , QKeySequence::MoveToEndOfBlock
    , QKeySequence::MoveToStartOfDocument
    , QKeySequence::MoveToEndOfDocument
    , QKeySequence::SelectNextChar
    , QKeySequence::SelectPreviousChar
    , QKeySequence::SelectNextWord
    , QKeySequence::SelectPreviousWord
    , QKeySequence::SelectNextLine
    , QKeySequence::SelectPreviousLine
    , QKeySequence::SelectNextPage
    , QKeySequence::SelectPreviousPage
    , QKeySequence::SelectStartOfLine
    , QKeySequence::SelectEndOfLine
    , QKeySequence::SelectStartOfBlock
    , QKeySequence::SelectEndOfBlock
    , QKeySequence::SelectStartOfDocument
    , QKeySequence::SelectEndOfDocument
    , QKeySequence::DeleteStartOfWord
    , QKeySequence::DeleteEndOfWord
    , QKeySequence::DeleteEndOfLine
    , QKeySequence::InsertParagraphSeparator
    , QKeySequence::InsertLineSeparator
    , QKeySequence::SaveAs
    , QKeySequence::Preferences
    , QKeySequence::Quit
};

static const char * const qtscript_QKeySequence_StandardKey_keys[] = {
    "UnknownKey"
    , "HelpContents"
    , "WhatsThis"
    , "Open"
    , "Close"
    , "Save"
    , "New"
    , "Delete"
    , "Cut"
    , "Copy"
    , "Paste"
    , "Undo"
    , "Redo"
    , "Back"
    , "Forward"
    , "Refresh"
    , "ZoomIn"
    , "ZoomOut"
    , "Print"
    , "AddTab"
    , "NextChild"
    , "PreviousChild"
    , "Find"
    , "FindNext"
    , "FindPrevious"
    , "Replace"
    , "SelectAll"
    , "Bold"
    , "Italic"
    , "Underline"
    , "MoveToNextChar"
    , "MoveToPreviousChar"
    , "MoveToNextWord"
    , "MoveToPreviousWord"
    , "MoveToNextLine"
    , "MoveToPreviousLine"
    , "MoveToNextPage"
    , "MoveToPreviousPage"
    , "MoveToStartOfLine"
    , "MoveToEndOfLine"
    , "MoveToStartOfBlock"
    , "MoveToEndOfBlock"
    , "MoveToStartOfDocument"
    , "MoveToEndOfDocument"
    , "SelectNextChar"
    , "SelectPreviousChar"
    , "SelectNextWord"
    , "SelectPreviousWord"
    , "SelectNextLine"
    , "SelectPreviousLine"
    , "SelectNextPage"
    , "SelectPreviousPage"
    , "SelectStartOfLine"
    , "SelectEndOfLine"
    , "SelectStartOfBlock"
    , "SelectEndOfBlock"
    , "SelectStartOfDocument"
    , "SelectEndOfDocument"
    , "DeleteStartOfWord"
    , "DeleteEndOfWord"
    , "DeleteEndOfLine"
    , "InsertParagraphSeparator"
    , "InsertLineSeparator"
    , "SaveAs"
    , "Preferences"
    , "Quit"
};

static QString qtscript_QKeySequence_StandardKey_toStringHelper(QKeySequence::StandardKey value)
{
    if ((value >= QKeySequence::UnknownKey) && (value <= QKeySequence::Quit))
        return qtscript_QKeySequence_StandardKey_keys[static_cast<int>(value)-static_cast<int>(QKeySequence::UnknownKey)];
    return QString();
}

static QScriptValue qtscript_QKeySequence_StandardKey_toScriptValue(QScriptEngine *engine, const QKeySequence::StandardKey &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QKeySequence"));
    return clazz.property(qtscript_QKeySequence_StandardKey_toStringHelper(value));
}

static void qtscript_QKeySequence_StandardKey_fromScriptValue(const QScriptValue &value, QKeySequence::StandardKey &out)
{
    out = qvariant_cast<QKeySequence::StandardKey>(value.toVariant());
}

static QScriptValue qtscript_construct_QKeySequence_StandardKey(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QKeySequence::UnknownKey) && (arg <= QKeySequence::Quit))
        return qScriptValueFromValue(engine,  static_cast<QKeySequence::StandardKey>(arg));
    return context->throwError(QString::fromLatin1("StandardKey(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QKeySequence_StandardKey_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QKeySequence::StandardKey value = qscriptvalue_cast<QKeySequence::StandardKey>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QKeySequence_StandardKey_toString(QScriptContext *context, QScriptEngine *engine)
{
    QKeySequence::StandardKey value = qscriptvalue_cast<QKeySequence::StandardKey>(context->thisObject());
    return QScriptValue(engine, qtscript_QKeySequence_StandardKey_toStringHelper(value));
}

static QScriptValue qtscript_create_QKeySequence_StandardKey_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QKeySequence_StandardKey,
        qtscript_QKeySequence_StandardKey_valueOf, qtscript_QKeySequence_StandardKey_toString);
    qScriptRegisterMetaType<QKeySequence::StandardKey>(engine, qtscript_QKeySequence_StandardKey_toScriptValue,
        qtscript_QKeySequence_StandardKey_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 66; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QKeySequence_StandardKey_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QKeySequence_StandardKey_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QKeySequence::SequenceMatch
//

static const QKeySequence::SequenceMatch qtscript_QKeySequence_SequenceMatch_values[] = {
    QKeySequence::NoMatch
    , QKeySequence::PartialMatch
    , QKeySequence::ExactMatch
};

static const char * const qtscript_QKeySequence_SequenceMatch_keys[] = {
    "NoMatch"
    , "PartialMatch"
    , "ExactMatch"
};

static QString qtscript_QKeySequence_SequenceMatch_toStringHelper(QKeySequence::SequenceMatch value)
{
    if ((value >= QKeySequence::NoMatch) && (value <= QKeySequence::ExactMatch))
        return qtscript_QKeySequence_SequenceMatch_keys[static_cast<int>(value)-static_cast<int>(QKeySequence::NoMatch)];
    return QString();
}

static QScriptValue qtscript_QKeySequence_SequenceMatch_toScriptValue(QScriptEngine *engine, const QKeySequence::SequenceMatch &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QKeySequence"));
    return clazz.property(qtscript_QKeySequence_SequenceMatch_toStringHelper(value));
}

static void qtscript_QKeySequence_SequenceMatch_fromScriptValue(const QScriptValue &value, QKeySequence::SequenceMatch &out)
{
    out = qvariant_cast<QKeySequence::SequenceMatch>(value.toVariant());
}

static QScriptValue qtscript_construct_QKeySequence_SequenceMatch(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QKeySequence::NoMatch) && (arg <= QKeySequence::ExactMatch))
        return qScriptValueFromValue(engine,  static_cast<QKeySequence::SequenceMatch>(arg));
    return context->throwError(QString::fromLatin1("SequenceMatch(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QKeySequence_SequenceMatch_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QKeySequence::SequenceMatch value = qscriptvalue_cast<QKeySequence::SequenceMatch>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QKeySequence_SequenceMatch_toString(QScriptContext *context, QScriptEngine *engine)
{
    QKeySequence::SequenceMatch value = qscriptvalue_cast<QKeySequence::SequenceMatch>(context->thisObject());
    return QScriptValue(engine, qtscript_QKeySequence_SequenceMatch_toStringHelper(value));
}

static QScriptValue qtscript_create_QKeySequence_SequenceMatch_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QKeySequence_SequenceMatch,
        qtscript_QKeySequence_SequenceMatch_valueOf, qtscript_QKeySequence_SequenceMatch_toString);
    qScriptRegisterMetaType<QKeySequence::SequenceMatch>(engine, qtscript_QKeySequence_SequenceMatch_toScriptValue,
        qtscript_QKeySequence_SequenceMatch_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QKeySequence_SequenceMatch_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QKeySequence_SequenceMatch_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QKeySequence
//

static QScriptValue qtscript_QKeySequence_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 10;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QKeySequence* _q_self = qscriptvalue_cast<QKeySequence*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QKeySequence.%0(): this object is not a QKeySequence")
            .arg(qtscript_QKeySequence_function_names[_id+4]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        uint _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isEmpty();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QKeySequence _q_arg0 = qscriptvalue_cast<QKeySequence>(context->argument(0));
        QKeySequence::SequenceMatch _q_result = _q_self->matches(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->operator int();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QKeySequence _q_arg0 = qscriptvalue_cast<QKeySequence>(context->argument(0));
        bool _q_result = _q_self->operator==(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        QKeySequence _q_arg0 = qscriptvalue_cast<QKeySequence>(context->argument(0));
        bool _q_result = _q_self->operator<(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        uint _q_arg0 = context->argument(0).toUInt32();
        int _q_result = _q_self->operator[](_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->toString();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QKeySequence::SequenceFormat _q_arg0 = qscriptvalue_cast<QKeySequence::SequenceFormat>(context->argument(0));
        QString _q_result = _q_self->toString(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QDataStream* _q_arg0 = qscriptvalue_cast<QDataStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QKeySequence_throw_ambiguity_error_helper(context,
        qtscript_QKeySequence_function_names[_id+4],
        qtscript_QKeySequence_function_signatures[_id+4]);
}

static QScriptValue qtscript_QKeySequence_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QKeySequence(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QKeySequence _q_cpp_result;
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QKeySequence::StandardKey>() == context->argument(0).toVariant().userType())) {
            QKeySequence::StandardKey _q_arg0 = qscriptvalue_cast<QKeySequence::StandardKey>(context->argument(0));
            QKeySequence _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if ((qMetaTypeId<QKeySequence>() == context->argument(0).toVariant().userType())) {
            QKeySequence _q_arg0 = qscriptvalue_cast<QKeySequence>(context->argument(0));
            QKeySequence _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QKeySequence _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            QKeySequence _q_cpp_result(_q_arg0);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        if (context->argument(0).isString()
            && (qMetaTypeId<QKeySequence::SequenceFormat>() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QKeySequence::SequenceFormat _q_arg1 = qscriptvalue_cast<QKeySequence::SequenceFormat>(context->argument(1));
            QKeySequence _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QKeySequence _q_cpp_result(_q_arg0, _q_arg1);
            QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
            return _q_result;
        }
    } else if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QKeySequence _q_cpp_result(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QKeySequence _q_cpp_result(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QKeySequence _q_result = QKeySequence::fromString(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QKeySequence::SequenceFormat _q_arg1 = qscriptvalue_cast<QKeySequence::SequenceFormat>(context->argument(1));
        QKeySequence _q_result = QKeySequence::fromString(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QKeySequence::StandardKey _q_arg0 = qscriptvalue_cast<QKeySequence::StandardKey>(context->argument(0));
        QList<QKeySequence> _q_result = QKeySequence::keyBindings(_q_arg0);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QKeySequence _q_result = QKeySequence::mnemonic(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QKeySequence_throw_ambiguity_error_helper(context,
        qtscript_QKeySequence_function_names[_id],
        qtscript_QKeySequence_function_signatures[_id]);
}

QScriptValue qtscript_create_QKeySequence_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QKeySequence*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QKeySequence*)0));
    for (int i = 0; i < 10; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QKeySequence_prototype_call, qtscript_QKeySequence_function_lengths[i+4]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QKeySequence_function_names[i+4]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QKeySequence>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QKeySequence*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QKeySequence_static_call, proto, qtscript_QKeySequence_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QKeySequence_static_call,
            qtscript_QKeySequence_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QKeySequence_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("SequenceFormat"),
        qtscript_create_QKeySequence_SequenceFormat_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("StandardKey"),
        qtscript_create_QKeySequence_StandardKey_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SequenceMatch"),
        qtscript_create_QKeySequence_SequenceMatch_class(engine, ctor));
    return ctor;
}
