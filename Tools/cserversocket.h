#ifndef CSERVERSOCKET_H
#define CSERVERSOCKET_H

#include "tools.h"
#include "cservertransport.h"

ENTER_NET{

class CServerSocket : public CServerTransport
{
public:
    CServerSocket();
    virtual ~CServerSocket() {}

    virtual void listen();

private:
    int _interruptSocketWriter;
    int _interruptSocketReader;
    int _childInterruptWriter;
    boost::shared_ptr<int> _childInterruptReader;
};

}LEAVE_NET

#endif // CSERVERSOCKET_H
