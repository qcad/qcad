#include "qtscriptshell_QPicture.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qdatastream.h>
#include <qiodevice.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpicture.h>
#include <qrect.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QPaintDevice::PaintDeviceMetric)
Q_DECLARE_METATYPE(QPaintEngine*)

QtScriptShell_QPicture::QtScriptShell_QPicture(const QPicture&  arg__1)
    : QPicture(arg__1) {}

QtScriptShell_QPicture::QtScriptShell_QPicture(int  formatVersion)
    : QPicture(formatVersion) {}

QtScriptShell_QPicture::~QtScriptShell_QPicture() {}

int  QtScriptShell_QPicture::devType() const
{
    QScriptValue _q_function = __qtscript_self.property("devType");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("devType") & QScriptValue::QObjectMember)) {
        return QPicture::devType();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QPicture::metric(QPaintDevice::PaintDeviceMetric  m) const
{
    QScriptValue _q_function = __qtscript_self.property("metric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metric") & QScriptValue::QObjectMember)) {
        return QPicture::metric(m);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, m)));
    }
}

QPaintEngine*  QtScriptShell_QPicture::paintEngine() const
{
    QScriptValue _q_function = __qtscript_self.property("paintEngine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEngine") & QScriptValue::QObjectMember)) {
        return QPicture::paintEngine();
    } else {
        return qscriptvalue_cast<QPaintEngine* >(_q_function.call(__qtscript_self));
    }
}

