#include "cprocessor.h"

ENTER_NET{


CProcessor::CProcessor()
{

}

bool CProcessor::process(boost::shared_ptr<CProtocol> proto)
{
    std::string name;
    MessageType type;
    int32_t seqid(0);
    proto->readMessageBegin(name, type, seqid);

    if (type != C_Call)
        return false;

    dispatchProcess(proto.get(), name, seqid);

}

} LEAVE_NET
