#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtabbar.h>
#include <QIcon>
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
#include <qstyle.h>
#include <qstyleoption.h>
#include <qtabbar.h>
#include <qwidget.h>

#include "qtscriptshell_QTabBar.h"

static const char * const qtscript_QTabBar_function_names[] = {
    "QTabBar"
    // static
    // prototype
    , "addTab"
    , "insertTab"
    , "isTabEnabled"
    , "minimumSizeHint"
    , "moveTab"
    , "removeTab"
    , "setTabButton"
    , "setTabData"
    , "setTabEnabled"
    , "setTabIcon"
    , "setTabText"
    , "setTabTextColor"
    , "setTabToolTip"
    , "setTabWhatsThis"
    , "sizeHint"
    , "tabAt"
    , "tabButton"
    , "tabData"
    , "tabIcon"
    , "tabRect"
    , "tabText"
    , "tabTextColor"
    , "tabToolTip"
    , "tabWhatsThis"
    , "toString"
};

static const char * const qtscript_QTabBar_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "QIcon icon, String text\nString text"
    , "int index, QIcon icon, String text\nint index, String text"
    , "int index"
    , ""
    , "int from, int to"
    , "int index"
    , "int index, ButtonPosition position, QWidget widget"
    , "int index, Object data"
    , "int index, bool arg__2"
    , "int index, QIcon icon"
    , "int index, String text"
    , "int index, QColor color"
    , "int index, String tip"
    , "int index, String text"
    , ""
    , "QPoint pos"
    , "int index, ButtonPosition position"
    , "int index"
    , "int index"
    , "int index"
    , "int index"
    , "int index"
    , "int index"
    , "int index"
""
};

