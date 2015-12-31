#ifndef CBINARYPROTOCOL_H
#define CBINARYPROTOCOL_H

#include "cdefaultprotocol.h"
#include "tools.h"
#include <limits>

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

    uint32_t writeMessageEnd();

    uint32_t writeInt32(int32_t val);

    uint32_t writeStructBegin(const char *name);

    uint32_t writeStructEnd();

    uint32_t writeFieldBegin(const std::string &name,
                              FieldType type,
                              int16_t fieldid);

    uint32_t writeFieldEnd();

    uint32_t writeFieldStop();

    uint32_t writeString(const std::string &val);

    uint32_t readMessageBegin(std::string &name,
                             MessageType &type,
                             int32_t &seqid);

    uint32_t readMessageEnd() { return 0; }

    uint32_t readFieldBegin(std::string &name,
                           FieldType &type,
                           int16_t &fieldid);

    uint32_t readFieldEnd() { return 0; }

    uint32_t readString(std::string &val);

    uint32_t readInt32(int32_t &val);

    uint32_t readStructBegin(std::string &name);

    uint32_t readStructEnd();

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

    result += writeString(name);
    result += writeInt32(type);
    result += writeInt32(seqid);

    return result;
}

template<class Transport_, class ByteOrder_>
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::writeMessageEnd()
{
    return 0;
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
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::writeStructBegin(const char *name)
{
    name;
    return 0;
}

template<class Transport_, class ByteOrder_>
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::writeStructEnd()
{
    return 0;
}

template<class Transport_, class ByteOrder_>
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::writeFieldBegin(const std::string &name, protocol::FieldType type, int16_t fieldid)
{
    uint32_t b = writeInt32((int32_t)type);
    b += writeInt32((int32_t)fieldid);
    return b;
}

template<class Transport_, class ByteOrder_>
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::writeFieldEnd()
{
    return 0;
}

template<class Transport_, class ByteOrder_>
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::writeFieldStop()
{
    uint32_t b = writeInt32((int32_t)C_STOP);
    return b;
}

template<class Transport_, class ByteOrder_>
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::writeString(const std::string &val)
{
    if (val.size() > static_cast<size_t>(std::numeric_limits<int32_t>::max()) )
        throw CTransportException(CTransportException::OverLimit);

    uint32_t len = val.size();
    uint32_t wBytes = writeInt32((uint32_t)len);
    if (len > 0)
    {
        this->_trans->write((const uint8_t *)val.data(), len);
        wBytes += len;
    }

    return wBytes;
}




template<class Transport_, class ByteOrder_>
uint32_t CBinaryProtocolT<Transport_, ByteOrder_>::readMessageBegin(std::string &name, protocol::MessageType &type, int32_t &seqid)
{
    uint32_t result(0);
    int32_t version(0);
    result += readInt32(version);

    if (version != VERSION)
        throw CTransportException(CTransportException::BadVer);

    result += this->readString(name);

    int32_t b;
    result += readInt32(b);
    type = (protocol::MessageType)b;
    result += readInt32(seqid);

    return result;
}

template<class Transport_, class ByteOrder_>
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::readFieldBegin(std::string &name, protocol::FieldType &type, int16_t &fieldid)
{
    uint32_t result(0);

    int32_t b;
    result += readInt32(b);
    type = (protocol::FieldType)b;
    if (type == C_STOP)
    {
        fieldid = 0;
        return result;
    }

    result += readInt32(b);
    fieldid = (int16_t)b;

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

template<class Transport_, class ByteOrder_>
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::readString(std::string &val)
{
    uint32_t result(0);

    int32_t len;
    result += readInt32(len);
    if (len <= 0)
    {
        val.clear();
        return result;
    }

    val.resize(len);
    result += this->_trans->readall(reinterpret_cast<uint8_t*>(&val[0]), len);

    return result;
}

template<class Transport_, class ByteOrder_>
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::readStructBegin(std::string &name)
{
    name;
    return 0;
}

template<class Transport_, class ByteOrder_>
uint32_t protocol::CBinaryProtocolT<Transport_, ByteOrder_>::readStructEnd()
{
    return 0;
}

}LEAVE_PROTOCOL

#endif // CBINARYPROTOCOL_H
