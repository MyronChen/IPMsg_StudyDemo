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

typedef CBinaryProtocolT<CTransport> CBinaryProtocol;

}LEAVE_PROTOCOL

#endif // CBINARYPROTOCOL_H
