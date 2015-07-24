#ifndef QTSCRIPTSHELL_QICONENGINEPLUGINV2_H
#define QTSCRIPTSHELL_QICONENGINEPLUGINV2_H

#include <qiconengineplugin.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QIconEnginePluginV2 : public QIconEnginePluginV2
{
public:
    QtScriptShell_QIconEnginePluginV2(QObject*  parent = 0);
    ~QtScriptShell_QIconEnginePluginV2();

    void childEvent(QChildEvent*  arg__1);
    QIconEngineV2*  create(const QString&  filename = QString());
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QStringList  keys() const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QICONENGINEPLUGINV2_H
