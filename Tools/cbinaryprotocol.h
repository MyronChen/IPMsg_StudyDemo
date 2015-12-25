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

    uint32_t readMessageBegin(std::string &name,
                             MessageType &type,
                             int32_t &seqid);

    uint32_t readInt32(int32_t &val);

};

template<class Transport_, class ByteOrder_ = CNetBigEndian>
class CBinaryProtocolFactoryT : public CProtocolFactory
{
public:
    virtual boost::shared_ptr<CProtocol> getProtocol(boost::shared_ptr<CTransport> trans)
    {
        boost::shared_ptr<Transport_> spec_trans = boost::dynamic_pointer_cast<Transport_>(trans);
        CProtocol *prot(NULL);
        if (spec_trans)
        {
            prot = new CBinaryProtocolT<Transport_, ByteOrder_>(spec_trans);
        }
        else
        {
            prot = new CBinaryProtocolT<CTransport, ByteOrder_>(trans);
        }

        return boost::shared_ptr<CProtocol>(prot);
    }
};






typedef CBinaryProtocolT<CTransport> CBinaryProtocol;
typedef CBinaryProtocolFactoryT<CTransport> CBinaryProtocolFactory;


}LEAVE_PROTOCOL

#endif // CBINARYPROTOCOL_H
