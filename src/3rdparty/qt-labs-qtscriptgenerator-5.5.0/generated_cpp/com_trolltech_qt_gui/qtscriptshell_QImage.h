#ifndef QTSCRIPTSHELL_QIMAGE_H
#define QTSCRIPTSHELL_QIMAGE_H

#include <qimage.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QImage : public QImage
{
public:
    QtScriptShell_QImage();
    QtScriptShell_QImage(const QImage&  arg__1);
    QtScriptShell_QImage(const QSize&  size, QImage::Format  format);
    QtScriptShell_QImage(const QString&  fileName, const char*  format = 0);
    QtScriptShell_QImage(const char**  xpm);
    QtScriptShell_QImage(int  width, int  height, QImage::Format  format);
    ~QtScriptShell_QImage();

    int  devType() const;
    void initPainter(QPainter*  painter) const;
    int  metric(QPaintDevice::PaintDeviceMetric  metric) const;
    QPaintEngine*  paintEngine() const;
    QPaintDevice*  redirected(QPoint*  offset) const;
    QPainter*  sharedPainter() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QIMAGE_H
