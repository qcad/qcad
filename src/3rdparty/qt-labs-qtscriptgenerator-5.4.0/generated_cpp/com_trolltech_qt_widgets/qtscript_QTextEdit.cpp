#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtextedit.h>
#include <QTextCursor>
#include <QTextEdit>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qmenu.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregexp.h>
#include <qregion.h>
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qtextcursor.h>
#include <qtextdocument.h>
#include <qtextedit.h>
#include <qtextformat.h>
#include <qurl.h>
#include <qwidget.h>

#include "qtscriptshell_QTextEdit.h"

static const char * const qtscript_QTextEdit_function_names[] = {
    "QTextEdit"
    // static
    // prototype
    , "alignment"
    , "anchorAt"
    , "canPaste"
    , "createStandardContextMenu"
    , "currentCharFormat"
    , "currentFont"
    , "cursorForPosition"
    , "cursorRect"
    , "ensureCursorVisible"
    , "extraSelections"
    , "find"
    , "fontFamily"
    , "fontItalic"
    , "fontPointSize"
    , "fontUnderline"
    , "fontWeight"
    , "mergeCurrentCharFormat"
    , "moveCursor"
    , "setCurrentCharFormat"
    , "setExtraSelections"
    , "setTextCursor"
    , "setWordWrapMode"
    , "textBackgroundColor"
    , "textColor"
    , "textCursor"
    , "wordWrapMode"
    , "toString"
};

static const char * const qtscript_QTextEdit_function_signatures[] = {
    "QWidget parent\nString text, QWidget parent"
    // static
    // prototype
    , ""
    , "QPoint pos"
    , ""
    , "\nQPoint position"
    , ""
    , ""
    , "QPoint pos"
    , "\nQTextCursor cursor"
    , ""
    , ""
    , "QRegExp exp, FindFlags options\nString exp, FindFlags options"
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QTextCharFormat modifier"
    , "MoveOperation operation, MoveMode mode"
    , "QTextCharFormat format"
    , "List selections"
    , "QTextCursor cursor"
    , "WrapMode policy"
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QTextEdit_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 1
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTextEdit_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTextEdit::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QTextEdit_metaObject()
{
    return &QTextEdit::staticMetaObject;
}

Q_DECLARE_METATYPE(QTextEdit*)
Q_DECLARE_METATYPE(QtScriptShell_QTextEdit*)
Q_DECLARE_METATYPE(QTextEdit::AutoFormattingFlag)
Q_DECLARE_METATYPE(QFlags<QTextEdit::AutoFormattingFlag>)
Q_DECLARE_METATYPE(QTextEdit::LineWrapMode)
Q_DECLARE_METATYPE(QFlags<Qt::AlignmentFlag>)
Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(QTextCharFormat)
Q_DECLARE_METATYPE(QTextCursor)
Q_DECLARE_METATYPE(QTextEdit::ExtraSelection)
Q_DECLARE_METATYPE(QList<QTextEdit::ExtraSelection >)
Q_DECLARE_METATYPE(QFlags<QTextDocument::FindFlag>)
Q_DECLARE_METATYPE(QTextCursor::MoveOperation)
Q_DECLARE_METATYPE(QTextCursor::MoveMode)
Q_DECLARE_METATYPE(QTextOption::WrapMode)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QAbstractScrollArea*)

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
// QTextEdit::AutoFormattingFlag
//

static const QTextEdit::AutoFormattingFlag qtscript_QTextEdit_AutoFormattingFlag_values[] = {
    QTextEdit::AutoAll
    , QTextEdit::AutoNone
    , QTextEdit::AutoBulletList
};

static const char * const qtscript_QTextEdit_AutoFormattingFlag_keys[] = {
    "AutoAll"
    , "AutoNone"
    , "AutoBulletList"
};

static QString qtscript_QTextEdit_AutoFormattingFlag_toStringHelper(QTextEdit::AutoFormattingFlag value)
{
    if ((value >= QTextEdit::AutoAll) && (value <= QTextEdit::AutoBulletList))
        return qtscript_QTextEdit_AutoFormattingFlag_keys[static_cast<int>(value)-static_cast<int>(QTextEdit::AutoAll)];
    return QString();
}

