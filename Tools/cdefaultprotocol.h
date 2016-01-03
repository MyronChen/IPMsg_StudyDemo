#ifndef CDEFAULTPROTOCOL_H
#define CDEFAULTPROTOCOL_H

#include <cprotocol.h>

USING_NET
ENTER_PROTOCOL{

class CDefaultProtocol : public CProtocol
{
public:
    uint32_t writeMessageBegin(const std::string &name,
                              MessageType type,
                              int32_t seqid)
    {
        throw CException();
    }

    uint32_t writeMessageEnd()
    {
        throw CException();
    }

    uint32_t writeFieldBegin(const std::string &name,
                                 FieldType type,
                                 int16_t fieldid)
    {
        throw CException();
    }

    uint32_t writeFieldEnd()
    {
        throw CException();
    }

    uint32_t writeStructBegin(const char *name)
    {
        throw CException();
    }

    uint32_t writeStructEnd()
    {
        throw CException();
    }

    uint32_t writeString(const std::string &val)
    {
        throw CException();
    }

    uint32_t writeInt32(int32_t val)
    {
        throw CException();
    }

    uint32_t writeDouble(double val)
    {
        throw CException();
    }

    uint32_t writeFieldStop()
    {
        throw CException();
    }

    uint32_t writeMapBegin(FieldType type1, FieldType type2, int32_t size)
    {
        throw CException();
    }

    uint32_t writeMapEnd()
    {
        throw CException();
    }

    uint32_t readMessageBegin(std::string &name,
                             MessageType &type,
                             int32_t &seqid)
    {
        throw CException();
    }

    uint32_t readMessageEnd()
    {
        throw CException();
    }

    uint32_t readFieldBegin(std::string &name,
                           FieldType &type,
                           int16_t &fieldid)
    {
        throw CException();
    }
    uint32_t readFieldEnd()
    {
        throw CException();
    }

    uint32_t readStructBegin(std::string &name)
    {
        throw CException();
    }

    uint32_t readStructEnd()
    {
        throw CException();
    }

    uint32_t readString(std::string &val)
    {
        throw CException();
    }

    uint32_t readInt32(int32_t &val)
    {
        throw CException();
    }

    uint32_t readDouble(double &val)
    {
        throw CException();
    }

    uint32_t readMapBegin(FieldType &type1, FieldType &type2, int32_t &size)
    {
        throw CException();
    }

    uint32_t readMapEnd()
    {
        throw CException();
    }

protected:
    CDefaultProtocol(boost::shared_ptr<CTransport> trans)
        : CProtocol(trans)
    {}
};

template<class Protocol_, class Super_ = CDefaultProtocol>
class CVirtualProtocol : public Super_
{
public:
    virtual uint32_t writeMessageBegin_virt(const std::string &name,
                              MessageType type,
                              int32_t seqid)
    {
        return static_cast<Protocol_*>(this)->writeMessageBegin(name, type, seqid);
    }

    virtual uint32_t writeMessageEnd_virt()
    {
        return static_cast<Protocol_*>(this)->writeMessageEnd();
    }

    virtual uint32_t writeFieldBegin_virt(const std::string &name,
                                 FieldType type,
                                 int16_t fieldid)
    {
        return static_cast<Protocol_*>(this)->writeFieldBegin(name, type, fieldid);
    }

    virtual uint32_t writeFieldEnd_virt()
    {
        return static_cast<Protocol_*>(this)->writeFieldEnd();
    }

    virtual uint32_t writeStructBegin_virt(const char *name)
    {
        return static_cast<Protocol_*>(this)->writeStructBegin(name);
    }

    virtual uint32_t writeStructEnd_virt()
    {
        return static_cast<Protocol_*>(this)->writeStructEnd();
    }

    virtual uint32_t writeString_virt(const std::string &val)
    {
        return static_cast<Protocol_*>(this)->writeString(val);
    }

    virtual uint32_t writeInt32_virt(int32_t val)
    {
        return static_cast<Protocol_*>(this)->writeInt32(val);
    }

    virtual uint32_t writeDouble_virt(double val)
    {
        return static_cast<Protocol_*>(this)->writeDouble(val);
    }

    virtual uint32_t writeFieldStop_virt()
    {
        return static_cast<Protocol_*>(this)->writeFieldStop();
    }

    virtual uint32_t writeMapBegin_virt(FieldType type1, FieldType type2, int32_t size)
    {
        return static_cast<Protocol_*>(this)->writeMapBegin(type1, type2, size);
    }

    virtual uint32_t writeMapEnd_virt()
    {
        return static_cast<Protocol_*>(this)->writeMapEnd();
    }

    virtual uint32_t readMessageBegin_virt(std::string &name,
                             MessageType &type,
                             int32_t &seqid)
    {
        return static_cast<Protocol_*>(this)->readMessageBegin(name, type, seqid);
    }

    virtual uint32_t readMessageEnd_virt()
    {
        return static_cast<Protocol_*>(this)->readMessageEnd();
    }

    virtual uint32_t readFieldBegin_virt(std::string &name,
                           FieldType &type,
                           int16_t &fieldid)
    {
        return static_cast<Protocol_*>(this)->readFieldBegin(name, type, fieldid);
    }
    virtual uint32_t readFieldEnd_virt()
    {
        return static_cast<Protocol_*>(this)->readFieldEnd();
    }

    virtual uint32_t readStructBegin_virt(std::string &name)
    {
        return static_cast<Protocol_*>(this)->readStructBegin(name);
    }
    virtual uint32_t readStructEnd_virt()
    {
        return static_cast<Protocol_*>(this)->readStructEnd();
    }

    virtual uint32_t readString_virt(std::string &val)
    {
        return static_cast<Protocol_*>(this)->readString(val);
    }

    virtual uint32_t readInt32_virt(int32_t &val)
    {
        return static_cast<Protocol_*>(this)->readInt32(val);
    }

    virtual uint32_t readDouble_virt(double &val)
    {
        return static_cast<Protocol_*>(this)->readDouble(val);
    }

    virtual uint32_t readMapBegin_virt(FieldType &type1, FieldType &type2, int32_t &size)
    {
        return static_cast<Protocol_*>(this)->readMapBegin(type1, type2, size);
    }

    virtual uint32_t readMapEnd_virt()
    {
        return static_cast<Protocol_*>(this)->readMapEnd();
    }

protected:
    CVirtualProtocol(boost::shared_ptr<CTransport> trans)
        : Super_(trans)
    {}
};


}LEAVE_PROTOCOL

#endif // CDEFAULTPROTOCOL_H
