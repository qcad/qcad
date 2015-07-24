#include "qtscriptshell_QBoxLayout.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qboxlayout.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qlist.h>
#include <qmargins.h>
#include <qobject.h>
#include <qrect.h>
#include <qsize.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QLayoutItem*)
Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::Orientation>)
Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(QSpacerItem*)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QBoxLayout::QtScriptShell_QBoxLayout(QBoxLayout::Direction  arg__1, QWidget*  parent)
    : QBoxLayout(arg__1, parent) {}

QtScriptShell_QBoxLayout::~QtScriptShell_QBoxLayout() {}

void QtScriptShell_QBoxLayout::addItem(QLayoutItem*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("addItem");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("addItem") & QScriptValue::QObjectMember)) {
        QBoxLayout::addItem(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QBoxLayout::childEvent(QChildEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QBoxLayout::childEvent(e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, e));
    }
}

int  QtScriptShell_QBoxLayout::count() const
{
    QScriptValue _q_function = __qtscript_self.property("count");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("count") & QScriptValue::QObjectMember)) {
        return QBoxLayout::count();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QBoxLayout::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QBoxLayout::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QBoxLayout::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QBoxLayout::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QBoxLayout::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QBoxLayout::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

Qt::Orientations  QtScriptShell_QBoxLayout::expandingDirections() const
{
    QScriptValue _q_function = __qtscript_self.property("expandingDirections");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("expandingDirections") & QScriptValue::QObjectMember)) {
        return QBoxLayout::expandingDirections();
    } else {
        return qscriptvalue_cast<Qt::Orientations >(_q_function.call(__qtscript_self));
    }
}

QRect  QtScriptShell_QBoxLayout::geometry() const
{
    QScriptValue _q_function = __qtscript_self.property("geometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("geometry") & QScriptValue::QObjectMember)) {
        return QBoxLayout::geometry();
    } else {
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QBoxLayout::hasHeightForWidth() const
{
    QScriptValue _q_function = __qtscript_self.property("hasHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hasHeightForWidth") & QScriptValue::QObjectMember)) {
        return QBoxLayout::hasHeightForWidth();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QBoxLayout::heightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("heightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("heightForWidth") & QScriptValue::QObjectMember)) {
        return QBoxLayout::heightForWidth(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

int  QtScriptShell_QBoxLayout::indexOf(QWidget*  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("indexOf");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("indexOf") & QScriptValue::QObjectMember)) {
        return QBoxLayout::indexOf(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

void QtScriptShell_QBoxLayout::invalidate()
{
    QScriptValue _q_function = __qtscript_self.property("invalidate");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("invalidate") & QScriptValue::QObjectMember)) {
        QBoxLayout::invalidate();
    } else {
        _q_function.call(__qtscript_self);
    }
}

bool  QtScriptShell_QBoxLayout::isEmpty() const
{
    QScriptValue _q_function = __qtscript_self.property("isEmpty");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isEmpty") & QScriptValue::QObjectMember)) {
        return QBoxLayout::isEmpty();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

QLayoutItem*  QtScriptShell_QBoxLayout::itemAt(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("itemAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemAt") & QScriptValue::QObjectMember)) {
        return QBoxLayout::itemAt(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QLayoutItem* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

QLayout*  QtScriptShell_QBoxLayout::layout()
{
    QScriptValue _q_function = __qtscript_self.property("layout");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("layout") & QScriptValue::QObjectMember)) {
        return QBoxLayout::layout();
    } else {
        return qscriptvalue_cast<QLayout* >(_q_function.call(__qtscript_self));
    }
}

QSize  QtScriptShell_QBoxLayout::maximumSize() const
{
    QScriptValue _q_function = __qtscript_self.property("maximumSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("maximumSize") & QScriptValue::QObjectMember)) {
        return QBoxLayout::maximumSize();
    } else {
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QBoxLayout::minimumHeightForWidth(int  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("minimumHeightForWidth");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minimumHeightForWidth") & QScriptValue::QObjectMember)) {
        return QBoxLayout::minimumHeightForWidth(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

QSize  QtScriptShell_QBoxLayout::minimumSize() const
{
    QScriptValue _q_function = __qtscript_self.property("minimumSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("minimumSize") & QScriptValue::QObjectMember)) {
        return QBoxLayout::minimumSize();
    } else {
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QBoxLayout::setGeometry(const QRect&  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("setGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setGeometry") & QScriptValue::QObjectMember)) {
        QBoxLayout::setGeometry(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QSize  QtScriptShell_QBoxLayout::sizeHint() const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHint") & QScriptValue::QObjectMember)) {
        return QBoxLayout::sizeHint();
    } else {
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self));
    }
}

QSpacerItem*  QtScriptShell_QBoxLayout::spacerItem()
{
    QScriptValue _q_function = __qtscript_self.property("spacerItem");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("spacerItem") & QScriptValue::QObjectMember)) {
        return QBoxLayout::spacerItem();
    } else {
        return qscriptvalue_cast<QSpacerItem* >(_q_function.call(__qtscript_self));
    }
}

QLayoutItem*  QtScriptShell_QBoxLayout::takeAt(int  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("takeAt");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("takeAt") & QScriptValue::QObjectMember)) {
        return QBoxLayout::takeAt(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QLayoutItem* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

void QtScriptShell_QBoxLayout::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QBoxLayout::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

QWidget*  QtScriptShell_QBoxLayout::widget()
{
    QScriptValue _q_function = __qtscript_self.property("widget");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("widget") & QScriptValue::QObjectMember)) {
        return QBoxLayout::widget();
    } else {
        return qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self));
    }
}

