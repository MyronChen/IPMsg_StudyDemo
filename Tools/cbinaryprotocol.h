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

    uint32_t writeMessageBegin(const std::string &name,
                                MessageType type,
                                int32_t seqid);

    uint32_t writeInt32(int32_t val);


    uint32_t readMessageBegin(std::string &name,
                             MessageType &type,
                             int32_t &seqid);

    uint32_t readInt32(int32_t &val);

private:
    const static uint32_t VERSION = 0x00fe;
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


template<class Transport_, class ByteOrder_>
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::writeMessageBegin(const std::string &name, protocol::MessageType type, int32_t seqid)
{
    uint32_t result(0);
    uint32_t version = VERSION;
    result += writeInt32(version);

    return result;
}

template<class Transport_, class ByteOrder_>
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::writeInt32(int32_t val)
{
    union bytes
    {
        uint8_t b[4];
        int32_t all;
    } theBytes;

    theBytes.all = ByteOrder_::towire32(val);

    this->_trans->write(theBytes.b, 4);

    return 4;
}

template<class Transport_, class ByteOrder_>
uint32_t CBinaryProtocolT<Transport_, ByteOrder_>::readMessageBegin(std::string &name, protocol::MessageType &type, int32_t &seqid)
{
    uint32_t result(0);
    int32_t version(0);
    result += readInt32(version);

    return result;
}

template<class Transport_, class ByteOrder_>
uint32_t CBinaryProtocolT<Transport_, ByteOrder_>::readInt32(int32_t &val)
{
    union bytes
    {
        uint8_t b[4];
        int32_t all;
    } theBytes;

    this->_trans->readall(theBytes.b, 4);

    val = ByteOrder_::fromwire32(theBytes.all);

    return 4;
}


}LEAVE_PROTOCOL

#endif // CBINARYPROTOCOL_H
