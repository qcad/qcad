#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>

#include <qplaintextedit.h>
#include <QAbstractTextDocumentLayout>
#include <QTextEdit>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qinputcontext.h>
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
#include <qplaintextedit.h>
#include <qpoint.h>
#include <qprinter.h>
#include <qrect.h>
#include <qregion.h>
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qtextcursor.h>
#include <qtextdocument.h>
#include <qtextformat.h>
#include <qtextobject.h>
#include <qurl.h>
#include <qwidget.h>

#include "qtscriptshell_QPlainTextEdit.h"

static const char * const qtscript_QPlainTextEdit_function_names[] = {
    "QPlainTextEdit"
    // static
    // prototype
    , "anchorAt"
    , "canPaste"
    , "createStandardContextMenu"
    , "currentCharFormat"
    , "cursorForPosition"
    , "cursorRect"
    , "document"
    , "ensureCursorVisible"
    , "extraSelections"
    , "find"
    , "loadResource"
    , "mergeCurrentCharFormat"
    , "moveCursor"
    , "print"
    , "setCurrentCharFormat"
    , "setDocument"
    , "setExtraSelections"
    , "setTextCursor"
    , "setWordWrapMode"
    , "textCursor"
    , "wordWrapMode"
    , "toString"
};

static const char * const qtscript_QPlainTextEdit_function_signatures[] = {
    "QWidget parent\nString text, QWidget parent"
    // static
    // prototype
    , "QPoint pos"
    , ""
    , ""
    , ""
    , "QPoint pos"
    , "\nQTextCursor cursor"
    , ""
    , ""
    , ""
    , "String exp, FindFlags options"
    , "int type, QUrl name"
    , "QTextCharFormat modifier"
    , "MoveOperation operation, MoveMode mode"
    , "QPrinter printer"
    , "QTextCharFormat format"
    , "QTextDocument document"
    , "List selections"
    , "QTextCursor cursor"
    , "WrapMode policy"
    , ""
    , ""
""
};

static const int qtscript_QPlainTextEdit_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
    , 2
    , 2
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QPlainTextEdit_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPlainTextEdit::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QPlainTextEdit_metaObject()
{
    return &QPlainTextEdit::staticMetaObject;
}

Q_DECLARE_METATYPE(QPlainTextEdit*)
Q_DECLARE_METATYPE(QtScriptShell_QPlainTextEdit*)
Q_DECLARE_METATYPE(QPlainTextEdit::LineWrapMode)
Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(QTextCharFormat)
Q_DECLARE_METATYPE(QTextCursor)
Q_DECLARE_METATYPE(QTextDocument*)
Q_DECLARE_METATYPE(QTextEdit::ExtraSelection)
Q_DECLARE_METATYPE(QList<QTextEdit::ExtraSelection>)
Q_DECLARE_METATYPE(QFlags<QTextDocument::FindFlag>)
Q_DECLARE_METATYPE(QTextCursor::MoveOperation)
Q_DECLARE_METATYPE(QTextCursor::MoveMode)
Q_DECLARE_METATYPE(QPrinter*)
Q_DECLARE_METATYPE(QTextOption::WrapMode)
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

//
// QPlainTextEdit::LineWrapMode
//

static const QPlainTextEdit::LineWrapMode qtscript_QPlainTextEdit_LineWrapMode_values[] = {
    QPlainTextEdit::NoWrap
    , QPlainTextEdit::WidgetWidth
};

static const char * const qtscript_QPlainTextEdit_LineWrapMode_keys[] = {
    "NoWrap"
    , "WidgetWidth"
};

static QString qtscript_QPlainTextEdit_LineWrapMode_toStringHelper(QPlainTextEdit::LineWrapMode value)
{
    const QMetaObject *meta = qtscript_QPlainTextEdit_metaObject();
    int idx = meta->indexOfEnumerator("LineWrapMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QPlainTextEdit_LineWrapMode_toScriptValue(QScriptEngine *engine, const QPlainTextEdit::LineWrapMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QPlainTextEdit"));
    return clazz.property(qtscript_QPlainTextEdit_LineWrapMode_toStringHelper(value));
}

