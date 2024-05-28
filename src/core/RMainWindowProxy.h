#ifndef RMAINWINDOWPROXY_H_
#define RMAINWINDOWPROXY_H_

class QObject;
class QString;

class RMainWindowProxy
{
public:
    virtual ~RMainWindowProxy() {}

    virtual void handleEnterKey(QObject* obj) = 0;
    virtual bool handleTabKey(QObject* obj, bool backTab = false) = 0;
    virtual bool handleOptionsShortcut(const QString& shortcut) = 0;
};

#endif
