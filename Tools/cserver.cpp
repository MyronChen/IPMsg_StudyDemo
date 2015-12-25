//#include "cserver.h"
#include "cserver.h"

using namespace boost;

ENTER_NET{

CServer::CServer(boost::shared_ptr<CProcessor> process, boost::shared_ptr<CServerSocket> socket, boost::shared_ptr<CProtocolFactory> factory)
    : _process(process),
      _serverTransport(socket),
      _factory(factory)
{

}

void CServer::serve()
{
    _serverTransport->listen();

    shared_ptr<CTransport> clientTrans;
    shared_ptr<CProtocol> clientProto;

    while(true)
    {
        clientTrans.reset();
        clientProto.reset();

        clientTrans = _serverTransport->accept();
        clientProto = _factory->getProtocol(clientTrans);

        shared_ptr<CConnectedClient> pConnectedClient = make_shared<CConnectedClient>(
                    _process, clientProto, clientTrans);
        onClientConnected(pConnectedClient);

    }

}

void CServer::onClientConnected(boost::shared_ptr<CConnectedClient> pConnectedClient)
{
    pConnectedClient->run();
}

}LEAVE_NET
