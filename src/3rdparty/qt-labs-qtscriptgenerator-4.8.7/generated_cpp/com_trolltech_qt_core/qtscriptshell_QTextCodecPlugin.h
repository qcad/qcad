#ifndef QTSCRIPTSHELL_QTEXTCODECPLUGIN_H
#define QTSCRIPTSHELL_QTEXTCODECPLUGIN_H

#include <qtextcodecplugin.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTextCodecPlugin : public QTextCodecPlugin
{
public:
    QtScriptShell_QTextCodecPlugin(QObject*  parent = 0);
    ~QtScriptShell_QTextCodecPlugin();

    QList<QByteArray >  aliases() const;
    void childEvent(QChildEvent*  arg__1);
    QTextCodec*  createForMib(int  mib);
    QTextCodec*  createForName(const QByteArray&  name);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QList<int >  mibEnums() const;
    QList<QByteArray >  names() const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTCODECPLUGIN_H
