#ifndef QTSCRIPTSHELL_QPAINTDEVICE_H
#define QTSCRIPTSHELL_QPAINTDEVICE_H

#include <qpaintdevice.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPaintDevice : public QPaintDevice
{
public:
    QtScriptShell_QPaintDevice();
    ~QtScriptShell_QPaintDevice();

    int  devType() const;
    void initPainter(QPainter*  painter) const;
    int  metric(QPaintDevice::PaintDeviceMetric  metric) const;
    QPaintEngine*  paintEngine() const;
    QPaintDevice*  redirected(QPoint*  offset) const;
    QPainter*  sharedPainter() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPAINTDEVICE_H
