#include "qtscriptshell_QUdpSocket.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qauthenticator.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qhostaddress.h>
#include <qlist.h>
#include <qnetworkproxy.h>
#include <qobject.h>
#include <qudpsocket.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QUdpSocket::QtScriptShell_QUdpSocket(QObject*  parent)
    : QUdpSocket(parent) {}

QtScriptShell_QUdpSocket::~QtScriptShell_QUdpSocket() {}

bool  QtScriptShell_QUdpSocket::atEnd() const
{
    QScriptValue _q_function = __qtscript_self.property("atEnd");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("atEnd") & QScriptValue::QObjectMember)) {
        return QUdpSocket::atEnd();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

qint64  QtScriptShell_QUdpSocket::bytesAvailable() const
{
    QScriptValue _q_function = __qtscript_self.property("bytesAvailable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bytesAvailable") & QScriptValue::QObjectMember)) {
        return QUdpSocket::bytesAvailable();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

qint64  QtScriptShell_QUdpSocket::bytesToWrite() const
{
    QScriptValue _q_function = __qtscript_self.property("bytesToWrite");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bytesToWrite") & QScriptValue::QObjectMember)) {
        return QUdpSocket::bytesToWrite();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QUdpSocket::canReadLine() const
{
    QScriptValue _q_function = __qtscript_self.property("canReadLine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canReadLine") & QScriptValue::QObjectMember)) {
        return QUdpSocket::canReadLine();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QUdpSocket::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QUdpSocket::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QUdpSocket::close()
{
    QScriptValue _q_function = __qtscript_self.property("close");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("close") & QScriptValue::QObjectMember)) {
        QUdpSocket::close();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QUdpSocket::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QUdpSocket::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QUdpSocket::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QUdpSocket::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QUdpSocket::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QUdpSocket::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

bool  QtScriptShell_QUdpSocket::isSequential() const
{
    QScriptValue _q_function = __qtscript_self.property("isSequential");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isSequential") & QScriptValue::QObjectMember)) {
        return QUdpSocket::isSequential();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QUdpSocket::open(QIODevice::OpenMode  mode)
{
    QScriptValue _q_function = __qtscript_self.property("open");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("open") & QScriptValue::QObjectMember)) {
        return QUdpSocket::open(mode);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, mode)));
    }
}

qint64  QtScriptShell_QUdpSocket::pos() const
{
    QScriptValue _q_function = __qtscript_self.property("pos");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pos") & QScriptValue::QObjectMember)) {
        return QUdpSocket::pos();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

qint64  QtScriptShell_QUdpSocket::readData(char*  data, qint64  maxlen)
{
    QScriptValue _q_function = __qtscript_self.property("readData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("readData") & QScriptValue::QObjectMember)) {
        return QUdpSocket::readData(data, maxlen);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, data)
            << qScriptValueFromValue(_q_engine, maxlen)));
    }
}

qint64  QtScriptShell_QUdpSocket::readLineData(char*  data, qint64  maxlen)
{
    QScriptValue _q_function = __qtscript_self.property("readLineData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("readLineData") & QScriptValue::QObjectMember)) {
        return QUdpSocket::readLineData(data, maxlen);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, data)
            << qScriptValueFromValue(_q_engine, maxlen)));
    }
}

bool  QtScriptShell_QUdpSocket::reset()
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)) {
        return QUdpSocket::reset();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QUdpSocket::seek(qint64  pos)
{
    QScriptValue _q_function = __qtscript_self.property("seek");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("seek") & QScriptValue::QObjectMember)) {
        return QUdpSocket::seek(pos);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pos)));
    }
}

qint64  QtScriptShell_QUdpSocket::size() const
{
    QScriptValue _q_function = __qtscript_self.property("size");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("size") & QScriptValue::QObjectMember)) {
        return QUdpSocket::size();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QUdpSocket::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QUdpSocket::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QUdpSocket::waitForBytesWritten(int  msecs)
{
    QScriptValue _q_function = __qtscript_self.property("waitForBytesWritten");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("waitForBytesWritten") & QScriptValue::QObjectMember)) {
        return QUdpSocket::waitForBytesWritten(msecs);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, msecs)));
    }
}

bool  QtScriptShell_QUdpSocket::waitForReadyRead(int  msecs)
{
    QScriptValue _q_function = __qtscript_self.property("waitForReadyRead");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("waitForReadyRead") & QScriptValue::QObjectMember)) {
        return QUdpSocket::waitForReadyRead(msecs);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, msecs)));
    }
}

qint64  QtScriptShell_QUdpSocket::writeData(const char*  data, qint64  len)
{
    QScriptValue _q_function = __qtscript_self.property("writeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("writeData") & QScriptValue::QObjectMember)) {
        return QUdpSocket::writeData(data, len);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<char *>(data))
            << qScriptValueFromValue(_q_engine, len)));
    }
}

