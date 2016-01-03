#ifndef BINARYPROTOCOL
#define BINARYPROTOCOL

#include "Tools/tools.h"
#include "Tools/cbinaryprotocol.h"


ENTER_PROTOCOL{

class BinaryProtocol : public CBinaryProtocol
{
public:
    BinaryProtocol(boost::shared_ptr<CTransport> trans)
        : CBinaryProtocol(trans)
    {}

    void setUserName(const std::string &user) { _user = user; }

    virtual uint32_t writeMessageBegin_virt(const std::string &name,
                              MessageType type,
                              int32_t seqid)
    {
        uint32_t result = writeInt32(CBinaryProtocol::VERSION);
        result += writeString(_user);
        result += CBinaryProtocol::writeMessageBegin_virt(name, type, seqid);
        return result;
    }

private:
    std::string _user;
};




} LEAVE_PROTOCOL


#endif // BINARYPROTOCOL
