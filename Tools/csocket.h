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
    CSocket(int socket);
    virtual ~CSocket();

    virtual void open();
    virtual void close();
    virtual bool isOpened() const;
    virtual bool peek();
    uint32_t write(const uint8_t *buf, uint32_t len);
    uint32_t read(uint8_t *buf, uint32_t len);

    std::string getPeerAddr();

private:
    void openConnect(addrinfo *res);
    void setLinger(bool lingerOn, int lingerVal);
    void setNoDelay(bool noDelay);

    uint32_t writePartial(const uint8_t *buf, uint32_t len);

    void setCachedPeerAddr(const sockaddr *addr, socklen_t len);
    sockaddr *getCachedPeerAddrPtr(socklen_t &len) const;

private:
    QString _addr;
    int _socket;
    bool _lingerOn;
    int _lingerVal;
    bool _noDelay;

    union {
        sockaddr_in ipv4;
        sockaddr_in6 ipv6;
    } _cachePeerAddr;

};

}LEAVE_NET

#endif // CSOCKET_H