static void qtscript_QPlainTextEdit_LineWrapMode_fromScriptValue(const QScriptValue &value, QPlainTextEdit::LineWrapMode &out)
{
    out = qvariant_cast<QPlainTextEdit::LineWrapMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QPlainTextEdit_LineWrapMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QPlainTextEdit_metaObject();
    int idx = meta->indexOfEnumerator("LineWrapMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QPlainTextEdit::LineWrapMode>(arg));
    return context->throwError(QString::fromLatin1("LineWrapMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QPlainTextEdit_LineWrapMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QPlainTextEdit::LineWrapMode value = qscriptvalue_cast<QPlainTextEdit::LineWrapMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QPlainTextEdit_LineWrapMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QPlainTextEdit::LineWrapMode value = qscriptvalue_cast<QPlainTextEdit::LineWrapMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QPlainTextEdit_LineWrapMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QPlainTextEdit_LineWrapMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QPlainTextEdit_LineWrapMode,
        qtscript_QPlainTextEdit_LineWrapMode_valueOf, qtscript_QPlainTextEdit_LineWrapMode_toString);
    qScriptRegisterMetaType<QPlainTextEdit::LineWrapMode>(engine, qtscript_QPlainTextEdit_LineWrapMode_toScriptValue,
        qtscript_QPlainTextEdit_LineWrapMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QPlainTextEdit_LineWrapMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QPlainTextEdit_LineWrapMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QPlainTextEdit
//

static QScriptValue qtscript_QPlainTextEdit_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QPlainTextEdit* _q_self = qscriptvalue_cast<QPlainTextEdit*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPlainTextEdit.%0(): this object is not a QPlainTextEdit")
            .arg(qtscript_QPlainTextEdit_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QString _q_result = _q_self->anchorAt(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->canPaste();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QMenu* _q_result = _q_self->createStandardContextMenu();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QTextCharFormat _q_result = _q_self->currentCharFormat();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QTextCursor _q_result = _q_self->cursorForPosition(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
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

    case 6:
    if (context->argumentCount() == 0) {
        QTextDocument* _q_result = _q_self->document();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        _q_self->ensureCursorVisible();
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QList<QTextEdit::ExtraSelection> _q_result = _q_self->extraSelections();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        bool _q_result = _q_self->find(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QFlags<QTextDocument::FindFlag> _q_arg1 = qscriptvalue_cast<QFlags<QTextDocument::FindFlag> >(context->argument(1));
        bool _q_result = _q_self->find(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QUrl _q_arg1 = qscriptvalue_cast<QUrl>(context->argument(1));
        QVariant _q_result = _q_self->loadResource(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QTextCharFormat _q_arg0 = qscriptvalue_cast<QTextCharFormat>(context->argument(0));
        _q_self->mergeCurrentCharFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
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

    case 13:
    if (context->argumentCount() == 1) {
        QPrinter* _q_arg0 = qscriptvalue_cast<QPrinter*>(context->argument(0));
        _q_self->print(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QTextCharFormat _q_arg0 = qscriptvalue_cast<QTextCharFormat>(context->argument(0));
        _q_self->setCurrentCharFormat(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QTextDocument* _q_arg0 = qscriptvalue_cast<QTextDocument*>(context->argument(0));
        _q_self->setDocument(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        QList<QTextEdit::ExtraSelection> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setExtraSelections(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QTextCursor _q_arg0 = qscriptvalue_cast<QTextCursor>(context->argument(0));
        _q_self->setTextCursor(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QTextOption::WrapMode _q_arg0 = qscriptvalue_cast<QTextOption::WrapMode>(context->argument(0));
        _q_self->setWordWrapMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QTextCursor _q_result = _q_self->textCursor();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        QTextOption::WrapMode _q_result = _q_self->wordWrapMode();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 21: {
    QString result = QString::fromLatin1("QPlainTextEdit");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPlainTextEdit_throw_ambiguity_error_helper(context,
        qtscript_QPlainTextEdit_function_names[_id+1],
        qtscript_QPlainTextEdit_function_signatures[_id+1]);
}

static QScriptValue qtscript_QPlainTextEdit_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QPlainTextEdit(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QPlainTextEdit* _q_cpp_result = new QtScriptShell_QPlainTextEdit();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPlainTextEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QPlainTextEdit* _q_cpp_result = new QtScriptShell_QPlainTextEdit(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPlainTextEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            QtScriptShell_QPlainTextEdit* _q_cpp_result = new QtScriptShell_QPlainTextEdit(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPlainTextEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QPlainTextEdit* _q_cpp_result = new QtScriptShell_QPlainTextEdit(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QPlainTextEdit*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QPlainTextEdit_throw_ambiguity_error_helper(context,
        qtscript_QPlainTextEdit_function_names[_id],
        qtscript_QPlainTextEdit_function_signatures[_id]);
}

static QScriptValue qtscript_QPlainTextEdit_toScriptValue(QScriptEngine *engine, QPlainTextEdit* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QPlainTextEdit_fromScriptValue(const QScriptValue &value, QPlainTextEdit* &out)
{
    out = qobject_cast<QPlainTextEdit*>(value.toQObject());
}

QScriptValue qtscript_create_QPlainTextEdit_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPlainTextEdit*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QPlainTextEdit*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractScrollArea*>()));
    for (int i = 0; i < 22; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPlainTextEdit_prototype_call, qtscript_QPlainTextEdit_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPlainTextEdit_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QPlainTextEdit*>(engine, qtscript_QPlainTextEdit_toScriptValue, 
        qtscript_QPlainTextEdit_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPlainTextEdit_static_call, proto, qtscript_QPlainTextEdit_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("LineWrapMode"),
        qtscript_create_QPlainTextEdit_LineWrapMode_class(engine, ctor));
    return ctor;
}
