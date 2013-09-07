#ifndef QTSCRIPTSHELL_QPICTURE_H
#define QTSCRIPTSHELL_QPICTURE_H

#include <qpicture.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPicture : public QPicture
{
public:
    QtScriptShell_QPicture(const QPicture&  arg__1);
    QtScriptShell_QPicture(int  formatVersion = -1);
    ~QtScriptShell_QPicture();

    int  devType() const;
    void initPainter(QPainter*  painter) const;
    int  metric(QPaintDevice::PaintDeviceMetric  m) const;
    QPaintEngine*  paintEngine() const;
    QPaintDevice*  redirected(QPoint*  offset) const;
    QPainter*  sharedPainter() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPICTURE_H
