#include "qtscriptshell_QLayoutItem.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qrect.h>
#include <qsize.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QFlags<Qt::Orientation>)
Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(QSpacerItem*)

QtScriptShell_QLayoutItem::QtScriptShell_QLayoutItem(Qt::Alignment  alignment)
    : QLayoutItem(alignment) {}

QtScriptShell_QLayoutItem::~QtScriptShell_QLayoutItem() {}

Qt::Orientations  QtScriptShell_QLayoutItem::expandingDirections() const
{
    QScriptValue _q_function = __qtscript_self.property("expandingDirections");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("expandingDirections") & QScriptValue::QObjectMember)) {
        qFatal("QLayoutItem::expandingDirections() is abstract!");
    } else {
        return qscriptvalue_cast<Qt::Orientations >(_q_function.call(__qtscript_self));
    }
}

QRect  QtScriptShell_QLayoutItem::geometry() const
{
    QScriptValue _q_function = __qtscript_self.property("geometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("geometry") & QScriptValue::QObjectMember)) {
        qFatal("QLayoutItem::geometry() is abstract!");
    } else {
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QLayoutItem::hasHeightForWidth() const
{
    QScriptValue _q_function = __qtscript_self.property("hasHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasHeightForWidth") & QScriptValue::QObjectMember)) {
        return QLayoutItem::hasHeightForWidth();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QLayoutItem::heightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("heightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("heightForWidth") & QScriptValue::QObjectMember)) {
        return QLayoutItem::heightForWidth(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

void QtScriptShell_QLayoutItem::invalidate()
{
    QScriptValue _q_function = __qtscript_self.property("invalidate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("invalidate") & QScriptValue::QObjectMember)) {
        QLayoutItem::invalidate();
    } else {
        _q_function.call(__qtscript_self);
    }
}

bool  QtScriptShell_QLayoutItem::isEmpty() const
{
    QScriptValue _q_function = __qtscript_self.property("isEmpty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isEmpty") & QScriptValue::QObjectMember)) {
        qFatal("QLayoutItem::isEmpty() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

QLayout*  QtScriptShell_QLayoutItem::layout()
{
    QScriptValue _q_function = __qtscript_self.property("layout");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("layout") & QScriptValue::QObjectMember)) {
        return QLayoutItem::layout();
    } else {
        return qscriptvalue_cast<QLayout* >(_q_function.call(__qtscript_self));
    }
}

QSize  QtScriptShell_QLayoutItem::maximumSize() const
{
    QScriptValue _q_function = __qtscript_self.property("maximumSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("maximumSize") & QScriptValue::QObjectMember)) {
        qFatal("QLayoutItem::maximumSize() is abstract!");
    } else {
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QLayoutItem::minimumHeightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("minimumHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minimumHeightForWidth") & QScriptValue::QObjectMember)) {
        return QLayoutItem::minimumHeightForWidth(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

QSize  QtScriptShell_QLayoutItem::minimumSize() const
{
    QScriptValue _q_function = __qtscript_self.property("minimumSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minimumSize") & QScriptValue::QObjectMember)) {
        qFatal("QLayoutItem::minimumSize() is abstract!");
    } else {
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QLayoutItem::setGeometry(const QRect&  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setGeometry") & QScriptValue::QObjectMember)) {
        qFatal("QLayoutItem::setGeometry() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QSize  QtScriptShell_QLayoutItem::sizeHint() const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHint") & QScriptValue::QObjectMember)) {
        qFatal("QLayoutItem::sizeHint() is abstract!");
    } else {
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
    }
}

QSpacerItem*  QtScriptShell_QLayoutItem::spacerItem()
{
    QScriptValue _q_function = __qtscript_self.property("spacerItem");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("spacerItem") & QScriptValue::QObjectMember)) {
        return QLayoutItem::spacerItem();
    } else {
        return qscriptvalue_cast<QSpacerItem* >(_q_function.call(__qtscript_self));
    }
}

QWidget*  QtScriptShell_QLayoutItem::widget()
{
    QScriptValue _q_function = __qtscript_self.property("widget");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("widget") & QScriptValue::QObjectMember)) {
        return QLayoutItem::widget();
    } else {
        return qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self));
    }
}

