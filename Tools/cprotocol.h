#ifndef CPROTOCOL_H
#define CPROTOCOL_H

#include "tools.h"
#include "ctransport.h"

ENTER_PROTOCOL{

enum MessageType{
    C_Call,
    C_REPLY,
    C_EXCEPTION
};

enum FieldType{
    C_STOP,
    C_STRING,
    C_INT32,
    C_DOUBLE,
    C_STRUCT
};

class CProtocol
{
public:
    //write
    virtual uint32_t writeMessageBegin_virt(const std::string &name,
                                           MessageType type,
                                           int32_t seqid) = 0;
    virtual uint32_t writeMessageEnd_virt() = 0;

    virtual uint32_t writeFieldBegin_virt(const std::string &name,
                                           FieldType type,
                                           int16_t fieldid) = 0;
    virtual uint32_t writeFieldEnd_virt() = 0;

    virtual uint32_t writeStructBegin_virt(const char *name) = 0;

    virtual uint32_t writeStructEnd_virt() = 0;

    virtual uint32_t writeString_virt(const std::string &val) = 0;

    virtual uint32_t writeInt32_virt(int32_t val) = 0;

    virtual uint32_t writeDouble_virt(double val) = 0;

    virtual uint32_t writeFieldStop_virt() = 0;

    uint32_t writeMessageBegin(const std::string &name,
                                MessageType type,
                                int32_t seqid)
    {
        return writeMessageBegin_virt(name, type, seqid);
    }

    uint32_t writeMessageEnd()
    {
        return writeMessageEnd_virt();
    }

    uint32_t writeFieldBegin(const std::string &name,
                              FieldType type,
                              int16_t fieldid)
    {
        return writeFieldBegin_virt(name, type, fieldid);
    }

    uint32_t writeFieldEnd()
    {
        return writeFieldEnd_virt();
    }

    uint32_t writeStructBegin(const char *name)
    {
        return writeStructBegin_virt(name);
    }

    uint32_t writeStructEnd()
    {
        return writeStructEnd_virt();
    }

    uint32_t writeString(const std::string &val)
    {
        return writeString_virt(val);
    }

    uint32_t writeInt32(int32_t val)
    {
        return writeInt32_virt(val);
    }

    uint32_t writeDouble(double val)
    {
        return writeDouble_virt(val);
    }

    uint32_t writeFieldStop()
    {
        return writeFieldStop_virt();
    }

    //read
    virtual uint32_t readMessageBegin_virt(std::string &name,
                                            MessageType &type,
                                            int32_t &seqid) = 0;
    virtual uint32_t readMessageEnd_virt() = 0;

    virtual uint32_t readFieldBegin_virt(std::string &name,
                                          FieldType &type,
                                          int16_t &fieldid) = 0;
    virtual uint32_t readFieldEnd_virt() = 0;

    virtual uint32_t readStructBegin_virt(std::string &name) = 0;

    virtual uint32_t readStructEnd_virt() = 0;

    virtual uint32_t readString_virt(std::string &val) = 0;

    virtual uint32_t readDouble_virt(double &val) = 0;

    virtual uint32_t readInt32_virt(int32_t &val) = 0;

    uint32_t readMessageBegin(std::string &name,
                               MessageType &type,
                               int32_t &seqid)
    {
        return readMessageBegin_virt(name, type, seqid);
    }
    uint32_t readMessageEnd()
    {
        return readMessageEnd_virt();
    }

    uint32_t readFieldBegin(std::string &name,
                             FieldType &type,
                             int16_t &fieldid)
    {
        return readFieldBegin_virt(name, type, fieldid);
    }
    uint32_t readFieldEnd()
    {
        return readFieldEnd_virt();
    }

    uint32_t readStructBegin(std::string &name)
    {
        return readStructBegin_virt(name);
    }

    uint32_t readStructEnd()
    {
        return readStructEnd_virt();
    }

    uint32_t readString(std::string &val)
    {
        return readString_virt(val);
    }

    uint32_t readInt32(int32_t &val)
    {
        return readInt32_virt(val);
    }

    uint32_t readDouble(double &val)
    {
        return readDouble_virt(val);
    }

    void increOutRecursionDepth()
    {
        if (_limit < ++_outRecursionDepth)
            throw CException();
    }

    void decreOutRecursionDepth()
    {
        _outRecursionDepth--;
    }

    void increInRecursionDepth()
    {
        if (_limit < ++_inRecursionDepth)
            throw CException();
    }

    void decreInRecursionDepth()
    {
        _inRecursionDepth--;
    }

    boost::shared_ptr<CTransport> getTransport() const
    {
        return _trans;
    }

    uint32_t skip(FieldType type)
    {
        uint32_t iBytes(0);
        int16_t iTemp16;
        std::string sTemp;
        switch(type)
        {
        case C_STRING:
            iBytes += readString(sTemp);
            break;
        case C_INT32:
            int32_t iTemp;
            iBytes += readInt32(iTemp);
            break;
        case C_DOUBLE:
            double dTemp;
            iBytes += readDouble(dTemp);
            break;
        case C_STRUCT:
        {
            iBytes += readStructBegin(sTemp);
            FieldType fldType;
            while (true)
            {
                iBytes += readFieldBegin(sTemp, fldType, iTemp16);
                if (fldType == C_STOP)
                    break;
                iBytes += skip(fldType);
                iBytes += readFieldEnd();
            }
            iBytes += readStructEnd();
            break;
        }
        default:
            ;
        }

        return iBytes;
    }

protected:
    CProtocol(boost::shared_ptr<CTransport> trans)
        : _trans(trans), _outRecursionDepth(0), _inRecursionDepth(0)
    {}

protected:
    boost::shared_ptr<CTransport> _trans;

private:
    CProtocol();
    static const uint _limit = 64;
    uint _outRecursionDepth;
    uint _inRecursionDepth;
};

struct CNetBigEndian
{
    static uint16_t towire16(const uint16_t &x) { return htons(x); }
    static uint32_t towire32(const uint32_t &x) { return htonl(x); }
    static uint16_t fromwire16(const uint16_t &x) { return ntohs(x); }
    static uint32_t fromwire32(const uint32_t &x) { return ntohl(x); }
};

class COutRecursionTraker
{
public:
    COutRecursionTraker(CProtocol &prot)
        : _prot(prot)
    {
        _prot.increOutRecursionDepth();
    }

    ~COutRecursionTraker()
    {
        _prot.decreOutRecursionDepth();
    }

private:
    CProtocol &_prot;
};

class CInRecursionTraker
{
public:
    CInRecursionTraker(CProtocol &prot)
        : _prot(prot)
    {
        _prot.increInRecursionDepth();
    }

    ~CInRecursionTraker()
    {
        _prot.decreInRecursionDepth();
    }

private:
    CProtocol &_prot;
};

class CProtocolFactory
{
public:
    virtual ~CProtocolFactory(){}
    virtual boost::shared_ptr<CProtocol> getProtocol(boost::shared_ptr<CTransport> trans) = 0;
};


}LEAVE_PROTOCOL

#endif // CPROTOCOL_H
