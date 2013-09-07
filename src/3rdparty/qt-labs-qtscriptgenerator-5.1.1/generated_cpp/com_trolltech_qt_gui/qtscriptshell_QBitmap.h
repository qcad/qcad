#ifndef QTSCRIPTSHELL_QBITMAP_H
#define QTSCRIPTSHELL_QBITMAP_H

#include <qbitmap.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QBitmap : public QBitmap
{
public:
    QtScriptShell_QBitmap();
    QtScriptShell_QBitmap(const QPixmap&  arg__1);
    QtScriptShell_QBitmap(const QSize&  arg__1);
    QtScriptShell_QBitmap(const QString&  fileName, const char*  format = 0);
    QtScriptShell_QBitmap(int  w, int  h);
    ~QtScriptShell_QBitmap();

    int  devType() const;
    void initPainter(QPainter*  painter) const;
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    QPaintEngine*  paintEngine() const;
    QPaintDevice*  redirected(QPoint*  offset) const;
    QPainter*  sharedPainter() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QBITMAP_H
