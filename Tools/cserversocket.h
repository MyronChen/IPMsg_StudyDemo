#ifndef CSERVERSOCKET_H
#define CSERVERSOCKET_H

#include "tools.h"
#include "cservertransport.h"

ENTER_NET{

class CServerSocket : public CServerTransport
{
public:
    const static int DEFAULT_BACKLOG = 1024;

    CServerSocket();
    virtual ~CServerSocket() {}

    virtual void listen();
    virtual void close();

protected:
    virtual boost::shared_ptr<CTransport> acceptImpl();

private:
    void setReuseAddr(bool);
    void setLinger(bool lingerOn, int lingerVal);
    void setNoDelay(bool noDelay);
    void setNonblock(bool nonblock);

private:
    int _socket;
    int _interruptSocketWriter;
    int _interruptSocketReader;
    int _childInterruptWriter;
    boost::shared_ptr<int> _childInterruptReader;
};

}LEAVE_NET

#endif // CSERVERSOCKET_H
