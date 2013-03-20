#include "qtscriptshell_QCompleter.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qbytearray.h>
#include <qcompleter.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qrect.h>
#include <qstringlist.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QModelIndex)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QCompleter::QtScriptShell_QCompleter(QAbstractItemModel*  model, QObject*  parent)
    : QCompleter(model, parent) {}

QtScriptShell_QCompleter::QtScriptShell_QCompleter(QObject*  parent)
    : QCompleter(parent) {}

QtScriptShell_QCompleter::QtScriptShell_QCompleter(const QStringList&  completions, QObject*  parent)
    : QCompleter(completions, parent) {}

QtScriptShell_QCompleter::~QtScriptShell_QCompleter() {}

void QtScriptShell_QCompleter::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QCompleter::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QCompleter::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QCompleter::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QCompleter::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QCompleter::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QCompleter::eventFilter(QObject*  o, QEvent*  e)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QCompleter::eventFilter(o, e);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, o)
            << qScriptValueFromValue(_q_engine, e)));
    }
}

QString  QtScriptShell_QCompleter::pathFromIndex(const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("pathFromIndex");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pathFromIndex") & QScriptValue::QObjectMember)) {
        return QCompleter::pathFromIndex(index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, index)));
    }
}

QStringList  QtScriptShell_QCompleter::splitPath(const QString&  path) const
{
    QScriptValue _q_function = __qtscript_self.property("splitPath");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("splitPath") & QScriptValue::QObjectMember)) {
        return QCompleter::splitPath(path);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QStringList >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, path)));
    }
}

void QtScriptShell_QCompleter::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QCompleter::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

