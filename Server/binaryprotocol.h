#ifndef BINARYPROTOCOL
#define BINARYPROTOCOL

#include "tools.h"
#include "cbinaryprotocol.h"
#include "session.h"

ENTER_PROTOCOL{

class BinaryProtocol : public CBinaryProtocol
{
public:
    BinaryProtocol(boost::shared_ptr<CTransport> trans)
        : CBinaryProtocol(trans)
    {}

    virtual uint32_t readMessageBegin_virt(std::string &name,
                             MessageType &type,
                             int32_t &seqid)
    {
        uint32_t result(0);
        int32_t version(0);
        result += readInt32(version);
        if (version != VERSION)
            throw CTransportException(CTransportException::BadVer);

        std::string user;
        result += readString(user);
        Session::instance()->setCurrentUser(user);
        result += CBinaryProtocol::readMessageBegin_virt(name, type, seqid);
        return result;
    }

};


class BinaryProtocolFactory : public CProtocolFactory
{
public:
    virtual boost::shared_ptr<CProtocol> getProtocol(boost::shared_ptr<CTransport> trans)
    {
        CProtocol *prot = new BinaryProtocol(trans);
        return boost::shared_ptr<CProtocol>(prot);
    }
};

} LEAVE_PROTOCOL


#endif // BINARYPROTOCOL

