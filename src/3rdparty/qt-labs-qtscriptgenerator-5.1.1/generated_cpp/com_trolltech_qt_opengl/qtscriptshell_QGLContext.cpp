#include "qtscriptshell_QGLContext.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcolor.h>
#include <qgl.h>
#include <qpaintdevice.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(const QGLContext*)

QtScriptShell_QGLContext::QtScriptShell_QGLContext(const QGLFormat&  format)
    : QGLContext(format) {}

QtScriptShell_QGLContext::QtScriptShell_QGLContext(const QGLFormat&  format, QPaintDevice*  device)
    : QGLContext(format, device) {}

QtScriptShell_QGLContext::~QtScriptShell_QGLContext() {}

bool  QtScriptShell_QGLContext::chooseContext(const QGLContext*  shareContext)
{
    QScriptValue _q_function = __qtscript_self.property("chooseContext");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("chooseContext") & QScriptValue::QObjectMember)) {
        return QGLContext::chooseContext(shareContext);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<const QGLContext *>(shareContext))));
    }
}

bool  QtScriptShell_QGLContext::create(const QGLContext*  shareContext)
{
    QScriptValue _q_function = __qtscript_self.property("create");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("create") & QScriptValue::QObjectMember)) {
        return QGLContext::create(shareContext);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, const_cast<const QGLContext *>(shareContext))));
    }
}

void QtScriptShell_QGLContext::doneCurrent()
{
    QScriptValue _q_function = __qtscript_self.property("doneCurrent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("doneCurrent") & QScriptValue::QObjectMember)) {
        QGLContext::doneCurrent();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QGLContext::makeCurrent()
{
    QScriptValue _q_function = __qtscript_self.property("makeCurrent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("makeCurrent") & QScriptValue::QObjectMember)) {
        QGLContext::makeCurrent();
    } else {
        _q_function.call(__qtscript_self);
    }
}

void QtScriptShell_QGLContext::swapBuffers() const
{
    QScriptValue _q_function = __qtscript_self.property("swapBuffers");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("swapBuffers") & QScriptValue::QObjectMember)) {
        QGLContext::swapBuffers();
    } else {
        _q_function.call(__qtscript_self);
    }
}

