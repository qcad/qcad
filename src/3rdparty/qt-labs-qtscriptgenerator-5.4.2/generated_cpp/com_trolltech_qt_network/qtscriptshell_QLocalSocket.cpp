#include "qtscriptshell_QLocalSocket.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qlocalsocket.h>
#include <qobject.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QTimerEvent*)
Q_DECLARE_METATYPE(const char*)

QtScriptShell_QLocalSocket::QtScriptShell_QLocalSocket(QObject*  parent)
    : QLocalSocket(parent) {}

QtScriptShell_QLocalSocket::~QtScriptShell_QLocalSocket() {}

bool  QtScriptShell_QLocalSocket::atEnd() const
{
    QScriptValue _q_function = __qtscript_self.property("atEnd");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("atEnd") & QScriptValue::QObjectMember)) {
        return QLocalSocket::atEnd();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

qint64  QtScriptShell_QLocalSocket::bytesAvailable() const
{
    QScriptValue _q_function = __qtscript_self.property("bytesAvailable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bytesAvailable") & QScriptValue::QObjectMember)) {
        return QLocalSocket::bytesAvailable();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

qint64  QtScriptShell_QLocalSocket::bytesToWrite() const
{
    QScriptValue _q_function = __qtscript_self.property("bytesToWrite");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bytesToWrite") & QScriptValue::QObjectMember)) {
        return QLocalSocket::bytesToWrite();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QLocalSocket::canReadLine() const
{
    QScriptValue _q_function = __qtscript_self.property("canReadLine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canReadLine") & QScriptValue::QObjectMember)) {
        return QLocalSocket::canReadLine();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QLocalSocket::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QLocalSocket::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QLocalSocket::close()
{
    QScriptValue _q_function = __qtscript_self.property("close");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("close") & QScriptValue::QObjectMember)) {
        QLocalSocket::close();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QLocalSocket::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QLocalSocket::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QLocalSocket::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QLocalSocket::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QLocalSocket::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QLocalSocket::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

bool  QtScriptShell_QLocalSocket::isSequential() const
{
    QScriptValue _q_function = __qtscript_self.property("isSequential");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isSequential") & QScriptValue::QObjectMember)) {
        return QLocalSocket::isSequential();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QLocalSocket::open(QIODevice::OpenMode  openMode)
{
    QScriptValue _q_function = __qtscript_self.property("open");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("open") & QScriptValue::QObjectMember)) {
        return QLocalSocket::open(openMode);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, openMode)));
    }
}

qint64  QtScriptShell_QLocalSocket::pos() const
{
    QScriptValue _q_function = __qtscript_self.property("pos");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pos") & QScriptValue::QObjectMember)) {
        return QLocalSocket::pos();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

qint64  QtScriptShell_QLocalSocket::readData(char*  arg__1, qint64  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("readData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("readData") & QScriptValue::QObjectMember)) {
        return QLocalSocket::readData(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

qint64  QtScriptShell_QLocalSocket::readLineData(char*  data, qint64  maxlen)
{
    QScriptValue _q_function = __qtscript_self.property("readLineData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("readLineData") & QScriptValue::QObjectMember)) {
        return QLocalSocket::readLineData(data, maxlen);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, data)
            << qScriptValueFromValue(_q_engine, maxlen)));
    }
}

bool  QtScriptShell_QLocalSocket::reset()
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)) {
        return QLocalSocket::reset();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QLocalSocket::seek(qint64  pos)
{
    QScriptValue _q_function = __qtscript_self.property("seek");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("seek") & QScriptValue::QObjectMember)) {
        return QLocalSocket::seek(pos);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pos)));
    }
}

qint64  QtScriptShell_QLocalSocket::size() const
{
    QScriptValue _q_function = __qtscript_self.property("size");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("size") & QScriptValue::QObjectMember)) {
        return QLocalSocket::size();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QLocalSocket::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QLocalSocket::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QLocalSocket::waitForBytesWritten(int  msecs)
{
    QScriptValue _q_function = __qtscript_self.property("waitForBytesWritten");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("waitForBytesWritten") & QScriptValue::QObjectMember)) {
        return QLocalSocket::waitForBytesWritten(msecs);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, msecs)));
    }
}

bool  QtScriptShell_QLocalSocket::waitForReadyRead(int  msecs)
{
    QScriptValue _q_function = __qtscript_self.property("waitForReadyRead");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("waitForReadyRead") & QScriptValue::QObjectMember)) {
        return QLocalSocket::waitForReadyRead(msecs);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, msecs)));
    }
}

qint64  QtScriptShell_QLocalSocket::writeData(const char*  arg__1, qint64  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("writeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("writeData") & QScriptValue::QObjectMember)) {
        return QLocalSocket::writeData(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<const char *>(arg__1))
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