static const int qtscript_QTabBar_function_lengths[] = {
    1
    // static
    // prototype
    , 2
    , 3
    , 1
    , 0
    , 2
    , 1
    , 3
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 0
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QTabBar_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTabBar::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QTabBar_metaObject()
{
    return &QTabBar::staticMetaObject;
}

Q_DECLARE_METATYPE(QTabBar*)
Q_DECLARE_METATYPE(QtScriptShell_QTabBar*)
Q_DECLARE_METATYPE(QTabBar::Shape)
Q_DECLARE_METATYPE(QTabBar::ButtonPosition)
Q_DECLARE_METATYPE(QTabBar::SelectionBehavior)
Q_DECLARE_METATYPE(QWidget*)

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
// QTabBar::Shape
//

static const QTabBar::Shape qtscript_QTabBar_Shape_values[] = {
    QTabBar::RoundedNorth
    , QTabBar::RoundedSouth
    , QTabBar::RoundedWest
    , QTabBar::RoundedEast
    , QTabBar::TriangularNorth
    , QTabBar::TriangularSouth
    , QTabBar::TriangularWest
    , QTabBar::TriangularEast
};

static const char * const qtscript_QTabBar_Shape_keys[] = {
    "RoundedNorth"
    , "RoundedSouth"
    , "RoundedWest"
    , "RoundedEast"
    , "TriangularNorth"
    , "TriangularSouth"
    , "TriangularWest"
    , "TriangularEast"
};

static QString qtscript_QTabBar_Shape_toStringHelper(QTabBar::Shape value)
{
    const QMetaObject *meta = qtscript_QTabBar_metaObject();
    int idx = meta->indexOfEnumerator("Shape");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QTabBar_Shape_toScriptValue(QScriptEngine *engine, const QTabBar::Shape &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTabBar"));
    return clazz.property(qtscript_QTabBar_Shape_toStringHelper(value));
}

static void qtscript_QTabBar_Shape_fromScriptValue(const QScriptValue &value, QTabBar::Shape &out)
{
    out = qvariant_cast<QTabBar::Shape>(value.toVariant());
}

static QScriptValue qtscript_construct_QTabBar_Shape(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QTabBar_metaObject();
    int idx = meta->indexOfEnumerator("Shape");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QTabBar::Shape>(arg));
    return context->throwError(QString::fromLatin1("Shape(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTabBar_Shape_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTabBar::Shape value = qscriptvalue_cast<QTabBar::Shape>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTabBar_Shape_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTabBar::Shape value = qscriptvalue_cast<QTabBar::Shape>(context->thisObject());
    return QScriptValue(engine, qtscript_QTabBar_Shape_toStringHelper(value));
}

static QScriptValue qtscript_create_QTabBar_Shape_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTabBar_Shape,
        qtscript_QTabBar_Shape_valueOf, qtscript_QTabBar_Shape_toString);
    qScriptRegisterMetaType<QTabBar::Shape>(engine, qtscript_QTabBar_Shape_toScriptValue,
        qtscript_QTabBar_Shape_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 8; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTabBar_Shape_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTabBar_Shape_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTabBar::ButtonPosition
//

static const QTabBar::ButtonPosition qtscript_QTabBar_ButtonPosition_values[] = {
    QTabBar::LeftSide
    , QTabBar::RightSide
};

static const char * const qtscript_QTabBar_ButtonPosition_keys[] = {
    "LeftSide"
    , "RightSide"
};

static QString qtscript_QTabBar_ButtonPosition_toStringHelper(QTabBar::ButtonPosition value)
{
    if ((value >= QTabBar::LeftSide) && (value <= QTabBar::RightSide))
        return qtscript_QTabBar_ButtonPosition_keys[static_cast<int>(value)-static_cast<int>(QTabBar::LeftSide)];
    return QString();
}

static QScriptValue qtscript_QTabBar_ButtonPosition_toScriptValue(QScriptEngine *engine, const QTabBar::ButtonPosition &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTabBar"));
    return clazz.property(qtscript_QTabBar_ButtonPosition_toStringHelper(value));
}

static void qtscript_QTabBar_ButtonPosition_fromScriptValue(const QScriptValue &value, QTabBar::ButtonPosition &out)
{
    out = qvariant_cast<QTabBar::ButtonPosition>(value.toVariant());
}

static QScriptValue qtscript_construct_QTabBar_ButtonPosition(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTabBar::LeftSide) && (arg <= QTabBar::RightSide))
        return qScriptValueFromValue(engine,  static_cast<QTabBar::ButtonPosition>(arg));
    return context->throwError(QString::fromLatin1("ButtonPosition(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTabBar_ButtonPosition_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTabBar::ButtonPosition value = qscriptvalue_cast<QTabBar::ButtonPosition>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTabBar_ButtonPosition_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTabBar::ButtonPosition value = qscriptvalue_cast<QTabBar::ButtonPosition>(context->thisObject());
    return QScriptValue(engine, qtscript_QTabBar_ButtonPosition_toStringHelper(value));
}

static QScriptValue qtscript_create_QTabBar_ButtonPosition_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTabBar_ButtonPosition,
        qtscript_QTabBar_ButtonPosition_valueOf, qtscript_QTabBar_ButtonPosition_toString);
    qScriptRegisterMetaType<QTabBar::ButtonPosition>(engine, qtscript_QTabBar_ButtonPosition_toScriptValue,
        qtscript_QTabBar_ButtonPosition_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTabBar_ButtonPosition_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTabBar_ButtonPosition_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTabBar::SelectionBehavior
//

static const QTabBar::SelectionBehavior qtscript_QTabBar_SelectionBehavior_values[] = {
    QTabBar::SelectLeftTab
    , QTabBar::SelectRightTab
    , QTabBar::SelectPreviousTab
};

static const char * const qtscript_QTabBar_SelectionBehavior_keys[] = {
    "SelectLeftTab"
    , "SelectRightTab"
    , "SelectPreviousTab"
};

static QString qtscript_QTabBar_SelectionBehavior_toStringHelper(QTabBar::SelectionBehavior value)
{
    if ((value >= QTabBar::SelectLeftTab) && (value <= QTabBar::SelectPreviousTab))
        return qtscript_QTabBar_SelectionBehavior_keys[static_cast<int>(value)-static_cast<int>(QTabBar::SelectLeftTab)];
    return QString();
}

static QScriptValue qtscript_QTabBar_SelectionBehavior_toScriptValue(QScriptEngine *engine, const QTabBar::SelectionBehavior &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTabBar"));
    return clazz.property(qtscript_QTabBar_SelectionBehavior_toStringHelper(value));
}

static void qtscript_QTabBar_SelectionBehavior_fromScriptValue(const QScriptValue &value, QTabBar::SelectionBehavior &out)
{
    out = qvariant_cast<QTabBar::SelectionBehavior>(value.toVariant());
}

static QScriptValue qtscript_construct_QTabBar_SelectionBehavior(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QTabBar::SelectLeftTab) && (arg <= QTabBar::SelectPreviousTab))
        return qScriptValueFromValue(engine,  static_cast<QTabBar::SelectionBehavior>(arg));
    return context->throwError(QString::fromLatin1("SelectionBehavior(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTabBar_SelectionBehavior_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTabBar::SelectionBehavior value = qscriptvalue_cast<QTabBar::SelectionBehavior>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTabBar_SelectionBehavior_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTabBar::SelectionBehavior value = qscriptvalue_cast<QTabBar::SelectionBehavior>(context->thisObject());
    return QScriptValue(engine, qtscript_QTabBar_SelectionBehavior_toStringHelper(value));
}

static QScriptValue qtscript_create_QTabBar_SelectionBehavior_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTabBar_SelectionBehavior,
        qtscript_QTabBar_SelectionBehavior_valueOf, qtscript_QTabBar_SelectionBehavior_toString);
    qScriptRegisterMetaType<QTabBar::SelectionBehavior>(engine, qtscript_QTabBar_SelectionBehavior_toScriptValue,
        qtscript_QTabBar_SelectionBehavior_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTabBar_SelectionBehavior_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTabBar_SelectionBehavior_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTabBar
//

static QScriptValue qtscript_QTabBar_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 24;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTabBar* _q_self = qscriptvalue_cast<QTabBar*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTabBar.%0(): this object is not a QTabBar")
            .arg(qtscript_QTabBar_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        int _q_result = _q_self->addTab(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        int _q_result = _q_self->addTab(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        int _q_result = _q_self->insertTab(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QIcon _q_arg1 = qscriptvalue_cast<QIcon>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        int _q_result = _q_self->insertTab(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isTabEnabled(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->minimumSizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        _q_self->moveTab(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->removeTab(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 6:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QTabBar::ButtonPosition _q_arg1 = qscriptvalue_cast<QTabBar::ButtonPosition>(context->argument(1));
        QWidget* _q_arg2 = qscriptvalue_cast<QWidget*>(context->argument(2));
        _q_self->setTabButton(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setTabData(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setTabEnabled(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QIcon _q_arg1 = qscriptvalue_cast<QIcon>(context->argument(1));
        _q_self->setTabIcon(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setTabText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QColor _q_arg1 = qscriptvalue_cast<QColor>(context->argument(1));
        _q_self->setTabTextColor(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setTabToolTip(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setTabWhatsThis(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        int _q_result = _q_self->tabAt(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QTabBar::ButtonPosition _q_arg1 = qscriptvalue_cast<QTabBar::ButtonPosition>(context->argument(1));
        QWidget* _q_result = _q_self->tabButton(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QVariant _q_result = _q_self->tabData(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QIcon _q_result = _q_self->tabIcon(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QRect _q_result = _q_self->tabRect(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->tabText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QColor _q_result = _q_self->tabTextColor(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->tabToolTip(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->tabWhatsThis(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 24: {
    QString result = QString::fromLatin1("QTabBar");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTabBar_throw_ambiguity_error_helper(context,
        qtscript_QTabBar_function_names[_id+1],
        qtscript_QTabBar_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTabBar_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTabBar(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTabBar* _q_cpp_result = new QtScriptShell_QTabBar();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTabBar*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QTabBar* _q_cpp_result = new QtScriptShell_QTabBar(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTabBar*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTabBar_throw_ambiguity_error_helper(context,
        qtscript_QTabBar_function_names[_id],
        qtscript_QTabBar_function_signatures[_id]);
}

static QScriptValue qtscript_QTabBar_toScriptValue(QScriptEngine *engine, QTabBar* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTabBar_fromScriptValue(const QScriptValue &value, QTabBar* &out)
{
    out = qobject_cast<QTabBar*>(value.toQObject());
}

QScriptValue qtscript_create_QTabBar_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTabBar*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTabBar*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 25; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTabBar_prototype_call, qtscript_QTabBar_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTabBar_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTabBar*>(engine, qtscript_QTabBar_toScriptValue, 
        qtscript_QTabBar_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTabBar_static_call, proto, qtscript_QTabBar_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Shape"),
        qtscript_create_QTabBar_Shape_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ButtonPosition"),
        qtscript_create_QTabBar_ButtonPosition_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SelectionBehavior"),
        qtscript_create_QTabBar_SelectionBehavior_class(engine, ctor));
    return ctor;
}
