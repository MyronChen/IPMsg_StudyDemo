#ifndef CSERVER_H
#define CSERVER_H

#include "tools.h"
#include "cserversocket.h"
#include "cbinaryprotocol.h"
#include "cprocessor.h"
#include "cconnectedclient.h"

using namespace CNetFramework::protocol;

ENTER_NET{

class CServer
{
public:
    CServer(boost::shared_ptr<CProcessor> process,
            boost::shared_ptr<CServerSocket> socket,
            boost::shared_ptr<CProtocolFactory> factory);

    virtual ~CServer() {}

    virtual void serve();

private:
    virtual void onClientConnected(boost::shared_ptr<CConnectedClient>);

private:
    boost::shared_ptr<CProcessor> _process;
    boost::shared_ptr<CServerSocket> _serverTransport;
    boost::shared_ptr<CProtocolFactory> _factory;
};




} LEAVE_NET

#endif // CSERVER_H
