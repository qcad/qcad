#include "qtscriptshell_QFile.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qfile.h>
#include <qlist.h>
#include <qobject.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QAbstractFileEngine*)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)
Q_DECLARE_METATYPE(char*)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QFile::QtScriptShell_QFile()
    : QFile() {}

QtScriptShell_QFile::QtScriptShell_QFile(QObject*  parent)
    : QFile(parent) {}

QtScriptShell_QFile::QtScriptShell_QFile(const QString&  name)
    : QFile(name) {}

QtScriptShell_QFile::QtScriptShell_QFile(const QString&  name, QObject*  parent)
    : QFile(name, parent) {}

QtScriptShell_QFile::~QtScriptShell_QFile() {}

bool  QtScriptShell_QFile::atEnd() const
{
    QScriptValue _q_function = __qtscript_self.property("atEnd");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("atEnd") & QScriptValue::QObjectMember)) {
        return QFile::atEnd();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

qint64  QtScriptShell_QFile::bytesAvailable() const
{
    QScriptValue _q_function = __qtscript_self.property("bytesAvailable");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bytesAvailable") & QScriptValue::QObjectMember)) {
        return QFile::bytesAvailable();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

qint64  QtScriptShell_QFile::bytesToWrite() const
{
    QScriptValue _q_function = __qtscript_self.property("bytesToWrite");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("bytesToWrite") & QScriptValue::QObjectMember)) {
        return QFile::bytesToWrite();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QFile::canReadLine() const
{
    QScriptValue _q_function = __qtscript_self.property("canReadLine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canReadLine") & QScriptValue::QObjectMember)) {
        return QFile::canReadLine();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QFile::childEvent(QChildEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QFile::childEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

void QtScriptShell_QFile::close()
{
    QScriptValue _q_function = __qtscript_self.property("close");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("close") & QScriptValue::QObjectMember)) {
        QFile::close();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QFile::customEvent(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QFile::customEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QFile::event(QEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QFile::event(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

bool  QtScriptShell_QFile::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QFile::eventFilter(arg__1, arg__2);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)
            << qScriptValueFromValue(_q_engine, arg__2)));
    }
}

QAbstractFileEngine*  QtScriptShell_QFile::fileEngine() const
{
    QScriptValue _q_function = __qtscript_self.property("fileEngine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("fileEngine") & QScriptValue::QObjectMember)) {
        return QFile::fileEngine();
    } else {
        return qscriptvalue_cast<QAbstractFileEngine* >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QFile::isSequential() const
{
    QScriptValue _q_function = __qtscript_self.property("isSequential");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("isSequential") & QScriptValue::QObjectMember)) {
        return QFile::isSequential();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QFile::open(QIODevice::OpenMode  flags)
{
    QScriptValue _q_function = __qtscript_self.property("open");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("open") & QScriptValue::QObjectMember)) {
        return QFile::open(flags);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, flags)));
    }
}

qint64  QtScriptShell_QFile::pos() const
{
    QScriptValue _q_function = __qtscript_self.property("pos");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pos") & QScriptValue::QObjectMember)) {
        return QFile::pos();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

qint64  QtScriptShell_QFile::readData(char*  data, qint64  maxlen)
{
    QScriptValue _q_function = __qtscript_self.property("readData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("readData") & QScriptValue::QObjectMember)) {
        return QFile::readData(data, maxlen);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, data)
            << qScriptValueFromValue(_q_engine, maxlen)));
    }
}

qint64  QtScriptShell_QFile::readLineData(char*  data, qint64  maxlen)
{
    QScriptValue _q_function = __qtscript_self.property("readLineData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("readLineData") & QScriptValue::QObjectMember)) {
        return QFile::readLineData(data, maxlen);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, data)
            << qScriptValueFromValue(_q_engine, maxlen)));
    }
}

bool  QtScriptShell_QFile::reset()
{
    QScriptValue _q_function = __qtscript_self.property("reset");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("reset") & QScriptValue::QObjectMember)) {
        return QFile::reset();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QFile::seek(qint64  offset)
{
    QScriptValue _q_function = __qtscript_self.property("seek");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("seek") & QScriptValue::QObjectMember)) {
        return QFile::seek(offset);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, offset)));
    }
}

qint64  QtScriptShell_QFile::size() const
{
    QScriptValue _q_function = __qtscript_self.property("size");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("size") & QScriptValue::QObjectMember)) {
        return QFile::size();
    } else {
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QFile::timerEvent(QTimerEvent*  arg__1)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QFile::timerEvent(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1));
    }
}

bool  QtScriptShell_QFile::waitForBytesWritten(int  msecs)
{
    QScriptValue _q_function = __qtscript_self.property("waitForBytesWritten");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("waitForBytesWritten") & QScriptValue::QObjectMember)) {
        return QFile::waitForBytesWritten(msecs);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, msecs)));
    }
}

bool  QtScriptShell_QFile::waitForReadyRead(int  msecs)
{
    QScriptValue _q_function = __qtscript_self.property("waitForReadyRead");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("waitForReadyRead") & QScriptValue::QObjectMember)) {
        return QFile::waitForReadyRead(msecs);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, msecs)));
    }
}

qint64  QtScriptShell_QFile::writeData(const char*  data, qint64  len)
{
    QScriptValue _q_function = __qtscript_self.property("writeData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("writeData") & QScriptValue::QObjectMember)) {
        return QFile::writeData(data, len);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<qint64 >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<char *>(data))
            << qScriptValueFromValue(_q_engine, len)));
    }
}

