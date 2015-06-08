#ifndef QTSCRIPTSHELL_QPAINTDEVICE_H
#define QTSCRIPTSHELL_QPAINTDEVICE_H

#include <qpaintdevice.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QPaintDevice : public QPaintDevice
{
public:
    QtScriptShell_QPaintDevice();
    ~QtScriptShell_QPaintDevice();

    int  devType() const;
    int  metric(QPaintDevice::PaintDeviceMetric  metric) const;
    QPaintEngine*  paintEngine() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPAINTDEVICE_H
