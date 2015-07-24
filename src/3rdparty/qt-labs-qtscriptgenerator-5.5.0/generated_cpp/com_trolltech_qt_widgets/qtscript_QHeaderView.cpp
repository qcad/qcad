#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qheaderview.h>
#include <QVariant>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qheaderview.h>
#include <qicon.h>
#include <qitemselectionmodel.h>
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
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qvector.h>
#include <qwidget.h>

#include "qtscriptshell_QHeaderView.h"

static const char * const qtscript_QHeaderView_function_names[] = {
    "QHeaderView"
    // static
    // prototype
    , "count"
    , "hiddenSectionCount"
    , "hideSection"
    , "isSectionHidden"
    , "length"
    , "logicalIndex"
    , "logicalIndexAt"
    , "moveSection"
    , "offset"
    , "orientation"
    , "resizeContentsPrecision"
    , "resizeSection"
    , "resizeSections"
    , "restoreState"
    , "saveState"
    , "sectionPosition"
    , "sectionResizeMode"
    , "sectionSize"
    , "sectionSizeHint"
    , "sectionViewportPosition"
    , "sectionsClickable"
    , "sectionsHidden"
    , "sectionsMovable"
    , "sectionsMoved"
    , "setResizeContentsPrecision"
    , "setSectionHidden"
    , "setSectionResizeMode"
    , "setSectionsClickable"
    , "setSectionsMovable"
    , "setSortIndicator"
    , "setVisible"
    , "showSection"
    , "sortIndicatorOrder"
    , "sortIndicatorSection"
    , "stretchSectionCount"
    , "swapSections"
    , "visualIndex"
    , "visualIndexAt"
    , "toString"
};

static const char * const qtscript_QHeaderView_function_signatures[] = {
    "Orientation orientation, QWidget parent"
    // static
    // prototype
    , ""
    , ""
    , "int logicalIndex"
    , "int logicalIndex"
    , ""
    , "int visualIndex"
    , "QPoint pos\nint position\nint x, int y"
    , "int from, int to"
    , ""
    , ""
    , ""
    , "int logicalIndex, int size"
    , "ResizeMode mode"
    , "QByteArray state"
    , ""
    , "int logicalIndex"
    , "int logicalIndex"
    , "int logicalIndex"
    , "int logicalIndex"
    , "int logicalIndex"
    , ""
    , ""
    , ""
    , ""
    , "int precision"
    , "int logicalIndex, bool hide"
    , "ResizeMode mode\nint logicalIndex, ResizeMode mode"
    , "bool clickable"
    , "bool movable"
    , "int logicalIndex, SortOrder order"
    , "bool v"
    , "int logicalIndex"
    , ""
    , ""
    , ""
    , "int first, int second"
    , "int logicalIndex"
    , "int position"
""
};

static const int qtscript_QHeaderView_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 0
    , 1
    , 1
    , 0
    , 1
    , 2
    , 2
    , 0
    , 0
    , 0
    , 2
    , 1
    , 1
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
    , 1
    , 2
    , 2
    , 1
    , 1
    , 2
    , 1
    , 1
    , 0
    , 0
    , 0
    , 2
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QHeaderView_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QHeaderView::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QHeaderView_metaObject()
{
    return &QHeaderView::staticMetaObject;
}

Q_DECLARE_METATYPE(QHeaderView*)
Q_DECLARE_METATYPE(QtScriptShell_QHeaderView*)
Q_DECLARE_METATYPE(QHeaderView::ResizeMode)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QAbstractItemView*)

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
// QHeaderView::ResizeMode
//

static const QHeaderView::ResizeMode qtscript_QHeaderView_ResizeMode_values[] = {
    QHeaderView::Interactive
    , QHeaderView::Stretch
    , QHeaderView::Fixed
    , QHeaderView::ResizeToContents
};

static const char * const qtscript_QHeaderView_ResizeMode_keys[] = {
    "Interactive"
    , "Stretch"
    , "Fixed"
    , "ResizeToContents"
};

static QString qtscript_QHeaderView_ResizeMode_toStringHelper(QHeaderView::ResizeMode value)
{
    const QMetaObject *meta = qtscript_QHeaderView_metaObject();
    int idx = meta->indexOfEnumerator("ResizeMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QHeaderView_ResizeMode_toScriptValue(QScriptEngine *engine, const QHeaderView::ResizeMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QHeaderView"));
    return clazz.property(qtscript_QHeaderView_ResizeMode_toStringHelper(value));
}

