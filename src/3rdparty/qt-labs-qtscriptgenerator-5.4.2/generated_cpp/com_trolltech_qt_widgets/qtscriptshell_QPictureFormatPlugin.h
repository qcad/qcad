#ifndef QTSCRIPTSHELL_QPICTUREFORMATPLUGIN_H
#define QTSCRIPTSHELL_QPICTUREFORMATPLUGIN_H

#include <qpictureformatplugin.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPictureFormatPlugin : public QPictureFormatPlugin
{
public:
    QtScriptShell_QPictureFormatPlugin(QObject*  parent = 0);
    ~QtScriptShell_QPictureFormatPlugin();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  installIOHandler(const QString&  format);
    bool  loadPicture(const QString&  format, const QString&  filename, QPicture*  pic);
    bool  savePicture(const QString&  format, const QString&  filename, const QPicture&  pic);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPICTUREFORMATPLUGIN_H
