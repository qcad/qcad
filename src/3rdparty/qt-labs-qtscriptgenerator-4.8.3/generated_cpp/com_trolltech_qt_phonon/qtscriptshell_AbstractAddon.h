#ifndef QTSCRIPTSHELL_ABSTRACTADDON_H
#define QTSCRIPTSHELL_ABSTRACTADDON_H

#include <addoninterface.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_AbstractAddon : public Phonon::AddonInterface
{
public:
    QtScriptShell_AbstractAddon();
    ~QtScriptShell_AbstractAddon();

    bool  hasInterface(Phonon::AddonInterface::Interface  iface) const;
    QVariant  interfaceCall(Phonon::AddonInterface::Interface  iface, int  command, const QList<QVariant >&  arguments = QList<QVariant>());

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_ABSTRACTADDON_H
