#ifndef QTSCRIPTSHELL_PLATFORMPLUGIN_H
#define QTSCRIPTSHELL_PLATFORMPLUGIN_H

#include <platformplugin.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_PlatformPlugin : public Phonon::PlatformPlugin
{
public:
    QtScriptShell_PlatformPlugin();
    ~QtScriptShell_PlatformPlugin();

    QString  applicationName() const;
    QObject*  createBackend();
    QObject*  createBackend(const QString&  library, const QString&  version);
    Phonon::AbstractMediaStream*  createMediaStream(const QUrl&  url, QObject*  parent);
    QIcon  icon(const QString&  name) const;
    bool  isMimeTypeAvailable(const QString&  mimeType) const;
    qreal  loadVolume(const QString&  outputName) const;
    void notification(const char*  notificationName, const QString&  text, const QStringList&  actions = QStringList(), QObject*  receiver = 0, const char*  actionSlot = 0) const;
    QList<int >  objectDescriptionIndexes(Phonon::ObjectDescriptionType  type) const;
    QHash<QByteArray , QVariant >  objectDescriptionProperties(Phonon::ObjectDescriptionType  type, int  index) const;
    void saveVolume(const QString&  outputName, qreal  volume);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_PLATFORMPLUGIN_H
