#ifndef QTSCRIPTSHELL_QPIXMAP_H
#define QTSCRIPTSHELL_QPIXMAP_H

#include <qpixmap.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPixmap : public QPixmap
{
public:
    QtScriptShell_QPixmap();
    QtScriptShell_QPixmap(const QPixmap&  arg__1);
    QtScriptShell_QPixmap(const QSize&  arg__1);
    QtScriptShell_QPixmap(const QString&  fileName, const char*  format = 0, Qt::ImageConversionFlags  flags = Qt::AutoColor);
    QtScriptShell_QPixmap(const char**  xpm);
    QtScriptShell_QPixmap(int  w, int  h);
    ~QtScriptShell_QPixmap();

    int  devType() const;
    void initPainter(QPainter*  painter) const;
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    QPaintEngine*  paintEngine() const;
    QPaintDevice*  redirected(QPoint*  offset) const;
    QPainter*  sharedPainter() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPIXMAP_H
