#ifndef CSOCKET_H
#define CSOCKET_H
#include "ctransport.h"
#include <QString>
#include "tools.h"
#include <netdb.h>

ENTER_NET{

class CSocket : public CVirtualTransport<CSocket>
{
public:
    CSocket(const QString &addr);
    virtual ~CSocket();

    virtual void open();
    virtual void close();
    virtual bool isOpened() const;

private:
    void openConnect(addrinfo *res);
    void setLinger(bool lingerOn, int lingerVal);
    void setNoDelay(bool noDelay);

private:
    QString _addr;
    int _socket;
    bool _lingerOn;
    int _lingerVal;
    bool _noDelay;

};

}LEAVE_NET

#endif // CSOCKET_H
