#include "qtscriptshell_QIconEngine.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qpainter.h>
#include <qpixmap.h>
#include <qrect.h>
#include <qsize.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QIcon::Mode)
Q_DECLARE_METATYPE(QIcon::State)
Q_DECLARE_METATYPE(QPainter*)

QtScriptShell_QIconEngine::QtScriptShell_QIconEngine()
    : QIconEngine() {}

QtScriptShell_QIconEngine::~QtScriptShell_QIconEngine() {}

QSize  QtScriptShell_QIconEngine::actualSize(const QSize&  size, QIcon::Mode  mode, QIcon::State  state)
{
    QScriptValue _q_function = __qtscript_self.property("actualSize");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("actualSize") & QScriptValue::QObjectMember)) {
        return QIconEngine::actualSize(size, mode, state);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, size)
            << qScriptValueFromValue(_q_engine, mode)
            << qScriptValueFromValue(_q_engine, state)));
    }
}

void QtScriptShell_QIconEngine::addFile(const QString&  fileName, const QSize&  size, QIcon::Mode  mode, QIcon::State  state)
{
    QScriptValue _q_function = __qtscript_self.property("addFile");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("addFile") & QScriptValue::QObjectMember)) {
        QIconEngine::addFile(fileName, size, mode, state);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, fileName)
            << qScriptValueFromValue(_q_engine, size)
            << qScriptValueFromValue(_q_engine, mode)
            << qScriptValueFromValue(_q_engine, state));
    }
}

void QtScriptShell_QIconEngine::addPixmap(const QPixmap&  pixmap, QIcon::Mode  mode, QIcon::State  state)
{
    QScriptValue _q_function = __qtscript_self.property("addPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("addPixmap") & QScriptValue::QObjectMember)) {
        QIconEngine::addPixmap(pixmap, mode, state);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pixmap)
            << qScriptValueFromValue(_q_engine, mode)
            << qScriptValueFromValue(_q_engine, state));
    }
}

void QtScriptShell_QIconEngine::paint(QPainter*  painter, const QRect&  rect, QIcon::Mode  mode, QIcon::State  state)
{
    QScriptValue _q_function = __qtscript_self.property("paint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paint") & QScriptValue::QObjectMember)) {
        qFatal("QIconEngine::paint() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, mode)
            << qScriptValueFromValue(_q_engine, state));
    }
}

QPixmap  QtScriptShell_QIconEngine::pixmap(const QSize&  size, QIcon::Mode  mode, QIcon::State  state)
{
    QScriptValue _q_function = __qtscript_self.property("pixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pixmap") & QScriptValue::QObjectMember)) {
        return QIconEngine::pixmap(size, mode, state);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QPixmap >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, size)
            << qScriptValueFromValue(_q_engine, mode)
            << qScriptValueFromValue(_q_engine, state)));
    }
}

