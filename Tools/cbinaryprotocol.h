#ifndef CBINARYPROTOCOL_H
#define CBINARYPROTOCOL_H

#include "cdefaultprotocol.h"
#include "tools.h"

ENTER_PROTOCOL{

template<class Transport_, class ByteOrder_ = CNetBigEndian>
class CBinaryProtocolT : public CVirtualProtocol<CBinaryProtocolT<Transport_, ByteOrder_> >
{
public:
    CBinaryProtocolT(boost::shared_ptr<Transport_> trans)
        : CVirtualProtocol<CBinaryProtocolT<Transport_, ByteOrder_> >(trans)
    {}
};

template<class Transport_, class ByteOrder_ = CNetBigEndian>
class CBinaryProtocolFactoryT : public CProtocolFactory
{
public:
    virtual boost::shared_ptr<CProtocol> getProtocol(boost::shared_ptr<CTransport> trans)
    {
        boost::shared_ptr<Transport_> trans = boost::dynamic_pointer_cast<Transport_>(trans);
        CProtocol *prot(NULL);
        if (trans)
        {
            prot = new CBinaryProtocolT<Transport_, ByteOrder_>(trans);
        }
        else
        {
            prot = new CBinaryProtocolT<CTransport, ByteOrder_>(tarans);
        }

        return boost::shared_ptr<CProtocol>(prot);
    }
};






typedef CBinaryProtocolT<CTransport> CBinaryProtocol;
typedef CBinaryProtocolFactoryT<CTransport> CBinaryProtocolFactory;


}LEAVE_PROTOCOL

#endif // CBINARYPROTOCOL_H