static QScriptValue qtscript_QTextEdit_AutoFormattingFlag_toScriptValue(QScriptEngine *engine, const QTextEdit::AutoFormattingFlag &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextEdit"));
    return clazz.property(qtscript_QTextEdit_AutoFormattingFlag_toStringHelper(value));
}

static void qtscript_QTextEdit_AutoFormattingFlag_fromScriptValue(const QScriptValue &value, QTextEdit::AutoFormattingFlag &out)
{
    out = qvariant_cast<QTextEdit::AutoFormattingFlag>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextEdit_AutoFormattingFlag(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTextEdit::AutoAll) && (arg <= QTextEdit::AutoBulletList))
        return qScriptValueFromValue(engine,  static_cast<QTextEdit::AutoFormattingFlag>(arg));
    return context->throwError(QString::fromLatin1("AutoFormattingFlag(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextEdit_AutoFormattingFlag_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextEdit::AutoFormattingFlag value = qscriptvalue_cast<QTextEdit::AutoFormattingFlag>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextEdit_AutoFormattingFlag_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextEdit::AutoFormattingFlag value = qscriptvalue_cast<QTextEdit::AutoFormattingFlag>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextEdit_AutoFormattingFlag_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextEdit_AutoFormattingFlag_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextEdit_AutoFormattingFlag,
        qtscript_QTextEdit_AutoFormattingFlag_valueOf, qtscript_QTextEdit_AutoFormattingFlag_toString);
    qScriptRegisterMetaType<QTextEdit::AutoFormattingFlag>(engine, qtscript_QTextEdit_AutoFormattingFlag_toScriptValue,
        qtscript_QTextEdit_AutoFormattingFlag_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextEdit_AutoFormattingFlag_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextEdit_AutoFormattingFlag_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextEdit::AutoFormatting
//

static QScriptValue qtscript_QTextEdit_AutoFormatting_toScriptValue(QScriptEngine *engine, const QTextEdit::AutoFormatting &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static void qtscript_QTextEdit_AutoFormatting_fromScriptValue(const QScriptValue &value, QTextEdit::AutoFormatting &out)
{
    QVariant var = value.toVariant();
    if (var.userType() == qMetaTypeId<QTextEdit::AutoFormatting>())
        out = qvariant_cast<QTextEdit::AutoFormatting>(var);
    else if (var.userType() == qMetaTypeId<QTextEdit::AutoFormattingFlag>())
        out = qvariant_cast<QTextEdit::AutoFormattingFlag>(var);
    else
        out = 0;
}

static QScriptValue qtscript_construct_QTextEdit_AutoFormatting(QScriptContext *context, QScriptEngine *engine)
{
    QTextEdit::AutoFormatting result = 0;
    if ((context->argumentCount() == 1) && context->argument(0).isNumber()) {
        result = static_cast<QTextEdit::AutoFormatting>(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            QVariant v = context->argument(i).toVariant();
            if (v.userType() != qMetaTypeId<QTextEdit::AutoFormattingFlag>()) {
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("AutoFormatting(): argument %0 is not of type AutoFormattingFlag").arg(i));
            }
            result |= qvariant_cast<QTextEdit::AutoFormattingFlag>(v);
        }
   }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue qtscript_QTextEdit_AutoFormatting_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextEdit::AutoFormatting value = qscriptvalue_cast<QTextEdit::AutoFormatting>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextEdit_AutoFormatting_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextEdit::AutoFormatting value = qscriptvalue_cast<QTextEdit::AutoFormatting>(context->thisObject());
    QString result;
    for (int i = 0; i < 3; ++i) {
        if ((value & qtscript_QTextEdit_AutoFormattingFlag_values[i]) == qtscript_QTextEdit_AutoFormattingFlag_values[i]) {
            if (!result.isEmpty())
                result.append(QString::fromLatin1(","));
            result.append(QString::fromLatin1(qtscript_QTextEdit_AutoFormattingFlag_keys[i]));
        }
    }
    return QScriptValue(engine, result);
}

static QScriptValue qtscript_QTextEdit_AutoFormatting_equals(QScriptContext *context, QScriptEngine *engine)
{
    QVariant thisObj = context->thisObject().toVariant();
    QVariant otherObj = context->argument(0).toVariant();
    return QScriptValue(engine, ((thisObj.userType() == otherObj.userType()) &&
                                 (thisObj.value<QTextEdit::AutoFormatting>() == otherObj.value<QTextEdit::AutoFormatting>())));
}

static QScriptValue qtscript_create_QTextEdit_AutoFormatting_class(QScriptEngine *engine)
{
    QScriptValue ctor = qtscript_create_flags_class_helper(
        engine, qtscript_construct_QTextEdit_AutoFormatting, qtscript_QTextEdit_AutoFormatting_valueOf,
        qtscript_QTextEdit_AutoFormatting_toString, qtscript_QTextEdit_AutoFormatting_equals);
    qScriptRegisterMetaType<QTextEdit::AutoFormatting>(engine, qtscript_QTextEdit_AutoFormatting_toScriptValue,
        qtscript_QTextEdit_AutoFormatting_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    return ctor;
}

//
// QTextEdit::LineWrapMode
//

static const QTextEdit::LineWrapMode qtscript_QTextEdit_LineWrapMode_values[] = {
    QTextEdit::NoWrap
    , QTextEdit::WidgetWidth
    , QTextEdit::FixedPixelWidth
    , QTextEdit::FixedColumnWidth
};

static const char * const qtscript_QTextEdit_LineWrapMode_keys[] = {
    "NoWrap"
    , "WidgetWidth"
    , "FixedPixelWidth"
    , "FixedColumnWidth"
};

static QString qtscript_QTextEdit_LineWrapMode_toStringHelper(QTextEdit::LineWrapMode value)
{
    const QMetaObject *meta = qtscript_QTextEdit_metaObject();
    int idx = meta->indexOfEnumerator("LineWrapMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QTextEdit_LineWrapMode_toScriptValue(QScriptEngine *engine, const QTextEdit::LineWrapMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTextEdit"));
    return clazz.property(qtscript_QTextEdit_LineWrapMode_toStringHelper(value));
}

static void qtscript_QTextEdit_LineWrapMode_fromScriptValue(const QScriptValue &value, QTextEdit::LineWrapMode &out)
{
    out = qvariant_cast<QTextEdit::LineWrapMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QTextEdit_LineWrapMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QTextEdit_metaObject();
    int idx = meta->indexOfEnumerator("LineWrapMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QTextEdit::LineWrapMode>(arg));
    return context->throwError(QString::fromLatin1("LineWrapMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTextEdit_LineWrapMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTextEdit::LineWrapMode value = qscriptvalue_cast<QTextEdit::LineWrapMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTextEdit_LineWrapMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTextEdit::LineWrapMode value = qscriptvalue_cast<QTextEdit::LineWrapMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QTextEdit_LineWrapMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QTextEdit_LineWrapMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTextEdit_LineWrapMode,
        qtscript_QTextEdit_LineWrapMode_valueOf, qtscript_QTextEdit_LineWrapMode_toString);
    qScriptRegisterMetaType<QTextEdit::LineWrapMode>(engine, qtscript_QTextEdit_LineWrapMode_toScriptValue,
        qtscript_QTextEdit_LineWrapMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTextEdit_LineWrapMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTextEdit_LineWrapMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTextEdit
//

static QScriptValue qtscript_QTextEdit_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 26;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTextEdit* _q_self = qscriptvalue_cast<QTextEdit*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTextEdit.%0(): this object is not a QTextEdit")
            .arg(qtscript_QTextEdit_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QFlags<Qt::AlignmentFlag> _q_result = _q_self->alignment();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QString _q_result = _q_self->anchorAt(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->canPaste();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QMenu* _q_result = _q_self->createStandardContextMenu();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QMenu* _q_result = _q_self->createStandardContextMenu(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QTextCharFormat _q_result = _q_self->currentCharFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QFont _q_result = _q_self->currentFont();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QTextCursor _q_result = _q_self->cursorForPosition(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->cursorRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
        QRect _q_result = _q_self->cursorRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        _q_self->ensureCursorVisible();
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QList<QTextEdit::ExtraSelection > _q_result = _q_self->extraSelections();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        if (context->argument(0).isRegExp()) {
            QRegExp _q_arg0 = context->argument(0).toRegExp();
            bool _q_result = _q_self->find(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            bool _q_result = _q_self->find(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if (context->argument(0).isRegExp()
            && (qMetaTypeId<QFlags<QTextDocument::FindFlag> >() == context->argument(1).toVariant().userType())) {
            QRegExp _q_arg0 = context->argument(0).toRegExp();
            QFlags<QTextDocument::FindFlag> _q_arg1 = qscriptvalue_cast<QFlags<QTextDocument::FindFlag> >(context->argument(1));
            bool _q_result = _q_self->find(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()
            && (qMetaTypeId<QFlags<QTextDocument::FindFlag> >() == context->argument(1).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            QFlags<QTextDocument::FindFlag> _q_arg1 = qscriptvalue_cast<QFlags<QTextDocument::FindFlag> >(context->argument(1));
            bool _q_result = _q_self->find(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fontFamily();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fontItalic();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->fontPointSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->fontUnderline();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->fontWeight();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QTextCharFormat _q_arg0 = qscriptvalue_cast<QTextCharFormat>(context->argument(0));
        _q_self->mergeCurrentCharFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QTextCursor::MoveOperation _q_arg0 = qscriptvalue_cast<QTextCursor::MoveOperation>(context->argument(0));
        _q_self->moveCursor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QTextCursor::MoveOperation _q_arg0 = qscriptvalue_cast<QTextCursor::MoveOperation>(context->argument(0));
        QTextCursor::MoveMode _q_arg1 = qscriptvalue_cast<QTextCursor::MoveMode>(context->argument(1));
        _q_self->moveCursor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QTextCharFormat _q_arg0 = qscriptvalue_cast<QTextCharFormat>(context->argument(0));
        _q_self->setCurrentCharFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QList<QTextEdit::ExtraSelection> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setExtraSelections(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
        _q_self->setTextCursor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        QTextOption::WrapMode _q_arg0 = qscriptvalue_cast<QTextOption::WrapMode>(context->argument(0));
        _q_self->setWordWrapMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->textBackgroundColor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        QColor _q_result = _q_self->textColor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QTextCursor _q_result = _q_self->textCursor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 0) {
        QTextOption::WrapMode _q_result = _q_self->wordWrapMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 26: {
    QString result = QString::fromLatin1("QTextEdit");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextEdit_throw_ambiguity_error_helper(context,
        qtscript_QTextEdit_function_names[_id+1],
        qtscript_QTextEdit_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTextEdit_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTextEdit(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTextEdit* _q_cpp_result = new QtScriptShell_QTextEdit();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTextEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QTextEdit* _q_cpp_result = new QtScriptShell_QTextEdit(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTextEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QTextEdit* _q_cpp_result = new QtScriptShell_QTextEdit(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTextEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QTextEdit* _q_cpp_result = new QtScriptShell_QTextEdit(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTextEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTextEdit_throw_ambiguity_error_helper(context,
        qtscript_QTextEdit_function_names[_id],
        qtscript_QTextEdit_function_signatures[_id]);
}

static QScriptValue qtscript_QTextEdit_toScriptValue(QScriptEngine *engine, QTextEdit* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTextEdit_fromScriptValue(const QScriptValue &value, QTextEdit* &out)
{
    out = qobject_cast<QTextEdit*>(value.toQObject());
}

QScriptValue qtscript_create_QTextEdit_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTextEdit*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTextEdit*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractScrollArea*>()));
    for (int i = 0; i < 27; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTextEdit_prototype_call, qtscript_QTextEdit_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTextEdit_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTextEdit*>(engine, qtscript_QTextEdit_toScriptValue, 
        qtscript_QTextEdit_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTextEdit_static_call, proto, qtscript_QTextEdit_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("AutoFormattingFlag"),
        qtscript_create_QTextEdit_AutoFormattingFlag_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("AutoFormatting"),
        qtscript_create_QTextEdit_AutoFormatting_class(engine));
    ctor.setProperty(QString::fromLatin1("LineWrapMode"),
        qtscript_create_QTextEdit_LineWrapMode_class(engine, ctor));
    return ctor;
}
