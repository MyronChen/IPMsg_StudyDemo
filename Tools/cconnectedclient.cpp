#include "cconnectedclient.h"

ENTER_NET{



CConnectedClient::CConnectedClient(const boost::shared_ptr<CProcessor> &processor, const boost::shared_ptr<CProtocol> &protocol, const boost::shared_ptr<CTransport> &clientTrans)
    : _processor(processor),
      _protocol(protocol),
      _clientTrans(clientTrans)
{

}

void CConnectedClient::run()
{
    for (bool bDone(false); !bDone; )
    {
        try
        {
            _processor->process(_protocol);
        }
        catch (const CTransportException &tx)
        {
            switch (tx.getType())
            {
            case CTransportException::Timeout:
                break;
            default:
                bDone = true;
                break;
            }
        }
        catch (const CException &cx)
        {
            ;
        }
    }

}


}LEAVE_NET
