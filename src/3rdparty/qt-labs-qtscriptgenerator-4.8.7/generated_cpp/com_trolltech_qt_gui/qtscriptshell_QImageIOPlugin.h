#ifndef QTSCRIPTSHELL_QIMAGEIOPLUGIN_H
#define QTSCRIPTSHELL_QIMAGEIOPLUGIN_H

#include <qimageiohandler.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QImageIOPlugin : public QImageIOPlugin
{
public:
    QtScriptShell_QImageIOPlugin(QObject*  parent = 0);
    ~QtScriptShell_QImageIOPlugin();

    QImageIOPlugin::Capabilities  capabilities(QIODevice*  device, const QByteArray&  format) const;
    void childEvent(QChildEvent*  arg__1);
    QImageIOHandler*  create(QIODevice*  device, const QByteArray&  format = QByteArray()) const;
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QStringList  keys() const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QIMAGEIOPLUGIN_H
