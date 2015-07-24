#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qtabwidget.h>
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
#include <qstyle.h>
#include <qstyleoption.h>
#include <qtabbar.h>
#include <qtabwidget.h>
#include <qwidget.h>

#include "qtscriptshell_QTabWidget.h"

static const char * const qtscript_QTabWidget_function_names[] = {
    "QTabWidget"
    // static
    // prototype
    , "addTab"
    , "clear"
    , "cornerWidget"
    , "currentWidget"
    , "indexOf"
    , "insertTab"
    , "isTabEnabled"
    , "minimumSizeHint"
    , "removeTab"
    , "setCornerWidget"
    , "setTabEnabled"
    , "setTabIcon"
    , "setTabText"
    , "setTabToolTip"
    , "setTabWhatsThis"
    , "sizeHint"
    , "tabBar"
    , "tabIcon"
    , "tabText"
    , "tabToolTip"
    , "tabWhatsThis"
    , "widget"
    , "toString"
};

static const char * const qtscript_QTabWidget_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , "QWidget widget, QIcon icon, String label\nQWidget widget, String arg__2"
    , ""
    , "Corner corner"
    , ""
    , "QWidget widget"
    , "int index, QWidget widget, QIcon icon, String label\nint index, QWidget widget, String arg__3"
    , "int index"
    , ""
    , "int index"
    , "QWidget w, Corner corner"
    , "int index, bool arg__2"
    , "int index, QIcon icon"
    , "int index, String arg__2"
    , "int index, String tip"
    , "int index, String text"
    , ""
    , ""
    , "int index"
    , "int index"
    , "int index"
    , "int index"
    , "int index"
""
};

