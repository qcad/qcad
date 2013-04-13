#ifndef RDXFPLUGIN_H_
#define RDXFPLUGIN_H_

#include <QDebug>
#include <QObject>
#include <QStringList>

#include "RPluginInterface.h"

class RSpline;

class RDxfPlugin : public QObject, public RPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(RPluginInterface)

public:
    virtual bool init();
    virtual void initScriptExtensions(QScriptEngine&) {}
    virtual RPluginInfo getPluginInfo();
};

#endif
