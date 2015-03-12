#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsplitter.h>
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
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qsplitter.h>
#include <qstyle.h>
#include <qtextstream.h>
#include <qwidget.h>

#include "qtscriptshell_QSplitter.h"

static const char * const qtscript_QSplitter_function_names[] = {
    "QSplitter"
    // static
    // prototype
    , "addWidget"
    , "count"
    , "getRange"
    , "handle"
    , "indexOf"
    , "insertWidget"
    , "isCollapsible"
    , "minimumSizeHint"
    , "readFrom"
    , "refresh"
    , "restoreState"
    , "saveState"
    , "setCollapsible"
    , "setSizes"
    , "setStretchFactor"
    , "sizes"
    , "widget"
    , "writeTo"
    , "toString"
};

static const char * const qtscript_QSplitter_function_signatures[] = {
    "QWidget parent\nOrientation arg__1, QWidget parent"
    // static
    // prototype
    , "QWidget widget"
    , ""
    , "int index, int arg__2, int arg__3"
    , "int index"
    , "QWidget w"
    , "int index, QWidget widget"
    , "int index"
    , ""
    , "QTextStream arg__1"
    , ""
    , "QByteArray state"
    , ""
    , "int index, bool arg__2"
    , "List list"
    , "int index, int stretch"
    , ""
    , "int index"
    , "QTextStream arg__1"
""
};

static const int qtscript_QSplitter_function_lengths[] = {
    2
    // static
    // prototype
    , 1
    , 0
    , 3
    , 1
    , 1
    , 2
    , 1
    , 0
    , 1
    , 0
    , 1
    , 0
    , 2
    , 1
    , 2
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QSplitter_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSplitter::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSplitter*)
Q_DECLARE_METATYPE(QtScriptShell_QSplitter*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(QSplitterHandle*)
Q_DECLARE_METATYPE(QTextStream*)
Q_DECLARE_METATYPE(QList<int >)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QFrame*)

//
// QSplitter
//

static QScriptValue qtscript_QSplitter_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 18;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSplitter* _q_self = qscriptvalue_cast<QSplitter*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSplitter.%0(): this object is not a QSplitter")
            .arg(qtscript_QSplitter_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->addWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int* _q_arg1 = qscriptvalue_cast<int*>(context->argument(1));
        int* _q_arg2 = qscriptvalue_cast<int*>(context->argument(2));
        _q_self->getRange(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QSplitterHandle* _q_result = _q_self->handle(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        int _q_result = _q_self->indexOf(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        _q_self->insertWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isCollapsible(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QTextStream* _q_arg0 = qscriptvalue_cast<QTextStream*>(context->argument(0));
        operator>>(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        _q_self->refresh();
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        bool _q_result = _q_self->restoreState(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->saveState();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setCollapsible(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QList<int> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        _q_self->setSizes(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->setStretchFactor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QList<int > _q_result = _q_self->sizes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_result = _q_self->widget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QTextStream* _q_arg0 = qscriptvalue_cast<QTextStream*>(context->argument(0));
        operator<<(*_q_arg0, *_q_self);
        return context->engine()->undefinedValue();
    }
    break;

    case 18: {
    QString result = QString::fromLatin1("QSplitter");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSplitter_throw_ambiguity_error_helper(context,
        qtscript_QSplitter_function_names[_id+1],
        qtscript_QSplitter_function_signatures[_id+1]);
}

static QScriptValue qtscript_QSplitter_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSplitter(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSplitter* _q_cpp_result = new QtScriptShell_QSplitter();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSplitter*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QSplitter* _q_cpp_result = new QtScriptShell_QSplitter(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSplitter*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if ((qMetaTypeId<Qt::Orientation>() == context->argument(0).toVariant().userType())) {
            Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
            QtScriptShell_QSplitter* _q_cpp_result = new QtScriptShell_QSplitter(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSplitter*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QSplitter* _q_cpp_result = new QtScriptShell_QSplitter(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSplitter*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSplitter_throw_ambiguity_error_helper(context,
        qtscript_QSplitter_function_names[_id],
        qtscript_QSplitter_function_signatures[_id]);
}

static QScriptValue qtscript_QSplitter_toScriptValue(QScriptEngine *engine, QSplitter* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSplitter_fromScriptValue(const QScriptValue &value, QSplitter* &out)
{
    out = qobject_cast<QSplitter*>(value.toQObject());
}

QScriptValue qtscript_create_QSplitter_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSplitter*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSplitter*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QFrame*>()));
    for (int i = 0; i < 19; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSplitter_prototype_call, qtscript_QSplitter_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSplitter_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSplitter*>(engine, qtscript_QSplitter_toScriptValue, 
        qtscript_QSplitter_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSplitter_static_call, proto, qtscript_QSplitter_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
