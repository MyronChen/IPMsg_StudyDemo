#ifndef CSERVERTRANSPORT_H
#define CSERVERTRANSPORT_H

#include "ctransport.h"

class CServerTransport
{
public:
    CServerTransport();
    virtual ~CServerTransport(){}

    virtual void listen() = 0;
    boost::shared_ptr<CTransport> accept()
    {
        boost::shared_ptr<CTransport> trans = acceptImpl();
        if (!trans)
        {
            throw CException();
        }

        return trans;
    }

    virtual void interrupt(){}

    virtual void interruptChildren(){}

    virtual void close() = 0;

protected:

    virtual boost::shared_ptr<CTransport> acceptImpl() = 0;




};

#endif // CSERVERTRANSPORT_H
