#ifndef QTSCRIPTSHELL_QSVGGENERATOR_H
#define QTSCRIPTSHELL_QSVGGENERATOR_H

#include <qsvggenerator.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QSvgGenerator : public QSvgGenerator
{
public:
    QtScriptShell_QSvgGenerator();
    ~QtScriptShell_QSvgGenerator();

    int  devType() const;
    int  metric(QPaintDevice::PaintDeviceMetric  metric) const;
    QPaintEngine*  paintEngine() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSVGGENERATOR_H
