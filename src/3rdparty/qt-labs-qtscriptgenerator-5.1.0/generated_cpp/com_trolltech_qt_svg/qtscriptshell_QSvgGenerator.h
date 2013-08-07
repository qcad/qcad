#ifndef QTSCRIPTSHELL_QSVGGENERATOR_H
#define QTSCRIPTSHELL_QSVGGENERATOR_H

#include <qsvggenerator.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSvgGenerator : public QSvgGenerator
{
public:
    QtScriptShell_QSvgGenerator();
    ~QtScriptShell_QSvgGenerator();

    int  devType() const;
    void initPainter(QPainter*  painter) const;
    int  metric(QPaintDevice::PaintDeviceMetric  metric) const;
    QPaintEngine*  paintEngine() const;
    QPaintDevice*  redirected(QPoint*  offset) const;
    QPainter*  sharedPainter() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSVGGENERATOR_H
