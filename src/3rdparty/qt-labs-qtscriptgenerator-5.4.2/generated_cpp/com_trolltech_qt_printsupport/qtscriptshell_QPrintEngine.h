#ifndef QTSCRIPTSHELL_QPRINTENGINE_H
#define QTSCRIPTSHELL_QPRINTENGINE_H

#include <qprintengine.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPrintEngine : public QPrintEngine
{
public:
    QtScriptShell_QPrintEngine();
    ~QtScriptShell_QPrintEngine();

    bool  abort();
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    bool  newPage();
    QPrinter::PrinterState  printerState() const;
    QVariant  property(QPrintEngine::PrintEnginePropertyKey  key) const;
    void setProperty(QPrintEngine::PrintEnginePropertyKey  key, const QVariant&  value);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPRINTENGINE_H
