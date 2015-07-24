#ifndef QTSCRIPTSHELL_QPICTURE_H
#define QTSCRIPTSHELL_QPICTURE_H

#include <qpicture.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QPicture : public QPicture
{
public:
    QtScriptShell_QPicture(const QPicture&  arg__1);
    QtScriptShell_QPicture(int  formatVersion = -1);
    ~QtScriptShell_QPicture();

    int  devType() const;
    int  metric(QPaintDevice::PaintDeviceMetric  m) const;
    QPaintEngine*  paintEngine() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPICTURE_H
