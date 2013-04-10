#ifndef QTSCRIPTSHELL_QIMAGE_H
#define QTSCRIPTSHELL_QIMAGE_H

#include <qimage.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QImage : public QImage
{
public:
    QtScriptShell_QImage();
    QtScriptShell_QImage(const QImage&  arg__1);
    QtScriptShell_QImage(const QSize&  size, QImage::Format  format);
    QtScriptShell_QImage(const QString&  fileName, const char*  format = 0);
    QtScriptShell_QImage(const char*  fileName, const char*  format = 0);
    QtScriptShell_QImage(const char**  xpm);
    QtScriptShell_QImage(const uchar*  data, int  width, int  height, QImage::Format  format);
    QtScriptShell_QImage(const uchar*  data, int  width, int  height, int  bytesPerLine, QImage::Format  format);
    QtScriptShell_QImage(int  width, int  height, QImage::Format  format);
    QtScriptShell_QImage(uchar*  data, int  width, int  height, QImage::Format  format);
    QtScriptShell_QImage(uchar*  data, int  width, int  height, int  bytesPerLine, QImage::Format  format);
    ~QtScriptShell_QImage();

    int  devType() const;
    int  metric(QPaintDevice::PaintDeviceMetric  metric) const;
    QPaintEngine*  paintEngine() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QIMAGE_H
