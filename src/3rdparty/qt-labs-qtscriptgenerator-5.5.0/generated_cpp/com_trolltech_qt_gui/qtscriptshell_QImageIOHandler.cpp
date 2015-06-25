#include "qtscriptshell_QImageIOHandler.h"

#include <QtScript/QScriptEngine>
#include <QRect>
#include <QVariant>
#include <qbytearray.h>
#include <qimage.h>
#include <qimageiohandler.h>
#include <qiodevice.h>
#include <qrect.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QImageIOHandler::ImageOption)
Q_DECLARE_METATYPE(QImage*)

QtScriptShell_QImageIOHandler::QtScriptShell_QImageIOHandler()
    : QImageIOHandler() {}

QtScriptShell_QImageIOHandler::~QtScriptShell_QImageIOHandler() {}

bool  QtScriptShell_QImageIOHandler::canRead() const
{
    QScriptValue _q_function = __qtscript_self.property("canRead");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("canRead") & QScriptValue::QObjectMember)) {
        qFatal("QImageIOHandler::canRead() is abstract!");
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QImageIOHandler::currentImageNumber() const
{
    QScriptValue _q_function = __qtscript_self.property("currentImageNumber");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("currentImageNumber") & QScriptValue::QObjectMember)) {
        return QImageIOHandler::currentImageNumber();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

QRect  QtScriptShell_QImageIOHandler::currentImageRect() const
{
    QScriptValue _q_function = __qtscript_self.property("currentImageRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("currentImageRect") & QScriptValue::QObjectMember)) {
        return QImageIOHandler::currentImageRect();
    } else {
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QImageIOHandler::imageCount() const
{
    QScriptValue _q_function = __qtscript_self.property("imageCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("imageCount") & QScriptValue::QObjectMember)) {
        return QImageIOHandler::imageCount();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

bool  QtScriptShell_QImageIOHandler::jumpToImage(int  imageNumber)
{
    QScriptValue _q_function = __qtscript_self.property("jumpToImage");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("jumpToImage") & QScriptValue::QObjectMember)) {
        return QImageIOHandler::jumpToImage(imageNumber);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, imageNumber)));
    }
}

bool  QtScriptShell_QImageIOHandler::jumpToNextImage()
{
    QScriptValue _q_function = __qtscript_self.property("jumpToNextImage");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("jumpToNextImage") & QScriptValue::QObjectMember)) {
        return QImageIOHandler::jumpToNextImage();
    } else {
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QImageIOHandler::loopCount() const
{
    QScriptValue _q_function = __qtscript_self.property("loopCount");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("loopCount") & QScriptValue::QObjectMember)) {
        return QImageIOHandler::loopCount();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QImageIOHandler::nextImageDelay() const
{
    QScriptValue _q_function = __qtscript_self.property("nextImageDelay");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("nextImageDelay") & QScriptValue::QObjectMember)) {
        return QImageIOHandler::nextImageDelay();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

QVariant  QtScriptShell_QImageIOHandler::option(QImageIOHandler::ImageOption  option) const
{
    QScriptValue _q_function = __qtscript_self.property("option");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("option") & QScriptValue::QObjectMember)) {
        return QImageIOHandler::option(option);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QVariant >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, option)));
    }
}

bool  QtScriptShell_QImageIOHandler::read(QImage*  image)
{
    QScriptValue _q_function = __qtscript_self.property("read");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("read") & QScriptValue::QObjectMember)) {
        qFatal("QImageIOHandler::read() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, image)));
    }
}

void QtScriptShell_QImageIOHandler::setOption(QImageIOHandler::ImageOption  option, const QVariant&  value)
{
    QScriptValue _q_function = __qtscript_self.property("setOption");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setOption") & QScriptValue::QObjectMember)) {
        QImageIOHandler::setOption(option, value);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, value));
    }
}

bool  QtScriptShell_QImageIOHandler::supportsOption(QImageIOHandler::ImageOption  option) const
{
    QScriptValue _q_function = __qtscript_self.property("supportsOption");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("supportsOption") & QScriptValue::QObjectMember)) {
        return QImageIOHandler::supportsOption(option);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, option)));
    }
}

bool  QtScriptShell_QImageIOHandler::write(const QImage&  image)
{
    QScriptValue _q_function = __qtscript_self.property("write");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("write") & QScriptValue::QObjectMember)) {
        return QImageIOHandler::write(image);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, image)));
    }
}