static void qtscript_QHeaderView_ResizeMode_fromScriptValue(const QScriptValue &value, QHeaderView::ResizeMode &out)
{
    out = qvariant_cast<QHeaderView::ResizeMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QHeaderView_ResizeMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QHeaderView_metaObject();
    int idx = meta->indexOfEnumerator("ResizeMode");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QHeaderView::ResizeMode>(arg));
    return context->throwError(QString::fromLatin1("ResizeMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QHeaderView_ResizeMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QHeaderView::ResizeMode value = qscriptvalue_cast<QHeaderView::ResizeMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QHeaderView_ResizeMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QHeaderView::ResizeMode value = qscriptvalue_cast<QHeaderView::ResizeMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QHeaderView_ResizeMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QHeaderView_ResizeMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QHeaderView_ResizeMode,
        qtscript_QHeaderView_ResizeMode_valueOf, qtscript_QHeaderView_ResizeMode_toString);
    qScriptRegisterMetaType<QHeaderView::ResizeMode>(engine, qtscript_QHeaderView_ResizeMode_toScriptValue,
        qtscript_QHeaderView_ResizeMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QHeaderView_ResizeMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QHeaderView_ResizeMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QHeaderView
//

static QScriptValue qtscript_QHeaderView_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 38;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QHeaderView* _q_self = qscriptvalue_cast<QHeaderView*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QHeaderView.%0(): this object is not a QHeaderView")
            .arg(qtscript_QHeaderView_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->count();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->hiddenSectionCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->hideSection(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isSectionHidden(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->length();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->logicalIndex(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            int _q_result = _q_self->logicalIndexAt(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_result = _q_self->logicalIndexAt(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_result = _q_self->logicalIndexAt(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->moveSection(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->offset();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        Qt::Orientation _q_result = _q_self->orientation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->resizeContentsPrecision();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->resizeSection(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QHeaderView::ResizeMode _q_arg0 = qscriptvalue_cast<QHeaderView::ResizeMode>(context->argument(0));
        _q_self->resizeSections(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        bool _q_result = _q_self->restoreState(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QByteArray _q_result = _q_self->saveState();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->sectionPosition(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QHeaderView::ResizeMode _q_result = _q_self->sectionResizeMode(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->sectionSize(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->sectionSizeHint(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->sectionViewportPosition(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->sectionsClickable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->sectionsHidden();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->sectionsMovable();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->sectionsMoved();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setResizeContentsPrecision(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 25:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setSectionHidden(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        QHeaderView::ResizeMode _q_arg0 = qscriptvalue_cast<QHeaderView::ResizeMode>(context->argument(0));
        _q_self->setSectionResizeMode(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QHeaderView::ResizeMode _q_arg1 = qscriptvalue_cast<QHeaderView::ResizeMode>(context->argument(1));
        _q_self->setSectionResizeMode(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSectionsClickable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSectionsMovable(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 29:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::SortOrder _q_arg1 = qscriptvalue_cast<Qt::SortOrder>(context->argument(1));
        _q_self->setSortIndicator(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 30:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setVisible(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 31:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->showSection(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 32:
    if (context->argumentCount() == 0) {
        Qt::SortOrder _q_result = _q_self->sortIndicatorOrder();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->sortIndicatorSection();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->stretchSectionCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 35:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->swapSections(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 36:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->visualIndex(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 37:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_result = _q_self->visualIndexAt(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 38: {
    QString result = QString::fromLatin1("QHeaderView");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHeaderView_throw_ambiguity_error_helper(context,
        qtscript_QHeaderView_function_names[_id+1],
        qtscript_QHeaderView_function_signatures[_id+1]);
}

static QScriptValue qtscript_QHeaderView_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QHeaderView(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        QtScriptShell_QHeaderView* _q_cpp_result = new QtScriptShell_QHeaderView(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHeaderView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QHeaderView* _q_cpp_result = new QtScriptShell_QHeaderView(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QHeaderView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QHeaderView_throw_ambiguity_error_helper(context,
        qtscript_QHeaderView_function_names[_id],
        qtscript_QHeaderView_function_signatures[_id]);
}

static QScriptValue qtscript_QHeaderView_toScriptValue(QScriptEngine *engine, QHeaderView* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QHeaderView_fromScriptValue(const QScriptValue &value, QHeaderView* &out)
{
    out = qobject_cast<QHeaderView*>(value.toQObject());
}

QScriptValue qtscript_create_QHeaderView_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QHeaderView*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QHeaderView*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractItemView*>()));
    for (int i = 0; i < 39; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QHeaderView_prototype_call, qtscript_QHeaderView_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QHeaderView_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QHeaderView*>(engine, qtscript_QHeaderView_toScriptValue, 
        qtscript_QHeaderView_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QHeaderView_static_call, proto, qtscript_QHeaderView_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ResizeMode"),
        qtscript_create_QHeaderView_ResizeMode_class(engine, ctor));
    return ctor;
}
