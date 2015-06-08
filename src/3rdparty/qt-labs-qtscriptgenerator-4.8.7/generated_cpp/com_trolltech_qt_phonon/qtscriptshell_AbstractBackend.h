#ifndef QTSCRIPTSHELL_ABSTRACTBACKEND_H
#define QTSCRIPTSHELL_ABSTRACTBACKEND_H

#include <backendinterface.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_AbstractBackend : public Phonon::BackendInterface
{
public:
    QtScriptShell_AbstractBackend();
    ~QtScriptShell_AbstractBackend();

    QStringList  availableMimeTypes() const;
    bool  connectNodes(QObject*  arg__1, QObject*  arg__2);
    QObject*  createObject(Phonon::BackendInterface::Class  c, QObject*  parent, const QList<QVariant >&  args = QList<QVariant>());
    bool  disconnectNodes(QObject*  arg__1, QObject*  arg__2);
    bool  endConnectionChange(QSet<QObject* >  arg__1);
    QList<int >  objectDescriptionIndexes(Phonon::ObjectDescriptionType  type) const;
    QHash<QByteArray , QVariant >  objectDescriptionProperties(Phonon::ObjectDescriptionType  type, int  index) const;
    bool  startConnectionChange(QSet<QObject* >  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_ABSTRACTBACKEND_H
