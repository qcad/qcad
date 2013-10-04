#ifndef QTSCRIPTSHELL_QPRINTER_H
#define QTSCRIPTSHELL_QPRINTER_H

#include <qprinter.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QPrinter : public QPrinter
{
public:
    QtScriptShell_QPrinter(QPrinter::PrinterMode  mode = QPrinter::ScreenResolution);
    QtScriptShell_QPrinter(const QPrinterInfo&  printer, QPrinter::PrinterMode  mode = QPrinter::ScreenResolution);
    ~QtScriptShell_QPrinter();

    int  devType() const;
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    QPaintEngine*  paintEngine() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPRINTER_H
