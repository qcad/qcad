#ifndef RDXFSERVICESPROXY_H_
#define RDXFSERVICESPROXY_H_

class QObject;
class QString;

class RDxfServicesProxy
{
public:
    virtual ~RDxfServicesProxy() {}

    virtual QString decodeMifString(const QString& input) = 0;
};

#endif
