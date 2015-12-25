#ifndef CCONNECTEDCLIENT_H
#define CCONNECTEDCLIENT_H

#include "tools.h"
#include "crunnable.h"
#include "cprotocol.h"
#include "cprocessor.h"

//USING_PROTOCOL;

ENTER_NET{



class CConnectedClient : public CRunnable
{
public:
    CConnectedClient(const boost::shared_ptr<CProcessor> &processor,
                     const boost::shared_ptr<CProtocol> &protocol,
                     const boost::shared_ptr<CTransport> &clientTrans);

    virtual void run();

private:
    const boost::shared_ptr<CProcessor> _processor;
    const boost::shared_ptr<CProtocol> _protocol;
    const boost::shared_ptr<CTransport> _clientTrans;
};

}LEAVE_NET
#endif // CCONNECTEDCLIENT_H
