#ifndef QTSCRIPTSHELL_QBITMAP_H
#define QTSCRIPTSHELL_QBITMAP_H

#include <qbitmap.h>

#include <QtScript/qscriptvalue.h>

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
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    QPaintEngine*  paintEngine() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QBITMAP_H
