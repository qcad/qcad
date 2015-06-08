#ifndef QTSCRIPTSHELL_QWEBPLUGINFACTORY_H
#define QTSCRIPTSHELL_QWEBPLUGINFACTORY_H

#include <qwebpluginfactory.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QWebPluginFactory : public QWebPluginFactory
{
public:
    QtScriptShell_QWebPluginFactory(QObject*  parent = 0);
    ~QtScriptShell_QWebPluginFactory();

    void childEvent(QChildEvent*  arg__1);
    QObject*  create(const QString&  mimeType, const QUrl&  arg__2, const QStringList&  argumentNames, const QStringList&  argumentValues) const;
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  extension(QWebPluginFactory::Extension  extension, const QWebPluginFactory::ExtensionOption*  option = 0, QWebPluginFactory::ExtensionReturn*  output = 0);
    QList<QWebPluginFactory::Plugin >  plugins() const;
    void refreshPlugins();
    bool  supportsExtension(QWebPluginFactory::Extension  extension) const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWEBPLUGINFACTORY_H
