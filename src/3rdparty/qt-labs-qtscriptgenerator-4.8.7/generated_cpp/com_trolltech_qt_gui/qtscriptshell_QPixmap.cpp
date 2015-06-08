#include "qtscriptshell_QPixmap.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qdatastream.h>
#include <qimage.h>
#include <qimagereader.h>
#include <qimagewriter.h>
#include <qiodevice.h>
#include <qmatrix.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qtransform.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QPaintDevice::PaintDeviceMetric)
Q_DECLARE_METATYPE(QPaintEngine*)

QtScriptShell_QPixmap::QtScriptShell_QPixmap()
    : QPixmap() {}

QtScriptShell_QPixmap::QtScriptShell_QPixmap(const QPixmap&  arg__1)
    : QPixmap(arg__1) {}

QtScriptShell_QPixmap::QtScriptShell_QPixmap(const QSize&  arg__1)
    : QPixmap(arg__1) {}

QtScriptShell_QPixmap::QtScriptShell_QPixmap(const QString&  fileName, const char*  format, Qt::ImageConversionFlags  flags)
    : QPixmap(fileName, format, flags) {}

QtScriptShell_QPixmap::QtScriptShell_QPixmap(const char**  xpm)
    : QPixmap(xpm) {}

QtScriptShell_QPixmap::QtScriptShell_QPixmap(int  w, int  h)
    : QPixmap(w, h) {}

QtScriptShell_QPixmap::~QtScriptShell_QPixmap() {}

int  QtScriptShell_QPixmap::devType() const
{
    QScriptValue _q_function = __qtscript_self.property("devType");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("devType") & QScriptValue::QObjectMember)) {
        return QPixmap::devType();
    } else {
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self));
    }
}

int  QtScriptShell_QPixmap::metric(QPaintDevice::PaintDeviceMetric  arg__1) const
{
    QScriptValue _q_function = __qtscript_self.property("metric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("metric") & QScriptValue::QObjectMember)) {
        return QPixmap::metric(arg__1);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, arg__1)));
    }
}

QPaintEngine*  QtScriptShell_QPixmap::paintEngine() const
{
    QScriptValue _q_function = __qtscript_self.property("paintEngine");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintEngine") & QScriptValue::QObjectMember)) {
        return QPixmap::paintEngine();
    } else {
        return qscriptvalue_cast<QPaintEngine* >(_q_function.call(__qtscript_self));
    }
}