static const int qtscript_QTabWidget_function_lengths[] = {
    1
    // static
    // prototype
    , 3
    , 0
    , 1
    , 0
    , 1
    , 4
    , 1
    , 0
    , 1
    , 2
    , 2
    , 2
    , 2
    , 2
    , 2
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QTabWidget_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTabWidget::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

static const QMetaObject *qtscript_QTabWidget_metaObject()
{
    return &QTabWidget::staticMetaObject;
}

Q_DECLARE_METATYPE(QTabWidget*)
Q_DECLARE_METATYPE(QtScriptShell_QTabWidget*)
Q_DECLARE_METATYPE(QTabWidget::TabPosition)
Q_DECLARE_METATYPE(QTabWidget::TabShape)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(Qt::Corner)
Q_DECLARE_METATYPE(QTabBar*)

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
// QTabWidget::TabPosition
//

static const QTabWidget::TabPosition qtscript_QTabWidget_TabPosition_values[] = {
    QTabWidget::North
    , QTabWidget::South
    , QTabWidget::West
    , QTabWidget::East
};

static const char * const qtscript_QTabWidget_TabPosition_keys[] = {
    "North"
    , "South"
    , "West"
    , "East"
};

static QString qtscript_QTabWidget_TabPosition_toStringHelper(QTabWidget::TabPosition value)
{
    const QMetaObject *meta = qtscript_QTabWidget_metaObject();
    int idx = meta->indexOfEnumerator("TabPosition");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QTabWidget_TabPosition_toScriptValue(QScriptEngine *engine, const QTabWidget::TabPosition &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTabWidget"));
    return clazz.property(qtscript_QTabWidget_TabPosition_toStringHelper(value));
}

static void qtscript_QTabWidget_TabPosition_fromScriptValue(const QScriptValue &value, QTabWidget::TabPosition &out)
{
    out = qvariant_cast<QTabWidget::TabPosition>(value.toVariant());
}

static QScriptValue qtscript_construct_QTabWidget_TabPosition(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QTabWidget_metaObject();
    int idx = meta->indexOfEnumerator("TabPosition");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QTabWidget::TabPosition>(arg));
    return context->throwError(QString::fromLatin1("TabPosition(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTabWidget_TabPosition_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTabWidget::TabPosition value = qscriptvalue_cast<QTabWidget::TabPosition>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTabWidget_TabPosition_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTabWidget::TabPosition value = qscriptvalue_cast<QTabWidget::TabPosition>(context->thisObject());
    return QScriptValue(engine, qtscript_QTabWidget_TabPosition_toStringHelper(value));
}

static QScriptValue qtscript_create_QTabWidget_TabPosition_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTabWidget_TabPosition,
        qtscript_QTabWidget_TabPosition_valueOf, qtscript_QTabWidget_TabPosition_toString);
    qScriptRegisterMetaType<QTabWidget::TabPosition>(engine, qtscript_QTabWidget_TabPosition_toScriptValue,
        qtscript_QTabWidget_TabPosition_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTabWidget_TabPosition_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTabWidget_TabPosition_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTabWidget::TabShape
//

static const QTabWidget::TabShape qtscript_QTabWidget_TabShape_values[] = {
    QTabWidget::Rounded
    , QTabWidget::Triangular
};

static const char * const qtscript_QTabWidget_TabShape_keys[] = {
    "Rounded"
    , "Triangular"
};

static QString qtscript_QTabWidget_TabShape_toStringHelper(QTabWidget::TabShape value)
{
    const QMetaObject *meta = qtscript_QTabWidget_metaObject();
    int idx = meta->indexOfEnumerator("TabShape");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    return QString::fromLatin1(menum.valueToKey(value));
}

static QScriptValue qtscript_QTabWidget_TabShape_toScriptValue(QScriptEngine *engine, const QTabWidget::TabShape &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QTabWidget"));
    return clazz.property(qtscript_QTabWidget_TabShape_toStringHelper(value));
}

static void qtscript_QTabWidget_TabShape_fromScriptValue(const QScriptValue &value, QTabWidget::TabShape &out)
{
    out = qvariant_cast<QTabWidget::TabShape>(value.toVariant());
}

static QScriptValue qtscript_construct_QTabWidget_TabShape(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    const QMetaObject *meta = qtscript_QTabWidget_metaObject();
    int idx = meta->indexOfEnumerator("TabShape");
    Q_ASSERT(idx != -1);
    QMetaEnum menum = meta->enumerator(idx);
    if (menum.valueToKey(arg) != 0)
        return qScriptValueFromValue(engine,  static_cast<QTabWidget::TabShape>(arg));
    return context->throwError(QString::fromLatin1("TabShape(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QTabWidget_TabShape_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QTabWidget::TabShape value = qscriptvalue_cast<QTabWidget::TabShape>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QTabWidget_TabShape_toString(QScriptContext *context, QScriptEngine *engine)
{
    QTabWidget::TabShape value = qscriptvalue_cast<QTabWidget::TabShape>(context->thisObject());
    return QScriptValue(engine, qtscript_QTabWidget_TabShape_toStringHelper(value));
}

static QScriptValue qtscript_create_QTabWidget_TabShape_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QTabWidget_TabShape,
        qtscript_QTabWidget_TabShape_valueOf, qtscript_QTabWidget_TabShape_toString);
    qScriptRegisterMetaType<QTabWidget::TabShape>(engine, qtscript_QTabWidget_TabShape_toScriptValue,
        qtscript_QTabWidget_TabShape_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QTabWidget_TabShape_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QTabWidget_TabShape_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QTabWidget
//

static QScriptValue qtscript_QTabWidget_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 22;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QTabWidget* _q_self = qscriptvalue_cast<QTabWidget*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTabWidget.%0(): this object is not a QTabWidget")
            .arg(qtscript_QTabWidget_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        int _q_result = _q_self->addTab(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QIcon _q_arg1 = qscriptvalue_cast<QIcon>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        int _q_result = _q_self->addTab(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        _q_self->clear();
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->cornerWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        Qt::Corner _q_arg0 = qscriptvalue_cast<Qt::Corner>(context->argument(0));
        QWidget* _q_result = _q_self->cornerWidget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->currentWidget();
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
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QString _q_arg2 = context->argument(2).toString();
        int _q_result = _q_self->insertTab(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QIcon _q_arg2 = qscriptvalue_cast<QIcon>(context->argument(2));
        QString _q_arg3 = context->argument(3).toString();
        int _q_result = _q_self->insertTab(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isTabEnabled(_q_arg0);
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
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->removeTab(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        _q_self->setCornerWidget(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        Qt::Corner _q_arg1 = qscriptvalue_cast<Qt::Corner>(context->argument(1));
        _q_self->setCornerWidget(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setTabEnabled(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QIcon _q_arg1 = qscriptvalue_cast<QIcon>(context->argument(1));
        _q_self->setTabIcon(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setTabText(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setTabToolTip(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_arg1 = context->argument(1).toString();
        _q_self->setTabWhatsThis(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QTabBar* _q_result = _q_self->tabBar();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QIcon _q_result = _q_self->tabIcon(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->tabText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->tabToolTip(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QString _q_result = _q_self->tabWhatsThis(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        QWidget* _q_result = _q_self->widget(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 22: {
    QString result = QString::fromLatin1("QTabWidget");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTabWidget_throw_ambiguity_error_helper(context,
        qtscript_QTabWidget_function_names[_id+1],
        qtscript_QTabWidget_function_signatures[_id+1]);
}

static QScriptValue qtscript_QTabWidget_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QTabWidget(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QTabWidget* _q_cpp_result = new QtScriptShell_QTabWidget();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTabWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QTabWidget* _q_cpp_result = new QtScriptShell_QTabWidget(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QTabWidget*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QTabWidget_throw_ambiguity_error_helper(context,
        qtscript_QTabWidget_function_names[_id],
        qtscript_QTabWidget_function_signatures[_id]);
}

static QScriptValue qtscript_QTabWidget_toScriptValue(QScriptEngine *engine, QTabWidget* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QTabWidget_fromScriptValue(const QScriptValue &value, QTabWidget* &out)
{
    out = qobject_cast<QTabWidget*>(value.toQObject());
}

QScriptValue qtscript_create_QTabWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTabWidget*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QTabWidget*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 23; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTabWidget_prototype_call, qtscript_QTabWidget_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTabWidget_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QTabWidget*>(engine, qtscript_QTabWidget_toScriptValue, 
        qtscript_QTabWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QTabWidget_static_call, proto, qtscript_QTabWidget_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("TabPosition"),
        qtscript_create_QTabWidget_TabPosition_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("TabShape"),
        qtscript_create_QTabWidget_TabShape_class(engine, ctor));
    return ctor;
}
